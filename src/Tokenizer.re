type listTypes =
  | Ordered
  | Unordered;

type primitives =
  | Paragraph
  | Blockquote
  | Heading(int)
  | Code
  | InlineCode
  | List(listTypes)
  | ListItem
  | Table
  | TableRow
  | TableCell
  | ThematicBreak
  | Break
  | Emphasis
  | Strong
  | Delete
  | Link
  | Image
  | Footnote
  | LinkReference
  | ImageReference
  | FootnoteReference
  | Definition
  | FootnoteDefinition;

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

let stringToPrimitives = line =>
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

type location = (int, int);

type element = {
  element: primitives,
  children: list(element),
  location,
};

let getDirectoryFiles = directory => "TODO";

let iterDirectoryFiles = fn => "TODO";

let readFileLineByLine = (filename, fn) => {
  let line = ref(1);
  let chan = open_in(filename);
  try (
    while (true) {
      fn(input_line(chan), string_of_int(line^));
      line := line^ + 1;
    }
  ) {
  | End_of_file => close_in(chan)
  };
};

let parseText = line => ();