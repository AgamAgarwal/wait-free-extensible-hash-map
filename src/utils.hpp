#ifndef _UTILS_H_
#define _UTILS_H_

#include "Node.hpp"
#include "DataNode.hpp"
#include "ArrayNode.hpp"

#ifdef DEBUG_H
#include <iostream>
#define DEBUG(x) std::cout<<x<<"\n"
#else
#define DEBUG(x)
#endif

#define ARRAY_LENGTH 256

extern Node* NULL_NODE;

char* hashKey(std::string, int);

Node* allocateNode(int, std::string, int);

void markDataNode(Node*, int);

Node* getNode(Node*, int);

bool isArrayNode(Node*);

bool isMarked(Node*);

ArrayNode* expandTable(Node*, int, Node*, int);

bool hashEqual(char*, char*, int);

bool unmarkedEqual(Node*, Node*, int);

#endif
