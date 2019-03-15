const usersController = require("../controllers/usersController");

const router = function (app) {
  app.get("/", function(req, res) {
    res.status(200).send("Welcome to our restful API");
  });
  app.get("/users", usersController.getUsers);
}

module.exports = router;