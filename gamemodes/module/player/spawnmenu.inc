#include <YSI\y_hooks>   

new Text:SpawnTextdraw[MAX_PLAYERS][10];


stock ShowSpawnTextdraw(playerid)
{
    SpawnTextdraw[playerid][0] = TextDrawCreate(76.000000, 119.000000, "_");
    TextDrawFont(SpawnTextdraw[playerid][0], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][0], 0.850000, 2.250004);
    TextDrawTextSize(SpawnTextdraw[playerid][0], 298.500000, 106.500000);
    TextDrawSetOutline(SpawnTextdraw[playerid][0], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][0], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][0], 2);
    TextDrawColor(SpawnTextdraw[playerid][0], 1687547391);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][0], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][0], 1687547391);
    TextDrawUseBox(SpawnTextdraw[playerid][0], 1);
    TextDrawSetProportional(SpawnTextdraw[playerid][0], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][0], 0);

    SpawnTextdraw[playerid][1] = TextDrawCreate(48.000000, 124.000000, "Spawn Selection");
    TextDrawFont(SpawnTextdraw[playerid][1], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][1], 0.208333, 0.950000);
    TextDrawTextSize(SpawnTextdraw[playerid][1], 400.000000, 17.000000);
    TextDrawSetOutline(SpawnTextdraw[playerid][1], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][1], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][1], 1);
    TextDrawColor(SpawnTextdraw[playerid][1], -1);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][1], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][1], 50);
    TextDrawUseBox(SpawnTextdraw[playerid][1], 0);
    TextDrawSetProportional(SpawnTextdraw[playerid][1], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][1], 0);

    SpawnTextdraw[playerid][2] = TextDrawCreate(76.000000, 146.000000, "_");
    TextDrawFont(SpawnTextdraw[playerid][2], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][2], 0.850000, 2.250004);
    TextDrawTextSize(SpawnTextdraw[playerid][2], 298.500000, 106.500000);
    TextDrawSetOutline(SpawnTextdraw[playerid][2], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][2], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][2], 2);
    TextDrawColor(SpawnTextdraw[playerid][2], 1296911871);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][2], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][2], 1296911871);
    TextDrawUseBox(SpawnTextdraw[playerid][2], 1);
    TextDrawSetProportional(SpawnTextdraw[playerid][2], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][2], 0);

    SpawnTextdraw[playerid][3] = TextDrawCreate(76.000000, 173.000000, "_");
    TextDrawFont(SpawnTextdraw[playerid][3], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][3], 0.850000, 2.250004);
    TextDrawTextSize(SpawnTextdraw[playerid][3], 298.500000, 106.500000);
    TextDrawSetOutline(SpawnTextdraw[playerid][3], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][3], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][3], 2);
    TextDrawColor(SpawnTextdraw[playerid][3], 1296911871);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][3], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][3], 1296911871);
    TextDrawUseBox(SpawnTextdraw[playerid][3], 1);
    TextDrawSetProportional(SpawnTextdraw[playerid][3], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][3], 0);

    SpawnTextdraw[playerid][4] = TextDrawCreate(76.000000, 201.000000, "_");
    TextDrawFont(SpawnTextdraw[playerid][4], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][4], 0.850000, 2.250004);
    TextDrawTextSize(SpawnTextdraw[playerid][4], 298.500000, 106.500000);
    TextDrawSetOutline(SpawnTextdraw[playerid][4], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][4], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][4], 2);
    TextDrawColor(SpawnTextdraw[playerid][4], 1296911871);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][4], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][4], 1296911871);
    TextDrawUseBox(SpawnTextdraw[playerid][4], 1);
    TextDrawSetProportional(SpawnTextdraw[playerid][4], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][4], 0);

    SpawnTextdraw[playerid][5] = TextDrawCreate(116.000000, 151.000000, "Bandara_International");
    TextDrawFont(SpawnTextdraw[playerid][5], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][5], 0.208333, 0.950000);
    TextDrawTextSize(SpawnTextdraw[playerid][5], 400.000000, 17.000000);
    TextDrawSetOutline(SpawnTextdraw[playerid][5], 0);
    TextDrawSetShadow(SpawnTextdraw[playerid][5], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][5], 3);
    TextDrawColor(SpawnTextdraw[playerid][5], -1);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][5], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][5], 50);
    TextDrawUseBox(SpawnTextdraw[playerid][5], 0);
    TextDrawSetProportional(SpawnTextdraw[playerid][5], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][5], 1);

    SpawnTextdraw[playerid][6] = TextDrawCreate(118.000000, 179.000000, "Pelabuhan_Ocean_Dock");
    TextDrawFont(SpawnTextdraw[playerid][6], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][6], 0.208333, 0.950000);
    TextDrawTextSize(SpawnTextdraw[playerid][6], 400.000000, 17.000000);
    TextDrawSetOutline(SpawnTextdraw[playerid][6], 0);
    TextDrawSetShadow(SpawnTextdraw[playerid][6], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][6], 3);
    TextDrawColor(SpawnTextdraw[playerid][6], -1);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][6], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][6], 50);
    TextDrawUseBox(SpawnTextdraw[playerid][6], 0);
    TextDrawSetProportional(SpawnTextdraw[playerid][6], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][6], 1);

    SpawnTextdraw[playerid][7] = TextDrawCreate(102.000000, 206.000000, "Posisi_Terakhir");
    TextDrawFont(SpawnTextdraw[playerid][7], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][7], 0.208333, 0.950000);
    TextDrawTextSize(SpawnTextdraw[playerid][7], 400.000000, 17.000000);
    TextDrawSetOutline(SpawnTextdraw[playerid][7], 0);
    TextDrawSetShadow(SpawnTextdraw[playerid][7], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][7], 3);
    TextDrawColor(SpawnTextdraw[playerid][7], -1);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][7], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][7], 50);
    TextDrawUseBox(SpawnTextdraw[playerid][7], 0);
    TextDrawSetProportional(SpawnTextdraw[playerid][7], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][7], 1);

    SpawnTextdraw[playerid][8] = TextDrawCreate(76.000000, 230.000000, "_");
    TextDrawFont(SpawnTextdraw[playerid][8], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][8], 0.850000, 2.250004);
    TextDrawTextSize(SpawnTextdraw[playerid][8], 298.500000, 106.500000);
    TextDrawSetOutline(SpawnTextdraw[playerid][8], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][8], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][8], 2);
    TextDrawColor(SpawnTextdraw[playerid][8], 1687547391);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][8], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][8], 1687547391);
    TextDrawUseBox(SpawnTextdraw[playerid][8], 1);
    TextDrawSetProportional(SpawnTextdraw[playerid][8], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][8], 0);

    SpawnTextdraw[playerid][9] = TextDrawCreate(64.000000, 236.000000, "Spawn");
    TextDrawFont(SpawnTextdraw[playerid][9], 1);
    TextDrawLetterSize(SpawnTextdraw[playerid][9], 0.208333, 0.950000);
    TextDrawTextSize(SpawnTextdraw[playerid][9], 400.000000, 17.000000);
    TextDrawSetOutline(SpawnTextdraw[playerid][9], 1);
    TextDrawSetShadow(SpawnTextdraw[playerid][9], 0);
    TextDrawAlignment(SpawnTextdraw[playerid][9], 1);
    TextDrawColor(SpawnTextdraw[playerid][9], -1);
    TextDrawBackgroundColor(SpawnTextdraw[playerid][9], 255);
    TextDrawBoxColor(SpawnTextdraw[playerid][9], 50);
    TextDrawUseBox(SpawnTextdraw[playerid][9], 0);
    TextDrawSetProportional(SpawnTextdraw[playerid][9], 1);
    TextDrawSetSelectable(SpawnTextdraw[playerid][9], 1);

    SelectTextDraw(playerid, X11_LIGHTBLUE);
    forex(txd, 10)
    {
        TextDrawShowForPlayer(playerid, SpawnTextdraw[playerid][txd]);
    }
}

