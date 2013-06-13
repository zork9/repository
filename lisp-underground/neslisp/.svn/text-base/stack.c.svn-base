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
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int make_stack(Stack **st)
{
	*st = (Stack *)malloc(sizeof(Stack));
	(*st)->length = 0;
	(*st)->stack = NULL;

}		

int stack_push(Stack **st, char **e, char **name)
{
	int i = 0;
	if (*st == NULL)
		return -1;	

	StackElt *se = (StackElt *)malloc(sizeof(StackElt));

	if (se == NULL) return -1;

	se->elt = strdup(*e);
	se->name = strdup(*name);
	se->next = (*st)->stack;
	(*st)->stack = se;
	(*st)->length ++;

	printf("STACK=%s\n",se->elt);
	
	return 1;
}

int stack_pop_andreturn(Stack **st, char **ret, char **retname) 
{
	int i = 0;
	if (*st == NULL)
		return -1;	

	StackElt *tmp = (*st)->stack;
	if (tmp != NULL) {
		 *ret = (*st)->stack->elt;
		 *retname = (*st)->stack->name;
	 } else { 
		 *ret = NULL;
		return -1;
		}
	//*ret = malloc(sizeof(*tmp));
	//memcpy(*ret, tmp, sizeof(tmp));
	(*st)->stack = tmp->next;	
	(*st)->length --;
	return 1;
}

int stack_pop(Stack **st) 
{
	int i = 0;
	if (*st == NULL)
		return -1;	

	StackElt *tmp = (*st)->stack;
	(*st)->stack = tmp->next;	

	free(tmp);
	(*st)->length --;

	return 1;
}

void stack_print(Stack **st)
{
	int i = 0;
	StackElt *tmp = (*st)->stack;
	for (i = 0; i < (*st)->length - 1; i++) {
		fprintf(stdout, "Stack print : %s\n", (char *)(*st)->stack);//FIXME char * -> void * 
		tmp = tmp->next;	

	}
	
}

#if 0 
int main()
{

	Stack *s;
	int i = 12;	
	make_stack(&s);
	char *e = &i;
	stack_push(&s, e); 

	char *e2 = &i;
	stack_push(&s, e2); 
	
	char *e3 = &i;
	stack_push(&s, e2); 
	
	char *e4 = &i;
	stack_push(&s, e2); 

	stack_print(&s);
	
	stack_pop(&s);
	stack_pop(&s);
	
	stack_print(&s);

	return 0;
}
#endif
