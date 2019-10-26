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
      <Link href="/clicker-counter">"Clicker Counter" -> React.string</Link>
      <Link href="/party-time">"Party Time" -> React.string</Link>
      <Link href="/message-updater">"Message Updater" -> React.string</Link>
      // <Link href="/list-users">"List Users" -> React.string</Link>
      // <Link href="/list-characters">"List Characters" -> React.string</Link>
    </div>
    <div className=Styles.appContent>
      (
        switch url.path {
          | [] => <Home />
          | ["clicker-counter"] => <ClickerCounter />
          | ["party-time"] => <PartyTime />
          | ["message-updater"] => <MessageUpdater />
          // | ["list-users"] => <ListUsers />
          // | ["list-characters"] => <ListCharacters />
          | _ => <Home />
        }
      )
    </div>
    <Footer />
  </div>
};
