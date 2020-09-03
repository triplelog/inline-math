function jsToMath(input){
	input = input.replace(/math\.cos\(/gi,'cos(');
	return input;
}