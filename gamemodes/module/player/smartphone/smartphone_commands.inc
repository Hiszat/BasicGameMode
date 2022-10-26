CMD:phonetd(playerid, params[])
{
    if(isOnPhone[playerid]) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu sudah membuka handphone");

    PhonePage[playerid] = PHONE_LOCKSCREEN;
    ShowPhoneLockscreen(playerid, true);
    SelectTextDraw(playerid, X11_RED);
    ShowPlayerPhone(playerid, true);
    return 1;
}

CMD:hidephone(playerid, params[])
{
    CancelSelectTextDraw(playerid);
    ShowPlayerPhone(playerid, false);
    return 1;
}