module Styles = {
  open Css;

  let partySection = style([
    margin2(
      ~h=px(15),
      ~v=px(25)
    ),
  ]);

  let button = style([marginLeft(px(5))]);

  let bounce = keyframes([
    (0, [transform(scale(0.1, 0.1)), opacity(0.0)]),
    (60, [transform(scale(1.2, 1.2)), opacity(1.0)]),
    (100, [transform(scale(1.0, 1.0)), opacity(1.0)]),
  ]);

  let partyTimeMessage = style([
    animationName(bounce),
    animationDuration(2000),
    width(px(250)),
    height(px(50)),
    marginLeft(px(25)),
    backgroundColor(rgb(255, 0, 0))
  ]);
};

[@react.component]
let make = () => {
  let (visible, setVisibile) = React.useState(_ => true);

  <div className=Styles.partySection>
    <button className=Styles.button onClick={_event => setVisibile(_ => !visible)}>
      "party switch" -> React.string
    </button>
    (
      visible
        ? (
          <h1 className=Styles.partyTimeMessage>"PARTY TIME!" -> React.string</h1>
        ) : (
          ReasonReact.null
        )
    )
  </div>
};

