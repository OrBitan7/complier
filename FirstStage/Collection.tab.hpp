
/* A Bison parser, made by GNU Bison 2.4.1.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* "%code requires" blocks.  */

/* Line 1676 of yacc.c  */
#line 16 "Collection.ypp"

#include <iostream>
#include <string>
#include <set>



/* Line 1676 of yacc.c  */
#line 48 "Collection.tab.hpp"

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     t_STRING = 258,
     t_ID = 259,
     t_INT = 260,
     t_IF_CMD = 261,
     t_ELSE_CMD = 262,
     t_FOR_CMD = 263,
     t_WHILE_CMD = 264,
     t_BIGGER_EQUAL = 265,
     t_LOWER_EQUAL = 266,
     t_EQUAL = 267,
     t_NOT = 268,
     t_COLLECTION_CMD = 269,
     t_SET_CMD = 270,
     t_INT_CMD = 271,
     t_STRING_CMD = 272,
     t_INPUT_CMD = 273,
     t_OUTPUT_CMD = 274
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
{

/* Line 1676 of yacc.c  */
#line 21 "Collection.ypp"
std::string type_string;
		int type_number;
		std::set<std::string> type_collection;
		std::set<int> type_set;
		


/* Line 1676 of yacc.c  */
#line 92 "Collection.tab.hpp"
} YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


