let () =
  Alcotest.run(
    ~argv=[|"--verbose --color"|],
    "MarkdownReasonReact",
    [
      ("ParserTests", ParserTests.tests),
      ("AstTests", AstTests.tests),
      ("CodegenTests", CodegenTests.tests),
      ("UtilsTests", UtilsTests.tests),
      ("Blockquotes", Blockquotes.tests),
      ("Code", Code.tests),
      ("Footnote", Footnote.tests),
      ("Heading", Heading.tests),
      ("Image", Image.tests),
      ("Link", Link.tests),
      ("List", Lists.tests),
      ("Paragraph", Paragraph.tests),
    ],
    /* ("tests", Test.tests), */
  );