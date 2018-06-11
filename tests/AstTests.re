open MarkdownReasonReact;
open Types;

let astOfLink = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfLink",
    {|{
  element: Link,
  startLoc: 1,
  endLoc: 1,
  nestRule: [],
  children: [],
  textContent: link http://lol.to title,
}|},
    Utils.nodeToString(Ast.nodeOfLink("[link](http://lol.to title)", 1, 1)),
  );

let astOfImage = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfImage",
    {|{
  element: Image,
  startLoc: 1,
  endLoc: 1,
  nestRule: [],
  children: [],
  textContent: link http://lol.to lol,
}|},
    Utils.nodeToString(Ast.nodeOfImage("![link](http://lol.to lol)", 1, 1)),
  );

let astOfFootnote = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfFootnote",
    {|{
  element: Footnote,
  startLoc: 1,
  endLoc: 1,
  nestRule: [],
  children: [],
  textContent: some footnote,
}|},
    Utils.nodeToString(Ast.nodeOfFootnote("[^some footnote]", 1, 1)),
  );

let astOfParagraph = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfParagraph",
    {|{
  element: Paragraph,
  startLoc: 1,
  endLoc: 5,
  nestRule: [],
  children: [],
  textContent: Lorem ipsum dolor sit amet, instructior vituperatoribus pri cu, quaeque
albucius quaerendum te vel. Zril tamquam maiestatis nam no, in utamur quaestio
scriptorem vim. Tota graeco vel ne, ne vel primis conclusionemque. Mea dicam
tritani reformidans te, at sed erant molestie incorrupte. Laudem iisque ea vis,
solet veniam dissentiet mea et.,
}|},
    Utils.nodeToString(
      Ast.nodeOfParagraph(
        [
          "Lorem ipsum dolor sit amet, instructior vituperatoribus pri cu, quaeque",
          "albucius quaerendum te vel. Zril tamquam maiestatis nam no, in utamur quaestio",
          "scriptorem vim. Tota graeco vel ne, ne vel primis conclusionemque. Mea dicam",
          "tritani reformidans te, at sed erant molestie incorrupte. Laudem iisque ea vis,",
          "solet veniam dissentiet mea et.",
        ],
        "",
        1,
        1,
      ),
    ),
  );

let astOfBlockquote = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfBlockquote",
    {|{
  element: Blockquote,
  startLoc: 1,
  endLoc: 2,
  nestRule: [],
  children: [],
  textContent: this is a memorable quote about something.
This is the secondLine.,
}|},
    Utils.nodeToString(
      Ast.nodeOfBlockquote(
        [
          "> this is a memorable quote about something.",
          "This is the secondLine.",
        ],
        "",
        1,
        1,
      ),
    ),
  );

let astOfCode = () =>
  Alcotest.(check(string))(
    "Ast.nodeOfCode",
    "{\n  element: Code,\n  startLoc: 1,\n  endLoc: 9,\n  nestRule: [],\n  children: [],\n  textContent: \n"
    ++ {|open LwtNode;

Node.run({
  let%lwt myDir = Fs.mkdir("myDir");
  let%lwt myDir2 = Fs.mkdir("myDir2");
  Node.resolved();
});,
}|},
    Utils.nodeToString(
      Ast.nodeOfCode(
        [
          "```",
          "open LwtNode;",
          "",
          "Node.run({",
          {|  let%lwt myDir = Fs.mkdir("myDir");|},
          {|  let%lwt myDir2 = Fs.mkdir("myDir2");|},
          "  Node.resolved();",
          "});",
        ],
        "",
        1,
        1,
      ),
    ),
  );

let tests = [
  ("Ast.nodeOfLink", `Slow, astOfLink),
  ("Ast.nodeOfImage", `Slow, astOfImage),
  ("Ast.nodeOfFootnote", `Slow, astOfFootnote),
  ("Ast.nodeOfBlockquote", `Slow, astOfBlockquote),
  ("Ast.nodeOfParagraph", `Slow, astOfParagraph),
  ("Ast.nodeOfCode", `Slow, astOfCode),
];