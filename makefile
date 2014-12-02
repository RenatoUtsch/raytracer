##
 # Copyright (c) 2014 Renato Utsch
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to whom the Software is
 # furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 ##

# Makefile
# make all - make the project
# make clean - Clean everything

# Compiler
CC=g++

# Compiler flags
CFLAGS=-Wall -Wextra -Werror

# Create object file compiler flag
OBJ=-c

# Link to a library compiler flag
LIB=-l

# Predefined libraries
PREDEF_LIBS=$(LIB)m

# Output filename compiler flag
OUT=-o

# Linker
LINKER=ar

# Linker flags
LDFLAGS=rcs

# Create commands
FOLDER_CREATE=mkdir
FOLDER_CREATE_FLAGS=-p

# Delete commands
FOLDER_DEL=rm
FOLDER_DEL_FLAGS=-f -r

# dependency files

# General rules

all: folder_create raytracer

raytracer: source/*.cpp source/*.hpp source/math/*.hpp
	$(CC) $(CFLAGS) $(OUT) bin/raytracer  $(PREDEF_LIBS) source/*.cpp

folder_create:
	$(FOLDER_CREATE) $(FOLDER_CREATE_FLAGS) bin

clean:
	$(FOLDER_DEL) $(FOLDER_DEL_FLAGS) bin


