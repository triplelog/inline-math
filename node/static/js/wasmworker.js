
function cpp_ready() {
	postMessage("ready");
}
importScripts('wasmhello.js');
importScripts('katex.min.js');
importScripts('conversions.js');
var l = Module.cwrap("LatexIt","string",["string"]);
var p = Module.cwrap("PlotIt","string",["string","number","number","number","number"]);
var a = Module.cwrap("AddRules","string",["string","string"]);
var t = Module.cwrap("TreeIt","string",["string"]);

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
var inputV = {};
importScripts('marked.js');

function mapOrNew(input,varName,forceNew=false,isTree=false){
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
	if (foundMatch && !forceNew){
		latex = latexedInputs[input].latex;
		k = latexedInputs[input].output;
	}
	else{
		if (varName != ""){
			if (isTree){
				t("|"+varName+":="+input);
				latex = latex.replace(/\\/g,'\\\\');
				var tree = JSON.parse('{'+latex+'}');
				var outText = "";
				for (var i=0;i<tree.allNodes.length;i++){
					var node = tree.allNodes[i];
					var text = tree.nodes[node].text;
					k = katex.renderToString(text, {throwOnError: false});
					outText += "<node id=\""+node+"\">"+k+"</node>";
					tree.nodes[node].text = "";

				}
				outText += JSON.stringify(tree);
				k = outText;
			}
			else {
				l("|"+varName+":="+input);
				k = katex.renderToString(latex, {throwOnError: false});
			}
			
		}
		else{
			if (isTree){
				t(input);
				latex = latex.replace(/\\/g,'\\\\');
				var tree = JSON.parse('{'+latex+'}');
				var outText = "";
				for (var i=0;i<tree.allNodes.length;i++){
					var node = tree.allNodes[i];
					var text = tree.nodes[node].text;
					k = katex.renderToString(text, {throwOnError: false});
					outText += "<node id=\""+node+"\">"+k+"</node>";
					tree.nodes[node].text = "";

				}
				outText += JSON.stringify(tree);
				k = outText;
			}
			else {
				l(input);
				latex = latex.replace('\\\\','\\');
				console.log("latexed",latex);
				latex = latex.replace('\\','|');
				console.log("latexed",latex);
				k = katex.renderToString(latex, {throwOnError: false});
				//console.log("katexed",k);
			}
			
		}
		latexedInputs[input]={dependents:{},output:k,varName:varName,latex:latex};
		for (var i=0;i<dependents.length;i++){
			latexedInputs[input].dependents[dependents[i]] = currentV[dependents[i]];
		}
		
	}
	return k;
}

