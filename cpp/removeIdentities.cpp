

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
	maxSteps = 25;
	
	auto a1 = std::chrono::high_resolution_clock::now();
	maxFound = 0;
	
	//std::cout << "mf:" << maxFound << " times: " << duration1 << " and " << duration2 << " and " << duration3 << "\n";
	

	
	
	auto a2 = std::chrono::high_resolution_clock::now();
	duration3 += std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	//std::cout << "times: " << duration1 << " and " << duration2 << " and " << duration3 << "\n";
	
	
	std::string newPostfix = removeBracketsOne(s);
	//std::cout << "\n\nStarting the Loop @$*&^@$*&^@*$&^@*$&^\n\n";

	
	//maxSteps = 5;
	//getAnswerList(newPostfix,0);
	maxSteps = 15;
	getAnswerList(newPostfix,0);
	//maxSteps = 15;
	//getAnswerList(newPostfix,0);
	//std::cout << "\n\n\n\nCompleted the InCorrect Loop @$*&^@$*&^@*$&^@*$&^\n\n\n\n" << " and " << std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count() << "\n\n\n";
	//std::cout << "total answers: "<< totalAnswers << "\n";
	//duration2 += std::chrono::duration_cast<std::chrono::microseconds>( a2 - a1 ).count();
	//std::cout << "\n\nCompleted the Loop @$*&^@$*&^@*$&^@*$&^\n\n";
	int i; int ii; int iii; int iiii;
	
	a1 = std::chrono::high_resolution_clock::now();
	//std::cout << "finished answers: " << finishedAnswers.size() << "\n";
	

	unfinishedOptions.clear();
	std::string finalAnswer = "";
	int longestAnswer = 0;
	for (ii=0;ii<finishedAnswers.size();ii++){
		////std::cout << "f: " << finishedAnswers[ii] << "\n";
		if (2 == 2){
			////std::cout << "cf: " << finishedAnswers[ii] << "\n";
			std::vector<Step> v = makeSolutionList(finishedAnswers[ii],newPostfix);
			int vsz = v.size();
			if (vsz > 0){
				
				Answer answer;
				answer.finished = true;
				answer.correct = true;
				if (vsz > longestAnswer){
					longestAnswer = vsz;
					finalAnswer = finishedAnswers[ii];
				}
				if (vsz > 1){
					answer.next = v[vsz-2].next;
				}
				answer.solution = v;
				answerMap[finishedAnswers[ii]]=answer;
				
			}
			else {
				v = makeIncorrectSolutionList(finishedAnswers[ii],newPostfix);
				vsz = v.size();
				
				Answer answer;
				answer.finished = true;
				answer.correct = false;
				if (vsz > 1){
					answer.next = v[vsz-2].next;
				}
				answer.solution = v;
				answerMap[finishedAnswers[ii]]=answer;
			}
		}
	}
	return finalAnswer;
}