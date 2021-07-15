#pragma once
#include "Tocken.h"

class TockenStream
{
public:

	TockenStream();

	Tocken get();

	void putback(Tocken t);

private:

	bool full{ false };

	Tocken buffer;
};

