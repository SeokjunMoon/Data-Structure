/*
No skeleton code is provided.
Please refer to the PA02 for how to read input text files from the standard input stream.
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
	string data;
	Node* par;
	Node* left;
	Node* right;
};

void getParents(Node* v, vector<string>& vpar) {
	if (v->par != nullptr) getParents(v->par, vpar);
	vpar.push_back(v->data);
}

void append(Node* root, Node* v) {
	Node* itr = root;
	while(true) {
		if (itr->data < v->data) {
			if (itr->right == nullptr) {
				itr->right = v;
				break;
			}
			else itr = itr->right;
		}
		else {
			if (itr->left == nullptr) {
				itr->left = v;
				break;
			}
			else itr = itr->left;
		}
	}
	v->par = itr;
}

int main(void) {
	int nNum;
	string a, b, root_name, name;
	vector<string> apar, bpar;
	
	getline(cin, a);
	getline(cin, b);
	cin >> nNum;
	getline(cin, root_name);
	
	Node* root = new Node;
	root->data = root_name;
	
	for (int i = 0; i < nNum; i++) {
		getline(cin, name);
		Node* tmp = new Node;
		tmp->data = name;
		append(root, tmp);
		
		if (name == a) getParents(tmp, apar);
		if (name == b) getParents(tmp, bpar);
	}

	for (size_t i = 0; i < apar.size(); i++) {
		for (size_t j = 0; j < bpar.size(); j++) {
			if (apar[i] == bpar[j]) cout << apar[i] << endl;
		}
	}
	
	return 0;
}