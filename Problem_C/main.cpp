#include <iostream>

//#include <fstream>

#include <list>
#include <map>

#include <vector>
#include <memory>

#include <bitset>

void s_n_1_calculator(long long k, const long long modul, std::map<long long, long>& s_n_1);
void s_n_calculator(long long n, const long long modul, std::map<long long, long> &s_n, std::map<long long, long> &s_n_1);

long long fkm(long long k, const long long modul);

long long s_r(long long n, const long long modul);

long long s_bits(long long n, const long long modul);

const long long maximum_k = 20000;

int main()
{
	std::list<long long> N;

	//std::ifstream input_file("input.txt");

	//std::ofstream output_file("output.txt");

	const long long modul = 1000000000 + 7;

	//const long long Modul = 13;

	std::auto_ptr<std::map<long long, long>> s_n(new std::map<long long, long>);

	if (s_n.get() != nullptr)
	{
		std::auto_ptr<std::map<long long, long>> s_n_1(new std::map<long long, long>);

		if (s_n_1.get() != nullptr)
		{
			//s_n_1_calculator(maximum_k, modul, *s_n_1);
			//s_n_calculator(maximum_k, modul, *s_n, *s_n_1);

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

				if (k <= maximum_k)
				{
					//long long result = 0;
					//result = fkm(k, modul);

					//std::cout	<< result << std::endl;	

					long long result = 0;
					result = s_bits(k, modul);

					std::cout << result << std::endl;

					//output_file << result << std::endl;

					//std::cout << s_n->at(k) << std::endl;

					//output_file << s_n->at(k) << std::endl;
				}
				else
				{
					//output_file << 0 << std::endl;
					std::cout << long(0) << std::endl;
				}
			}

			return 1;
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


long long s_r(long long n, const long long modul)
{
	if (n < 1)
	{
		return 0;
	}

	if (n == 1)
	{
		return 1;
	}

	long long result = 0;

	long long s_1 = 0;

	for (long long counter = 1; counter < n; counter++)
	{
		s_1 += counter & n;
	}

	long long s_2 = s_r(n - 1, modul);

	result = s_2 + 2 * s_1 + n;

	result %= modul;

	return result;
}

void s_n_calculator(long long n, const long long modul, std::map<long long, long> &s_n, std::map<long long, long> &s_n_1)
{
	if (n > 0)
	{
		s_n.insert(std::make_pair(1, 1));

		for (long long k = 2; k <= n; k++)
		{
			long long sum_1 = s_n_1.at(k);

			long long sum_2 = 0;

			sum_2 = k;

			sum_2 += 2 * sum_1;

			sum_2 += s_n[k - 1];

			s_n.insert(std::make_pair(k, long(sum_2 % modul)));
		}
	}
}

void s_n_1_calculator(long long n, const long long modul, std::map<long long, long>& s_n_1)
{
	if (n > 0)
	{
		s_n_1.insert(std::make_pair(1, 1));

		for (long long k = 2; k <= n; k++)
		{
			long long sum_1 = 0;

			for (long long a = 1; a < k; a++)
			{
				sum_1 += a & k;
			}

			s_n_1.insert(std::make_pair(k, long(sum_1 % modul)));
		}
	}
}

long long s_bits(long long n, const long long modul)
{
	const size_t maximum_bits = 100;

	std::vector<std::bitset<maximum_bits>> a_bits;
	std::vector<std::bitset<maximum_bits>> b_bits;

	a_bits.resize(n);
	b_bits.resize(n);

	for (long long counter = 0; counter < n; counter++)
	{
		a_bits[counter] = (counter + 1);
		b_bits[counter] = (counter + 1);
	}

	long long result = 0;

	for (long long counter_1 = 0; counter_1 < n; counter_1++)
	{
		for (long long counter_2 = 0; counter_2 < n; counter_2++)
		{
			std::bitset<maximum_bits> c_bits = 0;

			for (size_t counter_bits = 0; counter_bits < maximum_bits; counter_bits++)
			{
				c_bits[counter_bits] = a_bits[counter_1][counter_bits] && b_bits[counter_2][counter_bits];
			}

			result += c_bits.to_ullong() % modul;
		}
	}

	result %= modul;

	return result;
}