stock HideSpawnTextdraw(playerid)
{
    CancelSelectTextDraw(playerid);
    forex(txd, 10)
    {
        TextDrawDestroy(SpawnTextdraw[playerid][txd]);
        SpawnTextdraw[playerid][txd] = Text:-1;
    }
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(SpawnTextdraw[playerid][0] != Text:-1)
    {
        if(clickedid == SpawnTextdraw[playerid][5])
        {
            SellLastSpawn[playerid] = 0;
            PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
            InterpolateCameraPos(playerid, 1501.421386, -2186.599121, 70.820335, 1560.730102, -2478.765380, 102.223358, 7200, 1);
            InterpolateCameraLookAt(playerid, 1504.833618, -2188.617919, 70.290901, 1562.733032, -2475.431640, 101.288337, 7200, 1);
            SetSpawnInfo(playerid, 255, PlayerData[playerid][pSkin], 1682.8376,-2241.0151,13.5469, 178.1388, 0, 0, 0, 0, 0, 0);
            SendTextDrawMessageEx(playerid, NOTIFICATION_MESSAGE, "Lokasi spawn di tetapkan ke bandara international");
        }
        if(clickedid == SpawnTextdraw[playerid][6])
        {
            SellLastSpawn[playerid] = 0;
            PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
            InterpolateCameraPos(playerid, 2361.360595, -2239.473144, 70.822807, 2180.477539, -2383.681884, 109.199714, 7200, 1);
            InterpolateCameraLookAt(playerid, 2360.333496, -2243.171630, 69.697578, 2184.110351, -2383.914550, 107.541893, 7200, 1);
            SetSpawnInfo(playerid, 255, PlayerData[playerid][pSkin], 2299.2490,-2393.2683,13.5469,50.1184, 0, 0, 0, 0, 0, 0);
            SendTextDrawMessageEx(playerid, NOTIFICATION_MESSAGE, "Lokasi spawn di tetapkan ke pelabuhan ocean dock");

        }
        if(clickedid == SpawnTextdraw[playerid][7])
        {
            PlayerPlaySound(playerid, 1138, 0.0, 0.0, 0.0);
            SellLastSpawn[playerid] = 1;
            SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Lokasi spawn di tetapkan ke posisi terakhir keluar kota");
            SetSpawnInfo(playerid, 255, PlayerData[playerid][pSkin], PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2], 0, 0, 0, 0, 0, 0, 0);
        }
        if(clickedid == SpawnTextdraw[playerid][9])
        {
            if(SellLastSpawn[playerid] == -1) return SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Pilih salah satu tempat spawn!!");
            if(!IsPlayerConnected2(playerid)) return SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Data belum dimuat!");
            SpawnPlayer(playerid);
            HideSpawnTextdraw(playerid);
        }
    }
    return 1;
}