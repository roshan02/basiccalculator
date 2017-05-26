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

#ifndef __MYBCSTACKS_H
#define __MYBCSTACKS_H
#include "mybclist.h"

/*******************************stack.h**********************************/
#define MAX 1024
typedef struct stack{
	int i;
	list *l[MAX];
	
}stack;
void push(stack *s, list *l);
list *pop(stack *s);
int empty(stack *s);
int full(stack *s);
void sinit(stack *s);


/*******************************stack1.h**********************************/
#define MAX 1024
typedef struct stack1{
	int i;
	list *l[MAX];
	
}stack1;
void push1(stack1 *s, list *l);
list *pop1(stack1 *s);
int empty1(stack1 *s);
int full1(stack1 *s);
void sinit1(stack1 *s);


/****************************cstack.h***************************************/
#define MAX 1024
typedef struct cstack{
	char a[MAX];
	int i;
}cstack;
void cpush(cstack *s, char num);
char cpop(cstack *s);
int cempty(cstack *s);
int cfull(cstack *s);
void cinit(cstack *s);
#endif


