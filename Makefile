CC = gcc
LD = gcc

# -O0 désactive les optimisations à la compilation
# C'est utile pour débugger, par contre en "production"
# on active au moins les optimisations de niveau 2 (-O2).
CFLAGS = -Wall -Wextra -std=c99 -Iinclude -O3 -g
LDFLAGS = -lm

# Par défaut, on compile tous les fichiers source (.c) qui se trouvent dans le
# répertoire src/
SRC_FILES=$(wildcard src/*.c)

# Par défaut, la compilation de src/toto.c génère le fichier objet obj/toto.o
OBJ_FILES=$(patsubst src/%.c,obj/%.o,$(SRC_FILES))

all: ppm2jpeg

ppm2jpeg: $(OBJ_FILES)
	$(LD) $(OBJ_FILES) $(LDFLAGS) -o $@

obj/%.o: src/%.c
	$(CC) -c $(CFLAGS) $< -o $@

time:  $(OBJ_FILES)
	$(LD) $(OBJ_FILES) $(LDFLAGS) -pg -o  $@

.PHONY: clean

.PHONY: clean_images

clean:
	rm -rf ppm2jpeg $(OBJ_FILES)

clean_images:
	rm images/*.jpg
	rm images/*.bla
