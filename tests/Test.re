let () =
  Alcotest.run(
    ~argv=[|"--verbose --color"|],
    "MarkdownReasonReact",
    [
      ("ParserTests", ParserTests.tests),
      ("AstTests", AstTests.tests),
      ("CodegenTests", CodegenTests.tests),
      ("UtilsTests", UtilsTests.tests),
    ],
  );