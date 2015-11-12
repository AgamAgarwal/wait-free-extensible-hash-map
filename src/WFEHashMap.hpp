#ifndef _WFE_HASH_MAP_H_
#define _WFE_HASH_MAP_H_

#include <atomic>
#include <string>

#include "DataNode.hpp"
#include "ArrayNode.hpp"
#include "utils.hpp"

#define MAX_FAIL_COUNT 10

class WFEHashMap {
private:
	Node* head;
	const int keySize;

public:
	WFEHashMap(int _keySize);

	bool put(std::string key, int value);
	bool remove(std::string key);
	int* get(std::string key);
};

#endif
