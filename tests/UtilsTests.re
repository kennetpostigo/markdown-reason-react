open MarkdownReasonReact;

let getIndentEmpty = () =>
  Alcotest.(check(int))(
    "Utils.getIndent with empty string",
    0,
    Utils.getIndent(0, ""),
  );

let getIndentWithoutIndent = () =>
  Alcotest.(check(int))(
    "Utils.getIndent on string without indent",
    0,
    Utils.getIndent(0, "No indent in here"),
  );

let getIndentOf1 = () =>
  Alcotest.(check(int))(
    "Utils.getIndent on string with 1 indent",
    1,
    Utils.getIndent(0, " indent in here"),
  );

let getIndentOf5 = () =>
  Alcotest.(check(int))(
    "Utils.getIndent on string with 5 indents",
    5,
    Utils.getIndent(0, "     indent in here"),
  );

let addOneSpace = () =>
  Alcotest.(check(string))(
    "Utils.addSpace creates a string with a space",
    " ",
    Utils.addSpace(1),
  );

let tests = [
  ("Utils.getIndent with empty string", `Slow, getIndentEmpty),
  ("Utils.getIndent on string without indent", `Slow, getIndentWithoutIndent),
  ("Utils.getIndent on string with 1 indent", `Slow, getIndentOf1),
  ("Utils.getIndent on string with 5 indents", `Slow, getIndentOf5),
  ("Utils.addSpace creates a string with a space", `Slow, addOneSpace),
];