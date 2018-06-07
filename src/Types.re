type listTypes =
  | Ordered
  | Unordered;

type primitive =
  | Heading(int)
  | Blockquote
  | Paragraph
  | Break
  | Emphasis
  | Strong
  | Delete
  | List(listTypes)
  | ListItem
  | Code
  | InlineCode
  | Table
  | TableRow
  | TableCell
  | ThematicBreak
  | Link
  | Image
  | Footnote
  | LinkReference
  | ImageReference
  | FootnoteReference
  | Definition
  | FootnoteDefinition;

type ast = list(element)
and element = {
  element: primitive,
  startLoc: int,
  endLoc: int,
  nestRule: list(primitive),
  children: ast,
  textContent: option(string),
};