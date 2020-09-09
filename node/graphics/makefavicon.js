var fs = require("fs");
var svg = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"-100 -100 100 100\" width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">";

for (var i=0;i<100;i++){
	for (var ii=0;ii<100;ii++){
		var r = .2;
		if (i%2==0){
			r*=2;
		}
		if (ii%2==0){
			r*=2;
		}
		if (i%4==0){
			r*=2;
		}
		if (ii%4==0){
			r*=2;
		}
		svg += "<circle cx=\"" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"red\"/>";
		svg += "<circle cx=\"" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"red\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"" + ii + "\" r=\""+r+"\" fill=\"red\"/>";
		svg += "<circle cx=\"-" + i + "\" cy=\"-" + ii + "\" r=\""+r+"\" fill=\"red\"/>";
	}
}
svg += "</svg>";
fs.writeFileSync("../static/favicon.html", svg);