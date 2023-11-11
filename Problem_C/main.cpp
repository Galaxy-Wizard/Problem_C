#include <iostream>

//#include <fstream>

#include <list>
#include <map>

#include <vector>
#include <memory>

#include <bitset>

long long fkm(long long k, const long long modul);

long long s_bits(long long n, const long long modul);

int main()
{
	std::list<long long> N;

	//std::ifstream input_file("input.txt");

	//std::ofstream output_file("output.txt");

	const long long modul = 1000000000 + 7;

	//const long long Modul = 13;


	long long quantity;

	//input_file >> quantity;
	std::cin >> quantity;

	for (long long counter = 0; counter < quantity; counter++)
	{
		long long n;
		//input_file >> n;
		std::cin >> n;

		N.push_back(n);
	}

	for (auto counter_1 = N.begin(); counter_1 != N.end(); counter_1++)
	{
		long long k = *counter_1;

		{
			//long long result = 0;
			//result = fkm(k, modul);

			//std::cout	<< result << std::endl;	
		}

		{
			long long result = 0;
			result = s_bits(k, modul);

			std::cout << result << std::endl;

			//output_file << result << std::endl;
		}
	}

	return 0;
}

long long fkm(long long k, const long long modul)
{
	long long result_k = 0;

	for (long long i = 1; i <= k; i++)
	{
		long long s_i = 0;

		for (long long j = 1; j < i; j++)
		{
			long long value = i & j;

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

long long s_bits(long long n, const long long modul)
{
	const size_t maximum_bits = size_t(31) + size_t(31);

	size_t n_bits_size = 1;

	for (long long counter = 1; counter < n; counter <<= 1)
	{
		n_bits_size++;
	}

	long long result = 0;

	for (long long counter_1 = 1; counter_1 <= n; counter_1++)
	{
		std::bitset<maximum_bits> a_bits = counter_1;

		for (long long counter_2 = 1; counter_2 <= n; counter_2++)
		{
			std::bitset<maximum_bits> c_bits = 0;

			size_t real_bits = std::min(n_bits_size, maximum_bits);

			std::bitset<maximum_bits> b_bits = counter_2;

			for (size_t counter_bits = 0; counter_bits < real_bits; counter_bits++)
			{
				c_bits[counter_bits] = a_bits[counter_bits] && b_bits[counter_bits];
			}

			result += c_bits.to_ullong() % modul;
		}
	}

	result %= modul;

	return result;
}
