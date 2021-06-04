function getImcss(parent,parents) {
	var nParent = parent;
	var idParent = parent;
	while(!nParent.classList.contains('imcss') && nParent.parentElement){
		nParent = nParent.parentElement;
	}
	if (!nParent.classList.contains('imcss') ){
		console.log(parents);
		return;//Not within one formula
	}
	while(!idParent.classList.contains('imcss') && !idParent.id && idParent.parentElement){
		idParent = idParent.parentElement;
	}
	var formula = idParent.getAttribute('data-original');
	if (idParent.classList.contains('imcss') ){
		idParent.innerHTML = formula;
		return;
	}
	
	var location = idParent.id;
	console.log(formula,location);
	
	return "done";
	var children = parent.childNodes;
	var startCopy = false;
	if (parents == "all"){
		startCopy = true;
	}
	var fullLatex = "";
	if (!children || children.length == 0){
		fullLatex += parent.textContent;
		return fullLatex;
	}
	for (var i=0;i<children.length;i++){
		var isParent = false;
		for (var ii in parents){
			var p = parents[ii];
			if (p == children[i]){
				isParent = true;
				break;
			}
		}
		if (!startCopy){
			
			if (isParent){
				startCopy = true;
				
				var child = children[i];
				if (!child.hasAttribute || !child.hasAttribute('data-latex')){
					fullLatex += getLatex(child,parents);
				}
				else{
					fullLatex += "$"+child.getAttribute('data-latex').trim()+"$";
				}
			}
		}
		else {
			var child = children[i];
			if (!child.hasAttribute || !child.hasAttribute('data-latex')){
				if (isParent){
					fullLatex += getLatex(child,parents);
				}
				else {
					fullLatex += getLatex(child,"all");
				}
				
			}
			else{
				fullLatex += "$"+child.getAttribute('data-latex').trim()+"$";
			}
			if (isParent){
				startCopy = false;
			}
		}
		
	}
	return fullLatex;
}

function getLatex(parent,parents) {
	var children = parent.childNodes;
	var startCopy = false;
	if (parents == "all"){
		startCopy = true;
	}
	var fullLatex = "";
	if (!children || children.length == 0){
		fullLatex += parent.textContent;
		return fullLatex;
	}
	for (var i=0;i<children.length;i++){
		var isParent = false;
		for (var ii in parents){
			var p = parents[ii];
			if (p == children[i]){
				isParent = true;
				break;
			}
		}
		if (!startCopy){
			
			if (isParent){
				startCopy = true;
				
				var child = children[i];
				if (!child.hasAttribute || !child.hasAttribute('data-latex')){
					fullLatex += getLatex(child,parents);
				}
				else{
					fullLatex += "$"+child.getAttribute('data-latex').trim()+"$";
				}
			}
		}
		else {
			var child = children[i];
			if (!child.hasAttribute || !child.hasAttribute('data-latex')){
				if (isParent){
					fullLatex += getLatex(child,parents);
				}
				else {
					fullLatex += getLatex(child,"all");
				}
				
			}
			else{
				fullLatex += "$"+child.getAttribute('data-latex').trim()+"$";
			}
			if (isParent){
				startCopy = false;
			}
		}
		
	}
	return fullLatex;
}

function getInput(parent,parents) {
	var children = parent.childNodes;
	var startCopy = false;
	if (parents == "all"){
		startCopy = true;
	}
	var fullInput = "";
	if (!children || children.length == 0){
		fullInput += parent.textContent;
		return fullInput;
	}
	for (var i=0;i<children.length;i++){
		var isParent = false;
		for (var ii in parents){
			var p = parents[ii];
			if (p == children[i]){
				isParent = true;
				break;
			}
		}
		if (!startCopy){
			
			if (isParent){
				startCopy = true;
				
				var child = children[i];
				if (!child.hasAttribute || !child.hasAttribute('data-latex')){
					fullInput += getInput(child,parents);
				}
				else{
					fullInput += child.getAttribute('data-input');
				}
			}
		}
		else {
			var child = children[i];
			if (!child.hasAttribute || !child.hasAttribute('data-latex')){
				if (isParent){
					fullInput += getInput(child,parents);
				}
				else {
					fullInput += getInput(child,"all");
				}
				
			}
			else{
				fullInput += child.getAttribute('data-input');
			}
			if (isParent){
				startCopy = false;
			}
		}
		
	}
	return fullInput;
}

