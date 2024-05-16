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
        const char* dir = "/home/$(whoami)/.config/freefetch";
        const char* file = "/home/$(whoami)/.config/freefetch/fetch.data";
        struct stat info;
        struct stat info2;
        if(stat(dir, &info) != 0){
            const char* mkdir = "mkdir ~/.config/freefetch";
            system(mkdir);
            if(stat(file, &info2) != 0){
                const char* touch = "touch ~/.config/freefetch/fetch.data";
                system(touch);
                }
            }
        if(stat(dir, &info) == 0 && stat(file, &info2) != 0){
            const char* touch = "touch ~/.config/freefetch/fetch.data";
            system(touch);
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
        const char* mem = "cat /proc/meminfo | grep \"MemTotal\" >> ~/.config/freefetch/fetch.data && cat /proc/meminfo | grep \"MemFree\" >> ~/.config/freefetch/fetch.data";
        const char* cpu = "cat /proc/cpuinfo | grep \"model name\" >> ~/.config/freefetch/fetch.data";
        const char* gpu = "lspci | grep -i --color 'vga\\|3d\\|2d' >> ~/.config/freefetch/fetch.data";
        const char* kernel = "uname -r >> ~/.config/freefetch/fetch.data";
        const char* hostname = "cat /etc/hostname >> ~/.config/freefetch/fetch.data";
        string commands[] = {mem, cpu, gpu, kernel, hostname};
        for (int i = 0; i < 5; i++){
            system(commands[i].c_str());
        }
    #endif
        return;
};

int main(){
    //checkDir();
    fetchSystem();
    return 0;
};