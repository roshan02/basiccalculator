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

#ifndef __MYBCLIST_H
#define __MYBCLIST_H
#define PLUS 1
#define MINUS -1 
#define PI 3.1415926535
#include<math.h>
typedef struct node {
	int num;
	int flag;
	struct node *next, *prev;
}node;

typedef struct list {
	node *head, *tail;
	int len, dec, sign;
}list;
void init(list *l);
void insert(list *l, int pos, int num);
int remov(list *l, int pos);
void traverse(list *l, int arg);
void append(list *l, int num);
int length(list *l);
int dec(list *l);
int show(list *l, int pos);



#endif
