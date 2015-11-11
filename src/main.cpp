#include <string>
#include "WFEHashMap.cpp"

using namespace std;

int main() {
	WFEHashMap x(5);
	string a = "abcde";
	char *b = new char[6];
	strcpy(b, a.c_str());

	x.put(b, 5);
	x.put(b, 10);
	return 0;
}
