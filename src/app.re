let component = ReasonReact.statelessComponent("App");

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
};

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.app>
      <Header message=message />
      <div className=Styles.appContent>
        (ReasonReact.string("content"))
      </div>
      <Footer />
    </div>,
};
