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
#include "moose.h"
#include "symboltable.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int as1_write_functionjump(const char *name, const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i = 0,j = 0;
	char *opexp, *str;
	printf((char *)"writing function jump to %s...\n", name);	
	//utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);
	printf((char *)"writing %s...\n", opexp);	


	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);
	}
	for (j = 0; i < strlen(opexp); j++, i++) {
	if (getarg(&opexp, &i, &str) == 0) {
		
		printf((char *)"============%d\n", atoi(str));
		if (utility_isdigit(str) == 0) {
			fprintf(fp, (char *)"ldx #%d\n", atoi(str));
			fprintf(fp, (char *)"stx $%d\n", 3000+j);
		} else if (utility_isalpha(str) == 0) {
			SymtabElt *e = NULL;
			get_symtabname(&str, &e);	
			fprintf(fp, (char *)"ldx $%d\n", e->address);
			fprintf(fp, (char *)"stx $%d\n", 3000+j);
		} else if (utility_islist(str) == 0) {
			as1_write_list(str,opexp); 
		} else {
			fprintf(fp, (char *)"ldx $%d\n", 6000);//FIXME +j 6002 etc.;
			fprintf(fp, (char *)"stx $%d\n", 3000+j);
		}	/*FIXME	
		} else {
			fprintf(stdout, (char *)"_ function _ : unknown argument \n");
		}*/
	}
	}
	fprintf(fp, (char *)"jmp %s\n", name);
	fclose(fp);
	return 1;
}



int as1_write_operator_plus(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing operator +...\n");	


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	fprintf(fp, (char *)"sta #0\n");

	for (i = strlen(opexp); i >= 0; i--) {//NOTE opexp has been chomped : -2
	
	char *str;
	getstring(&opexp, &i,&str);
	//printf((char *)"str=%s\n",str);

	if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
	fprintf(fp, (char *)"lda #%d\n", n);
	fprintf(fp, (char *)"adc $%d\n", 1000);//FIXME j
	fprintf(fp, (char *)"sta $%d\n", 1000);
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ operator + _ undefined identifier : %s \n", str);
		} /*FIXME else if (se->type != INTEGER && se->type != FLOAT && se->type != LOOPARG && se->type != FUNCARG) {
			fprintf(stdout, (char *)"_ operator + _ wrong type argument : %s %s\n", opexp, opexp);	
			//exit(99);
		} */ else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"adc $%d\n", 1000);
			fprintf(fp, (char *)"sta $%d\n", 1000);
		}			
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}
	fprintf(fp, (char *)"sta $%d\n", 6000);
	fclose(fp);
	return 0;
}





int as1_write_operator_minus(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing operator -...\n");	


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	fprintf(fp, (char *)"sta #0\n");

	for (i = strlen(opexp); i >= 0; i--) {//NOTE opexp has been chomped : -2
	
	char *str;
	getstring(&opexp, &i,&str);
	printf((char *)"str=%s\n",str);

	if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
	fprintf(fp, (char *)"lda #%d\n", n);
	fprintf(fp, (char *)"sbc $%d\n", 1000);//FIXME j
	fprintf(fp, (char *)"sta $%d\n", 1000);
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ operator - _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, (char *)"_ operator - _ wrong type argument : %s\n", opexp);	
			//exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sbc $%d\n", 1000);
			fprintf(fp, (char *)"sta $%d\n", 1000);
		}			
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}
	fprintf(fp, (char *)"sta $%d\n", 6000);
	fclose(fp);
	return 0;
}



int as1_write_ifsecondclauseend(char *s, int labelc)
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing if second clause end...");	

	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	fprintf(fp, (char *)"%s%d:\n", (char *)"compare", labelc);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fclose(fp);
}


int as1_write_iffirstclauseend(char *s, int labelc)
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing if first clause end...");	

	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}
	//JUMP
	//labelcounter++;
	fprintf(fp, (char *)"jmp %s%d\n", (char *)"compare", labelc);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fprintf(fp, (char *)"%s%d:\n", (char *)"compare", labelc);//NOTE address 6000 FIXME1 loop var label must be fixed	
	//labelcounter++;
	fclose(fp);
}


