stock ShowPassport_1(playerid)
{
    SelectTextDraw(playerid, X11_LIGHTBLUE);

    PassportTD_1[playerid][0] = CreatePlayerTextDraw(playerid, 312.000000, 45.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][0], 0.600000, 32.999980);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][0], 298.500000, 189.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][0], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][0], 246);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][0], 0);

    PassportTD_1[playerid][1] = CreatePlayerTextDraw(playerid, 312.000000, 45.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][1], 0.600000, 32.999980);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][1], 298.500000, 189.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][1], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][1], 9109541);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][1], 0);

    PassportTD_1[playerid][2] = CreatePlayerTextDraw(playerid, 318.000000, 75.000000, "Los Santos");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][2], 0.404166, 1.899999);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][2], 1);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][2], -2686801);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][2], 0);

    PassportTD_1[playerid][3] = CreatePlayerTextDraw(playerid, 338.000000, 94.000000, "Passport");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][3], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][3], 0.216664, 1.000000);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][3], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][3], 1);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][3], -126);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][3], 0);

    PassportTD_1[playerid][4] = CreatePlayerTextDraw(playerid, 255.000000, 204.000000, "Klik menu di bawah");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][4], 0.316666, 1.149999);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][4], 545.000000, 245.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][4], 1);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][4], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][4], 0);

    PassportTD_1[playerid][5] = CreatePlayerTextDraw(playerid, 232.000000, 192.000000, "Untuk melakukan Pendaftaran");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][5], 0.316666, 1.149999);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][5], 545.000000, 245.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][5], 1);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][5], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][5], 0);

    PassportTD_1[playerid][6] = CreatePlayerTextDraw(playerid, 309.000000, 223.000000, "Submit");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][6], 0.166666, 1.700000);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][6], 16.500000, 27.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][6], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][6], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][6], 200);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][6], 1);

    PassportTD_1[playerid][7] = CreatePlayerTextDraw(playerid, 390.000000, 316.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][7], 0.570833, 1.649996);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][7], 239.500000, 18.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][7], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][7], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][7], 0);

    PassportTD_1[playerid][8] = CreatePlayerTextDraw(playerid, 390.000000, 317.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][8], 0.570833, 1.349997);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][8], 239.500000, 14.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][8], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][8], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][8], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][8], -764862721);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][8], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][8], 0);

    PassportTD_1[playerid][9] = CreatePlayerTextDraw(playerid, 382.000000, 326.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][9], 0.570833, -0.400002);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][9], 239.500000, 0.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][9], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][9], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][9], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][9], 255);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][9], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][9], 0);

    PassportTD_1[playerid][10] = CreatePlayerTextDraw(playerid, 390.000000, 331.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][10], 0.570833, -0.450002);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][10], 236.000000, 6.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][10], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][10], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][10], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][10], 255);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][10], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][10], 0);

    PassportTD_1[playerid][11] = CreatePlayerTextDraw(playerid, 390.000000, 321.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][11], 0.570833, -0.450002);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][11], 236.000000, 6.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][11], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][11], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][11], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][11], 255);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][11], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][11], 0);

    PassportTD_1[playerid][12] = CreatePlayerTextDraw(playerid, 397.000000, 326.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][12], 0.570833, -0.400002);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][12], 239.500000, 0.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][12], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][12], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][12], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][12], 255);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][12], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][12], 0);

    PassportTD_1[playerid][13] = CreatePlayerTextDraw(playerid, 384.000000, 323.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][13], 0.570833, 0.349999);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][13], 298.500000, -7.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][13], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][13], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][13], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][13], 0);

    PassportTD_1[playerid][14] = CreatePlayerTextDraw(playerid, 396.000000, 323.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_1[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_1[playerid][14], 0.570833, 0.349999);
    PlayerTextDrawTextSize(playerid, PassportTD_1[playerid][14], 298.500000, -7.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_1[playerid][14], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_1[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_1[playerid][14], 2);
    PlayerTextDrawColor(playerid, PassportTD_1[playerid][14], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_1[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_1[playerid][14], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_1[playerid][14], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_1[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_1[playerid][14], 0);

    forex(txd, 15)
    {
        PlayerTextDrawShow(playerid, PassportTD_1[playerid][txd]);
    }
    return 1;
}

stock DestoryPassport_1(playerid)
{
    forex(txd, 15)
    {
        PlayerTextDrawDestroy(playerid, PassportTD_1[playerid][txd]);
        PassportTD_1[playerid][txd] = PlayerText:-1;
    }
    return 1;
}

stock ShowPassport_2(playerid)
{
    DestoryPassport_1(playerid);

    PassportTD_2[playerid][0] = CreatePlayerTextDraw(playerid, 321.000000, 5.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][0], 0.600000, 36.550014);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][0], 298.500000, 224.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][0], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][0], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][0], 254);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][0], 0);

    PassportTD_2[playerid][1] = CreatePlayerTextDraw(playerid, 321.000000, 8.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][1], 0.600000, 35.800025);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][1], 298.500000, 219.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][1], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][1], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][1], -64);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][1], 0);

    PassportTD_2[playerid][2] = CreatePlayerTextDraw(playerid, 320.000000, 154.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][2], 0.600000, -0.400000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][2], 298.500000, 221.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][2], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][2], 1);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][2], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][2], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][2], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][2], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][2], 0);

    PassportTD_2[playerid][3] = CreatePlayerTextDraw(playerid, 223.000000, 15.000000, "Silahkan isi formulir untuk melakukan pendaftaran");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][3], 0.220832, 1.000000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][3], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][3], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][3], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][3], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][3], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][3], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][3], 0);

    PassportTD_2[playerid][4] = CreatePlayerTextDraw(playerid, 223.000000, 23.000000, "Di bawah ini");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][4], 0.237498, 0.899999);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][4], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][4], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][4], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][4], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][4], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][4], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][4], 0);

    PassportTD_2[playerid][5] = CreatePlayerTextDraw(playerid, 229.000000, 34.000000, ".");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][5], 0.158333, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][5], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][5], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][5], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][5], 0);

    PassportTD_2[playerid][6] = CreatePlayerTextDraw(playerid, 234.000000, 34.000000, "Nama - harus gunakan (A-Z) dan 20 karakter");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][6], 0.220832, 0.849999);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][6], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][6], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][6], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][6], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][6], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][6], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][6], 0);

    PassportTD_2[playerid][7] = CreatePlayerTextDraw(playerid, 229.000000, 42.000000, ".");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][7], 0.158333, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][7], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][7], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][7], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][7], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][7], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][7], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][7], 0);

    PassportTD_2[playerid][8] = CreatePlayerTextDraw(playerid, 234.000000, 43.000000, "tgl lahir - contoh (1999/96/02)");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][8], 0.249999, 0.849999);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][8], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][8], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][8], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][8], 0);

    PassportTD_2[playerid][9] = CreatePlayerTextDraw(playerid, 229.000000, 51.000000, ".");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][9], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][9], 0.158333, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][9], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][9], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][9], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][9], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][9], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][9], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][9], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][9], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][9], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][9], 0);

    PassportTD_2[playerid][10] = CreatePlayerTextDraw(playerid, 234.000000, 52.000000, "jenis kelamin - (F) atau (M)");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][10], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][10], 0.241666, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][10], 1161.000000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][10], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][10], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][10], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][10], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][10], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][10], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][10], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][10], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][10], 0);

    PassportTD_2[playerid][11] = CreatePlayerTextDraw(playerid, 229.000000, 60.000000, ".");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][11], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][11], 0.158333, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][11], 709.500000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][11], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][11], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][11], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][11], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][11], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][11], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][11], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][11], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][11], 0);

    PassportTD_2[playerid][12] = CreatePlayerTextDraw(playerid, 234.000000, 61.000000, "Tinggi badan maksimal 140-200");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][12], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][12], 0.224996, 0.949998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][12], 1161.000000, -21.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][12], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][12], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][12], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][12], 255);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][12], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][12], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][12], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][12], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][12], 0);

    PassportTD_2[playerid][13] = CreatePlayerTextDraw(playerid, 315.000000, 103.000000, "Submit");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][13], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][13], 0.145833, 1.350000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][13], 11.000000, 51.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][13], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][13], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][13], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][13], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][13], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][13], 65480);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][13], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][13], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][13], 1);

    PassportTD_2[playerid][14] = CreatePlayerTextDraw(playerid, 214.000000, 159.000000, "INTERNASIONAL PASSPORT");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][14], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][14], 0.187500, 1.450000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][14], 522.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][14], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][14], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][14], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][14], 1433087999);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][14], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][14], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][14], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][14], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][14], 0);

    PassportTD_2[playerid][15] = CreatePlayerTextDraw(playerid, 214.000000, 193.000000, "Tipe");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][15], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][15], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][15], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][15], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][15], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][15], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][15], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][15], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][15], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][15], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][15], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][15], 0);

    PassportTD_2[playerid][16] = CreatePlayerTextDraw(playerid, 297.000000, 193.000000, "Kota/Kode");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][16], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][16], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][16], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][16], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][16], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][16], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][16], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][16], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][16], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][16], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][16], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][16], 0);

    PassportTD_2[playerid][17] = CreatePlayerTextDraw(playerid, 381.000000, 193.000000, "Passport No.");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][17], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][17], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][17], 435.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][17], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][17], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][17], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][17], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][17], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][17], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][17], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][17], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][17], 0);

    PassportTD_2[playerid][18] = CreatePlayerTextDraw(playerid, 216.000000, 201.000000, "LS");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][18], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][18], 0.187500, 1.299998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][18], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][18], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][18], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][18], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][18], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][18], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][18], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][18], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][18], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][18], 0);

    PassportTD_2[playerid][19] = CreatePlayerTextDraw(playerid, 216.000000, 201.000000, "LS");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][19], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][19], 0.187500, 1.299998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][19], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][19], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][19], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][19], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][19], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][19], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][19], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][19], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][19], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][19], 0);

    PassportTD_2[playerid][20] = CreatePlayerTextDraw(playerid, 297.000000, 201.000000, "LS");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][20], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][20], 0.187500, 1.299998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][20], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][20], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][20], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][20], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][20], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][20], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][20], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][20], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][20], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][20], 0);

    PassportTD_2[playerid][21] = CreatePlayerTextDraw(playerid, 381.000000, 201.000000, "00020020");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][21], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][21], 0.187500, 1.299998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][21], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][21], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][21], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][21], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][21], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][21], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][21], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][21], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][21], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][21], 0);

    PassportTD_2[playerid][22] = CreatePlayerTextDraw(playerid, 180.000000, 224.000000, "Preview_Model");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][22], 5);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][22], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][22], 118.000000, 85.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][22], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][22], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][22], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawSetPreviewModel(playerid, PassportTD_2[playerid][22], 0);
    PlayerTextDrawSetPreviewRot(playerid, PassportTD_2[playerid][22], -10.000000, 0.000000, -3.000000, 0.839999);
    PlayerTextDrawSetPreviewVehCol(playerid, PassportTD_2[playerid][22], 1, 1);

    PassportTD_2[playerid][23] = CreatePlayerTextDraw(playerid, 215.000000, 219.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][23], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][23], 0.600000, 10.300003);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][23], 298.500000, -5.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][23], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][23], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][23], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][23], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][23], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][23], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][23], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][23], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][23], 0);

    PassportTD_2[playerid][24] = CreatePlayerTextDraw(playerid, 269.000000, 219.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][24], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][24], 0.600000, 10.300003);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][24], 298.500000, -5.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][24], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][24], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][24], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][24], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][24], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][24], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][24], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][24], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][24], 0);

    PassportTD_2[playerid][25] = CreatePlayerTextDraw(playerid, 242.000000, 219.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][25], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][25], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][25], 343.500000, 47.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][25], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][25], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][25], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][25], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][25], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][25], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][25], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][25], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][25], 0);

    PassportTD_2[playerid][26] = CreatePlayerTextDraw(playerid, 242.000000, 317.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][26], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][26], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][26], 343.500000, 47.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][26], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][26], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][26], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][26], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][26], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][26], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][26], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][26], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][26], 0);

    PassportTD_2[playerid][27] = CreatePlayerTextDraw(playerid, 272.000000, 221.000000, "Nama Depan");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][27], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][27], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][27], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][27], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][27], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][27], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][27], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][27], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][27], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][27], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][27], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][27], 0);

    PassportTD_2[playerid][28] = CreatePlayerTextDraw(playerid, 307.000000, 232.000000, "Input 5 Kata");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][28], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][28], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][28], 12.000000, 64.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][28], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][28], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][28], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][28], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][28], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][28], 134);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][28], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][28], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][28], 1);

    PassportTD_2[playerid][29] = CreatePlayerTextDraw(playerid, 272.000000, 243.000000, "Nama Belakang");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][29], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][29], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][29], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][29], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][29], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][29], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][29], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][29], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][29], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][29], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][29], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][29], 0);

    PassportTD_2[playerid][30] = CreatePlayerTextDraw(playerid, 307.000000, 255.000000, "Input 7 kata");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][30], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][30], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][30], 12.000000, 64.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][30], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][30], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][30], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][30], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][30], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][30], 134);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][30], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][30], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][30], 1);

    PassportTD_2[playerid][31] = CreatePlayerTextDraw(playerid, 272.000000, 268.000000, "Tgl/lahir/tahun");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][31], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][31], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][31], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][31], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][31], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][31], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][31], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][31], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][31], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][31], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][31], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][31], 0);

    PassportTD_2[playerid][32] = CreatePlayerTextDraw(playerid, 307.000000, 281.000000, "yyyy/ym/dd");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][32], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][32], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][32], 12.000000, 64.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][32], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][32], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][32], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][32], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][32], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][32], 134);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][32], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][32], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][32], 1);

    PassportTD_2[playerid][33] = CreatePlayerTextDraw(playerid, 256.000000, 205.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][33], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][33], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][33], 343.500000, 47.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][33], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][33], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][33], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][33], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][33], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][33], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][33], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][33], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][33], 0);

    PassportTD_2[playerid][34] = CreatePlayerTextDraw(playerid, 357.000000, 202.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][34], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][34], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][34], 333.500000, 37.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][34], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][34], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][34], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][34], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][34], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][34], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][34], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][34], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][34], 0);

    PassportTD_2[playerid][35] = CreatePlayerTextDraw(playerid, 353.000000, 268.000000, "Kelamin");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][35], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][35], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][35], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][35], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][35], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][35], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][35], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][35], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][35], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][35], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][35], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][35], 0);

    PassportTD_2[playerid][36] = CreatePlayerTextDraw(playerid, 366.000000, 281.000000, "M");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][36], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][36], 0.129166, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][36], 12.000000, 13.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][36], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][36], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][36], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][36], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][36], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][36], 134);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][36], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][36], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][36], 1);

    PassportTD_2[playerid][37] = CreatePlayerTextDraw(playerid, 403.000000, 268.000000, "Tinggi");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][37], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][37], 0.158333, 0.850000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][37], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][37], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][37], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][37], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][37], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][37], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][37], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][37], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][37], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][37], 0);

    PassportTD_2[playerid][38] = CreatePlayerTextDraw(playerid, 413.000000, 281.000000, "0cm");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][38], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][38], 0.170833, 0.800000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][38], 12.000000, 20.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][38], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][38], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][38], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][38], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][38], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][38], 134);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][38], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][38], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][38], 1);

    PassportTD_2[playerid][39] = CreatePlayerTextDraw(playerid, 353.000000, 305.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][39], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][39], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][39], 343.500000, 154.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][39], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][39], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][39], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][39], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][39], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][39], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][39], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][39], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][39], 0);

    PassportTD_2[playerid][40] = CreatePlayerTextDraw(playerid, 361.000000, 326.000000, "Copyright");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][40], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][40], 0.150000, 0.550000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][40], 435.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][40], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][40], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][40], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][40], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][40], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][40], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][40], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][40], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][40], 0);

    PassportTD_2[playerid][41] = CreatePlayerTextDraw(playerid, 395.000000, 326.000000, "@Dewata2022");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][41], 2);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][41], 0.116663, 0.550000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][41], 435.500000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][41], 0);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][41], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][41], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][41], 148);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][41], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][41], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][41], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][41], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][41], 0);

    PassportTD_2[playerid][42] = CreatePlayerTextDraw(playerid, 364.000000, 173.000000, "_");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][42], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][42], 0.600000, -0.600000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][42], 343.500000, 128.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][42], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][42], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][42], 2);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][42], -1);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][42], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][42], 135);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][42], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][42], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][42], 0);

    PassportTD_2[playerid][43] = CreatePlayerTextDraw(playerid, 333.000000, 95.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][43], 4);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][43], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][43], 18.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][43], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][43], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][43], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][43], 65494);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][43], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][43], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][43], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][43], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][43], 0);

    PassportTD_2[playerid][44] = CreatePlayerTextDraw(playerid, 276.000000, 95.000000, "ld_beat:chit");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][44], 4);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][44], 0.600000, 2.000000);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][44], 18.000000, 27.500000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][44], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][44], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][44], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][44], 65494);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][44], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][44], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][44], 1);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][44], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][44], 0);

    PassportTD_2[playerid][45] = CreatePlayerTextDraw(playerid, 201.000000, 137.000000, "-");
    PlayerTextDrawFont(playerid, PassportTD_2[playerid][45], 1);
    PlayerTextDrawLetterSize(playerid, PassportTD_2[playerid][45], 17.012533, 3.049998);
    PlayerTextDrawTextSize(playerid, PassportTD_2[playerid][45], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, PassportTD_2[playerid][45], 1);
    PlayerTextDrawSetShadow(playerid, PassportTD_2[playerid][45], 0);
    PlayerTextDrawAlignment(playerid, PassportTD_2[playerid][45], 1);
    PlayerTextDrawColor(playerid, PassportTD_2[playerid][45], -1061109596);
    PlayerTextDrawBackgroundColor(playerid, PassportTD_2[playerid][45], 255);
    PlayerTextDrawBoxColor(playerid, PassportTD_2[playerid][45], 50);
    PlayerTextDrawUseBox(playerid, PassportTD_2[playerid][45], 0);
    PlayerTextDrawSetProportional(playerid, PassportTD_2[playerid][45], 1);
    PlayerTextDrawSetSelectable(playerid, PassportTD_2[playerid][45], 0);

    forex(txd, 46)
    {
        PlayerTextDrawShow(playerid, PassportTD_2[playerid][txd]);
    }
    return 1;
}

