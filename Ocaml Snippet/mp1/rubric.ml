(*
 * grader for mp1
 * This file will be preprocessed to generate the actual OCaml file.
 *)
let rubric_version = "1.4"
let rubric_title = "CS421 Fall 2007 MP1"

open Grader
open Test
open Mp1common

(*
 * use a timeout of 4 seconds
 *)
let outputOk () =
  let n = !last_string_length in
  if n < 0 then true else
  try (
  let len = String.length !output
  in let half1 = String.sub !output 0 (len - n)
  and half2 = String.sub !output (len - n) n
     in half1=half2
  ) with e -> false

(* let len = List.length !output
  in if (len mod 2) != 0 then false else
    let rec aux slist half1 half2 idx =
      if idx = (len / 2) then half1 = half2
      else match slist with
           | x::y -> aux y (half1@[x]) y (idx + 1)
    in aux !output [] [] 0
*)


let isEq i j =
    (i = j) &&
    (let res = outputOk() in output := ""; last_string_length := -1; res)

let mp1test weight pair = compare isEq 4 weight pair


(**************************************************************************
 * You can add new test cases by adding new elements to the following lists
 * Format is:
 * TEST<X>ARG(<weight>, <function_name>, <arg1>, <arg2>, ..., <argX>)
 *
 * <X> is the number of argument that the function being tested takes.
 **************************************************************************)

(* This list is for regular problems *)
let rubric =
[
     "random", mp1test 1 (ss_pair0 Solution.random Student.random) ;
     "pi", mp1test 1 (ss_pair0 Solution.pi Student.pi) ;
     "myFirstFun"^" "^"17", mp1test 1 (ss_pair1 Solution.myFirstFun Student.myFirstFun 17) ;
     "circumference"^" "^"1.0", mp1test 1 (ss_pair1 Solution.circumference Student.circumference 1.0) ;
     "double"^" "^"0", mp1test 1 (ss_pair1 Solution.double Student.double 0) ;
     "make_bigger"^" "^"12.0", mp1test 1 (ss_pair1 Solution.make_bigger Student.make_bigger 12.0)
]
(* Note: the last entry should not be followed by a semicolon. *)

(* This is the list for extra credit problems *)
let extra_rubric = [ ]

let _ = Main.main rubric extra_rubric rubric_title rubric_version
