all:
	$(CC) -o plstest plstest.c 2>/dev/null

clean:
	rm -rf ./plstest 
