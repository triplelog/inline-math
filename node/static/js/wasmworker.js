
function cpp_ready() {
	postMessage("ready");
}
importScripts('wasmhello.js');
importScripts('katex.min.js');
importScripts('conversions.js');
var lcpp = Module.cwrap("LatexIt","string",["string"]);
var ccpp = Module.cwrap("ImcssIt","string",["string"]);
var pcpp = Module.cwrap("PlotIt","string",["string","number","number","number","number"]);
var tcpp = Module.cwrap("TreeIt","string",["string"]);
var icpp = Module.cwrap("InputIt","string",["string"]);



function ljs(input){
	lcpp(input);
}
function cjs(input){
	ccpp(input);
}
function ijs(input){
	icpp(input);
}
function pjs(input0,input1,input2,input3,input4){
	pcpp(input0,input1,input2,input3,input4);
}
function tjs(input){
	tcpp(input);
}



var latex = {};
var imcss = {};
//var newInput = {};
var inputted = {};
var svg = {};
var dependents = {};
var dependentfunctions = {};
var currentF = {};
var latexedInputs = {};
var currentV = {};
var inputV = {};
var plotid = {};
var renderIdx = {};

function addId(id){
	latex[id] = "";
	imcss[id] = "";
	//newInput[id] = "";
	inputted[id] = "";
	svg[id] = "";
	dependents[id] = "";
	dependentfunctions[id] = [];
	currentF[id] = {};
	latexedInputs[id] = {};
	currentV[id] = {};
	inputV[id] = {};
	plotid[id] = 0;
	renderIdx[id] = 0;
	
	currentId = id;
}

function addLatex(x) {
	latex[currentId] += x;
}
function addImcss(x) {
	imcss[currentId] += x;
}
/*function addInput(x) {
	newInput[currentId] += x;
}*/
function addInputted(x) {
	inputted[currentId] += x;
}
function addSVG(x) {
	svg[currentId] += x;
}
function setDependents(x) {
	dependents[currentId] = x;
}

function addDependentFunction(x) {
	dependentfunctions[currentId].push(x);
}
function updateCurrentFunctions(x) {
	const y = Date.now();
	currentF[currentId][x]=y;
}


importScripts('marked.js');




var katexOptions = {throwOnError: false, macros: {'\\pluseq':'\\mathrel{{+}{=}}','\\minuseq':'\\mathrel{{-}{=}}'}};

