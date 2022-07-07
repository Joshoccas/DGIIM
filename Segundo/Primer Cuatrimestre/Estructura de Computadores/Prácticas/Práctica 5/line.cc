#include <algorithm>    // nth_element
#include <array>        // array
#include <chrono>       // high_resolution_clock
#include <iomanip>      // setw
#include <iostream>     // cout
#include <vector>       // vector

using namespace std::chrono;

const unsigned MAXLINE = 1024; // maximun line size to test
const unsigned GAP = 12;       // gap for cout columns
const unsigned REP = 100;      // number of repetitions of every test

int main()
{
	std::cout << "#" 
	          << std::setw(GAP - 1) << "line (B)"
	          << std::setw(GAP    ) << "time (µs)"
	          << std::endl;

	for (unsigned line = 1; line <= MAXLINE; line <<= 1) // line in bytes
	{
		std::vector<duration<double, std::micro>> score(REP);

		for (auto &s: score)
		{
			std::vector<char> bytes(1 << 24); // 16MB

			auto start = high_resolution_clock::now();

			for (unsigned i = 0; i < bytes.size(); i += line)
				bytes[i] ^= 1;

			auto stop = high_resolution_clock::now();

			s = stop - start;
		}

		std::nth_element(score.begin(), 
		                 score.begin() + score.size() / 2, 
		                 score.end());

		std::cout << std::setw(GAP) << line
		          << std::setw(GAP) << std::fixed << std::setprecision(1)
		          << std::setw(GAP) << score[score.size() / 2].count()
		          << std::endl;
	}
}