stock DestoryPassport_2(playerid)
{
    forex(txd, 46)
    {
        PlayerTextDrawDestroy(playerid, PassportTD_2[playerid][txd]);
        PassportTD_2[playerid][txd] = PlayerText:-1;
    }
    return 1;
}

stock SubmitPassport1(playerid)
{
    if(PassportTD_1[playerid][6] != PlayerText:-1)
    {
        ShowPassport_2(playerid);
    }
    return 1;
}
stock InputAge(playerid)
{
    if(PassportTD_2[playerid][32] != PlayerText:-1)
    {
        Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Date of Birth", "Please enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
    }
    return 1;
}

stock InputGender(playerid)
{
    if(PassportTD_2[playerid][36] != PlayerText:-1)
    {
        Dialog_Show(playerid, Gender, DIALOG_STYLE_LIST, "Input Your Character Gender", "Male | Laki - Laki\nFemale | Perempuan", "Select", "Close");
    }
    return 1;
}

stock InputTinggi(playerid)
{
    if(PassportTD_2[playerid][38] != PlayerText:-1)
    {
        Dialog_Show(playerid, Tinggi, DIALOG_STYLE_INPUT, "Tinggi", "Masukan tinggi badan karaktermu\nCATATAN: Hanya boleh memasukan dari angka 120 - 220", "Select", "Close");
    }
    return 1;
}

