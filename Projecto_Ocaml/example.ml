(*#load "graph.cma";;*)
open Graph.Pack.Digraph;;
let show = display_with_gv;;

let g = Rand.graph ~v:100 ~e:20 ()
let () = show g;;


(* representation of a node -- must be hashable
module Node = struct
   type t = int
   let compare = Pervasives.compare
   let hash = Hashtbl.hash
   let equal = (=)
end

(* representation of an edge -- must be comparable *)
module Edge = struct
   type t = string
   let compare = Pervasives.compare
   let equal = (=)
   let default = ""
end

(* a functional/persistent graph *)
module G = Graph.Persistent.Digraph.ConcreteBidirectionalLabeled(Node)(Edge)

(* more modules available, e.g. graph traversal with depth-first-search *)
module D = Graph.Traverse.Dfs(G)

(* module for creating dot-files *)
module Dot = Graph.Graphviz.Dot(struct
   include G (* use the graph module from above *)
   let edge_attributes (a, e, b) = [`Label e; `Color 4711]
   let default_edge_attributes _ = []
   let get_subgraph _ = None
   let vertex_attributes _ = [`Shape `Box]
   let vertex_name v = string_of_int v
   let default_vertex_attributes _ = []
  let graph_attributes _ = []
end)
*)
