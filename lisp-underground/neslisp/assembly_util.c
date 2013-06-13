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
#include <math.h>


int utility_skip_whitespace_newlines_parens(const char **lispfilecontents, const int lispfilelength, int *index) 
{
	int j = 0;
	char c;
	for (j = 0; *index < lispfilelength && ((c = (*lispfilecontents)[(*index)]) == '\n' || c == ' ' || c == '('); j++) {
		(*index) ++;
	}
	return 1;
}

int utility_skip_whitespace_newlines(const char **lispfilecontents, const int lispfilelength, int *index) 
{
	int j = 0;
	char c;
	for (j = 0; *index < lispfilelength && (c = (*lispfilecontents)[(*index)]) == '\n' || c == ' '; j++) {
		(*index) ++;
	}
	return 1;
}

int comparealpha(char *needle, char *haystack)
{
	int i = 0;



	if (strlen(needle) <= strlen(haystack)) { 
	for (i = 0; i < strlen(needle); i++) {
		if ((haystack[i] >= 65 && haystack[i] <= 90) || (haystack[i] >= 97 && haystack[i] <= 122))
			if (haystack[i] == needle[i])
					continue;	
		else
			break;
	}
	} else {
	for (i = 0; i < strlen(haystack); i++) {
		if ((haystack[i] >= 65 && haystack[i] <= 90) || (haystack[i] >= 97 && haystack[i] <= 122))
			if (haystack[i] == needle[i])
					continue;	
		else
			break;

	}
	}
	return i;
}


int getnargs(char *str) 
{
	int i = 0, nargs = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == ' ') {
			if (str[i+1] == ' ') continue;
			nargs++;
			for (; i < strlen(str) && str[i] != ' ' && str[i] != '\n' && str[i] != '\0' && str[i] != ')' ; i++) 
				;		
		}
	}
	return nargs;
}

int getarg_until_parens(const char **str, int *len, char **retstr)
{
	int i = 0, j = 0;
	(*retstr) = (char *)malloc(strlen(*str));
	memset((*retstr),0,strlen(*str));
	for (j = 0, i = *len; i < strlen(*str); i++, j++) {
		if ((*str)[i] == ')')
			break;		
		else {
			(*retstr)[j] = (*str)[i];
		}
	}
	(*retstr)[j] = '\0';
	if ((*retstr) == (char *)0) retstr = NULL;	
	*len = i;	
	return 0;
}

int getarg(const char **str, int *len, char **retstr)
{
	int i = 0, j = 0;
	(*retstr) = (char *)malloc(strlen((*str)));
	memset((*retstr),0,strlen((*str)));
	for (j = 0, i = *len; i < strlen((*str)); i++, j++) {
		if ((*str)[i] == ' ' || (*str)[i] == ')')
			break;		
		else {
			(*retstr)[j] = (*str)[i];
		}
	}
	(*retstr)[j] = '\0';
	if ((*retstr) == (char *)0) retstr = NULL;	
	*len = i;	
	return 0;
}

/* string functions*/

int utility_islist(char *str)
{
	int i = 0, nlp = 0, nrp = 0;
	for (i = 0; i < strlen(str); i++) {
		if (str[i] == '(') nlp++;
		if (str[i] == ')') nrp++;
	}
	if (nlp > 1 )// nlp == nrp)
		return 1;
//	if ((nlp == nrp + 1 || nlp == nrp) && nlp > 0 && nrp > 0)//FIXME >= nrp
	//	return 1;
	else
		return -1; /* -1 if list is not closed and sublists are not closed */ 
}


int utility_isalpha(char *str)
{
	int i = 0;
	for (i = 0; i < strlen(str); i++)
		if (!isalpha(str[i])) break;
	if (i < strlen(str))
		return -1;
	else
		return 0;

}
int utility_isdigit(char *str)
{
	int i = 0;
	for (i = 0; i < strlen(str); i++)
		if (!isdigit(str[i])) break;
	if (i < strlen(str))
		return -1;
	else
		return 0;

}


/* symtab extracters */

int getint(char *str, int *len)
{

	int ret = 0;
	int i = 0, k = 0;
	int j = 0, l = 0, m = 0;
	for (j = *len; j >= 0 && (str[j] < 48 || str[j] >= 58); j--)
		;	
	for (i = j; i >= 0 && str[i] != ' ' && str[i] != ')'; i--)//NOTE ')' because of args of function 
		;	
	i++;		
	for (k = j, l = 0; k >= i ; k--, l++)
		if (l == 0) ret += (str[k]-48); else ret += (str[k]-48)*(int)(powf((float)10,(float)l));		
	*len = j-1;
	return ret; 
}

int getintsolo(char *str)
{
	int ret = 0, j = 0, i = 0, k = 0, l = 0;
	for (i = 0; i < strlen(str) && (str[i] < 48 || str[i] >= 58); i++) 
		;	
	for (j = strlen(str); j >= 0; j--) 
		;
	for (k = j, l = 0; k >= i; k--, l++)
		if (l == 0) ret += (str[k]-48); else ret += (str[k]-48)*(int)(powf((float)10,(float)l));		

	return 0; 
}


int getargstring(char *str, int *len, char **retstr)
{
	int flagi; 
	int ret = 0;
	int i = 0, k = 0;
	int j = 0, l = 0, m = 0;
	(*retstr) = (char *)malloc(strlen(str));
	memset((*retstr),0,strlen(str));
	for (j = *len, flagi = *len; j >= 0;  j--) {
		if (j == 0)
			break; 
		if (str[j] == ')')
			flagi = j; 

	}
	for (i = j; i >= 0 && str[i] != ' '; i--) 
		;	
	i++;		
	for (k = flagi, l = 0; k >= i ; k--, l++) {
		(*retstr)[l] = str[k];		
	}	
	*len = j-1;
	return 0; 
}

int getstring(char **str, int *len, char **retstr)
{

	int ret = 0;
	int i = 0, k = 0;
	int j = 0, l = 0, m = 0;
	(*retstr) = (char *)malloc(strlen(*str));
	memset((*retstr),0,strlen(*str));
	for (j = *len; j >= 0 && (((*str)[j] == ')' || (*str)[j] == ' ' || (*str)[j] == '(')); j--)
		;	
	for (i = j; i >= 0 && (*str)[i] != ' '; i--)
		;	
			
	i++;

	for (k = i, l = 0; k <= j && k < strlen(*str); k++, l++)
	{
		(*retstr)[l] = (*str)[k];
	}	
	*len = j-1;
	return 0; 
}

int getstringsolo(char *str, char *retstr)
{
	int ret = 0, j = 0, i = 0, k = 0, l = 0;
	for (i = 0; i < strlen(str) && ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == ' '); i++) 
		;	
	for (k = i, l = 0; k < strlen(str)-1; k++, l++)//NOTE the bracket at the end
		retstr[l] = str[k];

	return 0; 
}


