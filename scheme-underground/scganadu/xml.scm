
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

(define (xml-load-tree! filename)
  (let ((in (open-input-file filename))
        (contents ""))

    (define (tagify! c tagged)
      (cond ((> tagged 0) "")
            ((= tagged 0) (if (eq? c #\>) "" (string c)))
            ;; FIXME make node, descend one level
            (else "")))

    (define (xml-read-in-file contents)
      (let ((tagged 0))
        (do ((c (read-char in) (read-char in)))
            ((eof-object? c) contents)
          (cond ((and (= tagged 0)(eq? c #\<))
                 (set! tagged (+ tagged 1)))
                ((and (> tagged 0)(eq? c #\<))
                 (set! tagged (+ tagged 1)))
                ((and (= tagged 0)(eq? c #\>))
                 (set! tagged (- tagged 1)))
                ((and (> tagged 0)(eq? c #\>))
                 (set! tagged (- tagged 1)))
                ((< tagged 0)
                 (display "xml : bad xml file - broken tags.")(newline)
                 (set! tagged 0))
                )
          (set! contents (string-append contents (tagify! c tagged))))))
    (xml-read-in-file contents)))

