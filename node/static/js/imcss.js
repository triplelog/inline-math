function fixBaseline(){
	var lineHeight = 18;
	var root = document.querySelector(".imcss");
	var divs = [root, ...root.querySelectorAll("div")];
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
			if (divInfo[i].type == 'base' || divInfo[i].type == 'fraction'){
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
				if (divInfo[i].type != "noflow"){
					divInfo[i].children.push(parseInt(children[ii].getAttribute('data-id')));
				}
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
				
				
				if (divInfo[i].type == 'fraction' && divInfo[i].children.length != 2){
					divInfo[i].type == 'center';
				}
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				if (divs[i].classList.contains('root')){
					var svg = divs[i].querySelector(':scope > svg');
					svg.style.height = "calc(100% - "+mpb+"px)";
					//divs[i].style.marginLeft = (divs[i].getBoundingClientRect().height - mpb)*.5+"px";
					console.log(divs[i].getBoundingClientRect().height,mpb);
					divs[i].style.marginLeft = (20)*.5+"px";
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
				else if (divInfo[i].type == 'fraction'){
					var numerator = divInfo[i].children[0];
					var denominator = divInfo[i].children[1];
					var nHeight = divs[numerator].getBoundingClientRect().height;
					var dHeight = divs[denominator].getBoundingClientRect().height;
					if (dHeight < nHeight){
						divInfo[i].paddingBottom = nHeight - dHeight;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = dHeight;
						mpb += divInfo[i].height - midline*2;
					}
					else if (dHeight > nHeight){
						divInfo[i].paddingTop = dHeight - nHeight;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = dHeight;
						mpt += midline*2 - divInfo[i].height;
					}
					else {
						divInfo[i].paddingTop = 0;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = dHeight;
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
	root.style.marginBottom = (divInfo[0].mpb/2)+"px";
	console.log(divInfo);
}

fixBaseline();