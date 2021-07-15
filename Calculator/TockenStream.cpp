#include "TockenStream.h"
#include "Tocken.h"
#include <iostream>

TockenStream::TockenStream()
{
}

Tocken TockenStream::get()
// read characters from std::cin and compose a Tocken
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	std::cin >> ch;

	switch (ch) {
	case print_tocken:
	case quit_tocken:
	case '(': 
	case ')': 
	case '+': 
	case '-': 
	case '*': 
	case '/':
		Tocken t;
		t.kind = ch;
		return t;
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		std::cin.putback(ch);
		double val;
		std::cin >> val;
		return Tocken{ val, number_tocken };
	}
	default:
		throw std::runtime_error("Bad tocken");
	}
}

void TockenStream::putback(Tocken t)
{
	if (full) throw std::runtime_error("putback() into a full buffer");
	buffer = t;
	full = true;
}
