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
	}
  </style>
</head>

<body><svg version=\"1.1\" baseProfile=\"full\" viewBox=\"-100 -100 100 100\" width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">`;
svg += `<style>.inline { font: regular 40px MyWebFont;}</style>`;
svg += `<text x="0" y="0" class="inline">Inline</text>`;
svg += "</svg></body></html";
fs.writeFileSync("../node/static/logo.html", svg);