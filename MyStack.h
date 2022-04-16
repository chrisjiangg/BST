#ifndef MyStack_H_
#define MyStack_H_

#include "TNode.h"
#include "MyStack.h"
#include "SNode.h"
#include <vector>

class MyStack
{
private:
    SNode* root = NULL;
public:
    MyStack();

    bool isempty();
    void push(TNode* v);
    TNode* pop();
};
#endif /* MyStack_H_ */