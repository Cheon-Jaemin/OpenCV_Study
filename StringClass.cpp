#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void main (void)
{
	const char* str = "Open Source Computer Vision";
	string str1("Hello World");
	string str2(str, str + 11);
	string str3 = "Software Engineer";

	cout << "str1 : " << str1 << endl << "str2 : " << str2 << endl << "str3 : " << str3 << endl << endl;

	cout << "*str1.begin() : " << *str1.begin() << endl;
	cout << "str1[1] : " << str1[1] << endl;
	cout << "*(str1.endl() - 1) : " << *(str1.end() - 1) << endl << endl;

	cout << "str2.size() : " << str2.size() << endl;
	cout << "str2.length() : " << str2.length() << endl;
	cout << "str2.empty() : " << str2.empty() << endl;
	
	cout << "str3.find(\"ng\") : " << str3.find("ng") << endl<< endl;
	cout << "format(\"%s %d\", str3.c_str(), 100) : " << format("%s %d", str3.c_str(), 100) << endl << endl;

	str1.swap(str3);
	cout << "str1.swap(str3)" << endl;
	cout << "-str1 : " << str1 << endl << "-str3 : " << str3 << endl;
	str1.clear();
	cout << "str1.clear()" << endl;
	cout << "-str1 : " << endl;
}
