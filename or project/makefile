parse.exe: lex.yy.c Collection.tab.c functions.c
	gcc lex.yy.c functions.c Collection.tab.c -o parse.exe

lex.yy.c: Collection.tab.c collection.l
	flex Collection.l

Collection.tab.c: Collection.y
	bison -d Collection.y
	
clean: 
	del lex.yy.c Collection.tab.c Collection.tab.h parse.exe test.exe

test.exe: test.cpp
	g++ test.cpp -o test.exe