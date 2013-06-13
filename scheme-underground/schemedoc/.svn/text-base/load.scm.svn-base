
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

(load "schemedoc.scm")


(define ask (getenv "SCHEMEDOCDIR"))
(case ask
  ((#f) (begin (for-each
                display
                '("set your SCHEMEDOCDIR env var to the paths where pods and sods reside." (eoln) "exiting" (eoln)))
               (exit) ;; NOTE exit
               )))

(define SCHEMEDOCITEMS '())
(let ((directoriesl (schemedoc-get-env-list SCHEMEDOCDIR)))
  (do ((l directoriesl (cdr l)))
      ((null? l)
       0)
    (display (directory-files (car l)) )
    (do ((l2 (directory-files (car l)) (cdr l2)))
          ((null? l2)0)
      (set! SCHEMEDOCITEMS (append SCHEMEDOCITEMS (list (schemedoc-parser-grep (car l2)))))
      )))

(display "Your search is in the variable SCHEMEDOCITEMS list variable.")
(newline)
(display "You can regexp it if you want.")
(newline)

(define (schemedoc-search)
  (display "Do you want to search for something ? (type y/n)")
  (let ((s (read)))
    (newline)
    (cond ((and (symbol? s)(eq? s 'y))
           (display "What do you want to search for ?")
           (let ((s (read)))
             (newline)
             (let ((itemtexts (schemedoc-parser-get-items s SCHEMEDOCITEMS)))
               (display "Do you want me to print the items of your search ?")
               (let ((s (read)))
                 (newline)
                 (cond ((and (symbol? s)(eq? s 'y))
                        (display itemtexts))
                       (else (schemedoc-search)))))))
          (else (schemedoc-search)))))
(schemedoc-search)
