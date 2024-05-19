#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <cstdlib>
using namespace std;

const char* tempFile = "/tmp/freefetch.$(whoami)";

void fetchSystem();
void checkDir();

void checkDir(){
    #ifdef _WIN32
        // Windows specific code
    #else 
	const char* sfile = "touch /tmp/freefetch.$(whoami)";

        if(!filesystem::exists(tempFile)){
            system(sfile);
        }
    #endif
};

void fetchSystem(){
    #ifdef _WIN32
        //system("systeminfo");
        //verzin nog eventjes iets voor Windows implementation
    #else

	const char* mem = "cat /proc/meminfo | grep \"MemTotal\" >> /tmp/freefetch.$(whoami) && cat /proc/meminfo | grep \"MemFree\" >> /tmp/freefetch.$(whoami)";
        const char* cpu = "cat /proc/cpuinfo | grep \"model name\" >> /tmp/freefetch.$(whoami)";
        const char* gpu = "lspci | grep -i --color 'vga\\|3d\\|2d' >> /tmp/freefetch.$(whoami)";
        const char* kernel = "uname -r >> /tmp/freefetch.$(whoami)";
        const char* hostname = "cat /etc/hostname >> /tmp/freefetch.$(whoami)";
        string commands[] = {mem, cpu, gpu, kernel, hostname};
        for (int i = 0; i < 5; i++){
            system(commands[i].c_str());
        }
    #endif
};      // Moet ik nu uberhaupt een create directory hebben voor Linux?

void displayFetch(){
    const char* data = "cat /tmp/freefetch.$(whoami)"; 
    system(data);
    };

int main(){
    #ifdef _WIN32
        checkDir();
    	fetchSystem();
    	displayFetch();
    #else
	checkDir();
	fetchSystem();
	displayFetch();
	system("rm /tmp/freefetch.$(whoami)");
#endif

return 0;
};
