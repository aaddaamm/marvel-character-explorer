[@bs.val] external marvelBaseUrl : string = "process.env.MARVEL_API_ORIGIN";
[@bs.val] external apiKey : string = "process.env.MARVEL_API_KEY";

let expressOrigin = "http://localhost:5001";


let fetchUsers = () => Js.Promise.(
  Fetch.fetch({j|$(expressOrigin)/users|j})
  |> then_(Fetch.Response.json)
  |> then_(json =>
    json |> Decoders.users |> (users => Some(users) |> resolve)
  )
  |> catch(_err => resolve(None))
);

let fetchCharacters = (~offset=0, ()) => Js.Promise.(
  Fetch.fetchWithInit(
    {j|$(marvelBaseUrl)/characters?apikey=$(apiKey)&offset=$(offset)|j},
    Fetch.RequestInit.make(
      ~method_=Get,
      ~headers=Fetch.HeadersInit.make({ "Accept": "application/json" }),
      ~referrer="developer.marvel.com",
      ()
    )
  )
  |> then_(Fetch.Response.json)
  |> then_(json => {
    Js.log(json);
    json |> Decoders.response |> (response => Some(response) |> resolve);
  })
  |> catch(_err => resolve(None))
);
