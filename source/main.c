#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <switch.h>

#include "util.h"
#include "touch.h"
#include "menu.h"
#include "unzip.h"
#include "download.h"

//#define DEBUG                                              // enable for nxlink debug

int appInit()
{
    Result rc;

    if (R_FAILED(rc = socketInitializeDefault()))           // for curl / nxlink.
        printf("socketInitializeDefault() failed: 0x%x.\n\n", rc);

    #ifdef DEBUG
    if (R_FAILED(rc = nxlinkStdio()))                       // redirect all printout to console window.
        printf("nxlinkStdio() failed: 0x%x.\n\n", rc);
    #endif

    if (R_FAILED(rc = plInitialize(PlServiceType_User)))    // for shared fonts.
        printf("plInitialize() failed: 0x%x.\n\n", rc);

    if (R_FAILED(rc = romfsInit()))                         // load textures from app.
        printf("romfsInit() failed: 0x%x.\n\n", rc);

    sdlInit();                                              // int all of sdl and start loading textures.

    romfsExit();                                            // exit romfs after loading sdl as we no longer need it.

    return 0;
}

void appExit()
{
    sdlExit();
    socketExit();
    plExit();
    splExit();
    setsysExit();
}

int main(int argc, char **argv)
{
    // init stuff.
    appInit();
    mkdir(APP_PATH, 0777);
    chdir(ROOT);

    // set the cursor position to 0.
    short cursor = 0;

    // touch variables.
    int touch_lock = OFF;
    u32 tch = 0;
    HidTouchScreenState state={0};

    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    PadState pad;
    padInitializeDefault(&pad);
    u32 touch_count = hidGetTouchScreenStates(&state, 1);

    // muh loooooop
    while(appletMainLoop())
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);

        u32 touch_count = hidGetTouchScreenStates(&state, 1);

        // main menu display
        printOptionList(cursor);

        // move cursor down...
        if (kDown & HidNpadButton_Down)
        {
            if (cursor == CURSOR_LIST_MAX) cursor = 0;
            else cursor++;
        }

        // move cursor up...
        if (kDown & HidNpadButton_Up)
        {
            if (cursor == 0) cursor = CURSOR_LIST_MAX;
            else cursor--;
        }

        // select option
        if (kDown & HidNpadButton_A || (touch_lock == OFF && state.touches[0].x > 530 && state.touches[0].x < 1200 && state.touches[0].y > FIRST_LINE - HIGHLIGHT_BOX_MIN && state.touches[0].y < (NEWLINE * CURSOR_LIST_MAX) + FIRST_LINE + HIGHLIGHT_BOX_MAX))
        {
            // check if the user used touch to enter this option.
            if (touch_lock == OFF && touch_count > 0)
                cursor = touch_cursor(state.touches[0].x, state.touches[0].y);

            switch (cursor)
            {
            case DL_EU:
                if (yesNoBox(cursor, 390, 250, "Download EU mod?") == YES)
                    download_eu_jp_us(EU_URL, EU_OUTPUT, cursor);
                break;

            case DL_JP:
                if (yesNoBox(cursor, 390, 250, "Download JP mod?") == YES)
                    download_eu_jp_us(JP_URL, JP_OUTPUT, cursor);
                break;

            case DL_US:
                if (yesNoBox(cursor, 390, 250, "Download US mod?") == YES)
                    download_eu_jp_us(US_URL, US_OUTPUT, cursor);
                break;

            case UP_APP:
                if (yesNoBox(cursor, 390, 250, "Update App?") == YES)
                    update_app();
                break;
            }
        }

        // exit...
        if (kDown & HidNpadButton_Plus || (state.touches[0].x > 1145 && state.touches[0].x < SCREEN_W && state.touches[0].y > 675 && state.touches[0].y < SCREEN_H))
            break;

        // lock touch if the user has already touched the screen (touch tap).
        if (touch_count > 0) touch_lock = ON;
        else touch_lock = OFF;

        // display render buffer
        updateRenderer();
    }

    // cleanup then exit
    appExit();
    return 0;
}
