/*************************************************************************
	> File Name: setCover.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年05月03日 星期三 19时20分19秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <time.h>
#include <list>
#include <limits>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>

// const int COUNT = 1000;
using namespace std;

void show_vector(vector<int> &X);
vector<int> set_union_count(vector<vector<int> > &F);
vector<int> haveNotBelong(vector<int> &v1,vector<int> &v2);

void randomInit(vector<int> &X, vector<vector<int> > &F, int COUNT)
{
	vector<int> tempvector;
	tempvector.reserve(20);
	int j = 0;
	srand((int)time(0));
	//random set X
	for (int i = 0; i < COUNT; ++i)
	{
		X.push_back(i);
	}
	//random set F
	while(tempvector.size() < 20)
	{
		tempvector.push_back(rand()%COUNT);
		sort(tempvector.begin(), tempvector.end());
		tempvector.erase(unique(tempvector.begin(),tempvector.end()), tempvector.end());//unique return the iterator of the fisrt repreat number
	}
	F.push_back(tempvector);

	vector<int> vectorUnion;
	vector<int> vectorSub;
	int Xsize = X.size();
	int vectorUnionsize = 0;
	int vectorSubsize = 0;
	int n, n1, n2;
	// show_vector(vectorSub);
	// show_vector(X);
	vector<int> v;

	while(X.size() - vectorUnionsize > 20)
	{
		vectorUnion = set_union_count(F);
		vectorSub = haveNotBelong(X, vectorUnion);
		// cout<<"X.size() - vectorUnion.size() = "<<X.size() - vectorUnionsize<<endl;
		n = (rand()%20) + 1;
		n1 = rand()%n + 1; //numbers from X - S0
		n2 = n - n1;//numbers from set_union
		// cout<<"n = "<<n<<"\t"<<"n1 = "<<n1<<"\t"<<"n2 = "<<n2<<endl;
		vectorUnionsize = vectorUnion.size();
		// cerr<<"vectorUnionsize = "<<vectorUnionsize<<endl;
		if(X.size()-vectorUnionsize<=20) break;
		vectorSubsize = vectorSub.size();
		while(v.size() < n2)
		{
			v.push_back(vectorUnion[rand()%vectorUnionsize]);
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(),v.end()), v.end());
		}
		while(v.size() < n)
		{
			v.push_back(vectorSub[rand()%vectorSubsize]);
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(),v.end()), v.end());
		}//-------------------F is a sorted vector of all his members
		// show_vector(v);
		F.push_back(v);
		v.clear();
		// cout<<"v.size = "<<v.size()<<endl;
	}

	vectorUnion = set_union_count(F);
	vectorSub = haveNotBelong(X, vectorUnion);
	F.push_back(vectorSub);

	v.clear();
	while(F.size() < COUNT)
	{
		n = (rand()%20)+1;
		while(v.size() < n)
		{
			v.push_back(rand()%COUNT);
			sort(v.begin(), v.end());
			v.erase(unique(v.begin(),v.end()), v.end());
		}
		F.push_back(v);
		v.clear();
	}
}

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
			if (*itt < *it)
			{
				itt++;
			}
			else
			{
				it++;
			}
		}
	}
	// show_vector(x);
	return x;
}

vector<int> set_union_count(vector<vector<int> > &F)
{
	if (F.size() == 1)
	{
		// show_vector(F[0]);
		return F[0];
	}
	vector<vector<int> >::iterator it;
	vector<int> v1;
	vector<int> v2;
	it = F.begin();
	v1 = *it;
	it++;
	// v2 = *it;
	while(it < F.end())
	{
		v2 = *it;
		vector<int> v;
		sort(v1.begin(), v1.end());
		sort(v2.begin(), v2.end());
		set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));
		it++;
		v1 = v;
	}
	
	return v1;
}

vector<int> set_union_vector(vector<int> &v1, vector<int> &v2)
{
	vector<int> v;
	// sort(v1.begin(), v1.end());
	// sort(v2.begin(), v2.end());
	set_union(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));
	return v;
}

int set_insertsection_count(vector<int> &v1, vector<int> &v2)
{
	vector<int> v;
	// sort(v1.begin(), v1.end());
	// sort(v2.begin(), v2.end());
	set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),back_inserter(v));
	return v.size();
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

void greedy_setCover(vector<int> &X, vector<vector<int> > &F)
{
	vector<int> U = X;
	vector<vector<int> > C;
	vector<vector<int> > C0 = F;
	// C.reserve(COUNT);
	int maxcnt = 0;
	int intersectionNum = 0;
	// int indexChoose = 0;
	int m = 0;
	int n = 0;

	vector<vector<int> >::iterator it;

	while(!U.empty())
	{
		it = C0.begin();
		while(it < C0.end())
		{
			intersectionNum = set_insertsection_count(U,*it);
			if(maxcnt < intersectionNum)
			{
				maxcnt = intersectionNum;
				n = m;
			}
			m++;
			it++;
		}
		U = haveNotBelong(U, C0[n]);
		C.push_back(C0[n]);
		C0.erase(C0.begin()+n);
		m = n = 0;
		maxcnt = 0;
	}

	// cout<<"---------------------------------"<<endl;
	// vector<vector<int> >::iterator it2 = C.begin();
	// while(it2 < C.end())
	// {
	// 	show_vector(*it2);
	// 	it2++;
	// }
}

void line_program_setCover(vector<int> &X, vector<vector<int> > &F)
{
	vector<int> U;
	// vector<int> value;
	vector<vector<int> > C;
	vector<vector<int> > C0 = F;
	// value.reserve(COUNT);

	vector<vector<int> >::iterator itc;

	itc = F.begin();
	// while(itc < F.end())
	// {
	// 	value.push_back((*itc).size());//(*itc).size()
	// 	itc++;
	// }
	float score = std::numeric_limits<int>::max(); //std::numeric_limits<E>::max();
	float temp;
	int indexChoose;
	while(U.size() != X.size())
	{
		// cout<<"U.size() = "<<U.size()<<endl;
		for (int i = 0; i < C0.size(); ++i)
		{
			temp = (float)1/haveNotBelong(C0[i], U).size();
			if (score > temp)
			{
				score = temp;
				indexChoose = i;
			}
		}
		C.push_back(C0[indexChoose]);
		if (U.size() == 0)
		{
			U = C0[indexChoose];
		}else
		{
			U = set_union_vector(U,C0[indexChoose]);
		}

		C0.erase(C0.begin()+indexChoose);
		score = 0;
	}
	// cout<<"---------------------------------"<<endl;
	// vector<vector<int> >::iterator it2 = C.begin();
	// while(it2 < C.end())
	// {
	// 	show_vector(*it2);
	// 	it2++;
	// }
}

void print_all_solutions(vector<int> &X, vector<vector<int> > &F)
{

}

int main(int argc, char const *argv[])
{
	vector<int> X;
	vector<vector<int> > F;
	system("rm time.txt");

	char Time[20] = "time.txt";
	ofstream timeOut(Time, ios::app);

	for (int i = 100; i <= 5000; i = i+100)
	{
		X.clear();
		F.clear();
		cout<<"count = "<<i<<endl;
		X.reserve(i);
		// cout<<"begin Inital the data......"<<endl;
		randomInit(X, F,i);
		// cout<<"have successfuly Inital the data!"<<endl;

		// cout<<"members of F....."<<endl;
		// int j = 1;
		// vector<vector<int> >::iterator it2 = F.begin();
		// while(it2 < F.end())
		// {
		// 	cout<<"set"<<j<<":	";
		// 	show_vector(*it2);
		// 	it2++;
		// 	j++;
		// }
		timeOut<<i<<"\t";
		clock_t a1 = clock();
		// cout<<"greedy_setCover Method Solution:"<<endl;
		greedy_setCover(X,F);
		clock_t b1 = clock();
		cout<<"greedy time: "<<(b1-a1)<<"(ms)"<<endl;
		// cout<<"greedy_setCover time:"<<b1-a1<<endl;
		timeOut<<(double)(b1-a1)/CLOCKS_PER_SEC<<"\t";

		// cout<<"line_program_setCover Method Solution:"<<endl;
		clock_t a2 = clock();
		line_program_setCover(X,F);
		clock_t b2 = clock();
		cout<<"line_program time:"<<b2-a2<<"(ms)"<<endl;
		timeOut<<(double)(b2-a2)/CLOCKS_PER_SEC<<endl;
	}
	
	return 0;
}

