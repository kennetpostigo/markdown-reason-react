type listTypes =
  | Ordered
  | Unordered;

type primitives =
  | Heading(int)
  | Blockquote
  | Paragraph
  | TextNode
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

type element = {
  element: primitives,
  children,
  location,
}
and children =
  | Child(element)
  | Children(array(element))
  | String(string)
  | None;

type ast = array(element);

let primitivesToString = line =>
  switch (line) {
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
  | TextNode => "TextNode"
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

let stringToPrimitive = line =>
  switch (String.sub(line, 0, 1)) {
  | "" => Break
  | ">" => Blockquote
  | "#" => classifyHeading(line)
  | "`" => classifyCode(line)
  /* | "`" => InlineCode */
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
  /* | "***" => ThematicBreak */
  /* | "_" => Emphasis
     | "__" => Strong
     | "~~" => Delete
     | "[" => Link
     | "![" => Image
     | "^[" => Footnote */
  | exception (Invalid_argument(_e)) => Break
  | _ => Paragraph
  };

let getDirectoryFiles = directory => "TODO";

let iterDirectoryFiles = fn => "TODO";

let makeTextNode = (s, location) =>
  Child({element: TextNode, children: String(s), location});

let rec parseMultilineElements =
        (prmtv, chan, accumulatedStr, lineStart, lineEnd) => {
  let next = input_line(chan);
  if (next == (prmtv == Code ? "```" : "")) {
    (
      [|
        {
          element: prmtv,
          children: makeTextNode(accumulatedStr, (lineStart, lineEnd)),
          location: (lineStart, lineEnd),
        },
      |],
      lineEnd + 1,
    );
  } else {
    let nextStr = accumulatedStr ++ next;
    parseMultilineElements(prmtv, chan, nextStr, lineStart, lineEnd + 1);
  };
};

let rec parseLists = (chan, accumulatedList, listType, lineStart, lineEnd) => {
  let next = input_line(chan);
  if (next == "") {
    (
      [|
        {
          element: List(listType),
          children: Children(accumulatedList),
          location: (lineStart, lineEnd),
        },
      |],
      lineEnd + 1,
    );
  } else {
    let nextList =
      Array.append(
        accumulatedList,
        [|
          {
            element: ListItem,
            children:
              Child({
                element: TextNode,
                children: String(next),
                location: (lineEnd, lineEnd),
              }),
            location: (lineEnd, lineEnd),
          },
        |],
      );
    parseLists(chan, nextList, listType, lineStart, lineEnd + 1);
  };
};

let parseFileToAST = filename => {
  let ast: ref(ast) = ref([||]);
  let startLocation = ref(1);
  let chan = open_in(filename);

  try (
    while (true) {
      /* fn(input_line(chan), string_of_int(startLocation^)); */
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
        ast := Array.append(ast^, el);
        startLocation := finalLocation;
      | List(lt) =>
        let (el, finalLocation) =
          parseLists(chan, [||], lt, startLocation^, startLocation^);
        ast := Array.append(ast^, el);
        startLocation := finalLocation;
      | _ =>
        ast :=
          Array.append(
            ast^,
            [|
              {
                element: primitive,
                children:
                  makeTextNode(line, (startLocation^, startLocation^)),
                location: (startLocation^, startLocation^),
              },
            |],
          );
        startLocation := startLocation^ + 1;
      };
    }
  ) {
  | End_of_file => close_in(chan)
  };
  ast^;
};

let parseText = line => ();