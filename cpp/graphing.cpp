std::string convertCoordinates(double x,double  y,double left, double right,double bottom,double top){
	if (x<left){
		x = left-1;
	}
	if (x>right){
		x = right+1;
	}
	if (y<bottom){
		y = bottom-1;
	}
	if (y>top){
		y = top+1;
	}
	std::string xstr = std::to_string(100*(x-left)/(right-left));
	if (xstr.at(0) == '-'){xstr = xstr.substr(0,6);}
	else{xstr = xstr.substr(0,5);}
	
	std::string ystr = std::to_string(100-100*(y-bottom)/(top-bottom));
	if (ystr.at(0) == '-'){ystr = ystr.substr(0,6);}
	else{ystr = ystr.substr(0,5);}
	return xstr + " " + ystr;


}
std::string convertX(double x,double left, double right,double shift){
	if (x<left){
		x = left-1;
	}
	if (x>right){
		x = right+1;
	}
	std::string xstr = std::to_string(100*(x-left)/(right-left));
	if (xstr.at(0) == '-'){xstr = xstr.substr(0,6);}
	else{xstr = xstr.substr(0,5);}
	return xstr;

}
std::string convertY(double y,double bottom,double top,double shift){
	if (y<bottom){
		y = bottom-1;
	}
	if (y>top){
		y = top+1;
	}
	std::string ystr = std::to_string(100-100*(y-bottom)/(top-bottom));
	if (ystr.at(0) == '-'){ystr = ystr.substr(0,6);}
	else{ystr = ystr.substr(0,5);}
	return ystr;

}

std::string makeGraph(std::vector<std::string> postfixedV,std::string iV, std::string dV,double left, double right,double bottom,double top){
	
	char* buf;
	std::string svg = "";

	int i; int ii;
	int xMinor = 1;
	int xMajor = 1;
	if (right-left>50){
		xMajor = 10;
		xMinor = 2;
	}
	else if (right-left>30){
		xMajor = 5;
	}
	else if (right-left>20){
		xMajor = 3;
	}
	else if (right-left>10){
		xMajor = 2;
	}
	else if (right-left>5){
		xMajor = 1;
	}
	for (i=floor(left/xMinor)*xMinor+xMinor;i<floor(right)+xMinor;i+=xMinor){
		
		if (top-bottom>5){
			for (ii=floor(bottom)+1;ii<floor(top)+1;ii++){
				if (i%xMajor==0 && ii%5 == 0){
					svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".6\" fill=\"red\"/>";
				}
				else if (i%xMajor==0 || ii%5 == 0){
					svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".4\" fill=\"red\"/>";
				}
				else {
					svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".2\" fill=\"red\"/>";
				}
				
			}
		}
		
		if (i%xMajor == 0 && i != 0){
			svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(0,bottom,top,3) + "\" r=\"4px\" fill=\"white\"/>";

			svg += "<text fill=\"black\" font-size=\"6px\" text-anchor=\"middle\" dominant-baseline=\"hanging\" x=\"" + convertX(i,left,right,0) + "\" y=\"" + convertY(0,bottom,top,1) + "\">" + std::to_string(i) + "</text>";

		}
	}
	for (ii=floor(bottom)+1;ii<floor(top)+1;ii++){
		if (ii%5 == 0 && ii != 0){
			svg += "<circle cx=\"" + convertX(0,left,right,-3) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\"4px\" fill=\"white\"/>";

			svg += "<text font-size=\"6px\" text-anchor=\"end\" dominant-baseline=\"middle\" x=\"" + convertX(0,left,right,-1) + "\" y=\"" + convertY(ii,bottom,top,1) + "\">" + std::to_string(ii) + "</text>";

		}	
	}
	
	svg += "<path d=\"M" + convertCoordinates(0,top,left,right,bottom,top) + " V100 M" + convertCoordinates(left,0,left,right,bottom,top) + " H100\" stroke=\"rgb(160,160,160)\"/>";

	
	int n = 100;
	std::vector<double> points;
	maxDigits = 2;
	points = getPoints(postfixedV,iV,dV,left,right,n);
	maxDigits = -1;
	//console.log(outStr);
	svg += "<path d=\"M";
	if (points.size()<2*n+2){
		for (i=0;i<points.size()/2;i++){
			if (points[i*2]!=-10001 || points[i*2+1]!=-10001){
				svg += convertCoordinates(points[i*2],points[i*2+1],left,right,bottom,top)+ " ";
			}
			
		}
	}
	else {
		for (i=0;i<n+1;i++){
			if (points[i*2]!=-10001 || points[i*2+1]!=-10001){
				svg += convertCoordinates(points[i*2],points[i*2+1],left,right,bottom,top)+ " ";
			}
		}
	}
	if (svg.at(svg.length()-1) == 'M'){
		svg += "0,0 0,0";
	}
	
	svg += "\" stroke=\"rgb(60,60,60)\" fill=\"none\"/>";
	
	svg += "";
	svg += "\0";
	return svg;

}