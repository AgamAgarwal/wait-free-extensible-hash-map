#ifndef _WFE_HASH_MAP_H_
#define _WFE_HASH_MAP_H_

#include <atomic>

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

	bool put(char* key, int value);
	int* get(char* key);
};

#endif
