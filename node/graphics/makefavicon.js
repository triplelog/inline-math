var fs = require("fs");
var svg = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"-100 -100 100 100\" width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">";

for (var i=0;i<100;i++){
	for (var ii=0;ii<100;ii++){
		var r = .06;
		if (i%2==0){
			r*=1.5;
		}
		if (ii%2==0){
			r*=1.5;
		}
		if (i%4==0){
			r*=1.5;
		}
		if (ii%4==0){
			r*=1.5;
		}
		if (i%8==0){
			r*=1.5;
		}
		if (ii%8==0){
			r*=1.5;
		}
		if (i%16==0){
			r*=1.5;
		}
		if (ii%16==0){
			r*=1.5;
		}
		svg += "<circle cx=\"" + i + "\" cy=\"" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		svg += "<circle cx=\"" + i + "\" cy=\"-" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"-" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		
		svg += "<circle cx=\"" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
	}
}
svg += "</svg>";
fs.writeFileSync("../node/static/favicon.html", svg);


var svg = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"-128 -128 128 128\" width=\"600\" height=\"600\" xmlns=\"http://www.w3.org/2000/svg\">";

for (var i=0;i<129;i++){
	for (var ii=0;ii<129;ii++){
		var r = .06;
		if (i%2==0){
			r*=1.5;
		}
		if (ii%2==0){
			r*=1.5;
		}
		if (i%4==0){
			r*=1.3;
		}
		if (ii%4==0){
			r*=1.3;
		}
		if (i%8==0){
			r*=1.2;
		}
		if (ii%8==0){
			r*=1.2;
		}
		if (i%16==0){
			r*=1.1;
		}
		if (ii%16==0){
			r*=1.1;
		}
		//svg += "<circle cx=\"" + i + "\" cy=\"" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		//svg += "<circle cx=\"" + i + "\" cy=\"-" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		//svg += "<circle cx=\"-" + i + "\" cy=\"" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		//svg += "<circle cx=\"-" + i + "\" cy=\"-" + ii + "\" r=\""+(r*1.7)+"\" fill=\"#5381AC\"/>";
		
		svg += "<circle cx=\"" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"#AC6053\"/>";
	}
}
svg += "</svg>";
fs.writeFileSync("../node/static/bg.html", svg);



var svg = `<!DOCTYPE html>
<html>

<head>
  <meta charset="utf-8">
  <title></title>
  <meta name="author" content="">
  <meta name="description" content="">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" type="image/png" href="../img/fav.png">
  <style>
  	@font-face {
	  font-family: 'MyWebFont';
	  src: url('../img/Yatra_One/YatraOne-Regular.ttf');
	  src: url('../img/Yatra_One/YatraOne-Regular.ttf')  format('truetype');
	}
	body {
	  font-family: 'MyWebFont', Fallback, sans-serif;
	  background: #AC6053;
	}
  </style>
</head>

<body><svg version=\"1.1\" baseProfile=\"full\" width=\"600\" height=\"300\" xmlns=\"http://www.w3.org/2000/svg\">`;
svg += ``;
svg += `<text x="50" y="150" font-size="60px" fill="#5381AC">Inline</text>`;
svg += `<text x="195" y="120" font-size="60px" fill="#5381AC">math</text>`;
svg += "</svg></body></html";
fs.writeFileSync("../node/static/logo.html", svg);