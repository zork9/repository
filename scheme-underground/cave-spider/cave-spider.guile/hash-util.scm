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

(define HASHTABLESIZE 1000000)

(define (make-hash-table n)
  (let ((*symtab (make-vector 1000000)))
    *symtab))

(define url-ascii-vector
  (vector #\A #\B #\C #\D #\E #\F #\G #\H #\I #\J #\K #\L
        #\M #\N #\O #\P #\R #\S #\T #\U #\V #\W #\X #\Y
        #\Z
        #\a #\b #\c #\d #\e #\f #\g #\h #\i #\j #\k #\l
        #\m #\n #\o #\p #\r #\s #\t #\u #\v #\w #\x #\y
        #\z
        #\0 #\1 #\2 #\3 #\4 #\5 #\6 #\7 #\8 #\9))

(define (hash-explode str)
  (let ((ret (make-vector (string-length str))))
    (do ((i 0 (+ i 1)))
        ((>= i (string-length str))
         #t)
      (vector-set! ret i (string-ref str i))
      )
    ret))

(define (hash-f key)
  (let ((keyexplosionvec (hash-explode key))
        (sum 0))
    (do ((i 0 (+ i 1)))
        ((>= i (vector-length keyexplosionvec))
         (display "Unknown/Known KEY char"))
      (do ((j 0 (+ j 1)))
          ((cond ((>= j (vector-length url-ascii-vector))
                  #t)
                 ((eq? (vector-ref keyexplosionvec i)
                       (vector-ref url-ascii-vector j))
                  (set! sum (+ sum j)));;FIXME *
                 ))
        ))
    sum))

(define (hash-ref table key)
  (vector-ref table (hash-f key)))

(define (hash-set! table key value)
  (vector-set! table (hash-f key) value))

;; test
;;(define ht (make-hash-table HASHTABLESIZE))
;;(hash-set! ht "abc" 22)
;;(display (hash-ref ht "abc"))
