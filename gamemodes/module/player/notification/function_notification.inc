forward TimerHideTDN(playerid);
public TimerHideTDN(playerid)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][Hide] == -1)
        {
            TextDrawsNotification[playerid][cycle][Use] = 0;
            if(TextDrawsNotification[playerid][cycle][TextDraw] != PlayerText:-1)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][TextDraw]);
                TextDrawsNotification[playerid][cycle][Line] = 0;
                TextDrawsNotification[playerid][cycle][Text][0] = EOS;
                TextDrawsNotification[playerid][cycle][MinPosY] = 0;
                TextDrawsNotification[playerid][cycle][MaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][TextDraw] = PlayerText:-1;
                forex(txd, 12)
                {
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                }
            }
            TextDrawsNotification[playerid][cycle][Hide] = -1;
            UpdateTDN(playerid);

            return 1;
        }
    }
    return 0;
}

Function:ShowTDN(playerid, type, const reason[])
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(!TextDrawsNotification[playerid][cycle][Use])
        {
            TextDrawsNotification[playerid][cycle][Text][0] = EOS;

            new text[MAX_TDN_TEXT];

            for(new len = strlen(reason), pos; pos < len; pos ++)
            {
                switch(reason[pos])
                {
                    // case ' ': text[pos] = '_';
                    case '`': text[pos] = 177;
                    case '&': text[pos] = 38;
                    default:  text[pos] = reason[pos];
                }
            }
            
            strcat(TextDrawsNotification[playerid][cycle][Text], text, MAX_TDN_TEXT);
            TextDrawsNotification[playerid][cycle][mode] = type;
 
            TextDrawsNotification[playerid][cycle][Use] = 1;
 
            LinesTDN(playerid, cycle);

            #if defined TDN_MODE_DOWN

            MinPosYTDN(playerid, cycle);
            MaxPosYTDN(playerid, cycle);

            #endif

            #if defined TDN_MODE_UP

            MaxPosYTDN(playerid, cycle);
            MinPosYTDN(playerid, cycle);
            
            #endif

            TextDrawsNotification[playerid][cycle][Hide] = -1;

            CreateTDN(playerid, type, cycle);

            SetTimerEx("TimerHideTDN", TDN_TIME, false, "i", playerid);

            return 1;
        }
    }
    return -1;
}

Function:ShowTDN_Manual(playerid, type, const reason[])
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(!TextDrawsNotification[playerid][cycle][Use])
        {
            TextDrawsNotification[playerid][cycle][Text][0] = EOS;

            new text[MAX_TDN_TEXT];

            for(new len = strlen(reason), pos; pos < len; pos ++)
            {
                switch(reason[pos])
                {
                    default:  text[pos] = reason[pos];
                }
            }

            strcat(TextDrawsNotification[playerid][cycle][Text], text, MAX_TDN_TEXT);
            TextDrawsNotification[playerid][cycle][mode] = type;
 
            TextDrawsNotification[playerid][cycle][Use] = 1;
 
            LinesTDN(playerid, cycle);

            #if defined TDN_MODE_DOWN

            MinPosYTDN(playerid, cycle);
            MaxPosYTDN(playerid, cycle);

            #endif

            #if defined TDN_MODE_UP

            MaxPosYTDN(playerid, cycle);
            MinPosYTDN(playerid, cycle);
            
            #endif

            CreateTDN(playerid, type, cycle);

            for(new i; i < MAX_TDN; i++)
            {
                if(used(playerid, counter[playerid]))
                {
                    if(counter[playerid] == MAX_TDN - 1) counter[playerid] = 0;
                    else counter[playerid]++;
                }
                else break;
            }

            new TDN = counter[playerid];

            TextDrawsNotification[playerid][cycle][Hide] = TDN;

            if(counter[playerid] == MAX_TDN - 1) counter[playerid] = 0;
            else counter[playerid]++;

            return TDN;
        }
    }
    return -1;
}

stock used(playerid, id)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][Hide] == id) return 1;
    }
    return 0;
}

