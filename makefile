# FOR WINDOWS CHECK make.bat

# UNTESTED ON LINUX! Probably missing some link flags, or stuff to make SDL2 work.
CC = g++
CFLAGS = -Wall -g -Wextra -march=native -Iinclude
LFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs -lasound -lSDL2main -lSDL2

all: Subconscious

Subconscious: Subconscious.cpp uiBlinker.cpp uiGauges.cpp uiPanels.cpp uiRadar.cpp World.cpp SubSystems.cpp Sound.cpp 
	$(CC) $(CFLAGS) $(LFLAGS) Subconscious.c -o Subconscious

clean:
	rm Subconscious
