function fixBaseline(){
	var lineHeight = 16;
	var root = document.querySelector(".imcss");
	var divs = root.querySelectorAll("div");
	var divInfo = [];
	for (var i=0;i<divs.length;i++){
		var info = {'midline':false,'paddingTop':0,'paddingBottom':0,'height':0,'type':'base','children':[]};
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
	}
	console.log(divInfo);
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
			}
		}
		else {
			for (var ii=0;ii<children.length;ii++){
				divInfo[i].children.push(parseInt(children[ii].getAttribute('data-id')));
			}
		}
	}
	console.log(divInfo);
}

fixBaseline();