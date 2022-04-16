#include "BSTSet.h"
#include "MyStack.h"
#include "SNode.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

BSTSet::BSTSet() //running time theta(1), space complexity O(1)
{
	root = NULL; //empty tree
}

BSTSet::BSTSet(const std::vector<int>& input) //running time theta(n^2), space complexity O(n)
{
	bool prevdirection = false; //used to determine direction of the prev node traveled
	if (input.size() > 0) {
		root = new TNode(input[0], NULL, NULL); //first thing in input is the root
		TNode* current = root;
		TNode* prev = root;
		for (int i = 1; i < input.size(); i++) { //for is inserting everything else in the input
			while (current!=NULL && current->element!=input[i]) { //while is finding the spot to insert it
				if (current->element > input[i]) { //taking it left
					prev = current;
					current = current->left;
					prevdirection = false;
				}
				else if (current->element < input[i]) { //taking it right
					prev = current;
					current = current->right;
					prevdirection = true;
				}
			}
			if (current==NULL && prevdirection) { //inserts to the right of previous node
				prev->right = new TNode(input[i], NULL, NULL);
			}
			if (current == NULL && !prevdirection) { //inserts to the left of previous node
				prev->left = new TNode(input[i], NULL, NULL);
			}
			current = root; //resets current and prev so each new addition starts from the root
			prev = root;
		}
	}
}

BSTSet::~BSTSet() //running time theta(n^2), space complexity O(1)
{
	sort();// sorts
	for (int i = findMax(root); i >= findMin(root); i--) { //removing from right to left
		remove(i);
	}
}

bool BSTSet::isIn(int v) //worst case run time is big theta(n) n is the number of tree nodes, and the average run time is big theta(logn) //space complexity O(1)
{
	if (root==NULL) { //empty tree
		return false;
	}
	TNode* current = root;
	while (current!=NULL) { //not empty tree and loops through
		if (v < current->element) { //moves left
			current=current->left;
		}
		else if (v > current->element) { //moves right
			current = current->right;
		}
		else { //if found returns true
			return true;
		}
	}
	return false; //if not found returns false
}

void BSTSet::add(int v) //running time theta(n^2), space complexity O(1)
{
	if (root == NULL) { //empty tree
		root = new TNode(v, NULL, NULL); //sets v to root
	}
	if (isIn(v)==false) { //if not found to prevent dupes
		bool prevdirection = false;
		TNode* current = root;
		TNode* prev = root;
		while (current != NULL) { //loops through the tree
			if (current->element > v) { //moves left
				prev = current;
				current = current->left;
				prevdirection = false;
			}
			else if (current->element < v) {//move right
				prev = current;
				current = current->right;
				prevdirection = true;
			}
		}
		if (current == NULL && prevdirection) {// add it to the right of prev node
			prev->right = new TNode(v, NULL, NULL);
		}
		if (current == NULL && !prevdirection) { // add it to the left of prev node
			prev->left = new TNode(v, NULL, NULL);
		}
		current = root; //resets 
		prev = root;
	}
}

int BSTSet::findMin(TNode* t) { //finds min aka the very left //running time theta(n), space complexity O(1)
	if (t == NULL) { 
		return NULL;
	}
	while (t->left != NULL) {
		t = t->left;
	}
	return (t->element);
}

int BSTSet::findMax(TNode* t) { //finds max aka the very right //running time theta(n), space complexity O(1)
	if (t == NULL) {
		return NULL;
	}
	while (t->right != NULL) {
		t = t->right;
	}
	return (t->element);
}
void BSTSet::sort() { //sorts vector in increasing order //running time theta(n), space complexity O(1)
	TNode* newroot = new TNode(findMin(root), NULL, NULL); //creates new root to replace root later
	TNode* current = newroot;
	for (int i = findMin(root)+1; i <= findMax(root); i++) { //checks every possibility within vector
		if (isIn(i)) { //if i is in tree
			current->right = new TNode(i,NULL,NULL); //adds it in
			current = current->right;
		}
	}
	root = newroot; //replaces root with newroot
}
bool BSTSet::remove(int v) //running time theta(n), space complexity O(1)
{
	if (root == NULL || isIn(v) == false) { //empty tree or not found in tree
		return false;
	}
	sort();
	if (root->element == v) { //overwrites root
		root = root->right;
		return true;
	}
	TNode* current = root;
	TNode* prev = root;
	while (current->element != v) { //searches for v
		prev = current;
		current = current->right;
	}
	if (current->right == NULL) { //case 1 when the node you want to delete is a leaf
		prev->right = NULL;
		free(current);
	}
	else { //case 3 when the node you want to delete only has 1 child
		prev->right = current->right;
	}
    return true; 
}

