test: challenge
	./challenge < testinput.txt > /tmp/actualoutput.txt
	diff /tmp/actualoutput.txt ./testoutput.txt

challenge: challenge.c challenge.h token.c buffer.c
	cc -o $@ challenge.c token.c buffer.c
