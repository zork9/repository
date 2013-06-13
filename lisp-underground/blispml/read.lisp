;;Copyright (C) 2013 Johan Ceuppens
;;
;;;;This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.
;;;
;;;;;This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
;;;
;;;;;You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

(load "params.lisp")

(defclass Mail-File-Hex ()
  ((hex :accessor mail-file-hex
	  :initform "b0bb1e"
	  )
   ))

(defclass Mail-File (Mail-File-Hex)
  ((file :accessor mail-file
	  :initform ""
	  )
   ))

;; MailBox format not mbox
(defclass Mail (Mail-File)
  ((class :accessor mail
	  :initform ""
	  )
   ))

(defmethod isEmptyMail ((Mail mail)) (if (eq (mail mail-file) "")
				   *empty-mail-file*))


(defmacro xyzzy-mail (xyzzy mail)
  `(let ((,m (,mail mail))
	(let ((,mf (,m mail-file)))
	  (,xyzzy ,mf *current-mailing-list*)
	  ))))

(defmacro xyzzy-read-mail (xyzzy mail &optional ml)
  	`(let ((,ml (ml mailing-list))
	   (when (eq ,xyzzy 'send-to-all)
	     	(xyzzy-mail ,mail))
	   (when (eq xyzzy 'send-to)
	     	(xyzzy-mail ,mail ,ml)))
	))


