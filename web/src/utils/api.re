[@bs.val] external baseUrl : string = "process.env.REACT_APP_API_ORIGIN";
[@bs.val] external apiKey : string = "process.env.REACT_APP_API_KEY";

let expressOrigin = "http://localhost:5001";

type dataContainer('result) = {
   offset: option(int),
   limit: option(int),
   total: option(int),
   count: option(int),
   results: option(list('result))
};

type responseWrapper('result) = {
  code: option(int),
  status: option(string),
  copyright: option(string),
  attributionText: option(string),
  attributionHTML: option(string),
  etag: option(string),
  data: option(dataContainer('result))
};

module Decoders = {
  let user = user: Types.user =>
    Json.Decode.{
      id: field("id", int, user),
      firstName: field("firstName", string, user),
      lastName: field("lastName", string, user),
      username: field("username", string, user),
      email: field("email", string, user),
    };

    let users = json : list(Types.user) => Json.Decode.list(user, json);
};

let fetchUsers = () => Js.Promise.(
  Fetch.fetch({j|$(expressOrigin)/users|j})
  |> then_(Fetch.Response.json)
  |> then_(json =>
    json |> Decoders.users |> (users => Some(users) |> resolve)
  )
  |> catch(_err => resolve(None))
);
