[@bs.deriving abstract]
type summaryItem = {
  resourceURI: option(string),
  name: option(string),
  type_: option(string),
  role: option(string)
};

type listItem = {
  available: option(int),
  returned: option(int),
  collectionURI: option(string),
  items: option(summaryItem)
};

type urlItem = {
  type_: option(string),
  url: option(string)
};

type imageItem = {
  path: string,
  extension: string,
};

type textItem = {
  type_: option(string),
  language: option(string),
  text: option(string)
};

type dateItem = {
  type_: option(string),
  date: option(Js.Date.t)
};

type priceItem = {
  type_: option(string),
  price: option(float),
};

type creatorSummaryItem = {
  resourceURI: option(string),
  name: option(string),
  role: option(string)
};

type character = {
  id: option(int),
  name: option(string),
  description: option(string),
  modified: option(Js.Date.t),
  resourceURI: option(string),
  urls: option(list(urlItem)),
  thumbnail: option(imageItem),
  comics: option(listItem),
  stories: option(listItem),
  events: option(listItem),
  series: option(listItem)
};

type comic = {
  id: option(int),
  digitalId: option(int),
  title: option(string),
  issueNumber: option(float),
  variantDescription: option(string),
  description: option(string),
  modified: option(Js.Date.t),
  isbn: option(string),
  upc: option(string),
  diamondCode: option(string),
  ean: option(string),
  issn: option(string),
  format: option(string),
  pageCount: option(int),
  textObjects: option(list(textItem)),
  resourceURI: option(string),
  urls: option(list(urlItem)),
  series: option(list(summaryItem)),
  variants: option(list(summaryItem)),
  collections: option(list(summaryItem)),
  collectedIssues: option(list(summaryItem)),
  dates: option(list(dateItem)),
  prices: option(list(priceItem)),
  thumbnail: option(imageItem),
  images: option(list(imageItem)),
  creators: option(listItem),
  characters: option(listItem),
  stories: option(listItem),
  events: option(listItem),
};

type characterResult = {
  name: string,
  id: int,
  modified: string,
  resourceURI: string,
  description: string,
  thumbnail: imageItem,
};

type dataContainer = {
   offset: int,
   limit: int,
   total: int,
   count: int,
   results: list(characterResult),
};

type responseWrapper = {
  code: int,
  status: string,
  copyright: string,
  attributionText: string,
  attributionHTML: string,
  etag: string,
  data: dataContainer,
};

type user = {
  id: int,
  firstName: string,
  lastName: string,
  username: string,
  email: string,
};
