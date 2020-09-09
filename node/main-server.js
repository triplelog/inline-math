'use strict';
const { PerformanceObserver, performance } = require('perf_hooks');
var fs = require("fs");
const assert = require('assert');



const https = require('https');
var fs = require("fs");
var myParser = require("body-parser");
var qs = require('querystring');
const { exec } = require('child_process');
var nunjucks = require('nunjucks');
var crypto = require("crypto");

const options = {
  key: fs.readFileSync('/etc/letsencrypt/live/inlinemath.com/privkey.pem'),
  cert: fs.readFileSync('/etc/letsencrypt/live/inlinemath.com/fullchain.pem')
};





var express = require('express');
var app = express();
app.use('/',express.static('static'));


const server1 = https.createServer(options, app);

server1.listen(12312);

const server = https.createServer(options, (req, res) => {
  res.writeHead(200);
  res.end('\n');
}).listen(8081);

const WebSocket = require('ws');
//const wss = new WebSocket.Server({ port: 8080 , origin: 'http://tabdn.com'});
const wss = new WebSocket.Server({ server });
wss.on('connection', function connection(ws) {
	var username = '';
  	ws.on('message', function incoming(message) {
  		console.log(performance.now());
		var dm = JSON.parse(message);
		console.log(performance.now());
		if (dm.operation == 'key'){
			if (tempKeys[dm.message]){
				username = tempKeys[dm.message].username;
			}
		}
		
		
		
  	});
});

var startTime = performance.now();



app.get('/wasm',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/wasmblank.html',{

		}));
		res.end();
	}
);

app.get('/markdown',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/markdown.html',{

		}));
		res.end();
	}
);

app.get('/comprehensive',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/comprehensive.txt',{

		}));
		res.end();
	}
);

app.get('/clean',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/clean.txt',{

		}));
		res.end();
	}
);

app.get(['/','/index','/index.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/index.html',{

		}));
		res.end();
	}
);



