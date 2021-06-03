function fixBaseline(){
	var lineHeight = 18;
	var root = document.querySelector(".imcss");
	var divs = [root, ...root.querySelectorAll("div")];
	var divInfo = [];
	var divRun = {};
	for (var i=0;i<divs.length;i++){
		var info = {'midline':lineHeight/2,'paddingTop':0,'paddingBottom':0,'height':0,'type':'base','children':[],'siblings':false};
		if (divs[i].classList.contains('fraction')){
			info.type = 'fraction';
		}
		else if (divs[i].classList.contains('power')){
			info.type = 'power';
		}
		/*else if (divs[i].classList.contains('root')){
			info.type = 'center';
		}*/
		else if (divs[i].classList.contains('noflow')){
			info.type = 'noflow';
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
			if (divInfo[i].type != "noflow"){
				divInfo[i].children.push(parseInt(children[ii].getAttribute('data-id')));
				if (children.length > 1){
					divInfo[parseInt(children[ii].getAttribute('data-id'))].siblings = true;
				}
			}
		}
		
	}
	
	for (var idx=0;idx<divs.length;idx++){
		var again = false;
		for (var i in divRun){
			var noChildren = true;
			var midline = lineHeight/2;
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
				
				
				
				if (divInfo[i].type == 'fraction' && divInfo[i].children.length != 2){
					divInfo[i].type == 'center';
				}
				divInfo[i].height = divs[i].getBoundingClientRect().height;
				if (divs[i].classList.contains('root')){
					var svg = divs[i].querySelector(':scope > svg');
					//svg.style.height = "calc(100% - "+mpb+"px)";
					//divs[i].style.marginLeft = (divs[i].getBoundingClientRect().height - mpb)*.5+"px";
					//console.log(divs[i].getBoundingClientRect().height,mpb);
					divs[i].style.marginLeft = 10+"px";
					console.log(divs[i]);
				}
				if (divInfo[i].type == 'power'){
				
					if (divInfo[i].height > midline*2){
						divInfo[i].paddingBottom = divInfo[i].height - midline*2;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = divInfo[i].height - midline;
					}
					else if (divInfo[i].height < midline*2){
						divInfo[i].paddingTop = midline*2 - divInfo[i].height;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = midline;
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
					
					//divs[numerator].style.marginBottom = (divInfo[numerator].mpb*-1)+"px";
					//nHeight -= divInfo[numerator].mpb;
					if (dHeight < nHeight){
						divInfo[i].paddingBottom = nHeight - dHeight;
						divInfo[i].paddingTop = 0;
						divInfo[i].midline = dHeight;
					}
					else if (dHeight > nHeight){
						divInfo[i].paddingTop = dHeight - nHeight;
						divInfo[i].paddingBottom = 0;
						divInfo[i].midline = dHeight;
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
				else {
					divInfo[i].midline = midline;
				}
				
				divs[i].style.paddingTop = divInfo[i].paddingTop+"px";
				divs[i].style.paddingBottom = divInfo[i].paddingBottom+"px";
				
				
				delete divRun[i];
			}
		}
		
		if (!again){break}
	}
	//root.style.marginBottom = (divInfo[0].mpb/2)+"px";
	console.log(divInfo);
}

fixBaseline();