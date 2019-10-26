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
let make = () => {
  <div className=Styles.footer>
    <a href={"http://marvel.com"}>{j|Data provided by Marvel. \u00a9 $year Marvel|j} -> React.string</a>
  </div>
};

