#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Bucket {
	private:
	int n = 0;
	int index = 0;
	vector<pair<string, int>> entries;
	
	int finder(string key) {
		for (int i = 0; i < n; i++) {
			if (entries[i].first == key)
				return i;
		}
		return -1;
	}
	
	public:
	Bucket(int index_) : index(index_) {}
	int size() { return n; }
	int getIndex() { return index; }
	vector<pair<string, int>> getEntries() { return entries; }
	
	bool insert(string key, int value) {
		int exists = finder(key);
		if (exists == -1) {
			entries.emplace_back(key, value);
			n++;
			return true;
		}
		else {
			entries[exists].second = value;
			return false;
		}
	}
	
	bool remove(string key, int value) {
		int exists = finder(key);
		if (exists == -1) {
			return false;
		}
		else {
			entries.erase(entries.begin() + exists);
			n--;
			return true;
		}
	}
	
	void print() {
		for (int i = 0; i < size(); i++) 
			cout << "(" << entries[i].first << "," << entries[i].second << ")" << endl;
	}
};


class HashTable {
	private:
	int n = 0;
	int alpha = 1;
	int bucket_size = 512;
	double load_factor = (double) n / bucket_size;
	double min_load_factor = 0.5;
	double max_load_factor = 0.5;
	vector<Bucket> bucket_array;
	vector<pair<int, int>> rehashed_size;
	
	int hashCode(string key) {
		long long result = 0;
		long long modulo_ = 2147483647;
		for (int i = 0; i < key.length(); i++) {
			result = ((result * alpha) + key[i]) % modulo_;
		}
		return int(result % bucket_size);
	}
	
	void rehashing(int rehashing_size) {
		if (rehashing_size >= 512) {
			rehashed_size.emplace_back(bucket_size, rehashing_size);
			bucket_size = rehashing_size;

			vector<Bucket> rehashed;
			for (int i = 0; i < rehashing_size; i++) 
				rehashed.emplace_back(i);
			
			for (auto iter = bucket_array.begin(); iter < bucket_array.end(); iter++) {
				vector<pair<string, int>> en = iter->getEntries();
				for (auto iter2 = en.begin(); iter2 < en.end(); iter2++) {
					int rehashing_key = hashCode(iter2->first);
					rehashed[rehashing_key].insert(iter2->first, iter2->second);
				}
			}
			
			bucket_array.clear();
			bucket_array.assign(rehashed.begin(), rehashed.end());
			updateLoadFactor();
		}
	}
	
	public:
	HashTable() {
		for (int i = 0; i < bucket_size; i++) 
			bucket_array.emplace_back(i);
	}
	int size() { return n; }
	int getBucketArraySize() { return bucket_size; }
	void setAlpha(int alpha_) { alpha = alpha_; }
	void setMinLoadFactor(double factor) { min_load_factor = factor; }
	void setMaxLoadFactor(double factor) { max_load_factor = factor; }
	
	int getLongestBucketIndex() {
		int max_index = 0;
		for (int i = 1; i < bucket_size; i++) 
			if (bucket_array[max_index].size() <= bucket_array[i].size()) 
				max_index = i;
		return max_index;
	}
	
	void printBucket(int bucket_index) {
		bucket_array[bucket_index].print();
	}
	
	void printRehashed() {
		if (rehashed_size.size() != 0) 
			for(int i = 0; i < rehashed_size.size(); i++) 
				cout << "Rehashing: " << rehashed_size[i].first << " -> " << rehashed_size[i].second << endl;
	}
	
	void updateLoadFactor() {
		load_factor = (double) n / bucket_size;
		if (load_factor < min_load_factor) rehashing(bucket_size / 2);
		if (load_factor > max_load_factor) rehashing(bucket_size * 2);
	}
	
	void insert(string key, int value) {
		int hash_code = hashCode(key);
		if (bucket_array[hash_code].insert(key, value)) {
			n++;
			updateLoadFactor();
		}
	}
	
	void remove(string key, int value) {
		int hash_code = hashCode(key);
		if (bucket_array[hash_code].remove(key, value)) {
			n--;
			updateLoadFactor();
		}
	}
	
	int getBucketInLength(int c) {
		int result = 0;
		for (int i = 0; i < bucket_size; i++) 
			if (bucket_array[i].size() > c) result++;
		return result;
	}
};


void getInput(HashTable* table, int count) {
	for (int i = 0; i < count; i++) {
		char command;
		string key;
		int value;
		cin >> command >> key >> value;
		
		if (command == 'i') table->insert(key, value);
		if (command == 'r') table->remove(key, value);
	}
}


void printResult(HashTable table) {
	table.printRehashed();
	cout << "Number of entries: " << table.size() << endl;
	cout << "Size of the bucket array: " << table.getBucketArraySize() << endl;
	cout << table.getBucketInLength(5) << " buckets contain more than 5 elements" << endl;
	
	int LONGEST_BUCKET_INDEX = table.getLongestBucketIndex();
	cout << "The longest bucket: " << LONGEST_BUCKET_INDEX << endl;
	table.printBucket(LONGEST_BUCKET_INDEX);
}


int main(void) {
	int a, ENTRY_COUNT;
	float MIN_LOAD_FACTOR, MAX_LOAD_FACTOR;
	
	cin >> a >> MIN_LOAD_FACTOR >> MAX_LOAD_FACTOR;
	cin >> ENTRY_COUNT;
	
	HashTable table;
	table.setAlpha(a);
	table.setMinLoadFactor(MIN_LOAD_FACTOR);
	table.setMaxLoadFactor(MAX_LOAD_FACTOR);
	getInput(&table, ENTRY_COUNT);
	printResult(table);
	
	return 0;
}
