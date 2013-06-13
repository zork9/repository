;;Copyright (C) 2013 Johan Ceuppens
;;
;;;;This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
;;;
;;;;;This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
;;;
;;;;;You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA


(load "read.lisp")
(load "config.lisp")

;;(defvar input-mail-stream (open "test") "Mail File Contents")
;;

(defun post-mail-file-with-cat (file-contents)
	(print file-contents))

(defun post-mail-file (filename-args)
	(with-open-file (input-mail-stream (car filename-args) :direction :input :if-exists :supersede :if-does-not-exist :error)
  
  ;;(print (format "Your contents : %s" (string (read input-mail-stream))))
  ;;(do ((w (read input-mail-stream)))
  ;;  ((= 0 (length (string w))) t) 
  ;;  (print w)
  ;;  (setq w (read input-mail-stream))))

  
  ;;(do ((j 0 (+ j 1)))
  ;;  (nil)
  ;;  (let ((item (read input-mail-stream)))
  ;;    (if (typep end-of-file item) 
  ;;	(return)
  ;;	(print item))
  ;;    )))
  ;;

		  (block nil
			 (let ()
			   ;;(loop (when (typep end-of-file item) (return))
			   (loop for item = (read input-mail-stream nil nil)
				while item
				do 
				(print item)
				)))
  ))
