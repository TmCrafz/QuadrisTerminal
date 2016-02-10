CC=g++
CFLAGS=-g -std=c++11 -Wall

all: tetris

tetris: main.o Game.o Drawable.o Stone.o FallenStone.o PointF.o InputHelper.o Menu.o MenuMain.o
	$(CC) $(CFLAGS) main.o Game.o Drawable.o Stone.o FallenStone.o PointF.o InputHelper.o Menu.o MenuMain.o -o tetris.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o main.o

#WorldConstants.o: WorldConstants.h
#	$(CC) $(CFLAGS) -c WorldConstants.h -o WorldConstants.o

Game.o: Game.cpp Game.h
	$(CC) $(CFLAGS) -c Game.cpp -o Game.o

Drawable.o: Drawable.cpp Drawable.h
	$(CC) $(CFLAGS) -c Drawable.cpp -o Drawable.o

Stone.o: Stone.cpp Stone.h Game.o 
	$(CC) $(CFLAGS) -c Stone.cpp -o Stone.o

FallenStone.o: FallenStone.cpp FallenStone.h
	$(CC) $(CFLAGS) -c FallenStone.cpp -o FallenStone.o

PointF.o: PointF.cpp PointF.h
	$(CC) $(CFLAGS) -c PointF.cpp -o PointF.o

InputHelper.o: InputHelper.cpp InputHelper.h
	$(CC) $(CFLAGS) -c InputHelper.cpp -o InputHelper.o

Menu.o: Menu.cpp Menu.h
	$(CC) $(CFLAGS) -c Menu.cpp -o Menu.o

MenuMain.o: MenuMain.cpp MenuMain.h
	$(CC) $(CFLAGS) -c MenuMain.cpp -o MenuMain.o

clean:
	rm *o


