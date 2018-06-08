open Types;

let nodeOfHeading = (line, level, locS, locE) => {
  element: Heading(level),
  startLoc: locS,
  endLoc: locE,
  nestRule: [],
  children: [],
  textContent: None,
};

let nodeOfLink = (line, locS, locE) => {
  let prtv = "Link";
  let tEnd = ref(0);

  let title =
    switch (Utils.strIdx(prtv, (locS, locE), line, '[', true)) {
    | Some(tS) =>
      switch (Utils.strIdxFrom(prtv, (locS, locE), line, tS, ']', true)) {
      | Some(tE) =>
        switch (
          Utils.strSub(prtv, (locS, locE), line, tS + 1, tE - tS - 1, true)
        ) {
        | Some(sub) =>
          tEnd := tE;
          sub;
        | None => ""
        }
      | None => ""
      }
    | None => ""
    };

  let link =
    switch (Utils.strIdxFrom(prtv, (locS, locE), line, tEnd^ + 1, '(', true)) {
    | Some(lS) =>
      switch (Utils.strIdxFrom(prtv, (locS, locE), line, lS, ')', true)) {
      | Some(lE) =>
        switch (
          Utils.strSub(prtv, (locS, locE), line, lS + 1, lE - lS - 1, true)
        ) {
        | Some(sub) => sub
        | None => ""
        }
      | None => ""
      }
    | None => ""
    };

  {
    element: Link,
    startLoc: locS,
    endLoc: locE,
    nestRule: [],
    children: [],
    textContent: Some(title ++ " " ++ link),
  };
};

let nodeOfImage = (line, locS, locE) => {
  let prtv = "Image";
  let aEnd = ref(0);

  let alt =
    switch (Utils.strIdx(prtv, (locS, locE), line, '[', true)) {
    | Some(aS) =>
      switch (Utils.strIdxFrom(prtv, (locS, locE), line, aS, ']', true)) {
      | Some(aE) =>
        switch (
          Utils.strSub(prtv, (locS, locE), line, aS + 1, aE - aS - 1, true)
        ) {
        | Some(sub) =>
          aEnd := aE;
          sub;
        | None => ""
        }
      | None => ""
      }
    | None => ""
    };

  let link =
    switch (Utils.strIdxFrom(prtv, (locS, locE), line, aEnd^ + 1, '(', true)) {
    | Some(lS) =>
      switch (Utils.strIdxFrom(prtv, (locS, locE), line, lS, ')', true)) {
      | Some(lE) =>
        switch (
          Utils.strSub(prtv, (locS, locE), line, lS + 1, lE - lS - 1, true)
        ) {
        | Some(sub) => sub
        | None => ""
        }
      | None => ""
      }
    | None => ""
    };

  {
    element: Image,
    startLoc: locS,
    endLoc: locE,
    nestRule: [],
    children: [],
    textContent: Some(alt ++ " " ++ link),
  };
};

let nodeOfFootnote = (line, locS, locE) => {
  let prtv = "Footnote";

  let txt =
    switch (Utils.strIdx(prtv, (locS, locE), line, '^', true)) {
    | Some(tS) =>
      switch (Utils.strIdxFrom(prtv, (locS, locE), line, tS, ']', true)) {
      | Some(tE) =>
        switch (
          Utils.strSub(prtv, (locS, locE), line, tS + 1, tE - tS - 1, true)
        ) {
        | Some(sub) => sub
        | None => ""
        }
      | None => ""
      }
    | None => ""
    };

  {
    element: Footnote,
    startLoc: locS,
    endLoc: locE,
    nestRule: [],
    children: [],
    textContent: Some(txt),
  };
};

let nodeOfBreak = (locS, locE) => {
  element: Break,
  startLoc: locS,
  endLoc: locE,
  nestRule: [],
  children: [],
  textContent: None,
};

let rec nodeOfParagraph = (lines, str, locS, locE) =>
  switch (lines) {
  | [] => {
      element: Paragraph,
      startLoc: locS,
      endLoc: locE,
      nestRule: [],
      children: [],
      textContent: Some(str),
    }
  | [hd] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfParagraph([], nextStr, locS, nextEnd);
  | [hd, ...tl] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfParagraph(tl, nextStr, locS, nextEnd);
  };

