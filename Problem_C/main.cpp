#include <iostream>
#include <fstream>
#include <vector>

#include <list>
#include <map>

#include "kvant.h"


bool test(long long a, long long b);
std::map<long long, long long> test_2(long long a);


long long fk(long long k);

long long fkm(long long k, const long long modul);

long long fsab(long long a, long long b);
long long fnab(long long a1, long long a2, long long b1, long long b2);

long long matrix_multiplier(long long k, const long long modul, const long long correct_result);
long long matrix_multiplier_1(long long k, const long long modul, const long long correct_result);


long long fkm_sparse_matrix(long long k, const long long modul);


long long matrix_multiplier_2(long long n, const long long modul);


long long sum_km(long long k, const long long modul);

int main()
{
	std::vector<long long> N;

	std::ifstream input_file("input.txt");

	std::ofstream output_file("output.txt");

	std::ofstream correct_output_file("correct_output.txt");

	std::ofstream modul_output_file("modul_output.txt");

	std::ofstream modul_sparse_matrix("modul_sparse_matrix.txt");

	std::ofstream matrix_multiplier_output_file("matrix_multiplier.txt");

	std::ofstream matrix_multiplier_output_file_1("matrix_multiplier_1.txt");

	std::ofstream matrix_multiplier_output_file_2("matrix_multiplier_2.txt");

	std::ofstream sum_output_file("sum_output.txt");

	//const long long Modul = 1000000000 + 7;

	const long long Modul = 13;

	//auto sum_parameter = test_2(Modul);

	long long T;

	input_file >> T;

	for (long long counter = 0; counter < T; counter++)
	{
		long long n;
		input_file >> n;

		N.push_back(n);
	}

	for (int counter_T = 0; counter_T < T; counter_T++)
	{
		long long result = 0;
		long long K = N.at(counter_T);

		long long k = K;

		long long modul_result = 0;
		modul_result = fkm(k, Modul);

		modul_output_file << modul_result << std::endl;

		std::cout << "k = " << k << " ; modul_result = " << modul_result << std::endl;

		long long sum_result = 0;
		sum_result = sum_km(k, Modul);

		sum_output_file << sum_result << std::endl;

		std::cout << "k = " << k << " ; sum_result = " << sum_result << std::endl;

		//long long matrix_multiplier_result_2 = matrix_multiplier_2(k, Modul);

		//matrix_multiplier_output_file_2 << matrix_multiplier_result_2 << std::endl;

		//std::cout << "k = " << k << " ; matrix_multiplier_result_2 = " << matrix_multiplier_result_2 << std::endl;


		//long long matrix_multiplier_result_1 = matrix_multiplier_1(k, Modul, modul_result);

		//matrix_multiplier_output_file_1 << matrix_multiplier_result_1 << std::endl;

		//long long matrix_multiplier_result = matrix_multiplier(k, Modul, modul_result);

		//matrix_multiplier_output_file << matrix_multiplier_result << std::endl;

		////long long modul_sparse_matrix_result = fkm_sparse_matrix(k, Modul);

		////modul_sparse_matrix << modul_sparse_matrix_result << std::endl;

		////long long correct_result = fk(k);

		////correct_result = correct_result % Modul;

		////correct_output_file << correct_result << std::endl;

		////result = fsab(1, k);

		////result = result % Modul;

		////output_file << result << std::endl;
	}

	//std::cout << test(100, 1234) << std::endl;

	return 1;
}

long long fk(long long k)
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
	}

	return result_k;
}

long long fnab(long long a1, long long a2, long long b1, long long b2)
{
	long long result_ab = 0;

	/*///
	for (long long i = a1; i <= a2; i++)
	{
		for (long long j = b1; j <= b2; j++)
		{
			long long value = i & j;

			if (value != 0)
			{
				result_ab += value;
			}
		}
	}
	//*/

	if (a1 <= a2 && b1 <= b2)
	{
		if (a1 == a2)
		{
			for (long long j = b1; j <= b2; j++)
			{
				long long value = a1 & j;

				if (value != 0)
				{
					result_ab += value;
				}
			}
		}
		else
		{
			if (b1 == b2)
			{
				for (long long i = a1; i <= a2; i++)
				{
					long long value = i & b1;

					if (value != 0)
					{
						result_ab += value;
					}
				}
			}
			else
			{

				result_ab += fnab(a1, (a1 + a2) / 2, b1, (b1 + b2) / 2);

				result_ab += fnab(a1, (a1 + a2) / 2, (b1 + b2) / 2 + 1, b2);

				result_ab += fnab((a1 + a2) / 2 + 1, a2, b1, (b1 + b2) / 2);

				result_ab += fnab((a1 + a2) / 2 + 1, a2, (b1 + b2) / 2 + 1, b2);
			}
		}
	}

	return result_ab;
}

