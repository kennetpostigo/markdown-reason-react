type ast =
  | Paragraph
  | Blockquote
  | Heading
  | Code
  | InlineCode
  | YAML
  | HTML
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

type markdown('a) = {
  typ: string,
  body: list(ast),
};

type child = {
  typ: ast,
  value: string,
};

type children = list(child);

type paragraph = {
  typ: ast,
  diffP: string,
  children,
};

type blockquote = {
  typ: ast,
  diffbq: string,
  children: paragraph,
};

type heading = {
  typ: ast,
  depth: int,
  children,
};

type code = {
  typ: ast,
  lang: option(string),
  value: string,
};

type inlineCode = {
  typ: ast,
  diffIc: string,
  value: string,
};

type yaml = {
  typ: ast,
  diffY: string,
  value: string,
};

type html = {
  typ: ast,
  diffH: string,
  value: string,
};

type listItem = {
  typ: ast,
  loose: bool,
  checked: option(bool),
  children: paragraph,
};

type list = {
  typ: ast,
  ordered: bool,
  start: int,
  loose: bool,
  children: listItem,
};

type alignType =
  | Left
  | Right
  | Center
  | NULL;

type tableCell = {
  typ: ast,
  diffTC: string,
  children: paragraph,
};

type tableRow = {
  typ: ast,
  diffTR: string,
  children: tableCell,
};

type table = {
  typ: ast,
  align: alignType,
  children: tableRow,
};

type thematicBreak = {
  typ: ast,
  diffTB: string,
};

type break = {
  typ: ast,
  diffB: string,
};

type emphasis = {
  typ: ast,
  diffE: string,
  children,
};

type string = {
  typ: ast,
  diffE: string,
  children,
};

type delete = {
  typ: ast,
  diffE: string,
  children,
};

type link = {
  typ: ast,
  title: option(string),
  url: string,
  children,
};

type image = {
  typ: ast,
  title: option(string),
  alt: option(string),
  url: string,
};

type footnote = {
  typ: ast,
  diffFn: string,
  children,
};