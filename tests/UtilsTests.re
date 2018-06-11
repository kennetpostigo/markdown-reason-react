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

let strIdxSome = () =>
  Alcotest.(check(option(int)))(
    "Utils.strIdx with Some",
    Some(7),
    Utils.strIdx("Heading(1)", (1, 1), "# find meeeeee!", 'm', true),
  );

let strIdxNone = () =>
  Alcotest.(check(option(int)))(
    "Utils.strIdx with None",
    None,
    Utils.strIdx("Heading(1)", (1, 1), "# find meeeeee!", 'y', false),
  );

let strIdxFromSome = () =>
  Alcotest.(check(option(int)))(
    "Utils.strIdxFrom with Some",
    Some(8),
    Utils.strIdxFrom("Heading(1)", (1, 1), "# gucci gang!", 3, 'g', true),
  );

let strIdxFromNone = () =>
  Alcotest.(check(option(int)))(
    "Utils.strIdxFrom with None",
    None,
    Utils.strIdxFrom("Heading(1)", (1, 1), "# gucci gang!", 2, 'y', false),
  );

let strSubSome = () =>
  Alcotest.(check(option(string)))(
    "Utils.strSub with Some",
    Some("gang!"),
    Utils.strSub(
      "Heading(1)",
      (1, 1),
      "# gucci gang!",
      8,
      String.length("# gucci gang!") - 8,
      true,
    ),
  );

let strSubNone = () =>
  Alcotest.(check(option(string)))(
    "Utils.strSub with None",
    None,
    Utils.strSub("Heading(1)", (1, 1), "# gucci gang!", 0, 100, false),
  );

let nestRuleToStr = () =>
  Alcotest.(check(string))(
    "Utils.nestRuleToStr with a few Rules",
    "[Heading(1), Blockquote, Paragraph, ]",
    Utils.nestRuleToStr([Heading(1), Blockquote, Paragraph]),
  );

let nestRuleToStrEmpty = () =>
  Alcotest.(check(string))(
    "Utils.nestRuleToStr with an empty list",
    "[]",
    Utils.nestRuleToStr([]),
  );

let tests = [
  ("Utils.getIndent with empty string", `Slow, getIndentEmpty),
  ("Utils.getIndent on string without indent", `Slow, getIndentWithoutIndent),
  ("Utils.getIndent on string with 1 indent", `Slow, getIndentOf1),
  ("Utils.getIndent on string with 5 indents", `Slow, getIndentOf5),
  ("Utils.addSpace creates a string with a space", `Slow, addOneSpace),
  ("Utils.strIdx with Some", `Slow, strIdxSome),
  ("Utils.strIdx with None", `Slow, strIdxNone),
  ("Utils.strIdxFrom with Some", `Slow, strIdxFromSome),
  ("Utils.strIdxFrom with None", `Slow, strIdxFromNone),
  ("Utils.strIdxFrom with Some", `Slow, strIdxFromSome),
  ("Utils.strIdxFrom with None", `Slow, strIdxFromNone),
  ("Utils.strSub with Some", `Slow, strSubSome),
  ("Utils.strSub with None", `Slow, strSubNone),
  ("Utils.nestRuleToStr with a few Rules", `Slow, nestRuleToStr),
  ("Utils.nestRuleToStr with an empty list", `Slow, nestRuleToStrEmpty),
];