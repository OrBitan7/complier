parse.exe: lex.yy.c TestYacc.c Collection.tab.c
	g++ lex.yy.c  Collection.tab.cpp TestYacc.c -o parse.exe

lex.yy.c: Collection.tab.c collection.l
	flex Collection.l

Collection.tab.c: Collection.y
	bison -d Collection.y -o Collection.tab.cpp
	
clean: 
	del lex.yy.c Collection.tab.cpp Collection.tab.h parse.exe test.exe

test.exe: test.c
	g++ test.cpp -o test.exe