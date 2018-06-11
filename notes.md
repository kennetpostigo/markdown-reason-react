# Notes

## Issues

1. Require a line break to distinguish between elements
   - The current implementation will iterate line by  and then is classified
     as a specific type of node, and passed as a single item to a `nodeOf`
     function or will be sent to a helper if it's a multiline element to create
     a list until a line break is hit. If there are no line breaks the multiline
     element logic breaks and multiline elements are grouped together as one type
     of element.

2. Nesting Element
   - Unhandled case

3. Inline Element
   - Unhandled case, but we have setup the ground work of supplying nesting
     rules for elements.

### Solutions

1. Require a line break to distinguish between elements
   - This can be fixed if we maintain a temporary list of elements where we add
     to this list by peeking at the `hd` of the list and checking if the type of
     element matches the current element, if it does add to the list, if not,
     group the contents of the list into one element (if it's multiline) if not
     creating individual elements per element. Then appending it to the AST, and
     reseting the temporary list and repeating until we reach the end of the
     file.

- Nested Element Case:
  - If text is left dangling without a space between last line then it should be part of the same list item
  - Doesn't matter how many spaces are between list items
  - List does not end until it encounters another element that is not a list/list item nor break.
  - Use indentation as a guide for determining child/nested lists.

- Inline Element Case:
  - parse element text char by char for link, img, strong, emphasis, and delete.