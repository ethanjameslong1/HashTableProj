#include <iostream>
#include <list>
#include "hashtable.hpp"
#include "base64.h"
#include <string>
#include "PassServer.h"

const int MAXCHARSIZE=256;

using namespace std;
using namespace cop4530;
void PrintMenu();

int main() {
    cout<<"Testing GitHub Interaction.\n";

    PassServer PWS(19);
    PrintMenu();
    char choice;
    cin>>choice;
    while (choice != 'x') {
        string Str;
        pair<string,string> StrP;
        switch (choice)
        {
            case 'l': cout<<"Enter FileName: ";
            cin>>Str;
           while (!PWS.load(Str) && Str != "quit")
            {
                cout<<"error reading file, please re-enter or type 'quit'\n";
               cin>>Str;
            }
            break;
            case 'a': cout<<"Enter Username: "; cin>>Str;
            StrP.first = Str;
            cout<<"\nEnter Password: "; cin>>Str;
            StrP.second = Str;
            PWS.addUser(StrP);
            break;

            case 'd': PWS.dump();

            break;
            case 'r': cout<<"enter username: "; cin>>Str; PWS.removeUser(Str);
            break;
            case 'c': cout<<"enter Username: "; cin>>Str;
            StrP.first = Str;
            cout<<"\nEnter Old Password: "; cin>>Str;
            StrP.second = Str;
            cout<<"\nEnter new Password: "; cin>>Str;
            PWS.changePassword(StrP,Str);
            break;
            case 'f': cout<<"enter Username: "; cin>>Str;
            if (PWS.find(Str))
                cout<<"\nUser Found!";
            else
                cout<<"\nUser Not Found!";
            break;
            case 'p': cout<<"Enter Username: "; cin>>Str;
            cout<<"\nPassWord: "<<PWS.decodepw(Str)<<endl; break;
            case 's': cout<<"Size: "<<PWS.size()<<endl; break;
            case 'w':
                cout<<"Enter FileName: ";
            cin>>Str;
            while (!PWS.write_to_file(Str) && Str != "quit")
            {
                cout<<"error reading file, please re-enter or type 'quit'\n";
                cin>>Str;
            }
            break;
            default: cout<<"Invalid Input\n";


        }
        PrintMenu();
        cin>>choice;
    }

    return 0;
}

void PrintMenu()
{

    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "p - Display Decoded Password"<<endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}