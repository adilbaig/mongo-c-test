CFLAGS = `pkg-config --cflags --libs libmongoc-1.0`

example4:
	gcc -o example4 example4.c $(CFLAGS)
	
quotes:
	gcc -o quotes quotes.c $(CFLAGS)