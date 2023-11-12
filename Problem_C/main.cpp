#include <iostream>

//#include <fstream>

#include <list>
#include <map>

#include <vector>
#include <memory>

#include <bitset>

unsigned long long fkm(unsigned long long k, const unsigned long long modul);

unsigned long long s_bits(unsigned long long n, const unsigned long long modul);

int main()
{
	std::list<unsigned long long> N;

	//std::ifstream input_file("input.txt");

	//std::ofstream output_file("output.txt");

	const unsigned long long modul = 1000000000 + 7;

	//const unsigned long long Modul = 13;


	unsigned long long quantity;

	//input_file >> quantity;
	std::cin >> quantity;

	for (unsigned long long counter = 0; counter < quantity; counter++)
	{
		unsigned long long n;
		//input_file >> n;
		std::cin >> n;

		N.push_back(n);
	}

	for (auto counter_1 = N.begin(); counter_1 != N.end(); counter_1++)
	{
		unsigned long long k = *counter_1;

		/*///
		{
			unsigned long long result = 0;
			result = fkm(k, modul);

			std::cout	<< result << std::endl;	
		}
		///*/

		{
			unsigned long long result = 0;
			result = s_bits(k, modul);

			std::cout << result << std::endl;

			//output_file << result << std::endl;
		}
	}

	return 1;
}

unsigned long long fkm(unsigned long long k, const unsigned long long modul)
{
	unsigned long long result_k = 0;

	for (unsigned long long i = 1; i <= k; i++)
	{
		unsigned long long s_i = 0;

		for (unsigned long long j = 1; j < i; j++)
		{
			unsigned long long value = i & j;

			if (value != 0)
			{
				s_i += value;
			}
		}

		s_i <<= 1;

		result_k += s_i;

		result_k += i;

		result_k %= modul;
	}

	result_k %= modul;

	return result_k;
}

unsigned long long s_bits(unsigned long long n, const unsigned long long modul)
{
	const size_t maximum_bits = size_t(31) + size_t(31);

	size_t n_bits_size = 1;

	for (unsigned long long counter = 1; counter < n; counter <<= 1)
	{
		n_bits_size++;
	}

	unsigned long long result = 0;

	for (unsigned long long counter_1 = 1; counter_1 <= n; counter_1++)
	{
		const std::bitset<maximum_bits> a_bits = counter_1;

		unsigned long long sum_bits = 0;

		for (unsigned long long counter_2 = 1; counter_2 < counter_1; counter_2++)
		{
			const auto b_bits = counter_2;

			auto c_bits = a_bits;

			c_bits &= b_bits;

			sum_bits += c_bits.to_ullong() << 1;
		}

		result += sum_bits;

		result += counter_1;

		result %= modul;
	}

	result %= modul;

	return result;
}
