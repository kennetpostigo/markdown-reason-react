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

let rec nodeOfLists =
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
    nodeOfLists("$$$", chan, nextList, listType, lineStart, lineEnd + 1);
  };
};

let rec nodeOfMultilineElements =
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
    nodeOfMultilineElements(prmtv, chan, nextStr, lineStart, lineEnd + 1);
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