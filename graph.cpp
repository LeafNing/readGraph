#include "graph.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <sstream>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;

int  Graph::n = 0;
int  Graph::m = 0;
vector<Edge> Graph::edges;
vector<Nodes> Graph::nodes;

void Graph::qsort_edges(int h, int t)
{
	if (h<t)
	{
		int i = h, j = t;
		Edge mid = edges[(i + j) / 2];
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
void Graph::init_nodes(int num)
{
	for (int i = 0; i < num; i++){
		nodes[i].inD = 0;
		nodes[i].outD = 0;
		nodes[i].inS = 0;
		nodes[i].inW = 0;
		nodes[i].outS = 0;
		nodes[i].outW = 0;
		nodes[i].inVal = 0.0;
		nodes[i].outVal = 0.0;
	}
}
string Graph::intToStr(int i)
{
	stringstream ss;
	ss << i;
	return ss.str();
}
/**********************************find the max node id*******************************************/
void Graph::findMax(char *file){
	FILE *tmpfile = fopen(file, "r");
	if (!tmpfile){
		printf("ERROR OPENING FILES...\n");
		return;
	}
	int u, v;
	vector<int> nodes;
	int cnt = 0;
	while (!feof(tmpfile)){
		fscanf_s(tmpfile, "%ld %ld", &u, &v);
		nodes.push_back(u);
		nodes.push_back(v);
		cnt++;
	}
	sort(nodes.begin(), nodes.end());
	int len = nodes.size();
	printf("the max user id is : %ld\n", nodes[len - 1]);
	printf("the number of edges id %d\n", cnt);
}
/*********************************label ties with strong or weak****************************************/
void Graph::BuildFromFileNoWeitht_tie(char *file0, char *file1, char *file2)
{
	FILE *tmpfile = fopen(file0, "r");
	fscanf_s(tmpfile, "%ld %ld", &n, &m);
	edges.resize(m + 1);
	fclose(tmpfile);
	printf("number of nodes:%ld, number of edges:%ld\n", n, m);

	int m1, m2;
	FILE *tmpfile1 = fopen(file1, "r");
	fscanf_s(tmpfile1, "%ld %ld", &n, &m1);
	for (int i = 0; i < m1; i++){
		fscanf_s(tmpfile1, "%ld %ld", &edges[i].u, &edges[i].v);
		edges[i].c = 1;
		edges[i].tie = 's';
	}
	fclose(tmpfile1);
	printf("m1 = %ld\n", m1);
	printf("number of nodes:%ld, number of edges:%ld\n", n, m);
	FILE *tmpfile2 = fopen(file2, "r");
	fscanf_s(tmpfile2, "%ld %ld", &n, &m2);
	printf("m2 = %ld\n", m2);
	for (int i = m1; i < m; i++){
		fscanf_s(tmpfile2, "%ld %ld", &edges[i].u, &edges[i].v);
		edges[i].c = 1;
		edges[i].tie = 'w';
	}
	fclose(tmpfile2);
	printf("number of nodes:%ld, number of edges:%ld\n", n, m);
	qsort_edges(0, m - 1);

	m1 = 0;
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
	printf("number of edges : %d\n", m);

	FILE *tmpfile3 = fopen("tmp.txt", "w");
	fprintf(tmpfile3, "%ld %ld\n", n, m);
	for (int i = 0; i < m; i++)
		fprintf(tmpfile3, "%ld %ld %c\n", edges[i].u, edges[i].v, edges[i].tie);
	fclose(tmpfile3);
}

/**************************************unifrom weights**************************************************/
void Graph::BuildFromFileNoWeitht(char *file)
{
	FILE *tmpfile = fopen(file, "r");
	fscanf_s(tmpfile, "%ld %ld", &n, &m);
	edges.resize(m + 1);

	for (int i = 0; i<m; i++)
	{
		fscanf_s(tmpfile, "%ld %ld %c", &edges[i].u, &edges[i].v, &edges[i].tie);
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
	m1 = 0;
	int cnt = 1;
	for (int i = 1; i <m; i++){
		if (edges[i].u == edges[m1].u){
			cnt++;
		}
		else{
			if (cnt == 1){
				edges[m1].w1 = 1;
			}
			else{
				for (int j = m1; j <= m1 + cnt; j++){
					edges[j].w1 = (double)1 / (double)cnt;
					edges[j].w2 = 0.0;
				}
			}
			m1 = i;
			cnt = 1;
		}
		if (i == m - 1){
			if (cnt == 1){
				edges[m1].w1 = 1;
			}
			else{
				for (int j = m1; j <= m1 + cnt; j++){
					edges[j].w1 = (double)1 / (double)cnt;
					edges[j].w2 = 0.0;
				}
			}
		}
	}
	FILE *tmpfile1 = fopen("Graph_uniformweights_tie.txt", "w");
	fprintf(tmpfile1, "%ld %ld\n", n, m);
	for (int i = 0; i < m; i++)
		fprintf(tmpfile1, "%ld %ld %lf %lf %c\n", edges[i].v, edges[i].u, edges[i].w1, edges[i].w2, edges[i].tie);
	fclose(tmpfile1);
}

/***************************************loading nodes information*******************************************************/
void Graph::loadNodes()
{
	FILE *tmpfile = fopen("tmp.txt", "r");
	fscanf_s(tmpfile, "%ld %ld", &n, &m);
	edges.resize(m);
	nodes.resize(n + 1);
	init_nodes(n + 1);
	for (int i = 0; i<m; i++)
	{
		fscanf_s(tmpfile, "%ld %ld %c", &edges[i].u, &edges[i].v, &edges[i].tie);
		edges[i].c = 1;
		nodes[edges[i].u].outD++;
		if (edges[i].tie == 's')
			nodes[edges[i].u].outS++;
		else if (edges[i].tie == 'w')
			nodes[edges[i].u].outW++;
		
	}
	fclose(tmpfile);

	FILE *tmpfile1 = fopen("Graph0.txt", "r");
	fscanf_s(tmpfile1, "%ld %ld", &n, &m);
	edges.resize(m);
	for (int i = 0; i < m; i++){
		fscanf_s(tmpfile, "%ld %ld %c", &edges[i].u, &edges[i].v, &edges[i].tie);
		edges[i].c = 1;
		nodes[edges[i].u].inD++;
		if (edges[i].tie == 's')
			nodes[edges[i].u].inS++;
		else if (edges[i].tie == 'w')
			nodes[edges[i].u].inW++;
	}
	fclose(tmpfile1);

	for (int i = 1; i <= n; i++){
		if (nodes[i].inD != 0)
			nodes[i].inVal = (double)nodes[i].inW / (double)nodes[i].inD;
		if (nodes[i].outD != 0)
			nodes[i].outVal = (double)nodes[i].outW / (double)nodes[i].outD;
	}

	FILE *tmpfile2 = fopen("nodes.txt", "w");
	fprintf_s(tmpfile2, "%ld\n", n);
	//id inDegree outDegree #inStrongties #inWeakties #outStrongties #outWeakties inVal outVal
	for (int i = 1; i <= n; i++)
		fprintf_s(tmpfile2, "%ld %ld %ld %ld %ld %ld %ld %.3lf %.3lf\n", i, nodes[i].inD, nodes[i].outD, nodes[i].inS, nodes[i].inW, 
				nodes[i].outS, nodes[i].outW, nodes[i].inVal, nodes[i].outVal);
	fclose(tmpfile2);
}

/****************************************label the edges between seed nodes*********************************************/
void Graph::SeedsTie(char *file0, char *file1){
	vector<int> isSeed;
	FILE *tmpfile = fopen(file0, "r");
	fscanf_s(tmpfile, "%ld %ld", &n, &m);
	isSeed.resize(n, 0);
	edges.resize(m);
	for (int i = 0; i < m; i++)
		fscanf_s(tmpfile, "%d %d %c", &edges[i].u, &edges[i].v, &edges[i].tie);
	fclose(tmpfile);

	printf("111\n");
	int n_seeds;
	int seed;
	map<int, int> seed_out;
	map<int, int> seed_in;
	map<int, int> weak_in;
	map<int, int> weak_out;
	FILE *tmpfile1 = fopen(file1, "r");
	fscanf_s(tmpfile1, "%d", &n_seeds);
	for (int i = 0; i < n_seeds; i++){
		fscanf_s(tmpfile1, "%d", &seed);
		isSeed[seed] = 1;
		seed_out[seed] = 0;
		seed_in[seed] = 0;
		weak_in[seed] = 0;
		weak_out[seed] = 0;
		//fprintf_s(tmpfile2, "%d\t1\n", seed);
	}
	fclose(tmpfile1);
	//fclose(tmpfile2);

	printf("222\n");
	FILE *tmpfile4 = fopen("edge_type.txt", "w");
	fprintf_s(tmpfile4, "id1\tid2\ttie_type\tseed_id\n");
	for (int i = 0; i < m; i++){
		
		int u = edges[i].u;
		int v = edges[i].v;
		//printf("u = %d\tv = %d\n", u, v);
		if (isSeed[u] == 1 && isSeed[v] == 1){
			fprintf_s(tmpfile4, "%d\t%d\t%c\tboth\n", u, v, edges[i].tie);
			//printf("%d\t%d\t%c\tboth\n", u, v, edge.tie);
		}
		else if (isSeed[u] == 1 && isSeed[v] == 0){
			fprintf_s(tmpfile4, "%d\t%d\t%c\tseed1\n", u, v, edges[i].tie);
			//printf("%d\t%d\t%c\tseed1\n", u, v, edge.tie);
		}
		else if (isSeed[u] == 0 && isSeed[v] == 1){
			fprintf_s(tmpfile4, "%d\t%d\t%c\tseed2\n", u, v, edges[i].tie);
			//printf("%d\t%d\t%c\tseed2\n", u, v, edge.tie);
		}

		if (isSeed[u] == 1){
			seed_out[u]++;
			if (edges[i].tie == 'w')
				weak_out[u]++;
		}
		else if (isSeed[u] == 0 && isSeed[v] == 1){
			seed_in[v]++;
			if (edges[i].tie == 's')
				weak_in[v]++;
		}
	}
	printf("333\n");
	FILE *tmpfile2 = fopen("seeds_weak_tie.txt", "w");
	fprintf_s(tmpfile2, "seed_id\tweak_in\tweak_out\n");
	map<int, int>::iterator it;
	double t1, t2;
	int cnt = 0;
	for (it = seed_in.begin(); it != seed_in.end(); it++){
		seed = it->first;
		if (seed_in[seed] != 0)
			t1 = (double)weak_in[seed] / (double)seed_in[seed];
		else
			t1 = -1;
		if (seed_out[seed] != 0)
			t2 = (double)weak_out[seed] / (double)seed_out[seed];
		else
			t2 = -1;
		if (t2 > 0.5)
			cnt++;
		fprintf_s(tmpfile2, "%d\t%.3lf\t%.3lf\n", seed, t1, t2);
		printf("%d\t%.3lf\t%.3lf\n", seed, t1, t2);
	}
	printf("cnt = %d\n", cnt);
	fclose(tmpfile2);
	
	fclose(tmpfile4);
}

