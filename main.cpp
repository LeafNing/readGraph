#include "limit.h"
#include "graph.h"
#include "reverse.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <io.h>
#include <string>
#include <windows.h>
#include <iostream>

#include <math.h>

using namespace std;


int main(int argc, char * argv[]){
	if (argc <= 1) {
		printf("example: readGraph.exe -option GraphFileName.txt\n");
		return 0;
	}
	string s;

	//label ties
	s = "-tie";
	if (!s.compare(argv[1])){
		printf("please input the filenames(original graph, strong edges, weak edges):\n");
		char file0[100], file1[100], file2[100];
		cin >> file0 >> file1 >> file2;
		Graph::BuildFromFileNoWeitht_tie(file0, file1, file2);
		printf("label ties with strong or weak done...\n");
	}

	//reverse oringinal graph
	s = "-rv";
	if (!s.compare(argv[1])){
		Reverse::solve("tmp.txt");
		printf("reverse done...\n");
	}

	//loading nodes information
	s = "-node";
	if (!s.compare(argv[1])){
		Graph::loadNodes();
		printf("loading nodes information done...\n");
	}

	//generate graph with uniform weights and labeled ties
	s = "-u";
	if (!s.compare(argv[1])){
		Graph::BuildFromFileNoWeitht("Graph0.txt");
		printf("generate graph with uniform weights and labeled ties done...\n");
	}

	//find max node id
	s = "-find";
	if (!s.compare(argv[1])){
		Graph::findMax(argv[2]);
		printf("findMax done...\n");
	}

	//label the edges between seed nodes
	s = "-seed";
	if (!s.compare(argv[1])){
		Graph::SeedsTie("labeled_ties.txt", "seeds.txt");
		printf("label the edges between seed nodes done...\n");
	}

	return 0;
}