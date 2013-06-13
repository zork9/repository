;;; CSAN-util.scm - Compehensive Scheme Archive Network utilities
;;;
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

(define (url-bite-off url)
  (let ((s "")
        (rets "")
        (j 0))
    (do ((i 0 (+ i 1)))
        ((or (string=? s "http://")(string=? s "ftp://")
             (string=? s " http://")(string=? s " ftp://"))
         (set! j i))
      (set! s (string-append s (string (string-ref url i))))
      )


    (do ((i j (+ i 1)))
        ((or (>= i (string-length url))
             (eq? (string-ref url i) #\/)
             (eq? (string-ref url i) #\\)) ;; needs scheme URL parsing (e.g. with regexps or other perl things
         rets)
      (set! rets (string-append rets (string (string-ref url i))))
      )))

;;test
;;(display (url-bite-off "http://soft/vub/"))

(define CSAN-generators (make-table))
(table-set! CSAN-generators "helpfile" (lambda ()
                                         (display "Type in your helpfile : commands are 'get <filename-on-server>' and 'h'")
                                         (let ((*out (open-outputfile (string-append "/help"))))
                                           (do ((s (read)(read)))
                                               ((eof-object? s)0)
                                             (write s)(write " ")))))

(define (CSAN-shell-spawn CSAN-dir mirror)
  (newline)
  (display "span> ")
  (do ((s (read)(read)))
      ((null? s)0)
    (newline)
    (display "span> ")
    (cond ((symbol? s)
           (cond ((string<=? (symbol->string s)(string #\return))
                  0)
                 ((string=? "h" (symbol->string s))
                  (display "Generating helpfile...")(newline)
                  (let ((*helpfilename (string-append CSAN-dir "/help")))
                    (let ((*in (if (file-exists? *helpfilename)
                                   (open-input-file *helpfilename)
                                   (begin
                                     (display "no helpfile...")
                                     ((CSAN-generate "helpfile"))))))
                      (for-each write (read *in))))
                  0)
                 ((string<=? "get" (symbol->string s))
                  (display "enter package to fetch : ")
                  (CSAN-ask-server (string-append "get " (symbol->string (read)))
                                   (url-bite-off mirror) 6969))
                 ))
          ))
  (display "span> signing off."))
