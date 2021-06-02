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

app.get('/trig',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/trig.txt',{

		}));
		res.end();
	}
);

app.get('/calculus',
	function(req, res){
		
		
		res.write(nunjucks.render('templates/calculus.txt',{

		}));
		res.end();
	}
);

app.get(['/plots','/plots.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/plots.txt',{

		}));
		res.end();
	}
);

app.get(['/trees','/trees.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/trees.txt',{

		}));
		res.end();
	}
);

app.get(['/latex','/latex.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/latex.txt',{

		}));
		res.end();
	}
);

app.get(['/code','/code.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/code.txt',{

		}));
		res.end();
	}
);

app.get(['/functions','/functions.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/functions.txt',{

		}));
		res.end();
	}
);

app.get(['/inputs','/inputs.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/inputs.txt',{

		}));
		res.end();
	}
);

app.get(['/overview','/overview.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/overview.txt',{

		}));
		res.end();
	}
);

app.get(['/variables','/variables.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/variables.txt',{

		}));
		res.end();
	}
);
app.get(['/partial','/partial.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/partial.txt',{

		}));
		res.end();
	}
);
app.get(['/solve','/solve.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/solve.txt',{

		}));
		res.end();
	}
);

app.get(['/mathtest','/mathtest.html'],
	function(req, res){
		
		
		res.write(nunjucks.render('templates/mathtest.html',{

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

app.get(['*'],
	function(req, res){
		

		res.redirect('../');
	}
);



