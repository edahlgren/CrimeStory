CFLAGS=-g3
LEX = lex
YACC = yacc 
CC = gcc

crimes: y.tab.o buildcrimes.o svg.o
	gcc -g3 -o crimes lex.yy.c y.tab.o buildcrimes.o svg.o
y.tab.o:  y.tab.c
	${CC} -g3 -c y.tab.c
svg.o: svg.c svg.h buildcrimes.h
	${CC} -g3 -c svg.c
buildcrimes.o: buildcrimes.c buildcrimes.h
	${CC} -g3 -c buildcrimes.c
y.tab.c: lex.yy.c crimes.y buildcrimes.h svg.h
	$(YACC) -d crimes.y	
lex.yy.c: crimes.l
	$(LEX) crimes.l
clean:
	rm *.o y.tab.c lex.yy.c