let rec nodeOfBlockquote = (lines, str, locS, locE) =>
  switch (lines) {
  | [] => {
      element: Blockquote,
      startLoc: locS,
      endLoc: locE,
      nestRule: [],
      children: [],
      textContent: Some(str),
    }
  | [hd] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfBlockquote([], nextStr, locS, nextEnd);
  | [hd, ...tl] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfBlockquote(tl, nextStr, locS, nextEnd);
  };

let rec nodeOfCode = (lines, str, locS, locE) =>
  switch (lines) {
  | [] => {
      element: Code,
      startLoc: locS,
      endLoc: locE,
      nestRule: [],
      children: [],
      textContent: Some(str),
    }
  | [hd] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfCode([], nextStr, locS, nextEnd);
  | [hd, ...tl] =>
    let nextEnd = str == "" && locS == locE ? locE : locE + 1;
    let nextStr = str ++ (str == "" ? "" : "\n") ++ hd;
    nodeOfCode(tl, nextStr, locS, nextEnd);
  };

let getListType = line =>
  switch (String.sub(String.trim(line), 0, 2)) {
  | "* "
  | "- "
  | "+ " => Unordered
  | _ => Ordered
  };

let rec nodeOfLists = (line, list, listType, locS, locE) =>
  if (line == "") {
    {
      element: List(listType),
      startLoc: locS,
      endLoc: locE,
      nestRule: [],
      children: List.rev(list),
      textContent: None,
    };
  } else {
    let nextList = [
      {
        element: ListItem,
        startLoc: locS,
        endLoc: locE,
        nestRule: [],
        children: [],
        textContent: Some(line),
      },
      ...list,
    ];

    nodeOfLists(line, nextList, listType, locS, locE + 1);
  };

let rec astToString = (str, ast: ast, depth) =>
  if (str == "[\n" && ast == []) {
    "[]";
  } else {
    switch (ast) {
    | [] => depth > 2 ? str ++ Utils.addSpace(depth - 2) ++ "]" : str ++ "]\n"
    | [hd] =>
      if (str == "[\n") {
        let el =
          renderNode(
            hd.element,
            hd.startLoc,
            hd.endLoc,
            hd.nestRule,
            hd.children,
            hd.textContent,
            2,
          )
          ++ "\n";
        let next = str ++ el;
        astToString(next, [], depth);
      } else {
        let el =
          "\n"
          ++ renderNode(
               hd.element,
               hd.startLoc,
               hd.endLoc,
               hd.nestRule,
               hd.children,
               hd.textContent,
               depth,
             )
          ++ "\n";
        let next = str ++ el;
        astToString(next, [], depth);
      }
    | [hd, ...tl] =>
      if (str == "[\n") {
        let el =
          renderNode(
            hd.element,
            hd.startLoc,
            hd.endLoc,
            hd.nestRule,
            hd.children,
            hd.textContent,
            depth,
          )
          ++ ",\n";
        let next = str ++ el;
        astToString(next, tl, depth);
      } else {
        let el =
          "\n"
          ++ renderNode(
               hd.element,
               hd.startLoc,
               hd.endLoc,
               hd.nestRule,
               hd.children,
               hd.textContent,
               depth,
             )
          ++ ",\n";
        let next = str ++ el;
        astToString(next, tl, depth);
      }
    };
  }
and renderNode = (element, sloc, eloc, nestRule, children, textContent, depth) =>
  Utils.addSpace(depth)
  ++ "{\n"
  ++ Utils.addSpace(depth + 2)
  ++ "element: "
  ++ Utils.primitiveToString(element)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "startLoc: "
  ++ string_of_int(sloc)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "endLoc: "
  ++ string_of_int(eloc)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "nestRule: "
  ++ Utils.nestRuleToStr(nestRule)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "children: "
  ++ astToString("[\n", children, depth + 4)
  ++ ",\n"
  ++ Utils.addSpace(depth + 2)
  ++ "textContent: "
  ++ Utils.hasTextContent(textContent)
  ++ ",\n"
  ++ Utils.addSpace(depth)
  ++ "}";