forward hideTDN(playerid, TDN);
public hideTDN(playerid, TDN)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        if(TextDrawsNotification[playerid][cycle][Hide] == TDN)
        {
            TextDrawsNotification[playerid][cycle][Use] = 0;
            if(TextDrawsNotification[playerid][cycle][TextDraw] != PlayerText:-1)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][TextDraw]);
                TextDrawsNotification[playerid][cycle][Line] = 0;
                TextDrawsNotification[playerid][cycle][Text][0] = EOS;
                TextDrawsNotification[playerid][cycle][MinPosY] = 0;
                TextDrawsNotification[playerid][cycle][MaxPosY] = 0;
                TextDrawsNotification[playerid][cycle][TextDraw] = PlayerText:-1;
                forex(txd, 12)
                {
                    PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][cycle][textdraw_notification][txd]);
                    TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                }
            }
            TextDrawsNotification[playerid][cycle][Hide] = -1;
            UpdateTDN(playerid);
            return 1;
        }
    }
    return 0;
}

stock UpdateTDN(playerid)
{
    for(new cycle = 0; cycle < MAX_TDN; cycle ++)
    {
        if(!TextDrawsNotification[playerid][cycle][Use])
        {
            if(cycle != MAX_TDN - 1)
            {
                if(TextDrawsNotification[playerid][cycle + 1][Use])
                {
                    TextDrawsNotification[playerid][cycle][Use] = TextDrawsNotification[playerid][cycle + 1][Use];
                    TextDrawsNotification[playerid][cycle][Line] = TextDrawsNotification[playerid][cycle + 1][Line];
                    strcat(TextDrawsNotification[playerid][cycle][Text], TextDrawsNotification[playerid][cycle + 1][Text], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle][mode] = TextDrawsNotification[playerid][cycle + 1][mode];
                    TextDrawsNotification[playerid][cycle][TextDraw] = TextDrawsNotification[playerid][cycle + 1][TextDraw];
                    TextDrawsNotification[playerid][cycle][Hide] = TextDrawsNotification[playerid][cycle + 1][Hide];

                    TextDrawsNotification[playerid][cycle + 1][Use] = 0;
                    TextDrawsNotification[playerid][cycle + 1][Line] = 0;
                    TextDrawsNotification[playerid][cycle + 1][Text][0] = EOS;
                    TextDrawsNotification[playerid][cycle + 1][TextDraw] = PlayerText:-1;
                    TextDrawsNotification[playerid][cycle + 1][MinPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][MaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle + 1][Hide] = -1;
                    TextDrawsNotification[playerid][cycle + 1][mode] = -1;
                    TextDrawsNotification[playerid][cycle + 1][mode] = -1;

                    forex(txd, 12)
                    {
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd];
                        TextDrawsNotification[playerid][cycle + 1][textdraw_notification][txd] = PlayerText:-1;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle);
                    MaxPosYTDN(playerid, cycle);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle);
                    MinPosYTDN(playerid, cycle);
                    
                    #endif       
                }
            }
        }
        else if(TextDrawsNotification[playerid][cycle][Use])
        {
            if(cycle != 0)
            {
                if(!TextDrawsNotification[playerid][cycle - 1][Use])
                {
                    TextDrawsNotification[playerid][cycle - 1][Use] = TextDrawsNotification[playerid][cycle][Use];
                    TextDrawsNotification[playerid][cycle - 1][Line] = TextDrawsNotification[playerid][cycle][Line];
                    strcat(TextDrawsNotification[playerid][cycle - 1][Text], TextDrawsNotification[playerid][cycle][Text], MAX_TDN_TEXT);
                    TextDrawsNotification[playerid][cycle - 1][mode] = TextDrawsNotification[playerid][cycle][mode];
                    TextDrawsNotification[playerid][cycle - 1][TextDraw] = TextDrawsNotification[playerid][cycle][TextDraw];
                    TextDrawsNotification[playerid][cycle - 1][Hide] = TextDrawsNotification[playerid][cycle][Hide];

                    TextDrawsNotification[playerid][cycle][Use] = 0;
                    TextDrawsNotification[playerid][cycle][Line] = 0;
                    TextDrawsNotification[playerid][cycle][Text][0] = EOS;
                    TextDrawsNotification[playerid][cycle][mode] = -1;
                    TextDrawsNotification[playerid][cycle][TextDraw] = PlayerText:-1;
                    TextDrawsNotification[playerid][cycle][MinPosY] = 0;
                    TextDrawsNotification[playerid][cycle][MaxPosY] = 0;
                    TextDrawsNotification[playerid][cycle][Hide] = -1;

                    forex(txd, 12)
                    {
                        TextDrawsNotification[playerid][cycle - 1][textdraw_notification][txd] = TextDrawsNotification[playerid][cycle][textdraw_notification][txd];
                        TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
                    }

                    #if defined TDN_MODE_DOWN

                    MinPosYTDN(playerid, cycle - 1);
                    MaxPosYTDN(playerid, cycle - 1);
                    
                    #endif

                    #if defined TDN_MODE_UP
                    
                    MaxPosYTDN(playerid, cycle - 1);
                    MinPosYTDN(playerid, cycle - 1);
                    
                    #endif
                }
            }
        }
        CreateTDN(playerid, TextDrawsNotification[playerid][cycle][mode], cycle);
    }
    return 1;
}

