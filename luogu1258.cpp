#include<iostream>


using namespace std;
float s, a, b;

int main()
{
	cin >> s >> a >> b;
	float x = s * (a + b) / (b + 3*a);

	float ans = x / b + (s - x) / a;
	printf("%.6f", ans);

	return 0;
}
