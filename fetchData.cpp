#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <cstdlib>

using namespace std;

void fetchSystem();
void checkDir();

void checkDir(){
    #ifdef _WIN32
        // Windows specific code
    #else 
        const char* sdir = "/home/$(whoami)/.config/freefetch";
        const char* file = "/home/$(whoami)/.config/freefetch/fetch.data";
        const char* sfile = "touch /home/$(whoami)/.config/freefetch/fetch.data";
        string home = std::getenv("HOME");
        filesystem::path dir = home + "/.config/freefetch";

        if(!filesystem::exists(dir)){
            filesystem::create_directories(dir);
        }

        if(!filesystem::exists(file)){
            system(sfile);
        }
    #endif
};

void fetchSystem(){
    #ifdef _WIN32
        //system("systeminfo");
        //verzin nog eventjes iets voor Windows implementation
    #else
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
};      // Moet ik dit veranderen naar een /tmp/ bestand? Of een tijdelijke variabele?

void displayFetch(){
    const char* data = "cat /home/$(whoami)/.config/freefetch/fetch.data"; 
    system(data);
    };

int main(){
    checkDir();
    fetchSystem();
    displayFetch();
    return 0;
};