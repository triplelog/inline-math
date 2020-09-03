function getLatex(parent,parents) {
	var children = parent.childNodes;
	var startCopy = false;
	for (var i=0;i<children.length;i++){
		if (!startCopy){
			if (parents[children[i]]){
				startCopy = true;
				console.log(children[i]);
			}
		}
		else {
			console.log(children[i]);
			if (parents[children[i]]){
				startCopy = false;
			}
		}
		
	}
}

function getCopied() {
	var selected = window.getSelection();
	var parents = {};
	parents[selected.anchorNode]='anchor';
	parents[selected.focusNode]='focus';
	var commonParent = false;
	var currentAnchor = selected.anchorNode;
	var currentFocus = selected.focusNode;
	for (var i=0;i<100;i++){
		if (currentAnchor.parentElement){
			currentAnchor = currentAnchor.parentElement;
			for (var ii in parents){
				if (ii == currentAnchor){
					commonParent = ii;
					i = 100;
					break;
				}
			}
			parents[currentAnchor]='anchor';
		}
		if (currentFocus.parentElement){
			currentFocus = currentFocus.parentElement;
			for (var ii in parents){
				if (ii == currentFocus){
					commonParent = ii;
					i = 100;
					break;
				}
			}
			parents[currentFocus]='focus';
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
		getLatex(commonParent,parents);
	}
	//else: traverse valid children and get string
}