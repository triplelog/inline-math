function fixBaseline(){
	var lineHeight = 18;
	var root = document.querySelector(".imcss");
	var divs = root.querySelectorAll("div");
	var divInfo = [];
	var divRun = {};
	for (var i=0;i<divs.length;i++){
		var info = {'midline':-1,'mpt':0,'mpb':0,'paddingTop':0,'paddingBottom':0,'height':0,'type':'base','children':[]};
		if (divs[i].classList.contains('fraction')){
			info.type = 'fraction';
		}
		/*else if (divs[i].classList.contains('root')){
			info.type = 'center';
		}*/
		else if (divs[i].classList.contains('noflow')){
			info.type = 'noflow';
		}
		if (info.type == 'base'){
			divs[i].style.paddingTop = "0px";
			divs[i].style.paddingBottom = "0px";
		}
		
		
		divs[i].setAttribute('data-id',i);
		divInfo.push(info);
		divRun[i]=true;
	}

	for (var i=0;i<divs.length;i++){
		var children = divs[i].querySelectorAll(":scope > div");
		if (children.length == 0){
			if (divInfo[i].type == 'base'){
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				if (divInfo[i].height > lineHeight){
					divInfo[i].paddingBottom = divInfo[i].height - lineHeight;
					divInfo[i].paddingTop = 0;
					divInfo[i].midline = divInfo[i].height - lineHeight/2;
					divInfo[i].mpb = divInfo[i].height - lineHeight;
				}
				else if (divInfo[i].height < lineHeight){
					divInfo[i].paddingTop = lineHeight - divInfo[i].height;
					divInfo[i].paddingBottom = 0;
					divInfo[i].midline = lineHeight/2;
					divInfo[i].mpt = lineHeight - divInfo[i].height;
				}
				else {
					divInfo[i].paddingTop = 0;
					divInfo[i].paddingBottom = 0;
					divInfo[i].midline = lineHeight/2;
				}
			}
			else if (divInfo[i].type == 'center'){
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				divInfo[i].midline = divInfo[i].height/2;
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
			var midline = lineHeight/2;
			var mpt = -1;
			var mpb = -1;
			for (var ii=0;ii<divInfo[i].children.length;ii++){
				if (divRun[divInfo[i].children[ii]]){
					again = true;
					noChildren = false;
					break;
				}
				else {
					var ml = divInfo[divInfo[i].children[ii]].midline;
					if (ml > midline){
						midline = ml;
					}
				}
				
			}
			if (noChildren){
				console.log(i,midline);
				for (var ii=0;ii<divInfo[i].children.length;ii++){
					
					var bl = midline - divs[divInfo[i].children[ii]].getBoundingClientRect().height/2;
					
					var mpt1 = divInfo[divInfo[i].children[ii]].mpt;
					if (mpt1 < mpt || mpt == -1){
						mpt = mpt1;
					}
					var mpb1 = divInfo[divInfo[i].children[ii]].mpb + bl;
					if (mpb1 < mpb || mpb == -1){
						mpb = mpb1;
					}
			
				}
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				if (divs[i].classList.contains('root')){
					var svg = divs[i].querySelector(':scope > svg');
					svg.style.height = "calc(100% - "+mpb+"px)";
				}
				if (divInfo[i].type == 'base'){
				
					if (divInfo[i].height > midline*2){
						divInfo[i].paddingBottom = divInfo[i].height - midline*2;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = divInfo[i].height - midline;
						mpb += divInfo[i].height - midline*2;
					}
					else if (divInfo[i].height < midline*2){
						divInfo[i].paddingTop = midline*2 - divInfo[i].height;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = midline;
						mpt += midline*2 - divInfo[i].height;
					}
					else {
						divInfo[i].paddingTop = 0;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = midline;
					}
				}
				else if (divInfo[i].type == 'center'){
					divInfo[i].height = divs[i].getBoundingClientRect().height;
					divInfo[i].midline = divInfo[i].height/2;
				}
				divInfo[i].mpt = mpt;
				divInfo[i].mpb = mpb;
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