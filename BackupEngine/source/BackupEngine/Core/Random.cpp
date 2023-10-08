#include "bcpch.h"
#include "Random.h"
#include <random>

int Utility::Core::Random::Int()
{
	std::random_device rd;
	std::uniform_int_distribution<int> randomInt = std::uniform_int_distribution<int>(0, RAND_MAX);
	return randomInt(rd);
}

int Utility::Core::Random::Int(int min, int max)
{
	std::random_device rd;
	std::uniform_int_distribution<int> randomInt = std::uniform_int_distribution<int>(min, max);
	return randomInt(rd);
}

float Utility::Core::Random::Float()
{
	std::random_device rd;
	std::uniform_real_distribution<float> randomFloat = std::uniform_real_distribution<float>(0.0f, 1234556788.f);
	return randomFloat(rd);
}

float Utility::Core::Random::Float(float min, float max)
{
	std::random_device rd;
	std::uniform_real_distribution<float> randomFloat = std::uniform_real_distribution<float>(min, max);
	return randomFloat(rd);
}
