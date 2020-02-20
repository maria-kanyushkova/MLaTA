#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

long long maxCost = 0;
long long totalMaxPrice = 0;

vector<long long> tokenize(string line) {
	stringstream str(line);
	vector<long long> items;
	string token;
	while (getline(str, token, ' '))
	{
		items.emplace_back(stoi(token));
	}

	return items;
}

int main()
{
	ifstream input("input7.txt");
	string line;

	auto N = 0;
	auto M = 0;
	input >> N >> M;

	getline(input, line);
	line.clear();

	vector<long long> sellers;
	sellers.reserve(N);
	getline(input, line);
	sellers = tokenize(line);

	vector<long long> consumers;
	consumers.reserve(M);
	getline(input, line);
	consumers = tokenize(line);

	sort(sellers.begin(), sellers.end());
	sort(consumers.begin(), consumers.end());

	auto sellersPosition = 0;
	auto consumersPosition = 0;
	auto sellerAgree = 0;
	auto consumerAgree = 0;

	for (size_t i = 0; i < consumers.size(); ++i)
	{
		const auto maxPrice = consumers[i];

		for (size_t j = sellersPosition; j < sellers.size(); ++j)
		{
			const auto seller = sellers[j];
			if (seller <= maxPrice)
			{
				sellersPosition++;
				sellerAgree++;
			}
			else
			{
				break;
			}
		}

		for (size_t j = consumersPosition; j < consumers.size(); ++j)
		{
			const auto consumer = consumers[j];
			if (consumer >= maxPrice)
			{
				consumersPosition++;
				consumerAgree++;
			}
			else
			{
				break;
			}
		}

		const auto minPeople = min(sellerAgree, (int)(consumerAgree - i));
		const auto nextMaxCost = maxPrice * minPeople;

		if (nextMaxCost > maxCost)
		{
			totalMaxPrice = maxPrice;
			maxCost = nextMaxCost;
		}
	}

	cout << totalMaxPrice << ' ' << maxCost << endl;
}
