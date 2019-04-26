[%bs.raw {|require('./index.css')|}];

open Helpers;

ReactDOMRe.renderToElementWithId(
  <App message="Marvel Character Explorer" />,
  "root",
);

if (hot) {
  accept();
}
/* ReasonReactRouter.push calls the pushState browser API which */
/* when given an empty url will push the current url */
ReasonReactRouter.push("");
