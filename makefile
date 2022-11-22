all:	myshell	writef	execx

myshell: myshell.c
	gcc myshell.c -o myshell -lreadline

writef: writef.c
	gcc writef.c -o writef

execx: execx.c
	gcc execx.c -o execx