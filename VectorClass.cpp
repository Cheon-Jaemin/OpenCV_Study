#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

vector<int> func()
{
	vector<int> v{ -10, -20 };
	return v;
}

void main(void)
{
	vector<int> a;
	a.push_back(10);
	a.push_back(20);
	a.push_back(30);
	a.push_back(40);
	cout << "º¤ÅÍ a : " << a.size() << endl;
	for (int i = 0; i < a.size(); i++)
	{
		cout << "º¤ÅÍ aÀÇ ¿ø¼Ò : " << a[i] << endl;
	}

	vector<string> b{ "I", "love", "you" };
	for (int i = 0; i < b.size(); i++)
	{
		cout << "º¤ÅÍ bÀÇ ¿ø¼Ò : " << b[i] << endl;
	}

	vector<int> c(a.begin(), a.begin() + 3);
	for (int i = 0; i < c.size(); i++)
	{
		cout << "º¤ÅÍ cÀÇ ¿ø¼Ò : " << c[i] << endl;
	}

	a.clear();
	cout << "º¤ÅÍ a : " << a.size() << endl;

	vector<int> d = func();
	for (int i = 0; i < d.size(); i++)
	{
		cout << "º¤ÅÍ dÀÇ ¿ø¼Ò : " << d[i] << endl;
	}
}
