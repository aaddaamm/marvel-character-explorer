[@bs.module] external logo : string = "./MarvelLogo.svg";

let component = ReasonReact.statelessComponent("Header");

let make = (~message, _children) => {
  ...component,
  render: _self =>
    <div className="header">
      <img className="header-logo" src=logo/>
      <h2>(ReasonReact.string(message))</h2>
      <input className="header-search-box"></input>
    </div>,
};
