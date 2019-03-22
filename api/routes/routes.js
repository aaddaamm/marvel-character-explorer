const usersController = require("../controllers/usersController");

const router = function (app) {
  app.get("/users", usersController.getUsers);
  app.get("/user", usersController.getUser);
}

module.exports = router;