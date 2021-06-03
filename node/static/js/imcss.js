function fixBaseline(){
	var lineHeight = 18;
	var root = document.querySelector(".imcss");
	var divs = [root, ...root.querySelectorAll("div")];
	var divInfo = [];
	var divRun = {};
	for (var i=0;i<divs.length;i++){
		var info = {'midline':lineHeight/2,'cline':lineHeight/2,'tline':lineHeight/2,'margin':false,'noflow':false,'paddingTop':0,'paddingBottom':0,'height':0,'type':'base','children':[]};
		if (divs[i].classList.contains('fraction')){
			info.type = 'fraction';
		}
		else if (divs[i].classList.contains('power')){
			info.type = 'power';
		}
		else if (divs[i].classList.contains('root')){
			info.type = 'root';
		}
		else {
			info.type = 'center';
		}
		
		if (divs[i].classList.contains('noflow')){
			info.noflow = true;
		}
		if (divs[i].classList.contains('margin')){
			info.margin = true;
		}
		if (info.type == 'power' || info.type == "fraction"){
			divs[i].style.paddingTop = "0px";
			divs[i].style.paddingBottom = "0px";
		}
		
		
		divs[i].setAttribute('data-id',i);
		divInfo.push(info);
		divRun[i]=true;
	}

	for (var i=0;i<divs.length;i++){
		var children = divs[i].querySelectorAll(":scope > div");
		
		for (var ii=0;ii<children.length;ii++){
			
			divInfo[i].children.push(parseInt(children[ii].getAttribute('data-id')));
		}
		
	}
	
	for (var idx=0;idx<divs.length;idx++){
		var again = false;
		for (var i in divRun){
			var noChildren = true;
			var midline = lineHeight/2;
			var cline = lineHeight/2;
			var tline = lineHeight/2;
			var tlineAdj = 0;
			for (var ii=0;ii<divInfo[i].children.length;ii++){
				if (divRun[divInfo[i].children[ii]]){
					again = true;
					noChildren = false;
					break;
				}
				else if (divInfo[divInfo[i].children[ii]].noflow){
					
					
					var tl = divInfo[divInfo[i].children[ii]].tline + 100;
					if (tl > tlineAdj){
						tlineAdj = tl;
					}
				}
				else {
					var ml = divInfo[divInfo[i].children[ii]].midline;
					if (ml > midline){
						midline = ml;
					}
					var cl = divInfo[divInfo[i].children[ii]].cline;
					if (cl > cline){
						cline = cl;
					}
					var tl = divInfo[divInfo[i].children[ii]].tline;
					if (tl > tline){
						tline = tl;
					}
				}
				
			}
			if (noChildren){
				
				
				
				if (divInfo[i].type == 'fraction' && divInfo[i].children.length != 3){
					divInfo[i].type == 'center';
				}
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				
				if (divInfo[i].type == 'power'){
				
					if (divInfo[i].height > midline*2){
						divInfo[i].paddingBottom = divInfo[i].height - midline*2;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = divInfo[i].height - midline;
						divInfo[i].cline = midline;
						divInfo[i].tline = midline;
					}
					else if (divInfo[i].height < midline*2){
						divInfo[i].paddingTop = midline*2 - divInfo[i].height;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = midline;
						divInfo[i].cline = midline;
						divInfo[i].tline = divInfo[i].height - midline;
					}
					else {
						divInfo[i].paddingTop = 0;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = midline;
						divInfo[i].cline = midline;
						divInfo[i].tline = midline;
					}
				}
				else if (divInfo[i].type == 'fraction'){
					var numerator = divInfo[i].children[0];
					var denominator = divInfo[i].children[2];
					var nHeight = divInfo[numerator].height;
					var dHeight = divInfo[denominator].height;
					
					//divs[numerator].style.marginBottom = (divInfo[numerator].cline-divInfo[numerator].midline)+"px";
					//nHeight += divInfo[numerator].cline-divInfo[numerator].midline;
					//divs[denominator].style.marginTop = (divInfo[denominator].tline-(dHeight -divInfo[denominator].midline))+"px";
					//dHeight += divInfo[denominator].tline-(dHeight -divInfo[denominator].midline);
					if (dHeight < nHeight){
						divInfo[i].paddingBottom = nHeight - dHeight;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = dHeight;
						divInfo[i].cline = 2*dHeight - nHeight;
						divInfo[i].tline = 2*nHeight - dHeight;
					}
					else if (dHeight > nHeight){
						divInfo[i].paddingTop = dHeight - nHeight;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = dHeight;
						divInfo[i].cline = dHeight;
						divInfo[i].tline = nHeight;
					}
					else {
						divInfo[i].paddingTop = 0;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = dHeight;
						divInfo[i].cline = dHeight;
						divInfo[i].tline = dHeight;
					}
				}
				else if (divInfo[i].type == 'root'){
					var inside = divInfo[i].children[0];
					var height = divs[inside].getBoundingClientRect().height;
					divs[i].style.marginLeft = (height*0.5+2)+"px";
					
					//divs[inside].style.marginBottom = (divInfo[inside].cline-divInfo[inside].midline)+"px";
					divInfo[i].midline = midline;
					divInfo[i].cline = cline;
					divInfo[i].tline = tline;
				}
				else if (divInfo[i].type == 'center'){
					divInfo[i].height = divs[i].getBoundingClientRect().height;
					divInfo[i].midline = divInfo[i].height/2;
					divInfo[i].cline = cline;
					divInfo[i].tline = tline;
				}
				else {
					divInfo[i].midline = midline;
					divInfo[i].cline = cline;
					divInfo[i].tline = tline;
				}
				
				
				
				divs[i].style.paddingTop = divInfo[i].paddingTop+"px";
				divs[i].style.paddingBottom = divInfo[i].paddingBottom+"px";
				
				divInfo[i].tline += tlineAdj;
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				if (divInfo[i].margin){
					divs[i].style.marginTop = (divInfo[i].tline-(divInfo[i].height -divInfo[i].midline))+"px";
					divs[i].style.marginBottom = (divInfo[i].cline-divInfo[i].midline)+"px";
					divInfo[i].height += (divInfo[i].tline-(divInfo[i].height -divInfo[i].midline));
					divInfo[i].height += (divInfo[i].cline-divInfo[i].midline);
					//height += divInfo[i].tline-(divInfo[i].height -divInfo[i].midline);
				}
				
				delete divRun[i];
			}
		}
		
		if (!again){break}
	}
	//root.style.marginBottom = (divInfo[0].mpb/2)+"px";
	console.log(divInfo);
}

fixBaseline();