void BSTSet::Union(const BSTSet& s) //running time theta(n), space complexity O(1)
{
	BSTSet scopy = s; //duplicates s to use isIn() later
	for (int i = findMin(s.root); i <= findMax(s.root); i++) { //loops from min to max of s
		if (scopy.isIn(i)) { //if it's in s add it to this
			add(i);
		}
	}
}

void BSTSet::intersection(const BSTSet& s) //running time theta(n), space complexity O(1)
{
	sort(); //sorts
	BSTSet scopy = s; //duplicates s
	TNode* current = root;
	while (current != NULL) { //loops through tree
		if (!isIn(current->element) || !scopy.isIn(current->element)) { //removes things that are not in common
			remove(current->element);
		}
		current = current->right;
	}
}

void BSTSet::difference(const BSTSet& s) //running time theta(n^2), space complexity O(1)
{
	BSTSet scopy = s; //duplicates s
	for (int i = findMin(s.root); i <= findMax(s.root); i++) { //loops from min to max
		if (scopy.isIn(i)) { //removes what is in common
			remove(i);
		}
	}
}

int BSTSet::size() //running time theta(n),space complexity O(n)
{
	if (root == NULL) { //empty tree
		return 0;
	}
	sort();
	TNode* current = root;
	int i = 0;
	while (current != NULL) { //loops through tree
		i++;
		current = current->right;
	}
	return i;
}

int BSTSet::height() //running time theta(n),space complexity O(n)
{
	if (root == NULL) {
		return -1;
	}
	int height = 0;
	for (int i = findMin(root); i <= findMax(root); i++) { //loops to min to max of tree
		if (height < depth(i)) { //finds depth of every node and sets height has the highest depth
			height = depth(i);
		}
	}
	return height;
}

int BSTSet::depth(int i) { //running time theta(n),space complexity O(n)
	TNode* current = root;
	int count = 0;
	while (current != NULL) { //loops through tree
		if (i < current->element) { //moves left
			current = current->left;
		}
		else if (i > current->element) { //moves right
			current = current->right;
		}
		else {
			return count; //returns depth if found
		}
		count++;
	}
	return 0; //returns 0 otherwise
}

// create and use class MyStack
MyStack::MyStack() //running time theta(1),space complexity O(1)
{
	root = NULL; //empty tree
}

bool MyStack::isempty() { //running time theta(1),space complexity O(1)
	return(root == NULL);
}

void MyStack::push(TNode* v) //running time theta(1),space complexity O(1)
{
	root = new SNode(v, root); //creates new node 
}

TNode* MyStack::pop() //running time theta(1), space comeplexity O(1)
{
	if (isempty()) {
		throw std::underflow_error("Stack underflow");
	}
	else {
		SNode* oldroot = root; //tmp to hold root
		TNode* current = root->element;
		root = root->next;
		delete oldroot;
		return current;
	}
}

void BSTSet::printNonRec() //running time theta(n), space comeplexity O(n)
{
	TNode* pop;
	MyStack stack = MyStack();
	TNode* current = root;
	
	while (current != NULL || !stack.isempty()) { //step 5
		if (current != NULL) {
			stack.push(current);
			current = current->left;
		}
		if(current==NULL) {
			current = stack.pop();
			cout << current->element << ",";
			current = current->right;
		}
	}
}

// Do not modify following provided methods

void BSTSet::printBSTSet()
{
    if (root == NULL)
        std::cout << "";
    else {
        printBSTSet(root);
    }
}

void BSTSet::printBSTSet(TNode* t)
{
    if (t != NULL) {
        printBSTSet(t->left);
        std::cout << t->element << ",";
        printBSTSet(t->right);
    }
}
