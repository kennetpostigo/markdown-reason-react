open Types;

let rec nodeOfLink = (line, locS, locE) => {
  let titleStart = Utils.stringIndex("Link", (locS, locE), line, '[', true);
  let titleEnd =
    Utils.stringIndexFrom("Link", (locS, locE), line, titleStart, ']', true);
  let title =
    Utils.stringSub(
      "Link",
      (locS, locE),
      line,
      titleStart + 1,
      titleEnd - titleStart - 1,
      true,
    );

  let linkStart =
    Utils.stringIndexFrom(
      "Link",
      (locS, locE),
      line,
      titleEnd + 1,
      '(',
      true,
    );
  let linkEnd =
    Utils.stringIndexFrom("Link", (locS, locE), line, linkStart, ')', true);
  let link =
    Utils.stringSub(
      "Link",
      (locS, locE),
      line,
      linkStart + 1,
      linkEnd - linkStart - 1,
      true,
    );

  {
    element: Link,
    children: [],
    textContent: Some(title ++ " " ++ link),
    location: (locS, locE),
  };
};

let nodeOfImage = (line, locS, locE) => {
  let altStart = Utils.stringIndex("Image", (locS, locE), line, '[', true);
  let altEnd =
    Utils.stringIndexFrom("Image", (locS, locE), line, altStart, ']', true);
  let alt =
    Utils.stringSub(
      "Image",
      (locS, locE),
      line,
      altStart + 1,
      altEnd - altStart - 1,
      true,
    );

  let linkStart =
    Utils.stringIndexFrom(
      "Image",
      (locS, locE),
      line,
      altEnd + 1,
      '(',
      true,
    );
  let linkEnd =
    Utils.stringIndexFrom("Image", (locS, locE), line, linkStart, ')', true);
  let link =
    Utils.stringSub(
      "Image",
      (locS, locE),
      line,
      linkStart + 1,
      linkEnd - linkStart - 1,
      true,
    );

  {
    element: Image,
    children: [],
    textContent: Some(alt ++ " " ++ link),
    location: (locS, locE),
  };
};

let rec nodeOfFootnote = (line, locS, locE) => {
  let txtStart =
    Utils.stringIndex("Footnote", (locS, locE), line, '^', true);
  let txtEnd =
    Utils.stringIndexFrom(
      "Footnote",
      (locS, locE),
      line,
      txtStart,
      ']',
      true,
    );
  let txt =
    Utils.stringSub(
      "Footnote",
      (locS, locE),
      line,
      txtStart + 1,
      txtEnd - txtStart - 1,
      true,
    );

  {
    element: Footnote,
    children: [],
    textContent: Some(txt),
    location: (locS, locE),
  };
};

let rec nodeOfBlockquote = (chan, str, lineS, lineE) => {
  let next =
    switch (input_line(chan)) {
    | s => s
    | exception End_of_file => "$$$EndOFFile$$$"
    };

  if (next == "$$$EndOFFile$$$") {
    {
      element: Blockquote,
      children: [],
      textContent: Some(str),
      location: (lineS, lineE),
    };
  } else {
    let nextEnd = str == "" && lineE == 1 ? 1 : lineE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ next;
    nodeOfBlockquote(chan, nextStr, lineS, nextEnd);
  };
};

let rec nodeOfParagraph = (chan, str, lineS, lineE) => {
  let next =
    switch (input_line(chan)) {
    | s => s
    | exception End_of_file => "$$$EndOFFile$$$"
    };

  if (next == "$$$EndOFFile$$$") {
    {
      element: Paragraph,
      children: [],
      textContent: Some(str),
      location: (lineS, lineE),
    };
  } else {
    let nextEnd = str == "" && lineE == 1 ? 1 : lineE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ next;
    nodeOfParagraph(chan, nextStr, lineS, nextEnd);
  };
};

let rec nodeOfCode = (chan, str, lineS, lineE) => {
  let next =
    switch (input_line(chan)) {
    | s => s
    | exception End_of_file => "$$$EndOFFile$$$"
    };

  if (next == "$$$EndOFFile$$$") {
    {
      element: Code,
      children: [],
      textContent: Some(str),
      location: (lineS, lineE),
    };
  } else {
    let nextEnd = str == "" && lineE == 1 ? 1 : lineE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ next;
    nodeOfCode(chan, nextStr, lineS, nextEnd);
  };
};

let getListType = line =>
  switch (String.sub(String.trim(line), 0, 2)) {
  | "* "
  | "- "
  | "+ " => Unordered
  | _ => Ordered
  };

/*
  How to create AST for potentially infinitely nested lists
   1. If indent is equal then add the element as a ListItem into the accumulatedList
   2. If indent is greater recurse creating a new List with it's children inside, then add that       list as an element to the accumulatedList.
   3. If indent is lesser
 */
let rec nodeOfLists = (start, chan, list, listType, lineS, lineE) => {
  print_string("next: " ++ start ++ "\n");
  if (start == "") {
    print_string("HIT next == empty\n");
    {
      element: List(listType),
      children: List.rev(list),
      textContent: None,
      location: (lineS, lineE - 1),
    };
  } else {
    print_string("HIT else\n");
    let nextList = [
      {
        element: ListItem,
        children: [],
        textContent: Some(start),
        location: (lineE, lineE),
      },
      ...list,
    ];

    let line = input_line(chan);
    nodeOfLists(line, chan, nextList, listType, lineS, lineE + 1);
  };
};

let rec nodeOfMultilineElements = (prmtv, chan, str, lineS, lineE) => {
  let next = input_line(chan);
  if (next == (prmtv == Code ? "```" : "")) {
    {
      element: prmtv,
      children: [],
      textContent: Some(str),
      location: (lineS, lineE),
    };
  } else {
    let nextStr = str ++ "\n" ++ next;
    nodeOfMultilineElements(prmtv, chan, nextStr, lineS, lineE + 1);
  };
};

let rec astToString = (str, ast: ast, depth) =>
  if (str == "[\n" && ast == []) {
    "[]";
  } else {
    switch (ast) {
    | [] => depth > 2 ? str ++ Utils.addSpace(depth - 2) ++ "]" : str ++ "]\n"
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
  Utils.addSpace(depth)
  ++ "{\n"
  ++ Utils.addSpace(depth + 2)
  ++ "element: "
  ++ Utils.primitiveToString(element)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "children: "
  ++ astToString("[\n", children, depth + 4)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "textContent: "
  ++ Utils.hasTextContent(textContent)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "location: ("
  ++ string_of_int(sloc)
  ++ ", "
  ++ string_of_int(eloc)
  ++ ")"
  ++ "\n"
  ++ Utils.addSpace(depth)
  ++ "}";