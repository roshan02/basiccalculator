project:mybcmain.o mybcstacks.o mybclist.o mybcbignum.o mybctoken.o mybcinfix.o 
	cc -g mybcmain.o mybcstacks.o mybclist.o mybcbignum.o mybctoken.o mybcinfix.o -o project -lm
mybcmain.o: mybcmain.c mybcstacks.h mybclist.h mybcinfix.h
	cc -g -c mybcmain.c -Wall
mybcstacks.o: mybcstacks.c mybcstacks.h mybclist.h
	cc -g -c mybcstacks.c -Wall
mybclist.o: mybclist.c mybclist.h mybcstacks.h
	cc -g -c mybclist.c -Wall
mybcbignum.o: mybcbignum.c mybclist.h mybcbignum.h mybcstacks.h
	cc -g -c mybcbignum.c -Wall
mybctoken.o: mybctoken.c mybctoken.h mybclist.h
	cc -g -c mybctoken.c -Wall
mybcinfix.o: mybcinfix.c mybcinfix.h mybcstacks.h mybclist.h mybcbignum.h mybctoken.h
	cc -g -c mybcinfix.c -Wall

