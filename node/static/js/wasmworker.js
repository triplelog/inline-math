importScripts('wasmhello.js');
var l = Module.cwrap("LatexIt","string",["string"]);
var p = Module.cwrap("PlotIt","string",["string","number","number","number"]);
var a = Module.cwrap("AddRules","string",["string","string"]);

var latex = "";
function addLatex(x) {
	latex += x;
}
	
var svg = "";
function addSVG(x) {
	svg += x;
}

importScripts('marked.js');
const renderer = {
  codespan(text) {
	//const escapedText = text.toLowerCase().replace(/[^\w]+/g, '-');
	var match = text.match(/\$+([^\$\n]+?)\$+/);
	if (match && match.index == 0){
		latex = "";
		l(match[1].trim();
		var k = katex.renderToString(latex, {throwOnError: false});
		return k;
	}
	else {
		return false;
	}
	
  }
};
marked.use({ renderer });
	



onmessage = function(e) {
	var message = e.data;
	var result = [];
	if (message[0] == "markdown"){
		var html = marked(message[1]);
		result = ["latex",message[1],html];
	}
	else if (message[0] == "latex"){
		latex = "";
		l(message[1]);
		result = ["latex",message[1],latex];
	}
	else if (message[0] == "plot"){
		svg = "";
		p(message[1],message[2],message[3],message[4],message[5]);
		svg += '<input type="range" id="domainSlider" min="0" max="'+(message[6]*2)+'" value="'+message[6]+'"></input>';
		result = ["svg",message[1],svg];
	}
	else if (message[0] == "rules"){
		a(message[1],message[2]);
		result = ["rules",message[1],"done"];
	}
	postMessage(result);
}