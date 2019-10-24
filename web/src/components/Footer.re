module Styles = {
  open Css;

  let footer = style([
    display(flexBox),
    alignContent(flexEnd),
    margin2(
      ~h=px(15),
      ~v=px(5)
    ),
  ]);
};

let date = Js.Date.make();
let year = Js.Date.getFullYear(date);

[@react.component]
let make = (_children) => {
  <div className=Styles.footer>
    <a href={"http://marvel.com"}>(ReasonReact.string({j|Data provided by Marvel. \u00a9 $year Marvel|j}))</a>
  </div>
};

