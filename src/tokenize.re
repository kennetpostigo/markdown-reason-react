type typ =
  | Markdown
  | HTML
  | YAML;

type primitives =
  | Paragraph
  | Blockquote
  | Heading
  | Code
  | InlineCode
  | List
  | ListItem
  | Table
  | TableRow
  | TableCell
  | ThematicBreak
  | Break
  | Emphasis
  | Strong
  | Delete
  | Link
  | Image
  | Footnote
  | LinkReference
  | ImageReference
  | FootnoteReference
  | Definition
  | FootnoteDefinition
  | TextNode;

type location = (int, int);

type element = {
  element: (typ, primitives),
  children: list(element),
  location,
};

let read_file = filename => {
  let lines = ref([]);
  let chan = open_in(filename);
  try (
    {
      while (true) {
        lines := [input_line(chan), ...lines^];
      };
      lines^;
    }
  ) {
  | End_of_file =>
    close_in(chan);
    List.rev(lines^);
  };
};