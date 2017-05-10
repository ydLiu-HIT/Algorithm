/*************************************************************************
	> File Name: graph.h
	> Author: 
	> Mail: 
	> Created Time: 2017年04月30日 星期日 12时12分42秒
 ************************************************************************/

#ifndef _GRAPH_H
#define _GRAPH_H
#include <iomanip>
#include <limits>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

template<class E>  //the data type of edge
class Graph
{
	private:
		int maxVertices;
		E **matrix;

	public:
		E maxWeight;
		Graph(int size);//创建基于邻接矩阵的图
		~Graph();

		int getVertexNum(){
			return maxVertices;
		}

		E getWeight(int v1, int v2);
		int getFirstNeighbor(int v);
		int getNextNeighbor(int v, int w);

		int Init(istream &in);//根据用户输入，获得图的邻接矩阵
		int RandInitN();//随机初始化图（无向图）
		int RandInit();//随机初始化图（完全无向图）
		int output(ostream &out);//输出图的矩阵到文件
		int output();//输出到控制台

};

template<class E>
Graph<E>::Graph(int size)
{
	maxWeight = std::numeric_limits<E>::max();
	maxVertices = size;
	matrix = new E *[size];
	for (int i = 0; i < size; ++i)
	{
		matrix[i] = new E[size];
		for (int j = 0; j < size; ++j)
		{
			matrix[i][j] = maxWeight;
		}
	}
}

template<class E>
Graph<E>::~Graph()
{
	for (int i = 0; i < maxVertices; ++i)
	{
		delete matrix[i];
	}
}

template<class E>
int Graph<E>::getFirstNeighbor(int v) //取顶点v的第一个邻接点
{
	if (!(v >= 0 && v < maxVertices))
	{
		printf("wrong vertex!\n");
		return -1;
	}
	for (int i = 0; i < maxVertices; ++i)
	{
		if  ((matrix[v][i] != maxWeight) && (matrix[v][i] != 0))
		{
			return i;
		}
	}
	return -1;
}

template<class E>
int Graph<E>::getNextNeighbor(int v, int w)//取顶点v的邻接点w的下一个邻接点
{
	if (!(v >= 0 && v < maxVertices) || !(w >= 0 && w < maxVertices))
		return -1;
	for (int col = w + 1; col < maxVertices; ++col)
	{
		if ((matrix[v][col] != maxWeight) && (matrix[v][col] != 0))
		{
			return col;
		}
	}
	return -1;
}

template<class E>
E Graph<E>::getWeight(int v1, int v2) //取边(v1,v2)的权值
{
	if (v1 >= 0 && v1 < maxVertices && v2 >= 0 && v2 < maxVertices)
	{
		return matrix[v1][v2];
	}
	return 0;
}

template<class E>
int Graph<E>::Init(istream &fin) //根据文件输入，获得图的邻接矩阵
{
	int v1,v2;
	E edge;
	while(fin >> v1 >> v2 >> edge)
	{
		if (v1 >= 0 && v1 < maxVertices && v2 >= 0 && v2 < maxVertices)
		{
			matrix[v1][v2] = edge;
			matrix[v2][v1] = edge;
		}
		if (edge == maxWeight)//当输入边值为无穷大时停止输入
		{
			break;
		}
	}
	return -1;
}

template<class E>
int Graph<E>::RandInitN()//随机初始化，非完全图
{
	for (int i = 0; i < maxVertices; ++i)
	{
		for (int j = 0; j < maxVertices; ++j)
		{
			matrix[i][j] = maxWeight;
		}
	}

	srand((int)time(0));
	for (int v1 = 0; v1 < maxVertices; ++v1)
	{
		for (int v2 = 0; v2 < maxVertices; ++v2)
		{
			if (v1 != v2 && matrix[v1][v2] == maxWeight)
			{
				matrix[v1][v2] = matrix[v2][v1] = rand()%2; //0,1
			}
		}
	}
	return 1;
}

template<class E>
int Graph<E>::RandInit()//随机初始化，完全图
{
	for (int i = 0; i < maxVertices; ++i)
	{
		for (int j = 0; j < maxVertices; ++j)
		{
			matrix[i][j] = maxWeight;
		}
	}

	srand((int)time(0));
	int count = maxVertices*(maxVertices - 1)/2;
	int v1,v2;
	while(count)
	{
		v1 = rand()%maxVertices;
		v2 = rand()%maxVertices;
		if (v1 != v2 && matrix[v1][v2] == maxWeight)
		{
			if (v1-v2 == 1 || v2 - v1 == 1)
			{
				matrix[v1][v2] = matrix[v2][v1] = rand()%2000;
			}
			else
			{
				matrix[v1][v2] = matrix[v2][v1] = rand()%3000;
			}
			count--;
		}
	}
	return 1;
}

template<class E>
int Graph<E>::output(ostream &out)//输出图的矩阵
{
	for (int i = 0; i < maxVertices; ++i)
	{
		for (int j = 0; j < maxVertices; ++j)
		{
			out << setw(15) << matrix[i][j] << ",";
		}
		out << endl;
	}
	return 1;
}

template<class E>
int Graph<E>::output()//输出图的矩阵
{
	for (int i = 0; i < maxVertices; ++i)
	{
		cout << "\t";
		for (int j = 0; j < maxVertices; ++j)
		{
			cout << setw(15) << matrix[i][j] << ",";
		}
		cout << endl;
	}
	return 1;
}

#endif
