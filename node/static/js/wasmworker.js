importScripts('wasmhello.js');
importScripts('katex.min.js');
importScripts('conversions.js');
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
		console.log(latex);
		k = katex.renderToString(latex, {throwOnError: false});
		latexedInputs[input]={dependents:{},output:k,varName:varName,latex:latex};
		for (var i=0;i<dependents.length;i++){
			latexedInputs[input].dependents[dependents[i]] = currentV[dependents[i]];
		}
		
	}
	
	return k;
}

function createInputs(input,varName) {
	var html = "";
	if (input.search(/checkbox\(/)==0){
		input = input.replace('checkbox(','');
		input = input.substr(0,input.length-1);
		var options = input.split(',');
		
		for (var i=0;i<options.length;i++){
			if (options[i] != ""){
				k = mapOrNew(options[i],"");
				html += '<label for="inline-'+varName+'-'+i+'">'+k+'</label>';
				html += '<input type="checkbox" name="inline-'+varName+'" id="inline-'+varName+'-'+i+'"></input>';
			}
		}
	}
	else if (input.search(/radio\(/)==0){
		input = input.replace('radio(','');
		input = input.substr(0,input.length-1);
		var options = input.split(',');
		
		for (var i=0;i<options.length;i++){
			if (options[i] != ""){
				k = mapOrNew(options[i],"");
				html += '<label for="inline-'+varName+'-'+i+'">'+k+'</label>';
				html += '<input type="radio" name="inline-'+varName+'" id="inline-'+varName+'-'+i+'"></input>';
			}
		}
	}
	return html;
}

const renderer = {
  code(code, infostring, escaped) {
  	console.log(infostring);
  	return '<pre><code class="language-js">'+code+'</code></pre>';
  },
  codespan(text) {
	//const escapedText = text.toLowerCase().replace(/[^\w]+/g, '-');
	var match = text.match(/\$+([^\$\n]+?)\$+/);
	var matchUpper = text.match(/\$+([^\$\n]+?)\$\[[A-Z]\]+/);
	var varName = "";
	if (matchUpper && matchUpper.index == 0){
		varName = matchUpper[0][matchUpper[0].length-2];
	}
	
	if (match && match.index == 0){
	
	}
	else {
		return '<pre><code class="language-js">'+text+'</code></pre>';
	}
	
	var input = match[1].trim();
	if (input.search(/plot\(/)==0){
		input = input.replace('plot(','');
		input = input.substr(0,input.length-1);
		svg = "<span>";
		p(input,-10,10,-10,10);
		svg += '<br><input type="range" id="domainSlider" min="0" max="'+(20*2)+'" value="'+20+'"></input>';
		svg += '</span>';

		return svg;
	}
	else if (input.search(/checkbox\(/)==0 || input.search(/radio\(/)==0){
		var html = createInputs(input,varName);
		//html += '<script>document.getElementById("inline-A").addEventListener();</script>';
	
		return html;
	}
	else {
		k = mapOrNew(input,varName);
		if (varName != ""){
			currentV[varName]=k;
		}
		return k;
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
		markdown = markdown.replace(/\$+([^\$\n]+?)\$\[[A-Z]\]+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,'`$&`');
		markdown = markdown.replace(/``\$/g,'`$');
		markdown = markdown.replace(/\$`\[[A-Z]\]`/g,replacer);
		var html = marked(markdown);
		result = ["markdown",message[1],html];
	}
	else if (message[0] == "code"){
		var input = jsToMath(message[1]);
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