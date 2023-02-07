#pragma once
class Hex
{
	public:
		Hex();
		Hex(int q, int r);

		int q();
		int r();
		int s();

	private:
		int _q, _r, _s;
		int innerRadius;
		int outerRadius;
};

