test.exe: lex.yy.c TestLex.cpp
	g++ lex.yy.c Collection.tab.cpp TestLex.cpp -o test.exe

lex.yy.c: Collection.tab.hpp collection.l
	flex Collection.l

Collection.tab.h: Collection.ypp
	bison -d Collection.ypp
	
clean: 
	del lex.yy.c Collection.tab.cpp Collection.tab.hpp test.exe