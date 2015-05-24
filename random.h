#ifndef RANDOM_H
#define RANDOM_H

class Random
{
public:
	Random();
	float frandom();
	int irandom(int n);
	float frandom (float lo, float hi);
	int irandom (int lo, int hi);
private:
	__INT64_TYPE__ n;
	double x;

};

#endif // RANDOM_H
