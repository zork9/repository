/*
;; Copyright (C) Johan Ceuppens 2011-2012
;; This program is free software: you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation, either version 2 of the License, or
;; (at your option) any later version.

;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with this program.  If not, see <http://www.gnu.org/licenses/>.
;;Copyright (c) 2011-2012, Johan Ceuppens
;;All rights reserved.

;;Redistribution and use in source and binary forms, with or without
;;modification, are permitted provided that the following conditions are met:
;;1. Redistributions of source code must retain the above copyright
;;   notice, this list of conditions and the following disclaimer.
;;2. Redistributions in binary form must reproduce the above copyright
;;   notice, this list of conditions and the following disclaimer in the
;;   documentation and/or other materials provided with the distribution.
;;3. All advertising materials mentioning features or use of this software
;;   must display the following acknowledgement:
;;   This product includes software developed by the Johan Ceuppens.
;;4. Neither the name of the Johan Ceuppens nor the
;;   names of its contributors may be used to endorse or promote products
;;   derived from this software without specific prior written permission.

;;THIS SOFTWARE IS PROVIDED BY Johan Ceuppens ''AS IS'' AND ANY
;;EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
;;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;;DISCLAIMED. IN NO EVENT SHALL Johan Ceuppens BE LIABLE FOR ANY
;;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
;;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
;;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
;;ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;;(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
;;SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "symboltable.h"

char *get1(char *str)
{
	int i;
	char *retstr = (char *)malloc(strlen(str)+1);//FIXME
	for (i = 0; str[i] != '\0' && str[i] != ' ' && str[i] != ';' && str[i] != ',' /*&& 
		((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))*/; i++) {

		//printf("++++++++++++++++++++>%c\n", str[i]);

		retstr[i] = str[i];	

	}
	retstr[strlen(str)] = '\0';
	return retstr;
}

int make_symtab ()
{
	printf("Making symtab...\n");
//	heapmax_global = 2;
	return 0;
}

/*
* Symtab elt adding functions
*/
int add_symtab(SymtabElt **se)
{

	symtab_global[(*se)->address] = (*se);
	
	return 1;

}

int add_symtabname(char **name, SymtabElt **se)
{
	int i;
	SymtabNameElt *sne = (SymtabNameElt *)malloc(sizeof(SymtabNameElt));
	sne->name = strdup(*name);
	(*se)->address = heapmax_global;//sne->address;//FIXME strdup ?;
	sne->address = heapmax_global;	
	symtabname_global[heapmaxname_global] = sne;
	heapmaxname_global += 1;	
	heapmax_global += 2;	

	add_symtab(se);	
	return 0;	
}
int add_symtabname_withaddress(char **name, SymtabElt **se)
{
	int i;
	SymtabNameElt *sne = (SymtabNameElt *)malloc(sizeof(SymtabNameElt));
	sne->name = *name;
	sne->address = heapmaxname_global;	
	symtabname_global[heapmaxname_global] = sne;
	heapmaxname_global += 1;	
//	heapmax_global += 2;	
//	(*se)->address = sne->address;//FIXME strdup ?;
	add_symtab(se);	
	return 0;	
}

int get_symtabname(const char **name, SymtabElt **se)
{
	int i = 0;
	SymtabNameElt *sne;
	for (i = 0; i < HEAPSIZE; i++) {
		sne = symtabname_global[i];
		//printf("name=%d\n", sne);
		//printf("HEAPPTR=%d name=%s\n",i, *name);
		if (sne != NULL 
		&&
		*name != NULL
		&&
		strlen(*name) > 0	
		&&/* (comparealpha(sne->name, *name) >= 3 ||*/ 
		strncmp(sne->name, *name, strlen(*name)) == 0)//FIXME 1 -> strlen, only first letter is matched ! 
			break;
	}

	if (i >= HEAPSIZE) { (*se) = NULL; return -1; }
	(*se) = (SymtabElt *)malloc(sizeof(SymtabElt));
	(*se) = symtab_global[sne->address];
	//printf("se addr=%d\n", i/*sne->address*/ );	
	return 1; 
}


/*
void assign(char  *a, char *b)
{

//	isascii((int)b) ? add_symtab_character(*&s,(int)a, b[0]) : assign_number(s, a, atof(b));//mo

	printf("Assigning...%s := %s\n", a , b);

}
*/
#if 0
int main()
{

	Symtab s;
	make_symtab(&s);

	SymtabElt e;
	e.type = INTEGER;
	e.Integer = 123;	

	add_symtab(&e);	
	//print_symtab(&s);
}
#endif
