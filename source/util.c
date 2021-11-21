#include <stdio.h>
#include <string.h>
#include <switch.h>

#include "util.h"
#include "menu.h"
#include "unzip.h"
#include "download.h"

#define TEMP_FILE                 "/switch/nro-test/temp"
#define FILTER_STRING             "browser_download_url\":\""
#define VERSION_FILTER_STRING     "tag_name\":\""

void copyFile(char *src, char *dest)
{
    FILE *srcfile = fopen(src, "rb");
    FILE *newfile = fopen(dest, "wb");

    if (srcfile && newfile)
    {
        char buffer[10000]; // 10kb per write, which is fast
        size_t bytes;       // size of the file to write (10kb or filesize max)

        while (0 < (bytes = fread(buffer, 1, sizeof(buffer), srcfile)))
        {
            fwrite(buffer, 1, bytes, newfile);
        }
    }
    fclose(srcfile);
    fclose(newfile);
}

int parseSearch(char *parse_string, char *filter, char* new_string)
{
    FILE *fp = fopen(parse_string, "r");

    if (fp)
    {
        char c;
        while ((c = fgetc(fp)) != EOF)
        {
            if (c == *filter)
            {
                for (int i = 0, len = strlen(filter) - 1; c == filter[i]; i++)
                {
                    c = fgetc(fp);
                    if (i == len)
                    {
                        for (int j = 0; c != '\"'; j++)
                        {
                            new_string[j] = c;
                            new_string[j+1] = '\0';
                            c = fgetc(fp);
                        }
                        fclose(fp);
                        remove(parse_string);
                        return 0;
                    }
                }
            }
        }
    }

    errorBox(350, 250, "Failed to find parse url!");
    fclose(fp);
    return 1;
}

int download_eu_jp_us(char *url, char *output, int mode)
{
    if (!downloadFile(url, TEMP_FILE, ON))
    {
        char new_url[MAX_STRLEN];
        if (!parseSearch(TEMP_FILE, FILTER_STRING, new_url))
        {
            if (!downloadFile(new_url, output, OFF))
            {
                unzip(output, mode);
                return 0;
            }
            return 1;
        }
        return 1;
    }
    return 1;
}

void update_app()
{
    // download new nro as a tempfile.
    if (!downloadFile(APP_URL, TEMP_FILE, OFF))
    {
        // remove current nro file.
        remove(APP_OUTPUT);
        // remove nro from /switch/.
        remove(OLD_APP_PATH);
        // rename the downloaded temp_file with the correct nro name.
        rename(TEMP_FILE, APP_OUTPUT);
        // using errorBox as a message window on this occasion.
        errorBox(400, 250, "      Update complete!\nRestart app to take effect");
    }
}