int as1_write_whenendsecond()
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing when end...");	

	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	fprintf(fp, (char *)"compare%d:\n", labelcounter);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fclose(fp);
}

int as1_write_ifclausethird(char *s, int labelc)
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing when end...");	

	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}
	//JUMP2
	fprintf(fp, (char *)"compare%d:\n", labelc);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fclose(fp);
}


int as1_write_whenend()
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing when end...");	

	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	fprintf(fp, (char *)"sta $%d\n", 6000);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fprintf(fp, (char *)"when%d:\n", labelcounter);//NOTE address 6000 FIXME1 loop var label must be fixed	
	fclose(fp);
}



int as1_write_loopend()
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing loop end...");	

	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	fprintf(fp, (char *)"ldx $%d\n", 1500);//NOTE address 1500	
	fprintf(fp, (char *)"inx\n");//NOTE on address 1500	
	fprintf(fp, (char *)"stx $%d\n", 1500);//NOTE addres 1500	
	fprintf(fp, (char *)"cmp $%d\n", 1502);//NOTE address 1502
	fprintf(fp, (char *)"bne %s%d\n", LOOP, labelcounter);//FIXME1 loop var label must be fixed	

}

/*

Function args are stored at 3000
*/

int as1_write_loop(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i = 0;
	char *forname, *fromname, *toname, *doname, *minimumname, *maximumname;
	char *args;
	char *opexp;


	/* read in "for" */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &forname);

	/* read in opexp, counter variable */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &opexp);

	SymtabElt *se = (SymtabElt *)malloc(sizeof(SymtabElt));
	add_symtabname(&opexp, &se); //NOTE add a single name (loop arg)
	//se->Integer = atoi(minimumname);
	/* read in "from" */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &fromname);
	
	/* read in minimum value 1 */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &minimumname);
	
	/* read in "to" */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &toname);
	
	/* read in maximum value 2 */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &maximumname);
	
	/* read in "do" */

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &doname);
	
	printf((char *)"writing loop...%s %s %s %s %s %s %s\n", forname, opexp, fromname, minimumname, toname, maximumname, doname);	



	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	/* counter variable , see above */

	//char *value;
	//get_symtabname(&opexp, se);
	fprintf(fp, (char *)"ldx #%d\n", atoi(minimumname));	
	fprintf(fp, (char *)"stx $%d\n", se->address);	
	
	fprintf(fp, (char *)"ldx #%d\n", atoi(minimumname));	
	fprintf(fp, (char *)"stx $%d\n", 1500);	
	fprintf(fp, (char *)"%s%d:\n", LOOP,labelcounter);;//FIXME unique label	

	if (opexp == NULL)
		return 0;
/*
	if (opexp != NULL && utility_isalpha(opexp) == 0) { //NOTE str is loop arg
		SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
		//e->address = 3000 + j;
		//e->pn = 3000 + j;
		e->type = LOOPARG;
		e->Integer = NIL;	
		e->Float = NIL;	
		e->Character = 0;//NIL;	
		e->Null = 0;//NIL;	
		e->String = NULL;//NIL;		
		e->List = NULL;			
		add_symtabname(&opexp, &e); //NOTE add a single name (func arg)
*/		//fprintf(fp, (char *)"stx $%d\n", e->address);;//loop counter init
		fprintf(fp, (char *)"ldx #%d\n", atoi(maximumname));	
		fprintf(fp, (char *)"stx $%d\n", 1502);//NOTE addres 1500	
//	}
	fclose(fp);
//	free(str);
	return 0;
}

int as1_write_functionend(char **name)
{
	FILE *fp;
	int i = 0;

	
	printf((char *)"writing defun end..\n");	


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"nescc error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"nescc error - Cannot seek in code output file\n");
		exit(99);

	}

	fprintf(fp, (char *)"%s:\n", *name);	

	fclose(fp);
	return 0;
}

