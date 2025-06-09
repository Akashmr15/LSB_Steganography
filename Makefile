obj:=$(patsubst %c,%o,$(wildcard *.c))
output.exe:$(obj)
	gcc -o $@ $^
clean:
	rm *.exe *.o

