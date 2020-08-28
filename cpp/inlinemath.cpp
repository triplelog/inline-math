
#include <emscripten/emscripten.h>
/*
void MakeLesson(std::string a) {
	clearRules();
	oneLesson(a);
}

void OneRule(std::string a) {


	std::string postfixed = postfixify(a);
	std::vector<std::vector<Step>> steps = partialTree(postfixed);
	std::string jsonmessage = "[";
	int i;
	flat_hash_map<std::string,bool> uniqueSteps;
	int idx = 0;
	for (i=0;i<steps[0].size();i++){
		flat_hash_map<char,std::string> partMap = steps[0][i].partMap;
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


void GraphPoints(std::string a, double domainLeft, double domainRight) {
	std::string pointStr = getPoints(a,"x",domainLeft,domainRight);

}
*/
#ifdef __cplusplus
extern "C" {
#endif

int LatexIt(std::string a) {

	
	//std::vector<std::string> postfixedV = postfixifyVector(a,true);
	//std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	//std::string latexed = latexOne(postfixed);
	return 1;
}

#ifdef __cplusplus
}
#endif


int main() {
	//std::string jsonmessage = "var rule = {};";
	//srand(time(NULL));
	//initialRun();
	return 1;
}

