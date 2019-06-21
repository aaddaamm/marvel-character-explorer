let str = ReasonReact.string;

type state =
  | Loading
  | Failure
  | Success(Types.responseWrapper);

type action =
  | LoadCharacters
  | LoadedCharacters(Types.responseWrapper)
  | LoadCharactersFailed;

let listCharacters = ReasonReact.reducerComponent("ListCharacters");

module Styles = {
  open Css;

  let characterItem = style([
    margin2(
      ~h=px(10),
      ~v=px(5)
    ),
  ]);
};

let make = (_children) => {
  ...listCharacters,
  initialState: () => Loading,
  didMount: self => {
    self.send(LoadCharacters);
  },
  reducer: (action, _state) =>
    switch (action) {
    | LoadCharacters =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Api.fetchCharacters()
              |> then_(result =>
                   switch (result) {
                   | Some(response) => resolve(self.send(LoadedCharacters(response)))
                   | None => resolve(self.send(LoadCharactersFailed))
                   }
                 )
              |> ignore
            )
        ),
      )
    | LoadedCharacters(response) => ReasonReact.Update(Success(response))
    | LoadCharactersFailed => ReasonReact.Update(Failure)
    },
  render: self =>
    switch (self.state) {
    | Loading => <div> (str("Loading...")) </div>
    | Failure => <div> (str("could not load characters")) </div>
    | Success(response) =>
      <div>
        <h2> (str("Characters")) </h2>
        <div>
          <h3>(str("response"))</h3>
          <div> (str(response.copyright)) </div>
          <div> (str(response.attributionText)) </div>
          <div> (str(response.attributionHTML)) </div>
          <div> (str(response.etag)) </div>
        </div>
        <div>
          <h3>(str("Data Container"))</h3>
          <div> (str(string_of_int(response.data.offset))) </div>
          <div> (str(string_of_int(response.data.limit))) </div>
          <div> (str(string_of_int(response.data.total))) </div>
          <div> (str(string_of_int(response.data.count))) </div>
        </div>
        <div>
        <h2> (str("Characters")) </h2>
          (response.data.results
            |> List.map(result => {
              let { id, name, modified, resourceURI, description }: Types.characterResult = result;
              <div className=Styles.characterItem key=(string_of_int(id))>
                <div>(str({j|Character Name: $(name)|j}))</div>
                <div>(str({j|Character Description: $(description)|j}))</div>
                <a href={resourceURI}>(str("link"))</a>
                <div>(str({j|last modified: $(modified)|j}))</div>
              </div>
            })
            |> Array.of_list
            |> ReasonReact.array
          )
        </div>
      </div>
    },
};