let home = ReasonReact.statelessComponent("Home");

module Styles = {
  open Css;
  let homeContainer = style([
    display(flexBox),
    justifyContent(center),
  ]);
};

let make = (_children) => {
  ...home,
  render: _self =>
    <div className=Styles.homeContainer>
      <h1>(ReasonReact.string("Welcome to the Marvel Character Explorer!"))</h1>
    </div>
};