function jsToMath(input){
	input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	return input;
}

function pythonToMath(input){
	input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	return input;
}