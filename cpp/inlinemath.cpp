
#include "partialstuff.cpp"
#include <emscripten/emscripten.h>
#include "removeIdentities.cpp"


EM_JS(void, console_log, (int x), {
  console.log(x);
});


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


void GraphPoints(char* aa, double domainLeft, double domainRight) {
	std::string a = std::string(aa);
	std::string pointStr = getPoints(a,"x",domainLeft,domainRight);

}




char* LatexIt(char* aa) {
	auto a1 = std::chrono::high_resolution_clock::now();
	std::string a = std::string(aa);
	std::vector<std::string> postfixedV = postfixifyVector(a,true);
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	
	std::string noIdentities = removeIdentities(postfixed);
	
	std::string latexed = latexOne(noIdentities);
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	char* buf;
	strcpy(buf, latexed.c_str());
	console_log(duration);
	return buf;
}


}




int main() {
	//std::string jsonmessage = "var rule = {};";
	srand(time(NULL));
	initialRun();
	return 1;
}

