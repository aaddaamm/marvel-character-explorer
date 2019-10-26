[@bs.val] external require: string => string = "";
let logo = require("../assets/MarvelLogo.svg");

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
      Shadow.box(
        ~x=px(0),
        ~y=px(1),
        ~blur=px(4),
        ~spread=px(0),
        rgba(0, 21, 41, 0.8))
    ),
  ]);

  let headerLogo = style([
    display(flexBox),
    marginLeft(px(15)),
    height(px(60)),
  ]);

  let headerSearch = style([
    display(flexBox),
    marginRight(px(15)),
  ]);

  let headerSearchButton = style([
    display(flexBox),
    marginTop(px(1)),
  ]);
};

[@react.component]
let make = (~message) => {
  <div className=Styles.header>
    <Link href="/">
      <img className=Styles.headerLogo src=logo/>
    </Link>
    <h2>message -> React.string</h2>
    <div className=Styles.headerSearch>
      <input type_="search" placeholder="Search this site" />
      <button className=Styles.headerSearchButton>"Search" -> React.string</button>
    </div>
  </div>
};
