// WorldSerpent.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>

int main()
{
    using clock = std::chrono::high_resolution_clock;
    bool running = true;
    auto last_time = clock::now();

    while (running)
    {
        auto delta_time = clock::now() - last_time;
        last_time = clock::now();

        //simulate time
        
        //simulate world

        //display menu

        //wait for input 
    }
}


