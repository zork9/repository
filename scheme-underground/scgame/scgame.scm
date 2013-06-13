
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

(load "scgameutil.scm")
(load "scgamedictionaries.scm")


(define (make-scdraw1) (lambda (msg) (aspecterror)(display "make-scdraw1")))
(define (make-scimage1) (lambda (msg) (aspecterror)(display "make-scimage1")))

(define (coolness? x) (not (null? x))) ;; coolness


(load "config.scm")
(define (display-msg . msg)
  (if SCGAMEDEBUG
      (for-each display (append (list (aspectmsg) " ") msg))
      (newline)))

(define (putpixel x y colorname)
 (let ((gc (create-gc dpy win
                      (make-gc-value-alist (background (string->color 'White)
                                                       (foreground (string->Color colorname)))))))
   (draw-point dpy win gc (inexact->exact x) (inexact->exact y))))

(define (putpixel x y foregroundcolorname backgroundcolorname)
  (let ((gc (create-gc dpy win
                       (make-gc-value-alist (background (string->color backgroundcolorname)
                                                        (foreground (string->Color foregroundcolorname)))))))
    (draw-point dpy win gc (inexact->exact x) (inexact->exact y))))


(define (make-scdraw2)
  (define (draw-line x0 y0 x1 y1 . w) ;; FIXME w == line width
    (let ((width (if (coolness? w)(if (number? (car w)) (car w) 1))))
      (display-msg "drawing line...")
      ;;This should be optimized Bresenham
      (let ((steep (> (abs (- y1 y0))
		      (abs (- x1 x0))))
	    (swap (lambda (x y)
		      (list y x)))
	    (range (lambda (x y)
		     (let ((l '()))
		       (cond ((< x y)
			      (do ((i x (+ i 1)))
				  ((= x y) l)
				(set! l (append l (list i)))))
			     ((< y x)
			      (do ((i y (+ i 1)))
				  ((= y x) l)
				(set! l (append l (list i)))))
			     (else (display-msg "range : x == y")
				   x)))))
	    )
	(if steep
	    (let ((t (swap x0 y0))
		  (x0 (car t))
		  (y0 (cadr t)))
	      (let ((deltax (- x1 x0))
		    (deltay (abs (- y1 y0))))
		(let ((error (/ delta 2))
		      (ystep 0)
		      (y y0))
		  (if (< y0 y1)
		      (+ ystep 1)
		      (- ystep 1)
		      (for-each (if steep
				    (putpixel y x 'Black)
				    (putpixel x y ))

				(set! error (- error deltay))
				(if (< error 0)
				    (set! y (+ y ystep))
				    (set! error (+ error deltax)))
				(range x0 x1))
		      ))))))))

    (define (draw-lines l1 . w)
      (display-msg "drawing lines...")
      (for-each draw-line l1)
      )

    (lambda (msg)
      (cond ((eq? msg 'draw-line)draw-line)
	    (else (aspecterror)(display "scdraw2"))))
    ))



(define (make-xpm-color-table)
  (let ((dict (make-dictionary)))
    (define (add! key color)
      (dictionary-add! dict key color))
    (define (set! key color)
      (dictionary-set! dict key color))
    (lambda (msg)
      (cond ((eq? msg 'add!) add!)
	    ((eq? msg 'set!) set!)
	    (else (dict msg))))
    ))

(define (make-scimage2)
  (let ((*db (make-dictionary)))

    ;; private methods
    (define (load-xpm-image-native filename)
      (xputxpm filename))

    (define (load-xpm-image-scx win filename)
      (read-file-to-pixmap win filename #()));;FIXME xpm-attributes == '()

    (define (load-xpm-image filename)
      (let ((in (open-input-file filename))
	    (colorcharsdictionary (make-color-dictionary 8)) ;;
	    (colorcharstable (make-xpm-color-table))
	    )
	(do ((str (read in) (read in)))
	    ((string<=? "{" str)#t))
	(do ((chr (read-char in) (read-char in)))
	    ((eq? #\" chr)#t))
	(let ((width (read in))
	      (height (read in))
	      (number-of-colors (read in))
	      )
	  (do ((chr (read-char in) (read-char in)))
	      ((eq? #\, chr)#t))
	  (do ((n1 number-of-colors (- n1 1)))
	      ((<= n1 0)#t)
	    (do ((chr (read-char in) (read-char in)))
		((eq? #\" chr)#t))
	    (let* ((colorchar (read-char in))
		   (colorcharnumber (string->number (string colorchar)))
		   )
	      ((colorchars 'add!) colorchar colorcharnumber)  ;; FIXME color 255 (extra map-dict)
	      ))
	  ;;FIX
	)))

    ;; public methods

    (define (load-image win filename)
      ;; FIXME read in xpm or png
      (display-msg "loading image..")
      (cond ((string<=? ".xpm" filename)
             (display-msg "loading xpm suffixed file..")
	     (load-xpm-image-scx win filename)
	     )
            (else (display-msg "no supported image format found"))))

    (lambda (msg)
      (cond ((eq? msg 'load-image) load-image)
	    (else (aspecterror)(display "scimage2"))))))


(define (make-scgame . tm)
  (cond ((not (null? tm)
	      (let ((*scdraw (make-scdraw1))
		    (*scimage (make-scimage1))
		    )

		(lambda (msg)
		  (cond ((do ((i 0 (+ i 1)))
			     ((substring? "draw-" msg i) (*scdraw msg))))
			((do ((i 0 (+ i 1)))
			     ((substring? "image-" msg i) (*scimage msg))))
			(else (aspecterror)(display "scgame1"))
			))))
	 )
	(else
	 (let ((*scdraw (make-scdraw2))
	       (*scimage (make-scimage2))
	       )

	   (lambda (msg)
	     (cond ((eq? msg 'draw-line) (*scdraw msg))
		   ((eq? msg 'draw-lines) (*scdraw msg))
		   (else (aspecterror)(display "scgame2"))))
	   ))))
