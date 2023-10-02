ALL = *.o *~ o.* *.a *.so *.txt

all:	README prog prog-a prog-so

prog:	const.o fun.o prog.o
	cc $^ -o $@

prog-a:	prog.o liboutput_static.a
	cc $^ -o $@

prog-so:	prog.o liboutput.so
	cc $^ -o $@

%.o:	%.c outlib.h
		cc $< -c -o $@

liboutput_static.a:	fun.o const.o
	ar -rcs liboutput_static.a $^

liboutput.so:	fun.o const.o
	cc -shared $^ -o liboutput.so

README: prog
	./$< 2> $@

test:
	./prog 2>prog_result_0.txt
	./prog-a 2>prog_result_a_0.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so 2>prog_result_so_0.txt
	./prog "hello" > prog_result_1.txt
	./prog-a "hello" > prog_result_a_1.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so "hello" > prog_result_so_1.txt
	./prog "hello" "world" "!" > prog_result_3.txt
	./prog-a "hello" "world" "!" > prog_result_a_3.txt
	LD_LIBRARY_PATH=`pwd` ./prog-so "hello" "world" "!" > prog_result_so_3.txt
	cmp prog_result_0.txt prog_result_a_0.txt
	cmp prog_result_0.txt prog_result_so_0.txt
	cmp prog_result_1.txt prog_result_a_1.txt
	cmp prog_result_1.txt prog_result_so_1.txt
	cmp prog_result_3.txt prog_result_a_3.txt
	cmp prog_result_3.txt prog_result_so_3.txt

clean:
	rm -f $(ALL)
	rm -rf prog prog-a prog-so README
	cc -fPIC   -c -o prog.o prog.c
	cc -fPIC   -c -o const.o const.c
	cc -fPIC   -c -o fun.o fun.c