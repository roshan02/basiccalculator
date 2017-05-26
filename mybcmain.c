/*****************************************************************************
 * Copyright (C) Roshan Nalawade dn.roshan2@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston MA 02110-1301, USA.
 *****************************************************************************/

#include "mybcstacks.h"
#include "mybclist.h"
#include "mybcinfix.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define COUNT 2048
int main(int argc, char *argv[]) {
	int arg = 0;
	if(argc == 2 && strcmp(argv[1], "-h") == 0) {
		printf("MODE:- HELP\n");
		printf("My-bc 1.0.0\n");
		printf("Copyright 2016 --->Roshan Nalawade\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
		printf("\nUsage: project [option]\n");
		printf("\t-h\t--help\t\tprint this help and exit\n");
		printf("\t-v\t--version\tprints information about version of this software\n");
		printf("\t-q\t--quiet\t\tdon't print initial banner\n");
		printf("\t-i\t--integers\tprints answers in integer format only\n");
		printf("\t-f\t--friendly\tmakes ouput user friendly\n\n");
		printf("(-expr)\tThe result is the negation of the expression.\n");
		printf(" ++var \tThe variable is incremented by one and  the  new  value  is  the\n");
		printf("\tresult of the expression.\n\n");
		printf(" --var \tThe  variable  is  decremented  by  one and the new value is the\n");
		printf(" var++ \tThe result of the expression is the value of the variable and then the\n");
		printf("\tvariable is incremented by one.\n");
		printf(" var-- \tThe result of the expression is the value of the variable and then the\n");
		printf("\tvariable is decremented by one.\n");
		printf(" expr+expr\n");
		printf("\tThe result of the expression is the sum of the two expressions.\n");
		printf(" expr-expr\n");
		printf(" var-var\n");
		printf("\tThe result of the expression is the difference of the two expressions.\n\n");
		printf(" expr*expr\n");
		printf(" var*var\n");
		printf("\tThe result of the expression is the sum of the two expressions.\n\n");
		printf(" expr/expr\n");
		printf(" var/var\n");
		printf("\tThe result of the expression is the quotient of the two  expressions.\n\n");
		printf(" expr%%expr\n");
		printf(" var%%var\n");
		printf("\tThe result of the expression is the \"remainder\n\n");
		printf(" expr^expr\n");
		printf(" var^var\n");
		printf("\tThe result of the expression is the value of the first raised to the second\n\n");
		printf("expr!\n");
		printf(" var!\n");
		printf("\tThe result of the expression is the factorial of given input value\n");
		printf(" (expr)\n");
		printf("\tThis  alters  the standard precedence to force the evaluation of\n");
		printf("\tthe expression.\n");
		printf(" /*...*/\n");
		printf("\tThis can be used for putting comments\n");
		printf(" var=expr\n");
		printf("\tThe variable is assigned the value of the expression.\n");
		printf("\tRelational expressions are a special kind  of  expression  that  always\n");
		printf("\tevaluate to 0 or 1, 0 if the relation is false and 1 if the relation is\n");
		printf("\ttrue.\n");
		printf(" expr1<expr2\n");
		printf("\tThe result is 1 if expr1 is strictly less than expr2.\n");
		printf(" expr1>expr2\n");
		printf("\tThe result is 1 if expr2 is strictly less than expr1.\n");
		printf(" expr1<=expr2\n");
		printf("\t The result is 1 if expr1 is less than or equal to expr2.\n");
		printf(" expr1>=expr2\n");
		printf("\tThe result is 1 if expr1 is greater than or equal to expr2.\n");
		printf(" S(x)\n");
		printf("\tThe sine of x, x is in degrees.\n");
		printf(" C(x)\n");
		printf("\tThe cosine of x, x is in degrees.\n");
		printf(" T(x)\n");
		printf("\tThe tangent of x, x is in degrees.\n");
		printf(" E(x)\n");
		printf("\tThe exponential function of raising e to the value x.\n\n");
		printf(" D->Bexpr\n");
		printf("\tThe result is the binary notation of given decimal expr\n");
		printf(" D->Oexpr\n");
		printf("\tThe result is the octal notation of given decimal expr\n");
		printf(" B->Dexpr\n");
		printf("\tThe result is the Decimal notation of given binary input\n");
		printf(" O->Dexpr\n");
		printf("\tThe result is the Decimal notation of given octal input\n");
		printf(" Ip->x\n");
		printf("\tThe result of given expression is 1 if x  prime else if it is not a prime\n");
		printf("\tit prints the number by which it is divisible\n");
		exit(0);		
	}
	else if(argc == 2 && strcmp(argv[1], "-i") == 0) {
		arg = 2;
		printf("MODE:- INTEGER\n");
		printf("My-bc 1.0.0\n");
		printf("Copyright 2016 --->Roshan Nalawade\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else if(argc == 2 && strcmp(argv[1], "-v") == 0) {
		arg = 1;
		printf("MODE:- VERSION\n");
		printf("My-bc 1.0.0\n");
		printf("Copyright 2016 --->Roshan Nalawade\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
		exit(0);
	}
	else if(argc == 2 && strcmp(argv[1], "-q") == 0) {
		printf("MODE:- QUIET\n");
		arg = 4;
	}
	else if(argc == 2 && strcmp(argv[1], "-f") == 0) {
		arg = 5;
		printf("MODE:- FRIENDLY\n");
		printf("My-bc 1.0.0\n");
		printf("Copyright 2016 --->Roshan Nalawade\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else if(argc == 1) {
		arg = 0;
		printf("My-bc 1.0.0\n");
		printf("Copyright 2016 --->Roshan Nalawade\n");
		printf("This is free software with ABSOLUTELY NO WARRANTY.\n");
	}
	else {
		printf("USAGE: ./project [option] \n");
		printf("USAGE for help : ./project -h\n");
		exit(0);
	}
	char str[COUNT];	
	int x;
	list *ans;
	ans = (list *)malloc(sizeof(list));
	init(ans);
	while((x = readline(str, COUNT))) {
		ans = infix(str);
		if(ans == NULL) {
			fprintf(stderr, "Erorr in expression\n");
		}  
		else {
			if(arg != 5) {
				printf("answer = ");
				traverse(ans, arg);
			}
			else 
				traverse(ans, arg);
			printf("\n");
		}
	}
	int i, j;
	for(i = 0; i < 26; i++)
		for(j = 0; j < 10; j++)
			free(L[i][j]);
	return 0;
}

