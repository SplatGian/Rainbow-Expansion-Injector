#ifndef _UTIL_H_
#define _UTIL_H_

#define ROOT                    "/"
#define APP_PATH                "/switch/nro-test/"
#define EU_OUTPUT               "/switch/nro-test/EU.zip"
#define JP_OUTPUT               "/switch/nro-test/JP.zip"
#define US_OUTPUT               "/switch/nro-test/US.zip"
#define APP_OUTPUT              "/switch/nro-test/nro-test.nro"
#define OLD_APP_PATH            "/switch/nro-test.nro"

#define YES                     10
#define NO                      20
#define ON                      1
#define OFF                     0

void copyFile(char *src, char *dest);                                   // basic copy file. Use malloc if you need dynamic mem
int parseSearch(char *phare_string, char *filter, char* new_string);    // hacky way to parse a file for a string
int download_eu_jp_us(char *url, char *output, int mode);               // download either eu,jp or us
void update_app();                                                      // update the app

#endif