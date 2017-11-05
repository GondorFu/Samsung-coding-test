#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class TreeNode{
	int val;
	TreeNode* left;
	TreeNode* right;
public:
	TreeNode(int val = 1): val(val), left(NULL), right(NULL){}
	void add(TreeNode* root);
	int getVal() const { return this->val; }
	void setVal(int val=1) { this->val = val; return; }
	friend TreeNode* getNode(TreeNode* root, TreeNode* v1, TreeNode* v2);
	friend int getNum(TreeNode* root);
};

void TreeNode :: add(TreeNode* child){
	if(this->left == NULL) this->left = child;
	else this->right = child;
	return;
}

TreeNode* getNode(TreeNode* root, TreeNode* v1, TreeNode* v2){
	if(root == NULL || root == v1 || root == v2) return root;
	TreeNode* left = getNode(root->left, v1, v2);
	TreeNode* right = getNode(root->right, v1, v2);
	if(left != NULL && right != NULL) return root;
	else if(left != NULL) return left;
	return right;
}

int getNum(TreeNode* root){
	int n = 0;
	if(root == NULL) return n;
	int nl = getNum(root->left);
	int nr = getNum(root->right);
	n = nl + nr + 1;
	return n;
}


int main(){
	ifstream fin("1- sample_input.txt");
	ofstream fout("1- sample_output_test.txt");
	int N;
	fin >> N;
	for(int iN=1; iN<=N; iN++){
		int V, E, v1, v2;
		int i;
		fin >> V >> E >> v1 >> v2;
		vector<TreeNode> arr(V+1);
		for(i=0; i<=V; i++) arr[i].setVal(i);
		int e1, e2;
		while(E--){
			fin >> e1 >> e2;
			arr[e1].add(&arr[e2]);
		}
		TreeNode* rlt = getNode(&arr[1], &arr[v1], &arr[v2]);
		int nrlt = getNum(rlt);
		fout << "#" << iN << ' ' << rlt->getVal() << ' ' << nrlt << endl;
	}

	return 0;
}