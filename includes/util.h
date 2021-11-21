#ifndef _UTIL_H_
#define _UTIL_H_

#define ROOT                    "/"
#define APP_PATH                "/switch/Rainbow-Expansion-Injector/"
#define EU_OUTPUT               "/switch/Rainbow-Expansion-Injector/EU.zip"
#define JP_OUTPUT               "/switch/Rainbow-Expansion-Injector/JP.zip"
#define US_OUTPUT               "/switch/Rainbow-Expansion-Injector/US.zip"
#define APP_OUTPUT              "/switch/Rainbow-Expansion-Injector/Rainbow-Expansion-Injector.nro"
#define OLD_APP_PATH            "/switch/Rainbow-Expansion-Injector.nro"

#define YES                     10
#define NO                      20
#define ON                      1
#define OFF                     0

void copyFile(char *src, char *dest);                                   // basic copy file. Use malloc if you need dynamic mem
int parseSearch(char *phare_string, char *filter, char* new_string);    // hacky way to parse a file for a string
int download_eu_jp_us(char *url, char *output, int mode);               // download either eu,jp or us
void update_app();                                                      // update the app

#endif