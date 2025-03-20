#ifndef __RPN_HPP__
# define __RPN_HPP__

# include <stack>
# include <algorithm>
# include <sstream>
# include <stdlib.h>
# include <iostream>

class RPN
{
	private:
		std::stack<double> _calculator;
		bool _isOperand(char x);
		bool _isDigit(char x);
		double _poppedResult(double num1, double num2, char operand);
	
	public:
		RPN();
		RPN(RPN &other);
		RPN &operator=(RPN &rhs);
		~RPN();
		
		double	calculateResult(std::string expression);
		
};
#endif