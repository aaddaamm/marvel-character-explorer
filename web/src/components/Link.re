let handleClick = (href, event) =>
  /* the default action will reload the page, which will cause us to lose state */
  if (! ReactEvent.Mouse.defaultPrevented(event)) {
    ReactEvent.Mouse.preventDefault(event);
    ReasonReactRouter.push(href)
  };

[@react.component]
let make = (~href, ~children) => {
  <a href={href} onClick=handleClick(href)>
    children
  </a>
};
