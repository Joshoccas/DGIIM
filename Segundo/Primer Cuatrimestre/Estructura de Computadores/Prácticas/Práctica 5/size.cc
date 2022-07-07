#include <algorithm>    // nth_element
#include <array>        // array
#include <chrono>       // high_resolution_clock
#include <iomanip>      // setw
#include <iostream>     // cout
#include <vector>       // vector

using namespace std::chrono;

const unsigned MINSIZE = 1 << 10; // minimun line size to test:  1KB
const unsigned MAXSIZE = 1 << 26; // maximun line size to test: 32MB
const unsigned GAP = 12;          // gap for cout columns
const unsigned REP = 100;         // number of repetitions of every test
const unsigned STEPS = 1e6;       // steps

int main()
{
	std::cout << "#" 
	          << std::setw(GAP - 1) << "line (B)"
	          << std::setw(GAP    ) << "time (µs)"
	          << std::endl;

	for (unsigned size = MINSIZE; size <= MAXSIZE; size *= 2)
	{
		std::vector<duration<double, std::micro>> score(REP);

		for (auto &s: score)
		{
			std::vector<char> bytes(size);

			auto start = high_resolution_clock::now();

			for (unsigned i = 0; i < STEPS; ++i)
				bytes[(i*64)&(size-1)]++;

			auto stop = high_resolution_clock::now();

			s = stop - start;
		}

		std::nth_element(score.begin(), 
		                 score.begin() + score.size() / 2, 
		                 score.end());

		std::cout << std::setw(GAP) << size
		          << std::setw(GAP) << std::fixed << std::setprecision(1)
		          << std::setw(GAP) << score[score.size() / 2].count()
		          << std::endl;
	}
}

