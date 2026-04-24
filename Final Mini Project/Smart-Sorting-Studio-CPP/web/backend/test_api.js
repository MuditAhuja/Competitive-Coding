const http = require('http');

const req = http.request({
  hostname: 'localhost',
  port: 3001,
  path: '/api/sort',
  method: 'POST',
  headers: {
    'Content-Type': 'application/json',
  }
}, (res) => {
  let data = '';
  res.on('data', (chunk) => data += chunk);
  res.on('end', () => console.log(data));
});

req.write(JSON.stringify({ dataset: "1", algorithm: "1" }));
req.end();
