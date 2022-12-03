ShowNavigationPhone(playerid, status)
{
    if(status)
    {
        PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][navigasi]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][batrai_0]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][batrai_1]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][provider]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][ptime]);
    }
    else{
        PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][navigasi]);
		PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][batrai_0]);
		PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][batrai_1]);
		PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][provider]);
		PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][ptime]);
    }
    return 1;
}

stock ShowPhoneApp(playerid, status)
{
    if(status)
    {
        forex(txd, 27)
        {
            PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][myapplication][txd]);
        }
    }
    else 
    {
        forex(txd, 27)
        {
            PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][myapplication][txd]);
        }
    }
    return 1;
}

stock ShowHomePagePhone(playerid, status)
{
    if(status)
    {
        ShowNavigationPhone(playerid, true);
        ShowPhoneApp(playerid, true);
        PhonePage[playerid] = PHONE_HOMESCREEN;
    }
    else{
        ShowNavigationPhone(playerid, false);
        ShowPhoneApp(playerid, false);
    }
    return 1;
}

stock ShowPhoneLockscreen(playerid, status)
{
    if(status)
    {
        forex(txd, 5)
        {
            PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][lockscreen][txd]);
        }
    }
    else{
        forex(txd, 5)
        {
            PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][lockscreen][txd]);
        }
    }
    return 1;
}

stock ShowPlayerPhone(playerid, status)
{
    if(status)
    {
        forex(txd, 11)
        {
            TextDrawShowForPlayer(playerid, PhoneTextdraw[playerid][main_phone][txd]);
        }
        TextDrawShowForPlayer(playerid, PhoneTextdraw[playerid][layar]);
        isOnPhone[playerid] = true;
    }
    else{
        forex(txd, 11)
        {
            TextDrawHideForPlayer(playerid, PhoneTextdraw[playerid][main_phone][txd]);
        }
        TextDrawHideForPlayer(playerid, PhoneTextdraw[playerid][layar]);

        ShowNavigationPhone(playerid, false);
        ShowPhoneLockscreen(playerid, false);
        // if(PhonePage[playerid] == PHONE_HOMESCREEN) ShowHomePagePhone(playerid, false);
        // if(PhonePage[playerid == PHONE_MBANKING]) ShowMobileBanking(playerid, false);
        // if(PhonePage[playerid] == PHONE_DJEK) ShowPhoneDjek(playerid, false);

        ShowHomePagePhone(playerid, false);
        ShowMobileBanking(playerid, false);
        ShowPhoneDjek(playerid, false);
        
        isOnPhone[playerid] = false;
        PhonePage[playerid] = PHONE_OFF;
    }
    return 1;
}

stock ShowMobileBanking(playerid, status)
{
    if(status)
    {
        PhonePage[playerid] = PHONE_MBANKING;
        ShowNavigationPhone(playerid, true);

        PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][0]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][1]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][2]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][3]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][4]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][5]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][6]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][7]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][8]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][9]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][10]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][11]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][12]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][13]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][14]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][15]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][16]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][17]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][18]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][19]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][20]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][21]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][22]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][23]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][24]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][25]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][26]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][27]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][28]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][29]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][30]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][mbanking][31]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][bank_ammount]);
		PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][bank_id]);

    } else {
        forex(txd, 32)
        {
            PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][mbanking][txd]);
        }
        PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][bank_ammount]);
        PlayerTextDrawHide(playerid, PhoneTextdraw[playerid][bank_id]);
    }
    return 1;
}

