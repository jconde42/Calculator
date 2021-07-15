#include <iostream>
#include <cmath>
#include "Tocken.h"
#include "TockenStream.h"

// Functions to match grammer rules:
TockenStream ts;
double expression();
double term();
double primary();
void calculate();

const std::string prompt = "> ";
const std::string result = "= ";

int main(void) {
	try {
		calculate();
		return 0;
	}
	catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		std::cerr << "exception" << std::endl;
		return 2;
	}
}

void calculate()
{
		while (std::cin)
		{
			std::cout << prompt;
			Tocken t = ts.get();
			while (t.kind == print_tocken) t = ts.get();
			if (t.kind == quit_tocken) return;
			ts.putback(t);
			std::cout << result << expression() << std::endl;
		}
}

Tocken get_tocken()
{
	return Tocken();
}

double expression()
{
	double left = term();
	Tocken t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

double term()
{
	double left = primary();
	Tocken t = ts.get();
	while (true) {
		switch (t.kind) {
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) throw std::runtime_error("divide by zero");
			left /= d;
			t = ts.get();
			break;
		}
		case '%':
		{
			double d = primary();
			if (d == 0) throw std::runtime_error("divide by zero");
			left = fmod(left, d);
			t = ts.get();
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

double primary()
{
	Tocken t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') throw std::runtime_error("')' expected");
		return d;
	}
	case number_tocken:
		return t.value;
	case '-':
		return - primary();
	case '+':
		return primary();
	default:
		throw std::runtime_error("primary expected");
	}
}
