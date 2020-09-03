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

var dependents = "";
function setDependents(x) {
	dependents = x;
}

var latexedInputs = {};
var currentV = {};

importScripts('marked.js');

function mapOrNew(input,varName=""){
	latex = "";
	
	var foundMatch = false;
	if (latexedInputs[input]){
		foundMatch = true;
		if (latexedInputs[input].varName != varName){
			foundMatch = false;
		}
		else if (latexedInputs[input].dependents){
			for (var i in latexedInputs[input].dependents){
				if (latexedInputs[input].dependents[i] != currentV[i]){
					foundMatch = false;
					break;
				}
			}
		}
		
	}
	var k;
	if (foundMatch){
		console.log(input);
		console.log(latexedInputs[input]);
		latex = latexedInputs[input].latex;
		k = latexedInputs[input].output;
	}
	else{
		console.log(varName, input);
		if (varName != ""){
			l("|"+varName+":="+input);
		}
		else {
			l(input);
		}
		
		k = katex.renderToString(latex, {throwOnError: false});
		latexedInputs[input]={dependents:{},output:k,varName:varName,latex:latex};
		for (var i=0;i<dependents.length;i++){
			latexedInputs[input].dependents[dependents[i]] = currentV[dependents[i]];
		}
		
	}
	
	return k;
}

const renderer = {
  code(code, infostring, escaped) {
  	console.log(infostring);
  	return '<pre><code class="language-js">'+code+'</code></pre>';
  },
  codespan(text) {
	//const escapedText = text.toLowerCase().replace(/[^\w]+/g, '-');
	var match = text.match(/\$+([^\$\n]+?)\$+/);
	var matchLower = text.match(/\$+([^\$\n]+?)\$[a-z]+/);
	var matchUpper = text.match(/\$+([^\$\n]+?)\$\[[A-Z]\]+/);
	if (matchLower && matchLower.index == 0){
		if (matchLower[0].search(/\$p/)>0){
			svg = "<span>";
			p(match[1].trim(),-10,10,-10,10);
			svg += '<br><input type="range" id="domainSlider" min="0" max="'+(20*2)+'" value="'+20+'"></input>';
			svg += '</span>';

			return svg;
		}
		else if (matchLower[0].search(/\$i/)>0){
			var html = '<input type="text" id="inline-A">';
			html += match[1].trim();
			html += '</input>';
			html += '<script>document.getElementById("inline-A").addEventListener();</script>';
		
			return html;
		}
		else {
		
		}
	}
	else if (matchUpper && matchUpper.index == 0){
		var varName = matchUpper[0][matchUpper[0].length-2];
		
		var input = match[1].trim();
		
		k = mapOrNew(input,varName);
		currentV[varName]=k;
		return k;
	}
	else if (match && match.index == 0){
		var input = match[1].trim();
		k = mapOrNew(input);
		return k;
	}
	else {
		return '<pre><code class="language-js">'+text+'</code></pre>';
	}
	
  }
};
marked.use({ renderer });
	


function replacer(match){
	match = match.replace('$`','$');
	return match;
}
onmessage = function(e) {
	var message = e.data;
	var result = [];
	if (message[0] == "markdown"){
		var markdown = message[1];
		markdown = markdown.replace(/\$+([^\$\n]+?)\$[a-z]+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$\[[A-Z]\]+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,'`$&`');
		markdown = markdown.replace(/``\$/g,'`$');
		markdown = markdown.replace(/\$`[a-z]`/g,replacer);
		markdown = markdown.replace(/\$`\[[A-Z]\]`/g,replacer);
		var html = marked(markdown);
		result = ["markdown",message[1],html];
	}
	else if (message[0] == "code"){
		var input = message[1];
		k = mapOrNew(input);
		result = ["code",message[1],k,message[2],latex];
	}
	else if (message[0] == "latex"){
		var input = message[1];
		k = mapOrNew(input);
		result = ["latex",message[1],k];
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