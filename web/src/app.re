module Styles = {
  open Css;

  let app = style([
    display(flexBox),
    flexDirection(column),
    minHeight(vh(100.)),
  ]);

  let appContent = style([
    padding(px(15)),
    flex(auto),
  ]);

  let navigation = style([
    display(flexBox),
    flexDirection(row),
    justifyContent(spaceEvenly),
    paddingTop(px(15)),
    paddingBottom(px(15)),
  ]);
};

[@react.component]
let make = (~message) => {
  let url = ReasonReactRouter.useUrl();

  <div className=Styles.app>
    <Header message=message />
    <div className=Styles.navigation>
      <Link href="/clicker-counter">(ReasonReact.string("Clicker Counter"))</Link>
      <Link href="/party-time">(ReasonReact.string("Party Time"))</Link>
      <Link href="/message-updater">(ReasonReact.string("Message Updater"))</Link>
      // <Link href="/list-users">(ReasonReact.string("List Users"))</Link>
      // <Link href="/list-characters">(ReasonReact.string("List Characters"))</Link>
    </div>
    <div className=Styles.appContent>
      (
        switch url.path {
          | [] => <Home />
          | ["clicker-counter"] => <ClickerCounter />
          | ["party-time"] => <PartyTime />
          | ["message-updater"] => <MessageUpdater />
          // | ListUsers => <ListUsers />
          // | ListCharacters => <ListCharacters />
          | _ => <Home />
        }
      )
    </div>
    <Footer />
  </div>
};
