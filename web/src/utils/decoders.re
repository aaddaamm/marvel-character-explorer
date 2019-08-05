
let user = user: Types.user =>
  Json.Decode.{
    id: user |> field("id", int),
    firstName: user |> field("firstName", string),
    lastName: user |> field("lastName", string),
    username: user |> field("username", string),
    email: user |> field("email", string),
  };

let users = json : list(Types.user) => Json.Decode.list(user, json);

let characterUrl = data: Types.urlItem =>
  Json.Decode.{
    type_: data |> field("type", string),
    path: data |> field("url", string),
  };

let thumbnail = data: Types.imageItem =>
  Json.Decode.{
    path: data |> field("path", string),
    extension: data |> field("extension", string),
  };

let character = result: Types.characterResult =>
  Json.Decode.{
    id: result |> field("id", int),
    name: result |> field("name", string),
    modified: result |> field("modified", string),
    resourceURI: result |> field("resourceURI", string),
    description: result |> field("description", string),
    thumbnail: result |> field("thumbnail", thumbnail),
    urls: result |> field("urls", list(characterUrl))
  };

let dataContainer = data: Types.dataContainer =>
  Json.Decode.{
    offset: data |> field("offset", int),
    limit: data |> field("limit", int),
    total: data |> field("total", int),
    count: data |> field("count", int),
    results: data |> field("results", list(character))
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
