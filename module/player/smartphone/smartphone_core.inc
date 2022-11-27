enum PHONE_TEXTDRAW
{
    Text:main_phone[11],
    Text:layar,
    PlayerText:lockscreen[5],
    PlayerText:navigasi,
    PlayerText:batrai_0,
    PlayerText:batrai_1,
    PlayerText:provider,
    PlayerText:ptime,
    PlayerText:myapplication[27],
    PlayerText:mbanking[32],
    PlayerText:bank_ammount,
    PlayerText:bank_id,
    PlayerText:djek[31]
}
 
#define PHONE_OFF          0
#define PHONE_LOCKSCREEN   1
#define PHONE_HOMESCREEN   2
#define PHONE_MBANKING     3
#define PHONE_DJEK         4

#define PHONE_COLOR       255

new PhoneTextdraw[MAX_PLAYERS][PHONE_TEXTDRAW];

new bool:isOnPhone[MAX_PLAYERS];
new PhonePage[MAX_PLAYERS];