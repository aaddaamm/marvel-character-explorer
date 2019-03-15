const faker = require("faker");

const getUsers = (req, res) => {
  const users = [];

  for (i = 0; i < 50; i++) {
    users.push({
      id: i+1,
      firstName: faker.name.firstName(),
      lastName: faker.name.lastName(),
      username: faker.internet.userName(),
      email: faker.internet.email()
    });
  };

  res.status(200).send(users);
}

module.exports = {
  getUsers,
};