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

#include "mybclist.h"
#include "mybctoken.h"
#include<stdlib.h>
/*********************************token.c************************************/

//enum states { SPC, DIG, OPR, VAR, STOP, ERR };
token *getnext(char *arr, int *reset) {
	static int currstate;
	int nextstate;
	static int i;
	static list *l;
	static int dec = 0;
	static int flag = 0;
	static int m = 0, num = 0, sign = 1;
	l = (list *)malloc(sizeof(list));
	init(l);
	if(m == 1) {
		append(l, num);
		m = 0;
	}	
	if(*reset == 1) {
		i = 0;
		currstate = SPC;
		*reset = 0;
	}
	token *t = (token *)malloc(sizeof(token));
	while(1) {
		switch(arr[i]) {
			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
			case '8': case '9': case '.':
				nextstate = DIG;
				break;
			case '+': case '-': case '*': case '/':
			case '%': case '(': case ')': case '^':
			case '!': case '<': case '>': case '=':
			case 'S': case 'C': case 'T': case 'E':
			case 'D': case 'B': case 'H': case 'O':
			case 'I':
				nextstate = OPR;
				break;
			case 'a': case 'b': case 'c': case 'd':
			case 'e': case 'f': case 'g': case 'h':
			case 'i': case 'j': case 'k': case 'l':
			case 'm': case 'n': case 'o': case 'p':
			case 'q': case 'r': case 's': case 't':
			case 'u': case 'v': case 'w': case 'x':
			case 'y': case 'z': 
				nextstate = VAR;
				break;
			case '\0':
				nextstate = STOP;
				break;
			case ' ':
				nextstate = SPC;
				break;
			default:
				nextstate = ERR;
				break;
		}
		switch(currstate) {
			case SPC:
				if(nextstate == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(l,(arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}			
				break;
			case DIG:
				if(nextstate == DIG) {
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						append(l, (arr[i] - '0'));
						if(flag == 1)
							dec++;
					}
				}
				else  { 
					t->type = OPERAND;
					t->l = l;
					t->l->dec = dec;
					t->l->sign = sign;
					sign = 1; 
					dec = 0;
					flag = 0;
					currstate = nextstate;
					i++;
					return t;
				}
				break;
			case OPR:
				if(arr[i - 2] == '(') {
					if(arr[i - 1] == '-')
						sign = -1;
					else
						sign = 1;
				}
				if(arr[i - 1] == 'D') {
					if(arr[i + 2] == 'B')
						t->var = 'd';
					if(arr[i + 2] == 'O')
						t->var = 'e';
					if(arr[i + 2] == 'H')
						t->var = 'f';
				}
				if(arr[i - 1] == 'B' || arr[i - 1] == 'O' || arr[i - 1] == 'H') {
					if(arr[i - 1] == 'B' && arr[i + 2] == 'D')
						t->var = 'a';
					if(arr[i - 1] == 'O' && arr[i + 2] == 'D')
						t->var = 'b';
					if(arr[i - 1] == 'H' && arr[i + 2] == 'D')
						t->var = 'c';
				}
				if(arr[i - 1] == 'I' && arr[i] == 'p' && arr[i + 1] == '-' && arr[i + 2] == '>')
					t->var = 'i';		 
				if(sign != -1) {
					t->type = OPERATOR;
					t->op = arr[i - 1];
				}
				if(arr[i-1] == '+' && arr[i] == '+' && arr[i + 1] <= 'z' && arr[i + 1] >= 'a')
					t->type = PREINC;
				if(arr[i-1] == '+' && arr[i] == '+' && arr[i - 2] <= 'z' && arr[i - 2] >= 'a')
					t->type = POSINC;
				if(arr[i-1] == '-' && arr[i] == '-' && arr[i + 1] <= 'z' && arr[i + 1] >= 'a')
					t->type = PREDEC;
				if(arr[i-1] == '-' && arr[i] == '-' && arr[i - 2] <= 'z' && arr[i - 2] >= 'a')
					t->type = POSDEC;		
				currstate = nextstate;
				if(arr[i - 1] == '/' && arr[i] == '*') {
					while(1) {
						i++;
						if(arr[i] == '*' && arr[i + 1] == '/') {
							break;
						}
					}
					nextstate = SPC;
					i = i + 1;
					break;
				}
				if(arr[i-1] == '<' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '>' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '=' && arr[i] == '=') {
					t->var = 'y';
				}
				if(arr[i - 1] == '=' && arr[i] == '!') {
					t->var = 'n';
				}		
				if(nextstate == DIG) { 
					if(arr[i] == '.') {
						flag = 1;
						dec = 0;
					}
					else {	
						m = 1;
						num = arr[i] - '0';
						if(flag == 1)
							dec++;
					}
				}
				i++;
				return t;
				break;
			case VAR:
				if(arr[i] == '=') {
					t->flag = 1;
				}
				else
					t->flag = 0;
				t->type = VARIABLE;
				t->var = arr[i - 1];
				currstate = nextstate;
				if(nextstate == DIG) { 
					if(arr[i] == '.') {
						flag = 1;
					}
					else {
						m = 1;
						num = arr[i] - '0';
						if(flag == 1)
							dec++;
					}
				}
				i++;
				return t;
				break;
			case STOP:
				t->type = END;
				currstate = nextstate;
				i++;
				return t;
				break;
			case ERR:
				t->type = ERROR;
				currstate = nextstate;
				i++;
				return t;
				break;
		}
		currstate = nextstate;
		i++;
	}
}



