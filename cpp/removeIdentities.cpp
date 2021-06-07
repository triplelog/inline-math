#include "graphing.cpp"

std::string removeIdentities(std::string s){
	
	clearRules();
	rules = rulesMap["identities"];
	ruleIndex = ruleIndexMap["identities"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createIdentities();
	//makeRulesNew(rows);
	

	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	std::map<std::string, std::string> followAMap;
	std::string newPostfix = removeBracketsOne(s, followAMap);

	bool foundNext = true;
	int counter = 0;
	while (foundNext){
		if (killNow.check() || counter >100){
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next, followAMap);
		}
		counter++;
	}
	return newPostfix;
}

std::string solveArithmetic(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["arithmetic"];
	ruleIndex = ruleIndexMap["arithmetic"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createIdentities();
	//makeRulesNew(rows);
	//rows = createArithmetic();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	std::map<std::string, std::string> followAMap;
	std::string newPostfix = removeBracketsOne(s, followAMap);

	bool foundNext = true;
	int counter = 0; int ii; int iii;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix);
			newPostfix = removeIdentities(newPostfix);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,10)[0];
		if (someStrings.size()>0){
			
			int minLeft = 1000;
			for (ii=0;ii<someStrings.size();ii++){
				std::string tempPF = removeBracketsOne(someStrings[ii].next, followAMap);
				for (iii=0;iii<tempPF.length();iii++){
					if (tempPF.at(iii)=='@'){
						if (iii<minLeft){
							foundNext = true;
							newPostfix = tempPF;
							minLeft = iii;
							break;
						}
					}
				}
			}
		}
		counter++;
	}
	newPostfix = removeType11(newPostfix);
	newPostfix = removeIdentities(newPostfix);
	return newPostfix;
}

std::string toCanonical(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["canonical"];
	ruleIndex = ruleIndexMap["canonical"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createCanonical();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	std::map<std::string, std::string> followAMap;
	std::string newPostfix = removeBracketsOne(s, followAMap);

	bool foundNext = true;
	int counter = 0;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix);
			newPostfix = removeIdentities(newPostfix);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next, followAMap);
		}
		else if (maxDepth == "4"){
			maxDepth = "5";
			maxDepthn1 = "4";
			foundNext = true;
		}
		counter++;
	}
	newPostfix = removeType11(newPostfix);
	newPostfix = removeIdentities(newPostfix);
	return newPostfix;
}

/*
std::string doCalculus(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	
	clearRules();
	rules = rulesMap["calculus"];
	ruleIndex = ruleIndexMap["calculus"];
	maxDepth = "4";
	maxDepthn1 = "3";
	//std::vector<std::string> rows = createCanonical();
	//makeRulesNew(rows);
	
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::milliseconds>( a2 - a1 ).count();
	//console_log(duration);
	
	finishedAnswers.resize(0);
	answerListMap.clear();
	answerListMapF.clear();
	correctSolutionList.clear();
	incorrectSolutionList.clear();
	answerMap.clear();
	reverseMap.clear();
	reverseMapCorrect.clear();
	unfinishedOptions.clear();
	foundOneAnswer = false;
	startedWrong = false;
	
	
	std::string newPostfix = removeBracketsOne(s);

	bool foundNext = true;
	int counter = 0; int ii; int iii;
	while (foundNext){
		if (killNow.check() || counter >100){
			newPostfix = removeType11(newPostfix);
			newPostfix = removeIdentities(newPostfix);
			return newPostfix;
		}
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,10)[0];
		if (someStrings.size()>0){
			
			
			int minLeft = 1000;
			for (ii=0;ii<someStrings.size();ii++){
				
				std::string tempPF = removeBracketsOne(someStrings[ii].next);
				for (iii=0;iii<tempPF.length();iii++){
					if (tempPF.at(iii)=='@'){
						if (iii<minLeft){
							foundNext = true;
							newPostfix = tempPF;
							minLeft = iii;
							break;
						}
					}
				}
			}
		}
		counter++;
	}
	
	newPostfix = removeType11(newPostfix);
	newPostfix = removeIdentities(newPostfix);
	return newPostfix;

}
*/


