;; Available functions
;; ===================
;;
;; polygon*
;; -------
;; Returns a polygon object.
;; Syntax: (polygon* sides fill?)
;;     sides  uint  number of sides/vertices the polygon will have
;;     fill?  bool  when true the inner polygon area will be color filled
;; Examples:
;;    (polygon* 3 #t)
;;    (polygon* 4 #f)
;;
;; transformation*
;; ---------
;; Returns a transformation object.
;; Syntax: (transformation* #:name value)
;;     name   keyword  transformation name
;;     value  float    transformation value
;; Description:
;;     A transformation name can be any of:
;;         - :identity
;;         - :translate-x
;;         - :translate-y
;;         - :scale
;;         - :rotate
;;     You can use both the traditional scheme notation (#:key)
;;     or the short notation (:key).
;; Examples:
;;     (transformation :translate-x 1/2)
;;     (transformation #:translate-x 1/4)
;;
;; draw
;; ----
;; Syntax: (draw ...)
;; Examples:
;;     (draw
;;      (list (list (polygon* 3 #t)
;;                  (transformation* :identity 0))
;;            (list (polygon 4 #f)
;;                  (transformation :scale 1/4)
;;                  (transformation :rotate 1/3))))


;; Working examples
;; ================

(draw
 (list (list (polygon* 6 #f)
             (transformation* :scale 1/2)
             (transformation* :translate-x 1/2)
             (transformation* :scale 3/2))
       (list (polygon* 6 #t)
             (transformation* :scale 1/3)
             (transformation* :scale 1/12))))


;; Old examples using the old syntax.
;; ==================================

(define >~ transform)
(define &  list)
(define >+ combine)

(define (>* n . body)
  (define (aux n tr)
    (if (> n 1)
      '(tr
        (aux (1- n)
             tr))
      tr))
  (aux n (apply list body)))


(define move-x translate-x)
(define move-y translate-y)



(draw (list (list (polygon 6)
             (>* 3
                 (scale 1/2)
                 (move-x 1/2)
                 (rotate (nth 6)))
             (scale 3/2))

         (>~ (polygon 6 fill)

             (& (scale 1/3 1/12)

                (>+ (scale 1/9)
                    (move-y 1/9)
                    (move-y 1/3)
                    (rotate (nth 3)))

                (>+ (scale  1/6)
                    (move-y 1/3)
                    (rotate (nth 3))
                    (rotate 1/2)))

             (rotate 1/2))))
