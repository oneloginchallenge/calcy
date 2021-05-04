test: challenge
	echo '1/2 * 3_3/4' | ./challenge | grep -e '^= 1_7/8$$'
	echo '2_3/8 + 9/8' | ./challenge | grep -e '^= 3_1/2$$'
	echo '2_3/8+9/8' | ./challenge | grep -e '^= 3_1/2$$'
	echo '3_1/4 + 2/7' | ./challenge | grep -e '^= 3_15/28$$'
	echo '9 / 3' | ./challenge | grep -e '^= 3$$'
	echo '1 / 3' | ./challenge | grep -e '^= 1/3$$'
	echo '24 / 48' | ./challenge | grep -e '^= 1/2$$'
	echo '3 * 1 / 3' | ./challenge | grep -e '^= 1$$'
	echo '1/4 * 8' | ./challenge | grep -e '^= 2$$'
	echo '2+2+2+2' | ./challenge | grep -e '^= 8$$'
	echo '2*2*2*2' | ./challenge | grep -e '^= 16$$'
	echo '10 - 7' | ./challenge | grep -e '^= 3$$'
	echo '2 - -7' | ./challenge | grep -e '^= 9$$'
	echo '-1/3 * -3 * 10' | ./challenge | grep -e '^= 10$$'

challenge: challenge.c challenge.h token.c buffer.c
	cc -o $@ challenge.c token.c buffer.c
