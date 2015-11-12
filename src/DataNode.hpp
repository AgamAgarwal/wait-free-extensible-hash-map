#ifndef _DATA_NODE_H_
#define _DATA_NODE_H_

#include <string>
#include "Node.hpp"
#include "utils.hpp"

class DataNode: public Node {
private:
	std::string key;
	char* hash;
	int keySize;
public:
	int value;
	bool marked;

	DataNode(std::string _key, int _value, int _keySize);
	DataNode(const DataNode&);
	~DataNode();
	std::string getKey();
	char* getHash();
};

#endif
