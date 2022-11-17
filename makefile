text0 = 
text1 = Compilación del proyecto...
text2 = Modo de empleo:
text3 = ./grammar2CNF input.gra output.gra
text4 = Se han eliminado el fichero ejecutable y los ficheros objetos.

CC=g++
CXXFLAGS=-g -std=c++14

OBJS = src/grammar2CNF.o

all: ${OBJS}
	@echo $(text0)
	@echo $(text1)
	$(CC) $(CXXFLAGS) -o grammar2CNF ${OBJS}
	@echo $(text0)
	@echo $(text2)
	@echo $(text3)

clean: 
	rm -rf src/*.o grammar2CNF
	@echo $(text4)