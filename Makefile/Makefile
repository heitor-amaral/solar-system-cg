CC=g++
OPCOES_COMPILADOR=-I. -I/usr/include/SOIL -lglut -lGLU -lSOIL -lGLEW -lSDL_mixer -lGL -lm -lstdc++ -w
TODOS_ARQUIVOS_PONTOH =
TODOS_ARQUIVOS_OBJ = main.o

%.o: ../%.cpp $(TODOS_ARQUIVOS_PONTOH)
	@$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	@gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	@(cd .. && exec Makefile/main)

clean:
	@rm *.o main
