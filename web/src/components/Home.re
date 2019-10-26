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
    <h1>"Welcome to the Marvel Character Explorer!" -> React.string</h1>
  </div>
};