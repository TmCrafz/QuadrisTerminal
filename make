CC=g++
CFLAGS=-g -std=c++11 -Wall

all: quadris

quadris: main.o Game.o Drawable.o Stone.o FallenStone.o PointF.o InputHelper.o ScreenBuffer.o Screen.o ScoreScreen.o  MenuMain.o MenuSettings.o
	$(CC) $(CFLAGS) main.o Game.o Drawable.o Stone.o FallenStone.o PointF.o InputHelper.o ScreenBuffer.o Screen.o MenuMain.o MenuSettings.o ScoreScreen.o -o quadris.o

main.o: main.cpp MenuMain.h Game.h InputHelper.h
	$(CC) $(CFLAGS) -c main.cpp -o main.o

Game.o: Game.cpp Game.h Screen.h WorldConstants.h PointF.h Stone.h FallenStone.h InputHelper.h ScoreScreen.h
	$(CC) $(CFLAGS) -c Game.cpp -o Game.o

Drawable.o: Drawable.cpp Drawable.h WorldConstants.h 
	$(CC) $(CFLAGS) -c Drawable.cpp -o Drawable.o

Stone.o: Stone.cpp Stone.h Game.o ScreenBuffer.h Drawable.h WorldConstants.h PointF.h
	$(CC) $(CFLAGS) -c Stone.cpp -o Stone.o

FallenStone.o: FallenStone.cpp FallenStone.h WorldConstants.h Drawable.h PointF.h ScreenBuffer.h
	$(CC) $(CFLAGS) -c FallenStone.cpp -o FallenStone.o

PointF.o: PointF.cpp PointF.h 
	$(CC) $(CFLAGS) -c PointF.cpp -o PointF.o

InputHelper.o: InputHelper.cpp InputHelper.h
	$(CC) $(CFLAGS) -c InputHelper.cpp -o InputHelper.o

ScreenBuffer.o: ScreenBuffer.cpp ScreenBuffer.h
	$(CC) $(CFLAGS) -c ScreenBuffer.cpp -o ScreenBuffer.o

Screen.o: Screen.cpp Screen.h WorldConstants.h InputHelper.h
	$(CC) $(CFLAGS) -c Screen.cpp -o Screen.o

MenuMain.o: MenuMain.cpp MenuMain.h Screen.h WorldConstants.h Game.h ScoreScreen.h MenuSettings.h
	$(CC) $(CFLAGS) -c MenuMain.cpp -o MenuMain.o

MenuSettings.o: MenuSettings.cpp Screen.h MenuSettings.h WorldConstants.h 
	$(CC) $(CFLAGS) -c MenuSettings.cpp -o MenuSettings.o

ScoreScreen.o: ScoreScreen.cpp ScoreScreen.h WorldConstants.h Screen.h 
	$(CC) $(CFLAGS) -c ScoreScreen.cpp -o ScoreScreen.o

clean:
	rm *o


