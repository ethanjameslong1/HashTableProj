#ifndef _BASE64_H_
#define _BASE64_H_

#include <vector>
#include <string>
typedef unsigned char BYTE;
using namespace std; 
std::string base64_encode(BYTE const* buf, unsigned int bufLen);
std::string encode(string & s);
std::vector<BYTE> base64_decode(std::string const&);
std::string  decode(std::string  & );
#endif
