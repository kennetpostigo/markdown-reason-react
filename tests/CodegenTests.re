open MarkdownReasonReact;
open Types;

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
      children: [],
      textContent: Some("# Hello World"),
      location: (1, 1),
    }),
  );

let renderElementHeading2 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(2)",
    "<h2>\n(ReasonReact.string({|## Hello World|}))\n</h2>\n",
    Codegen.renderElement({
      element: Heading(2),
      children: [],
      textContent: Some("## Hello World"),
      location: (1, 1),
    }),
  );

let renderElementHeading3 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(3)",
    "<h3>\n(ReasonReact.string({|### Hello World|}))\n</h3>\n",
    Codegen.renderElement({
      element: Heading(3),
      children: [],
      textContent: Some("### Hello World"),
      location: (1, 1),
    }),
  );

let renderElementHeading4 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(4)",
    "<h4>\n(ReasonReact.string({|#### Hello World|}))\n</h4>\n",
    Codegen.renderElement({
      element: Heading(4),
      children: [],
      textContent: Some("#### Hello World"),
      location: (1, 1),
    }),
  );

let renderElementHeading5 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(5)",
    "<h5>\n(ReasonReact.string({|##### Hello World|}))\n</h5>\n",
    Codegen.renderElement({
      element: Heading(5),
      children: [],
      textContent: Some("##### Hello World"),
      location: (1, 1),
    }),
  );

let renderElementHeading6 = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Heading(5)",
    "<h6>\n(ReasonReact.string({|###### Hello World|}))\n</h6>\n",
    Codegen.renderElement({
      element: Heading(6),
      children: [],
      textContent: Some("###### Hello World"),
      location: (1, 1),
    }),
  );

let renderElementBlockquote = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Blockquote",
    "<blockquote>\n(ReasonReact.string({|> Hello World|}))\n</blockquote>\n",
    Codegen.renderElement({
      element: Blockquote,
      children: [],
      textContent: Some("> Hello World"),
      location: (1, 1),
    }),
  );

let renderElementCode = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Code",
    "<pre>\n<code>\n(ReasonReact.string({|```\n Hello World\n```|}))\n</code>\n</pre>\n",
    Codegen.renderElement({
      element: Code,
      children: [],
      textContent: Some("```\n Hello World\n```"),
      location: (1, 3),
    }),
  );

let renderElementLink = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Link",
    "<a href=\"https://lol.to\" title=\"shit\">\n(ReasonReact.string({|home|}))\n</a>\n",
    Codegen.renderElement({
      element: Link,
      children: [],
      textContent: Some("home https://lol.to shit"),
      location: (1, 1),
    }),
  );

let renderElementImage = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Image",
    "<img src=\"https://whale.to\" alt=\"whale\" />\n",
    Codegen.renderElement({
      element: Image,
      children: [],
      textContent: Some("whale https://whale.to"),
      location: (1, 1),
    }),
  );

let renderElementFootnote = () =>
  Alcotest.(check(string))(
    "Codegen.renderElement on Footnote",
    "<sup>\n(ReasonReact.string({|Hello World|}))\n</sup>\n",
    Codegen.renderElement({
      element: Footnote,
      children: [],
      textContent: Some("Hello World"),
      location: (1, 1),
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