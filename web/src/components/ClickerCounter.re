type state = {
  count: int,
};

type action =
  | Click;

let clickerCounter = ReasonReact.reducerComponent("ClickerCounter");

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

let make = (_children) => {
  ...clickerCounter,
  initialState: () => { count: 0 },
  reducer: (action, state) =>
    switch(action) {
      | Click => ReasonReact.Update({ count: state.count + 1 })
    },
  render: self => {
    let count = string_of_int(self.state.count);
    let countMessage = {j|you have clicked the button $count times|j};

    <div className=Styles.clickerCounterSection>
      {ReasonReact.string(countMessage)}
      <button className=Styles.button onClick={_event => self.send(Click)}>
        {ReasonReact.string("button")}
      </button>
    </div>
  },
};
