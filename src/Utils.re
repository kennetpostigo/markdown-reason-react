open Types;

exception MalformedMarkdown(string);

let rec getIndent = (count, str) =>
  switch (str) {
  | "" => count
  | " " => getIndent(count + 1, "")
  | _ =>
    switch (String.index(str, ' ')) {
    | i =>
      i != 0 ?
        getIndent(count, "") :
        getIndent(count + 1, String.sub(str, 1, String.length(str) - 1))
    | exception Not_found => getIndent(count, "")
    }
  };

let primitiveToString = t =>
  switch (t) {
  | Paragraph => "Paragraph"
  | Blockquote => "Blockquote"
  | Heading(int) => "Heading(" ++ string_of_int(int) ++ ")"
  | Code => "Code"
  | InlineCode => "InlineCode"
  | List(Ordered) => "List(Ordered)"
  | List(Unordered) => "List(Unordered)"
  | ListItem => "ListItem"
  | Table => "Table"
  | TableRow => "TableRow"
  | TableCell => "TableCell"
  | ThematicBreak => "ThematicBreak"
  | Break => "Break"
  | Emphasis => "Emphasis"
  | Strong => "Strong"
  | Delete => "Delete"
  | Link => "Link"
  | Image => "Image"
  | Footnote => "Footnote"
  | LinkReference => "LinkReference"
  | ImageReference => "ImageReference"
  | FootnoteReference => "FootnoteReference"
  | Definition => "Definition"
  | FootnoteDefinition => "FootnoteDefinition"
  };

/* TODO: convert to option */
let stringIndex = (prmtv, (sl, el), str, ch, fail) =>
  switch (String.index(str, ch)) {
  | i => i
  | exception Not_found =>
    fail ?
      raise(
        MalformedMarkdown(
          "The "
          ++ prmtv
          ++ " at ("
          ++ string_of_int(sl)
          ++ ", "
          ++ string_of_int(el)
          ++ ") "
          ++ "is malformed.",
        ),
      ) :
      (-1)
  | exception (Invalid_argument(c)) =>
    fail ?
      failwith(
        "MarkdownReasonReact.Parser.safeStringindex: This is a bug, please report it.",
      ) :
      (-1)
  };

/* TODO: convert to option */
let stringIndexFrom = (prmtv, (sl, el), str, index, ch, fail) =>
  switch (String.index_from(str, index, ch)) {
  | i => i
  | exception Not_found =>
    fail ?
      raise(
        MalformedMarkdown(
          "The "
          ++ prmtv
          ++ " at ("
          ++ string_of_int(sl)
          ++ ", "
          ++ string_of_int(el)
          ++ ") "
          ++ "is malformed.",
        ),
      ) :
      (-1)
  | exception (Invalid_argument(c)) =>
    fail ?
      failwith(
        "MarkdownReasonReact.Parser.safeStringindexFrom: This is a bug, please report it.",
      ) :
      (-1)
  };

/* TODO: convert to option */
let stringSub = (prmtv, (sl, el), str, ss, se, fail) =>
  switch (String.sub(str, ss, se)) {
  | i => i
  | exception (Invalid_argument(c)) =>
    fail ?
      failwith(
        "MarkdownReasonReact.Parser.safeStringSub: This is a bug, please report it.",
      ) :
      "$$$NotFound$$$"
  };

let addSpace = depth => {
  let x = ref(0);
  let spaces = ref("");
  while (x^ < depth) {
    spaces := spaces^ ++ " ";
    x := x^ + 1;
  };
  spaces^;
};

let hasTextContent = tc =>
  switch (tc) {
  | Some(s) => s
  | None => "None"
  };

let nodeToString = (element: element) => {
  let (locS, locE) = element.location;
  addSpace(0)
  ++ "{\n"
  ++ addSpace(2)
  ++ "element: "
  ++ primitiveToString(element.element)
  ++ ",\n"
  ++ addSpace(2)
  ++ "children: []"
  ++ ",\n"
  ++ addSpace(0 + 2)
  ++ "textContent: "
  ++ hasTextContent(element.textContent)
  ++ ",\n"
  ++ addSpace(2)
  ++ "location: ("
  ++ string_of_int(locS)
  ++ ", "
  ++ string_of_int(locE)
  ++ ")"
  ++ "\n"
  ++ addSpace(0)
  ++ "}";
};

let codegenToString = (file, page) =>
  Lexing.from_string(page)
  |> Reason_toolchain.RE.implementation_with_comments
  |> Reason_toolchain.RE.print_implementation_with_comments(
       Format.str_formatter,
     )
  |> Format.flush_str_formatter;