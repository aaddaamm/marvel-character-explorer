type state = {
  pendingMessage: string,
  textMessage: string,
};

type action =
  | UpdatePendingMessage(string)
  | UpdateMessage;

let messageUpdater = ReasonReact.reducerComponent("MessageUpdater");

module Styles = {
  open Css;

  let button = style([marginLeft(px(5))]);

  let messageSection = style([
    display(flexBox),
    flexDirection(column),
    margin2(
      ~h=px(15),
      ~v=px(25),
    ),
  ]);
};

let make = (_children) => {
  ...messageUpdater,
  initialState: () => { pendingMessage: "", textMessage: "Hello" },
  reducer: (action, state) =>
    switch(action) {
      | UpdatePendingMessage(text) => ReasonReact.Update({ ...state, pendingMessage: text})
      | UpdateMessage => ReasonReact.Update({ textMessage: state.pendingMessage, pendingMessage: ""})
    },
  render: self => {
    <div className=Styles.messageSection>
      <div> {ReasonReact.string(self.state.textMessage)} </div>
      <div>
        <input
          value={self.state.pendingMessage}
          onChange={event =>
            self.send(
              UpdatePendingMessage(ReactEvent.Form.target(event)##value),
            )
          }
        />
        <button onClick={_event => self.send(UpdateMessage)}>
          {ReasonReact.string("Update message")}
        </button>
      </div>
    </div>;
  },
};
