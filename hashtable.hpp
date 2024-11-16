#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hashtable.h"

using namespace std;
using namespace cop4530;
const int DEFAULT_CAPACITY = 101;
//CODE SOURCE: David Gaitros
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below (unsigned long n)
{
  if (n > max_prime)
  {
    cerr << "** input too large for prime_below()\n";
    return 0;
  }
  if (n == max_prime)
  {
    return max_prime;
  }
  if (n <= 1)
  {
    cerr << "** input too small \n";
    return 0;
  }

  // now: 2 <= n < max_prime
  vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
  {
    if (v[n] == 1)
      return n;
    --n;
  }

  return 2;
}

//CODE SOURCE: David Gaitros
//Sets all prime number indexes to 1. Called by method prime_below(n)
template <typename K, typename V>
void HashTable<K,V>::setPrimes(vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
  {
    if (vprimes[i] == 1)
      for(j = i + i ; j < n; j += i)
      vprimes[j] = 0;
  }
}



/*
 * Constructor and Destructor
 */
template <typename K, typename V>
HashTable<K,V>::HashTable(size_t hashCapacity)
{
  if (hashCapacity<=0) hashCapacity = DEFAULT_CAPACITY;
  hashCapacity = prime_below(hashCapacity);
  bucketsVector.resize(hashCapacity);
  this->capacity = hashCapacity;
  this->size = 0;
}
template <typename K, typename V>
HashTable<K,V>::HashTable()
{
  capacity = prime_below(DEFAULT_CAPACITY);
  bucketsVector.resize(capacity);
  this->size = 0;
}

/*
 * Inserts and Hash Stuff
 */

template <typename K, typename V>
bool HashTable<K,V>::insert(const pair<K,V> & KVpair)
{
  if (match(KVpair)) return false;
  int listIndex = myhash(KVpair.first);
  bucketsVector[listIndex].push_back(KVpair);
  size++;
  if (size>=capacity) rehash();
  return true;
}

template <typename K, typename V>
bool HashTable<K,V>::insert(pair<K,V> && KVpair)
{
  if (match(KVpair)) return false;
  pair<K,V> KVpair2 = move(KVpair);
  bucketsVector[myhash(KVpair2.first)].push_back(KVpair2);
  size++;
  if (size>=capacity) rehash();
  return true;
}

template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &key)
{
  int hashIndex=0;
  for (int i=0; i < key.size(); i++)
  {
    hashIndex += (int)(key[i]);
    hashIndex ^= 13;
  }
  return hashIndex % capacity;
}


template <typename K, typename V>
void HashTable<K,V>::rehash()
{
  unsigned long newCapacity = prime_below(capacity*3);
  VLP new_bucketsVector(newCapacity);
  capacity = newCapacity;
  for (int i=0; i < bucketsVector.size(); i++)
  {
    if (bucketsVector[i].empty()) continue;
    typename list<pair<K,V>>::iterator it = bucketsVector[i].begin();
    for (int j=0; j < bucketsVector[i].size(); j++)
    {
      new_bucketsVector[myhash((*it).first)].push_back(*it);
      ++it;
    }
  }
  bucketsVector = new_bucketsVector;
}

/*
 * Match and gets
 */
template <typename K, typename V>
bool HashTable<K,V>::match(const pair<K,V> & KVpair)
{
  int hashIndex = myhash(KVpair.first);
  typename list<pair<K,V>>::iterator it = bucketsVector[hashIndex].begin();
  for (int i=0; i < bucketsVector[hashIndex].size(); i++)
  {
    if (*it == KVpair) return true;
    ++it;
  }
  return false;
}

template <typename K,typename V>
string HashTable<K,V>::getValue(const string & Key)
{
  int hashIndex = myhash(Key);
  typename list<pair<K,V>>::iterator pos = bucketsVector[hashIndex].begin();

  while (pos != bucketsVector[hashIndex].end())
  {
    if (Key == (*pos).first) return (*pos).second;
    ++pos;
  }
  return "ERROR NOT FOUND";
}

template <typename K, typename V>
bool HashTable<K,V>::contains(const K & Key)
  {
    typename list<pair<K,V>>::iterator pos = bucketsVector[myhash(Key)].begin();

    while (pos != bucketsVector[myhash(Key)].end())
    {
      if (Key == (*pos).first) return true;
      ++pos;
    }
    return false;
  }



/*
 * clear and remove
 */
template <typename K,typename V>
void HashTable<K,V>::clear()
  {
    makeEmpty(); //for some reason the assignment had me do this, if there is a reason it is beyond me
  }

//*********************************************************************
//THIS IS WHERE I GOT ON MY REWRITES                                  *
//RESUME EDITING HERE                                                 *
//*********************************************************************
template <typename K, typename V>
bool HashTable<K,V>::remove(const K & key)
  {
    int hashIndex = myhash(key);
    typename list<pair<K,V>>::iterator pos = bucketsVector[hashIndex].begin();
    while (pos != bucketsVector[hashIndex].end())
    {
      if (key == (*pos).first) { bucketsVector[hashIndex].erase(pos); size--; return true; }
      ++pos;
    }
    return false;
  }

template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
  {
    for (int i=0; i<this->capacity; i++)
    {
      bucketsVector[i].clear();
    }
    size=0;
  }

/*
 * dump
 */
template <typename K, typename V>
void HashTable<K,V>::dump()
  {
    cout<<"Size is:"<<size<<"\nCapacity is: "<<capacity<<endl;
    for (int i=0; i<this->capacity; i++)
    {
      if (bucketsVector[i].empty()) continue;
      typename list<pair<K,V>>::iterator it = bucketsVector[i].begin();
      for (int j=0;j<bucketsVector[i].size();j++)
      {
        cout<<"Key: "<<(*it).first<<" Value: "<<(*it).second<<endl;
        ++it;
      }
    }
  }

/*
 * file interactions
 */

template <typename K, typename V>
bool HashTable<K,V>::load(const char*filename)
  {
    clear();
    ifstream infile;
    string line;
    pair<K,V> KVpair;
    infile.open(filename);
    if (!infile.is_open()) { return false; }
    while (getline(infile,line))
    {
      istringstream ss;
      ss.str(line);
      ss>>KVpair.first>>KVpair.second;
      insert(KVpair);
    }

    infile.close();
    return true;
  }

template <typename K, typename V>
bool HashTable<K,V>::write(string filename)
  {
    ofstream outfile;
    outfile.open(filename);
    if (!outfile.is_open()) { return false; }
    for (int i=0; i<this->capacity; i++)
    {
      typename list<pair<K,V>>::iterator it = bucketsVector[i].begin();
      for (int j=0;j<bucketsVector[i].size();j++)
      {
        outfile<<(*it).first<<" "<<(*it).second<<endl;
        ++it;
      }
    }
    outfile.close();
    return true;
  }






#endif