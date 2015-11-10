#ifndef _UTILS_H_
#define _UTILS_H_

#include "Node.cpp"
#include "DataNode.cpp"
#include "ArrayNode.cpp"

#ifdef DEBUG_H
#include <iostream>
#define DEBUG(x) std::cout<<x<<"\n"
#else
#define DEBUG(x)
#endif

#define ARRAY_LENGTH 256

extern Node* NULL_NODE;

char* hashKey(char*);

Node* allocateNode(int, char*);

void markDataNode(Node*, int);

Node* getNode(Node*, int);

bool isArrayNode(Node*);

bool isMarked(Node*);

ArrayNode* expandTable(Node*, int, Node*, int);

bool hashEqual(char*, char*, int);

bool unmarkedEqual(Node*, Node*, int);

#endif
