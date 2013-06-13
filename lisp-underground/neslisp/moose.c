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
#include <string.h>

#include "symboltable.h"
#include "moose.h"

int moose_match()
{
	int i = 0;
	char *lispfilecontents;
	int lispfilelength = 0;
	char *configfilecontents;
	int configfilelength = 0;
	int configfileindex = 0;
	int lispfileindex = 0;
	char *dlfunction;
	char *lastfunctionname;


	make_stack(&stack_global); 

	moose_getfilelength(&lispfilelength, "./moose.lisp");
	moose_readfile(&lispfilecontents, lispfilelength, "./moose.lisp"); 

	moose_getfilelength(&configfilelength, "./moose.config");
	moose_readfile(&configfilecontents, configfilelength, "./moose.config"); 


	for ( ; lispfileindex < lispfilelength-1; ) {

		skip_whitespace_newlines(&lispfilecontents, lispfilelength, &lispfileindex); 
		char *str = NULL;
		if (moose_getstring(&lispfilecontents, lispfilelength, &str, &lispfileindex) < 0) {

			printf("+++ Finished parsing\n");	

		}

		if (configfileindex >= configfilelength) {
		//	configfileindex = 0;	
		}	
	
		for ( ;; ) {
			char *pattern = NULL, *patternstr = NULL;
			dlfunction = NULL;
			if (moose_getpattern(&configfilecontents, configfilelength, &pattern,&patternstr, &configfileindex, &dlfunction) < 0) {
				configfileindex = 0;
				break;
			}

	
			if (strncmp(str, patternstr, strlen(patternstr)) == 0 && strlen(patternstr) > 0 && strlen(pattern) > 0) { //FIXME strlen pattern can not be zero if we loop all the time through the patterns

				if (strlen(patternstr) < strlen(str) && strlen(str) > 0 && strlen(pattern) > 0 && strlen(patternstr) > 0) {

					lispfileindex = lispfileindex - (strlen(str) - strlen(patternstr));
				//	free(pattern);
				//	free(patternstr);
					//break; //FIXME free
	
				}
				stack_push(&stack_global, &patternstr, &str);
				//stack_print(&stack_global);
				//lispfileindex += strlen(patternstr);
				//lispfileindex += 1;
				configfileindex = 0;	
				printf("MATCH=%s dlfunction=%s\n", str, dlfunction);

				//if (dlfunction != NULL && strlen(dlfunction) > 0) {
					switch(atoi(pattern)){
					case 1:{
						stack_pop(&stack_global);
						break;
					}
					case 2:{
						printf("popped\n");
						char *retpatternstr = NULL;
						char *retnamestr = NULL;
						stack_pop(&stack_global);
						stack_pop_andreturn(&stack_global, &retpatternstr, &retnamestr);
						if (retpatternstr != NULL && strlen((char *)retpatternstr) > 0) {

							if (strncmp((char *)retpatternstr, LOOP, strlen(LOOP)) == 0) {

							printf("LOOP POP RETURN=%s\n", (char *)retpatternstr);
								as1_write_loopend();
							} else if (strncmp((char *)retpatternstr, WHEN, strlen(WHEN)) == 0) {
							printf("WHEN POP RETURN=%s\n", (char *)retpatternstr);
							stack_print(&stack_global);
							as1_write_whenend();	
							char *elsestr = (char *)malloc(1024);
							elsestr = strdup(WHENELSE);
							stack_push(&stack_global, &elsestr, &elsestr);
										
							} else if (strncmp((char *)retpatternstr, IF, strlen(IF)) == 0) {
							printf("IF POP RETURN=%s\n", (char *)retpatternstr);
							stack_print(&stack_global);	
							as1_write_iffirstclauseend(&lastfunctionname, atoi(retnamestr));	
							//FIXME1
							char *elsestr = (char *)malloc(1024);
							elsestr = strdup(IFELSE);
							char *elsestr2 = (char *)malloc(1024);
							sprintf(elsestr2, "%d\0", labelcounter); 
							stack_push(&stack_global, &elsestr, &elsestr2);
							} else if (strncmp((char *)retpatternstr, IFELSE, strlen(IFELSE)) == 0) {
							labelcounter++;
							printf("ELSE POP RETURN=%s\n", (char *)retpatternstr);
					
							as1_write_ifsecondclauseend(&lastfunctionname, atoi(retnamestr));	
							char *elsestr = (char *)malloc(1024);
							elsestr = strdup(IFTHIRD);
							stack_push(&stack_global, &elsestr, &elsestr);
							} else if (strncmp((char *)retpatternstr, WHENELSE, strlen(WHENELSE)) == 0) {
							printf("WHEN ELSE POP RETURN=%s\n", (char *)retpatternstr);
							as1_write_whenendsecond(&lastfunctionname);	
							} else if (strncmp((char *)retpatternstr, IFTHIRD, strlen(IFTHIRD)) == 0) {
							//labelcounter++;
							printf("IF THIRD POP RETURN=%s\n", (char *)retpatternstr);
							as1_write_ifclausethird(&lastfunctionname, atoi(retnamestr));	
							} else if (strncmp((char *)retpatternstr, DEFUN, strlen(DEFUN)) == 0) {
							printf("DEFUN POP RETURN=%s\n", (char *)retpatternstr);
							stack_print(&stack_global);
							as1_write_functionend(&lastfunctionname);	
							}			
						}
						break; 	
					}
					case 3:{
						as1_write_setq(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 4:{
						labelcounter++;	
						as1_write_functionheader(&lispfilecontents, &lispfileindex);
						//////stack_pop(&stack_global);
						break; 	
					}
					case 5:{
						as1_write_operator_plus(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 6:{
						labelcounter++;	
						as1_write_loop(&lispfilecontents, &lispfileindex);
						break; 	
					}
					case 7:{
						labelcounter++;	
						as1_write_when(&lispfilecontents, &lispfileindex);
						break; 	
					}
					case 8:{
						as1_write_lessthan(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 9:{
						as1_write_greaterthan(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 10:{
						as1_write_equalthan(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 11:{
						as1_write_operator_minus(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					case 12:{
						labelcounter++;	
						as1_write_if(&lispfilecontents, &lispfileindex);
						break; 	
					}
					case 13:{
						as1_write_list(&lispfilecontents, &lispfileindex);
						break; 	
					}
					case 14:{
						as1_write_asm(&lispfilecontents, &lispfileindex);
						stack_pop(&stack_global);
						break; 	
					}
					default:{
						break;
					}
					}

						


				//}	
				//if (pattern != NULL) free(pattern);
				//if (patternstr != NULL) free(patternstr);
				break;
	
			} else {
				SymtabElt *e = NULL;
				if (get_symtabname(&str, &e) && e != NULL && e->type == FUNC) {
					lastfunctionname = str;	
					as1_write_functionjump(str, &lispfilecontents, &lispfileindex);
					break;	
				}
			}
			//free(pattern);
			//free(patternstr);
		}
		//free(str);	
	}
}

int skip_whitespace_newlines(const char **lispfilecontents, const int lispfilelength, int *index) 
{
	int j = 0;
	char c;
	for (j = 0; *index < lispfilelength && (c = (*lispfilecontents)[(*index)]) == '\n' || c == ' '; j++) {
		(*index) ++;
	}
	return 1;
}


int moose_getfilelength(int *length, const char *filename)
{
	int i = 0;
	char c;
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL)
		return -1;

	for (i = 0; (c = getc(fp)) != EOF; i++ ) 
		;

	(*length) = i;	
	fclose(fp);	
	return 1;
}

int moose_readfile(char **filecontents, const int lispfilelength, const char *filename)
{

	int i = 0;
	char c = '\0';
	FILE *fp;

	if ((fp = fopen(filename, "r")) == NULL)
		return -1;

	(*filecontents) = (char *)malloc(lispfilelength);

	for (i = 0; (c = getc(fp)) != EOF; i++ ) 
		(*filecontents)[i] = (char)c;
	 
	fclose(fp);
	return 1;
}


int moose_getstring(const char **lispfilecontents, const int lispfilelength, char **retstr, int *index)
{

	int i = 0, j = 0;
	char c;
	(*retstr) = (char *)malloc(BUFSIZE);
	memset(*retstr, 0 ,BUFSIZE);
	for (i = 0; i < lispfilelength && (c = (*lispfilecontents)[(*index)]) != ' ' && c != '\n'; i++) {
		(*retstr)[i] = (char)c;
		/*if ((*lispfilecontents)[*index]	== '(') {
			(*index)++;
			return 1;//moose_getstring(lispfilecontents, lispfilelength, retstr, index);
		}	
		*/
		(*index)++;
	
	} 
	return 1;

}

int moose_getpattern(const char **configfilecontents, const int configfilelength, char **pattern, char **patternstr, int *index, char **dlfunction)
{
	*pattern = (char *)malloc(BUFSIZE); //FIXME BUFSIZE
	*patternstr = (char *)malloc(BUFSIZE);
	memset(*pattern, 0 ,BUFSIZE);
	memset(*patternstr, 0 ,BUFSIZE);
	int i = 0, j = 0, k = 0;
	char c;
	(*dlfunction) = NULL;	
	for (i = *index, j = 0; i < configfilelength && (c = (*configfilecontents)[i]) != ' '; i++, j++) //PARSE only 2 in a PATTERN, let the write_ functions do the rest
		(*pattern)[j] = (char)c;

	*index += j;
	
	for (; i < configfilelength && (*configfilecontents)[i] == ' '; i++) {
		
	}
	//i++;	
	for (j = 0; i < configfilelength && (c = (*configfilecontents)[i]) != ' ' && c != '\n'; i++, j++) { 
		(*patternstr)[j] = (char)c;
	}
	*index += j;
	for (j = 0; i < configfilelength && (c = (*configfilecontents)[i]) == '\n' || c == ' '; i++, j++) {
		
	}
	*index += j;

	if (i < configfilelength && (*configfilecontents)[i-1] == '\n' ) {
		*index += 1;//NOTE default newline
		return 1;	
	}	
	
	*dlfunction = (char *)malloc(BUFSIZE);
	memset(*dlfunction, 0 ,BUFSIZE);
	for (j = 0; i < configfilelength && (c = (*configfilecontents)[i]) != ' ' && c != '\n'; i++, j++) {

		(*dlfunction)[j] = (char)c;

	}
	(*dlfunction)[j] = '\0';


	*index += j;

	for (j = 0; i < configfilelength && (c = (*configfilecontents)[i] == '\n' || c != ' '); i++, j++)
		;

	*index += j;
	*index += 1;//NOTE default newline

	return 1;
}

//#if 0 


int main()
{

	moose_match();


	return 0;

}	
