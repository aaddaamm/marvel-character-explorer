let component = ReasonReact.statelessComponent("Footer");

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

let make = (_children) => {
  ...component,
  render: _self =>
    <div className=Styles.footer>
      (ReasonReact.string({j|Data provided by Marvel. \u00a9 2014 Marvel|j}))
    </div>
};