stock SubmitPassport(playerid)
{
    if(PassportTD_2[playerid][13] != PlayerText:-1)
    {
        if (PlayerData[playerid][pGender] == -1) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu belum memilih jenis kelamin.");	
        else if (!strlen(PlayerData[playerid][pAge])) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu belum memasukan tanggal lahir.");
        else if(PlayerData[playerid][pHeigth] < 120 || PlayerData[playerid][pHeigth] > 220) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu belum memasukan tinggi badan.");

        CancelSelectTextDraw(playerid);
        DestoryPassport_2(playerid);

        if(PlayerData[playerid][pGender] == 1) PlayerData[playerid][pSkin] = maleskin[random(177)];
        else PlayerData[playerid][pSkin] = femaleskin[random(54)];

        UpdatePlayerSkin(playerid, PlayerData[playerid][pSkin]);
        SetPlayerPos(playerid, 1682.8376,-2241.0151,13.5469);

        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);

        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
        PlayerData[playerid][pPos][0]  = 1682.8376;
        PlayerData[playerid][pPos][1]  = -2241.0151;
        PlayerData[playerid][pPos][2]  = 13.5469;
        PlayerData[playerid][pWorld]  = 0;
        PlayerData[playerid][pInterior]  = 0;
        PlayerData[playerid][pSpawned] = true;
        SetPlayerVirtualWorld(playerid, 0);
        SetPlayerInterior(playerid, 0);
        SetPlayerTeam(playerid, 255);
        UpdatePlayerSkin(playerid, PlayerData[playerid][pSkin]);
        SetCameraBehindPlayer(playerid);
        SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1682.8376, -2241.0151, 13.5469, 178.1388, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
    }
    return 1;
}