stock MinPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][MinPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][MinPosY] = TextDrawsNotification[playerid][TDN - 1][MaxPosY] + TDN_DISTANCE;
    }
    return 1;

    #endif

    #if defined TDN_MODE_UP

    TextDrawsNotification[playerid][TDN][MinPosY] = TextDrawsNotification[playerid][TDN][MaxPosY] - ((TDN_LETTER_SIZE_Y * 2) + 2) - ((TDN_LETTER_SIZE_Y * 5.75) * TINGGI_BOX) - ((TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) - (TDN_LETTER_SIZE_Y + 3);
    return 1;

    #endif
}

stock MaxPosYTDN(playerid, TDN)
{
    #if defined TDN_MODE_DOWN

    TextDrawsNotification[playerid][TDN][MaxPosY] = TextDrawsNotification[playerid][TDN][MinPosY] + (TDN_LETTER_SIZE_Y * 2) + 2 + (TDN_LETTER_SIZE_Y * 5.75 * TINGGI_BOX) + ((TINGGI_BOX - 1) * ((TDN_LETTER_SIZE_Y * 2) + 2 + TDN_LETTER_SIZE_Y)) + TDN_LETTER_SIZE_Y + 3;
    return 1;

    #endif

    #if defined TDN_MODE_UP

    if(TDN == 0)
    {
        TextDrawsNotification[playerid][TDN][MaxPosY] = TDN_POS_Y;
    }
    else
    {
        TextDrawsNotification[playerid][TDN][MaxPosY] = TextDrawsNotification[playerid][TDN - 1][MinPosY] - TDN_DISTANCE;
    }
    return 1;

    #endif
}

stock LinesTDN(playerid, TDN)
{
    new lines = 1, Float:width, lastspace = -1, supr, len = strlen(TextDrawsNotification[playerid][TDN][Text]);
 
    for(new i = 0; i < len; i ++)
    {
        if(TextDrawsNotification[playerid][TDN][Text][i] == '~')
        {
            if(supr == 0)
            {
                supr = 1;
                if(TextDrawsNotification[playerid][TDN][Text][i+2] != '~') SendClientMessage(playerid, -1, "Error: '~' used incorrectly'");
            }
            else if(supr == 1) supr = 0;
        }
        else
        {
            if(supr == 1)
            {
                if(TextDrawsNotification[playerid][TDN][Text][i] == 'n')
                {
                    lines ++;
                    lastspace = -1;
                    width = 0;
                }
            }
            else
            {
                if(TextDrawsNotification[playerid][TDN][Text][i] == ' ') lastspace = i;
 
                width += TDN_LETTER_SIZE_X * GetTextDrawCharacterWidth(TextDrawsNotification[playerid][TDN][Text][i], TDN_FONT, bool:TDN_PROPORTIONAL);

                if(width > TDN_SIZE - 3)
                {
                    if(lastspace != i && lastspace != -1)
                    {
                        lines ++;
                        i = lastspace;
                        lastspace = -1;
                        width = 0;
                    }
                    else
                    {
                        lines ++;
                        lastspace = -1;
                        width = 0;
                    }
                }
            }
        }
    }
    
    TextDrawsNotification[playerid][TDN][Line] = lines;
 
    return 1;
}

