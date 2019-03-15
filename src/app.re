type state = {
  count: int,
  show: bool,
  pendingMessage: string,
  textMessage: string,
};

type action =
  | Click
  | UpdatePendingMessage(string)
  | UpdateMessage
  | Toggle;

let component = ReasonReact.reducerComponent("App");

module Styles = {
  open Css;

  let app = style([
    display(flexBox),
    flexDirection(column),
    minHeight(vh(100.)),
  ]);

  let appContent = style([
    padding(px(15)),
    flex(1)
  ]);

  let button = style([
    marginLeft(px(5))
  ]);
};

let make = (~message, _children) => {
  ...component,
  initialState: () => { count: 0, show: true, pendingMessage: "", textMessage: "Hello" },
  reducer: (action, state) =>
    switch(action) {
      | Click => ReasonReact.Update({ ...state, count: state.count + 1 })
      | UpdatePendingMessage(text) => ReasonReact.Update({ ...state, pendingMessage: text})
      | UpdateMessage => ReasonReact.Update({ ...state, textMessage: state.pendingMessage, pendingMessage: ""})
      | Toggle => ReasonReact.Update({ ...state, show: !state.show })
    },
  render: self => {
    let count = string_of_int(self.state.count);
    let countMessage = {j|you have clicked the button $(count) times|j};

    <div className=Styles.app>
      <Header message=message />
      <div className=Styles.appContent>
        (ReasonReact.string(countMessage))
        <button className=Styles.button onClick={_event => self.send(Click)}>
          (ReasonReact.string("button"))
        </button>
        <button className=Styles.button onClick={_event => self.send(Toggle)}>
          (ReasonReact.string("party switch"))
        </button>
        (
          self.state.show
            ? (
              <h1>(ReasonReact.string("PARTY TIME!"))</h1>
            ) : (
              ReasonReact.null
            )
        )
        <div>
          (ReasonReact.string(self.state.textMessage))
        </div>
        <div>
          <input
            value={self.state.pendingMessage}
            onChange={event => self.send(UpdatePendingMessage(ReactEvent.Form.target(event)##value))} />
          <button onClick={_event => self.send(UpdateMessage)}>
            (ReasonReact.string("Update message"))
          </button>
        </div>
      </div>
      <Footer />
    </div>
  },
};
