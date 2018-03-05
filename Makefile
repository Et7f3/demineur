CC=gcc
CFLAGS=-Wall -Wextra -ansi -Wwrite-strings -Wstrict-prototypes\
 -Wno-self-assign -Wuninitialized -Wunreachable-code          \
 -Wno-unused-parameter -I..\SDL2-2.0.7\i686-w64-mingw32\include -std=c89
LDFLAGS=-L..\SDL2-2.0.7\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2\
 -lSDL2.dll
SRC             =$(wildcard src/*.c)
EXECUTABLE_NAME =demin
OUT_DIR         =bin\\

final: CFLAGS += -O

debug: CFLAGS          += -ggdb -O0
debug: LDFLAGS         += -DDEBUG
debug: EXECUTABLE_NAME :=$(EXECUTABLE_NAME).debug

all: final

debug: $(SRC:src/%.c=obj/debug/%.o)
	$(CC) -o $(OUT_DIR)$(EXECUTABLE_NAME).exe $^ $(CFLAGS) $(LDFLAGS)

final: $(SRC:src/%.c=obj/final/%.o)
	$(CC) -o $(OUT_DIR)$(EXECUTABLE_NAME).exe $^ $(CFLAGS) $(LDFLAGS)

indent: $(wildcard src/*.c) $(wildcard src/*.h)
	c:\msys64\mingw64\bin\indent.exe $^ -bli0 -ppi2 -l79 -lc79 -npsl -bbb -bls -blf -ts2 -nce -bl -npcs -di25

#/C/msys64/mingw64/bin/indent.exe $^ -bli0 -ppi2 -l79 -lc79 -npsl -bbb -bls -blf -ts2 -nce -bl -npcs -di25

test: $(wildcard test/*.c:test/%.c=obj/%.o)

obj/final/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

obj/debug/%.o: src/%.c
	$(CC) -c $< -o $@ $(CFLAGS) $(LDFLAGS)

clean:
	del obj\final\*.o obj\debug\*.o src\*~

distclean: clean
	del  bin\*.exe bin\*.zip
