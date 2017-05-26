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

#ifndef __MYBCBIGNUM_H
#define __MYBCBIGNUM_H
#define PLUS 1
#define MINUS -1 
#define PI 3.1415926535
#include<math.h>
#include "mybclist.h"

void copy(list *l1, list *l2);
int checkzero(list *l);
list *addnum(list *l1, list *l2);
list *subnum(list *l1, list *l2);
list *mulnum(list *l1, list *l2);
list *division(list *l1, list *l2);
list *modulus(list *l1, list *l2);
int compare(list *l1, list *l2);
list *power(list *l1, list *l2);
list *factorial(list *l1, list *l2);
double radian(list *l1);
list *sine(list *l);
list *cosine(list *l);
list *tangent(list *l);
list *expo(list *l);
list *todecimal(list *l1, list *l2);
list *decimalto(list *l1, list *l2);
list *isprime(list *l);
#endif
