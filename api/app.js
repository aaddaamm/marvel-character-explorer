const express = require("express");
const cors = require('cors');
const bodyParser = require("body-parser");
const routes = require("./routes/routes.js");
const app = express();

app.use(bodyParser.json());
app.use(bodyParser.urlencoded({ extended: true }));
app.use(cors());

routes(app);

const server = app.listen(5001, function () {
    console.log("api running on port.", server.address().port);
});