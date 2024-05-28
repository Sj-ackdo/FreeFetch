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
        const char* cpu = "lscpu | grep 'Model name' >> /tmp/freefetch.tmp"; // Save all CPU cores and their info
        const char* gpu = "lspci | grep 'VGA' >> /tmp/freefetch.tmp"; // Save GPU  | sed -e 's/^[ \t]*//' 
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
        char* Windows = "cat /tmp/freefetch.tmp | grep 'Windows' >> /dev/null";
        if(system(Windows) == 0) {
            char* windowsLogo = "  _____ _                 _     _            _    _ \n"
                                " / ____| |               | |   | |          | |  | |\n"
                                "| |    | | ___  _   _  __| | __| | ___ _ __ | |__| |\n"
                                "| |    | |/ _ \\| | | |/ _` |/ _` |/ _ \\ '_ \\|  __  |\n"
                                "| |____| | (_) | |_| | (_| | (_| |  __/ | | | |  | |\n"
                                " \\_____|_|\\___/ \\__,_|\\__,_|\\__,_|\\___|_| |_|_|  |_|\n";
            cout << windowsLogo << endl;
        }

        if (system(Debian) == 0) {
            char* debianLogo = "\n"
                                "        _,met$$$$$gg.                  \n"
                                "        ,g$$$$$$$$$$$$$$$P.            \n"
                                "    ,g$$P"        """Y$$.\".            \n"
                                "    ,$$P'              `$$$.           \n"
                                "    ',$$P       ,ggs.     `$$b:        \n"
                                "    `d$$'     ,$P\"'   .    $$$         \n"
                                "    $$P      d$'     ,    $$P          \n"
                                "    $$:      $$.   -    ,d$$'          \n"
                                "    $$;      Y$b._   _,d$P'            \n"
                                "    Y$$.    `.`\"Y$$$$P\"'            \n"
                                "    `$$b      \"-.__                    \n"
                                "    `Y$$                               \n"
                                "    `Y$$.                              \n"
                                "        `$$b.                          \n"
                                "        `Y$$b.                         \n"
                                "            `\"Y$b._                    \n"
                                "                `\"\"\"\"\";           \n";
                                            
            
            cout << debianLogo << endl;
        } 
        else if (system(Arch) == 0) {
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