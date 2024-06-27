build:
	gcc -I/opt/homebrew/Cellar/sdl2/2.30.3/include -L/opt/homebrew/Cellar/sdl2/2.30.3/lib -Wall -std=c99 ./src/*.c -lSDL2 -lm -o renderer
run:
	./renderer 
clean:
	rm renderer
br:
	make build && make run