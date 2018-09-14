#include "reverse.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <map>
using namespace std;

int  Reverse::n = 0;
int  Reverse::m = 0;
vector<Edge1> Reverse::edges;
vector<Edge1> Reverse::edges1;

void Reverse::qsort_edges(int h, int t)
{
	if (h<t)
	{
		int i = h, j = t;
		Edge1 mid = edges[(i + j) / 2];
		edges[(i + j) / 2] = edges[i];

		while (i<j)
		{
			while ((i<j) && ((edges[j].u>mid.u) || ((edges[j].u == mid.u) && (edges[j].v>mid.v))))
				j--;
			if (i<j) {
				edges[i] = edges[j];
				i++;
			}
			while ((i<j) && ((edges[i].u<mid.u) || ((edges[i].u == mid.u) && (edges[i].v<mid.v))))
				i++;
			if (i<j) {
				edges[j] = edges[i];
				j--;
			}
		}

		edges[i] = mid;
		qsort_edges(h, i - 1);
		qsort_edges(i + 1, t);
	}
}


/**************************************reverse**************************************************/
void Reverse::solve(char *file)
{
	FILE *tmpfile = fopen(file, "r");
	fscanf_s(tmpfile, "%ld %ld", &n, &m);
	edges.resize(m + 1);
	edges1.resize(m + 1);
	printf("m = %ld\n", m);
	for (int i = 0; i<m; i++)
	{
		fscanf_s(tmpfile, "%ld	%ld %c", &edges1[i].u, &edges1[i].v, &edges1[i].tie);
		edges[i].v = edges1[i].u;
		edges[i].u = edges1[i].v;
		edges[i].tie = edges1[i].tie;
		edges[i].c = 1;
	}
	qsort_edges(0, m - 1);
	fclose(tmpfile);
	int m1 = 0;
	for (int i = 1; i<m; i++)
	{
		if ((edges[i].u != edges[m1].u) || (edges[i].v != edges[m1].v))
		{
			m1++;
			edges[m1] = edges[i];
		}
		else
		{
			edges[m1].c++;
		}
	}
	if (m != 0)
		m = m1 + 1;
	printf("m:%d\n", m);


	FILE *tmpfile1 = fopen("Graph0.txt", "w");
	fprintf(tmpfile1, "%ld %ld\n", n, m);
	for (int i = 0; i <m; i++){
		fprintf(tmpfile1, "%ld %ld %c\n", edges[i].u, edges[i].v, edges[i].tie);
	}
	fclose(tmpfile1);
}

