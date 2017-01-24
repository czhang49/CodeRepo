(* CS 421 Fall 2015 MP2 *)

(* Problem 1 *)
let rec even_count l = match l with
[]-> 0 | (x::xs) -> if ((x mod 2)=0) then 1+ even_count xs else 0+even_count xs;;

(* Problem 2 *)
let rec split f lst = match lst with
[] -> ([],[]) | (x::xs) -> match split f xs with (yesarray,noarray) -> if (f x) then (x::yesarray,noarray) else (yesarray,x::noarray);;

(* Problem 3 *)
let rec rle lst = match lst with
[] -> [] | (x::xs) -> match rle xs with [] -> (x,1)::[] | (head::tail) ->
                      match head with (key,value) -> if (x=key) then (key,value+1)::tail
                      else (x,1)::head::tail;;

(* Problem 4 *)
let rec sub_list l1 l2 =
    match l1 with [] -> if (l2=[]) then true else false | (f1x::f1xs) ->
    match l2 with [] -> true | (f2x::f2xs) ->
    if (f1x=f2x) then sub_list f1xs f2xs
    else sub_list f1xs l2 ;;


(* Problem 5 *)
let concat s list = match list with [] -> "" | (firstx::firstxs) ->
                    let rec concat_aux lst acc =
                   match lst with [] -> acc | (x::xs) ->
                   concat_aux xs (acc^s^x)
                   in concat_aux firstxs firstx;;


(* Problem 6 *)
let split_base = ([],[]);;
let split_step f first (yes, no) =  if (f first) then  (first::yes,no) else (yes, first::no);;

(* Problem 7 *)
let helper lst pairs = match pairs with [] -> (lst,1)::[] |
                       x::xs -> match x with (key,value) ->
                       if (lst=key) then (key,value+1)::xs else
                       (lst,1)::pairs;;
let rle2 lst =  List.fold_right (fun x-> fun n-> helper x n) lst [];;

(* Problem 8 *)
let helper acc y s = acc^"*"^y ;;
let concat2 s list = match list with []-> "" | x::xs ->
                    List.fold_left (fun acc -> fun y -> helper acc y s) x xs;;


(* Problem 9 *)
let helper fs y = List.map (fun x-> x y) fs ;;
let app_all fs list =  List.map (fun x-> helper fs x) list;;

(* Extra Credit, Problem *)
let sub_list2 l1 l2 =  match List.fold_left (fun acc-> fun y-> match acc with []->[] | (x::xs)
                      ->  if (x=y) then xs else acc ) l2 l1 with []-> true | _ -> false;;
