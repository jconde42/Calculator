#include <iostream>
#include <cmath>
#include "Tocken.h"
#include "TockenStream.h"

// Functions to match grammer rules:
TockenStream ts;
double expression();
double term();
double primary();

int main(void) {
	try {
		while (std::cin)
		{
			std::cout << "> ";
			Tocken t = ts.get();
			while (t.kind == ';') t = ts.get();
			if (t.kind == 'q') {
				return 0;
			}
			ts.putback(t);
			std::cout << "= " << expression() << std::endl;
		}
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
	case '8':
		return t.value;
	case '-':
		return - primary();
	case '+':
		return primary();
	default:
		throw std::runtime_error("primary expected");
	}
}
