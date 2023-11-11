#include <iostream>

#include <fstream>

#include <vector>
#include <map>

std::map<long long, long> s_n;
void s_n_calculator(long long n, const long long modul);

long long fkm(long long k, const long long modul);

long long s_r(long long n, const long long modul);

const long long maximum_k = 50000;

int main()
{
	std::vector<long long> N;

	//std::ifstream input_file("input.txt");

	//std::ofstream output_file("output.txt");

	const long long Modul = 1000000000 + 7;

	//const long long Modul = 13;

	s_n_calculator(maximum_k, Modul);

	long long T;

	//input_file >> T;
	std::cin >> T;

	for (long long counter = 0; counter < T; counter++)
	{
		long long n;
		//input_file >> n;
		std::cin >> n;

		N.push_back(n);
	}

	for (int counter_T = 0; counter_T < T; counter_T++)
	{
		long long result = 0;
		long long K = N.at(counter_T);

		long long k = K;


		if (k <= maximum_k)
		{
			//long long modul_result = 0;
			//modul_result = fkm(k, Modul);

			//std::cout	<< modul_result << std::endl;	

			//output_file << modul_result << std::endl;

			std::cout << s_n[k] << std::endl;

			//output_file << s_n[k] << std::endl;
		}
		else
		{
			//output_file << 0 << std::endl;
			std::cout << 0 << std::endl;
		}
	}

	return 1;
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

void s_n_calculator(long long n, const long long modul)
{
	if (n > 0)
	{
		s_n.insert(std::make_pair(1, 1));

		for (long long k = 2; k <= n; k++)
		{
			long long sum_1 = 0;

			for (long long a = 1; a < k; a++)
			{
				sum_1 += a & k;
			}

			long long sum_2 = 0;

			sum_2 = k;

			sum_2 += 2 * sum_1;

			sum_2 += s_n[k - 1];

			s_n.insert(std::make_pair(k, long(sum_2 % modul)));
		}
	}
}
