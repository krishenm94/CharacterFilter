//
// Character Filter
//
// (C) By Autonomous Intelligent Driving GmbH
//
#include <iostream>
#include <string>
#include <vector>
#include <iterator>

class AlphaNumericPredicate {
	// Fill implementation here
	const static int Int_0 = 48;
	const static int Int_9 = 57;
	const static int Int_A = 65;
	const static int Int_Z = 90;
	const static int Int_a = 97;
	const static int Int_z = 122;

public:
	bool operator()(char c)
	{
		auto asciiCode = static_cast<int>(c);
		if ((asciiCode >= Int_0 && asciiCode <= Int_9) ||
			(asciiCode >= Int_A && asciiCode <= Int_Z) ||
			(asciiCode >= Int_a && asciiCode <= Int_z))
		{
			return true;
		}

		return false;
	}
};

template<typename InputIterator, typename OutputIterator, typename UnaryPredicate>
OutputIterator filter(
	InputIterator first,
	InputIterator last,
	OutputIterator result,
	UnaryPredicate predicate,
	size_t history_size
)
{
	// Fill implementation here
	for (auto iter = first; iter != last; iter = std::next(iter))
	{
		const auto value = *iter;
		if (!predicate(value))
		{
			result = std::next(iter);
			continue;
		}

		auto hasOccuredWithinHistory = false;

		if (iter == first)
		{
			continue;
		}

		for (auto historyIter = std::prev(iter);
			true;
			historyIter = std::prev(historyIter))
		{
			if (historyIter == first)
			{
				break;
			}

			const auto distance = std::distance(historyIter, iter);
			if (distance > history_size)
			{
				break;
			}

			if (*historyIter == *iter)
			{
				hasOccuredWithinHistory = true;
			}
		}

		if (!hasOccuredWithinHistory)
		{
			result = std::next(iter);
		}
		else
		{
			result = iter;
			break;
		}

	}
	return result;
}

//
// Filter string. Helper for mapping binary blobs to strings.
//
std::string filter_string(std::string source, size_t history_size)
{
	source.erase(filter(std::begin(source), std::end(source),
		std::begin(source),
		AlphaNumericPredicate{}, history_size),
		std::end(source));
	return source;
}

//
// Main entry point.
//
int main()
{
	while (!std::cin.eof())
	{
		size_t history_size = 0;
		std::cin >> history_size;
		std::string source;
		std::getline(std::cin, source);
		std::cout << filter_string(source, history_size) << std::endl;
	}
	return 0;
}

// Example input
//0 $Mamma
//
//1 $Mamma
//
//3 $Mamma
//
//3 $MammaMamma
