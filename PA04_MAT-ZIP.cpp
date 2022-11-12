// Add any additional header files freely
#include <iostream>
#include <string>
#include <sstream>

using namespace std;
int MAX_LENGTH = 100;

// Returns menu serving time of each menu
int getMenuTime(char menu){
	switch(menu){
		case 'A': return 1;
		case 'B': return 2;
		case 'C': return 3;
		case 'D': return 4;
		case 'E': return 5;
		case 'F': return 7;
		case 'G': return 10;
		case 'H': return 12;
		case 'I': return 14;
		case 'J': return 15;
	}
}

int pow(int a, int b) {
	if (b == 0) return 1;
	if (b == 1) return a;
	
	int result = 1;
	for (int i = 0; i < b; i++) {
		result *= a;
	}
	return result;
}


int str2int(string s) {
	int result = 0;
	int strlen = s.size();
	for (int i = 0; i < strlen; i++) {
		if (s[i] >= '0' && s[i] <= '9') result += pow(10, strlen - i - 2) * (s[i] - '0');
	}
	return result;
}


bool check(string s) {
	int space_index = s.find(' ');
	if (space_index == -1) return false;
	return true;
}


void addSchedule(string schedule, int* table) {
	if (!check(schedule)) {
		return;
	}
	int space_index = schedule.find(' ');
	char schedule_time = (char) schedule[space_index + 1];
	int start_time = str2int(schedule.substr(0, space_index + 1));
	int table_time = getMenuTime(schedule_time);
	
	for (int i = start_time; i < (start_time + table_time); i++) {
		if (i <= MAX_LENGTH) table[i]++;
	}
}


int getMaxTableCount(int* table) {
	int result = 0;
	for (int i = 1; i < 1 + MAX_LENGTH; i++) {
		if (table[i] > result) result = table[i];
	}
	return result;
}


int main(void) {
	int n = 1;
	int c = 0;
	int ScheduleTable[MAX_LENGTH + 1];
	
	for (int i = 0; i < 1 + MAX_LENGTH; i++) {
		ScheduleTable[i] = 0;
	}
	
	cin >> n;
	for (int i = 0; i <= n; i++) {
		string tmp;
		getline(cin, tmp);
		addSchedule(tmp, ScheduleTable);
	}
	cout << getMaxTableCount(ScheduleTable) << endl;
	
	return 0;
}