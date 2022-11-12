#include <iostream>
#include <string>
#include <stack>

using namespace std;

string s_units = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.,!?@#$%^&*";
string ns = "0123456789ABCDEF";
stack<int> repeated;
class StringDecoder{
	private:
		string data_;
	// Implement your class here
	public:
		StringDecoder() {}
		StringDecoder(string& datain) : data_(datain) {}

		friend ostream& operator<< (ostream& os, const StringDecoder& sd);
		friend istream& operator>> (istream& is, StringDecoder& sd);

		string print() {
			string repeated_str = "";
			string real_res = "";
			int rep_start = 0;
			int rep_end = 0;
			int is_first = 0;
			
			string result = "";
			
			int len = data_.length();
			for(int i = 0; i < len; i++) {
				if (repeated.size() == 0 && data_[i + 1] != '{' && data_[i] != '{' && data_[i] != '}') {
					if (s_units.find(data_[i]) != string::npos) {
						real_res += data_[i];
					}
					else {
						real_res = "ERROR: Invalid input";
						return real_res;
					}
				}
				
				if (data_[i] == '{') {
					int counts = ns.find(data_[i - 1]);
					
					if (counts == string::npos) {
						real_res = "ERROR: Invalid input";
						return real_res;
					}
					repeated.push(counts);
					rep_start = i + 1;
				}
				if (data_[i] == '}' && repeated.size() != 0) {
					if (data_[i - 1] != '}') {
						rep_end = i - 1;
						
						for (int x = rep_start; x <= rep_end; x++) {
							if (s_units.find(data_[x]) == string::npos) {
								real_res = "ERROR: Invalid input";
								return real_res;
							}
						}
						
						repeated_str += data_.substr(rep_start, rep_end - rep_start + 1);
						if (data_[i + 1] != '}') rep_start = i + 1;
					}

					if (is_first != 0) {
						result = "";
						
						for (int x = 0; x < repeated.top(); x++) {
							result += repeated_str;
						}
						repeated.pop();
						repeated_str = result;
						
						if (repeated.size() == 0) {
							is_first = 0;
							repeated_str = "";
							real_res += result;
							continue;
						}
					}
					else if (is_first == 0) {
						is_first = 1;
						string mres = "";
						for (int x = 0; x < repeated.top(); x++) {
							mres += repeated_str;
						}
						repeated.pop();
						repeated_str = mres;
						if (repeated.size() == 0) {
							real_res += mres;
							is_first = 0;
							repeated_str = "";
						}
					}
				}
			}
			
			if (repeated.size() != 0) real_res = "ERROR: Invalid input";
			
			return real_res;
		}
};

// Implement your class here
istream& operator>> (istream& is, StringDecoder& sd) {
	cin >> sd.data_;
	return is;
}


ostream& operator<< (ostream& os, StringDecoder& sd) {
	os << sd.print();
	return os;
}
int main(){
	StringDecoder sd;
	
	// Note:
	// encoded input strings are read from an input file using operator>>
	// your class may store a decoded string in data_ to print it using operator<<
	while(cin >> sd){
		cout << sd << endl;
	}
	
	return 0;
}