long long fsab(long long a, long long b)
{
	long long result_ab = 0;

	if (a <= b)
	{
		if (a == b)
		{
			result_ab = a;
		}
		else
		{
			result_ab += fsab(a, (a + b) / 2);

			result_ab += fnab(a, (a + b) / 2, (a + b) / 2 + 1, b);

			result_ab += fnab((a + b) / 2 + 1, b, a, (a + b) / 2);

			result_ab += fsab((a + b) / 2 + 1, b);
		}
	}

	return result_ab;
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


long long fkm_sparse_matrix(long long k, const long long modul)
{
	long long result_k = 0;

	if (k > 0)
	{
		std::list<long long> sparse_matrix;
		std::list<long long> sparse_matrix_x;
		std::list<long long> sparse_matrix_y;

		for (long long i = 1; i <= k; i++)
		{
			for (long long j = 1; j <= k; j++)
			{
				long long value = i & j;

				if (value != 0)
				{
					sparse_matrix.push_back(value);
					sparse_matrix_x.push_back(i);
					sparse_matrix_y.push_back(j);
				}
			}
		}

		for (std::list<long long>::iterator iterator_sparse_matrix = sparse_matrix.begin(); iterator_sparse_matrix != sparse_matrix.end(); iterator_sparse_matrix++)
		{
			long long value = *iterator_sparse_matrix;
			result_k += value;
		}

		result_k %= modul;
	}

	return result_k;
}




long long matrix_multiplier(long long k, const long long modul, const long long correct_result)
{
	long long result_k = 0;

	long long a = 0;
	long long b = 0;

	int n_bits = 1;

	long long value_k2 = 1;
	for (; value_k2 < k; value_k2 <<= 1)
	{
		n_bits++;
	}

	Kvant<long long> A;
	
	int r_bits = n_bits;

	for (long long q = 1; q <= r_bits; q++)
	{
		for (long long l = 1; l <= k; l++)		
		{
			a = 0;

			long long temp = l * k;

			for (long long i = 1; i <= n_bits; i++)
			{
				long long aq = 1;

				aq <<= q - 1;

				long long temp_1 = temp;

				temp_1 >>= i - 1;

				aq &= temp_1;

				a += aq;
			}

			A.insert(a);
		}
	}


	for (long long j = 1; j <= k; j++)
	{
		int j_bits = 1;

		long long value_j2 = 1;
		for (; value_j2 < j; value_j2 <<= 1)
		{
			j_bits++;
		}


		long long bi = j & value_j2;

		b += bi;
	}

	for (long counter = 1; counter <= 10000; counter++)
	{
		a = A.get();

		result_k = (a * b) % modul;

		//std::cout << "k = " << k << " ;a = " << a << " ;b = " << b << " ;result_k = " << result_k << std::endl;
		
		if (correct_result == result_k)
		{
			std::cout << "k = " << k << " ;a = " << a << " ;b = " << b << " ;result_k = " << result_k << "; counter = " << counter << std::endl;
			break;
		}
	}

	return result_k;
}

bool test(long long a, long long b)
{
	long long t = a;

	if (t < b)
	{
		t = b;
	}

	int t_bits = 1;

	long long value_t2 = 1;
	for (; value_t2 < t; value_t2 <<= 1)
	{
		t_bits++;
	}

	for (long long i = 1; i < t_bits; i++)
	{
		long long value_i2 = 1;
		for (; (value_i2 << 1) < i; value_i2 <<= 1);

		long long v1 = 0;
		long long v2 = 0;

		v1 = (value_i2 * a) & ((value_i2 << 1) & b);

		v2 = value_i2 * (a & ((value_i2 << 1) & b));

//		std::cout << "v1 = " << v1 << "; v2 = " << v2 << std::endl;

		if (v1 != v2)
		{
			return false;
		}
	}

	return true;
}


long long matrix_multiplier_1(long long k, const long long modul, const long long correct_result)
{
	long long result_k = 0;

	long long a = 0;
	long long b = 0;

	Kvant<long long> A;
	Kvant<long long> B;

	int n_bits = 1;

	long long value_k2 = 1;
	for (; value_k2 < k; value_k2 <<= 1)
	{
		n_bits++;
	}

	long long temp = 0;

	for (long long l = 1; l <= k+1; l++)
	{
		temp += k;

		for (long long i = 1; i <= n_bits * n_bits; i++)
		{
			a = temp >> (i - 1);

			A.insert(a);
		}
	}


	for (long long j = 1; j <= k+1; j++)
	{
		b = j;

		B.insert(b);
	}

	const long attempts_to_guess = 1;

	const long attempts_to_guess_a = attempts_to_guess;
	const long attempts_to_guess_b = attempts_to_guess;

	const double requested_accuracy = 1.0 / attempts_to_guess_a / attempts_to_guess_b;

	bool solved = false;

	bool attempts_limit_hit = false;

	for (long counter_a = 1; counter_a <= attempts_to_guess_a; counter_a++)
	{
		a = A.get();

		for (long counter_b = 1; counter_b <= attempts_to_guess_b; counter_b++)
		{
			double accuracy = 1.0 / double(counter_a) / double(counter_b) * 100.0;

			if (accuracy < requested_accuracy)
			{
				attempts_limit_hit = true;

				break;
			}

			b = B.get();

			result_k = (a * b) % modul;

			if (correct_result == result_k)
			{
				std::cout << "k = " << k << " ;a = " << a << " ;b = " << b << " ;result_k = " << result_k << "; accuracy (%) = " << accuracy << std::endl;

				solved = true;

				break;
			}
		}

		if (solved)
		{
			break;
		}

		if (attempts_limit_hit)
		{
			break;
		}
	}

	return result_k;
}




long long matrix_multiplier_2(long long n, const long long modul)
{
	long long result_s = 0;


	long long sx = 0;

	for (long long x = 1; x <= n; x++)
	{
		int x_bits = 1;

		long long value_x2 = 1;
		for (; value_x2 < x; value_x2 <<= 1)
		{
			x_bits++;
		}

		auto deg_2_x = x_bits;

		long long sy = 0;

		for (long long y = 1; y <= n; y++)
		{
			int y_bits = 1;

			long long value_y2 = 1;
			for (; value_y2 < y; value_y2 <<= 1)
			{
				y_bits++;
			}

			auto deg_2_y = y_bits;

			for (auto counter_y = 1; counter_y <= deg_2_y; counter_y++)
			{
				sy += counter_y;
			}
		}

		for (auto counter_x = 1; counter_x <= deg_2_x; counter_x++)
		{
			sx += counter_x * sy;
		}
	}

	long long s = sx;

	result_s = s % modul;

	return result_s;
}

long long sum_km(long long n, const long long modul)
{
	long long result_s = 0;

	long long s = 0;

	int m_bits = 1;

	long long value_m2 = 1;
	for (; value_m2 < modul; value_m2 <<= 1)
	{
		m_bits++;
	}

	for (long long a = 1; a <= n; a++)
	{
		long long s_a = 0;

		int a_bits = 1;

		long long value_a2 = 1;
		for (; value_a2 < a; value_a2 <<= 1)
		{
			a_bits++;
		}

		for (long long b = 1; b < a; b++)
		{
			/*/
			int b_bits = 1;

			long long value_b2 = 1;
			for (; value_b2 < b; value_b2 <<= 1)
			{
				b_bits++;
			}

			auto ab_bits = std::min(a_bits, b_bits);
			///*/

			auto ab_bits = a_bits;

			for (int k = 1; k <= ab_bits; k++)
			{
				auto a_2_k = a & (long long(1) << (k - 1));
				bool temp_a_k = bool( a_2_k >> (k - 1) );
				bool temp_b_k = bool( (b & (long long(1) << (k - 1))) >> (k - 1) );

				bool temp_ab = temp_a_k && temp_b_k;

				if (temp_ab)
				{
					s_a += (a_2_k % modul);
				}
			}
			
			s_a %= modul;
		}

		s_a <<= 1;

		s_a += a;

		s += s_a;

		s %= modul;
	}

	result_s = s % modul;

	return result_s;
}

std::map<long long, long long> test_2(long long a)
{
	std::map<long long, long long> result;

	int a_bits = 1;

	long long value_a2 = 1;
	for (; value_a2 <= a; value_a2 <<= 1)
	{
		a_bits++;
	}

	for (long long t = 1; t < a_bits; t++)
	{
		long long count_t = 0;
		
		for (long long i = 1; i <= a; i++)
		{
			long long temp_1 = long long(1) << (t - 1);

			if (i & temp_1)
			{
				count_t++;
			}
		}

		result.insert(std::make_pair(t - 1, count_t));
		//std::cout << "a = " << a << "; t-1 = " << t-1 << "; count_t = " << count_t << std::endl;
	}

	return result;
}
