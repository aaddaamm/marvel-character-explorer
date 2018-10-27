[%bs.raw {|require('./app.css')|}];

let component = ReasonReact.statelessComponent("App");

let make = (~message, _children) => {
  ...component,
  render  : _self =>
    <div className="app">
      <Header message=message />
      <div className="app-content">
        (ReasonReact.string("content"))
      </div>
    </div>,
};