stock CreateTDN(playerid, type = NOTIFICATION_INFO, TDN)
{
    if(TextDrawsNotification[playerid][TDN][Use] == 1)
    {
        TextDrawsNotification[playerid][TDN][mode] = type;
        if(TextDrawsNotification[playerid][TDN][TextDraw] != PlayerText:-1)
        {
            PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][TextDraw]);
            forex(txd, 12)
            {
                PlayerTextDrawDestroy(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
            }
        }
        if(type == NOTIFICATION_INFO)
        {
            TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 112.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 134.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 111.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 17.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 132.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 16.500000, 16.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 500.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 105.000000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 96.500000, 21.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 114.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 96.500000, 22.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 594.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 10.500000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 504.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 121.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 14.000000, 15.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1687547391);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 520.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 118.000000), "INFORMASI");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0.195831, 0.800000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -1);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 510.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "i");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0.274996, 0.949998);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 508.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 123.000000), "_");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0.183329, 0.849999);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
        }
        else if(type == NOTIFICATION_ERROR)
        {
            TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 112.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], -16776961);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 134.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], -16776961);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 111.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 17.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 132.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 16.500000, 16.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 500.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 105.000000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], -16776961);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 96.500000, 21.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 114.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 96.500000, 22.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 594.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 10.500000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 504.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 121.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 14.000000, 15.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], -16776961);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1687547391);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 520.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 118.000000), "KESALAHAN");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0.195831, 0.800000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -1);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 508.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "X");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0.274996, 0.949998);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 508.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 123.000000), "_");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0.183329, 0.849999);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
        }
        else{

            TextDrawsNotification[playerid][TDN][textdraw_notification][0] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 112.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][0], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][1] = CreatePlayerTextDraw(playerid, 499.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 134.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 7.500000, 13.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][1], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][2] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 111.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 17.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][2], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][3] = CreatePlayerTextDraw(playerid, 591.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 132.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 16.500000, 16.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][3], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][4] = CreatePlayerTextDraw(playerid, 500.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 105.000000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][4], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][5] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 96.500000, 21.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][5], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][6] = CreatePlayerTextDraw(playerid, 503.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 114.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 96.500000, 22.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][6], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][7] = CreatePlayerTextDraw(playerid, 594.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 119.000000), "ld_dual:white");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 10.500000, 20.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1296911871);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][7], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][8] = CreatePlayerTextDraw(playerid, 504.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 121.000000), "ld_beat:chit");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 4);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0.600000, 2.000000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 14.000000, 15.500000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1687547391);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1687547391);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][8], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][9] = CreatePlayerTextDraw(playerid, 520.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 118.000000), "INFORMASI");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0.195831, 0.800000);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], -1);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][9], 0);

            TextDrawsNotification[playerid][TDN][textdraw_notification][10] = CreatePlayerTextDraw(playerid, 510.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 124.000000), "i");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0.274996, 0.949998);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][10], 0);
            
            TextDrawsNotification[playerid][TDN][textdraw_notification][11] = CreatePlayerTextDraw(playerid, 508.000000, TextDrawsNotification[playerid][TDN][MinPosY] - (127.000000 - 123.000000), "_");
            PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0.183329, 0.849999);
            PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 400.000000, 17.000000);
            PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 255);
            PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 50);
            PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
            PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 1);
            PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][11], 0);
        }

        // PATOKAN NYA ADALAH NILAI Y TEXTDRAW TEXTNYA DI KURANG Y

        // SplitTest("CLIENT: You are connected to the game using a mobile device");

        TextDrawsNotification[playerid][TDN][TextDraw] = CreatePlayerTextDraw(playerid, 520.000000, TextDrawsNotification[playerid][TDN][MinPosY], TextDrawsNotification[playerid][TDN][Text]);
        PlayerTextDrawFont(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 1);
        PlayerTextDrawLetterSize(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 0.162496, 0.699998);
        PlayerTextDrawTextSize(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 596.000000, 17.000000);
        PlayerTextDrawSetOutline(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 0);
        PlayerTextDrawSetShadow(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 0);
        PlayerTextDrawAlignment(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 1);
        PlayerTextDrawColor(playerid, TextDrawsNotification[playerid][TDN][TextDraw], -1);
        PlayerTextDrawBackgroundColor(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 255);
        PlayerTextDrawBoxColor(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 50);
        PlayerTextDrawUseBox(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 0);
        PlayerTextDrawSetProportional(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 1);
        PlayerTextDrawSetSelectable(playerid, TextDrawsNotification[playerid][TDN][TextDraw], 0);

        forex(txd, 12)
        {
            PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][textdraw_notification][txd]);
        }
        PlayerTextDrawShow(playerid, TextDrawsNotification[playerid][TDN][TextDraw]);
    }
    return 1;
}

