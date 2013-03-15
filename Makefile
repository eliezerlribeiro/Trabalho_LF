#Makefile

#Compilador
CC=g++

# Objects
OBJETOS = analisadorLexico.o analisadorSintatico.o analisador.o

EXECUTAVEL = analisador
BASE_FILENAME=trabalho_lf

all: $(OBJETOS) 
	$(CC) $(OBJETOS) -o $(EXECUTAVEL)

analisadorLexico: analisador.hpp analisadorLexico.cpp
	$(CC) -c analisadorLexico.cpp
analisadorSintatico: analisador.hpp analisadorSintatico.cpp
	$(CC) -c analisadorSintatico.cpp
analisador.o: analisador.hpp analisador.cpp
	$(CC) -c analisador.cpp


#limpeza
clean:
	rm -rf $(OBJETOS)
	rm -rf analisadorLexicoSintatico.o
	rm -rf $(EXECUTAVEL)
	rm -rf saidaAnalisador.txt

package:
	@echo "Empacotando: "
ifneq ($(wildcard *$(BASE_FILENAME)*),)
	rename 's/tar.gz/$(REVISION).tar.gz' $(wildcard *$(BASE_FILENAME)*) 
	#@echo "Arquivo Existe"
endif
ifeq ($(wildcard $(BASE_FILENAME).tar.gz),)
	mkdir $(BASE_FILENAME)
	cp -R README.md *.cpp *.hpp Makefile Uteis/ sintatico_versao_1/ $(BASE_FILENAME)/
	tar -zcvf $(BASE_FILENAME).tar.gz $(BASE_FILENAME)/
	#zip -r $(BASE_FILENAME).zip $(BASE_FILENAME)/
	rm -R $(BASE_FILENAME)/
endif
