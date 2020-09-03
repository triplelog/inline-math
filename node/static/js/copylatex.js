function getLatex(parent,parents) {
	var children = parent.childNodes;
	var startCopy = false;
	for (var i=0;i<children.length;i++){
		var isParent = false;
		for (var ii in parents){
			if (ii == children[i]){
				isParent = true;
				break;
			}
		}
		if (!startCopy){
			
			if (isParent){
				startCopy = true;
				console.log(children[i]);
			}
		}
		else {
			console.log(children[i]);
			if (isParent){
				startCopy = false;
			}
		}
		
	}
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
				console.log(ii);
				console.log(currentAnchor);
				if (ii == currentAnchor){
					console.log(ii);
					console.log(currentAnchor);
					commonParent = ii;
					i = 100;
					break;
				}
			}
			parents.push(currentAnchor);
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
			parents(currentFocus);
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