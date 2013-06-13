#!/usr/bin/clisp

;;Copyright (C) 2013 Johan Ceuppens

;;This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

;;This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

;;You should have received a copy of the GNU General Public License along with this program; if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA

;; Documenation :
;;
;; You can cat a file to this program through a pipe ('cat mail-file | ./blispml-cat-exe.lisp')
;;


(load "./blispml.lisp")

(defvar current-mail-file-contents "" "Current mail file contents")
(defvar in *standard-input*)
(loop for line = (read-line in nil nil :eof)
	while line
	do 
	(setq current-mail-file-contents (concatenate 'string current-mail-file-contents line))
	(print line)
	)

(post-mail-file-with-cat current-mail-file-contents)
