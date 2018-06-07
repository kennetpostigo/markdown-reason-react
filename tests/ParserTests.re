open MarkdownReasonReact;
open Types;

let getSingleDigitPeriod = () =>
  Alcotest.(check(string))(
    "Parser.getPeriodSubStr a single digit list",
    "1",
    Parser.getPeriodSubStr("1. ...lol"),
  );

let getDoubleDigitPeriod = () =>
  Alcotest.(check(string))(
    "Parser.getPeriodSubStr a double digit list",
    "10",
    Parser.getPeriodSubStr("10. ...lol"),
  );

let getTripleDigitPeriod = () =>
  Alcotest.(check(string))(
    "Parser.getPeriodSubStr a triple digit list",
    "101",
    Parser.getPeriodSubStr("101. ...lol"),
  );

let parseHeading1 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 1",
    "Heading(1)",
    Utils.primitiveToString(Parser.parseHeading("# This is Heading 1")),
  );

let parseHeading2 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 2",
    "Heading(2)",
    Utils.primitiveToString(Parser.parseHeading("## This is Heading 2")),
  );

let parseHeading3 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 3",
    "Heading(3)",
    Utils.primitiveToString(Parser.parseHeading("### This is Heading 3")),
  );

let parseHeading4 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 4",
    "Heading(4)",
    Utils.primitiveToString(Parser.parseHeading("#### This is Heading 4")),
  );

let parseHeading5 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 5",
    "Heading(5)",
    Utils.primitiveToString(Parser.parseHeading("##### This is Heading 5")),
  );

let parseHeading6 = () =>
  Alcotest.(check(string))(
    "Parser.parseHeading a markdown header 6",
    "Heading(6)",
    Utils.primitiveToString(Parser.parseHeading("###### This is Heading 6")),
  );

let parseCode = () =>
  Alcotest.(check(string))(
    "Parser.parseCode a code block",
    "Code",
    Utils.primitiveToString(
      Parser.parseCode("```
  Js.log(\"Shit!\")
  ```"),
    ),
  );

let parseUnorderedList = () =>
  Alcotest.(check(string))(
    "Parser.parseList an unordred list",
    "List(Unordered)",
    Utils.primitiveToString(Parser.parseList("- yo waddup im unordered!")),
  );

let parseOrderedList = () =>
  Alcotest.(check(string))(
    "Parser.parseList an ordered list",
    "List(Ordered)",
    Utils.primitiveToString(Parser.parseList("1. yo waddup im ordered!")),
  );

let parseImage = () =>
  Alcotest.(check(string))(
    "Parser.parseImage an image",
    "Image",
    Utils.primitiveToString(
      Parser.parseImage("![alt](https://image.to title)"),
    ),
  );

let parseLink = () =>
  Alcotest.(check(string))(
    "Parser.parseLinkFootnote a link",
    "Link",
    Utils.primitiveToString(
      Parser.parseLinkFootnote("[eyyy](https://link.to)"),
    ),
  );

let parseFootnote = () =>
  Alcotest.(check(string))(
    "Parser.parseLinkFootnote a footnote",
    "Footnote",
    Utils.primitiveToString(
      Parser.parseLinkFootnote("[^eyy heres a footnote]"),
    ),
  );

let tests = [
  ("Parser.getPeriodSubStr a single digit list", `Slow, getSingleDigitPeriod),
  ("Parser.getPeriodSubStr a double digit list", `Slow, getDoubleDigitPeriod),
  ("Parser.getPeriodSubStr a triple digit list", `Slow, getTripleDigitPeriod),
  ("Parser.parseHeading a markdown header 1", `Slow, parseHeading1),
  ("Parser.parseHeading a markdown header 2", `Slow, parseHeading2),
  ("Parser.parseHeading a markdown header 3", `Slow, parseHeading3),
  ("Parser.parseHeading a markdown header 4", `Slow, parseHeading4),
  ("Parser.parseHeading a markdown header 5", `Slow, parseHeading5),
  ("Parser.parseHeading a markdown header 6", `Slow, parseHeading6),
  ("Parser.parseCode a code block", `Slow, parseCode),
  ("Parser.parseList an unordered list", `Slow, parseUnorderedList),
  ("Parser.parseImage an image", `Slow, parseImage),
  ("Parser.parseList an ordered list", `Slow, parseLink),
  ("Parser.parseLinkFootnote an link", `Slow, parseFootnote),
  ("Parser.parseLinkFootnote a footnote", `Slow, parseOrderedList),
];