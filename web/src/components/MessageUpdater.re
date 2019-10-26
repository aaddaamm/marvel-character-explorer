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

[@react.component]
let make = () => {
  let (message, updateMessage) = React.useState(() => "Hello There");
  let (tempMessage, updateTempMessage) = React.useState(() => "");

  <div className=Styles.messageSection>
    <div>message -> React.string</div>
    <div>
      <input
        value={tempMessage}
        onChange={event => updateTempMessage(ReactEvent.Form.target(event)##value)}
      />
      <button onClick={_event => updateMessage(_ => tempMessage)}>
        "Update message" -> React.string
      </button>
    </div>
  </div>
};
