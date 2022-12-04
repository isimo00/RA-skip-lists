#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
using namespace std;

template <typename Key, typename Value>
class Dictionary{
	private:
		struct node_skip_list { // class/struct delcaration of node_skip_list
			friend class Dictionary<Key, Value>;		
			Key _k;
			Value _v;
			int _height;
			vector<node_skip_list*> _next;

			node_skip_list(const Key& k, const Value& v, int h):
			_k(k), _v(v), _height(h), _next(h, nullptr){};
			
		};
		node_skip_list* _header;
		int _height;
		double _p;
		double _rng() {
			//srand ((unsigned) time(NULL) ); // seed for random generator
			return rand()/double(RAND_MAX) ;
		}
	public:
		Dictionary(double q){
                         Dictionary<Key, Value>::_height = 1; // setting ok
                         _p = q;
			 (*_header)._next.push_back(nullptr);// https://stackoverflow.com/questions/61545236/3810-error-member-reference-base-type-node-is-not-a-structure-or-union-p
                         // set p to indicated value by user
                         // set height to 0 (initial value for an empty skiplist)
                };
                ~Dictionary(){};

		void lookup(const Key& k, bool& exists, Value& v) const throw();
                int lookup_skip_list(node_skip_list* p, int l, const Key& k) const throw();
                void insert_skip_list(const Key& k, Value& v);
		void remove_skip_list(const Key& k, Value& v);
		// void print_node(const Key& k);

		int total_search_cost() const;
		int number_pointers() const;

};

template <typename Key, typename Value>
void Dictionary<Key,Value>::lookup(const Key& k, bool& exists, Value& v) const throw () { // nullptr? error?
	node_skip_list* p=lookup_skip_list(_header, _height-1, k);
	if (p == nullptr)
		exists = false;
	else{
		exists = true;
		v= p-> _v;
	}
}

template <typename Key, typename Value>
int Dictionary<Key,Value>::lookup_skip_list(node_skip_list* p, int l, const Key& k) const throw() {
		while(l >= 0)
			if (p -> _next[l] == nullptr or k <= p-> _next[l] -> _k)
				--l;
			else
				p=p -> _next[l];
		if (p -> _next[0] == nullptr or p -> _next[0] -> _k !=k){
		// k is not present
			return 0; // return nullptr
			}
		else // k is present
		    return p -> _next[0];
}

template <typename Key, typename Value>
void Dictionary<Key,Value>::insert_skip_list(const Key& k, Value& v){
	cout<<"trying to insert value: "<<v<<endl;
	node_skip_list* p = _header;
	int l=_height - 1;
	vector<node_skip_list*> pred(_height);

	cout<<"vector next"<<(*p)._next[0]<<endl;
	while (l >= 0){ // for current level
		if (p -> _next[l] == nullptr or k <= p-> _next[l] -> _k){
			// if same level doesn't have more nodes or next is too big
			pred[l] = p; // pred[level] = this node's pointer 
			--l; // stay in current node, go down one level
		} else { // go to next node in same level (same level does have valid nodes)
			p=p -> _next[l]; // pointer takes pointer of next node in same level
		}
	}
	if ( p -> _next[0] == nullptr or p -> _next[0] -> _k != k){
		// k is not present, add new node here
		l=0;
		int h=l;
		while(_rng() > _p){
			++h;
		};
		cout<<"Node height is: "<<h<<endl;

		node_skip_list* nn = new node_skip_list(k, v, h);
		// ++number_pointers();
		if (h> _height){
			for (int i=_height; i<=h; i++){
				(*_header)._height ++;
				_height ++;
				pred[i] = _header;
			}
			// add new levels to the header
			// make pred[i] = _header for all i=_height .. h-1 (rango)
		}
		cout<<"New header height is: "<<_height<<endl;	

		for (int i=h-l; i>=0; --i){
			nn -> _next[i] = pred[i] -> _next[i];
			pred[i] -> _next[i] = nn;
		}
		cout<<"Node with key "<<k<<" has been added."<<endl;
	}
	else // k is present
	     	p-> _next[0] -> _v=v;
}

template <typename Key, typename Value>
void Dictionary<Key,Value>::remove_skip_list(const Key& k, Value& v){
}

int main(){

	srand((unsigned) time(NULL));
	Dictionary<int, int> SL(0.4);
	int len=10;

	for (int i=1; i<len; i++){
		SL.insert_skip_list(i, i);
	}
}
