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

#ifndef __MYBCTOKEN_H
#define __MYBCTOKEN_H
#define OPERAND 10 
#define OPERATOR 20
#define VARIABLE 30
#define	END	40
#define ERROR	50
#define PREINC	60
#define POSINC	70
#define PREDEC	80
#define POSDEC	90
typedef struct token {
	char op;
	int dec;
	int type; /* type takes values OPERAND/OPERATOR/END/*/	
	list *l; 
	int flag;
	char var;
	
}token;
token *getnext(char *, int *);
enum states { SPC, DIG, OPR, VAR, STOP, ERR };
#endif
