#ifndef SKIP_LIST_H
#define SKIP_LIST_H 

#include <stdlib.h>                                                                                                    
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

template<typename Key, typename Value>
class Skip_list{
	private:
		struct Skip_Node {
			Key _k;
			Value _v;
			int _height;
			vector<Skip_Node*> _next;

			Skip_Node (const Key& k, const Value& v, int h):
				_k(k), _v(v), _height(h), _next(h, nullptr){}; 
		};

		// pointer to first node
    		Skip_Node* _header;
    		// last node
    		Skip_Node* NIL;

		int _height;
		double _q;
		double _rng() {
			return rand()/double(RAND_MAX);
		};
		int nodeLevel(const vector<Skip_Node*>& v);

		int total_search_cost;
                int number_pointers;

	public:
    		Skip_list(double q){
			_q = q;
			Skip_list<Key, Value>::_height = 0;
			// Initialize the head of the skip list

     			// smallest possible key
     			int headKey = numeric_limits<int>::min();
     			_header = new Skip_Node(headKey, 0, 100);

			// Initialize the last element of the list

     			// largest possible key
     			int nilKey = numeric_limits<int>::max();
    			NIL = new Skip_Node(nilKey, 1000000, 100);

     			// Connect start to end
     			// connect all the levels/forward pointers of the header to NIL
     			for (size_t i = 0; i < _header->_next.size(); ++i)
         			_header->_next[i] = NIL;
			
			number_pointers = 0;		
		};
    		~Skip_list (){
			delete _header;
			delete NIL;
		};

		int lookup(const Key& k);
    		void insert(const Key& k, const Value& v);
    		void remove(const Key& k);
		int get_number_pointers();
		int get_total_search_cost();
		void print();
};

// ================================================================

template <typename Key, typename Value>
int Skip_list<Key, Value>::get_number_pointers(){
	return number_pointers + _height; // add current height of _header
}

template <typename Key, typename Value>
int Skip_list<Key, Value>::get_total_search_cost(){
	return total_search_cost;
}
/*
    Function: nodeLevel()
    Use: Implicitly in most of the member functions.

    It returns the number of non-null pointers
    corresponding to the level of the current node.
    (the node that contains the checked vector of 
    forward pointers)

    If list empty returns 1.
*/
template <typename Key, typename Value>
int Skip_list<Key, Value>::nodeLevel (const vector<Skip_Node*>& v) {
    int currentLevel = 1;
    // last element's key is the largest
    int nilKey = numeric_limits<int>::max();

    if (v[0]->_k == nilKey) {
        return currentLevel;
    }

    for (size_t i = 0; i < v.size(); ++i) {

        if (v[i] != nullptr && v[i]->_k != nilKey) {
            ++currentLevel;
        } else { 
            break;
        }
    }
    return currentLevel;
}

/*
    Function: print()
    Use: skip_list_obj.print();

    It prints the key, value, level
    of each node of the skip list.

    Prints two nodes per line.
*/
template <typename Key, typename Value>
void Skip_list<Key, Value>::print () {
    Skip_Node* list = _header;
    int lineLenght = 1;

    std::cout <<"{";

    while (list->_next[0] != nullptr) {
        std::cout <<"value: "<< list->_next[0]->_v
                  <<", key: "<< list->_next[0]->_k
                  <<", level: "<< nodeLevel(list->_next); 

        list = list->_next[0];

        if (list->_next[0] != nullptr) std::cout <<" : ";

        if (++lineLenght % 2 == 0) std::cout <<"\n";
    }
    std::cout <<"}\n";
}
/*
    Function: find()
    Use: Skip_Node* found = skip_list_obj.find(searchKey);

    It searches the skip list and
    returns the element corresponding 
    to the searchKey; otherwise it returns
    failure, in the form of null pointer.
*/

template<typename Key, typename Value>
int Skip_list<Key, Value>::lookup(const Key& k) {
	total_search_cost = 0;	
    Skip_Node* p = _header;
    int l =_height;
    cout<<"Looking for key "<<k<<endl;
    // unsigned int currentMaximum = nodeLevel(head->forward);
    while(l>=0){
                 if (p -> _next[l] == nullptr or k < p-> _next[l] -> _k){
                         --l;
			 //total_search_cost ++;
                } else {
                         p=p -> _next[l];
			 total_search_cost ++;
                }
		cout<<"In level "<<l<<", node with key "<<(*p)._k<<endl; 
         }

    if (p->_k == k) {
        //return p;
	cout<<"found at pointer: "<<p<<endl;
    } else {
        //return nullptr;
	cout<<"Not found"<<endl;
    }
   	return get_total_search_cost();
} 


// Modifying member functions
/*
    Function: insert();
    Use: void insert(searchKey, newValue);

    It searches the skip list for elements
    with seachKey, if there is an element
    with that key its value is reassigned to the 
    newValue, otherwise it creates and splices
    a new node, of random level.
*/
template <typename Key, typename Value>
void Skip_list<Key, Value>::insert(const Key& k, const Value& v) {
	int l = _height;
    // reassign if node exists 
    Skip_Node* p = nullptr;

    // vector of pointers that needs to be updated to account for the new node
    vector<Skip_Node*> update(_header->_next);
    // unsigned int currentMaximum = nodeLevel(_header->_next);
    p = _header;

    // search the list 
	while(l>=0){
		if (p -> _next[l] == nullptr or k <= p-> _next[l] -> _k){
			update[l] = p;
			--l;
		} else {
			p=p -> _next[l];
		}
	}
	l++;
	if ( p -> _next[0] == nullptr or p -> _next[0] -> _k != k){
		    // create new node
		int h = l;
		while(_rng() > _q){
                         ++h;
                 };
		//cout<<"New node's height is: "<<h<<endl;

		if (h > l) {
            		for (int i = _height; i < h; ++i) {
				update[i] = _header;
				_height ++;
            		}   
        	}
		Skip_Node* nn = new Skip_Node(k, v, h+1);
		number_pointers = number_pointers +h+1;
   		 // connect pointers of predecessors and new node to successors
    		for (int i = 0; i < h+1; ++i) {

       			 nn->_next[i] = update[i]->_next[i];
        		update[i]->_next[i] = nn;
    		}
	cout<<"Inserted node "<<(*nn)._k<<" with height "<<(*nn)._next.size()<<endl;	
	}
}

/*
    Function: delete_node()
    Use: skip_list_obj.erase(searchKey)

    It deletes the element containing 
   searchKey, if it exists.
*/

template<typename Key, typename Value>
void Skip_list<Key, Value>::remove(const Key& k) {
    // vector of pointers that needs to be updated to account for the deleted node
    vector<Skip_Node*> update(_header->_next);
    Skip_Node* p = _header;
	int l = _height;
    while(l>=0){
                 if (p -> _next[l] == nullptr or k <= p-> _next[l] -> _k){
                         update[l] = p;
                         --l;
                 } else {
                         p=p -> _next[l];
                 }
         }
    p = p->_next[0];

    // update pointers and delete node 
    if (p->_k == k) {
        for (size_t i = 0; i < update.size(); ++i) {

            if (update[i]->_next[i] != p) {

                break;
            }
            update[i]->_next[i] = p->_next[i];
        }
	number_pointers = number_pointers - (*p)._next.size()-1;
        delete p;    
    }    
}

#include "Skip_list.cpp"
#endif
