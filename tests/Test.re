let () =
  Alcotest.run(
    ~argv=[|"--verbose --color"|],
    "MarkdownReasonReact",
    [],
      /* ("tests", Test.tests), */
  );