function createInputs(input,varName) {
	var html = "";
	var defaultValue = "";
	if (input.search(/checkbox\(/)==0){
		input = input.replace('checkbox(','');
		input = input.substr(0,input.length-1);
		var options = input.split(',');
		var dataYes = "true";
		var dataNo = "false";
		if (options.length>1){
			dataYes = options[0];
			dataNo = options[1];
		}
		else if (options.length == 1){
			dataYes = options[0];
		}
		
		
		defaultValue = dataYes;
		if (inputV[varName]){
			if (inputV[varName] == dataYes){
				selected = "checked";
			}
			else if (inputV[varName] == dataNo){
				selected = "";
			}
			else {
				selected = "checked";
			}
		}
		else {
			selected = "checked";
		}
		//html += '<label for="inline-'+varName+'">'+k+'</label>';
		html += '<input type="checkbox" class="inline-checkbox" name="inline-'+varName+'" data-no="'+dataNo+'" data-yes="'+dataYes+'" id="inline-'+varName+'" '+selected+'></input>';

	}
	else if (input.search(/radio\(/)==0){
		input = input.replace('radio(','');
		input = input.substr(0,input.length-1);
		var options = input.split(',');
		defaultValue = options[0];
		for (var i=0;i<options.length;i++){
			if (options[i] != ""){
				k = mapOrNew(options[i],"");
				var selected = "";
				if (inputV[varName]){
					if (inputV[varName] == options[i]){selected = "checked";}
				}
				else {
					if (defaultValue == options[i]){selected = "checked";}
				}
				html += '<label for="inline-'+varName+'-'+i+'">'+k+'</label>';
				html += '<input type="radio" class="inline-radio" name="inline-'+varName+'" value="'+options[i]+'" id="inline-'+varName+'-'+i+'" '+selected+'></input>';
			}
		}
	}
	else if (input.search(/input\(/)==0){
		input = input.replace('input(','');
		input = input.substr(0,input.length-1);
		defaultValue = "";
		
		if (inputV[varName]){
			defaultValue = inputV[varName];
		}
		html += '<label for="inline-'+varName+'-'+i+'">'+input+'</label>';
		html += '<input type="text" class="inline-input" name="inline-'+varName+'" value="'+defaultValue+'" id="inline-'+varName+'-'+i+'"></input>';

	}
	else if (input.search(/number\(/)==0){
		input = input.replace('number(','');
		input = input.substr(0,input.length-1);
		var minRange = "0";
		var maxRange = "100";
		var options = input.split(',');
		if (options.length>1){
			minRange = options[0];
			maxRange = options[1];
		}
		defaultValue = "50";
		
		if (inputV[varName]){
			defaultValue = inputV[varName];
		}
		html += '<input type="number" class="inline-input" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'-'+i+'"></input>';

	}
	else if (input.search(/range\(/)==0){
		input = input.replace('number(','');
		input = input.substr(0,input.length-1);
		var minRange = "0";
		var maxRange = "100";
		var options = input.split(',');
		if (options.length>1){
			minRange = options[0];
			maxRange = options[1];
		}
		defaultValue = "50";
		
		if (inputV[varName]){
			defaultValue = inputV[varName];
		}
		
		html += '<input type="range" class="inline-input" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'-'+i+'"></input>';

	}
	if (varName != ""){
		if (!inputV[varName]){
			inputV[varName]=defaultValue;
			var j = mapOrNew(defaultValue,varName,true);
			currentV[varName]=j;
		}
		else {
			var j = mapOrNew(inputV[varName],varName,true);
			currentV[varName]=j;
		}
	}
	return html;
}

const renderer = {
  code(code, infostring, escaped) {
  	if (!infostring || infostring.trim() == ''){
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	else if (infostring.trim() == 'javascript' || infostring.trim() == 'js'){
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	else if (infostring.trim() == 'python' || infostring.trim() == 'py'){
  		console.log('<pre><code class="language-python">'+code+'</code></pre>');
  		return '<pre><code class="language-python">'+code+'</code></pre>';
  	}
  	else {
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	
  },
  codespan(text) {
	//const escapedText = text.toLowerCase().replace(/[^\w]+/g, '-');
	var match = text.match(/\$+([^\$\n]+?)\$+/);
	var matchUpper = text.match(/\$+([^\$\n]+?)\$\[[A-Z]\]+/);
	var matchInvisible = text.match(/\$+([^\$\n]+?)\$!\[[A-Z]\]+/);
	var varName = "";
	if (matchUpper && matchUpper.index == 0){
		varName = matchUpper[0][matchUpper[0].length-2];
	}
	else if (matchInvisible && matchInvisible.index == 0){
		varName = matchInvisible[0][matchInvisible[0].length-2];
		console.log(varName);
	}
	matchInvisible = text.match(/\$+([^\$\n]+?)\$!+/);
	
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
	else if (input.search(/tree\(/)==0){
		input = input.replace('tree(','');
		input = input.substr(0,input.length-1);
		//latex = "";
		var outText = mapOrNew(input,varName,false,true);
		
		return '<span class="inline-tree">'+outText+'</span>';
	}
	else if (input.search(/checkbox\(/)==0 || input.search(/radio\(/)==0 || input.search(/input\(/)==0 || input.search(/number\(/)==0 || input.search(/range\(/)==0){
		var html = createInputs(input,varName);
		//html += '<script>document.getElementById("inline-A").addEventListener();</script>';
	
		return html;
	}
	else {
		k = mapOrNew(input,varName);
		if (varName != ""){
			currentV[varName]=k;
		}
		if (matchInvisible && matchInvisible.index == 0){
			console.log(k);
			return "";
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
		markdown = markdown.replace(/\$+([^\$\n]+?)\$!\[[A-Z]\]+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,'`$&`');
		markdown = markdown.replace(/``\$/g,'`$');
		markdown = markdown.replace(/\$`\[[A-Z]\]`/g,replacer);
		markdown = markdown.replace(/\$`!\[[A-Z]\]`/g,replacer);
		markdown = markdown.replace(/\$`!/g,'$&`');
		markdown = markdown.replace(/\$`!/g,replacer);
		var html = marked(markdown);
		result = ["markdown",message[1],html];
	}
	else if (message[0] == "code"){
		var input;
		if (message[3] == 'js'){
			input = jsToMath(message[1]);
		}
		else if (message[3] == 'python'){
			input = pythonToMath(message[1]);
			console.log(input);
		}
		else {
			input = jsToMath(message[1]);
		}
		k = mapOrNew(input,"");
		result = ["code",message[1],k,message[2],latex,message[3]];
	}
	else if (message[0] == "latex"){
		var input = message[1];
		k = mapOrNew(input,"");
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
	else if (message[0] == "inputValue"){
		inputV[message[1]]=message[2];
	}
	postMessage(result);
}