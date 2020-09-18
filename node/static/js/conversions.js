function jsToMath(input){
	
	
	input = input.replace(/math\.asin\(/gi,'arcsin(');
	input = input.replace(/math\.acos\(/gi,'arccos(');
	input = input.replace(/math\.atan\(/gi,'arctan(');
	//input = input.replace(/math\.asinh\(/gi,'arcsinh(');
	//input = input.replace(/math\.acosh\(/gi,'arccosh(');
	//input = input.replace(/math\.atanh\(/gi,'arctanh(');
	input = input.replace(/math\.exp\(/gi,'e^(');
	
	input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	//math.pow(b,exponent)
	//rounding functions
	//max and min
	
	input = input.replace(/math\.e/gi,'e');
	input = input.replace(/math\.pi/gi,'pi');
	input = input.replace(/math\.sqrt2/gi,'sqrt(2)');
	input = input.replace(/math\.sqrt1_2/gi,'sqrt(1/2)');
	input = input.replace(/math\.log2e/gi,'log_2(e)');
	input = input.replace(/math\.log10e/gi,'log_10(e)');
	input = input.replace(/math\.ln2/gi,'ln(2)');
	input = input.replace(/math\.ln10/gi,'ln(10)');
	
	return input;
}

function mathToJS(input){
	
	
	input = input.replace(/arcsin\(/gi,'Math.asin(');
	input = input.replace(/arccos\(/gi,'Math.acos(');
	input = input.replace(/arctan\(/gi,'Math.atan(');
	//input = input.replace(/math\.asinh\(/gi,'arcsinh(');
	//input = input.replace(/math\.acosh\(/gi,'arccosh(');
	//input = input.replace(/math\.atanh\(/gi,'arctanh(');
	input = input.replace(/e^\(/gi,'Math.exp(');
	//input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	//math.pow(b,exponent)
	//rounding functions
	//max and min
	
	input = input.replace(/math\.e/gi,'e');
	input = input.replace(/math\.pi/gi,'pi');
	input = input.replace(/math\.sqrt2/gi,'sqrt(2)');
	input = input.replace(/math\.sqrt1_2/gi,'sqrt(1/2)');
	input = input.replace(/math\.log2e/gi,'log_2(e)');
	input = input.replace(/math\.log10e/gi,'log_10(e)');
	input = input.replace(/math\.ln2/gi,'ln(2)');
	input = input.replace(/math\.ln10/gi,'ln(10)');
	
	return input;
}

function pythonToMath(input){
	input = input.replace(/math\.exp\(/gi,'e^(');
	input = input.replace(/math\.log2\(/gi,'log_2(');
	input = input.replace(/math\.log10\(/gi,'log_10(');
	input = input.replace(/math\.asin\(/gi,'arcsin(');
	input = input.replace(/math\.acos\(/gi,'arccos(');
	input = input.replace(/math\.atan\(/gi,'arctan(');
	input = input.replace(/math\.fabs\(/gi,'abs(');
	input = input.replace(/math\.gcd\(/gi,'gcd(');
	input = input.replace(/math\.comb\(/gi,'comb(');
	input = input.replace(/math\.perm\(/gi,'perm(');
	
	//input = input.replace(/math\.factorial\(/gi,'abs(');
	input = input.replace(/math\.e/gi,'e');
	input = input.replace(/math\.pi/gi,'pi');
	input = input.replace(/math\.tau/gi,'(2*pi)');
	
	

	
	
	input = input.replace(/math\.(.{1,6})\(/gi,'$1(');
	return input;
}

function mathToPython(input){
	input = input.replace(/math\.exp\(/gi,'e^(');
	input = input.replace(/math\.log2\(/gi,'log_2(');
	input = input.replace(/math\.log10\(/gi,'log_10(');
	input = input.replace(/math\.asin\(/gi,'arcsin(');
	input = input.replace(/math\.acos\(/gi,'arccos(');
	input = input.replace(/math\.atan\(/gi,'arctan(');
	input = input.replace(/math\.fabs\(/gi,'abs(');
	input = input.replace(/math\.gcd\(/gi,'gcd(');
	input = input.replace(/math\.comb\(/gi,'comb(');
	input = input.replace(/math\.perm\(/gi,'perm(');
}