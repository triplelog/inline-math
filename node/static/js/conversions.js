function jsToMath(input){
	input = input.replace(/math\.cos\(/g,'cos(');
	return input;
}