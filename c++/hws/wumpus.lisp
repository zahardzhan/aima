(in-package "UCPOP")

(define (domain wumpus-world-domain)

  (:fact (geq ?x ?y)
    (cond ((or (variable:variable? ?x) (variable:variable? ?y))
           :no-match-attempted)
          ((and (numberp ?x) (numberp ?y) (>= ?x ?y))
           '(nil))
          (t nil))
    )

  (:fact (leq ?x ?y)
    (cond ((or (variable:variable? ?x) (variable:variable? ?y))
           :no-match-attempted)
          ((and (numberp ?x) (numberp ?y) (<= ?x ?y))
           '(nil))
          (t nil))
    )

  (:fact (increment ?x ?y)
    (cond ((and (variable:variable? ?x) (variable:variable? ?y))
           :no-match-attempted)
          ((and (variable:variable? ?x) (numberp ?y))
           (list (setb ?x (- ?y 1))))
          ((and (variable:variable? ?y) (numberp ?x))
           (list (setb ?y (+ ?x 1))))
          ((and (numberp ?x) (numberp ?y) (= ?y (+ ?x 1)))
           '(nil))
          (t nil))
    )

  (:operator TURNLEFT
    :parameters (?d1 ?d2)
    :precondition (and (agent-in-cave)
                       (agent-orientation ?d2)
                       (left-of ?d1 ?d2))
    :effect (and (not (agent-orientation ?d2))
                 (agent-orientation ?d1))
    )

  ;; TURNRIGHT

  ;; GOFORWARD

  ;; GRAB

  ;; SHOOT

  (:operator CLIMB
    :parameters ()
    :precondition (and (agent-in-cave)
                       (agent-location 1 1))
    :effect (not (agent-in-cave))
    )
  )

(define (problem world1)
  :domain 'wumpus-world-domain
  :inits (
          (left-of left up)    ;; basic facts
          (left-of down left)
          (left-of right down)
          (left-of up right)

          (agent-in-cave)      ;; agent initial state
          (agent-location 1 1)
          (agent-orientation right)
          (agent-arrows 1)
          (agent-gold 0)

          (extent 2)           ;; wumpus world
          (gold 2 2)
         )
  :goal (agent-gold 1)
  )
