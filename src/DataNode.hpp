#ifndef _DATA_NODE_H_
#define _DATA_NODE_H_

#include "Node.hpp"
#include "utils.hpp"

class DataNode: public Node {
private:
	char* key;
	char* hash;
public:
	int value;
	bool marked;

	DataNode(char* _key, int _value);
	char* getKey();
	char* getHash();
};

#endif
