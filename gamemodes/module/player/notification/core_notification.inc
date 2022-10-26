#define MAX_TDN 4
#define TDN_POS_X_INFO 4.00000
#define TDN_POS_X 494.0
#define TDN_POS_Y 120.000000
#define TDN_FONT 1
#define TDN_LETTER_SIZE_X 0.250000
#define TDN_LETTER_SIZE_Y 1.000000
#define TDN_SIZE 112.000000
#define TDN_COLOR 0xFFFFFFFF
#define TDN_COLOR_BOX 1296911871
#define TDN_PROPORTIONAL 1
#define TDN_DISTANCE 20
#define TDN_MODE_DOWN
#define TDN_TIME 5000
#define MAX_TDN_TEXT 800

#define MAX_TDN  4

#define TINGGI_BOX  1.7
#include <td-string-width>
 
enum InformationTDN
{
    Use,
    Line,
    Text[MAX_TDN_TEXT],
    PlayerText:TextDraw,
    PlayerText:textdraw_notification[12],
    Float:MinPosY,
    Float:MaxPosY,
    Hide,
    mode
}
new TextDrawsNotification[MAX_PLAYERS][MAX_TDN][InformationTDN],
    counter[MAX_PLAYERS];