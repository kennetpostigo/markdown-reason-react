let () = {
  let version = ref(false);
  let static = ref(false);

  let synopsis = "SYNOPSIS\n markdown-to-reason-react [OPTION]... DIRECTORY\n\n";
  let description = "DESCRIPTION\n Create reason-react pages from markdown files\n\n";
  let arguments = "ARGUMENTS\n  DIRECTORY\n    Input directories\n\n";

  let usage_msg =
    "\n\t\t\t\tMARKDOWN-TO-REASON-REACT\n\n\n"
    ++ synopsis
    ++ description
    ++ arguments
    ++ "OPTIONS";

  let speclist = [
    ("-v", Arg.Set(version), "Show version information"),
    (
      "-static",
      Arg.Set(static),
      "Generate a single page application from the directory ofmarkdown pages",
    ),
  ];

  Arg.parse(
    speclist,
    anon => print_endline("Anonymous argument: " ++ anon),
    usage_msg,
  );

  version^ ? print_string("0.1.0\n") : ();

  static^ ?
    MarkdownReasonReact.Tokenizer.parseText("lol") :
    MarkdownReasonReact.Tokenizer.parseText("lol");
};