function getHTML(parent,parents) {
	var children = parent.childNodes;
	var startCopy = false;
	if (parents == "all"){
		startCopy = true;
	}
	var fullInput = "";
	if (!children || children.length == 0){
		if (parent.outerHTML){
			fullInput += parent.outerHTML;
		}
		else if (parent.textContent){
			fullInput += parent.textContent;
		}
		else {
			fullInput += parent;
		}
		
		return fullInput;
	}
	for (var i=0;i<children.length;i++){
		var isParent = false;
		for (var ii in parents){
			var p = parents[ii];
			if (p == children[i]){
				isParent = true;
				break;
			}
		}
		if (!startCopy){
			
			if (isParent){
				startCopy = true;
				
				var child = children[i];
				if (child.outerHTML){
					fullInput += child.outerHTML;
				}
				else if (child.textContent){
					fullInput += child.textContent;
				}
				else {
					fullInput += child;
				}
			}
		}
		else {
			var child = children[i];
			if (child.outerHTML){
				fullInput += child.outerHTML;
			}
			else if (child.textContent){
				fullInput += child.textContent;
			}
			else {
				fullInput += child;
			}
			if (isParent){
				startCopy = false;
			}
		}
		
	}
	return fullInput;
}

function getParents() {
	var selected = window.getSelection();
	if (!selected.anchorNode || !selected.focusNode){
		commonParent = document.getElementById('output-math');
		parents = "all";
		return [commonParent,parents];
	}
	var parents = [selected.anchorNode,selected.focusNode];
	var commonParent = false;
	var currentAnchor = selected.anchorNode;
	var currentFocus = selected.focusNode;
	for (var i=0;i<100;i++){
		if (currentAnchor.parentElement){
			currentAnchor = currentAnchor.parentElement;
			for (var ii in parents){
				var p = parents[ii];
				if (p == currentAnchor){
					commonParent = p;
					i = 100;
					break;
				}
			}
			parents.push(currentAnchor);
		}
		if (currentFocus.parentElement){
			currentFocus = currentFocus.parentElement;
			for (var ii in parents){
				var p = parents[ii];
				if (p == currentFocus){
					commonParent = p;
					i = 100;
					break;
				}
			}
			parents.push(currentFocus);
		}
		if (commonParent){
			break;
		}
	}

	var nParent = commonParent;
	while(nParent.id != "output-math" && nParent.parentElement){
		nParent = nParent.parentElement;
	}
	if (nParent.id != "output-math"){
		commonParent = document.getElementById('output-math');
		parents = "all";
	}
	
	return [commonParent,parents];
}

function getCopied(evt) {
	var el = evt.target;
	var output = 'latex';
	while (el.tagName != 'BUTTON' && el.parentElement){
		el = el.parentElement;
	}
	if (el.classList && el.classList.contains('copy-text')){
		output = 'code';
	}
	if (el.classList && el.classList.contains('copy-html')){
		output = 'html';
	}
	if (el.classList && el.classList.contains('copy-imcss')){
		output = 'imcss';
	}
	var el = el.parentElement.querySelector('textarea');

	var p = getParents();
	var commonParent = p[0];
	var parents = p[1];
	if (!commonParent){
		return;
	}

	var katexParent = false;
	var superParent = commonParent;
	while (superParent){
		if (superParent.hasAttribute && superParent.hasAttribute('data-latex')){
			katexParent = superParent;
			break;
		}
		superParent = superParent.parentElement;
	}
	if (katexParent){
		if (output == 'latex'){
			var fL = katexParent.getAttribute('data-latex');
			el.value = fL;
		}
		else if (output == 'imcss'){
			var fI = getImcss(commonParent,parents);
			el.value = fI;
		}
		else if (output == 'code'){
			var fI = katexParent.getAttribute('data-input');
			el.value = fI;
		}
		else if (output == 'html'){
			var fH = katexParent.outerHTML;
			el.value = fH;
		}
		else {
			var fL = katexParent.getAttribute('data-latex');
			el.value = fL;
		}
		
	}
	else {
		if (output == 'latex'){
			var fL = getLatex(commonParent,parents);
			console.log(fL);
			el.value = fL;
		}
		else if (output == 'imcss'){
			var fI = getImcss(commonParent,parents);
			el.value = fI;
		}
		else if (output == 'code'){
			var fI = getInput(commonParent,parents);
			el.value = fI;
		}
		else if (output == 'html'){
			var fH = getHTML(commonParent,parents);
			el.value = fH;
		}
		else {
			var fL = getLatex(commonParent,parents);
			el.value = fL;
		}
		
		
	}
	el.select();
	document.execCommand('copy');
}

//var div = document.createElement('div');
//div.innerHTML = '<button class="copy-latex">Copy Latex</button><button class="copy-code">Copy Code</button>';
//var ta = document.createElement('textarea');
//ta.style.visibility = 'hidden';
//div.appendChild(ta);
//codeParent.parentElement.appendChild(div);
document.querySelector('button.copy-latex').addEventListener('click',getCopied);
document.querySelector('button.copy-text').addEventListener('click',getCopied);
document.querySelector('button.copy-html').addEventListener('click',getCopied);
document.querySelector('button.copy-imcss').addEventListener('click',getCopied);

