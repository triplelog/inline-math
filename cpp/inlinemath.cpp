
#include "partialstuff.cpp"
#include <emscripten/emscripten.h>

EM_JS(void, console_log, (int x), {
  console.log(x);
});

EM_JS(void, string_log, (const char* x), {
  console.log(UTF8ToString(x));
});

EM_JS(void, graph_svg, (const char* x), {
  addSVG(UTF8ToString(x));
});

EM_JS(void, output_latex, (const char* x), {
  addLatex(UTF8ToString(x));
});

EM_JS(void, output_dependents, (const char* x), {
  setDependents(UTF8ToString(x));
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
	char varName = ' ';
	if (a.length()>4 && a.at(0) == '|' && a.at(2) == ':' && a.at(3) == '='){
		a = a.substr(4,a.length()-4);
		varName = a.at(1);
		char* out = new char[1];
		out[0] = varName;
		out[1] = '\0';
		string_log(a.c_str());
		string_log(out);
	}
	
	dependentChars.clear();

	std::vector<std::string> postfixedV = postfixifyVector(a,true);
	
	dependentChars = getDependents(postfixedV[1]);
	int sz = dependentChars.size();
	int i;
	char* dc = new char[sz];
	for (i=0;i<sz;i++){
		dc[i]=dependentChars[i];
	}
	dc[sz]='\0';
	output_dependents(dc);
	
	//TODO: replace dependents
	if (currentV.find('A') != currentV.end()){
		string_log(currentV['A'].c_str());
	}
	postfixedV[1] = removeDependents(postfixedV[1]);
	
	std::string postfixed = postfixedV[0]+"@"+postfixedV[1];
	if (varName >= 'A' && varName <= 'Z'){
		string_log(postfixed.c_str());
		currentV[varName]=postfixed;
	}
	
	
	
	
	
	
	//console_log(sz);
	std::string noIdentities = removeIdentities(postfixed);
	
	//std::string noIdentities = solveArithmetic(postfixed);
	
	//std::string noIdentities = toCanonical(postfixed);
	
	//std::string noIdentities = doCalculus(postfixed);
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

void AddRules(char* aa,char* bb) {
	auto a1 = std::chrono::high_resolution_clock::now();
	
	std::string ruleType = std::string(aa);
	int i;
	std::vector<std::string> ruleText;
	std::string oneLine = "";
	for (i =0;bb[i] != '\0';i++){
		if (bb[i] == '\n'){
			ruleText.push_back(oneLine);
			oneLine = "";
		}
		else {
			oneLine += bb[i];
		}
	}
	if (oneLine != ""){
		ruleText.push_back(oneLine);
		oneLine = "";
	}
	
	if (ruleType == "identities"){
		rules = rulesMap["identities"];
		ruleIndex = ruleIndexMap["identities"];
		ridx = rules.size();
		makeRulesNew(ruleText);
		rulesMap["identities"]=rules;
		ruleIndexMap["identities"]=ruleIndex;
	}
	else if (ruleType == "arithmetic"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);

		std::vector<std::string> rows2 = createArithmetic();
		makeRulesNew(rows2);
		makeRulesNew(ruleText);
		rulesMap["arithmetic"]=rules;
		ruleIndexMap["arithmetic"]=ruleIndex;
	}
	else if (ruleType == "canonical"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);
		std::vector<std::string> rows3 = createCanonical();
		makeRulesNew(rows3);
		
		makeRulesNew(ruleText);
		rulesMap["canonical"]=rules;
		ruleIndexMap["canonical"]=ruleIndex;
	}
	else if (ruleType == "calculus"){
		rules.clear();
		ruleIndex.clear();
		ridx = 0;
		std::vector<std::string> rows1 = createIdentities();
		makeRulesNew(rows1);
		std::vector<std::string> rows2 = createArithmetic();
		makeRulesNew(rows2);
		std::vector<std::string> rows4 = createCalculus();
		makeRulesNew(rows4);
		
		makeRulesNew(ruleText);
		rulesMap["calculus"]=rules;
		ruleIndexMap["calculus"]=ruleIndex;
	}
	
	
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

