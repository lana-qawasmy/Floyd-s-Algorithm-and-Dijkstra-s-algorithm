#include<iostream>
#include<fstream>
#include<queue>
#include<string>
#include<cmath>
#define V 100
#include<list>
using namespace std;

int print(int dist[100][100], int n, int x, int y, char c);

void Floyd(int w[100][100], int n, int x, int y)
{
	int p[100][100], s[100][100];
	list<int> l;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			p[i][j] = 0;
			s[i][j] = w[i][j];
		}
	}
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (s[i][j] > s[i][k] + s[k][j])
				{
					p[i][j] = k;
					s[i][j] = s[i][k] + s[k][j];
					l.push_front(print(p, n, x, y, 'w'));

				}

			}
		}
	}
	l.unique();
	l.reverse();
	cout << "path : " << x << " ";
	for (int i = 0; i < l.size(); i++)
	{
		cout << l.front() << " ";
		l.pop_front();
	}
	cout << " " << y << endl << "Floyd shortest path value =  " << print(s, n, x, y, 'w') << endl;
	cout << endl;

}
int print(int dist[100][100], int n, int x, int y, char c)
{

	int w = dist[x][y];
	return w;
}



int minDistance(int dist[], bool sptSet[], int n)
{

	int min = 99999, min_index;

	for (int v = 0; v < n; v++)
		if (sptSet[v] == false && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}


void printPath(int parent[], int j)
{

	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	cout << j << "  ";
}


void printSolution(int dist[], int n, int parent[], int des)
{
	int src = 0;
	cout << endl;

	for (int i = 0; i < n; i++)
	{
		if (i == des)
		{
			cout << endl;
			cout << "dijkstra shortest path value = " << dist[i] << endl;
			cout << "path: " << src << " ";
			printPath(parent, i);
		}

	}
}

void dijkstra(int graph[V][V], int n, int src, int des)
{


	int dist[V];
	bool sptSet[V];
	int parent[V];
	for (int i = 0; i < V; i++)
	{
		parent[i] = -1;
		dist[i] = 99999;
		sptSet[i] = false;
	}

	dist[src] = 0;
	for (int count = 0; count < n - 1; count++)
	{

		int u = minDistance(dist, sptSet, n);

		sptSet[u] = true;

		for (int v = 0; v < n; v++)
			if (!sptSet[v] && graph[u][v] && dist[u] + graph[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v];
			}
	}

	printSolution(dist, n, parent, des);
}

int main()
{
	string filename;
	fstream inFile;
	int T[100][100];
	int source_vertex, destination_vertex;
	queue<int> q;
	int x;
	do
	{
		cout << "Hello to Lana Qawasmy Final Project !\n";
		cout << "Enter the name of the input file . \n";
		cout << "Filename: ";
		cin >> filename;
		cout << endl;
		inFile.open(filename/*.c_str()*/);
		if (!inFile)
			cout << "That is not a valid file. Try again !\n";
		while (!inFile.eof())
		{
			inFile >> x;
			q.push(x);
		}
	} while (!inFile);

	int n = sqrt(q.size());
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			T[i][j] = q.front();
			q.pop();
		}
	}
	cout << "Enter the source vertex :" << endl;
	cin >> source_vertex;
	cout << "Enter the destination vertex :" << endl;
	cin >> destination_vertex;
	Floyd(T, n, source_vertex, destination_vertex);


	dijkstra(T, n, source_vertex, destination_vertex);

inFile.close();
	system("pause");

	return 0;
}
