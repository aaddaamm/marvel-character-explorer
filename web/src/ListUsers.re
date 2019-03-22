let str = ReasonReact.string;

type state =
  | Loading
  | Failure
  | Success(list(Types.user));

type action =
  | LoadUsers
  | LoadedUsers(list(Types.user))
  | LoadUsersFailed;


let listUsers = ReasonReact.reducerComponent("ListUsers");

module Styles = {
  open Css;

  let userItem = style([
    margin2(
      ~h=px(10),
      ~v=px(5)
    ),
  ]);
};

let make = (_children) => {
  ...listUsers,
  initialState: () => Loading,
  didMount: self => {
    self.send(LoadUsers);
  },
  reducer: (action, _state) =>
    switch (action) {
    | LoadUsers =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Api.fetchUsers()
              |> then_(result =>
                   switch (result) {
                   | Some(users) => resolve(self.send(LoadedUsers(users)))
                   | None => resolve(self.send(LoadUsersFailed))
                   }
                 )
              |> ignore
            )
        ),
      )
    | LoadedUsers(users) => ReasonReact.Update(Success(users))
    | LoadUsersFailed => ReasonReact.Update(Failure)
    },
  render: self =>
    switch (self.state) {
    | Loading => <div> (str("Loading...")) </div>
    | Failure => <div> (str("could not load users")) </div>
    | Success(users) =>
      <div>
        <h2> (str("Users")) </h2>
        <div>
          (users
            |> List.map((user: Types.user) => {
              <div className=Styles.userItem key=(string_of_int(user.id))>
                <div>(str({j|First Name: user.firstName|j}))</div>
                <div>(str(user.lastName))</div>
                <div>(str(user.username))</div>
                <div>(str(user.email))</div>
              </div>
            })
            |> Array.of_list
            |> ReasonReact.array
          )
        </div>
      </div>
    },
};
