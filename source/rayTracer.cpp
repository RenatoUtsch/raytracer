/*
 * Author: Renato Utsch Gonçalves
 * Computer Science, UFMG
 * Computer Graphics
 * Practical exercise 3 - Ray Tracer
 *
 * Copyright (c) 2014 Renato Utsch <renatoutsch@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "rayTracer.hpp"
#include "intersection.hpp"
#include "types.hpp"
#include "math/Point.hpp"
#include "math/Vector.hpp"

static Vector reflectionDirection(const Vector &dir, const Vector &normal) {
    // get the inversion of the direction.
    float c = Vector::dot((-1) * dir, normal);

    return (dir + (2 * normal * c)).normalize();
}

static Vector transmissionDirection(float refrRate, const Vector &dir,
        const Vector &normal) {
    float c1 = Vector::dot((-1) * dir, normal);
    float c2 = sqrt(1.0f - std::pow(refrRate, 2) * (1 - std::pow(c1, 2)));

    return (refrRate * dir) + (refrRate * c1 - c2) * normal;
}

Color rayTracer(Scene &scene, const Point &p, const Vector &dir, size_t depth,
        Object *exclObj) {
    Point q;
    Object obj;
    Color c;
    Vector normal;
    bool inside;

    // If the ray does not intersect with any object, just return the ambient
    // light color.
    if(!intersection(scene, p, dir, q, c, normal, obj, NULL, exclObj, &inside))
        return scene.ambient.color;

    Color ambientColor = scene.ambient.color * obj.material().ambientCoef;
    Color diffuseColor;
    Color specularColor;

    // Local component of the light.
    for(std::vector<Light>::iterator it = scene.lights.begin();
            it != scene.lights.end(); ++it) {
        Point feeler;
        Object feelerObj;
        Color feelerColor;
        Vector feelerNormal;

        // Direction
        Vector lightDir = it->pos - q;
        lightDir.normalize();

        // Distance.
        float dist = Point::distance(it->pos, q);

        // Atenuation.
        float att = 1.0f / (it->attenuation.constant + dist * it->attenuation.linear
                + std::pow(dist, 2) * it->attenuation.quadratic);

        // If the feeler ray does not intersect the surface of any object before
        // reaching the light, then the object is not shadowed.
        // If the object intersects, just use the ambient color.
        if(!intersection(scene, q, lightDir, feeler, feelerColor, feelerNormal,
                    feelerObj, &it->pos, &obj)) {
            // Diffuse light.
            float cosDiff = Vector::dot(lightDir, normal);
            if(cosDiff < FLT_EPSILON) {
                cosDiff = 0.0f;
            }

            diffuseColor += it->color * cosDiff * obj.material().diffuseCoef * att;

            // Specular light.

            // halfway vector.
            Vector e = dir * (-1); // dir é a direção da câmera ao ponto de interseção.
            Vector halfway = lightDir + e; // lightdir é normalizado.
            halfway.normalize();

            // Cos of the angle between the halfway vector and the normal.
            float cosSpec = Vector::dot(halfway, normal.normalize());
            if(cosSpec < FLT_EPSILON) {
                cosSpec = 0.0f;
            }

            // Shininess.
            cosSpec = std::pow(cosSpec, obj.material().specularExp);

            specularColor += it->color * cosSpec * obj.material().specularCoef * att;
        }
    }

    Color reflectionColor;
    Color transmissionColor;

    // Global component of the light.
    if(depth > 0) {
        // Reflected component added in recursively.
        Vector reflDir = reflectionDirection(dir, normal);
        reflectionColor = obj.material().reflectionCoef
            * rayTracer(scene, q, reflDir, depth - 1, &obj);

        // If inside the object invert the refraction rate.
        float refrRate = 1.0f / obj.material().refractionRate;
        if(inside)
            refrRate = obj.material().refractionRate;

        // Transmission component added in recursively.
        Vector transDir = transmissionDirection(refrRate, dir, normal);
        transmissionColor = obj.material().transmissionCoef
            * rayTracer(scene, q, transDir, depth - 1, &obj);
    }

    // specular color needs a sum.
    Color finalColor = ambientColor + diffuseColor + reflectionColor + transmissionColor;

    return (c * finalColor + specularColor).clamp();
}
