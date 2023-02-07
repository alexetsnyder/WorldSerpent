#include "Hex.h"

Hex::Hex()
{
	_q = 0;
	_r = 0;
	_s = 0;
	innerRadius = 0;
	outerRadius = 0;
}

Hex::Hex(int q, int r)
{
	_q = q;
	_r = r;
	_s = -q - r;
	innerRadius = 0;
	outerRadius = 0;
}

int Hex::q()
{
	return _q;
}

int Hex::r()
{
	return _r;
}

int Hex::s()
{
	return _s;
}
