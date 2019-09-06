let str = ReasonReact.string;

type state =
  | Loading
  | Failure
  | Success(Types.responseWrapper);

type action =
  | LoadCharacters(int)
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
    self.send(LoadCharacters(0));
  },
  reducer: (action, _state) =>
    switch (action) {
    | LoadCharacters(offset) =>
      ReasonReact.UpdateWithSideEffects(
        Loading,
        (
          self =>
            Js.Promise.(
              Api.fetchCharacters(~offset=offset, ())
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
                    <h3>(str({j|Character Name: $(name)|j}))</h3>
                    <h4>(str("Character Description: "))(String.length(description) > 0 ? str(description) : str("N/A"))</h4>
                    (urls
                      |> List.map(url => {
                        let { type_, path }: Types.urlItem = url;
                        <a key={string_of_int(id) ++ type_} className=Styles.characterLink target="_blank" href={path}>
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
              (offset > 0 ?
                <button onClick={_event => self.send(LoadCharacters(offset - count))}>(str("previous"))</button>
                :
                ReasonReact.null
              )
              <div>(str({j|$count of $total|j}))</div>
              (offset + count < total ?
                <button
                  className=Styles.nextButton
                  onClick={_event => self.send(LoadCharacters(offset + count))}>
                  (str("next"))
                </button>
                :
                ReasonReact.null
              )
            </div>
          </div>
        }
        })
      </div>,
};