int as1_write_functionheader(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i = 0;
	char *name;
	char *args;
	char *opexp;

	utility_skip_whitespace_newlines_parens(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &name);
	utility_skip_whitespace_newlines_parens(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);
	
	printf((char *)"writing defun...opexp=%s\n",opexp);	


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"nescc error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"nescc error - Cannot seek in code output file\n");
		exit(99);

	}

	//fprintf(fp, (char *)"%s:\n", name);	

	SymtabElt *se = (SymtabElt *)malloc(sizeof(SymtabElt));
	se->type = FUNC;
	//FIXME type etc. of se	

	se->address = heapmax_global;
	heapmax_global += 2;
	se->pn = se->address;

	add_symtabname(&name, &se);
	/* jump out if there are no arguments */
	if (opexp == NULL)
		return 0;
	/* put all arguments in str */	
	char *str;// = (char *)malloc(1024);
	/*for (i = strlen(opexp); i >= 0; i--) {
		getargstring(opexp, &i, &str);
	}*/
	/* extract all single arguments out of str */
	char *str2;
	int j = 0;
	for (i = 0, j = 0; i < strlen(str)-1; i++, j++) {
		
		getarg(&opexp, &i, &str2);

			printf((char *)"str2=%s\n", str2);
		/*if the string is alphanumeric we need to look up the symbol */
		if (str2 != NULL && utility_isalpha(str2) == 0) { //NOTE string is func arg
			SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
			e->address = 3000 + j;//heapmax_global;//FIXME 3000 ++ globally;
			//heapmax_global += 2;
			e->pn = 3000 + j;
			
			e->type = FUNCARG;//NOTE nil types are not nil but are searched for at runtime for dynamic binding
			e->Integer = NIL;	
			e->Float = NIL;	
			e->Character = 0;//NIL;	
			e->Null = 0;//NIL;	
			e->String = NULL;//NIL;		
			e->List = NULL;			
			add_symtabname_withaddress(&str2, &e); //NOTE add a single name (func arg)
		} else if (str2 != NULL && utility_isdigit(str2) == 0) { //NOTE string is func arg
			fprintf(stdout, (char *)"_ unknown function argument : is a digit : %s\n", str2);
		} else if (utility_islist(str2) == 0) {
			fprintf(stdout, (char *)"_ unknown function argument : is a list : %s\n", str2);
		} else {
			fprintf(stdout, (char *)"_ unknown function argument : type : %s %d\n", str2, i);
		}	
	}
//	fclose(fp);
//	free(str);
	return 0;
}


/*
* Lists are stored at 4000
*/
int as1_write_listorfunction(char *opexp)
{
	FILE *fp;
	int i = 0, j = 0;
	printf((char *)"writing list or function...");	
	int tempmax = heapmax_global;

	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	/* jump out if there are no arguments */
	if (opexp == NULL)
		return 0;//NOTE return empty list ?
	/* put all arguments in str */	
	char *str = opexp;//(char *)malloc(1024);
	int len = 0;
	for ( ; len < strlen(str)-1; len++) {
		char *str2 = (char *)malloc(1024);
		getarg(&str, &len, str2);	
		
		/*if the string is alphanumeric we need to look up the symbol */
	
		if (str2 != NULL && utility_isalpha(str2) == 0 && strlen(str2) > 0) {
			SymtabElt *se = NULL;
			get_symtabname(&str2, &se);
			if (se == NULL) {
				fprintf(stdout, (char *)"_ undefined indentifier : %s\n", str2);
			} else {
				if (se->type == FUNC) {
				}
			}				
		} else if (utility_isdigit(str2) == 0 && strlen(str2) > 0) {//FIXME heapmax
			int n = atoi(str2);		
			fprintf(fp, (char *)"ldx #%d\n", n);
			fprintf(fp, (char *)"stx $%d\n", 3000+j);
			//heapmax_global += 2;
			//i++;///NOTE
		} else if (utility_islist(str2) == 0) {
			as1_write_list(str2,opexp); 
		} else {
			fprintf(stdout, (char *)"_ unknown type : %s\n", str2);
		}	
		free(str2);	
	}

	fprintf(fp, (char *)"sta $%d\n", 6000);//FIXME stack;
	//free(str);
/*
	SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
	e->address = tempmax; 
	e->pn = e->address;
	e->type = LIST;//NOTE nil types are not nil but are searched for at runtime for dynamic binding
	e->Integer = NIL;	
	e->Float = NIL;	
	e->Character = NIL;	
	e->Null = NULL;	
	e->String = NULL;		
	e->List = (List *)malloc(sizeof(List));			
	e->List->length = tempmax - heapmax_global; 
*/
}



