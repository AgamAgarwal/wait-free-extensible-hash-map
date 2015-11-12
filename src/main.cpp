#include <string>
#include <cstring>
#include <iostream>
#include <thread>

#include "WFEHashMap.hpp"

using namespace std;

#define NUM_PUTTERS 10
#define NUM_GETTERS 10
#define NUM_REMOVERS 10
#define ITER 10

void putter(WFEHashMap *hm, int me) {
	string a = "abcde";

	for (int i = 0; i < ITER; i++) {
		hm->put(a, 9);
	}
}

void getter(WFEHashMap *hm, int me) {
	string a = "abcde";

	for (int i = 0; i < ITER; i++) {
		int* r;
		r = hm->get(a);
		if (r == nullptr)
			cout<<-1<<endl;
		else
			cout<<(*r)<<endl;
	}
}

void remover(WFEHashMap *hm, int me) {
	string a = "abcde";

	for (int i = 0; i < ITER; i++) {
		cout<<"Remove status: "<<hm->remove(a)<<endl;
	}
}

int main() {
	WFEHashMap *x = new WFEHashMap(5);


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
