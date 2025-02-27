opt=-03 -Wall -std=c2x

all: clean macspoof

macspoof: macspoof:o
	cc ${opt} $^ -o $@

macspoof.o: macspoof.c
	cc${opt} -c $^

clean:
	rm -f macspoof *.o