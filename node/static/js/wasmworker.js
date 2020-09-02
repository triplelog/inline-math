importScripts('wasmhello.js');
importScripts('katex.min.js');
var l = Module.cwrap("LatexIt","string",["string"]);
var p = Module.cwrap("PlotIt","string",["string","number","number","number","number"]);
var a = Module.cwrap("AddRules","string",["string","string"]);

var latex = "";
function addLatex(x) {
	latex += x;
}
	
var svg = "";
function addSVG(x) {
	svg += x;
}

var varMap = {};

importScripts('marked.js');

const renderer = {
  codespan(text) {
	//const escapedText = text.toLowerCase().replace(/[^\w]+/g, '-');
	var match = text.match(/\$+([^\$\n]+?)\$+/);
	var matchPlot = text.match(/\$+([^\$\n]+?)\$p+/);
	var matchInput = text.match(/\$+([^\$\n]+?)\$i+/);
	if (matchPlot && matchPlot.index == 0){
		svg = "<span>";
		p(match[1].trim(),-10,10,-10,10);
		svg += '<br><input type="range" id="domainSlider" min="0" max="'+(20*2)+'" value="'+20+'"></input>';
		svg += '</span>';

		return svg;
	}
	else if (matchInput && matchInput.index == 0){
		var html = '<input type="text" id="inline-A">';
		html += match[1].trim();
		html += '</input>';
		html += '<script>document.getElementById("inline-A").addEventListener();</script>';
		
		return html;
	}
	else if (match && match.index == 0){
		latex = "";
		l(match[1].trim());
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
		var markdown = message[1];
		markdown = markdown.replace(/\$+([^\$\n]+?)\$i+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$p+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,'`$&`');
		markdown = markdown.replace(/``\$/g,'`$');
		markdown = markdown.replace(/\$`p`/g,'$p`');
		markdown = markdown.replace(/\$`i`/g,'$i`');
		var html = marked(markdown);
		result = ["markdown",message[1],html];
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