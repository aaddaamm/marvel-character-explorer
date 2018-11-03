[@bs.module] external logo : string = "./MarvelLogo.svg";

let component = ReasonReact.statelessComponent("Header");

module Styles = {
  open Css;

  let header = style([
    display(flexBox),
    flexDirection(row),
    justifyContent(spaceBetween),
    backgroundColor(hex("282c34")),
    height(vh(10.)),
    alignItems(center),
    fontSize(Calc.(+)(px(12), vmin(2.))),
    color(white),
    minHeight(px(100)),
    boxShadow(
      ~x=px(0),
      ~y=px(1),
      ~blur=px(4),
      ~spread=px(0),
      rgba(0, 21, 41, 0.8)
    )
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
