#ifndef _HASH_MAP_H_
#define _HASH_MAP_H_
#include <string>

#define MAX_FAIL_COUNT 10

class HashMap {
public:
	virtual bool put(std::string key, int value) = 0;
	virtual bool remove(std::string key) = 0;
	virtual int* get(std::string key) = 0;
};

#endif
