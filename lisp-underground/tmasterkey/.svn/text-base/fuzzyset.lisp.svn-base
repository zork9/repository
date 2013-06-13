
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







(defun make-fuzzy-set (&optional msgl)
  (let ((*name (when (not (null msgl)) (car msgl)))
        (*set-types ()) ;; e.g "low medium high"
        (*set-values ())) ;; e.g. probability, bayes

    #'(lambda (msgl)
        (cond ((eq (car msgl) 'init) (print "init fuzzy set : ")(print (cadr msgl))(setq *name (cadr msgl)))
              ((eq (car msgl) 'add-rule-type)
               (setq *set-types (append *set-types (list (cadr msgl))))

               )
              ((eq (car msgl) 'add-rule-value)
               (setq *set-values (append *set-values (list (cadr msgl))))

               )
              (T (print "Fuzzy Set : message not understood : ")(print msgl))))
    ))

(defun make-rule (&optional msgl)
  (let ((*typeX "")
        (*type2 ""))

    #'(lambda (msgl)
        (cond ((eq (car msgl) 'init)(setq *typeX (parse-for-typeX (cadr msgl)))(setq *type2 (parse-for-type2 (cadr msgl)))
               )
              (t (print "Rule : message not understood : ")(print msgl))))
    ))

(defun make-fuzzy-rule-set (&optional msgl)
  (let ((*fuzzy-set (make-fuzzy-set (when (not (null msgl)) (car msgl)))))

    #'(lambda (msgl)
        (cond ((eq (car msgl) 'init)(funcall *fuzzy-set (list 'init (cadr msgl))))
              ((eq (car msgl) 'add-rule-variables)
               (funcall *fuzzy-set (list 'add-rule-type (cadr msgl)))
               (funcall *fuzzy-set (list 'add-rule-value (caddr msgl))))
              (t (print "Fuzzy Rule Set : message not understood")(print msgl))))
    ))


(defun make-fuzzy-rule-system (&optional msgl)
  (let ((*fuzzy-sets ()))
    #'(lambda (msgl)
        (cond ((eq (car msgl) 'init) (print "init fuzzy rule system");;(setq *fuzzy-set (append *fuzzy-sets (list (make-fuzzy-set))))
               )
              ((eq (car msgl) 'add-fuzzy-set) (setq *fuzzy-sets (append *fuzzy-sets (list (cadr msgl)))))
              (t (print "Fuzzy Rule System : message not understood"))))
    ))


