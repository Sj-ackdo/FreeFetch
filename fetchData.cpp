#include <iostream>
#include <bits/stdc++.h>
#include <string>
#include <sys/stat.h>
#include <filesystem>
#include <fstream>
#include <cstdlib>
using namespace std;

const char* tempFile = "/tmp/freefetch.tmp";    // Constant .tmp

void fetchSystem();     // Define all functions
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
            system(sfile);                      // Check if .tmp file exists and else create it
        }
    #endif
};      // Linux defined func might be ommitted by fetchSystem()

void fetchSystem(){
    #ifdef _WIN32
        //system("systeminfo");
        //verzin nog eventjes iets voor Windows implementation
    #else

	    const char* mem = "cat /proc/meminfo | grep \"MemTotal\" >> /tmp/freefetch.tmp && cat /proc/meminfo | grep \"MemFree\" >> /tmp/freefetch.tmp"; // Locate and save memory
        const char* cpu = "cat /proc/cpuinfo | grep \"model name\" >> /tmp/freefetch.tmp"; // Save all CPU cores and their info
        const char* gpu = "inxi -G | grep 'Device-1' | sed -e 's/^[ \t]*//' >> /tmp/freefetch.tmp"; // Save GPU
        const char* kernel = "uname -r >> /tmp/freefetch.tmp"; // Save Kernel name and version
        const char* hostname = "cat /etc/hostname >> /tmp/freefetch.tmp"; // Save hostname
        string commands[] = {mem, cpu, gpu, kernel, hostname};
        for (int i = 0; i < 5; i++){                            // loop through system commands
            system(commands[i].c_str());
        }
    #endif
};      // Moet ik nu uberhaupt een create directory hebben voor Linux?

void displayFetch(){
    const char* data = "cat /tmp/freefetch.tmp"; 
    imagesDistros();    //print distro image
    system(data);       //print out /tmp/freefetch.tmp
};

void distroName(){
    #ifdef _WIN32
        // Windows specific code
    #else
        const char* distro = "cat /etc/os-release | grep \"PRETTY_NAME\" | cut -d \"=\" -f2 >> /tmp/freefetch.tmp";
        system(distro);     // Find out about the distro 

    #endif
};

int main(){
    #ifdef _WIN32
        checkDir();
    	fetchSystem();
    	displayFetch();
    #else
	checkDir(); // Check if /tmp/freefetch.tmp exists (this func might be deleted)
	fetchSystem(); // Get info about system
    distroName(); // Find out about distro name
	displayFetch(); // Display previously collected data
	system("rm /tmp/freefetch.tmp"); // Delete .tmp file for next run
    
#endif
return 0;
};

void imagesDistros(){
    #ifdef _WIN32
    // Insert windows related code here 
    #else
        char* Debian = "cat /tmp/freefetch.tmp | grep 'Debian' >> /dev/null";       //define all distro's
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
    #endif
    
};