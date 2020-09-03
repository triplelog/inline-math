function getLatex(parent,parents) {
	console.log(parent);
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
				if (!child.classList || !child.classList.contains('katex')){
					fullLatex += getLatex(child,parents);
				}
				else{
					fullLatex += child.getAttribute('data-latex');
				}
			}
		}
		else {
			var child = children[i];
			if (!child.classList || !child.classList.contains('katex')){
				if (isParent){
					fullLatex += getLatex(child,parents);
				}
				else {
					fullLatex += getLatex(child,"all");
				}
				
			}
			else{
				fullLatex += child.getAttribute('data-latex');
			}
			if (isParent){
				startCopy = false;
			}
		}
		
	}
	return fullLatex;
}

function getInput(parent,parents) {
	console.log(parent);
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
				if (!child.classList || !child.classList.contains('katex')){
					fullInput += getInput(child,parents);
				}
				else{
					fullInput += child.getAttribute('data-input');
				}
			}
		}
		else {
			var child = children[i];
			if (!child.classList || !child.classList.contains('katex')){
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

function getCopied() {
	var selected = window.getSelection();
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
	console.log(commonParent);
	

	var katexParent = false;
	var superParent = commonParent;
	while (superParent){
		if (superParent.classList.contains('katex')){
			katexParent = superParent;
			break;
		}
		superParent = superParent.parentElement;
	}
	if (katexParent){
		console.log(katexParent.getAttribute('data-latex'));
	}
	else {
		var fL = getLatex(commonParent,parents);
		console.log(fL);
		var fI = getInput(commonParent,parents);
		console.log(fI);
	}
	//else: traverse valid children and get string
}