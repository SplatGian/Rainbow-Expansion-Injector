#include <unistd.h>
#include <switch.h>

#include "menu.h"
#include "touch.h"
#include "util.h"

#define APP_VERSION "nro-test: 0.1.0"

void refreshScreen(char loaded)
{
    clearRenderer();

    // app version.
    drawText(fntMedium, 40, 40, SDL_GetColour(white), APP_VERSION);

    if (loaded)
    {
      //drawText(fntMedium, 120, 225, SDL_GetColour(white), "Menu Here"); // menu options
      drawButton(fntButton, BUTTON_A, 970, 672, SDL_GetColour(white));
      drawText(fntSmall, 1010, 675, SDL_GetColour(white), "Select");

      drawButton(fntButton, BUTTON_PLUS, 1145, 672, SDL_GetColour(white));
      drawText(fntSmall, 1185, 675, SDL_GetColour(white), "Exit");
    }
}

void printOptionList(int cursor)
{
    refreshScreen(/*loaded=*/1);

    char *option_list[]      = {    "Download european mod", \
                                    "Download japanese mod", \
                                    "Download american mod", \
                                    "Update app" };

    char *description_list[] = {    "Downloades the mod for european Splatoon 2", \
                                    "Downloades the mod for japanese Splatoon 2", \
                                    "Downloades the mod for american Splatoon 2", \
                                    "Update app and removes old version" };

    SDL_Texture *textureArray[] = { ams_icon, ams_plus_icon, hekate_icon, app_icon, reboot_icon };

    for (int i=0, nl=0; i < (CURSOR_LIST_MAX+1); i++, nl+=NEWLINE)
    {
        if (cursor != i) drawText(fntSmall, 550, FIRST_LINE+nl, SDL_GetColour(white), option_list[i]);
        else
        {
            // icon for the option selected.
            drawImage(textureArray[i], 125, 350);
            // highlight box.
            drawShape(SDL_GetColour(dark_blue), 530, (FIRST_LINE + nl - HIGHLIGHT_BOX_MIN), 700, HIGHLIGHT_BOX_MAX);
            // option text.
            drawText(fntSmall, 550, FIRST_LINE+nl, SDL_GetColour(jordy_blue), option_list[i]);
            // description.
            drawText(fntSmall, 25, 675, SDL_GetColour(white), description_list[i]);
        }
    }
}

void popUpBox(TTF_Font *font, int x, int y, SDL_Colour colour, char *text)
{
    // outline. box
    drawShape(SDL_GetColour(black), (SCREEN_W/4)-5, (SCREEN_H/4)-5, (SCREEN_W/2)+10, (SCREEN_H/2)+10);
    // popup box.
    drawShape(SDL_GetColour(dark_blue), SCREEN_W/4, SCREEN_H/4, SCREEN_W/2, SCREEN_H/2);
    // text to draw.
    drawText(font, x, y, colour, text);
}

int yesNoBox(int mode, int x, int y, char *question)
{
    printOptionList(mode);
    popUpBox(fntMedium, x, y, SDL_GetColour(white), question);
    // highlight box.
    drawShape(SDL_GetColour(faint_blue), 380, 410, 175, 65);
    drawShape(SDL_GetColour(faint_blue), 700, 410, 190, 65);
    // option text.
    drawButton(fntButtonBig, BUTTON_B, 410, 425, SDL_GetColour(white));
    drawText(fntMedium, 455, 425, SDL_GetColour(white), "No");
    drawButton(fntButtonBig, BUTTON_A, 725, 425, SDL_GetColour(white));
    drawText(fntMedium, 770, 425, SDL_GetColour(white), "Yes");

    updateRenderer();

    int res = 0;
    int touch_lock = OFF;
    // touchPosition touch;
    // u32 tch = 0;
    HidTouchScreenState state={0};

    u32 touch_count = hidGetTouchScreenStates(&state, 1);

    // check if the user is already touching the screen.
    if (touch_count > 0) touch_lock = ON;

    PadState pad;
    padInitializeDefault(&pad);

    while (1)
    {
        padUpdate(&pad);
        u64 kDown = padGetButtonsDown(&pad);
        touch_count = hidGetTouchScreenStates(&state, 1);

        if (touch_count == 0) touch_lock = OFF;

        if (touch_count > 0 && touch_lock == OFF)
            res = touch_yes_no_option(state.touches[0].x, state.touches[0].y);

        if (kDown & HidNpadButton_A || res == YES)
            return YES;

        if (kDown & HidNpadButton_B || res == NO)
            return NO;
    }
}

void errorBox(int x, int y, char *errorText)
{
    popUpBox(fntMedium, x, y, SDL_GetColour(white), errorText);
    drawImageScale(error_icon, 570, 340, 128, 128);
    updateRenderer();

    sleep(3);
}