(*
 Jubatus: Online machine learning framework for distributed environment
 Copyright (C) 2013 Preferred Infrastructure and Nippon Telegraph and
 Telephone Corporation.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License version 2.1 as published by the Free Software Foundation.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*)

(* tsushima wrote *)

open Syntax
open Lib

let comment_out_head = "#"
;;

let make_header conf source filename content =
  make_source conf source filename content comment_out_head
;;

let gen_args args = 
  "(" ^ String.concat ", " args ^ ")"
;;

(* return : retval = self.client.call(names) *)
let gen_retval func args =
  let func_literal = "'" ^ func ^ "'" in
  "retval = self.client.call" ^ gen_args (func_literal::args)
;;

(* return : def func_name (self, args): *)
let gen_def func args =
  "def " ^ func ^ gen_args ("self"::args) ^ ":"
;;

let gen_string_literal s =
  "\"" ^ String.escaped s ^ "\""
;;

let gen_typename_with_bar name num = 
  if num = "" then name
  else name ^ "_" ^ num ^ "_"
;;

let gen_bool_literal = function
  | true -> "True"
  | false -> "False"
;;

let gen_string_literal s =
  "\"" ^ String.escaped s ^ "\""
;;

let gen_call func args =
  (* TODO(unnonouno): format for long lines *)
  func ^ gen_args args
;;

let rec gen_type = function
  | Object -> "TObject()"
  | Bool -> "TBool()"
  | Int(signed, bits) -> gen_call "TInt" [gen_bool_literal signed; string_of_int bits]
  | Float(_) -> "TFloat()"
  | Raw -> "TRaw()"
  | String -> "TString()"
  | Struct s  -> gen_call "TUserDef" [s]
  | List t -> gen_call "TList" [gen_type t]
  | Map(key, value) -> gen_call "TMap" [gen_type key; gen_type value]
  | Tuple ts -> gen_call "TTuple" (List.map gen_type ts)
  | Nullable(t) -> gen_call "TNulallable" [gen_type t]
;;

let gen_client_call func args =
  let args' = gen_string_literal func :: args in
  gen_call "self.client.call" args'
;;

let gen_client_method m =
  let name = m.method_name in
  let arg_vars = List.map (fun f -> f.field_name) m.method_arguments in
  let args = List.map (fun f ->
    let t = (gen_type f.field_type) ^ ".to_msgpack" in
    gen_call t [f.field_name]) m.method_arguments in 
  match m.method_return_type with
  | None ->
    [ (0, gen_def name arg_vars);
      (1,   gen_client_call name args);
    ]
  | Some typ ->
    let ret_type = gen_type typ in
    [ (0, gen_def name arg_vars);
      (1,   "retval = " ^ gen_client_call name args);
      (1,   "return " ^ ret_type ^ ".from_msgpack(retval)");
    ]
;;

let gen_client s =
  let methods = List.map gen_client_method s.service_methods in
  let constructor = [
    (0, "def __init__ (self, host, port):");
    (1,   "address = msgpackrpc.Address(host, port)");
    (1,   "self.client = msgpackrpc.Client(address)");
    (0, "");
    (0, "def get_client (self):");
    (1,   "return self.client")
  ] in
  let content = concat_blocks (constructor :: methods) in
    List.concat [
      [
        (0, "class " ^ s.service_name ^ ":");
      ];
    indent_lines 1 content
    ]
;;

let gen_self_without_comma field_names =
  (List.map (fun s -> (0, "self." ^ s ^ " = " ^ s)) field_names)
;;

let gen_to_msgpack field_names field_types =
  let types = List.map gen_type field_types in
  let tuple = gen_call "TTuple" types in
  let vars = List.map (fun v -> "self." ^ v) field_names in
  List.concat [
    [(0, "def to_msgpack (self):")];
    [(1,   "t = " ^ gen_call "" vars)];
    [(1,   "return " ^ gen_call (tuple ^ ".to_msgpack") ["t"])];
  ]
;;

let gen_str name field_names =
  List.concat [
    [
      (0, "def __str__(self):");
      (1,   "gen = jubatus.common.MessageStringGenerator()");
      (1,   gen_call "gen.open" [gen_string_literal name])
    ];
    List.map (fun f ->
      (1,   gen_call "gen.add" [gen_string_literal f; "self." ^ f])
    ) field_names;
    [
      (1,   "gen.close()");
      (1,   "return gen.to_string()")
    ]
  ]
;;

let mapi f lst =
  let rec mapi_impl f i = function
    | [] -> []
    | x::xs -> f i x :: mapi_impl f (i + 1) xs in
  mapi_impl f 0 lst
;;

let rec gen_from_msgpack_types field_types =
  mapi (fun i t -> gen_type t "arg" (string_of_int i)) field_types
;;

let gen_from_msgpack field_names field_types s =
  let types = List.map gen_type field_types in
  let tuple = gen_call "TTuple" types in
  [
    (0, "@staticmethod");
    (0, "def from_msgpack(arg):");
    (1,   "val = " ^ tuple ^ ".from_msgpack(arg)");
    (1,   "return " ^ gen_call s ["*val"]);
  ]
;;

let gen_message m =
  let field_names = List.map (fun f -> f.field_name) m.message_fields in
  let field_types = List.map (fun f -> f.field_type) m.message_fields in
  List.concat [
    [
      (0, "class " ^ m.message_name ^ ":");
      (1, gen_def "__init__" field_names);
    ];
    indent_lines 2 (gen_self_without_comma field_names);
    [(0, "")];
    indent_lines 1 (gen_to_msgpack field_names field_types);
    [(0, "")];
    indent_lines 1 (gen_from_msgpack field_names field_types m.message_name);
    [(0, "")];
    indent_lines 1 (gen_str m.message_name field_names)
  ]
;;

let gen_from_msgpack_for_typedef typ =
  let t = gen_type typ ^ ".from_msgpack" in
  [
    (0, "@staticmethod");
    (0, "def from_msgpack(arg):");
    (1,   "return " ^ gen_call t ["arg"]);
  ]
;;

let gen_typedef' name typ = 
  List.concat [
    [
      (0, "class " ^ name ^ ":");
    ];
    indent_lines 1 (gen_from_msgpack_for_typedef typ);
  ]
;;


let gen_typedef = function
  | Message m ->
    gen_message m
  | _ ->
    []
;;

let gen_client_file conf source services =
  let base = File_util.take_base source in
  let filename = Filename.concat base "client.py" in
  let clients = List.map gen_client services in
  let content = concat_blocks [
    [
      (0, "");
      (0, "import msgpackrpc");
      (0, "import jubatus.common");
      (0, "from types import *");
      (0, "from mpidl import *")
    ];
    (concat_blocks clients)
  ]
  in make_header conf source filename content
;;

let gen_type_file conf source idl =
  let base = File_util.take_base source in
  let name = Filename.concat base "types.py" in
  let types = List.map gen_typedef idl in
  let includes = [
    (0, "");
    (0, "import sys");
    (0, "import msgpack");
    (0, "import jubatus.common")
  ] in
  let content = concat_blocks [
    includes;
    (concat_blocks types)
  ] in
  make_header conf source name content
;;

let gen_init_file conf source =
  let base = File_util.take_base source in
  let name = Filename.concat base "__init__.py" in
  make_header conf source name []
;;

let generate conf source idl =
  let services = get_services idl in
  gen_client_file conf source services;
  gen_type_file conf source idl;
  gen_init_file conf source
;;
