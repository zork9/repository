;; Copyright (C) Johan Ceuppens 2012
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

(load "quaternion.scm")

(define fruitloops 2000)
(define fruitw 2000)
(define fruitx 2000)
(define fruity 2000)
(define fruitz 2000)

(define (sqr x)
	(* x x))

(define v (make-vector3 x y z))

(define (norm1 w x y z)
	(sqr (sqr w)(sqr x)(sqr y)(sqr z))) 

;;test sample coords
(define *x 100)
(define *xn 1000)
(define *y 100)
(define *z 100)

(define (print-transformation q m)
	(let ((vn ((m 'mul) v)))
		(cond ((and (>= ((vn 'get-x)) *x)(<= ((vn 'get-x)) *xn))
			(display "hit")(display "x=")
					(display ((q 'get-x)))
					(display " y=")
					((q 'get-y))
					(display " z=")
					((q 'getz))
					(newline)))
	))
				
(do ((i 0 (+ i 1)))
	((i > fruitloops) (display "quitting...")(newline))
	(let ((q (make-quaternion (random fruitw)(random fruitx)(random fruity)(random fruitz))))
		(let ((m (q 'get-rotationmatrix)))
			(let ((n (norm1 ((q 'get-w))((q 'get-x))((q 'get-y))((q 'get-z)))))
				(set! q (make-quaternion (/ w n)
							(/ x n)
							(/ y n)
							(/ z n))) 
 
				(print-transformation q m)	
		)))
	)

	
