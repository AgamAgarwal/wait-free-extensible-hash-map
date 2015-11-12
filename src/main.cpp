#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <thread>
#include <random>
#include <chrono>
#include <unistd.h>

#include "HashMap.hpp"
#include "WFEHashMap.hpp"
#include "LBEHashMap.hpp"

using namespace std;

#define KEY_POOL_SIZE 50
#define KEY_POOL_MIN_LENGTH 8
#define KEY_SIZE 10

#define VALUE_MIN 0
#define VALUE_MAX 100

int NUM_PUTTERS,
	NUM_GETTERS,
	NUM_REMOVERS,
	ITER,
	MU;

const string OUTPUT_FOLDER = "output/";
const string OUTPUT_FILE_EXTENSION = ".out";

int hashMapType = 1;

HashMap* hm;

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
exponential_distribution<double> *exp_distribution;
vector<string> keyPool;

string getOutputFilename(int hmType, int opType, int tid) {
	return OUTPUT_FOLDER
		+ string(hmType==0?"wait_free_":"lock_based_")
		+ string(opType==0?"put_":(opType==1?"get_":"remove_"))
		+ to_string(tid)
		+ OUTPUT_FILE_EXTENSION;
}

long long getSysTime() {
	return chrono::system_clock::now().time_since_epoch().count();
}

string generateRandomString(int length) {
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	static uniform_int_distribution<int> distribution(0, sizeof(alphanum) - 1);

	string s = "";

	for (int i = 0; i < length; i++)
		s += alphanum[distribution(generator)];

	return s;
}

void generateKeyPool(int minLength, int maxLength, int size) {
	uniform_int_distribution<int> distribution(minLength, maxLength);
	for (int i = 0; i < size; i++) {
		keyPool.push_back(generateRandomString(distribution(generator)));
	}
}

string getRandomKey() {
	static uniform_int_distribution<int> distribution(0, KEY_POOL_SIZE - 1);
	return keyPool[distribution(generator)];
}

void putter(HashMap *hm, int me) {
	static uniform_int_distribution<int> distribution(VALUE_MIN, VALUE_MAX);

	string filename = getOutputFilename(hashMapType, 0, me);
	ofstream fout(filename);

	long long before, after;
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		before = getSysTime();
		hm->put(key, distribution(generator));
		after = getSysTime();
		fout<<(after-before)<<endl;

		usleep((*exp_distribution)(generator));
	}
	fout.close();
}

void getter(HashMap *hm, int me) {
	string filename = getOutputFilename(hashMapType, 1, me);
	ofstream fout(filename);

	long long before, after;
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		int* r;
		before = getSysTime();
		r = hm->get(key);
		after = getSysTime();
		fout<<(after-before)<<endl;

		usleep((*exp_distribution)(generator));
	}
	fout.close();
}

void remover(HashMap *hm, int me) {
	string filename = getOutputFilename(hashMapType, 2, me);
	ofstream fout(filename);

	long long before, after;
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		before = getSysTime();
		hm->remove(key);
		after = getSysTime();
		fout<<(after-before)<<endl;

		usleep((*exp_distribution)(generator));
	}
	fout.close();
}

void runTests() {
	thread* putters[NUM_PUTTERS];

	for (int i = 0; i < NUM_PUTTERS; i++) {
		putters[i] = new thread(putter, hm, i);
	}

	thread* getters[NUM_GETTERS];

	for (int i = 0; i < NUM_GETTERS; i++) {
		getters[i] = new thread(getter, hm, i);
	}

	thread* removers[NUM_REMOVERS];

	for (int i = 0; i < NUM_REMOVERS; i++) {
		removers[i] = new thread(remover, hm, i);
	}

	for (int i = 0; i < NUM_PUTTERS; i++) {
		putters[i]->join();
	}

	for (int i = 0; i < NUM_GETTERS; i++) {
		getters[i]->join();
	}

	for (int i = 0; i < NUM_REMOVERS; i++) {
		removers[i]->join();
	}
}

int main(int argc, char** argv) {
	string in_file;

	if(argc>=2)
		in_file = argv[1];
	else {
		cout<<"Enter the input file name: ";
		cin>>in_file;
	}

	ifstream fin(in_file);
	fin>>NUM_PUTTERS>>NUM_GETTERS>>NUM_REMOVERS>>ITER>>MU;
	fin.close();

	exp_distribution = new exponential_distribution<double>(1/((double)MU));

	generateKeyPool(KEY_POOL_MIN_LENGTH, KEY_SIZE, KEY_POOL_SIZE);

	hm = new WFEHashMap(KEY_SIZE);
	hashMapType = 0;
	runTests();

	hm = new LBEHashMap(KEY_SIZE);
	hashMapType = 1;
	runTests();

	return 0;
}
