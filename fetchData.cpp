#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <cstdlib>
using namespace std;

const char* tempFile = "/tmp/freefetch.tmp";

void fetchSystem();
void checkDir();
void displayfetch();
void imagesDistros();
void distroName();

void checkDir(){
    #ifdef _WIN32
        // Windows specific code
    #else 
	const char* sfile = "touch /tmp/freefetch.tmp";

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

	const char* mem = "cat /proc/meminfo | grep \"MemTotal\" >> /tmp/freefetch.tmp && cat /proc/meminfo | grep \"MemFree\" >> /tmp/freefetch.tmp";
        const char* cpu = "cat /proc/cpuinfo | grep \"model name\" >> /tmp/freefetch.tmp";
        const char* gpu = "inxi -G | grep 'Device-1' | sed -e 's/^[ \t]*//' >> /tmp/freefetch.tmp";
        const char* kernel = "uname -r >> /tmp/freefetch.tmp";
        const char* hostname = "cat /etc/hostname >> /tmp/freefetch.tmp";
        string commands[] = {mem, cpu, gpu, kernel, hostname};
        for (int i = 0; i < 5; i++){
            system(commands[i].c_str());
        }
    #endif
};      // Moet ik nu uberhaupt een create directory hebben voor Linux?

void displayFetch(){
    const char* data = "cat /tmp/freefetch.tmp"; 
    imagesDistros();
    system(data);
};

void distroName(){
    #ifdef _WIN32
        // Windows specific code
    #else
        const char* distro = "cat /etc/os-release | grep \"PRETTY_NAME\" | cut -d \"=\" -f2 >> /tmp/freefetch.tmp";
        system(distro);

    #endif
};

int main(){
    #ifdef _WIN32
        checkDir();
    	fetchSystem();
    	displayFetch();
    #else
	checkDir();
	fetchSystem();
    	distroName();
	displayFetch();
	system("rm /tmp/freefetch.tmp");
    
#endif
return 0;
};

void imagesDistros(){
    char* Debian = "cat /tmp/freefetch.tmp | grep 'Debian' >> /dev/null";
    char* Arch = "cat /tmp/freefetch.tmp | grep 'Arch' >> /dev/null";
    char* Ubuntu = "cat /tmp/freefetch.tmp | grep 'Ubuntu' >> /dev/null";

    if (system("cat /tmp/freefetch.tmp | grep 'Debian' >> /dev/null") == 0) {
        cout << "Debian" << endl;
    } 
    else if (system("cat /tmp/freefetch.tmp | grep 'Arch' >> /dev/null") == 0) {
        char* archLinux =   "                         -`                        \n"
                            "                        .o+`                       \n"
                            "                        ooo/                       \n"
                            "                      +oooo:                       \n"
                            "                      +oooooo:                     \n"
                            "                    -+oooooo+:                     \n"
                            "                    /:-:++oooo+:                   \n"
                            "                  /++++/+++++++:                   \n"
                            "                  /++++++++++++++:                 \n"
                            "                /+++ooooooooooooo/`                \n"
                            "               ./ooosssso++osssssso+`              \n"
                            "             .oossssso-````/ossssss+`              \n"
                            "             -osssssso.      :ssssssso.            \n"
                            "           :osssssss/        osssso+++.            \n"
                            "           /ossssssss/        +ssssooo/-           \n"
                            "         /ossssso+/:-        -:/+osssso+-          \n"
                            "         +sso+:-`                 `.-/+oso:        \n"
                            "       ++:.                           `-/+/        \n"
                            "       .`                                 `/\"      \n";
        cout << archLinux << endl;
    } 
};
