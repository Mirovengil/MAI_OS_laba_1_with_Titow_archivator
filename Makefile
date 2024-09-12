all : directories main.o archivator.o
	gcc ./obj/main.o ./obj/archivator_by_IVAN.o -o ./bin/runme
	./bin/runme
	
main.o : 
	gcc -I./headers/ ./src/main.c -c -o./obj/main.o

archivator.o : 
	gcc -I./headers/ ./src/archivator_by_IVAN.c -c -o ./obj/archivator_by_IVAN.o

directories : 
	mkdir obj
	mkdir bin

clean : 
	rm -rf ./obj/*
	rm -rf ./bin/*
