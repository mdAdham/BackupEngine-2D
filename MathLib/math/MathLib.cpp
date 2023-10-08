#include "MathLib.h"
#include <math.h>

const double vectorDistance(const float x1, const float y1, const float x2, const float y2)
{
    const float dx = x2 - x1;
    const float dy = y2 - y1;

    return sqrt(pow(dx, 2) + pow(dy, 2));
}

const double vectorDistance(sf::Vector2f vec1, sf::Vector2f vec2)
{
    const sf::Vector2f dVec = vec2 - vec1;

    return sqrt(pow(dVec.x, 2) + pow(dVec.y, 2));
}

const double pythagorasTheoremFindValueOfHypo(const float opp, const float adj)
{
    const double result = sqrt(pow(opp, 2) + pow(adj, 2));
    return result;
}

const double pythagorasTheoremFindValueOfOpp(const float hypo, const float adj)
{
    const double result = sqrt(pow(hypo, 2) - pow(adj, 2));
    return result;
}

const double pythagorasTheoremFindValueOfAdj(const float hypo, const float opp)
{
    const double result = sqrt(pow(hypo, 2) - pow(opp, 2));
    return result;
}
