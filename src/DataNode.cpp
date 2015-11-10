#ifndef _DATA_NODE_H_
#define _DATA_NODE_H_

#include "Node.cpp"
#include <iostream>

class DataNode: public Node {
private:
	char* key;
public:
	int value;
	bool marked;

	DataNode(char* _key, int _value) {
		key = _key;
		value = _value;
		std::cout<<"data node constructor"<<std::endl;
	}

	char* getKey() {
		return key;
	}
};

#endif
