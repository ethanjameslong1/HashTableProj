#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <list>
#include <vector>
#include "utility"
#include <string>
#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include "base64.h"


using namespace std;
namespace cop4530 {

    // max_prime is used by the helpful functions provided
    // to you.
    static const unsigned int max_prime = 1301081;
    // the default_capacity is used if the initial capacity
    // of the underlying vector of the hash table is zero.
    static const unsigned int default_capacity = 11;
template <typename K,typename V>
class HashTable {
    typedef vector<list<pair<K,V>>> VLP;

public:
    unsigned long prime_below(unsigned long n);

    void setPrimes(std::vector<unsigned long> &vprimes);

    HashTable(size_t size);
    HashTable();
    inline ~HashTable() { clear(); }
    bool contains(const K & Key);
    bool match(const pair<K,V> & KVpair);
    bool insert(const pair<K,V> & KVpair);
    bool insert(pair<K,V> && KVpair);
    bool remove(const K & key);
    void clear();
    string getpassword(const string & s);
    bool load(const char*filename);
    void dump();
    bool write(string filename);
    size_t size;

private:
    void makeEmpty();
    void rehash();
    size_t myhash(const K &key);

    VLP bucketsVector;
    size_t capacity;
};


}
#endif
