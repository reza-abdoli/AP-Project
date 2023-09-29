CC := g++
CCRDL += rsdl.cpp -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer
ALL_F :=main.o bullet.o getMapandRun.o checkConditionsandDraw.o update.o powers.o

all: starwars.out

starwars.out: $(ALL_F)
	$(CC) $(ALL_F) $(CCRDL) -o starwars.out

main.o: main.cpp game.h
	$(CC) -c main.cpp

bullet.o: bullet.cpp objects.h defines.h
	$(CC) -c bullet.cpp

getMapandRun.o: getMapandRun.cpp game.h objects.h defines.h
	$(CC) -c getMapandRun.cpp

map.o: map.txt
	$(CC) -c map.txt

checkConditionsandDraw.o: checkConditionsandDraw.cpp game.h objects.h defines.h
	$(CC) -c checkConditionsandDraw.cpp

update.o: update.cpp objects.h defines.h
	$(CC) -c update.cpp

powers.o: powers.cpp objects.h defines.h
	$(CC) -c powers.cpp

.PHONY: clean
clean:
	rm -r *.o