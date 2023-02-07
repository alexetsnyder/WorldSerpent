#pragma once
class TimeSim
{
	public:
		TimeSim();

		void tick();

	private:
		int day_ticks, night_ticks;
		int day, night;
		int days_in_month, months_in_year;
		int month, year;
};

