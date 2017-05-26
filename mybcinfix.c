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


/*******************************infix2.c**************************************/
#include<stdio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "mybcstacks.h"
#include "mybclist.h"
#include "mybcbignum.h"
#include "mybcinfix.h"
#include "mybctoken.h"
/*Precedence function returns the precedence of operand given as argument*/
int precedence(char op) {
	if(op == '*' || op == '/' || op == '%')
		return 3;
	if(op == '+' || op == '-')
		return 2;
	if(op == '(')
		return 1;
	return 0;
}

/*Readline reads the string inputed and stores it in an array */
int readline(char *arr, int len) {
	int k = 0;
	int ch;
	while((ch = getchar()) != '\n' && k < len - 1) {
		arr[k] = ch;
		k++;
	}
	arr[k] = '\0';
	return k;
}
/*Infix function solves the infix equation.
*It takes Input in form of tokens from getnext
*and stores operators in cstack and operands in stack
* '(' and ')' are considered to be as operands.
* When a closing bracket comes it pops the operands out and do the calculations. At a time it pops two operators out.  
*/ 
static list *L[26][10];
list *infix(char *str) {
	list *x, *y, *z, *w;
	x = (list *)malloc(sizeof(list));
	y = (list *)malloc(sizeof(list));
	z = (list *)malloc(sizeof(list));
	w = (list *)malloc(sizeof(list));
	static int r[26];
	static int f[26];
	init(x);
	init(y);
	init(z);
	init(w);
	int reset = 1, c, b;
	char op1, op2, ch;
	token *t;
	t = (token *)malloc(sizeof(token));
	cstack cs;
	stack a;
	stack1 e;
	sinit(&a);
	cinit(&cs);
	sinit1(&e);
	int flag = 0, setpow = 0, settrigo = 0, comparison = 0, ip = 0;
	int i = 0, k, varflag = 0, m, prepos, postfix = 0, decimal = 0, decimal1 = 0;
	i = 0;
	while(1) {
		t = getnext(str, &reset);
		if(t->type == OPERAND){
			if(setpow == 1) {
				x = pop(&a);
				if(dec(t->l) != 0)
					return NULL;
				y = power(x, t->l);
				setpow = 0;
				push(&a, y);
			}
			else {
				push(&a, t->l);
			}
		}
		else if(t->type == OPERATOR) {
			switch(t->op) {
				case '+': case '/': case '*': case '-': case '%':
					cpush(&cs, t->op);
					break;
				case '(':
					cpush(&cs, t->op);
					flag++;
					break;
				case '^':
					setpow = 1;
					break;
				case 'S': 
					settrigo = 1;
					break;
				case 'C':
					settrigo = 2;
					break; 
				case 'T':
					settrigo = 3;
					break;
				case 'E':
					settrigo = 4;
					break;
				case 'B': case 'O': case 'H':
					decimal = 2;
					if(t->var == 'a')
						decimal = 2;
					if(t->var == 'b')
						decimal = 8;
					if(t->var == 'c')
						decimal = 16;
					t = getnext(str, &reset);
					t = getnext(str, &reset);
					t = getnext(str, &reset);
					break;
				case 'D':
					decimal1 = 2;
					if(t->var == 'd')
						decimal1 = 2;
					if(t->var == 'e')
						decimal1 = 8;
					if(t->var == 'f')
						decimal = 16;
					t = getnext(str, &reset);
					t = getnext(str, &reset);
					t = getnext(str, &reset);
					break;
				case '!':
					x = pop(&a);
					append(w, 1);
					if(dec(x) != 0 || x->sign == -1)
						return NULL;
					else {	
						push(&a, factorial(x, w));
					}
					remov(w, 0);
					break;
				case 'I': 
					if(t->var == 'i') {
						ip = 1;
						getnext(str, &reset);
						getnext(str, &reset);
						getnext(str, &reset);
					}
					break;
				case '<':
					comparison = 1;
					if(t->var == 'y') {
						t = getnext(str, &reset);
						comparison = 2;
					}
					break;
				case '>':
					comparison = 3;
					if(t->var == 'y') {
						t = getnext(str, &reset);
						comparison = 4;
					}
					break;
				case '=':
					if(t->var == 'y') {
						t = getnext(str, &reset);
						comparison = 5;
					}
					if(t->var == 'n') {
						t = getnext(str, &reset);
						comparison = 6;
					}
					break;	
				case ')':
					if(settrigo != 0) {
						switch(settrigo) {
							case 1:
								x = pop(&a);
								y = sine(x); 
								push(&a, y);
								break;
							case 2:
								x = pop(&a);
								y = cosine(x); 
								push(&a, y);
								break;
							case 3:
								x = pop(&a);
								y = tangent(x); 
								push(&a, y);
								break;
							case 4:
								x = pop(&a);
								y = expo(x);
								push(&a, y);
								break;
						}
						settrigo = 0;
					}						 
					flag--;
					if(flag < 0)
						return NULL;
					while(1) {
						if(!cempty(&cs)) {
							op1 = cpop(&cs);
							if(op1 == '(') {
								break;
							}						
						}
						else
							break;
						if(!cempty(&cs)) 
							op2 = cpop(&cs);
						c = precedence(op1);
						b = precedence(op2);
						if(c > b) {
							if(!empty(&a)) 
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							switch(op1) {
								case '+':
									push(&a, addnum(y, z));
									break;
								case '-':
									push(&a, subnum(y, z));
									break;
								case '/':
									push(&a, division(y, z));
									break;
								case '*':
									push(&a, mulnum(y, z));
									break;
								case '%':
									push(&a, modulus(y,z));
									break;
							}
							if(op2 != '(') {
								if(!empty(&a))
									z = pop(&a);
								else
									return NULL;
								if(!empty(&a))
									y = pop(&a);
								else
									return NULL;
								switch(op2) {
									case '+':
										push(&a, addnum(y, z));
										break;
									case '-':
										push(&a, subnum(y, z));
										break;
									case '/':
										push(&a, division(y, z));
										break;
									case '*':
										push(&a, mulnum(y, z));
										break;
									case '%':
										push(&a, modulus(y,z));
										break;
								}
							}
						}
						else if(c <= b) {
							if(!empty(&a))
								z = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								y = pop(&a);
							else
								return NULL;
							if(!empty(&a))
								x = pop(&a);
							else
								return NULL;
							switch(op2) {
								case '+':
									x = addnum(x, y);
									break;
								case '-':
									x = subnum(x, y);
									break;
								case '/':
									x = division(x, y);
									break;
								case '*':
									x = mulnum(x, y);
									break;
								case '%':
									x = modulus(x, y);
									break;	
							}
							switch(op1) {
								case '+':
									push(&a, addnum(x, z));
									break;
								case '-':
									push(&a, subnum(x, z));
									break;
								case '/':
									push(&a, division(x, z));
									break;
								case '*':
									push(&a, mulnum(x, z));
									break;
								case '%':
									push(&a, modulus(x,z));
									break;
							}
						}
					}
					break;	
				default:
					printf("default");
					return NULL;
					break;
			}
		}			
		else if(t->type == END) {
			while(!empty(&a)) {
				x = pop(&a);
				push1(&e, x);
				
			}
			char op[100];
			i = 0;
			while(!cempty(&cs)) {
				op[i] = cpop(&cs);
				i++;
			}
			int j = 0;
			while(j < i) {
				cpush(&cs, op[j]);
				j++;
			}
						
			while(1) {
				if(flag != 0)
					return NULL;
				if(!cempty(&cs)) {
					op1 = cpop(&cs);
				}
				else {
					break;
				}
				if(!cempty(&cs))
					op2 = cpop(&cs);
				else {	
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push1(&e, addnum(z, y));
							break;
						case '-':
							push1(&e, subnum(z, y));
							break;
						case '/':
							push1(&e, division(z, y));
							break;
						case '*':
							push1(&e, mulnum(z, y));
							break;
						case '%':
							push1(&e, modulus(z,y));
							break;
					}
					break;
				}
				c = precedence(op1);
				b = precedence(op2);
				if(c >= b) {
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					switch(op1) {
						case '+':
							push1(&e, addnum(z, y));
							break;
						case '-':
							push1(&e, subnum(z, y));
							break;
						case '/':
							push1(&e, division(z, y));
							break;
						case '*':
							push1(&e, mulnum(z, y));
							break;
						case '%':
							push1(&e, modulus(z, y));
							break;
					}
					cpush(&cs, op2);
				}
				else if(c < b) {
					if(!empty1(&e)) {
						z = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e)) {
						y = pop1(&e);
					}
					else
						return NULL;
					if(!empty1(&e))
						x = pop1(&e);
					else
						return NULL;
					switch(op2) {
						case '+':
							push1(&e, addnum(y, x));
							break;
						case '-':
							push1(&e, subnum(y, x));
							break;
						case '/':
							push1(&e, division(y, x));
							break;
						case '*':
							push1(&e, mulnum(y, x));
							break;
						case '%':
							push1(&e, modulus(y, x));
							break;		
					}
					push1(&e, z);
					cpush(&cs, op1);
				}		
			}
			if(ip == 1) {
				if(!empty1(&e))
					y = pop1(&e);
				else
					return NULL;
				push1(&e, isprime(y));
				ip = 0;
			}
			if(!empty1(&e) && cempty(&cs)) {
				
				y = (pop1(&e));
				if(varflag == 1) {
					L[k][f[k]] = y;
					if(postfix == 1) {
						list *unity;
						unity = (list *)malloc(sizeof(list));
						init(unity);
						append(unity, 1);
						if(prepos == 2) {
							L[m][f[k]] = addnum(L[m][f[k]], unity);
							r[k] = r[k] + 1;
							prepos = 0;
						}
						else if(prepos == 4) {
							L[m][f[k]] = subnum(L[m][f[k]], unity);
							r[k] = r[k] + 1;
							prepos = 0;
						}
						postfix = 0;		
					}
					varflag = 0;
					f[k] = f[k] + 1;
					x = NULL;
					free(x);
					z = NULL;
					free(z);
					w = NULL;
					free(w);
					return y;
				}
				if(decimal == 2 || decimal == 8 || decimal == 16) {
					list *base;
					base = (list *)malloc(sizeof(list));
					init(base);
					append(base, decimal);
					if(decimal == 2) {
						z = todecimal(y, base);
						push1(&e, z);						
					}
					if(decimal == 8) {
						z = todecimal(y, base);
						push1(&e, z);						
					}
					if(decimal == 16) {
						z = todecimal(y, base);
						push1(&e, z);						
						
					}
					decimal = 0;
					free(base);
					x = NULL;
					y = NULL;
					w = NULL;
					free(x);
					free(y);
					free(w);
					return z;
				}
				if(decimal1 == 2 || decimal1 == 8 || decimal1 == 16) {
					list *base;
					base = (list *)malloc(sizeof(list));
					init(base);
					append(base, decimal1);
					if(decimal1 == 2) {
						z = decimalto(y, base);
						push1(&e, z);						
					}
					if(decimal1 == 8) {
						z = decimalto(y, base);
						push1(&e, z);						
					}
					if(decimal1 == 16) {
						z = decimalto(y, base);
						push1(&e, z);						
						
					}
					decimal1 = 0;
					free(base);
					x = NULL;
					y = NULL;
					w = NULL;
					free(x);
					free(y);
					free(w);
					return z;
				}
				if(comparison != 0) {	
					switch(comparison) {
						z = NULL;
						free(z);
						z = (list *)malloc(sizeof(list));
						init(z);
						case 1:
							x = pop1(&e);
							if(compare(y, x) < 0) {
								append(z, 1);
							 	push1(&e, z);
							 
							}
							else {
							 	append(z, 0);
							 	push1(&e, z);
							}
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
						case 2:
							x = pop1(&e);
							if(compare(y, x) <= 0) {
								append(z, 1);
								push1(&e, z);
							}
							else {
								append(z, 0);
								push1(&e, z);
							}
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
						case 3:
							x = pop1(&e);
							if(compare(y, x) > 0) {
							 	append(z, 1);
							 	push1(&e, z);
							 }
							 else {
							 	append(z, 0);
							 	push1(&e, z);
							 }
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
						case 4:
							x = pop1(&e);
							if(compare(y, x) >= 0) {
								append(z, 1);
								push1(&e, z);
							}
							else {
								append(z, 0);
								push1(&e, z);
							}
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
						case 5:
							x = pop1(&e);
							traverse(x, 1);
							traverse(y, 1);
							if(compare(y, x) == 0) {
								append(z, 1);
								push1(&e, z);
							}
							else {
								append(z, 0);
								push1(&e, z);
							}
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
						case 6:
							x = pop1(&e);
							if(compare(y, x) != 0) {
								append(z, 1);
								push1(&e, z);
							}
							else {
								append(z, 0);
								push1(&e, z);
							}
							x = NULL;
							y = NULL;
							w = NULL;
							free(x);
							free(y);
							free(w);
						 	return z;
							break;
					}
					comparison = 0;
				}
				if(empty1(&e) && cempty(&cs)) {
					x = NULL;
					z = NULL;
					w = NULL;
					free(x);
					free(z);
					free(w);
					return (y);
					
				}
				else if(setpow == 1) {
					if(!empty1(&e))
						x = pop1(&e);
					else
						return NULL;
					if(x->dec != 0)
						return NULL;
					z = power(y, x);
					setpow = 0;
					x = NULL;
					y = NULL;
					w = NULL;
					free(x);
					free(y);
					free(w);
					return z;
				}
				else {
					x = NULL;
					y = NULL;
					w = NULL;
					z = NULL;
					free(x);
					free(y);
					free(w);
					free(z);
					return NULL;	
				}	
			}
			else {
				
				x = NULL;
				y = NULL;
				w = NULL;
				z = NULL;
				free(x);
				free(y);
				free(w);
				free(z);
				return NULL;
			}
			
		}
		else if(t->type == ERROR) {
			printf("error");
			x = NULL;
			y = NULL;
			z = NULL;
			w = NULL;
			free(x);
			free(y);
			free(z);
			free(w);
			return NULL;
		}
		else if(t->type == PREINC) {
			prepos = 1;
			getnext(str, &reset);
		}
		else if(t->type == POSINC) {
			postfix = 1;
			getnext(str, &reset);
			varflag = 1;
			prepos = 2;
		}
		else if(t->type == PREDEC) {
			prepos = 3;
			getnext(str, &reset);
		}
		else if(t->type == POSDEC) {
			postfix = 1;
			getnext(str, &reset);
			prepos = 4;
			varflag = 1;
		}
		else if(t->type == VARIABLE) {
			if(t->flag == 1) {
				ch = t->var;
				k = ch - 'a';
				if(r[k] != 0) {
					
					L[k][r[k]] = (list*)malloc(sizeof(list));
					init(L[k][r[k]]);
					r[k] = r[k] + 1;
				}
				else {
					L[k][0] = (list*)malloc(sizeof(list));
					init(L[k][0]);
					r[k] = 1;
					f[k] = 0;
				}					
				varflag = 1;
				t = getnext(str, &reset);
			}
			else {
				ch = t->var;
				m = ch - 'a';
				if(prepos == 1 || prepos == 3) {
					list *unity;
					unity = (list *)malloc(sizeof(list));
					init(unity);
					append(unity, 1);
					L[m][r[m]] = (list*)malloc(sizeof(list));
					init(L[m][r[m]]);
					r[m] = r[m] + 1;
					varflag = 1;
					switch(prepos) {
						case 1:	
							L[m][f[m] - 1] = addnum(L[m][f[m] - 1], unity);
							push(&a, L[m][f[m] - 1]);
							break;
						case 3:
							L[m][f[m] - 1] = subnum(L[m][f[m] - 1], unity);
							push(&a, L[m][f[m] - 1]);
							break;
					}
					prepos = 0;
				}
				else {
					push(&a, L[m][f[m] - 1]);
				}
			}
			
		} 	
	}
	if(!empty1(&e))
		return (pop1(&e));
	printf("last");
	return NULL;						
}
		

