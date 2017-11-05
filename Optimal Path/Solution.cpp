
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Pair{
public:
	int x;
	int y;
	Pair(int x=0, int y=0) : x(x), y(y){}
	bool operator<(Pair y){
		if(this->x < y.x) return true;
		else if(this->x > y.x) return false;
		else if(this->y < y.y) return true;
		return false;
	}
};

int calDis(Pair x, Pair y){
	return abs(x.x - y.x) + abs(x.y - y.y);
}

bool judgeEnd(vector<bool> flag){
	for(int i=2; i<flag.size(); i++)
		if(flag[i] == false) return false;
	return true;
}

int findMax(vector<int> val){
	int rlt = 0;
	int maxVal = val[0];
	for(int i=1; i<val.size(); i++){
		if(val[i] > maxVal){
			maxVal = val[i];
			rlt = i;
		}
	}
	return rlt;
}

vector<int> heuristic(const vector<vector<int>> disMap, vector<bool> flag, int index){
	int N = 3;
	int i;
	vector<int> rlt, val;
	for(i=2; i<flag.size(); i++)
		if(flag[i] == false){
			rlt.push_back(i);
			val.push_back(disMap[index][i]);
		}
	while(rlt.size() > N){
		int it = findMax(val);
		rlt.erase(rlt.begin() + it);
		val.erase(val.begin() + it);
	}
	return rlt;
}

int getDis(const vector<vector<int>> disMap, vector<bool> flag, int index){
	flag[index] = true;
	if(judgeEnd(flag)) return disMap[index][1];
	int rlt = numeric_limits<int>::max();
	int n = flag.size();
	int i, j;
	vector<int> sel = heuristic(disMap, flag, index);
	for(j=0; j<sel.size(); j++){
		i = sel[j];
		rlt = min(rlt, disMap[index][i] + getDis(disMap, flag, i));
	}
	return rlt;
}

int main(){
	ifstream fin("2- sample_input.txt");
	ofstream fout("2- sample_output_test.txt");
	int T = 0; 
	fin >> T;
	int iN, i, j;
	for(iN=1; iN<=T; iN++){
		cout << '#' << iN << endl;
		int N;
		fin >> N;
		vector<Pair> arr(N+2, Pair());
		for(i=0; i<N+2; i++) fin >> arr[i].x >> arr[i].y;
		vector<vector<int>> disMap(N+2, vector<int>(N+2, 0));
		for(i=0; i<N+2; i++)
			for(j=i+1; j<N+2; j++)
				disMap[i][j] = disMap[j][i] = calDis(arr[i], arr[j]);
		int index = 0;
		vector<bool> flag(N+2, false);
		int rlt = getDis(disMap, flag, index);
		fout << '#' << iN << ' ' << rlt << endl;
	}

	return 0;
}