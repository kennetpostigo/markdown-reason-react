open Types;

let parseHeading = line =>
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

let parseCode = line =>
  if (String.sub(line, 0, 3) == "```") {
    Code;
  } else {
    InlineCode;
  };

let getPeriodSubStr = str =>
  switch (Utils.strIdx("List", ((-1), (-1)), str, '.', false)) {
  | Some(i) =>
    switch (Utils.strSub("List", ((-1), (-1)), str, 0, i, false)) {
    | Some(sub) => sub
    | None => ""
    }
  | None => ""
  };

let parseList = line =>
  switch (String.sub(line, 0, 2)) {
  | "* "
  | "- "
  | "+ " => List(Unordered)
  | _ =>
    try (
      {
        let _x = int_of_string(String.trim(getPeriodSubStr(line)));
        List(Ordered);
      }
    ) {
    | Failure(_) => Paragraph
    }
  };

let parseLinkFootnote = line =>
  switch (String.sub(line, 1, 1)) {
  | "^" => Footnote
  | _ => Link
  };

let parseImage = line =>
  switch (String.sub(line, 0, 2)) {
  | "![" => Image
  | _ => Paragraph
  };

let parsePrimitives = line =>
  switch (String.sub(line, 0, 1)) {
  | "" => Break
  | ">" => Blockquote
  | "#" => parseHeading(line)
  | "`" => parseCode(line)
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
  | "+" => parseList(line)
  | "[" => parseLinkFootnote(line)
  | "!" => parseImage(line)
  /* | "***" => ThematicBreak */
  /* | "_" => Emphasis
     | "__" => Strong
     | "~~" => Delete */
  | exception (Invalid_argument(_e)) => Break
  | _ => Paragraph
  };

let getDirectoryFiles = directory => "TODO";
let iterDirectoryFiles = fn => "TODO";

let rec aggregate = (ls, chan, locS, locE, id, idHandler: 'a) =>
  switch (input_line(chan)) {
  | line =>
    let nextLocE = locE + 1;
    if (line == id) {
      (List.rev(ls), idHandler(nextLocE, nextLocE));
    } else {
      let next = [line, ...ls];
      aggregate(next, chan, locS, nextLocE, id, idHandler);
    };
  | exception End_of_file => (List.rev(ls), Ast.nodeOfNull(0, 0))
  };

let nextList = (ast, node, lastNode) =>
  switch (lastNode.element) {
  | Null => [node, ...ast]
  | _ => [lastNode, node, ...ast]
  };

let parseFileToAST = filename => {
  let chan = open_in(filename); /* open file */

  let rec parse = (chan, ast: ast, loc) =>
    try (
      {
        let locE = ast == [] && loc == 1 ? loc : loc + 1; /* increment line */
        let line = input_line(chan); /* read line from file */

        switch (parsePrimitives(line)) {
        | Paragraph =>
          let (content, lastNode) =
            aggregate([line], chan, locE, locE, "", Ast.nodeOfBreak);
          let node = Ast.nodeOfParagraph(content, "", locE, locE);
          parse(chan, nextList(ast, node, lastNode), lastNode.endLoc);
        | Blockquote =>
          let (content, lastNode) =
            aggregate([line], chan, locE, locE, "", Ast.nodeOfBreak);
          let node = Ast.nodeOfBlockquote(content, "", locE, locE);
          parse(chan, nextList(ast, node, lastNode), lastNode.endLoc);
        | Heading(int) =>
          let node = Ast.nodeOfHeading(line, int, locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | Code =>
          let (content, _) =
            aggregate([line], chan, locE, locE, "```", Ast.nodeOfNull);
          let node = Ast.nodeOfCode(content, "", locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | List(lt) =>
          /* let (content, lastNode) =
             aggregate(line, chan, locE, locE, "", Ast.nodeOfBreak); */
          let node = Ast.nodeOfLists(line, [], lt, locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | Link =>
          let node = Ast.nodeOfLink(line, locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | Image =>
          let node = Ast.nodeOfImage(line, locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | Footnote =>
          let node = Ast.nodeOfFootnote(line, locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        | Null => parse(chan, ast, locE + 1)
        | Emphasis
        | Strong
        | Delete
        | ThematicBreak
        | ListItem
        | InlineCode
        | Table
        | TableRow
        | TableCell
        | LinkReference
        | ImageReference
        | FootnoteReference
        | Definition
        | FootnoteDefinition
        | Break =>
          let node = Ast.nodeOfBreak(locE, locE);
          parse(chan, [node, ...ast], node.endLoc);
        };
      }
    ) {
    | End_of_file =>
      close_in(chan);
      List.rev(ast);
    };

  parse(chan, [], 1);
};