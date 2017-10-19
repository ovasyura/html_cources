var express = require('express');
var morgan = require('morgan');
var bodyParser = require('body-parser');
var dish_Router = require('./dishRouter');
var leader_Router = require('./leaderRouter');
var promotion_router = require('./promoRouter');

var hostname = 'localhost';
var port = 3000;

var app = express();

app.use(morgan('dev'));

app.use('/dishes',dish_Router.dishRouter(express, bodyParser));
app.use('/leadership',leader_Router.leaderRouter(express, bodyParser));
app.use('/promotions',promotion_router.promoRouter(express, bodyParser));

app.use(express.static(__dirname + '/public'));

app.listen(port, hostname, function(){
  console.log(`Server running at http://${hostname}:${port}/`);
});