stock ShowPhoneDjek(playerid, status)
{
    if(status)
    {
        ShowNavigationPhone(playerid, true);
        PhonePage[playerid] = PHONE_DJEK;
        
        PhoneTextdraw[playerid][djek][0] = CreatePlayerTextDraw(playerid, 537.000000, 236.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][0], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][0], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][0], 80.000000, 160.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][0], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][0], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][0], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][0], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][0], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][0], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][0], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][0], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][0], 0);

        PhoneTextdraw[playerid][djek][1] = CreatePlayerTextDraw(playerid, 541.000000, 252.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][1], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][1], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][1], 71.000000, 21.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][1], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][1], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][1], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][1], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][1], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][1], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][1], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][1], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][1], 0);

        PhoneTextdraw[playerid][djek][2] = CreatePlayerTextDraw(playerid, 538.000000, 245.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][2], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][2], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][2], 17.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][2], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][2], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][2], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][2], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][2], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][2], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][2], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][2], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][2], 0);

        PhoneTextdraw[playerid][djek][3] = CreatePlayerTextDraw(playerid, 598.000000, 245.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][3], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][3], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][3], 17.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][3], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][3], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][3], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][3], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][3], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][3], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][3], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][3], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][3], 0);

        PhoneTextdraw[playerid][djek][4] = CreatePlayerTextDraw(playerid, 598.000000, 264.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][4], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][4], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][4], 17.000000, 18.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][4], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][4], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][4], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][4], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][4], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][4], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][4], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][4], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][4], 0);

        PhoneTextdraw[playerid][djek][5] = CreatePlayerTextDraw(playerid, 538.000000, 265.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][5], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][5], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][5], 17.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][5], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][5], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][5], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][5], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][5], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][5], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][5], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][5], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][5], 0);

        PhoneTextdraw[playerid][djek][6] = CreatePlayerTextDraw(playerid, 545.000000, 248.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][6], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][6], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][6], 62.000000, 31.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][6], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][6], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][6], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][6], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][6], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][6], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][6], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][6], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][6], 0);

        PhoneTextdraw[playerid][djek][7] = CreatePlayerTextDraw(playerid, 545.000000, 254.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][7], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][7], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][7], 31.000000, 19.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][7], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][7], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][7], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][7], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][7], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][7], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][7], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][7], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][7], 0);

        PhoneTextdraw[playerid][djek][8] = CreatePlayerTextDraw(playerid, 543.000000, 250.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][8], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][8], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][8], 11.500000, 12.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][8], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][8], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][8], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][8], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][8], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][8], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][8], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][8], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][8], 0);

        PhoneTextdraw[playerid][djek][9] = CreatePlayerTextDraw(playerid, 543.000000, 266.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][9], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][9], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][9], 11.500000, 12.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][9], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][9], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][9], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][9], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][9], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][9], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][9], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][9], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][9], 0);

        PhoneTextdraw[playerid][djek][10] = CreatePlayerTextDraw(playerid, 567.000000, 250.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][10], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][10], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][10], 11.000000, 12.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][10], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][10], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][10], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][10], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][10], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][10], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][10], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][10], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][10], 0);

        PhoneTextdraw[playerid][djek][11] = CreatePlayerTextDraw(playerid, 567.000000, 266.000000, "ld_beat:chit");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][11], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][11], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][11], 11.000000, 12.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][11], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][11], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][11], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][11], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][11], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][11], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][11], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][11], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][11], 0);

        PhoneTextdraw[playerid][djek][12] = CreatePlayerTextDraw(playerid, 547.000000, 252.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][12], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][12], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][12], 25.000000, 24.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][12], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][12], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][12], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][12], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][12], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][12], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][12], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][12], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][12], 0);

        PhoneTextdraw[playerid][djek][13] = CreatePlayerTextDraw(playerid, 548.000000, 253.000000, "Djek");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][13], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][13], 0.154165, 0.750000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][13], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][13], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][13], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][13], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][13], 255);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][13], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][13], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][13], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][13], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][13], 0);

        PhoneTextdraw[playerid][djek][14] = CreatePlayerTextDraw(playerid, 548.000000, 261.000000, "$5000");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][14], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][14], 0.141665, 0.699999);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][14], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][14], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][14], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][14], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][14], 255);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][14], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][14], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][14], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][14], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][14], 0);

        PhoneTextdraw[playerid][djek][15] = CreatePlayerTextDraw(playerid, 573.000000, 269.000000, "Tap for history");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][15], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][15], 0.100000, 0.500000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][15], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][15], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][15], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][15], 3);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][15], 9109759);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][15], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][15], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][15], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][15], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][15], 0);

        PhoneTextdraw[playerid][djek][16] = CreatePlayerTextDraw(playerid, 580.000000, 259.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][16], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][16], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][16], 8.500000, 8.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][16], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][16], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][16], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][16], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][16], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][16], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][16], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][16], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][16], 1);

        PhoneTextdraw[playerid][djek][17] = CreatePlayerTextDraw(playerid, 598.000000, 257.000000, "+");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][17], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][17], 0.308333, 1.250000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][17], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][17], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][17], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][17], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][17], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][17], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][17], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][17], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][17], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][17], 0);

        PhoneTextdraw[playerid][djek][18] = CreatePlayerTextDraw(playerid, 607.000000, 269.000000, "Top_Up");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][18], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][18], 0.104166, 0.699999);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][18], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][18], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][18], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][18], 3);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][18], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][18], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][18], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][18], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][18], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][18], 0);

        PhoneTextdraw[playerid][djek][19] = CreatePlayerTextDraw(playerid, 597.000000, 259.000000, "ld_dual:white");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][19], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][19], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][19], 8.500000, 8.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][19], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][19], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][19], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][19], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][19], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][19], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][19], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][19], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][19], 1);

        PhoneTextdraw[playerid][djek][20] = CreatePlayerTextDraw(playerid, 587.000000, 269.000000, "Pay");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][20], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][20], 0.104166, 0.699999);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][20], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][20], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][20], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][20], 3);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][20], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][20], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][20], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][20], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][20], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][20], 0);

        PhoneTextdraw[playerid][djek][21] = CreatePlayerTextDraw(playerid, 582.000000, 259.000000, "}");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][21], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][21], 0.200000, 0.850000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][21], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][21], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][21], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][21], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][21], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][21], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][21], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][21], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][21], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][21], 0);

        PhoneTextdraw[playerid][djek][22] = CreatePlayerTextDraw(playerid, 542.000000, 288.000000, "ld_dual:white"); // KLIK GOJEK
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][22], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][22], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][22], 69.500000, 22.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][22], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][22], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][22], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][22], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][22], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][22], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][22], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][22], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][22], 1);

        PhoneTextdraw[playerid][djek][23] = CreatePlayerTextDraw(playerid, 545.000000, 294.000000, "HUD:radar_airyard");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][23], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][23], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][23], 11.000000, 11.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][23], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][23], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][23], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][23], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][23], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][23], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][23], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][23], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][23], 0);

        PhoneTextdraw[playerid][djek][24] = CreatePlayerTextDraw(playerid, 569.000000, 295.000000, "DJEK");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][24], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][24], 0.200000, 0.850000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][24], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][24], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][24], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][24], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][24], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][24], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][24], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][24], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][24], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][24], 0);

        PhoneTextdraw[playerid][djek][25] = CreatePlayerTextDraw(playerid, 542.000000, 316.000000, "ld_dual:white"); // KLIK GOCAR
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][25], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][25], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][25], 69.500000, 22.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][25], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][25], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][25], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][25], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][25], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][25], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][25], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][25], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][25], 1);

        PhoneTextdraw[playerid][djek][26] = CreatePlayerTextDraw(playerid, 545.000000, 322.000000, "HUD:radar_impound");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][26], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][26], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][26], 11.000000, 11.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][26], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][26], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][26], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][26], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][26], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][26], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][26], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][26], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][26], 0);

        PhoneTextdraw[playerid][djek][27] = CreatePlayerTextDraw(playerid, 569.000000, 324.000000, "DCAR");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][27], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][27], 0.200000, 0.850000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][27], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][27], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][27], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][27], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][27], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][27], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][27], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][27], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][27], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][27], 0);

        PhoneTextdraw[playerid][djek][28] = CreatePlayerTextDraw(playerid, 542.000000, 344.000000, "ld_dual:white"); // KLIK GOFOOD
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][28], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][28], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][28], 69.500000, 22.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][28], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][28], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][28], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][28], 1687547391);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][28], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][28], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][28], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][28], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][28], 1);

        PhoneTextdraw[playerid][djek][29] = CreatePlayerTextDraw(playerid, 545.000000, 349.000000, "HUD:radar_pizza");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][29], 4);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][29], 0.600000, 2.000000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][29], 11.000000, 11.500000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][29], 1);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][29], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][29], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][29], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][29], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][29], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][29], 1);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][29], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][29], 0);

        PhoneTextdraw[playerid][djek][30] = CreatePlayerTextDraw(playerid, 569.000000, 351.000000, "DFOOD");
        PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][djek][30], 1);
        PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][djek][30], 0.200000, 0.850000);
        PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][djek][30], 400.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][djek][30], 0);
        PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][djek][30], 0);
        PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][djek][30], 1);
        PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][djek][30], -1);
        PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][djek][30], 255);
        PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][djek][30], 50);
        PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][djek][30], 0);
        PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][djek][30], 1);
        PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][djek][30], 0);

        forex(txd, 31)
        {
            PlayerTextDrawShow(playerid, PhoneTextdraw[playerid][djek][txd]);
        }
    } else {
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][0]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][1]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][2]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][3]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][4]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][5]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][6]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][7]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][8]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][9]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][10]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][11]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][12]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][13]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][14]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][15]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][16]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][17]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][18]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][19]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][20]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][21]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][22]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][23]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][24]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][25]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][26]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][27]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][28]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][29]);
        PlayerTextDrawDestroy(playerid, PhoneTextdraw[playerid][djek][30]);
    }
    return 1;
}

task PhoneUpdate[1000]() 
{
    foreach (new i : Player)
    {
        new hour, minute;
		gettime(hour, minute);

        if(PhonePage[i] == PHONE_HOMESCREEN)
        {
            PlayerTextDrawSetString(i, PhoneTextdraw[i][lockscreen][0], sprintf("%02d:%02d", hour, minute));
        }
    }   
}