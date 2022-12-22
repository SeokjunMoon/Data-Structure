#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};


void getInput(vector<vector<int>>& mat, int n, int m) {
	for (int i = 0; i < n; i++) {
		vector<int> tv;
		string tmp;
		cin >> tmp;
		for (int j = 0; j < m; j++) {
			tv.push_back(tmp[j] - '0');
		}
		mat.push_back(tv);
	}
}


bool isDone(vector<vector<int>>& mat, int n, int m) {
	for (int i = 0; i < n; i++) 
		for (int j = 0; j < m; j++) 
			if (mat[i][j] == 1)
				return false;
	return true;
}


bool isValid(int n, int m, int x, int y) {
	return (x >= 0 && x < n && y >= 0 && y < m);
}


void zero_cluster(vector<vector<int>>& mat, int n, int m, int x, int y, int count) {
	mat[x][y] = count;
	for (int i = 0; i < 4; i++) {
		int xx = x + dx[i];
		int yy = y + dy[i];
		
		if (isValid(n, m, xx, yy) && mat[xx][yy] == 0)
				zero_cluster(mat, n, m, xx, yy, count);
	}
}


void melting(vector<vector<int>>& mat, int n, int m, int count) {
	vector<vector<int>> nm;
	nm.assign(mat.begin(), mat.end());
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (mat[i][j] == count) {
				for (int a = 0; a < 4; a++) {
					int x = i + dx[a];
					int y = j + dy[a];
					if (isValid(n, m, x, y)) {
						zero_cluster(nm, n, m, x, y, count);
					}
				}
			}
		}
	}
	
	mat.assign(nm.begin(), nm.end());
}


int dfs(vector<vector<int>>& mat, int n, int m) {
	int count = 2;
	int dp = 1;
	
	while(true) {
		queue<pair<int, int>> q;
		q.emplace(0, 0);

		int ptr = count;
		if (count == 2) ptr = 0;

		while(!q.empty()) {
			pair<int, int> tmp = q.front();
			q.pop();

			for (int i = 0; i < 4; i++) {
				int x = tmp.first + dx[i];
				int y = tmp.second + dy[i];

				if (isValid(n, m, x, y) && mat[x][y] == ptr) {
					q.emplace(x, y);
					mat[x][y] = count + 1;
				}
			}
		}
		
		melting(mat, n, m, count + 1);
		
		if (isDone(mat, n, m)) {
			break;
		}
		
		count += 1;
		dp += 1;
	}
	
	return dp;
}


int main(void){
	// cout << "Thank you for WITHSTANDING the Data Structure lecture in this semester! :)" << endl;
	
	int a, b;
	cin >> a >> b;
	
	vector<vector<int>> glaciers;
	getInput(glaciers, a, b);
	
	int year = dfs(glaciers, a, b);
	cout << year << endl;
	
	return 0;
}

