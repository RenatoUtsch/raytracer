Documentação do TP 2 de Computação Gráfica
Boids
2014/02
Aluno: Renato Utsch Gonçalves

== Compilando
=============
Para compilar o TP, deve-se utilizar a makefile.
Passos:
1. Extrair o zip do TP para uma nova pasta.
2. Navegar até essa pasta com o terminal.
3. Executar o comando: "make"

Para muma maior flexibilidade, também é possível utilizar o CMake.
Os passos estão a seguir:
1. Extrair o zip do tp para uma nova pasta.
2. Criar uma pasta chamada "build".
3. Navegar até a pasta "build" com o terminal.
4. Executar o comando: "cmake .."
5. Executar o comando: "make"

Um executável de nome raytracer será gerado e poderá ser
executado por "./raytracer".

As dependências do programa são apenas em um compilador de C++ que
suporta variadic macros (sendo necessário suporte de ao menos essa
feature da C++11 por parte do compilador) e na biblioteca standard
da C++03.
O CMake é uma dependência opcional.

A compilação do jogo foi testada em ambiente
Linux (Ubuntu) e OS X (OS X Yosemite).

== Decisões de Implementação
============================
O trabalho implementou todas as exigências básicas (80% da nota).

O raytracer foi feito em C++.
A implementação utilizou apenas a standard da C++ como dependência.

A implementação dividiu o código em um parser para interpretar o
arquivo de entrada, em estruturas de dados e classes para armazenar
os dados do arquivo de entrada e nas funções de ray tracing e
interseção.

As funções de ray tracing podem ser localizadas em rayTracer.cpp
e as funções de interseção em intersection.cpp.

O Ray Tracing implementado utiliza o modelo de Phong como iluminação
local e tem chamadas recursivas para reflexão e refração.

O Ray Tracer não é distribuído.
