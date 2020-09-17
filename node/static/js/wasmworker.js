
function cpp_ready() {
	postMessage("ready");
}
importScripts('wasmhello.js');
importScripts('katex.min.js');
importScripts('conversions.js');
var lcpp = Module.cwrap("LatexIt","string",["string"]);
var pcpp = Module.cwrap("PlotIt","string",["string","number","number","number","number"]);
var tcpp = Module.cwrap("TreeIt","string",["string"]);



function ljs(input){
	lcpp(input);
}
function pjs(input0,input1,input2,input3,input4){
	pcpp(input0,input1,input2,input3,input4);
}
function tjs(input){
	tcpp(input);
}

var latex = "";
function addLatex(x) {
	latex += x;
}

var inputted = "";
function addInputted(x) {
	inputted += x;
}

var svg = "";
function addSVG(x) {
	svg += x;
}

var dependents = "";
function setDependents(x) {
	dependents = x;
}
var dependentfunctions = [];
function addDependentFunction(x) {
	console.log(x);
	dependentfunctions.push(x);
}

var currentF = {};
function updateCurrentFunctions(x) {
	const y = Date.now();
	currentF[x]=y;
}

var latexedInputs = {};
var currentV = {};

var inputV = {};
var plotid = 0;
importScripts('marked.js');


var katexOptions = {throwOnError: false, macros: {'\\pluseq':'\\mathrel{{+}{=}}','\\minuseq':'\\mathrel{{-}{=}}'}};

function mapOrNew(input,varName,forceNew=false,isTreePlot=false,isDisplay=false){
	latex = "";
	dependentfunctions = [];
	var type = 'latex';
	if (isTreePlot == 'tree'){
		type = 'tree';
	}
	else if (isTreePlot == 'plot'){
		type = 'plot';
		inputFull = [];
		for (var i=0;i<5;i++){
			inputFull.push(input[i]);
		}
		input = inputFull[0];
		svg = "";
	}
	var foundMatch = false;
	
	if (latexedInputs[type+input]){
		foundMatch = true;
		if (latexedInputs[type+input].varName != varName){
			foundMatch = false;
		}
		else if (latexedInputs[type+input].display != isDisplay){
			foundMatch = false;
		}
		else if (latexedInputs[type+input].dependents || latexedInputs[type+input].dependentfunctions){
			if (latexedInputs[type+input].dependents){
				for (var i in latexedInputs[type+input].dependents){
					if (latexedInputs[type+input].dependents[i] != currentV[i]){
						foundMatch = false;
						break;
					}
				}
			}
			if (latexedInputs[type+input].dependentfunctions){
				for (var i in latexedInputs[type+input].dependentfunctions){
					if (latexedInputs[type+input].dependentfunctions[i] != currentF[i]){
						foundMatch = false;
						break;
					}
				}
			}
		}
		if (isTreePlot == 'plot'){
			for (var i=0;i<5;i++){
				if (latexedInputs[type+input].options.dr[i] != inputFull[i]) {
					foundMatch = false;
					break;
				}
			}
		}
		
	}
	var k;
	if (foundMatch && !forceNew){
		latex = latexedInputs[type+input].latex;
		k = latexedInputs[type+input].output;
	}
	else{
		if (varName != ""){
			if (isTreePlot == 'tree'){
				tjs("|"+varName+":="+input);
				latex = latex.replace(/\\/g,'\\\\');
				var tree;
				if (latex == "???"){
					tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
				}
				else {
					try {
						tree = JSON.parse('{'+latex+'}');
					}
					catch(err){
						tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
					}
				}
				var outText = "";
				for (var i=0;i<tree.allNodes.length;i++){
					var node = tree.allNodes[i];
					var text = tree.nodes[node].text;
					katexOptions.displayMode = isDisplay;
					k = katex.renderToString(text, katexOptions);
					katexOptions.displayMode = false;
					outText += "<node id=\""+node+"\">"+k+"</node>";
					tree.nodes[node].text = "";

				}
				outText += JSON.stringify(tree);
				k = outText;
			}
			//else if (isTreePlot == 'plot'){
			//	pjs(inputFull[0],inputFull[1],inputFull[2],inputFull[3],inputFull[4]);
			//}
			else {
				inputted = "";
				ljs("|"+varName+":="+input);
				katexOptions.displayMode = isDisplay;
				k = katex.renderToString(latex, katexOptions);
				katexOptions.displayMode = false;
				k = k.replace('class="katex"','class="katex" data-input="'+inputted+'" data-latex="'+latex+'"');
			}
			
		}
		else{
			if (isTreePlot == 'tree'){
				tjs(input);
				latex = latex.replace(/\\/g,'\\\\');
				var tree;
				if (latex == "???"){
					tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
				}
				else {
					try {
						tree = JSON.parse('{'+latex+'}');
					}
					catch(err){
						tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
					}
				}
				var outText = "";
				for (var i=0;i<tree.allNodes.length;i++){
					var node = tree.allNodes[i];
					var text = tree.nodes[node].text;
					katexOptions.displayMode = isDisplay;
					k = katex.renderToString(text, katexOptions);
					katexOptions.displayMode = false;
					outText += "<node id=\""+node+"\">"+k+"</node>";
					tree.nodes[node].text = "";

				}
				outText += JSON.stringify(tree);
				k = outText;
			}
			else if (isTreePlot == 'plot'){
				inputted = "";
				pjs(inputFull[0],inputFull[1],inputFull[2],inputFull[3],inputFull[4]);
				if (svg == "???"){
					latex = "";
					k = "";
				}
				else {
					latex = inputted;
					k = svg;
				}
			}
			else {
				inputted = "";
				ljs(input);
				katexOptions.displayMode = isDisplay;
				k = katex.renderToString(latex, katexOptions);
				katexOptions.displayMode = false;
				k = k.replace('class="katex"','class="katex" data-input="'+inputted+'" data-latex="'+latex+'"');
			}
			
		}
		latexedInputs[type+input]={dependents:{},dependentfunctions:{},output:k,varName:varName,latex:latex,display:isDisplay,options:{}};
		for (var i=0;i<dependents.length;i++){
			latexedInputs[type+input].dependents[dependents[i]] = currentV[dependents[i]];
		}
		for (var i=0;i<dependentfunctions.length;i++){
			latexedInputs[type+input].dependentfunctions[dependentfunctions[i]] = currentF[dependentfunctions[i]];
		}
		if (isTreePlot == 'plot'){
			latexedInputs[type+input].options.dr = inputFull; 
		}
		
	}
	return k;
}

