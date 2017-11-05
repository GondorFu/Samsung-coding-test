#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

int main(){
	ifstream fin("3- sample_input.txt");
	ofstream fout("3- sample_output_test.txt");
	int N = 10;
	int i;
	for (int iN=1; iN<=N; iN++)
	{
		int V, E;
		fin >> V >> E;
		vector<int> indegree(V+1, 0);
		vector<list<int>> arrlist(V+1, list<int>());
		while(E--){
			int v1, v2;
			fin >> v1 >> v2;
			arrlist[v1].push_front(v2);
			indegree[v2]++;
		}
		fout << "#" << iN;
		queue<int> q;
		for(i=1; i<=V; i++) 
			if(indegree[i] == 0) 
				q.push(i);
		while(!q.empty()){
			int t = q.front();
			q.pop();
			fout << ' ' << t;
			for(list<int>::iterator it=arrlist[t].begin(); it!=arrlist[t].end(); it++){
				if(--indegree[*it] == 0) q.push(*it);
			}
		}
		fout << endl;
	}

	return 0;
}