#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_

#define EU_URL      "https://github.com/SplatGian/Rainbow-Expansion/releases/latest/download/EU.zip"
#define JP_URL      "https://github.com/SplatGian/Rainbow-Expansion/releases/latest/download/JP.zip"
#define US_URL      "https://github.com/SplatGian/Rainbow-Expansion/releases/latest/download/US.zip"
#define APP_URL     ""

int downloadFile(const char *url, const char *output, int api_mode);

#endif