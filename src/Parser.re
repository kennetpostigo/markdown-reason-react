exception MalformedMarkdown(string);

type listTypes =
  | Ordered
  | Unordered;

type primitives =
  | Heading(int)
  | Blockquote
  | Paragraph
  | Break
  | Emphasis
  | Strong
  | Delete
  | List(listTypes)
  | ListItem
  | Code
  | InlineCode
  | Table
  | TableRow
  | TableCell
  | ThematicBreak
  | Link
  | Image
  | Footnote
  | LinkReference
  | ImageReference
  | FootnoteReference
  | Definition
  | FootnoteDefinition;

type location = (int, int);
type ast = list(element)
and element = {
  element: primitives,
  children: ast,
  textContent: option(string),
  location,
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

let classifyHeading = line =>
  if (String.sub(line, 0, 2) == "# ") {
    Heading(1);
  } else if (String.sub(line, 0, 3) == "## ") {
    Heading(2);
  } else if (String.sub(line, 0, 4) == "### ") {
    Heading(3);
  } else if (String.sub(line, 0, 5) == "#### ") {
    Heading(4);
  } else if (String.sub(line, 0, 6) == "##### ") {
    Heading(5);
  } else {
    Heading(6);
  };

let classifyCode = line =>
  if (String.sub(line, 0, 3) == "```") {
    Code;
  } else {
    InlineCode;
  };

let classifyList = line =>
  switch (String.sub(line, 0, 2)) {
  | "* "
  | "- "
  | "+ " => List(Unordered)
  | _ =>
    try (
      {
        let _x = int_of_string(String.sub(line, 0, 1));
        if (String.sub(line, 1, 1) == ".") {
          List(Ordered);
        } else {
          Paragraph;
        };
      }
    ) {
    | Failure(_) => Paragraph
    }
  };

let classifyLinkFootnote = line =>
  switch (String.sub(line, 1, 1)) {
  | "^" => Footnote
  | _ => Link
  };

let stringToPrimitive = line =>
  switch (String.sub(line, 0, 1)) {
  | "" => Break
  | ">" => Blockquote
  | "#" => classifyHeading(line)
  | "`" => classifyCode(line)
  | "1"
  | "2"
  | "3"
  | "4"
  | "5"
  | "6"
  | "7"
  | "8"
  | "9"
  | "*"
  | "-"
  | "+" => classifyList(line)
  | "[" => classifyLinkFootnote(line)
  | "!" => Image
  /* | "***" => ThematicBreak */
  /* | "_" => Emphasis
     | "__" => Strong
     | "~~" => Delete */
  | exception (Invalid_argument(_e)) => Break
  | _ => Paragraph
  };

let getDirectoryFiles = directory => "TODO";
let iterDirectoryFiles = fn => "TODO";

let rec parseMultilineElements =
        (prmtv, chan, accumulatedStr, lineStart, lineEnd) => {
  let next = input_line(chan);
  if (next == (prmtv == Code ? "```" : "")) {
    (
      {
        element: prmtv,
        children: [],
        textContent: Some(accumulatedStr),
        location: (lineStart, lineEnd),
      },
      lineEnd + 1,
    );
  } else {
    let nextStr = accumulatedStr ++ "\n" ++ next;
    parseMultilineElements(prmtv, chan, nextStr, lineStart, lineEnd + 1);
  };
};

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

let parseImage = (line, locS, locE) => {
  let altStart = stringIndex("Image", (locS, locE), line, '[', true);
  let altEnd =
    stringIndexFrom("Image", (locS, locE), line, altStart, ']', true);
  let alt =
    stringSub(
      "Image",
      (locS, locE),
      line,
      altStart + 1,
      altEnd - altStart - 1,
      true,
    );

  let linkStart =
    stringIndexFrom("Image", (locS, locE), line, altEnd + 1, '(', true);
  let linkEnd =
    stringIndexFrom("Image", (locS, locE), line, linkStart, ')', true);
  let link =
    stringSub(
      "Image",
      (locS, locE),
      line,
      linkStart + 1,
      linkEnd - linkStart - 1,
      true,
    );

  (
    {
      element: Image,
      children: [],
      textContent: Some(alt ++ " " ++ link),
      location: (locS, locE),
    },
    locE,
  );
};

let rec parseLink = (line, locS, locE) => {
  let titleStart = stringIndex("Link", (locS, locE), line, '[', true);
  let titleEnd =
    stringIndexFrom("Link", (locS, locE), line, titleStart, ']', true);
  let title =
    stringSub(
      "Link",
      (locS, locE),
      line,
      titleStart + 1,
      titleEnd - titleStart - 1,
      true,
    );

  let linkStart =
    stringIndexFrom("Link", (locS, locE), line, titleEnd + 1, '(', true);
  let linkEnd =
    stringIndexFrom("Link", (locS, locE), line, linkStart, ')', true);
  let link =
    stringSub(
      "Link",
      (locS, locE),
      line,
      linkStart + 1,
      linkEnd - linkStart - 1,
      true,
    );

  (
    {
      element: Link,
      children: [],
      textContent: Some(title ++ " " ++ link),
      location: (locS, locE),
    },
    locE,
  );
};

let rec parseFootnote = (line, locS, locE) => {
  let txtStart = stringIndex("Footnote", (locS, locE), line, '^', true);
  let txtEnd =
    stringIndexFrom("Footnote", (locS, locE), line, txtStart, ']', true);
  let txt =
    stringSub(
      "Footnote",
      (locS, locE),
      line,
      txtStart + 1,
      txtEnd - txtStart - 1,
      true,
    );
  (
    {
      element: Footnote,
      children: [],
      textContent: Some(txt),
      location: (locS, locE),
    },
    locE,
  );
};

let rec parseLists =
        (start, chan, accumulatedList, listType, lineStart, lineEnd) => {
  let next = start != "$$$" ? start : input_line(chan);
  if (next == "") {
    (
      {
        element: List(listType),
        children: List.rev(accumulatedList),
        textContent: None,
        location: (lineStart, lineEnd),
      },
      lineEnd + 1,
    );
  } else {
    let nextList = [
      {
        element: ListItem,
        children: [],
        textContent: Some(next),
        location: (lineEnd, lineEnd),
      },
      ...accumulatedList,
    ];
    parseLists("$$$", chan, nextList, listType, lineStart, lineEnd + 1);
  };
};

let parseFileToAST = filename => {
  let ast: ref(ast) = ref([]);
  let startLocation = ref(1);
  let chan = open_in(filename);

  try (
    while (true) {
      let line = input_line(chan);
      let primitive = stringToPrimitive(line);

      switch (primitive) {
      | Paragraph
      | Blockquote
      | Code =>
        let (el, finalLocation) =
          parseMultilineElements(
            primitive,
            chan,
            line,
            startLocation^,
            startLocation^,
          );
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Link =>
        let (el, finalLocation) =
          parseLink(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Image =>
        let (el, finalLocation) =
          parseImage(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | Footnote =>
        let (el, finalLocation) =
          parseFootnote(line, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | List(lt) =>
        let (el, finalLocation) =
          parseLists(line, chan, [], lt, startLocation^, startLocation^);
        ast := [el, ...ast^];
        startLocation := finalLocation + 1;
      | _ =>
        ast :=
          [
            {
              element: primitive,
              children: [],
              textContent: Some(line),
              location: (startLocation^, startLocation^),
            },
            ...ast^,
          ];
        startLocation := startLocation^ + 1;
      };
    }
  ) {
  | End_of_file => close_in(chan)
  };
  List.rev(ast^);
};

let hasTextContent = tc =>
  switch (tc) {
  | Some(s) => s
  | None => "None"
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

let rec astToString = (str, ast: ast, depth) =>
  if (str == "[\n" && ast == []) {
    "[]";
  } else {
    switch (ast) {
    | [] => depth > 2 ? str ++ addSpace(depth - 2) ++ "]" : str ++ "]\n"
    | [hd] =>
      if (str == "[\n") {
        let (sloc, eloc) = hd.location;
        let el =
          renderNode(hd.element, hd.children, hd.textContent, sloc, eloc, 2)
          ++ "\n";
        let next = str ++ el;
        astToString(next, [], depth);
      } else {
        let (sloc, eloc) = hd.location;
        let el =
          "\n"
          ++ renderNode(
               hd.element,
               hd.children,
               hd.textContent,
               sloc,
               eloc,
               depth,
             )
          ++ "\n";
        let next = str ++ el;
        astToString(next, [], depth);
      }
    | [hd, ...tl] =>
      if (str == "[\n") {
        let (sloc, eloc) = hd.location;
        let el =
          renderNode(
            hd.element,
            hd.children,
            hd.textContent,
            sloc,
            eloc,
            depth,
          )
          ++ ",\n";
        let next = str ++ el;
        astToString(next, tl, depth);
      } else {
        let (sloc, eloc) = hd.location;
        let el =
          "\n"
          ++ renderNode(
               hd.element,
               hd.children,
               hd.textContent,
               sloc,
               eloc,
               depth,
             )
          ++ ",\n";
        let next = str ++ el;
        astToString(next, tl, depth);
      }
    };
  }
and renderNode = (element, children, textContent, sloc, eloc, depth) =>
  addSpace(depth)
  ++ "{\n"
  ++ addSpace(depth + 2)
  ++ "element: "
  ++ primitiveToString(element)
  ++ ",\n"
  ++ addSpace(depth + 2)
  ++ "children: "
  ++ astToString("[\n", children, depth + 4)
  ++ ",\n"
  ++ addSpace(depth + 2)
  ++ "textContent: "
  ++ hasTextContent(textContent)
  ++ ",\n"
  ++ addSpace(depth + 2)
  ++ "location: ("
  ++ string_of_int(sloc)
  ++ ", "
  ++ string_of_int(eloc)
  ++ ")"
  ++ "\n"
  ++ addSpace(depth)
  ++ "}";