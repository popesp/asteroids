all: game.o render.o shader.o
	gcc src/main.c -o asteroid obj/game.o obj/render.o obj/shader.o -lGL -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi -lm -Wall -Wextra

game.o: src/game.c
	gcc -c src/game.c -o obj/game.o

render.o: src/render/render.c
	gcc -c src/render/render.c -o obj/render.o

shader.o: src/render/shader.c
	gcc -c src/render/shader.c -o obj/shader.o

clean:
	rm obj/*.o asteroids