int as1_write_equalthan(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing equalthan ...\n");	


	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	fprintf(fp, (char *)"sta #0\n");

	for (j = 0, i = strlen(opexp); i >= 0; i--, j++) {
	
	char *str;
	getstring(&opexp, &i,&str);

	if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
		fprintf(fp, (char *)"lda #%d\n", n);
		fprintf(fp, (char *)"sta $%d\n", 1000+j);//FIXME if cond;
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ equal than _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, (char *)"_ equal than = _ wrong type argument : %s %s\n", opexp, opexp);	
			exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sta $%d\n", 1000+j);
		}		
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}


	fprintf(fp, (char *)"cmp $%d\n", 1000);//FIXME2 fixed value
	fprintf(fp, (char *)"sta $%d\n", 1000);
	fprintf(fp, (char *)"bne compare%d\n", labelcounter);
	

	fclose(fp);
	return 0;
}



int as1_write_greaterthan(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing greaterthan ...\n");	


	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	fprintf(fp, (char *)"sta #0\n");

	for (j = 0, i = strlen(opexp); i >= 0; i--, j++) {//NOTE opexp has been chomped : -2
	
	char *str;// = (char *)malloc(1024);	
	getstring(&opexp, &i,&str);

	if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
		fprintf(fp, (char *)"lda #%d\n", n);
		fprintf(fp, (char *)"sta $%d\n", 1000+j);//FIXME if cond;
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ greater than _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, "_ greater than > _ wrong type argument : %s %s\n", opexp, opexp);	
			exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sta $%d\n", 1000+j);
		}		
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}


	fprintf(fp, (char *)"cmp $%d\n", 1000);//FIXME2 fixed value
	fprintf(fp, (char *)"sta $%d\n", 1000);
	fprintf(fp, (char *)"bne compare%d\n", labelcounter);
	

	fclose(fp);
	return 0;
}



//fprintf(fp, (char *)"bne when%d\n", labelcounter);//result of < is stored in 1000

int as1_write_lessthan(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing lessthan ...\n");	


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}
	fprintf(fp, (char *)"sta #0\n");

	for (j = 0, i = 0; i < strlen(opexp); i++, j++) {//NOTE opexp has been chomped : -2
	
	char *str;
	//getstring(&opexp, &i,&str);
	getarg(&opexp, &i,&str);


	if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
		fprintf(fp, (char *)"lda #%d\n", n);
		fprintf(fp, (char *)"stx $%d\n", 1000+j);//FIXME if cond;
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, "_ lessthan _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, (char *)"_ lessthan < _ wrong type argument : %s %s\n", opexp, opexp);	
			exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sta $%d\n", 1000+j);
		}		
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	}


	fprintf(fp, (char *)"cmp $%d\n", 1000);
	fprintf(fp, (char *)"sta $%d\n", 1000);
	fprintf(fp, (char *)"bne compare%d\n", labelcounter);
	

	fclose(fp);
	return 0;
}





int as1_write_when(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing when ...\n");	


	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"nescc error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"nescc error - Cannot seek in code output file\n");
		exit(99);

	}


	for (j = 0, i = strlen(opexp); i >= 0; i--, j++) {//NOTE opexp has been chomped : -2
	
	char *str;
	getstring(&opexp, &i,&str);


	/* read if conditional and return */	

	if (opexp[1] == '<') {
		lispfileindex -= strlen(opexp);
		as1_write_lessthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne when%d\n", labelcounter);//result of < is stored in 1000


		return 1;
	} else if (opexp[1] == '>') {
		lispfileindex -= strlen(opexp);
		as1_write_greaterthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne when%d\n", labelcounter);//result of < is stored in 1000
		return 1;
	} else if (opexp[1] == '=') {
		lispfileindex -= strlen(opexp);
		as1_write_equalthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne when%d\n", labelcounter);//result of < is stored in 1000
		return 1;
	} else if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
		fprintf(fp, (char *)"sta $%d\n", 1000+j);
		i--;
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ lessthan _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, (char *)"_ when _ wrong type argument : %s %s\n", opexp, opexp);	
			exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sta $%d\n", 1000+j);
		}		
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}

	fprintf(fp, (char *)"bne when%d\n", labelcounter);//result of < is stored in 1000

	fclose(fp);
	return 0;
}





