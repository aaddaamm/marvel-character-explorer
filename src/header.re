[@bs.module] external logo : string = "./MarvelLogo.svg";

let component = ReasonReact.statelessComponent("Header");

module Styles = {
  open Css;

  let header = style([
    display(flexBox),
    flexDirection(row),
    justifyContent(spaceBetween),
    backgroundColor(hex("282c34")),
    height(vh(15.)),
    alignItems(center),
    fontSize(Calc.(+)(px(12), vmin(2.))),
    color(white)
  ]);

  let headerLogo = style([
    display(flexBox),
    marginLeft(px(15)),
    height(px(60))
  ]);

  let headerSearchBox = style([
    display(flexBox),
    marginRight(px(15)),
  ]);
};

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.header>
      <img className=Styles.headerLogo src=logo/>
      <h2>(ReasonReact.string(message))</h2>
      <input className=Styles.headerSearchBox />
    </div>,
};
