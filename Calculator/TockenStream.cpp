#include "TockenStream.h"
#include "Tocken.h"
#include <iostream>

TockenStream::TockenStream()
{
}

Tocken TockenStream::get()
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	std::cin >> ch;

	switch (ch) {
	case ';':
	case 'q':
	case '(': case ')': case '+': case '-': case '*': case '/':
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
		return Tocken{ val, '8' };
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
