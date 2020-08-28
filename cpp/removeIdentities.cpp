

std::string removeIdentities(std::string s){
	
	clearRules();
	std::vector<std::string> rows = createIdentities();
	makeRulesNew(rows);
	

	
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
	while (foundNext){
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next);
		}
	}
	return newPostfix;
}

std::string solveArithmetic(std::string s){
	auto a1 = std::chrono::high_resolution_clock::now();
	clearRules();
	auto a2 = std::chrono::high_resolution_clock::now();
	int duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	std::vector<std::string> rows = createIdentities();
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	makeRulesNew(rows);
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	rows = createArithmetic();
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	makeRulesNew(rows);
	
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	
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
	
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	
	std::string newPostfix = removeBracketsOne(s);
	
	a2 = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	console_log(duration);
	
	bool foundNext = true;
	while (foundNext){
		foundNext = false;
		std::vector<Step> someStrings = makeTree(newPostfix,1)[0];
		if (someStrings.size()>0){
			foundNext = true;
			newPostfix = removeBracketsOne(someStrings[0].next);
		}
		a2 = std::chrono::high_resolution_clock::now();
		duration = std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
		console_log(duration);
	}
	return newPostfix;
}