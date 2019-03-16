type route =
  | Home
  | ClickerCounter
  | PartyTime
  | MessageUpdater;

type state = {
  route: route,
};

type action =
  | ChangeRoute(route);

let component = ReasonReact.reducerComponent("App");

module Styles = {
  open Css;

  let app = style([
    display(flexBox),
    flexDirection(column),
    minHeight(vh(100.)),
  ]);

  let appContent = style([
    padding(px(15)),
    flex(1),
  ]);

  let navigation = style([
    display(flexBox),
    flexDirection(row),
    justifyContent(spaceEvenly),
    paddingTop(px(15)),
    paddingBottom(px(15)),
  ]);
};

let mapUrlToRoute = (url: ReasonReact.Router.url) =>
  switch url.path {
    | [] => Home
    | ["clicker-counter"] => ClickerCounter
    | ["party-time"] => PartyTime
    | ["message-updater"] => MessageUpdater
    | _ => Home
  };

let make = (~message, _children) => {
  ...component,
  initialState: () => { route: ClickerCounter },
  didMount: (self) => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        self.send(ChangeRoute(url |> mapUrlToRoute))
      );

    self.onUnmount(() => ReasonReact.Router.unwatchUrl(watcherID));
  },
  reducer: (action, _state) =>
    switch action {
      | ChangeRoute(route) => ReasonReact.Update({ route: route});
  },
  render: self => {
    <div className=Styles.app>
      <Header message=message />
      <div className=Styles.navigation>
        <Link href="/clicker-counter">(ReasonReact.string("Clicker Counter"))</Link>
        <Link href="/party-time">(ReasonReact.string("Party Time"))</Link>
        <Link href="/message-updater">(ReasonReact.string("Message Updater"))</Link>
      </div>
      <div className=Styles.appContent>
        (
          switch self.state.route {
            | Home => <Home />
            | ClickerCounter => <ClickerCounter />
            | PartyTime => <PartyTime />
            | MessageUpdater => <MessageUpdater />
          }
        )
      </div>
      <Footer />
    </div>
  },
};
