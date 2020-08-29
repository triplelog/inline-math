std::string convertCoordinates(double x,double  y,double left, double right,double bottom,double top){
	if (x>=left && x<=right){
		std::string xstr = std::to_string(100*(x-left)/(right-left));
		if (xstr.at(0) == '-'){xstr = xstr.substr(0,6);}
		else{xstr = xstr.substr(0,5);}
		if (y>=bottom && y<=top){
			std::string ystr = std::to_string(100-100*(y-bottom)/(top-bottom));
			if (ystr.at(0) == '-'){ystr = ystr.substr(0,6);}
			else{ystr = ystr.substr(0,5);}
			return xstr + " " + ystr;
		}
		else {
			return "";
		}
	}
	else {
		return "";
	}
}
std::string convertX(double x,double left, double right,double shift){
	if (x>=left && x<=right){
		std::string xstr = std::to_string(100*(x-left)/(right-left));
		if (xstr.at(0) == '-'){xstr = xstr.substr(0,6);}
		else{xstr = xstr.substr(0,5);}
		return xstr;
	}
	else {
		return "";
	}
}
std::string convertY(double y,double bottom,double top,double shift){
	if (y>=bottom && y<=top){
		std::string ystr = std::to_string(100-100*(y-bottom)/(top-bottom));
		if (ystr.at(0) == '-'){ystr = ystr.substr(0,6);}
		else{ystr = ystr.substr(0,5);}
		return ystr;
	}
	else {
		return "";
	}
}

std::string makeGraph(std::string fn){
	double left = -20;
	double right = 20;
	double bottom = -20;
	double top = 20;
	char* buf;
	std::string svg = "<svg version=\"1.1\" baseProfile=\"full\" viewBox=\"0 0 100 100\" width=\"200\" height=\"200\" xmlns=\"http://www.w3.org/2000/svg\">";

	int i; int ii;
	if (right-left>5){
		for (i=floor(left)+1;i<floor(right)+1;i++){
			
			if (top-bottom>5){
				for (ii=floor(bottom)+1;ii<floor(top)+1;ii++){
					if (i%5==0 && ii%5 == 0){
						svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".6\" fill=\"red\"/>";
					}
					else if (i%5==0 || ii%5 == 0){
						svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".4\" fill=\"red\"/>";
					}
					else {
						svg += "<circle cx=\"" + convertX(i,left,right,0) + "\" cy=\"" + convertY(ii,bottom,top,0) + "\" r=\".2\" fill=\"red\"/>";
					}
					
				}
			}
			
			if (i%5 == 0 && i != 0){
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
	}
	
	svg += "<path d=\"M" + convertCoordinates(0,top,left,right,bottom,top) + " V100 M" + convertCoordinates(left,0,left,right,bottom,top) + " H100\" stroke=\"rgb(160,160,160)\"/>";

	
	
	std::vector<double> points = getPoints(fn,"x",left,right);
	//console.log(outStr);
	svg += "<path d=\"M";
	for (i=0;i<101;i++){
		svg += convertCoordinates(points[i*2],points[i*2+1],left,right,bottom,top)+ " ";
	}
	svg += "\" stroke=\"rgb(60,60,60)\" fill=\"none\"/>";
	
	svg += "</svg>";
	svg += "\0";
	return svg;

}