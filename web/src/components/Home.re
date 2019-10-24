module Styles = {
  open Css;
  let homeContainer = style([
    display(flexBox),
    justifyContent(center),
  ]);
};

[@react.component]
let make = () => {
  <div className=Styles.homeContainer>
    <h1>(ReasonReact.string("Welcome to the Marvel Character Explorer!"))</h1>
  </div>
};