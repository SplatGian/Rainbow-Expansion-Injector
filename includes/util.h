#ifndef _UTIL_H_
#define _UTIL_H_

#define ROOT                    "/"
#define APP_PATH                "/switch/rainbow-expansion-installer/"
#define EU_OUTPUT              "/switch/rainbow-expansion-installer/EU.zip"
#define JP_OUTPUT              "/switch/rainbow-expansion-installer/JP.zip"
#define US_OUTPUT              "/switch/rainbow-expansion-installer/US.zip"
#define WIPEU_OUTPUT              "/switch/rainbow-expansion-installer/WIP/EU.zip"
#define WIPJP_OUTPUT              "/switch/rainbow-expansion-installer/WIP/JP.zip"
#define WIPUS_OUTPUT              "/switch/rainbow-expansion-installer/WIP/US.zip"
#define APP_OUTPUT              "/switch/rainbow-expansion-installer/rainbow-expansion-installer.nro"
#define OLD_APP_PATH            "/switch/rainbow-expansion-installer.nro"

#define YES                     10
#define NO                      20
#define ON                      1
#define OFF                     0

void copyFile(char *src, char *dest);                                   // basic copy file. Use malloc if you need dynamic mem
int parseSearch(char *phare_string, char *filter, char* new_string);    // hacky way to parse a file for a string
int download_mod(char *url, char *output, int mode);                    // download the mod
void update_app();                                                      // update the app

#endif