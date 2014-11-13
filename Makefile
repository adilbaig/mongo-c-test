CFLAGS = `pkg-config --cflags --libs libmongoc-1.0`

example4:
	gcc -o bin/example4 example4.c $(CFLAGS)
	
quotes:
	gcc -o bin/quotes quotes.c $(CFLAGS)