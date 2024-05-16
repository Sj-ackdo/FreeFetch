#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sys/stat.h>

using namespace std;

void fetchSystem();
void checkDir();

void checkDir(){
    #ifdef _WIN32
        //const char* Wdir = "C:/Users/apples";
        //verzin nog eventjes iets later
    #else 
        const char* Udir = "~/.config/freefetch";
        const char* Ufile = "~/.config/freefetch/fetch.data";
        struct stat sb;

        if(stat(Ufile, &sb) == 0 && !(sb.st_mode & S_IFDIR)){
            cout << "hoi";
        }
        else{
            cout << "hoi";
        }
    #endif
        return;
};

void fetchSystem(){
    #ifdef _WIN32
        //system("systeminfo");
        //verzin nog eventjes iets voor Windows implementation
    #else
        //system("mkdir ~/.config/freefetch && touch ~/.config/freefetch/fetch.data");
        system("uname -r >> ~/.config/freefetch/fetch.data");                              //kernel naam & build
        system("cat /etc/hostname >> ~/.config/freefetch/fetch.data");                     //Hostname
        system("cat /proc/meminfo >> ~/.config/freefetch/fetch.data");         //memoryinfo
    #endif
        return;
};

int main(){
    //fetchSystem();
    checkDir();
    return 0;
};