function mapOrNew(input,varName,forceNew=false,isTreePlot=false,isDisplay=false){
	latex[currentId] = "";
	imcss[currentId] = "";
	dependentFunctions[currentId] = [];
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
		svg[currentId] = "";
	}
	var foundMatch = false;
	input = cleanInput(input);
	if (latexedInputs[currentId][type+input]){
		foundMatch = true;
		if (latexedInputs[currentId][type+input].varName != varName){
			foundMatch = false;
		}
		else if (latexedInputs[currentId][type+input].display != isDisplay){
			foundMatch = false;
		}
		else if (latexedInputs[currentId][type+input].dependents || latexedInputs[currentId][type+input].dependentfunctions){
			if (latexedInputs[currentId][type+input].dependents){
				for (var i in latexedInputs[currentId][type+input].dependents){
					if (latexedInputs[currentId][type+input].dependents[i] != currentV[currentId][i]){
						foundMatch = false;
						break;
					}
				}
			}
			if (latexedInputs[currentId][type+input].dependentfunctions){
				for (var i in latexedInputs[currentId][type+input].dependentfunctions){
					if (latexedInputs[currentId][type+input].dependentfunctions[i] != currentF[currentId][i]){
						foundMatch = false;
						break;
					}
				}
			}
		}
		if (isTreePlot == 'plot'){
			for (var i=0;i<5;i++){
				if (latexedInputs[currentId][type+input].options.dr[i] != inputFull[i]) {
					foundMatch = false;
					break;
				}
			}
		}
		
	}
	var k;
	if (foundMatch && !forceNew){
		inputted[currentId] = latexedInputs[currentId][type+input].inputted;
		latex[currentId] = latexedInputs[currentId][type+input].latex;
		imcss[currentId] = latexedInputs[currentId][type+input].imcss;
		k = latexedInputs[currentId][type+input].output;
	}
	else{
		if (varName != ""){
			if (isTreePlot == 'tree'){
				tjs("|"+varName+":="+input);
				latex[currentId] = latex[currentId].replace(/\\/g,'\\\\');
				var tree;
				if (latex[currentId] == "???"){
					tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
				}
				else {
					try {
						tree = JSON.parse('{'+latex[currentId]+'}');
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
				inputted[currentId] = "";
				ljs("|"+varName+":="+input);
				/*katexOptions.displayMode = isDisplay;
				k = katex.renderToString(latex, katexOptions);
				katexOptions.displayMode = false;
				k = k.replace('class="katex"','class="katex" data-input="'+inputted+'" data-latex="'+latex+'"');*/
				inputted[currentId] = "";
				cjs("|"+varName+":="+input);
				//k ='<div class=\"imcss\" data-input="'+inputted+'" data-latex="'+latex+'">' +imcss+ "\n</div>";
				k = imcss[currentId].replace('class="imcss"','class="imcss" data-input="'+inputted[currentId]+'" data-latex="'+latex[currentId]+'"');
			}
			
		}
		else{
			if (isTreePlot == 'tree'){
				tjs(input);
				latex[currentId] = latex[currentId].replace(/\\/g,'\\\\');
				var tree;
				if (latex[currentId] == "???"){
					tree = {'nodes':{'node0':{'text':'error','op':'x','parent':'' }},'allNodes':['node0']};
				}
				else {
					try {
						tree = JSON.parse('{'+latex[currentId]+'}');
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
				inputted[currentId] = "";
				latex[currentId] = "";
				imcss[currentId] = "";
				pjs(input,inputFull[1],inputFull[2],inputFull[3],inputFull[4]);
				if (svg[currentId] == "???"){
					latex[currentId] = "";
					imcss[currentId] = "";
					inputted[currentId] = "";
					k = "";
				}
				else {
					k = svg[currentId];
				}
			}
			else {
				inputted[currentId] = "";
				ljs(input);
				/*cjs(input);
				katexOptions.displayMode = isDisplay;
				k = katex.renderToString(latex, katexOptions);
				katexOptions.displayMode = false;
				k = k.replace('class="katex"','class="katex" data-input="'+inputted+'" data-latex="'+latex+'"');*/
				
				inputted[currentId] = "";
				cjs(input);
				k = imcss[currentId].replace('class="imcss"','class="imcss" data-input="'+inputted[currentId]+'" data-latex="'+latex[currentId]+'"');
				//k ='<div class=\"imcss\" data-input="'+inputted+'" data-latex="'+latex+'">' +imcss+ "\n</div>";
			}
			
		}
		latexedInputs[currentId][type+input]={dependents:{},dependentfunctions:{},output:k,varName:varName,latex:latex[currentId],imcss:imcss[currentId],inputted:inputted[currentId],display:isDisplay,options:{}};
		for (var i=0;i<dependents[currentId].length;i++){
			latexedInputs[currentId][type+input].dependents[dependents[currentId][i]] = currentV[currentId][dependents[currentId][i]];
		}
		for (var i=0;i<dependentFunctions[currentId].length;i++){
			latexedInputs[currentId][type+input].dependentfunctions[dependentFunctions[currentId][i]] = currentF[currentId][dependentFunctions[currentId][i]];
		}
		if (isTreePlot == 'plot'){
			latexedInputs[currentId][type+input].options.dr = inputFull; 
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
		if (inputV[currentId][varName]){
			if (inputV[currentId][varName] == dataYes){
				selected = "checked";
			}
			else if (inputV[currentId][varName] == dataNo){
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
				if (inputV[currentId][varName]){
					if (inputV[currentId][varName] == options[i]){selected = "checked";}
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
		
		if (inputV[currentId][varName]){
			defaultValue = inputV[currentId][varName];
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
		defaultValue = ""+Math.floor((parseInt(maxRange) + parseInt(minRange) + 1) / 2);
		
		if (inputV[currentId][varName]){
			defaultValue = inputV[currentId][varName];
		}
		html += '<input type="number" class="inline-number" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'"></input>';

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
		defaultValue = ""+Math.floor((parseInt(maxRange) + parseInt(minRange) + 1) / 2);
		if (inputV[currentId][varName]){
			defaultValue = inputV[currentId][varName];
		}
		html += '<input type="range" class="inline-range" name="inline-'+varName+'" min="'+minRange+'" max="'+maxRange+'" value="'+defaultValue+'" id="inline-'+varName+'"></input>';

	}
	if (varName != ""){
		if (!inputV[currentId][varName]){
			inputV[currentId][varName]=defaultValue;
			var j = mapOrNew(defaultValue,varName,true,false,isDisplay);
			currentV[currentId][varName]=j;
		}
		else {
			var j = mapOrNew(inputV[currentId][varName],varName,true,false,isDisplay);
			currentV[currentId][varName]=j;
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
  	text = text.replace(/&amp;/g,'&');
  	text = text.replace(/=([^\( =])/g,'= '+'$1');
  	text = text.replace(/!([^\=])/g,'!!'+'$1');
  	text = text.replace(/!$/,'!!');
  	renderIdx[currentId]++;
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
				svg[currentId] = '<div class="plotDiv" data-input="" data-latex="" data-sliders="'+dr+'" id="plot-'+plotid[currentId]+'" data-formula="'+fn+'" data-left="'+left+'" data-right="'+right+'" data-bottom="'+bottom+'" data-top="'+top+'" >';
				svg[currentId] += '</div>';
			}
			else {
				svg[currentId] = '<span class="plotSpan" data-input="" data-latex="" data-sliders="'+dr+'" id="plot-'+plotid[currentId]+'" data-formula="'+fn+'" data-left="'+left+'" data-right="'+right+'" data-bottom="'+bottom+'" data-top="'+top+'" >';
				svg[currentId] += '</span>';
			}
			plotid[currentId]++;
			
			return svg[currentId];
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
						latex[currentId] = latex[currentId].replace(aligners[ii],'&'+aligners[ii]+'&');
					}
				
					outText += latex[currentId] + "\\\\\n";
				}
			
			}
			if (aligners.length>1){
				outText += "\\end{alignedat}";
			}
			else {
				outText += "\\end{aligned}";
			}
		
			katexOptions.displayMode = true;
			k = katex.renderToString(outText, katexOptions);
			k = k.replace('class="katex"','class="katex" data-input="'+input+'" data-latex="'+outText+'"');
			katexOptions.displayMode = false;
			return k;
		}
		else if (input.search(/checkbox\(/)==0 || input.search(/radio\(/)==0 || input.search(/input\(/)==0 || input.search(/number\(/)==0 || input.search(/range\(/)==0){
			var html = createInputs(input,varName,isDisplay);
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
				return '<div>'+latex[currentId]+'</div>';
			}
			else {
				return '<span>'+latex[currentId]+'</span>';
			}
			
		}
		else {
			k = mapOrNew(input,varName,false,false,isDisplay);
			//var uniqueId = 'imcss-'+(10000+Math.floor(Math.random() * 90000));
			var uniqueId = 'imcss-'+renderIdx[currentId];
			console.log(originalMarkdown.substr(originalMarkdownMap[2*renderIdx[currentId]],originalMarkdownMap[2*renderIdx[currentId]+1]));
			k = k.replace('class="imcss"','class="imcss" id="'+uniqueId+'"');
			if (varName != ""){
				currentV[currentId][varName]=k;
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
var originalMarkdownMap = [];
var originalMarkdown;
function justTrack(match,p1,offset,string){
	originalMarkdownMap.push(offset);
	originalMarkdownMap.push(match.length);
	return match;
}
onmessage = function(e) {
	var message = e.data;
	var result = [];
	if (message[0] == "id"){
		addId(message[1]);
	}
	else if (message[0] == "markdown"){
		currentId = message[2];
		var markdown = message[1];
		originalMarkdown = message[1];
		originalMarkdownMap = [];
		markdown = markdown.replace(/\$+([^\$\n]+?)\$+/g,justTrack);
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
		plotid[currentId] = 0;
		var html;
		try {
			renderIdx[currentId] = -1;
			html = marked(markdown);
		}
		catch(err){
			html = "";
		}
		result = ["markdown",message[1],html,message[2]];
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
		result = ["code",message[1],k,message[2],latex[currentId],message[3]];
	}
	else if (message[0] == "plot"){
		
		k = mapOrNew([message[1],message[3],message[4],message[5],message[6]],"",false,'plot',false);
		svg[currentId] = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"0 0 100 100\" xmlns=\"http://www.w3.org/2000/svg\">";
		svg[currentId] += k;
		svg[currentId] += "</svg>";
		if (message[9].search('D')>-1){
			svg[currentId] += '<br><input type="range" data-formula="'+message[1]+'" id="domainSlider-'+message[2]+'" min="0" max="'+(message[7]*2)+'" value="'+message[7]+'"></input>';	
		}
		if (message[9].search('R')>-1){
			svg[currentId] += '<br><input type="range" data-formula="'+message[1]+'" id="rangeSlider-'+message[2]+'" min="0" max="'+(message[8]*2)+'" value="'+message[8]+'"></input>';	
		}
		result = ["svg",message[1],svg[currentId],message[2],inputted[currentId],latex[currentId]];
	}
	else if (message[0] == "inputValue"){
		inputV[currentId][message[1]]=message[2];
	}
	postMessage(result);
}

function cleanInput(input){
	var fns = ['max','min','perm','comb','gcd','pow','mod'];
	for (var i=0;i<fns.length;i++){
		var re = new RegExp(fns[i]+'\\(');
		var maxStr = input.match(re);
		var counter = 0;
		while (maxStr){
			var inside = insidePar(input.substr(maxStr.index+fns[i].length));
			if (fns[i] == 'pow'){
				var insideSplit = inside.split(',').join(") ^ (");
				input = input.substr(0,maxStr.index)+"(("+insideSplit+"))"+input.substr(maxStr.index+inside.length+fns[i].length+2);
			}
			else {
				var insideSplit = inside.split(',').join(") "+fns[i]+" (");
				input = input.substr(0,maxStr.index)+"(("+insideSplit+"))"+input.substr(maxStr.index+inside.length+fns[i].length+2);
			} 
			counter++;
			if (counter>100){
				break;
			}
			maxStr = input.match(re);
		}
	}
	input = input.replace(/ choose /g, ' comb ');
	return input;
}

function insidePar(input){
	if (input == "" || input[0] != "("){
		return "";
	}
	var openPar = 1;
	for (var i=1;i<input.length;i++){
		if (input[i]=="("){
			openPar++;
		}
		else if (input[i]==")"){
			openPar--;
		}
		
		if (openPar == 0){
			return input.substr(1,i-1);
		}
	}
	return "";
}