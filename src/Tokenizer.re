type typ =
  | Markdown
  | HTML
  | YAML;

type primitives =
  | Paragraph
  | Blockquote
  | Heading(int)
  | Code
  | InlineCode
  | List
  /*
   | ListItem
   | Table
   | TableRow
   | TableCell */
  | ThematicBreak
  | Break
  | Emphasis
  | Strong
  | Delete
  | Link
  | Image
  | Footnote; /* | LinkReference   | ImageReference   | FootnoteReference   | Definition   | FootnoteDefinition   | TextNode */

let stringToPrimitives = pattern =>
  switch (pattern) {
  | ">" => Blockquote
  | "#" => Heading(1)
  | "##" => Heading(2)
  | "###" => Heading(3)
  | "####" => Heading(4)
  | "#####" => Heading(5)
  | "######" => Heading(6)
  | "```" => Code
  | "`" => InlineCode
  | "1." => List
  | "*" => List
  | "-" => List
  | "+" => List
  | "***" => ThematicBreak
  | "\n" => Break
  | "_" => Emphasis
  | "__" => Strong
  | "~~" => Delete
  | "[" => Link
  | "![" => Image
  | "^[" => Footnote
  | _ => failwith("THIS CASE IS NOT HANDLED")
  };

type location = (int, int);

type element = {
  element: (typ, primitives),
  children: list(element),
  location,
};

let readFileLineByLine = (filename, fn) => {
  let chan = open_in(filename);
  try (
    while (true) {
      fn(input_line(chan));
    }
  ) {
  | End_of_file => close_in(chan)
  };
};