int as1_write_if(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i,j = 0;
	char *opexp;
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing if ...opexp=%s\n", opexp);	


	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"nescc error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"nescc error - Cannot seek in code output file\n");
		exit(99);

	}


	for (j = 0, i = 0; i < strlen(opexp); i++, j++) {//NOTE opexp has been chomped : -2
	
	char *str;
	//getstring(&opexp, &i,&str);
	getarg_until_parens(&opexp, &i,&str);//33333333333333;

	/* read if conditional and return */	

	if (opexp[1] == '<') {
		printf((char *)"lispfileindex=%s index=%d str=%s\n", *lispfilecontents, *lispfileindex, str);
		*lispfileindex -= strlen(str);//3333333333strlen(opexp);
		//*lispfileindex -= strlen(str);
		*lispfileindex +=2;//333333333333
		utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
		printf((char *)"lispfileindex=%s index=%d str=%s\n", *lispfilecontents, *lispfileindex, str);
		as1_write_lessthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne GNU%d\n", labelcounter);//result of < is stored in 1000
		return 1;
	} else if (opexp[1] == '>') {
		*lispfileindex -= strlen(opexp);
		*lispfileindex +=2;//333333333333
		utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
		as1_write_greaterthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne if%d\n", labelcounter);//result of < is stored in 1000
		return 1;
	} else if (opexp[1] == '=') {
		*lispfileindex -= strlen(opexp);
		*lispfileindex +=2;//333333333333
		utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
		as1_write_equalthan(lispfilecontents, lispfileindex);
		//fprintf(fp, (char *)"bne if%d\n", labelcounter);//result of < is stored in 1000
		return 1;
	} else if (utility_isdigit(str) == 0) {	
		int n = atoi(str);
		//fprintf(fp, (char *)"sta $%d\n", 1000+j);
		i--;
	} else if (utility_isalpha(str) == 0) {	
		SymtabElt *se = NULL;//FIXME return it;
		get_symtabname(&str, &se);
		if (se == NULL) {
			fprintf(stdout, (char *)"_ lessthan _ undefined identifier : %s %s\n", str, str);
		} else if (se->type != INTEGER && se->type != FLOAT && se->type != FUNCARG && se->type != LOOPARG) {
			fprintf(stdout, (char *)"_ when _ wrong type argument : %s %s\n", opexp, opexp);	
			exit(99);
		} else {
			fprintf(fp, (char *)"lda $%d\n", se->address);
			fprintf(fp, (char *)"sta $%d\n", 1000+j);
		}		
	} else if (utility_islist(str) == 0) {
		as1_write_list(str,opexp);
	} 
	j++;
	i--;
	free(str);
	}


	fclose(fp);
	return 0;
}








int as1_write_setq(const char **lispfilecontents, int *lispfileindex)//char *name, char *opexp)
{
	FILE *fp;
	char *name;
	char *opexp;
	char *str;
	printf((char *)"writing setq...\n");

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg(lispfilecontents, lispfileindex, &name);
	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
//FIXME	tullariscgetarg_until_parens(lispfilecontents, lispfileindex, &opexp);
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);


	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
		exit(99);

	}


	//opexp[strlen(opexp)-1] = '\0';
		printf((char *)"OPEXP=%s\n", opexp);
	if (utility_isdigit(opexp) == 0) {
		SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
		add_symtabname(*name, &e);


		//getarg_until_parens(opexp, &str); //getintsolo(opexp);
		//int n = atoi(str); //getintsolo(opexp);
		//int n = getintsolo(opexp);
		int n = atoi(opexp);
		make_integer(&e, n); 
		fprintf(fp, (char *)"ldx #%d\n", n);
		fprintf(fp, (char *)"stx $%d\n", e->address);

	} else if (utility_isalpha(opexp) == 0) {//FIXME lists other than integer or alpha lookup
		SymtabElt *se;// = (SymtabElt *)malloc(sizeof(SymtabElt));
		SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
		add_symtabname(&name, &e);
		char *str2 = (char *)malloc(1024);
		getstringsolo(opexp, str2);
		get_symtabname(&str2, &se);
		fprintf(fp, (char *)"ldx $%d\n", se->address);
		fprintf(fp, (char *)"stx $%d\n", e->address);
		free(str2);	
	
	} else if (utility_islist(opexp)) {
		as1_write_list(name, opexp);
		//make_list(&e, n); 
		//fprintf(fp, (char *)"ldx #%d\n", n);
		//fprintf(fp, (char *)"stx $%d\n", e->address);
	} 
	fclose(fp);
	return 0;
}