function createInputs(input,varName,isDisplay) {
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
				k = mapOrNew(options[i],"",false,false,isDisplay);
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
		html += '<label for="inline-'+varName+'">'+input+'</label>';
		html += '<input type="text" class="inline-input" name="inline-'+varName+'" value="'+defaultValue+'" id="inline-'+varName+'"></input>';

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
		html += '<input type="number" class="inline-input" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'"></input>';

	}
	else if (input.search(/range\(/)==0){
		input = input.replace('range(','');
		input = input.substr(0,input.length-1);
		var minRange = "0";
		var maxRange = "100";
		var options = input.split(',');
		if (options.length>1){
			minRange = options[0];
			maxRange = options[1];
		}
		defaultValue = Math.floor((parseInt(maxRange) + parseInt(minRange) + 1) / 2);
		
		if (inputV[varName]){
			defaultValue = inputV[varName];
		}
		
		html += '<input type="range" class="inline-input" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'"></input>';

	}
	if (varName != ""){
		if (!inputV[varName]){
			inputV[varName]=defaultValue;
			var j = mapOrNew(defaultValue,varName,true,false,isDisplay);
			currentV[varName]=j;
		}
		else {
			var j = mapOrNew(inputV[varName],varName,true,false,isDisplay);
			currentV[varName]=j;
		}
	}
	return html;
}

