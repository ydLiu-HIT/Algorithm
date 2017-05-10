/*************************************************************************
	> File Name: graph.cpp
	> Author: 
	> Mail: 
	> Created Time: 2017年04月30日 星期日 12时12分57秒
 ************************************************************************/

#include <iostream>  
#include <fstream>  
#include <sstream>  
#include <stack>  
#include <queue>  
#include <limits>  
#include <memory.h>  
#include <string>  
#include "graph.h"  

using namespace std;

template<class E>
struct Node
{
	int depth;
	int *vertices;
	E length;

	Node(int dep){
		depth = dep;
		vertices = new int[dep];
	};

	void cpy(int *&des){
		for (int i = 0; i < depth; ++i)
		{
			des[i] = vertices[i];
		}
	}

	bool find(int v){
		for (int i = 0; i < depth; ++i)
		{
			if (vertices[i] == v)
			{
				return true;
			}
		}
		return false;
	}
};

template<class E>
int dfs(int start, Graph<E> &myGraph)//deepFirst
{
	stack<int> myStack;
	myStack.push(start);
	int numVertices = myGraph.getVertexNum();
	bool *visited = new bool[numVertices];

	memset(visited,false,numVertices);
	int v;
	int w = -1;

	while(!myStack.empty())//栈不空
	{
		v= myStack.top();
		visited[v] = true;
		if (w == -1)
		{
			w = myGraph.getFirstNeighbor(v);
		}else{
			w = myGraph.getNextNeighbor(v,w);
		}
		for (; w != -1 && visited[w] == true; w = myGraph.getNextNeighbor(v,w)){}
		if (w == -1)//未找到可行的下一个顶点，子结点都在栈中
		{
			myStack.pop(); //回溯
			w = v;
			visited[v] = false;
		}
		else //找到下一个可行点
		{
			myStack.push(w);
			if (myStack.size() == numVertices) //走过所有顶点
			{
				if (myGraph.getWeight(start,w) == std::numeric_limits<E>::max())
				{//判断最优一个顶点有没有回到起点的边
					myStack.pop();
					visited[w] = false;
				}
				else
				{
					return 1;//success find the path.
				}
			}
			else
			{
				w = -1;
			}
		}
	}
	return 0;
}

template<class E>
int ch(int start, Graph<E> &myGraph) //climbingHill
{
	stack<int> myStack;
	myStack.push(start);
	int numVertices = myGraph.getVertexNum();
	bool *visited = new bool[numVertices];

	memset(visited,false,numVertices);
	int v;
	int w = -1;

	while(!myStack.empty())//栈不空
	{
		v= myStack.top();
		visited[v] = true;
		if (w == -1)
		{
			w = myGraph.getFirstNeighbor(v);
		}else{
			w = myGraph.getNextNeighbor(v,w);
		}
		for (; w != -1 && visited[w] == true; w = myGraph.getNextNeighbor(v,w)){}

		int greedy = w; //choose greedy point
		for (;w != -1 && visited[w] == false; w = myGraph.getNextNeighbor(v,w))
		{
			if (myGraph.getWeight(v,w) < myGraph.getWeight(v,greedy))
			{
				greedy = w;
			}
		}
		w = greedy;
		if (w == -1)
		{
			myStack.pop();
			w = v;
			visited[v] = false;
		}
		else
		{
			myStack.push(w);
			if (myStack.size() == numVertices)
			{
				if (myGraph.getWeight(start,w) == std::numeric_limits<E>::max())
				{
					myStack.pop();
					visited[w] = false;
				}
				else
				{
					return 1;
				}
			}
			else
			{
				w = -1;
			}
		}
	}
	return 0;
}

