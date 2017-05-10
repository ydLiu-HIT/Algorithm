#include <iostream>
#include <vector>
#include <time.h>
#include <list>
#include <limits>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

using namespace std;


vector<int> haveNotBelong(vector<int> &v1,vector<int> &v2) //sub
{
	vector<int> x = v1;
	vector<int>::iterator it;
	vector<int>::iterator itt;
	// sort(x.begin(), x.end());
	it = v2.begin();
	itt = x.begin();
	while(itt < x.end() && it < v2.end())
	{
		if (*itt == *it)
		{
			itt = x.erase(itt);
			// itt++;
			it++;
		}
		else
		{
			itt++;
		}
	}
	// show_vector(x);
	return x;
}

void show_vector(vector<int> &X)
{
	vector<int>::iterator it = X.begin();
	while(it < X.end())
	{
		cout<<*it<<" ";
		it++;
	}
	cout<<endl;
}

int main(int argc, char const *argv[])
{
	int a = 5;
	int b = 10;
	float c = (float)a/b;
	cout<<"c = "<<c<<endl;

	return 0;
}