#ifndef _DOWNLOAD_H_
#define _DOWNLOAD_H_

#define EU_URL     "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/latest/download/EU.zip"
#define JP_URL     "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/latest/download/JP.zip"
#define US_URL     "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/latest/download/US.zip"
#define EUWIP_URL  "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/tag/wip/download/EU.zip"
#define JPWIP_URL  "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/tag/wip/download/JP.zip"
#define USWIP_URL  "https://api.github.com/repos/SplatGian/Rainbow-Expansion-Download/releases/tag/wip/download/US.zip"
#define APP_URL     "https://github.com/AntoSkate/rainbow-expansion-installer/releases/latest/download/rainbow-expansion-installer.nro"

int downloadFile(const char *url, const char *output, int api_mode);

#endif