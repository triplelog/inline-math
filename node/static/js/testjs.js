
  	autosize(document.getElementById('inline-rules'));
  	
  	function startMarkdown() {
  		updateMarkdown("1");
  		autoNow["1"]="";
  		autoComplete["1"]={};
  	}
	
	
  	var myWorker = new Worker('js/wasmworker.js');
  	
  	myWorker.onmessage = function(e) {
  		if (e.data == "ready"){
  			setTimeout(startMarkdown,50);
  		}
		else if (e.data[0] == "markdown"){
			console.log(e.data);
			var html = e.data[2];
			autoComplete[e.data[3]][e.data[1]] = html;
			if (autoNow[e.data[3]] == e.data[1]){
  				chgAuto(e.data[1],e.data[3]);
			}
		}
		else if (e.data[0] == "code"){
			var html = e.data[2];
			var formEl = document.querySelector('#pid-'+e.data[5]+'-'+e.data[3]);
			formEl.innerHTML = " "+html;
			//formEl.querySelector('.katex').setAttribute('data-input',e.data[1]);
			//formEl.querySelector('.katex').setAttribute('data-latex',e.data[4]);
		}
		else if (e.data[0] == "svg"){
			//if (autoNow == e.data[1]){
			var svg = e.data[2];
			document.getElementById(e.data[3]).innerHTML = svg;
			document.getElementById(e.data[3]).setAttribute('data-input','plot('+e.data[4]+')');
			document.getElementById(e.data[3]).setAttribute('data-latex','plot('+e.data[5]+')');
			if (document.getElementById("domainSlider-"+e.data[3])){
				document.getElementById("domainSlider-"+e.data[3]).addEventListener('change',plotChange);
			}
			if (document.getElementById("rangeSlider-"+e.data[3])) {
				document.getElementById("rangeSlider-"+e.data[3]).addEventListener('change',plotChange);
			}
			
			
			//}
			//else {
			//	var latex = e.data[2];
			//	var html = katex.renderToString(latex, {throwOnError: false});
  			//	autoComplete[e.data[1]] = html;
			//}
		}
		
	}
	function updateInputValue(evt){
		var t = evt.target;
		while (!t.classList || !t.classList.contains('inline-math') ){
			if (t.parentNode){t = t.parentNode;}
			else {break;}
		}
		console.log(t);
		//TODO: restrct to radios of same name as event
		var els = t.querySelectorAll('input.inline-radio:checked, input.inline-input, input.inline-number, input.inline-range');

		for (var i=0;i<els.length;i++){
			var varName = els[i].getAttribute('name').substr(7);
			myWorker.postMessage(["inputValue",varName,els[i].value,t.id]);
		}
		
		els = t.querySelectorAll('input.inline-checkbox');
		for (var i=0;i<els.length;i++){
			//console.log(els[i]);
			//console.log(els[i].checked);
			var varName = els[i].getAttribute('name').substr(7);
			if (els[i].checked){
				//console.log("checked");
				myWorker.postMessage(["inputValue",varName,els[i].getAttribute('data-yes'),t.id]);
			}
			else {
				myWorker.postMessage(["inputValue",varName,els[i].getAttribute('data-no'),t.id]);
			}
			
		}
		
		updateMarkdown(t.id);
		
	}
	function updateMarkdown(id){
		console.log(id);
		console.log(document.getElementById(""+id));
		var answer = document.getElementById(""+id).value;
		myWorker.postMessage(["markdown",answer,id]);
		autoNow[id] = answer;
	}
  	function chgAuto(input,id) {
		var el = document.getElementById('out-'+id);
		el.innerHTML = autoComplete[id][input];
		fixBaseline();
		Prism.highlightAll();
		var els = el.querySelectorAll('input.inline-radio, input.inline-checkbox');
		for (var i=0;i<els.length;i++){
			els[i].addEventListener('click',updateInputValue);
		}
		els = el.querySelectorAll('input.inline-input, input.inline-number, input.inline-range');
		for (var i=0;i<els.length;i++){
			els[i].addEventListener('change',updateInputValue);
			//els[i].addEventListener('input',updateInputValue);
		}
		
		var treeEls = el.querySelectorAll('.inline-tree');
		for (var i=0;i<treeEls.length;i++){
			createTree(treeEls[i],0);
		}
		
		var plotEls = el.querySelectorAll('.plotSpan, .plotDiv');
		for (var i=0;i<plotEls.length;i++){
			var left = parseInt(plotEls[i].getAttribute('data-left'));
			var right = parseInt(plotEls[i].getAttribute('data-right'));
			var bottom = parseInt(plotEls[i].getAttribute('data-bottom'));
			var top = parseInt(plotEls[i].getAttribute('data-top'));
			var input = plotEls[i].getAttribute('data-formula');
			var id = plotEls[i].id;
			var sliders = plotEls[i].getAttribute('data-sliders');
			var spread = right-left;
			var spreadtb = top-bottom;
			myWorker.postMessage(["plot",input,id,left,right,bottom,top,spread,spreadtb,sliders]);
		}
		
	}
  	function answerDown(evt) {
		var key = evt.key;
		var t = evt.target;
		while (!t.classList || !t.classList.contains('inline-math') ){
			if (t.parentNode){t = t.parentNode;}
			else {break;}
		}
		console.log(t);
		if (key != 'Shift'){
			var answer = t.value;
			autoComplete[t.id][answer+key] = "in-progress";
			myWorker.postMessage(["markdown",answer+key,t.id]);
		}
		
	}
	function answerChange(evt) {
		var t = evt.target;
		while (!t.classList || !t.classList.contains('inline-math') ){
			if (t.parentNode){t = t.parentNode;}
			else {break;}
		}
		console.log(t);
		var answer = t.value;
		if (autoComplete[t.id][answer] == "in-progress"){
			autoNow[t.id] = answer;
		}
		else if (autoComplete[t.id][answer]){
			chgAuto(answer,t.id);
		}
		else {
			myWorker.postMessage(["markdown",answer,t.id]);
			autoNow[t.id] = answer;
		}
		
	}
	var autoComplete = {};
	var autoNow = {};
	var answerEls = document.querySelectorAll('.inline-math');
	for (var i=0;i<answerEls.length;i++){
		answerEl = answerEls[i];
		answerEl.addEventListener('keydown',answerDown);
		answerEl.addEventListener('input',answerChange);
	}
	
	function plotChange(evt) {
		var left = -10;
		var right = 10;
		var spread = 20;
		var bottom = -10;
		var top = 10;
		var input = "";
		var id = "";
		//console.log(evt.target);
		if (evt){
			spread = evt.target.value;
			if (spread == 0){return;}
			if (evt.target.id.substr(0,5) == 'domai'){
				var center = Math.floor(parseInt(evt.target.parentElement.getAttribute('data-right')) + parseInt(evt.target.parentElement.getAttribute('data-left')) + 1)/2;
				left = center-.5*spread;
				right = center+.5*spread;
				bottom = parseInt(evt.target.parentElement.getAttribute('data-bottom'));
				top = parseInt(evt.target.parentElement.getAttribute('data-top'));
				spreadtb = top-bottom;
				id = evt.target.id.substr(13);
				evt.target.parentElement.setAttribute('data-left',left);
				evt.target.parentElement.setAttribute('data-right',right);
			}
			else if (evt.target.id.substr(0,5) == 'range'){
				spreadtb = evt.target.value;
				var center = Math.floor(parseInt(evt.target.parentElement.getAttribute('data-top')) + parseInt(evt.target.parentElement.getAttribute('data-bottom')) + 1)/2;
				
				bottom = center-.5*spread;
				top = center+.5*spread;
				left = parseInt(evt.target.parentElement.getAttribute('data-left'));
				right = parseInt(evt.target.parentElement.getAttribute('data-right'));
				spread = right-left;
				id = evt.target.id.substr(12);
				evt.target.parentElement.setAttribute('data-bottom',bottom);
				evt.target.parentElement.setAttribute('data-top',top);
				
			}
			sliders = evt.target.parentElement.getAttribute('data-sliders');
			
			input = evt.target.getAttribute('data-formula');
			
		}
		
		myWorker.postMessage(["plot",input,id,left,right,bottom,top,spread,spreadtb,sliders]);
		
	}
	
	window.Prism = window.Prism || {};
	window.Prism.manual = true;
	

  	Prism.hooks.add('complete', function(env) {
  		var pid = 0;
  		var formEls;
  		if (env.language == 'js'){
  			formEls = document.querySelectorAll('code.language-js .token.formula');
  		}
  		else if (env.language == 'python'){
  			formEls = document.querySelectorAll('code.language-python .token.formula');
  		}
		for (pid=0;pid<formEls.length;pid++){
			formEls[pid].id = "pid-"+env.language+"-"+pid;
			myWorker.postMessage(["code",formEls[pid].textContent,pid,env.language]);
		}
	});
	

  	function toggleNode(evt) {
		var collapseTarget = evt.target.getAttribute('data-target');
		console.log(collapseTarget);
		var el = document.querySelector(collapseTarget);
		if (el.style.display != 'block'){
			el.style.display = "block";
		}
		else {
			el.style.display = "none";
		}
	
	}
	function createTree(treeEl,i){
		var nodeText = {};
		var els = treeEl.querySelectorAll('node');
		for (var i=0;i<els.length;i++){
			nodeText[els[i].id]=els[i].innerHTML;
		}
		for (var i=els.length-1;i>=0;i--){
			els[i].parentElement.removeChild(els[i]);
		}
		var tree = JSON.parse(treeEl.textContent);
		treeEl.innerHTML = "";
	
		var treeDiv = document.createElement('div');
		treeDiv.classList.add('tf-tree');
		var ul = document.createElement('ul');
		ul.id = "tree-simple"+i;
		treeDiv.appendChild(ul);

		var allNodes = tree.allNodes;
		var nodes = tree.nodes;
		var jsonTree = {};
		for (var ii=0;ii<allNodes.length;ii++){
			var name = allNodes[ii];
			var text = nodeText[name];
			var children = [];
			var parent = nodes[name].parent;
			var node = document.createElement('li');
			var span = document.createElement('span');
			span.classList.add("tf-nc");
			span.classList.add("rounded");
			if (nodes[name].startNode){
				span.classList.add("startNode");
			}
			else if (nodes[name].startNodes){
				span.classList.add("startNodes");
			}
			if (nodes[name].endNode){
				span.classList.add("endNode");
			}
			else if (nodes[name].endNodes){
				span.classList.add("endNodes");
			}
			span.innerHTML = text;
			node.appendChild(span);
			if (name[name.length-1]=='f'){
				var opSpan = document.createElement('span');
				opSpan.innerHTML = nodes[name].op;
				opSpan.style.position = "absolute";
				opSpan.style.top = "calc(100% + .4rem)";
				opSpan.style.left = "calc(50% - .6rem)";
				opSpan.style.width = "1.2rem";
				opSpan.style.height = "1.2rem";
				opSpan.style.background = "white";
				opSpan.style.border = "1px solid black";
				opSpan.style.borderRadius = "1rem";
				opSpan.style.zIndex = "2";
				opSpan.style.textAlign = "center";
				span.appendChild(opSpan);
			}
	
			jsonTree[name]={text:text,children:children,node:node};
			if (parent != ""){
				jsonTree[parent].children.push(name);
				var pnode = jsonTree[parent].node;
			
				if (pnode.querySelector('ul')){
					pnode.querySelector('ul').appendChild(node);
				}
				else {
					var ul = document.createElement('ul');
					pnode.appendChild(ul);
					pnode.querySelector('ul').appendChild(node);
				}
		
			}
			else if (ii==0){
				if (ul){
					ul.appendChild(node);
				}
			}
	
		}


		treeEl.appendChild(treeDiv);
	}

