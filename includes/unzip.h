#ifndef _UNZIP_H_
#define _UNZIP_H_

#define DL_EU           0
#define DL_JP           1
#define DL_US           2
#define DL_WIP_EU       3
#define DL_WIP_JP       4
#define DL_WIP_US       5
#define UP_APP          6

int unzip(const char *output, int mode);

#endif