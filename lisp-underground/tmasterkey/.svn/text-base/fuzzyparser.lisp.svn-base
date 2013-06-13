
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





(defun parse-for-typeX-rec (haystack i retstr previ delimiters)
  (cond ((>= i (length haystack))
         (list "" i));;end node of haystack
        (T (let* ((c (aref haystack i))
                  (r NIL)
                  (foo (mapcar #'(lambda (delimiter) (if (string= c delimiter) (setq r T))) delimiters)))
             (cond ((not (null r))
                    (do ((ii  (- i 1) (- ii 1)));;skip whitepspace
                        ((or (< ii previ)
                             (>= ii i))
                         (list (reverse retstr) i))
                      (setq retstr (concatenate 'string retstr (string (char haystack ii))))))
                   (T (parse-for-typeX-rec haystack (+ i 1) retstr previ delimiters)))))
        ))


(defun parse-for-typeX (haystack ii retl delimiters)
  (let* ((ret (parse-for-typeX-rec haystack ii "" ii delimiters))
         (retstr  (car ret))
         (reti (+ (cadr ret))))


    ;;(cond ((string= retstr "12345678") (print "FOO"))
    ;;	(T
    ;;		(when (= (+ reti 1) (length haystack))
    ;;		(print "FOO"))
    (cond ((< (+ reti 1) (length haystack))
           (parse-for-typeX haystack (+ reti 1) (append retl (list ret)) delimiters))
          (T
           retl))
    ))

(defun parse-for (haystack &optional delimitersl)
  (let ((haystack1 (concatenate 'string haystack '(#\space)))
        (delimiters (cond ((not (stringp delimitersl))
                           (list " " "\n"))
                          (T delimitersl))))
    (parse-for-typeX haystack1 0 () delimiters)
    ))
