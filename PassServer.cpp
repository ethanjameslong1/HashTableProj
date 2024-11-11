//
// Created by ethan on 11/8/2024.
//

#include "PassServer.h"
#include "hashtable.h"

#include "hashtable.hpp"
#include "base64.h"

using namespace cop4530;
using namespace std;

PassServer::PassServer(size_t capacity) {
    passServer = HashTable<string,string>(capacity);
}


bool PassServer::addUser(pair<string,string> & kv)
{
    kv.second = encrypt(kv.second);
    return passServer.insert(kv);
}


string PassServer::encrypt( string & str)
{
    return encode(str);
}

bool PassServer::removeUser(const string & k)
{
    return passServer.remove(k);

}

bool PassServer::find(const string & user)
{
    return passServer.contains(user);
}

void PassServer::dump()
{
    passServer.dump();
}

size_t PassServer::size()
{
    return passServer.size;
}

string PassServer::decodepw(string & s)
{
    string str;
    str = passServer.getpassword(s);
    return decode(str);
}

bool PassServer::write_to_file(string filename)
{
    return passServer.write(filename);
}

bool PassServer::load(string filename)
{
    passServer.clear();
    ifstream infile;
    string line;
    pair<string,string> StrPair;
    infile.open(filename);
    if (!infile.is_open()) { return false; }
    while (getline(infile,line))
    {
        istringstream ss;
        ss.str(line);
        ss>>StrPair.first;
        string temp;
        ss>>temp;
        StrPair.second = encode(temp);
        passServer.insert(StrPair);
    }

    infile.close();
    return true;
}

bool PassServer::changePassword(const pair<string, string> &p, string &newPassword)
{
    string temp = p.second;
    temp = encrypt(temp);
    pair<string,string> StrPair;
    StrPair.first = p.first;
    StrPair.second = temp;
    if (passServer.match(StrPair)) {
        removeUser(p.first);
        StrPair.second = newPassword;
        addUser(StrPair);
        return true;
    }
    else {cout<<"No User Found"; return false;}
}

