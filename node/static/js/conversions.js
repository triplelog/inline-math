function jsToMath(input){
	console.log(input);
	input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	console.log(input);
	return input;
}