template<class E>
int climbingHill(int start, Graph<E> &myGraph, ostream &fout)//find the min path
{
	stack<int> myStack;
	myStack.push(start);
	int numVertices = myGraph.getVertexNum();
	bool *visited = new bool[numVertices];

	memset(visited,false,numVertices);
	int v;
	int w = -1;

	while(!myStack.empty())//栈不空
	{
		v= myStack.top();
		visited[v] = true;
		if (w == -1)
		{
			w = myGraph.getFirstNeighbor(v);
		}else{
			w = myGraph.getNextNeighbor(v,w);
		}
		for (; w != -1 && visited[w] == true; w = myGraph.getNextNeighbor(v,w)){}

		int greedy = w; //choose greedy point
		for (;w != -1 && visited[w] == false; w = myGraph.getNextNeighbor(v,w))
		{
			if (myGraph.getWeight(v,w) < myGraph.getWeight(v,greedy))
			{
				greedy = w;
			}
		}
		w = greedy;
		if (w == -1)
		{
			myStack.pop();
			w = v;
			visited[v] = false;
		}
		else
		{
			myStack.push(w);
			if (myStack.size() == numVertices)
			{
				if (myGraph.getWeight(start,w) == std::numeric_limits<E>::max())
				{
					myStack.pop();
					visited[w] = false;
				}
				else // success find the path
				{
					stack<int> temp;
					while(!myStack.empty())
					{
						int n = myStack.top();
						temp.push(n);
						myStack.pop();
					}
					// fout<<"Hamiltonian path:";
					E distance = 0;
					int n = temp.top();
					myStack.push(n);
					temp.pop();
					int last = n;
					// fout<< n<< "--";
					while(!temp.empty())
					{
						n = temp.top();
						myStack.push(n);
						temp.pop();
						distance += myGraph.getWeight(last, n);
						last = n;
						// fout<<n<<"--";
					}
					// fout<<start<<endl;
					distance += myGraph.getWeight(last,start);
					// fout<<"total length is:"<<distance<<endl;
				}
			}
			else
			{
				w = -1;
			}
		}
	}
	return std::numeric_limits<E>::max();
}

template<class E>
int bfs(int start, Graph<E> &myGraph) //broad first
{
	stack<Node<E> > myStack;
	int s = myGraph.getFirstNeighbor(start);
	
	for (s = myGraph.getNextNeighbor(start, s); s != -1; s = myGraph.getNextNeighbor(start, s)) 
	{  
        Node<E> n(2);
        // cout<<"n.depth = "<<n.depth<<endl;
        n.vertices[0] = start;
        n.vertices[1] = s;
        n.length = myGraph.getWeight(start, s);
        myStack.push(n);
    }
    while (!myStack.empty())
    {
    	Node<E> node = myStack.top();
    	myStack.pop();
    	int v = node.vertices[node.depth - 1];
    	if (node.depth+1  == myGraph.getVertexNum())//到了最后一层，判断是不是哈密顿回路
    	{
    		int w;
    		for (w = myGraph.getFirstNeighbor(v); w != -1; w = myGraph.getNextNeighbor(v,w))
    		{
    			if (node.find(w) == false)
    			{
    				break;
    			}
    		}
    		if (w != -1)
    		{
    			if (myGraph.getWeight(w,start) < std::numeric_limits<E>::max())
    			{
    				return 1;
    			}
    		}
    	}
    	for (int w = myGraph.getFirstNeighbor(v); w != -1; w = myGraph.getNextNeighbor(v, w))
    	{
    		if (node.find(w) == false)
    		{
    			Node<E> node1(node.depth + 1);
    			node1.length = node.length + myGraph.getWeight(v, w);
    			node.cpy(node1.vertices);
    			node1.vertices[node1.depth - 1] = w;
    			myStack.push(node1);
    		}
    	}
    }
    return 0;
}

template<class E>
int branchBound(int start, Graph<E> &myGraph, ostream &fout) //分枝界限求解最短哈密顿回路问题
{
	stack<Node<E> > myStack;
	E minDistance = climbingHill(start, myGraph, fout);//爬山法获取首界限
	int s = start;
	for (s = myGraph.getFirstNeighbor(start); s != -1; s = myGraph.getNextNeighbor(start, s))
	{
		Node<E> n(2);  
        n.vertices[0] = start;  
        n.vertices[1] = s;  
        n.length = myGraph.getWeight(start, s);  
        myStack.push(n);
	}
	while (!myStack.empty())
	{
		Node<E> node = myStack.top();  
        myStack.pop();  
        int v = node.vertices[node.depth - 1];
        if (node.depth + 1 == myGraph.getVertexNum())
        {
        	int w;
    		for (w = myGraph.getFirstNeighbor(v); w != -1; w = myGraph.getNextNeighbor(v,w))
    		{
    			if (node.find(w) == false)
    			{
    				break;
    			}
    		}
    		if (w != -1)
    		{
    			if (myGraph.getWeight(w,start) < std::numeric_limits<E>::max())
    			{
    				E tempDistance = node.length + myGraph.getWeight(v,w) + myGraph.getWeight(w,start);
    				if (minDistance > tempDistance)
    				{
    					// fout << "哈密顿回路为：";
    					for (int i = 0; i < node.depth; ++i)
    					{
    						// fout<<node.vertices[i]<<"   ";
    					}
    					// fout << w << "   " << start << endl;
    					// fout << "总长度为:  " << tempDistance << endl; 
    					minDistance = tempDistance;
    				}
    			}
    		}
        }
        for (int w = myGraph.getFirstNeighbor(v); w != -1; w = myGraph.getNextNeighbor(v, w))
        {
        	if (node.find(w) == false)
        	{
        		Node<E> node1(node.depth + 1);
        		node1.length = node.length + myGraph.getWeight(v, w);
        		if (node1.length < minDistance) //剪枝
        		{
        			node.cpy(node1.vertices);
        			node1.vertices[node1.depth - 1] = w;
        			myStack.push(node1);
        		}
        	}
        }
	}
	return minDistance;
}

