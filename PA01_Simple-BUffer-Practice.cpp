#include <iostream>
#include <string>

using namespace std;

// Your class SimpleBuffer
template <class T>
class SimpleBuffer{
	private:
		T data_;
	
	public:	
		// Implement your public members
		SimpleBuffer(T dat): data_(dat) {};
		template <typename B>
		friend ostream& operator<<(ostream& os, const SimpleBuffer<B>& dat);
		template <typename B>
		friend istream& operator>>(istream& is, SimpleBuffer<B>& dat);
};	// Class implementation ends

// Implement your overloaded functions
template <typename B>
ostream& operator<<(ostream& os, const SimpleBuffer<B>& dat) {
	os << "Current data: " << dat.data_;
	return os;
};

template <typename B>
istream& operator>>(istream& is, SimpleBuffer<B>& dat) {
	B temp;
	is >> temp;
	
	dat.data_ += temp;
	
	return is;
};


// main() of your program for test
int main() {
	SimpleBuffer<string> buf_str("");
	
	for(int k = 0; k < 3; k++){
		cin >> buf_str;
		cout << buf_str << endl;
	}
	
	SimpleBuffer<int> buf_int(0);
	
	for(int k = 0; k < 5; k++){
		cin >> buf_int;
		cout << buf_int << endl;
	}
	
	return 0;
}