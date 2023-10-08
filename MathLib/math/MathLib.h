#pragma once

#ifdef MATHLIB_EXPORTS
#define MATHLIB_API __declspec(dllexport)
#else
#define MATHLIB_API __declspec(dllimport)
#endif // MATHLIB_EXPORTS

#include <SFML/System/Vector2.hpp>

MATHLIB_API const double vectorDistance(const float x1, const float y1, const float x2, const float y2);
MATHLIB_API const double vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2);
MATHLIB_API const double pythagorasTheoremFindValueOfHypo(const float opp, const float adj);
MATHLIB_API const double pythagorasTheoremFindValueOfOpp(const float hypo, const float adj);
MATHLIB_API const double pythagorasTheoremFindValueOfAdj(const float hypo, const float opp);