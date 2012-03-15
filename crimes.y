%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "buildcrimes.h"
#include "svg.h"
#define YYSTYPE char *

int line = 0;

char * word; 
int addword = 0;
double latitude;

FILE * f = NULL;
struct crimelist * cs = NULL;
struct crime * current_crime = NULL;


void yyerror(const char *str) {
        fprintf(stderr,"error: %s\n",str);
}
 
int yywrap() {
        return 1;
}

void main(int argc, char ** argv) {

	char * newfile;
	if(argc == 2 && strcmp(argv[1], "ops") == 0) {
		fine_ops();
		return;
	}
	if(argc == 3 && strcmp(argv[2], "ops") == 0) {
		ops(argv[1]);
		return;
	}
	else {
		char ** flags = NULL;
		int last, i = 1;
		last = argc-1;
		if(last > 1) {
			flags = malloc(last*sizeof(char *));
			while(i < last) {
				flags[i-1] = argv[i];
				++i;
			}
		}
		char * flag;
		i = 0;
		/**
		while(flag = flags[i]) {
			printf("flag %s\n", flag);
			++i;
		}
		**/
		char * file = argv[last];
		

		if(newfile = unfinish(file)) {
		  	if(f = fopen(newfile, "a+")) {	
				cs = malloc(sizeof(struct crimelist));

				word = calloc(500, sizeof(char));
				init_crimes(cs);
				yyparse();
				printf("yacc parsed\n");
				// print_crimes(cs);
				build_svg(cs, f, flags);
				printf("got through build svg\n");
				fclose(f);
				printf("closed file\n");
				printf("inkscape exporting bitmap to high-res png\n");
				svg2png();
			}
			else {
				perror("Error");
			}
		}
		else {
			printf("Couldn't do sed script yikkes\n");
		}
	}
}


%}

%token BOOL ADDR DICT OPAREN EPAREN WORD NUM EMPTYSET QUOTE OBRACE EBRACE OBOX EBOX

%%

definition:
	|
	OBRACE commands EBRACE
	;

commands:
	|
	commands command
	;

command:
	quote DICT statement
	;


statement:
	NUM 
	|
	BOOL 
	|
	quote 
	|
	OBRACE commands EBRACE
	|
	OBOX statements EBOX
	{
		line = 0;
	}
	;

statements:
	|
	statements statement
	{
		if(line == 0) {
			// initialize new crime
			// add global crime to crimelist
			// make new crime global
			struct crime * c = malloc(sizeof(struct crime));
			init_crime(c);

			if(current_crime != NULL && full(current_crime)) {
				add_crime(cs, current_crime);
			}
			current_crime = c;
        	}

		// IUCR code
		if(line == 12) {
			current_crime->IUCR = atoi($2);
			// printf("IUCR code %s\n", $2);

		}		

		// IUCR name
		if(line == 13) {
			char * text = malloc(100*sizeof(char));

			strcpy(text, word);
			current_crime->IUCRname = text;
			// printf("IUCR name %s\n", text);
		}

		// latitude
		if(line == 24) {
			current_crime->lat = translate_lat($2);
			// printf("lat %s\n", $2);
		}

		// longitude
		if(line == 25) {
			current_crime->lon = translate_lon($2);
			// printf("long %s\n", $2);
		}
	
        	++line;
	}
	;


quote:
	QUOTE quoted QUOTE
	{
		//printf("quoted: %s\n", $2);
		//printf("word: %s\n", word);
		$$ = $2;
		
	}
	;

quoted:	
	phrase
	{
		addword = 0;
		$$ = word;
	}
	|
	BOOL
	|
	EMPTYSET
	; 


phrase:
	|
	phrase cluster
	{
		if(addword == 0) {
			word = flush(word);
		}
		++addword;
		strcat(word, $2);
		strcat(word, " ");
	}
	;


cluster:
	ADDR
	|
	WORD
	|
	NUM 
	|
	OPAREN phrase EPAREN 
	{ 
		//addword = 0;
		//$$ = word;
	}
	;



%%













