const express = require('express');
const request = require('request');
const cors = require('cors')
const app = express();

app.use(cors());
app.use(express.json());

app.use('/', (req, res) => {
  const url = 'https://todo.doczilla.pro' + req.url;
  req.pipe(request({ url, qs: req.query, method: req.method })).pipe(res);
});

app.listen(3000, () => {
  console.log('Proxy server is running on http://localhost:3000');
});