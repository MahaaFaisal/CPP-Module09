#include "RPN.hpp"

RPN::RPN()
{
	//something
}

RPN::RPN(RPN &other)
{
	*this = other;
}

RPN &RPN::operator=(RPN &rhs)
{
	(void) rhs;
	return (*this);
}

RPN::~RPN()
{

}

bool RPN::_isDigit(char x)
{
	if(x >= '0' && x <= '9')
		return 1;
	return 0;
}

bool RPN::_isOperand(char x)
{
	if(x == '+' || x == '-' || x == '*' || x == '/')
		return 1;
	return 0;
}

double RPN::_poppedResult(int num1, int num2, char operand)
{
	std::cout << num1 << " " << operand << " " << num2 << " = ";
	if (operand == '+')
	{
		std::cout << num1 + num2 << std::endl;
		return num1 + num2;
	}
	if (operand == '-')
	{
		std::cout << num1 - num2 << std::endl;
		return num1 - num2;
	}
	if (operand == '*')
	{
		std::cout << num1 * num2 << std::endl;
		return num1 * num2;
	}
	if (operand == '/')
	{
		std::cout << num1 / num2 << std::endl;
		return num1 / num2;

	}
	throw std::invalid_argument("invalid expression");	
}

double RPN::calculateResult(std::string expression)
{
	std::stringstream expStream(expression);
	std::string word;
	while (!expStream.eof())
	{
		expStream >> word;
		if (word.length () == 1)
		{
			if (_isDigit(word[0]))
				_calculator.push(atoi(word.c_str()));
			else if (_isOperand(word[0]) && _calculator.size() > 1)
			{
				int num2 = _calculator.top();
				_calculator.pop();
				int num1 = _calculator.top();
				_calculator.pop();
				_calculator.push(_poppedResult(num1, num2, word[0]));
			}
			else
				throw std::invalid_argument("invalid expression");	
		}
		else
				throw std::invalid_argument("invalid expression");	
		
	}
	if (_calculator.size() > 1)
	{
		while (!_calculator.empty())
			_calculator.pop();
		throw std::invalid_argument("invalid expression");
	}
	double result = _calculator.top();
	_calculator.pop();
	return (result);

}