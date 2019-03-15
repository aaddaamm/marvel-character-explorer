[%bs.raw {|require('./index.css')|}];

[@bs.module "./serviceWorker"]
external register_service_worker : unit => unit = "register";
[@bs.module "./serviceWorker"]
external unregister_service_worker : unit => unit = "unregister";

ReactDOMRe.renderToElementWithId(
  <App message="Marvel Character Explorer" />,
  "root",
);
/* ReasonReact.Router.push calls the pushState browser API which */
/* when given an empty url will push the current url */
ReasonReact.Router.push("");

unregister_service_worker();
