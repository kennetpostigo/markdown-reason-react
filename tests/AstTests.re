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

/* let astOfBlockquote = () => {
     let chan = open_in("../../../tests/stubs/astBlockquote.md");
     Alcotest.(check(string))(
       "Ast.nodeOfBlockquote",
       {|{
     element: Blockquote,
     children: [],
     textContent: > this is a memorable quote about something.
   This is the secondLine.,
     location: (1, 2)
   }|},
       Utils.nodeToString(Ast.nodeOfBlockquote(chan, "", 1, 1)),
     );
     close_in(chan);
   };

   let astOfParagraph = () => {
     let chan = open_in("../../../tests/stubs/astParagraph.md");
     Alcotest.(check(string))(
       "Ast.nodeOfParagraph",
       {|{
     element: Paragraph,
     children: [],
     textContent: Lorem ipsum dolor sit amet, instructior vituperatoribus pri cu, quaeque
   albucius quaerendum te vel. Zril tamquam maiestatis nam no, in utamur quaestio
   scriptorem vim. Tota graeco vel ne, ne vel primis conclusionemque. Mea dicam
   tritani reformidans te, at sed erant molestie incorrupte. Laudem iisque ea vis,
   solet veniam dissentiet mea et.,
     location: (1, 5)
   }|},
       Utils.nodeToString(Ast.nodeOfParagraph(chan, "", 1, 1)),
     );
     close_in(chan);
   };

   let astOfCode = () => {
     let chan = open_in("../../../tests/stubs/astCode.md");
     Alcotest.(check(string))(
       "Ast.nodeOfCode",
       {|{
     element: Code,
     children: [],
     textContent: ```
   open LwtNode;

   Node.run({
     let%lwt myDir = Fs.mkdir("myDir");
     let%lwt myDir2 = Fs.mkdir("myDir2");
     Node.resolved();
   });
   ```,
     location: (1, 9)
   }|},
       Utils.nodeToString(Ast.nodeOfCode(chan, "", 1, 1)),
     );
     close_in(chan);
   }; */

let tests = [
  ("Ast.nodeOfLink", `Slow, astOfLink),
  ("Ast.nodeOfImage", `Slow, astOfImage),
  ("Ast.nodeOfFootnote", `Slow, astOfFootnote),
  /* ("Ast.nodeOfBlockquote", `Slow, astOfBlockquote),
     ("Ast.nodeOfParagraph", `Slow, astOfParagraph),
     ("Ast.nodeOfCode", `Slow, astOfCode), */
];