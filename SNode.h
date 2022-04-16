#ifndef SNODE_H_
#define SNODE_H_

#include "TNode.h"

class SNode
{
public:
    TNode* element;
    SNode* next;

    SNode(TNode* i, SNode* n)
    {
        element = i;
        next = n;
    }
};

#endif /* TNODE_H_ */

