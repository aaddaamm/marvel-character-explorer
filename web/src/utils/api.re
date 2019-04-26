[@bs.val] external baseUrl : string = "process.env.REACT_APP_API_ORIGIN";
[@bs.val] external apiKey : string = "process.env.REACT_APP_API_KEY";

let expressOrigin = "http://localhost:5001";
let marvelOrigin = "https://gateway.marvel.com/v1/public";


module Decoders = {
  let user = user: Types.user =>
    Json.Decode.{
      id: user |> field("id", int),
      firstName: user |> field("firstName", string),
      lastName: user |> field("lastName", string),
      username: user |> field("username", string),
      email: user |> field("email", string),
    };

  let users = json : list(Types.user) => Json.Decode.list(user, json);

  let dataContainer = data: Types.dataContainer =>
    Json.Decode.{
      offset: data |> field("offset", int),
      limit: data |> field("limit", int),
      total: data |> field("total", int),
      count: data |> field("count", int)
    };

  let response = response: Types.responseWrapper =>
    Json.Decode.{
      code: response |> field("code", int),
      status: response |> field("status", string),
      copyright: response |> field("copyright", string),
      attributionText: response |> field("attributionText", string),
      attributionHTML: response |> field("attributionHTML", string),
      etag: response |> field("etag", string),
      data: response |> field("data", dataContainer)
    };
};

let fetchUsers = () => Js.Promise.(
  Fetch.fetch({j|$(expressOrigin)/users|j})
  |> then_(Fetch.Response.json)
  |> then_(json =>
    json |> Decoders.users |> (users => Some(users) |> resolve)
  )
  |> catch(_err => resolve(None))
);

let fetchCharacters = () => Js.Promise.(
  Fetch.fetchWithInit(
    {j|$(marvelOrigin)/characters?apikey=54ad35742989cb9270c1a61a9bcf9ca2|j},
    Fetch.RequestInit.make(
      ~method_=Get,
      ~headers=Fetch.HeadersInit.make({ "Accept": "application/json" }),
      ~referrer="developer.marvel.com",
      ()
    )
  )
  |> then_(Fetch.Response.json)
  |> then_(json =>
    json |> Decoders.response |> (response => Some(response) |> resolve)
  )
  |> catch(_err => resolve(None))
);
