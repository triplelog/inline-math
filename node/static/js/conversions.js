function jsToMath(input){
	console.log(input);
	input = input.replace(/math\.cos\(/g,'cos(');
	console.log(input);
	return input;
}