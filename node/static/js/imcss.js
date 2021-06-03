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
		if (divInfo[i].type == 'base'){
			divs[i].style.paddingTop = "0px";
			divs[i].style.paddingBottom = "0px";
		}
		
		
		divs[i].setAttribute('data-id',i);
		divInfo.push(info);
		divRun[i]=true;
	}

	for (var i=0;i<divs.length;i++){
		var children = divs[i].querySelectorAll("div");
		if (children.length == 0){
			if (divInfo[i].type == 'base'){
				divInfo[i].height = divs[i].getBoundingClientRect().height;
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
			divs[i].style.paddingTop = divInfo[i].paddingTop+"px";
			divs[i].style.paddingBottom = divInfo[i].paddingBottom+"px";
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
			console.log(i);
			var noChildren = true;
			for (var ii=0;ii<divInfo[i].children.length;ii++){
				if (divRun[divInfo[i].children[ii]]){
					again = true;
					noChildren = false;
					break;
				}
			}
			if (noChildren){
				console.log(i);
				divInfo[i].height = divs[i].getBoundingClientRect().height;
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
				console.log(divs[i]);
				divs[i].style.paddingTop = divInfo[i].paddingTop+"px";
				divs[i].style.paddingBottom = divInfo[i].paddingBottom+"px";
				delete divRun[i];
			}
		}
		
		if (!again){break}
	}
	console.log(divInfo);
}

fixBaseline();