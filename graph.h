#ifndef GRAPH_H
#define GRAPH_H

#include "limit.h"
#include <vector>

using namespace std;

struct Edge
{
	int u, v, c;	//u,v are the two nodes and c = count	
	double w1, w2;
	char tie;
};

struct Nodes{
	int inD, outD;
	int inS, inW;
	int outS, outW;
	double inVal, outVal;
};

class Graph
{
private:
	static int n;
	static int m;
	static vector<Edge> edges;
	static vector<Nodes> nodes;

	static void qsort_edges(int h, int t);
	static void init_nodes(int num);


public:
	static void BuildFromFileNoWeitht_tie(char *file0, char *file1, char *file2);
	static void BuildFromFileNoWeitht(char *file);
	static void loadNodes();
	static string intToStr(int i);
	static void findMax(char *file);
	static void SeedsTie(char *file0, char *file1);
};

#endif

