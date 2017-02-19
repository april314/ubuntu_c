generator:	generator.o password.o
		cc generator.o password.o -o passgen
generator.o:	password.h
password.o:	password.h

clean:
		rm *.o
