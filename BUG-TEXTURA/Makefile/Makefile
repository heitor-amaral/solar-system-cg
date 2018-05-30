CC=g++
OPCOES_COMPILADOR=-I../lib -lglut -lGLU -lSOIL -lGLEW -lGL -lm -lstdc++ -w
LIB=../lib/
SRC=../src/
TODOS_ARQUIVOS_OBJ = main.o texturas.o texto.o


%.o: $(LIB)%.cpp
	@echo "Compilando as bibliotecas.."
	@$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

%.o: ../%.cpp
	@echo "Compilando componentes do jogo.."
	@$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	@echo "Compilando o jogo.."
	@$(CC) -o start $(TODOS_ARQUIVOS_OBJ) $(OPCOES_COMPILADOR)

run: all
	@echo "Inciando.."
	@./start

clean:
	@echo "Limpando arquivos.."
	@rm -f start
	@rm -f *.o
	@rm -f ./src/*.o
	@rm -f ./lib/*.o