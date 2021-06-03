function fixBaseline(){
	var lineHeight = 18;
	var root = document.querySelector(".imcss");
	var divs = root.querySelectorAll("div");
	var divInfo = [];
	var divRun = {};
	for (var i=0;i<divs.length;i++){
		var info = {'midline':-1,'paddingTop':0,'paddingBottom':0,'height':0,'type':'base','children':[]};
		if (divs[i].classList.contains('fraction')){
			info.type = 'fraction';
		}
		else if (divs[i].classList.contains('root')){
			info.type = 'center';
		}
		
		if (divs[i].style.paddingTop){
			info.paddingTop = divs[i].style.paddingTop;
		}
		if (divs[i].style.paddingBottom){
			info.paddingBottom = divs[i].style.paddingBottom;
		}
		info.height = divs[i].getBoundingClientRect().height - info.paddingTop - info.paddingBottom;
		divs[i].setAttribute('data-id',i);
		divInfo.push(info);
		divRun[i]=true;
	}

	for (var i=0;i<divs.length;i++){
		var children = divs[i].querySelectorAll("div");
		if (children.length == 0){
			if (divInfo[i].type == 'base'){
				
				if (divInfo[i].height > lineHeight){
					divInfo[i].paddingBottom = divInfo[i].height - lineHeight;
					divInfo[i].paddingTop = 0;
					divInfo[i].midline = divInfo[i].height/2;
				}
				else if (divInfo[i].height < lineHeight){
					divInfo[i].paddingTop = lineHeight - divInfo[i].height;
					divInfo[i].paddingBottom = 0;
					divInfo[i].midline = lineHeight/2;
				}
				else {
					divInfo[i].paddingTop = 0;
					divInfo[i].paddingBottom = 0;
					divInfo[i].midline = lineHeight/2;
				}
			}
			divs[i].style.paddingTop = divInfo[i].paddingTop;
			divs[i].style.paddingBottom = divInfo[i].paddingBottom;
			delete divRun[i];
		}
		else {
			for (var ii=0;ii<children.length;ii++){
				divInfo[i].children.push(parseInt(children[ii].getAttribute('data-id')));
			}
		}
	}
	
	for (var idx=0;idx<divs.length;idx++){
		var again = false;
		for (var i in divRun){
			var noChildren = false;
			for (var ii=0;ii<divInfo[i].children.length;ii++){
				if (divRun[ii]){
					again = true;
					noChildren = true;
					break;
				}
			}
			if (noChildren){
				divInfo[i].height = divs[i].getBoundingClientRect().height - divInfo[i].paddingTop - divInfo[i].paddingBottom;
				if (divInfo[i].type == 'base'){
				
					if (divInfo[i].height > lineHeight){
						divInfo[i].paddingBottom = divInfo[i].height - lineHeight;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = divInfo[i].height/2;
					}
					else if (divInfo[i].height < lineHeight){
						divInfo[i].paddingTop = lineHeight - divInfo[i].height;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = lineHeight/2;
					}
				}
				divs[i].style.paddingTop = divInfo[i].paddingTop;
				divs[i].style.paddingBottom = divInfo[i].paddingBottom;
				delete divRun[i];
			}
		}
		
		if (!again){break}
	}
	console.log(divInfo);
}

fixBaseline();