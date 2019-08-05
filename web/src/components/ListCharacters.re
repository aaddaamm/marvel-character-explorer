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

  let characterItemRow = style([
    display(flexBox),
    flexDirection(row),
    margin2(
      ~h=px(10),
      ~v=px(5)
    ),
  ]);

  let characterItemRowDetails = style([
    marginLeft(px(15)),
  ]);

  let characterLink = style([
    marginRight(px(5)),
  ]);

  let characterListControls = style([
    display(flexBox),
    flexDirection(row),
  ]);

  let nextButton = style([
    marginLeft(px(5)),
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
    <div>
      <h2> (str("Characters")) </h2>
        (switch (self.state) {
        | Loading => <div> (str("Loading...")) </div>
        | Failure => <div> (str("could not load characters")) </div>
        | Success(response) => {
          let { data: { count, total, offset, results: characters } }: Types.responseWrapper = response;
          <div>
            (characters
              |> List.map(character => {
                let { id, name, description, urls, thumbnail: { path, extension } }: Types.characterResult = character;
                // image documentation here
                // https://developer.marvel.com/documentation/images
                <div className=Styles.characterItemRow key=(string_of_int(id))>
                  <img src={{j|$(path)/standard_large.$(extension)|j}} alt={name} />
                  <div className=Styles.characterItemRowDetails>
                    <div>(str({j|Character Name: $(name)|j}))</div>
                    <div>(str({j|Character Description: $(description)|j}))</div>
                    (urls
                      |> List.map(url => {
                        let { type_, path }: Types.urlItem = url;
                        <a key={string_of_int(Random.int(100000))} className=Styles.characterLink target="_blank" href={path}>
                          (switch (type_) {
                            | "detail" => str("Details")
                            | "wiki" => str("Wiki")
                            | "comiclink" => str("Comics")
                            | _ => ReasonReact.null
                          })
                        </a>
                      })
                      |> Array.of_list
                      |> ReasonReact.array
                    )
                  </div>
                </div>
              })
              |> Array.of_list
              |> ReasonReact.array
            )
            <div className=Styles.characterListControls>
              (offset > 0 ? <button>(str("previous"))</button> : ReasonReact.null)
              <div>(str({j|$(count) of $(total)|j}))</div>
              <button className=Styles.nextButton>(str("next"))</button>
            </div>
          </div>
        }
        })
      </div>,
};