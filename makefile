build:
	gcc -I/opt/homebrew/Cellar/sdl2/2.30.3/include -L/opt/homebrew/Cellar/sdl2/2.30.3/lib -lSDL2 -Wall -std=c99 -o renderer ./src/main.c
run:
	./renderer 
clean:
	rm renderer
br:
	make build && make run