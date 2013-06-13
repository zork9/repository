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


(load "matrix.scm")

(define (make-quaternion ww xx yy zz)
	(let ((x xx)
		(y yy)
		(z zz)
		(w ww))

	(define (get-w)
		w)
	(define (get-x)
		x)
	(define (get-y)
		y)
	(define (get-z)
		z)

	(define (get-conjugate)
		(make-quaternion w -x -y -z))	

	(define (mulitply q2)
		(let ((x2 ((q2 'x)))
			(y2 ((q2 'y)))
			(z2 ((q2 'z)))
			(w2 ((q2 'w))))

		(make-quaternion (- (- (- (* w w2) (* x x2)) (* y y2)) (* z z2))
				(- (+ (* w x2) (* x w2)(* y z2)) (* z y2))
				(+ (- (* w y2)(* x z2))(* y w2)(* z x2))
				(+ (- (+ (* w z2)(* x y2))(* y x2))(* z w2)))
			))
		))

	(define (sqr x)
		(* x x))

	(define (normalise)
		(sqrt (sqr w) (sqr x) (sqr y) (sqr z))) 

	(define (rotationmatrix)
		(make-matrix (+ (sqr x) (sqr y) (sqr z) (sqr w))
				(- (* 2 x y)(* 2 w z))  
				(+ (* 2 x z)(* 2 w y))
				(+ (* 2 x y)(* 2 w z))
				(+ (- (sqr w)(sqr x))(- (sqr y)(sqr z)))  
				(+ (* 2 y z)(* 2 w x))
				(- (* 2 x z)(* 2 w y))  
				(- (* 2 y z)(* 2 w x))  
				(+ (- (- (sqr w)(sqr x))(sqr y)) (sqr z)))) 

	(lambda (msg)
	(cond ((eq msg 'x)get-x)
		((eq msg 'w) get-w)
		((eq msg 'x) get-x)
		((eq msg 'y) get-y)
		((eq msg 'z) get-z)
		((eq msg 'conjugate) get-conjugate)
		((eq msg 'normalise) normalise)
		((eq msg 'get-rotationmatrix)rotationmatrix)	
		(else (display "make-quaternion : message not understood ")
			(display msg)(newline))))

))
