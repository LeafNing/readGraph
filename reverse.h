#ifndef REVERSE_H
#define REVERSE_H

#include "limit.h"
#include <vector>

using namespace std;

struct Edge1
{
	int u, v, c;
	char tie;
};

class Reverse
{
private:
	static int n;
	static int m;
	static vector<Edge1> edges;
	static vector<Edge1> edges1;

	static void qsort_edges(int h, int t);

public:

	static void solve(char *file);
};

#endif

