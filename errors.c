#include "main.h"

void err_first(int err)
{
    if (err == -2)
        printf("%s\n%s\n", ERROR, RES_ERROR);
    else if (err == -3)
        printf("%s\n%s\n", ERROR, TEXT_ERROR);
    else if (err == -4)
        printf("%s\n%s\n", ERROR, F_C_ERROR);
    else if (err == -5)
        printf("%s\n%s\n", ERROR, ODD_ERROR);
    else if (err == -6)
        printf("%s\n%s\n", ERROR, MISS_ERROR);
    else if (err == -7)
        printf("%s\n%s\n", ERROR, RES_SIZE_ERROR);
    else if (err == -8)
        printf("%s\n%s\n", ERROR, COLOR_ERROR);
    else if (err == -9)
        printf("%s\n%s\n", ERROR, PLAYER_ERROR);
    else if (err == -10)
        printf("%s\n%s\n", ERROR, MAP_ERROR);
}

void err_second(int err)
{
    if (err == -11)
        printf("%s\n%s\n", ERROR, XPM_WALL_ERROR);
    else if (err == -12)
        printf("%s\n%s\n", ERROR, XPM_SPRITE_ERROR);
    else if (err == -13)
        printf("%s\n%s\n", ERROR, WRONG_TEXTURES);
    else if (err == -14)
        printf("%s\n%s\n", ERROR, WRONG_SPRITE);
    else if (err == -15)
        printf("%s\n%s\n", ERROR, IMAGE_ERROR);
    else if (err == -16)
        printf("%s\n%s\n", ERROR, WINDOW_ERROR);
    else if (err == -17)
        printf("%s\n%s\n", ERROR, FD_ERROR);
    else if (err == -100)
        printf("%s\n%s\n", ERROR, MALLOC_ERROR);
}
