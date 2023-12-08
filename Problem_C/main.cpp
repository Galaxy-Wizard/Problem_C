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

		///*///
		{
			unsigned long long result = 0;
			result = s_bits(k, modul);

			std::cout << result << std::endl;

			//output_file << result << std::endl;
		}
		///*/
	}

	return 0;
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
	#define maximum_bits (size_t(31) + size_t(31))

	size_t n_bits_size = 1;

	for (unsigned long long counter = 1; counter <= n; counter <<= 1)
	{
		n_bits_size++;
	}

	if (n_bits_size < maximum_bits)
	{

		std::vector<long> set_bits_quantity_by_bit;

		set_bits_quantity_by_bit.resize(n_bits_size);

		for (unsigned long long counter = 1; counter <= n; counter++)
		{
			for (long n_bits_counter = 0; n_bits_counter < n_bits_size; n_bits_counter++)
			{
				if (counter & (1ULL << n_bits_counter))
				{
					set_bits_quantity_by_bit[n_bits_counter]++;
				}
			}
		}

		unsigned long long result = 0;

		for (long n_bits_counter = 0; n_bits_counter < n_bits_size; n_bits_counter++)
		{
			result += (set_bits_quantity_by_bit[n_bits_counter] ) * ((unsigned long long)(set_bits_quantity_by_bit[n_bits_counter]) * (1ULL << n_bits_counter));
			result %= modul;
		}

		result %= modul;

		return result;
	}

	return 0;
}
