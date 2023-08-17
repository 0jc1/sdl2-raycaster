OBJS = *.cpp
CC = g++
COMPILER_FLAGS = -I src/include -L src/lib -Wall -O3
LINKER_FLAGS = -lmingw32 -lSDL2main -lSDL2
OBJ_NAME = raycast

all : $(OBJS)
	$(CC) $(COMPILER_FLAGS) -o $(OBJ_NAME) $(OBJS) $(LINKER_FLAGS)

run:
	./$(OBJ_NAME)

