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

open Syntax
open Lib

let comment_out_head = "//"
;;

let make_header conf source filename content =
  make_source conf source filename content comment_out_head
;;

(* rename : e.g., "rename_without_underbar" -> "RenameWithoutUnderbar" *) 
let rename_without_underbar st = 
  let rec loop str b =
    match str with
    | "" -> ""
    | _ -> 
      let s = String.get str 0 in
      let str' = String.sub str 1 ((String.length str) - 1) in
      if s = '_' then (loop str' true)
      else if b then (String.capitalize (Char.escaped s)) ^ (loop str' false)
      else (Char.escaped s) ^ (loop str' false) in
  loop st true
;;

let gen_public_class name content =
  List.concat [
    [ (0, "public class " ^ (rename_without_underbar name) ^ " implements UserDefinedMessage {") ];
    indent_lines 1 content;
    [ (0, "};") ]
  ]
;;

let include_list t =
  type_exists (function 
  | List _ -> true
  | _ -> false) t
;;

let include_map t =
  type_exists (function 
  | Map _ -> true
  | _ -> false) t
;;

let include_datum t =
  type_exists (function
  | Datum -> true
  | _ -> false) t
;;

let gen_import_for_client ts =
  (if List.exists include_map ts then
      [ (0, "import java.util.Map;"); ]
   else [])
  @ (if List.exists include_list ts then
      [ (0, "import java.util.List;"); ]
    else [])
  @ (if List.exists include_datum ts then
      [ (0, "import us.jubat.common.Datum;") ]
    else [])
;;
let gen_import_for_message ts =
  (if List.exists include_map ts then
      [ (0, "import java.util.Map;");
        (0, "import java.util.HashMap;"); ]
   else [])
  @ (if List.exists include_list ts then
      [ (0, "import java.util.List;");
        (0, "import java.util.ArrayList;"); ]
    else [])
  @ (if List.exists include_datum ts then
      [ (0, "import us.jubat.common.Datum;") ]
    else [])
;;

let gen_args args = 
  "(" ^ String.concat ", " args ^ ")"
;;

let gen_call func args =
  (* TODO(unnonouno): format for long lines *)
  func ^ gen_args args
;;

let gen_template typ args =
  typ ^ "<" ^ String.concat ", " args ^ ">"
;;

let rec gen_type = function
  | Object -> raise (Unknown_type("Object is not supported"))
  | Bool -> "boolean"
  | Int(_, n) -> if n <= 4 then "int" else "long" 
  | Float(false) -> "float"
  | Float(true) -> "double"
  | Raw -> raise (Unknown_type("Raw is not supported"))
  | String -> "String"
  | Datum -> "Datum"
  | Struct s  ->
    rename_without_underbar s
  | List t ->
    gen_template "List" [gen_object_type t]
  | Map(key, value) -> 
    gen_template "Map" [gen_object_type key; gen_object_type value]
  | Nullable(t) -> gen_object_type t
and gen_object_type = function
  | Bool -> "Boolean"
  | Int(_, n) ->
    if n <= 4 then "Integer" else "Long"
  | Float(false) -> "Float"
  | Float(true) -> "Double"
  | t -> gen_type t
;;

let rec gen_type_class = function
  | Object -> Some "TObject.instance"
  | Bool
  | Int _
  | Float _ -> None
  | Raw -> Some "TRaw.instance"
  | String -> Some "TString.instance"
  | Datum -> Some "TDatum.instance"
  | Struct s ->
    let t = rename_without_underbar s in
    Some (gen_call ("new " ^ gen_template "TUserDef" [t]) [])
  | List t ->
    let tlist = gen_template "TList" [gen_object_type t] in
    Some (gen_call ("new " ^ tlist) [gen_object_type_class t])
  | Map(key, value) ->
    let tmap = gen_template "TMap" [gen_object_type key; gen_object_type value] in
    Some (gen_call ("new " ^ tmap) [gen_object_type_class key; gen_object_type_class value])
  | Nullable t ->
    let tnullable = gen_template "TNullable" [gen_object_type t] in
    Some (gen_call ("new " ^ tnullable) [gen_object_type_class t])
and gen_object_type_class = function
  | Bool -> "TBool.instance"
  | Int(_, n) -> if n <= 4 then "TInt.instance" else "TLong.instance"
  | Float false -> "TFloat.instance"
  | Float true -> "TDouble.instance"
  | _ as t ->
    match gen_type_class t with
    | Some t -> t
    | None -> ""
;;

let gen_default_value = function
  | Object -> "null"
  | Bool -> "false"
  | Int _ -> "0"
  | Float _ -> "0"
  | Raw -> "null"
  | String -> "\"\""
  | Datum -> "null"
  | Struct _ -> "null"
  | List t -> "new " ^ gen_template "ArrayList" [gen_object_type t] ^ "()"
  | Map(k, v) -> "new " ^ gen_template "HashMap" [gen_object_type k; gen_object_type v] ^ "()"
  | Nullable _ -> "null"
;;

let gen_package conf =
  if conf.Config.namespace == "" then
    []
  else
    [ (0, "package " ^ conf.Config.namespace ^ ";");
      (0, ""); ]
;;

let split_namespace conf =
  Str.split (Str.regexp "\\.") conf.Config.namespace
;;

let make_path conf filename =
  let package = split_namespace conf in
  File_util.concat_path (package @ [filename])
;;

let gen_ret_type = function
  | None -> "void"
  | Some typ -> gen_type typ
;;

let gen_arg_def f =
  gen_type f.field_type ^ " " ^ f.field_name
;;

let gen_string_literal s =
  "\"" ^ String.escaped s ^ "\""
;;

let gen_public ret_typ name args opt content =
  let ret = gen_ret_type ret_typ in
  let args = List.map gen_arg_def args in
  List.concat
    [
      [ (0, "public " ^ ret ^ " " ^ gen_call name args ^ opt ^ " {")];
      content;
      [ (0, "}") ]
    ]
;;

let gen_client_method m =
  let name = m.method_name in
  let args = m.method_arguments in
  let checks = ExtList.List.filter_map (fun f ->
    match gen_type_class f.field_type with
    | None -> None
    | Some t -> Some (1, gen_call (t ^ ".check") [f.field_name] ^ ";")) args in
  let vars = "this.name":: (List.map (fun f -> f.field_name) m.method_arguments) in
  let call = [
    match m.method_return_type with
    | None ->
      (1, gen_call ("iface."^ name) vars ^ ";");
    | Some ret ->
      (1, "return " ^ gen_call ("iface."^ name)  vars ^ ";");
  ] in
  gen_public m.method_return_type name args ""  (checks @ call)
;;

let gen_interface m = 
  let name = m.method_name in
  let args = List.map gen_arg_def m.method_arguments in
  let ret = gen_ret_type m.method_return_type in
  ret ^ " " ^ gen_call name ("String name"::args) ^ ";"
;;  

let gen_client s name =
  let constructor = [
    (0, "public " ^ name ^ "Client(String host, int port, String name, int timeout_sec) throws UnknownHostException {");
    (1,   "EventLoop loop = EventLoop.defaultEventLoop();"); 
    (1,   "this.client = new Client(host, port, loop);");
    (1,   "this.client.setRequestTimeout(timeout_sec);");
    (1,   "this.iface = this.client.proxy(RPCInterface.class);");
    (1,   "this.name = name;");
    (0, "}");
    (0, "")
  ] in
  let interfaces = 
    List.concat [
      [ (0, "public static interface RPCInterface {") ];
      List.map (fun i -> (1, gen_interface i)) s.service_methods;
      [ (0, "}"); ]
    ] in
  let methods = List.map gen_client_method s.service_methods in
  let content = concat_blocks methods in
  concat_blocks [
    [
      (0, "public class " ^ (rename_without_underbar s.service_name) ^ "Client {");
    ];
    indent_lines 1 constructor;
    indent_lines 1 interfaces;
    indent_lines 1 content;
    [
      (1,   "public Client get_client() {");
      (2,     "return client;");
      (1,   "}");
      (0, "");
      (1,   "private Client client;");
      (1,   "private RPCInterface iface;");
      (1,   "private String name;");
      (0, "};")
    ]
  ]
;;

let gen_message_field f =
  (0, "public " ^ gen_arg_def f ^ " = " ^ gen_default_value f.field_type ^ ";")
;;

let gen_to_string m =
  let add_fields = List.map (fun f ->
    let key = gen_string_literal f.field_name in
    gen_call "gen.add" [key; f.field_name] ^ ";"
  ) m.message_fields in
  let call_open = gen_call "gen.open" [gen_string_literal m.message_name] ^ ";" in
  List.concat [
    [ (0, "public String toString() {");
      (1,   "MessageStringGenerator gen = new MessageStringGenerator();");
      (1,   call_open);
    ];
    List.map (fun l -> (1, l)) add_fields;
    [ (1,   "gen.close();");
      (1,   "return gen.toString();");
      (0, "}"); ]
  ]
;;

let gen_message_check m =
  let calls = ExtList.List.filter_map (fun f ->
    match gen_type_class f.field_type with
    | None -> None
    | Some t ->
      Some (1, gen_call (t ^ ".check") [f.field_name] ^ ";")
  ) m.message_fields in

  List.concat [
    [ (0, "public void check() {"); ];
    calls;
    [ (0, "}"); ]
  ]
;;

let gen_message_constructor m =
  let s = rename_without_underbar m.message_name in
  let args = m.message_fields in
  let content = List.map (fun f ->
    (1, "this." ^ f.field_name ^ " = " ^ f.field_name ^ ";")
  ) args in

  let args = List.map gen_arg_def args in
  List.concat [
    [ (0, "public " ^ gen_call s args ^ " {")];
    content;
    [ (0, "}") ]
  ]
;;

let gen_message m conf source =
  let field_types = List.map (fun f -> f.field_type) m.message_fields in
  let class_name = rename_without_underbar m.message_name in
  let filename = class_name ^ ".java" in
  let path = make_path conf filename in
  let header =
    List.concat
      [gen_package conf;
       gen_import_for_message field_types;
       [
         (0, "import org.msgpack.annotation.Message;");
         (0, "import us.jubat.common.MessageStringGenerator;");
         (0, "import us.jubat.common.UserDefinedMessage;");
         (0, "import us.jubat.common.type.*;");
         (0, "");
       ]
      ] in
  let field_defs = List.map gen_message_field m.message_fields in
  let constructor = 
    [ (0, "public " ^ class_name ^ "() {");
      (0, "}"); ] in
  let to_string = gen_to_string m in
  let class_content = concat_blocks [
    field_defs;
    constructor;
    gen_message_constructor m;
    gen_message_check m;
    to_string;
  ] in
  let content =
    (0, "@Message") :: 
      gen_public_class class_name class_content
  in
  make_header conf source path (header @ content)
;;

let gen_typedef stat conf source =
  match stat with
  | Message m ->
    gen_message m conf source
  | _ ->
    ()
;;

let collect_types_of_method m =
  let arg_types = List.map (fun f -> f.field_type) m.method_arguments in
  match m.method_return_type with
  | None -> arg_types
  | Some(t) -> t::arg_types
;;

let collect_types_of_service s =
  List.concat (List.map collect_types_of_method s.service_methods)
;;

let gen_client_file conf source services =
  let base = File_util.take_base source in
  let filename = (rename_without_underbar base) ^ "Client.java" in
  let path = make_path conf filename in
  let clients = List.map (fun x -> gen_client x (rename_without_underbar base)) services  in
  let types = List.concat (List.map collect_types_of_service services) in
  let content = concat_blocks [
    gen_package conf;
    gen_import_for_client types;
    [
      (0, "import java.net.UnknownHostException;");
      (0, "import org.msgpack.rpc.Client;");
      (0, "import org.msgpack.rpc.loop.EventLoop;");
      (0, "import us.jubat.common.type.*;");
    ];
    (concat_blocks clients)
  ]
  in make_header conf source path content
;;

let gen_typedef_file conf source idl =
  List.iter (fun stat -> gen_typedef stat conf source) idl
;;

let generate conf source idl =
  let services = get_services idl in
  gen_typedef_file conf source idl;
  gen_client_file conf source services
;;
