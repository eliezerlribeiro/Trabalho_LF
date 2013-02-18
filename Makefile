#Makefile

#Compilador
CC=g++

# Objects
OBJETOS = analisadorLexico.o

EXECUTAVEL = anaisadorLexico

all: $(OBJETOS) 
	$(CC) $(OBJETOS) -o $(EXECUTAVEL)

analisador: anaisadorLexico.cpp
	$(CC) -c analisadorLexico.cpp

#limpeza
clean:
	rm -rf $(OBJETOS)
	rm -rf $(EXECUTAVEL)
	rm -rf saidaAnalisador.txt
