#ifndef _LBE_HASH_MAP_H_
#define _LBE_HASH_MAP_H_

#include <atomic>
#include <string>
#include <mutex>

#include "HashMap.hpp"
#include "DataNode.hpp"
#include "ArrayNode.hpp"
#include "utils.hpp"

#define MAX_FAIL_COUNT 10

class LBEHashMap: public HashMap {
private:
	Node* head;
	const int keySize;
	std::mutex lock;

public:
	LBEHashMap(int _keySize);

	bool put(std::string key, int value);
	bool remove(std::string key);
	int* get(std::string key);
};

#endif
