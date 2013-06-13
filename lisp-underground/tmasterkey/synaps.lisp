
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




(defun make-synaps (msg &optional n)
  (let ((*input-neurons ())
        (*output-neurons ())
        (*weight 0.3)
        (*theta 0.1)
        (*omega 0.5)
        (*sigmoidf #'(lambda (a) (/ 1 (+ ( exp a) 1))))
        (*learnrate 0.5))

    #'(lambda (msg2 neuron)
        (cond ((eq msg2 'add-input-neuron)
               (setq *input-neurons (append *input-neurons (list neuron))))
              ((eq msg2 'add-output-neuron)
               (setq *output-neurons (append *output-neurons (list neuron))))
              ((eq msg2 'get-weight)
               *weight)
              ((eq msg2 'init) #'(lambda (msg &optional n) make-synaps))

              ((eq msg2 'propagate)
               (let ((w *weight)
                     (activs ()))
                 (dolist (l *input-neurons)
                   (setq activs (append activs (l 'get-activation)))))
                 (setq w (+ w (* *learnrate ej (log (+ (exp a) 1)))))
                 ;;UNDER DEV - FIXME
                 ;;formula: w_ij = w_ij + r * e_j * A_j'(I_j) * O_i where r is the learning rate, e_j is the blame of neuron j, A_j' is the derivative of neuron j's activation function, I_j is the input fed to neuron j during calculation of the output in the first step, and O_i is the output of neuron i during the first step. The biases are similarly adjusted using the formula: bias_i = bias_i + r*e_i.
                 )

                  ((eq msg2 'transmit)
                   (let ((deltas ())
                         (deltas2 ())
                         (w 0))
                     (dolist (l *input-neurons) (setq deltas (append deltas (list (* (l 'get-activation) *weight)))))
                     (dolist ((l deltas)(is *input-neurons)) (setq deltas2 (append deltas2 (list (* (is 'get-activation) (- 1 (is 'get-activation) l))))))
                     (dolist ((l deltas2)(is *input-neurons)) (setq w (+ (* *omega (is 'get-activation) l)))
                             (setq *weight w))))

                  (T (print "Synaps : message not understood.")))
                 )))
