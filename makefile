all: game.o lodepng.o render.o shader.o texture.o
	gcc src/main.c -o asteroids obj/game.o obj/lodepng.o obj/render.o obj/shader.o obj/texture.o -lGL -lGLEW -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -Wall -Wextra

game.o: src/game.c
	gcc -c src/game.c -o obj/game.o

lodepng.o: src/lodepng/lodepng.c
	gcc -c src/lodepng/lodepng.c -o obj/lodepng.o

render.o: src/render/render.c
	gcc -c src/render/render.c -o obj/render.o

shader.o: src/render/shader.c
	gcc -c src/render/shader.c -o obj/shader.o

texture.o:	src/render/texture.c
	gcc -c src/render/texture.c -o obj/texture.o

clean:
	rm obj/*.o asteroids
