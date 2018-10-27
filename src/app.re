[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

module Styles = {
  open Css;

  let app = style([
    display(flexBox),
    flexDirection(column),
  ]);

  let appContent = style([
    padding(px(15)),
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
    </div>,
};
