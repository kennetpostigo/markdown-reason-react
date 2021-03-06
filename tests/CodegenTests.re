open MarkdownReasonReact;

let getTextContentSome = () =>
  Alcotest.(check(string))(
    "Codegen.getTextContent with Some",
    "\n(ReasonReact.string({|hey lol!|}))\n",
    Codegen.getTextContent(Some("hey lol!")),
  );

let getTextContentNone = () =>
  Alcotest.(check(string))(
    "Codegen.getTextContent with None",
    "",
    Codegen.getTextContent(None),
  );

let renderText = () =>
  Alcotest.(check(string))(
    "Codegen.renderText",
    "\n(ReasonReact.string({|hey lol!|}))\n",
    Codegen.renderText("hey lol!"),
  );

let getRawTextContentSome = () =>
  Alcotest.(check(string))(
    "Codegen.getTextContent with Some",
    "hey lol!",
    Codegen.getRawTextContent(Some("hey lol!")),
  );

let getRawTextContentNone = () =>
  Alcotest.(check(string))(
    "Codegen.getTextContent with None",
    "",
    Codegen.getRawTextContent(None),
  );

let renderElementHeading1 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(1)",
    "<h1>\n(ReasonReact.string({|# Hello World|}))\n</h1>\n",
    Codegen.renderElement({
      element: Heading(1),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("# Hello World"),
    }),
  );

let renderElementHeading2 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(2)",
    "<h2>\n(ReasonReact.string({|## Hello World|}))\n</h2>\n",
    Codegen.renderElement({
      element: Heading(2),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("## Hello World"),
    }),
  );

let renderElementHeading3 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(3)",
    "<h3>\n(ReasonReact.string({|### Hello World|}))\n</h3>\n",
    Codegen.renderElement({
      element: Heading(3),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("### Hello World"),
    }),
  );

let renderElementHeading4 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(4)",
    "<h4>\n(ReasonReact.string({|#### Hello World|}))\n</h4>\n",
    Codegen.renderElement({
      element: Heading(4),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("#### Hello World"),
    }),
  );

let renderElementHeading5 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(5)",
    "<h5>\n(ReasonReact.string({|##### Hello World|}))\n</h5>\n",
    Codegen.renderElement({
      element: Heading(5),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("##### Hello World"),
    }),
  );

let renderElementHeading6 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(5)",
    "<h6>\n(ReasonReact.string({|###### Hello World|}))\n</h6>\n",
    Codegen.renderElement({
      element: Heading(6),
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("###### Hello World"),
    }),
  );

let renderElementBlockquote = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Blockquote",
    "<blockquote>\n(ReasonReact.string({|> Hello World|}))\n</blockquote>\n",
    Codegen.renderElement({
      element: Blockquote,
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("> Hello World"),
    }),
  );

let renderElementCode = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Code",
    "<pre>\n<code>\n(ReasonReact.string({|```\n Hello World\n```|}))\n</code>\n</pre>\n",
    Codegen.renderElement({
      element: Code,
      startLoc: 1,
      endLoc: 3,
      nestRule: [],
      children: [],
      textContent: Some("```\n Hello World\n```"),
    }),
  );

let renderElementLink = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Link",
    "<a href=\"https://lol.to\">\n(ReasonReact.string({|home|}))\n</a>\n",
    Codegen.renderElement({
      element: Link,
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("home https://lol.to"),
    }),
  );

let renderElementImage = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Image",
    "<img src=\"https://whale.to\" alt=\"whale\" />\n",
    Codegen.renderElement({
      element: Image,
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("whale https://whale.to"),
    }),
  );

let renderElementFootnote = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Footnote",
    "<sup>\n(ReasonReact.string({|Hello World|}))\n</sup>\n",
    Codegen.renderElement({
      element: Footnote,
      startLoc: 1,
      endLoc: 1,
      nestRule: [],
      children: [],
      textContent: Some("Hello World"),
    }),
  );

let tests = [
  ("Codegen.getTextContent with some", `Slow, getTextContentSome),
  ("Codegen.getTextContent with none", `Slow, getTextContentNone),
  ("Codegen.renderText", `Slow, renderText),
  ("Codegen.getRawTextContent with some", `Slow, getRawTextContentSome),
  ("Codegen.getRawTextContent with none", `Slow, getRawTextContentNone),
  ("Codegen.renderElement on Heading(1)", `Slow, renderElementHeading1),
  ("Codegen.renderElement on Heading(2)", `Slow, renderElementHeading2),
  ("Codegen.renderElement on Heading(3)", `Slow, renderElementHeading3),
  ("Codegen.renderElement on Heading(4)", `Slow, renderElementHeading4),
  ("Codegen.renderElement on Heading(5)", `Slow, renderElementHeading5),
  ("Codegen.renderElement on Heading(6)", `Slow, renderElementHeading6),
  ("Codegen.renderElement on Blockquote", `Slow, renderElementBlockquote),
  ("Codegen.renderElement on Code", `Slow, renderElementCode),
  ("Codegen.renderElement on Link", `Slow, renderElementLink),
  ("Codegen.renderElement on Image", `Slow, renderElementImage),
  ("Codegen.renderElement on Footnote", `Slow, renderElementFootnote),
];