test: challenge
	./challenge < testinput.txt > /tmp/actualoutput.txt
	diff /tmp/actualoutput.txt ./testoutput.txt

challenge: challenge.c challenge.h token.c buffer.c
	cc -o $@ challenge.c token.c buffer.c

checkmem: challenge
	cat testinput.txt | valgrind --leak-check=yes --undef-value-errors=no ./challenge

pythonver: pythonver.py
	cat testinput.txt | python pythonver.py
