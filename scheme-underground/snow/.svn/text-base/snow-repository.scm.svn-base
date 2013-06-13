
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

(define (parse-for s needle index)
  (let ((word "("))
    (do ((i index (+ i 1)))
        ((cond ((string=? needle word)
                ;;(set! index i))
                i)
               ((eq? (string-ref s i) #\space)
                (set! word ""))
               ((eq? (string-ref s i) #\newline)
                #t));;(string-set! s i ""

         (set! word (string-append word (string (string-ref s i))))))))

(define (read-in-file-contents filename)
  (let ((contents ""))
  (do ((s (read-char)(read-char)))
      ((eof-object? s)
       contents)
    (set! contents (append contents (string s))))))

(define (parse-for-url s index)
  (let ((word "")
        (index (+ index 1)))
    (if (eq? (string-ref s (- index 1))
             #\")
        (do ((i index (+ i 1)))
            ((eq? (string-ref s i) #\")
             (string-append s (string #\"))
             i)

          (set! word (string-append word (string (string-ref s i)))))
        (error "parse-for-url : malformed url string"))))

(define (snow-repository filename db)
  (let ((urlstr "")
        (db db)
        (contents (read-in-file-contents filename))
        (index4 0)
        (index3 0)
        (index2 0)
        (index 0))
    (set! index2 (parse-for contents "repository" index))
    (set! index3 (parse-for contents "package" index))
    (set! index4 (parse-for contents "url" index))
    (set! urlstr (parse-for-url contents index4))

    (set! db (append db (list (list "url" urlstr))))
    db))