public OnGameModeInit()
{
    for(new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        for(new TDN = 0; TDN < MAX_TDN; TDN++)
        {
            TextDrawsNotification[playerid][TDN][TextDraw] = PlayerText:-1;
            TextDrawsNotification[playerid][TDN][Hide] = -1;

            forex(txd, 12)
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][txd] = PlayerText:-1;
            }
        }
    }
    #if defined TDN_OnGameModeInit
		return TDN_OnGameModeInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnGameModeInit
	#undef OnGameModeInit
#else
	#define _ALS_OnGameModeInit
#endif

#define OnGameModeInit TDN_OnGameModeInit
#if defined TDN_OnGameModeInit
	forward TDN_OnGameModeInit();
#endif

 
public OnFilterScriptInit()
{
    for(new playerid = 0; playerid < MAX_PLAYERS; playerid++)
    {
        for(new TDN = 0; TDN < MAX_TDN; TDN++)
        {
            TextDrawsNotification[playerid][TDN][TextDraw] = PlayerText:-1;
            TextDrawsNotification[playerid][TDN][Hide] = -1;
            forex(txd, 12)
            {
                TextDrawsNotification[playerid][TDN][textdraw_notification][txd] = PlayerText:-1;
            }
        }
    }
    #if defined TDN_OnFilterScriptInit
		return TDN_OnFilterScriptInit();
	#else
		return 1;
	#endif
}
#if defined _ALS_OnFilterScriptInit
	#undef OnFilterScriptInit
#else
	#define _ALS_OnFilterScriptInit
#endif

#define OnFilterScriptInit TDN_OnFilterScriptInit
#if defined TDN_OnFilterScriptInit
	forward TDN_OnFilterScriptInit();
#endif

public OnPlayerDisconnect(playerid, reason)
{
    for(new cycle; cycle < MAX_TDN; cycle++)
    {
        TextDrawsNotification[playerid][cycle][Use] = 0;
        TextDrawsNotification[playerid][cycle][Line] = 0;
        TextDrawsNotification[playerid][cycle][Text][0] = EOS;
        TextDrawsNotification[playerid][cycle][MinPosY] = 0;
        TextDrawsNotification[playerid][cycle][MaxPosY] = 0;
        TextDrawsNotification[playerid][cycle][Hide] = -1;
        TextDrawsNotification[playerid][cycle][TextDraw] = PlayerText:-1;
        forex(txd, 12)
        {
            TextDrawsNotification[playerid][cycle][textdraw_notification][txd] = PlayerText:-1;
        }
    }
    #if defined TDN_OnPlayerDisconnect
		return TDN_OnPlayerDisconnect(playerid, reason);
	#else
		return 1;
	#endif
}
#if defined _ALS_OnPlayerDisconnect
	#undef OnPlayerDisconnect
#else
	#define _ALS_OnPlayerDisconnect
#endif

#define OnPlayerDisconnect TDN_OnPlayerDisconnect
#if defined TDN_OnPlayerDisconnect
	forward TDN_OnPlayerDisconnect(playerid, reason);
#endif