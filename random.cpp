#include "random.h"
#include <math.h>
Random::Random()
{
	n = 9036192184;
	x = 0.9036192184;
}

float Random::frandom()
{
	x = x * n;
	x = x-floor(x);
	if (x==0.0f)
		x = 0.9036192184;
	return (float) x;
}
int Random::irandom (int N)
{
	float xx = frandom() *N;
	return (int) round(xx);
}

float Random::frandom(float lo, float hi)
{
	double xx = frandom();
	xx = lo + xx * (hi-lo);
}

int Random::irandom(int lo, int hi)
{
	double xx = frandom();
	return (int) round (lo + xx * (hi-lo));

}