/*
* Lists are stored at 4000
*/
int as1_write_list(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	int i = 0, j = 0;
	int tempmax = heapmax_global;
	char *opexp;

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing list...opexp=%s\n", opexp);	
	if ((fp = fopen((char *)"./code.s", (char *)"a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	/* jump out if there are no arguments */
	if (opexp == NULL)
		return 0;//NOTE return empty list ?

	/* put all arguments in str */	

	char *str = opexp;
	int len = 0;

	///FIXME2utility_skip_whitespace_newlines_parens(&opexp, strlen(opexp), &len); 

	for ( i = 1; i < strlen(opexp); i++) {//NOTE2 i = 1
		char *str2;
		getarg(&opexp, &i, &str2);	
		
		/*if the string is alphanumeric we need to look up the symbol */
	
		if (str2 != NULL && utility_isalpha(str2) == 0 && strlen(str2) > 0) {
			SymtabElt *se = NULL;
			get_symtabname(&str2, &se);
			if (se == NULL) {
				fprintf(stdout, (char *)"_ undefined indentifier : %s\n", str2);
			} else {
			}				
		} else if (utility_isdigit(str2) == 0 && strlen(str2) > 0) {//FIXME heapmax
			int n = atoi(str2);		
			fprintf(fp, (char *)"ldx #%d\n", n);
			fprintf(fp, (char *)"stx $%d\n", 4000+j);
			j++;///NOTE
		} else if (utility_islist(str2) == 0) {
			//FIXME2 as1_write_list(str2,opexp); 
		} else {
			fprintf(stdout, (char *)"_ unknown type : %s\n", str2);
		}	
		free(str2);	
	}


	SymtabElt *e = (SymtabElt *)malloc(sizeof(SymtabElt));
	e->address = tempmax; 
	e->pn = e->address;
	e->type = LIST;//NOTE nil types are not nil but are searched for at runtime for dynamic binding
	e->Integer = NIL;	
	e->Float = NIL;	
	e->Character = 0;	
	e->Null = NULL;	
	e->String = NULL;		
	e->List = (List *)malloc(sizeof(List));			
	e->List->length = tempmax - heapmax_global; 
	char *name = (char *)"list1";//FIXME2;
	add_symtabname_withaddress(&name, &e);

}

int as1_write_asm(const char **lispfilecontents, int *lispfileindex)
{
	FILE *fp;
	char *opexp;

	utility_skip_whitespace_newlines(lispfilecontents, strlen(*lispfilecontents), lispfileindex); 
	getarg_until_parens(lispfilecontents, lispfileindex, &opexp);//FIXME *
	printf((char *)"writing asm...opexp=%s\n", opexp);	
	if ((fp = fopen((char *)"./code.s", "a+")) < 0) {

		printf((char *)"neslisp error - Cannot open code output file\n");
		exit(99);

	}

	if (fseek(fp, 0, SEEK_END) < 0) {

		printf((char *)"neslisp error - Cannot seek in code output file\n");
	}

	/* jump out if there are no arguments */
	if (opexp == NULL)
		return 0;//NOTE return empty list ?

	/* put all arguments in str */	
	opexp[0] = '\n';
	fprintf(fp, (char *)"%s\n", opexp);
}


