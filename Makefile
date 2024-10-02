main: main.o heap.o
	gcc -o main main.o heap.o
	
main.o:
	gcc -c main.c

heap.o: heap.c
	gcc -c heap.c

clean:
	rm -f main main.o heap.o output.txt

test: main
	bash test.sh
