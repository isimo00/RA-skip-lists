#include <stdlib.h>
#include <vector>
#include <cstdlib>
using namespace std;

template <typename Key, typename Value>
class Dictionary{
	private:
		struct node_skip_list {
			Key _k;
			Value _v;
			int _height;
			vector<node_skip_list*> _next;

			node_skip_list(const Key& k, const Value& v, int h):
				_k(k), _v(v), _height(h), _next(h, nullptr){}
			
		};
		node_skip_list* _header;
		int _height;
		double _p;

		double _rng() {return rand() % 1;}
	public:
				void lookup(const Key& k, bool& exists, Value& v) const throw();
                int lookup_skip_list(node_skip_list* p, int l, const Key& k) const throw();
                void insert_skip_list(const Key& k, Value& v, int _height);
	
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
			return nullptr;}
		else // k is present
		      	return p -> _next[0];
	}

// diapo 27

template <typename Key, typename Value>
void Dictionary<Key,Value>::insert_skip_list(const Key& k, Value& v, int _height){
	node_skip_list* p = _header;
	int l=_height -l;
	vector<node_skip_list*> pred(_height);
	while (l >= 0){
		if (p -> _next[l] == nullptr or k <= p-> _next[l] -> _k){
			pred[l] = p;
			--l;
		} else {
			p=p -> _next[l];
		}
	if ( p -> _next[0] == nullptr or p -> _next[0] -> _k != k){
		// k is not present, add new node here
		int h=l;
		while(_rng() > _p) ++h;
		node_skip_list* nn = new node_skip_list(k, v, h);
		if (h> _height){
			// add new levels to the header
			// make pred[i] = _header for all i=_height .. h-1 (rango)
		}	

		for (int i=h-l; i>=0; --i){
			nn -> _next[i] = pred[i] -> _next[i];
			pred[i] -> _next[i] = nn;
		}
	}
	else // k is present
	     	p-> _next[0] -> _v=v;
}}