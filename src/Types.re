type listTypes =
  | Ordered
  | Unordered;

type primitives =
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

type location = (int, int);
type ast = list(element)
and element = {
  element: primitives,
  children: ast,
  textContent: option(string),
  location,
};