const renderer = {
  code(code, infostring, escaped) {
  	code = code.replace(/&lt;/g,'<');
  	code = code.replace(/&gt;/g,'>');
  	if (!infostring || infostring.trim() == ''){
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	else if (infostring.trim() == 'javascript' || infostring.trim() == 'js'){
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	else if (infostring.trim() == 'python' || infostring.trim() == 'py'){
  		return '<pre><code class="language-python">'+code+'</code></pre>';
  	}
  	else {
  		return '<pre><code class="language-js">'+code+'</code></pre>';
  	}
  	
  },
  codespan(text) {
  	text = text.replace(/&lt;/g,'<');
  	text = text.replace(/&gt;/g,'>');
  	text = text.replace(/=([^\( =])/g,'= '+'$1');
  	text = text.replace(/!([^\=])/g,'!!'+'$1');
  	text = text.replace(/!$/,'!!');
  	try{
		var matchDisplay = text.match(/\$\$+([^\$\n]+?)\$\$+/);
		var match = text.match(/\$+([^\$\n]+?)\$+/);
		var matchUpper = text.match(/\$+([^\$\n]+?)\$\[[A-Z]\]+/);
		var matchInvisible = text.match(/\$+([^\$\n]+?)\$!!\[[A-Z]\]+/);
	
		var isDisplay = false;
		if (matchDisplay && matchDisplay.index == 0){
			match = text.match(/\$\$+([^\$\n]+?)\$\$+/);
			matchUpper = text.match(/\$\$+([^\$\n]+?)\$\$\[[A-Z]\]+/);
			matchInvisible = text.match(/\$\$+([^\$\n]+?)\$\$!!\[[A-Z]\]+/);
			isDisplay = true;
		}
	
		var varName = "";
		if (matchUpper && matchUpper.index == 0){
			varName = matchUpper[0][matchUpper[0].length-2];
		}
		else if (matchInvisible && matchInvisible.index == 0){
			varName = matchInvisible[0][matchInvisible[0].length-2];
		}
		else {
		}
		matchInvisible = text.match(/\$+([^\$\n]+?)\$!!+/);
		if (matchDisplay && matchDisplay.index == 0){
			matchInvisible = text.match(/\$\$+([^\$\n]+?)\$\$!!+/);
		}
	
	
		if (match && match.index == 0){
	
		}
		else {
			return '<pre><code class="language-js">'+text+'</code></pre>';
		}
	
		var input = match[1].trim();
		if (input.search(/plot\(/)==0){
			input = input.replace('plot(','');
			var dr = input.split(')');
			if (dr.length>1){
				input = dr.slice(0,dr.length-1).join(')');
				dr = dr[dr.length-1].replace('[','').replace(']','');
			}
			else {
				input = dr.join(')');
				dr = "";
			}
			var inputs = input.split(',');
			var fn = inputs[0];
			var left = -10;
			var right = 10;
			var bottom = -10;
			var top = 10;
			
			if (inputs.length > 1){
				left = parseInt(inputs[1]);
				if (isNaN(left)){
					left = -10;
				}
				if (inputs.length>2){
					right = parseInt(inputs[2]);
					if (isNaN(right)){
						right = 10;
					}
					
					if (inputs.length>3){
						bottom = parseInt(inputs[3]);
						if (isNaN(bottom)){
							bottom = -10;
						}
						if (inputs.length>4){
							top = parseInt(inputs[4]);
							if (isNaN(top)){
								top = 10;
							}
							
						}
					}
				}
			}
			if (right <= left){
				right = left + 20;
			}
			if (top <= bottom){
				top = bottom + 20;
			}
			
			if (isDisplay){
				svg = '<div class="plotDiv" data-sliders="'+dr+'" id="plot-'+plotid+'" data-formula="'+fn+'" data-left="'+left+'" data-right="'+right+'" data-bottom="'+bottom+'" data-top="'+top+'" >';
				svg += '</div>';
			}
			else {
				svg = '<span class="plotSpan" data-sliders="'+dr+'" id="plot-'+plotid+'" data-formula="'+fn+'" data-left="'+left+'" data-right="'+right+'" data-bottom="'+bottom+'" data-top="'+top+'" >';
				svg += '</span>';
			}
			plotid++;
			
			return svg;
		}
		else if (input.search(/tree\(/)==0){
			input = input.replace('tree(','');
			input = input.substr(0,input.length-1);
			//latex = "";
			var outText = mapOrNew(input,varName,false,'tree',true);
		
			return '<span class="inline-tree">'+outText+'</span>';
		}
		else if (input.search(/align\(/)==0){
			input = input.replace('align(','');
			var aligners = ["="];
			if (input[input.length-1] == ']'){
				var alignSplit = input.split('[');
				var aSplit = alignSplit[alignSplit.length-1];
				aSplit = aSplit.substr(0,aSplit.length-1);
				aligners = aSplit.split(',');
				input = input.split(')');
				input = input.slice(0,input.length-1);
				input = input.join(')');
			}
			else {
				input = input.substr(0,input.length-1);
			}
		
			var inputs = input.split(',');
			var outText = '\\begin{aligned}\n';
			if (aligners.length>1){
				outText = '\\begin{alignedat}{'+(aligners.length*2)+'}\n';
			}
			for (var i=0;i<inputs.length;i++){
				var inp = inputs[i].trim();
				if (inp.length > 0){
					mapOrNew(inputs[i].trim(),"",false,false,isDisplay);
					for (var ii=0;ii<aligners.length;ii++){
						latex = latex.replace(aligners[ii],'&'+aligners[ii]+'&');
					}
				
					outText += latex + "\\\\\n";
				}
			
			}
			if (aligners.length>1){
				outText += "\\end{alignedat}";
			}
			else {
				outText += "\\end{aligned}";
			}
		
			console.log(outText);
			katexOptions.displayMode = true;
			k = katex.renderToString(outText, katexOptions);
			k = k.replace('class="katex"','class="katex" data-input="'+input+'" data-latex="'+outText+'"');
			katexOptions.displayMode = false;
			return k;
		}
		else if (input.search(/checkbox\(/)==0 || input.search(/radio\(/)==0 || input.search(/input\(/)==0 || input.search(/number\(/)==0 || input.search(/range\(/)==0){
			var html = createInputs(input,varName,isDisplay);
			//html += '<script>document.getElementById("inline-A").addEventListener();</script>';
	
			return html;
		}
		else if (input.search(/display\(/)==0){
			input = input.replace('display(','');
			input = input.substr(0,input.length-1);
			
			katexOptions.displayMode = isDisplay;
			k = katex.renderToString(input, katexOptions);
			katexOptions.displayMode = false;
			k = k.replace('class="katex"','class="katex" data-input="" data-latex="'+input+'"');
		
			return k;
		}
		else if (input.search(/latex\(/)==0){
			input = input.replace('latex(','');
			input = input.substr(0,input.length-1);
			//latex = "";
			var k = mapOrNew(input,varName,false,false,isDisplay);
			if (isDisplay){
				return '<div>'+latex+'</div>';
			}
			else {
				return '<span>'+latex+'</span>';
			}
			
		}
		else {
			k = mapOrNew(input,varName,false,false,isDisplay);
			if (varName != ""){
				currentV[varName]=k;
			}
			if (matchInvisible && matchInvisible.index == 0){
				return "";
			}
			return k;
		}
	}
	catch(err){
		return text;
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
		markdown = markdown.replace(/\$\$+([^\$\n]+?)\$\$\[[A-Z]\]+/g,'`$&`');
		markdown = markdown.replace(/\$\$+([^\$\n]+?)\$\$!\[[A-Z]\]+/g,'`$&`');
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,'`$&`');
		
		markdown = markdown.replace(/``\$/g,'`$');
		markdown = markdown.replace(/\$``/g,'$`');
		markdown = markdown.replace(/\$`\[[A-Z]\]`/g,replacer);
		markdown = markdown.replace(/\$`!\[[A-Z]\]`/g,replacer);
		markdown = markdown.replace(/\$`!/g,'$&`');
		markdown = markdown.replace(/\$`!/g,replacer);

		plotid = 0;
		var html;
		try {
			html = marked(markdown);
		}
		catch(err){
			html = "";
		}
		result = ["markdown",message[1],html];
	}
	else if (message[0] == "code"){
		var input;
		message[1] = message[1].replace(/&lt;/g,'<');
  		message[1] = message[1].replace(/&gt;/g,'>');
		if (message[3] == 'js'){
			input = jsToMath(message[1]);
		}
		else if (message[3] == 'python'){
			input = pythonToMath(message[1]);
		}
		else {
			input = jsToMath(message[1]);
		}
		k = mapOrNew(input,"",false,false,false);
		result = ["code",message[1],k,message[2],latex,message[3]];
	}
	else if (message[0] == "plot"){
		
		//pjs(message[1],message[3],message[4],message[5],message[6]);
		k = mapOrNew([message[1],message[3],message[4],message[5],message[6]],"",false,'plot',false);
		svg = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">";
		svg += k;
		svg += "</svg>";
		if (message[9].search('D')>-1){
			svg += '<br><input type="range" data-formula="'+message[1]+'" id="domainSlider-'+message[2]+'" min="0" max="'+(message[7]*2)+'" value="'+message[7]+'"></input>';	
		}
		if (message[9].search('R')>-1){
			svg += '<br><input type="range" data-formula="'+message[1]+'" id="rangeSlider-'+message[2]+'" min="0" max="'+(message[8]*2)+'" value="'+message[8]+'"></input>';	
		}
		result = ["svg",message[1],svg,message[2]];
	}
	else if (message[0] == "inputValue"){
		inputV[message[1]]=message[2];
	}
	postMessage(result);
}