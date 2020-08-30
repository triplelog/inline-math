
#include "partialstuff.cpp"
#include <emscripten/emscripten.h>

EM_JS(void, console_log, (int x), {
  console.log(x);
});

EM_JS(void, graph_svg, (const char* x), {
  addSVG(UTF8ToString(x));
});

EM_JS(void, output_latex, (const char* x), {
  addLatex(UTF8ToString(x));
});

#include "removeIdentities.cpp"





extern "C" {

void MakeLesson(char* aa) {
	std::string a = std::string(aa);
	clearRules();
	oneLesson(a);
}

void OneRule(char* aa) {
	std::string a = std::string(aa);

	std::string postfixed = postfixify(a);
	std::vector<std::vector<Step>> steps = partialTree(postfixed);
	std::string jsonmessage = "[";
	int i;
	std::map<std::string,bool> uniqueSteps;
	int idx = 0;
	for (i=0;i<steps[0].size();i++){
		std::map<char,std::string> partMap = steps[0][i].partMap;
		if (steps[0][i].rule < 0){
			continue;
		}
		
		
		std::string oneStep = displayOne(steps[0][i],postfixed,steps[0][i].next);
		
		
		if (uniqueSteps.find(oneStep) == uniqueSteps.end()){
			if (idx ==0){
				jsonmessage += oneStep;
			}
			else {
				jsonmessage += ","+oneStep;
			}
			uniqueSteps[oneStep]=true;
			idx++;
		}
		
	}
	jsonmessage += "]";
	
}






void LatexIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string a = std::string(aa);
	std::vector<std::string> postfixedV = postfixifyVector(a,true);
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	
	//std::string noIdentities = removeIdentities(postfixed);
	
	//std::string noIdentities = solveArithmetic(postfixed);
	
	std::string noIdentities = toCanonical(postfixed);
	postfixed = "\0";
	std::string latexed = latexOne(noIdentities);
	noIdentities = "\0";
	latexed += "\0";
	output_latex(latexed.c_str());
	latexed = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	console_log(duration);
}

void PlotIt(char* aa,double left,double right, double bottom, double top) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string a = std::string(aa);

	std::string plot = makeGraph(a,left,right,bottom,top);
	plot += "\0";
	graph_svg(plot.c_str());
	plot = "\0";
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();

	
	console_log(duration);
}

}




int main() {
	//std::string jsonmessage = "var rule = {};";
	srand(time(NULL));
	initialRun();
	return 1;
}

