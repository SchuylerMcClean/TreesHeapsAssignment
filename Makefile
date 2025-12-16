CFLAGS = -std=c99 -Wall -pedantic -fPIC -I./src
CC = clang

all: bin/preorder bin/postorder bin/inorder bin/calculate bin/heap


bin/preorder: obj/preorder.o lib/libparse.so lib/libstringerror.so | bin
	$(CC) -Llib obj/preorder.o lib/libparse.so lib/libstringerror.so -o bin/preorder
bin/postorder: obj/postorder.o lib/libparse.so lib/libstringerror.so | bin
	$(CC) -Llib obj/postorder.o lib/libparse.so lib/libstringerror.so -o bin/postorder
bin/inorder: obj/inorder.o lib/libparse.so lib/libstringerror.so | bin
	$(CC) -Llib obj/inorder.o lib/libparse.so lib/libstringerror.so -o bin/inorder
bin/calculate: obj/calculate.o lib/libparse.so lib/libstringerror.so lib/libcalculateexp.so | bin
	$(CC) -Llib obj/calculate.o lib/libparse.so lib/libstringerror.so lib/libcalculateexp.so -o bin/calculate
bin/heap: obj/heap.o lib/libheapify.so | bin
	$(CC) -Llib obj/heap.o lib/libheapify.so -o bin/heap

obj/preorder.o: src/preorder.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/preorder.c -o obj/preorder.o
obj/postorder.o: src/postorder.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/postorder.c -o obj/postorder.o
obj/inorder.o: src/inorder.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/inorder.c -o obj/inorder.o
obj/calculate.o: src/calculate.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/calculate.c -o obj/calculate.o
obj/heap.o: src/heap.c | obj	
	$(CC) $(CFLAGS) -c src/heap.c -o obj/heap.o

obj/parseStrToTree.o: src/parseStrToTree.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/parseStrToTree.c -o obj/parseStrToTree.o
lib/libparse.so: obj/parseStrToTree.o | lib
	$(CC) -shared obj/parseStrToTree.o -o lib/libparse.so

obj/stringError.o: src/stringError.c | obj
	$(CC) $(CFLAGS) -c src/stringError.c -o obj/stringError.o
lib/libstringerror.so: obj/stringError.o | lib
	$(CC) -shared obj/stringError.o -o lib/libstringerror.so

obj/calculateExpression.o: src/calculateExpression.c src/binaryExpressionTree.h | obj
	$(CC) $(CFLAGS) -c src/calculateExpression.c -o obj/calculateExpression.o
lib/libcalculateexp.so: obj/calculateExpression.o | lib
	$(CC) -shared obj/calculateExpression.o -o lib/libcalculateexp.so

obj/heapify.o: src/heapify.c  | obj
	$(CC) $(CFLAGS) -c src/heapify.c -o obj/heapify.o
lib/libheapify.so: obj/heapify.o | lib
	$(CC) -shared obj/heapify.o -o lib/libheapify.so

clean: 
	rm -f obj/*
cleaner: 
	rm -f obj/* bin/* lib/*

obj:
	mkdir -p obj
bin:
	mkdir -p bin
lib:
	mkdir -p lib
