var addon = require('./index');

console.log(addon.parseDicom(
  process.argv[2]
));
