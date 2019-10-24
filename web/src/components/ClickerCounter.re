let str = ReasonReact.string

module Styles = {
  open Css;

  let button = style([marginLeft(px(5))]);

  let clickerCounterSection = style([
    margin2(
      ~h=px(15),
      ~v=px(25),
    ),
  ]);
};

[@react.component]
let make = () => {
  let (count, setCount) = React.useState(() => 0);

  <div className=Styles.clickerCounterSection>
    {str({j|you have clicked the button $count times|j})}
    <button className=Styles.button onClick={_event => setCount(_ => count + 1)}>
      {str("button")}
    </button>
  </div>
};
