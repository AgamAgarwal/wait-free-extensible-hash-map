#include <string>
#include <cstring>
#include <iostream>
#include <thread>
#include <random>

#include "WFEHashMap.hpp"

using namespace std;

#define NUM_PUTTERS 10
#define NUM_GETTERS 10
#define NUM_REMOVERS 10
#define ITER 10

#define KEY_POOL_SIZE 50
#define KEY_POOL_MIN_LENGTH 10
#define KEY_SIZE 10

default_random_engine generator(chrono::system_clock::now().time_since_epoch().count());
vector<string> keyPool;

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

void putter(WFEHashMap *hm, int me) {
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		hm->put(key, 9);
	}
}

void getter(WFEHashMap *hm, int me) {
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		int* r;
		r = hm->get(key);
		if (r == nullptr)
			cout<<key<<" : NULL"<<endl;
		else
			cout<<key<<" : "<<(*r)<<endl;
	}
}

void remover(WFEHashMap *hm, int me) {
	for (int i = 0; i < ITER; i++) {
		string key = getRandomKey();
		cout<<"Removed "<<key<<hm->remove(key)<<endl;
	}
}

int main() {
	generateKeyPool(KEY_POOL_MIN_LENGTH, KEY_SIZE, KEY_POOL_SIZE);

	WFEHashMap *x = new WFEHashMap(KEY_SIZE);

	thread* putters[NUM_PUTTERS];

	for (int i = 0; i < NUM_PUTTERS; i++) {
		putters[i] = new thread(putter, x, i);
	}

	thread* getters[NUM_GETTERS];

	for (int i = 0; i < NUM_GETTERS; i++) {
		getters[i] = new thread(getter, x, i);
	}

	thread* removers[NUM_REMOVERS];

	for (int i = 0; i < NUM_REMOVERS; i++) {
		removers[i] = new thread(remover, x, i);
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
	return 0;
}
