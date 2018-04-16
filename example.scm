;; Available functions
;; ===================
;;
;; polygon
;; -------
;; Syntax: (polygon sides fill?)
;;     sides  uint  number of sides/vertices the polygon will have
;;     fill?  bool  when true the inner polygon area will be color filled
;; Examples:
;;    (polygon 3 #t)
;;    (polygon 4 #f)
;;
;; transform
;; ---------
;; Syntax: (transform polygon transformation)
;;     polygon         polygon         polygon object to be transformed
;;     transformation  transformation  transformation to apply
;; Description:
;;     A transformation can be any of:
;;         - translate-x
;;         - translate-y
;;     Each of them take exactly one float argument.
;; Examples:
;;     (transform (polygon 3 #t) (translate-x 1/4))
;;
;; draw
;; ----
;; Syntax: (draw object)
;;     poly  polygon  either a polygon or a transform
;; Examples:
;;     (draw (polygon 3 #t))
;;     (draw (transform (polygon 3 #t) (translate-x 1/4)))


;; Working examples
;; ================

(draw
 (polygon 5 #f))

(draw
 (polygon 6 #t))


;; Not currently working. Coming back soon.
;; ========================================

(define >~ transform)
(define &  list)
(define >+ combine)

(define (>* n . body)
  (define (aux n tr)
    (if (> n 1)
      (>+ tr
          (aux (1- n)
               tr))
      tr))
  (aux n (apply >+ body)))


(define move-x translate-x)
(define move-y translate-y)


(draw (& (>~ (polygon 6)
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
