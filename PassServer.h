//
// Created by ethan on 11/8/2024.
//

#ifndef PASSSERVER_H
#define PASSSERVER_H
#include "hashtable.h"
namespace cop4530 {
    class PassServer {
        typedef vector<list<pair<string,string>>> SVLP;

    public:

        PassServer(size_t capacity);
        ~PassServer() { passServer.clear(); }
        bool load(string filename);
        bool addUser(pair<string,string> & kv);
        bool removeUser(const string & k);
        bool changePassword(const pair<string, string> &p, string &newPassword);
        bool find(const string & user);
        string decodepw(string & s);
        void dump();
        size_t size();
        bool write_to_file(string filename);
        private:

        HashTable<string,string> passServer;

        string encrypt( string & str);


    };
}


#endif //PASSSERVER_H
