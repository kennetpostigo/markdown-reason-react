MarkdownReasonReact.Tokenizer.readFileLineByLine(
  "readme.md", (line, location) =>
  print_string(
    MarkdownReasonReact.Tokenizer.primitivesToString(
      MarkdownReasonReact.Tokenizer.stringToPrimitives(line),
    )
    ++ " - "
    ++ location
    ++ ": "
    ++ (String.length(line) === 0 ? "NEW LINE" : line)
    ++ "\n===============================================\n\n",
  )
);