int main(int argc, char const *argv[])
{
	// char dfsTime[20] = "dfsTime.txt";
	// char bfsTime[20] = "bfsTime.txt";
	// char chTime[20] = "chTime.txt";
	// ofstream dfsOut(dfsTime, ios::app);
	// ofstream bfsOut(bfsTime, ios::app);
	// ofstream chOut(chTime, ios::app);
	system("rm time.txt");
	system("rm branchBound.txt");

	char Time[20] = "time.txt";
	ofstream timeOut(Time, ios::app);

	char bbn[20] = "branchBound.txt";
	ofstream bbnOut(bbn, ios::app);

	char matN[20] = "matrixN.txt";  
	char mat[20] = "matrix.txt";
	ofstream fout3(matN); 
	ofstream fout2(mat);


	int countN = 100;
	for (int count = 80; count <= countN; count = count + 2)
	{
		cout<<"----------------------------------"<<endl;
		cout<<"vertices num:"<<count<<endl;
		Graph<int> myGraph(count);//完全无向图
		Graph<int> myGraphN(count);//

		myGraph.RandInit();//初始化完全无向图
		myGraphN.RandInitN();

		// cout<<"output graph"<<endl;
	 //    myGraphN.output(fout3);
		myGraph.output(fout2);
		
		timeOut<<count<<"\t";
		clock_t timea = clock();
		if (dfs(0,myGraphN) == 1)
		{
			cout<<"deepFirst Method:"<<"Have found the Hamiltonian path!"<<"\t\t";
		}
		else
		{
			cout<<"deepFirst Method:"<<"Couldn't found the Hamiltonian path!"<<"\t\t";
		}
		clock_t timeb = clock();
		cout<<"dfs time:"<<(double)(timeb-timea)/CLOCKS_PER_SEC<<"(s)"<<endl;

		// dfsOut<<count<<"\t"<<st<<endl;
		timeOut<<(double)(timeb-timea)/CLOCKS_PER_SEC<<"\t";

		clock_t timea1 = clock();
		if (bfs(0,myGraphN) == 1)
		{
			cout<<"broadFirst Method:"<<"Have found the Hamiltonian path!"<<"\t\t";
		}
		else
		{
			cout<<"broadFirst Method:"<<"Couldn't found the Hamiltonian path!"<<"\t\t";
		}
		clock_t timeb1 = clock();
		cout<<"bfs time: "<<(double)(timeb1-timea1)/CLOCKS_PER_SEC<<"(s)"<<endl;

		// bfsOut<<count<<"\t"<<st1<<endl;
		timeOut<<(double)(timeb1-timea1)/CLOCKS_PER_SEC<<"\t";

		clock_t timea2 = clock();
		if (ch(0,myGraphN) == 1)
		{
			cout<<"climbHill Method:"<<"Have found the Hamiltonian path!"<<"\t\t";
		}
		else
		{
			cout<<"climbHill Method:"<<"Couldn't found the Hamiltonian path!"<<"\t\t";
		}
		clock_t timeb2 = clock();
		cout<<"ch time: "<<(double)(timeb2-timea2)/CLOCKS_PER_SEC<<"(s)"<<endl;

		// chOut<<count<<"\t"<<st2<<endl;
		timeOut<<(double)(timeb2-timea2)/CLOCKS_PER_SEC<<"\t"<<endl;


	   // bbnOut<<count<<"\t";
	   // clock_t a = clock();
	   // int dis = branchBound(0,myGraph,bbnOut);
	   // cout<<"branchBound:"<<dis<<"\t";
	   // clock_t b = clock();
	   // cout<<"branchBound time:"<<(double)(b-a)/CLOCKS_PER_SEC<<endl; 
	   // bbnOut<<dis<<"\t";
	   // bbnOut<<(double)(b-a)/CLOCKS_PER_SEC<<endl;

	}


	return 0;
}