// =====
Dialog:Gender(playerid, response, listitem, inputtext[])
{
	if(listitem == 0)
	{
		PlayerData[playerid][pGender] = 1;
        PlayerTextDrawSetString(playerid, PassportTD_2[playerid][36], "M");
        SetTimerEx("SelectTD", 200, false, "d", playerid);
	}
	else if(listitem == 1)
	{
		PlayerData[playerid][pGender] = 2;
        PlayerTextDrawSetString(playerid, PassportTD_2[playerid][36], "F");
        SetTimerEx("SelectTD", 200, false, "d", playerid);
	}
    SetTimerEx("SelectTD", 200, false, "d", playerid);
	return 1;
}

Dialog:Tinggi(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(strval(inputtext) < 120 || strval(inputtext) > 220) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Angka yang kamu masukan tidak valid!");
        PlayerData[playerid][pHeigth] = strval(inputtext);
        PlayerTextDrawSetString(playerid, PassportTD_2[playerid][38], sprintf("%d_CM", PlayerData[playerid][pHeigth]));
    }
    return 1;
}

Dialog:DateBirth(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new
			iDay,
			iMonth,
			iYear,
			str[64];

	    static const
	        arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	    if (sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
	        Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid format specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
		}
		else if (iYear < 1900 || iYear > 2014) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid year specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
		}
		else if (iMonth < 1 || iMonth > 12) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid month specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
		}
		else if (iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
		    Dialog_Show(playerid, DateBirth, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid day specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
		}
		else {
		    format(PlayerData[playerid][pAge], 24, inputtext);

		    format(str, sizeof(str), "%s", inputtext);
		    PlayerTextDrawSetString(playerid, PassportTD_2[playerid][32], str);
		}
	}
    SetTimerEx("SelectTD", 200, false, "d", playerid);
	return 1;
}