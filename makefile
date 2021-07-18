# FOR WINDOWS DO:
# g++ -std=c++17 Subconscious.cpp -o Sub -luser32 -lgdi32 -lopengl32 -lgdiplus -lshlwapi -lstdc++fs -ldwmapi

CC = g++
CFLAGS = -Wall -g -Wextra
LFLAGS = -lX11 -lGL -lpthread -lpng -lstdc++fs

all: Subconscious

Subconscious: Subconscious.cpp Subconscious.hpp
	$(CC) $(CFLAGS) $(LFLAGS) Subconscious.c -o Subconscious

clean:
	rm Subconscious
