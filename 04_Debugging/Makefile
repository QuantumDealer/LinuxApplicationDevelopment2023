CFLAGS=-O0 -g

test: range
	gdb --batch -x gdb1 a.out | grep -A4 -E "^36" > result1.txt
	gdb --batch -x gdb2.py ./range 2>/dev/null | grep --color=none -P "[abci] = -?\\d+" > result2.txt
	cmp 01.txt result1.txt
	cmp 02.txt result2.txt

clean:
	rm -f result1.txt result2.txt range