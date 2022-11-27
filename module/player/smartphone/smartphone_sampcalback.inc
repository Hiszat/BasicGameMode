#include <YSI_Coding\y_hooks>

hook OnPlayerConnect(playerid)
{
    //reset variable
    isOnPhone[playerid] = false;
    PhoneTextdraw[playerid][main_phone][0] = TextDrawCreate(532.000000, 216.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][0], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][0], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][0], 20.500000, 17.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][0], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][0], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][0], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][0], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][0], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][0], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][0], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][0], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][0], 0);

    PhoneTextdraw[playerid][main_phone][1] = TextDrawCreate(601.000000, 216.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][1], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][1], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][1], 21.500000, 17.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][1], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][1], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][1], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][1], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][1], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][1], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][1], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][1], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][1], 0);

    PhoneTextdraw[playerid][main_phone][2] = TextDrawCreate(535.000000, 224.000000, "ld_dual:white");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][2], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][2], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][2], 84.000000, 184.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][2], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][2], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][2], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][2], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][2], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][2], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][2], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][2], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][2], 0);

    PhoneTextdraw[playerid][main_phone][3] = TextDrawCreate(532.000000, 399.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][3], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][3], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][3], 20.500000, 17.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][3], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][3], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][3], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][3], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][3], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][3], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][3], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][3], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][3], 0);

    PhoneTextdraw[playerid][main_phone][4] = TextDrawCreate(601.000000, 399.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][4], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][4], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][4], 21.500000, 17.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][4], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][4], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][4], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][4], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][4], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][4], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][4], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][4], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][4], 0);

    PhoneTextdraw[playerid][main_phone][5] = TextDrawCreate(541.000000, 219.000000, "ld_dual:white");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][5], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][5], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][5], 73.000000, 185.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][5], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][5], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][5], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][5], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][5], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][5], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][5], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][5], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][5], 0);

    PhoneTextdraw[playerid][main_phone][6] = TextDrawCreate(542.000000, 229.000000, "ld_dual:white");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][6], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][6], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][6], 72.000000, 184.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][6], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][6], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][6], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][6], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][6], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][6], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][6], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][6], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][6], 0);

    PhoneTextdraw[playerid][main_phone][7] = TextDrawCreate(575.000000, 223.000000, "Handphone");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][7], 1);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][7], 0.125000, 0.800000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][7], 9.500000, 2.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][7], 0);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][7], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][7], 2);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][7], -1);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][7], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][7], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][7], 0);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][7], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][7], 0);

    PhoneTextdraw[playerid][main_phone][8] = TextDrawCreate(606.000000, 224.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][8], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][8], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][8], 5.000000, 5.500000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][8], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][8], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][8], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][8], -1);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][8], PHONE_COLOR);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][8], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][8], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][8], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][8], 0);

    PhoneTextdraw[playerid][main_phone][9] = TextDrawCreate(607.000000, 225.000000, "ld_beat:chit");
    TextDrawFont(PhoneTextdraw[playerid][main_phone][9], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][9], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][9], 3.000000, 3.500000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][9], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][9], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][9], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][9], PHONE_COLOR);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][9], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][9], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][9], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][9], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][9], 0);

    PhoneTextdraw[playerid][main_phone][10] = TextDrawCreate(567.000000, 396.000000, "ld_beat:chit"); // Tombol Keluar
    TextDrawFont(PhoneTextdraw[playerid][main_phone][10], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][main_phone][10], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][main_phone][10], 17.000000, 17.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][main_phone][10], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][main_phone][10], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][main_phone][10], 1);
    TextDrawColor(PhoneTextdraw[playerid][main_phone][10], -1);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][main_phone][10], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][main_phone][10], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][main_phone][10], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][main_phone][10], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][main_phone][10], 1);

    PhoneTextdraw[playerid][layar] = TextDrawCreate(537.000000, 236.000000, "ld_dual:white");
    TextDrawFont(PhoneTextdraw[playerid][layar], 4);
    TextDrawLetterSize(PhoneTextdraw[playerid][layar], 0.600000, 2.000000);
    TextDrawTextSize(PhoneTextdraw[playerid][layar], 80.000000, 160.000000);
    TextDrawSetOutline(PhoneTextdraw[playerid][layar], 1);
    TextDrawSetShadow(PhoneTextdraw[playerid][layar], 0);
    TextDrawAlignment(PhoneTextdraw[playerid][layar], 1);
    TextDrawColor(PhoneTextdraw[playerid][layar], 1687547391);
    TextDrawBackgroundColor(PhoneTextdraw[playerid][layar], 255);
    TextDrawBoxColor(PhoneTextdraw[playerid][layar], 50);
    TextDrawUseBox(PhoneTextdraw[playerid][layar], 1);
    TextDrawSetProportional(PhoneTextdraw[playerid][layar], 1);
    TextDrawSetSelectable(PhoneTextdraw[playerid][layar], 0);

    // Lockscreen
    PhoneTextdraw[playerid][lockscreen][0] = CreatePlayerTextDraw(playerid, 554.000000, 256.000000, "00:00");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][lockscreen][0], 1);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][lockscreen][0], 0.404166, 1.750000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][lockscreen][0], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][lockscreen][0], 0);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][lockscreen][0], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][lockscreen][0], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][lockscreen][0], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][lockscreen][0], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][lockscreen][0], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][lockscreen][0], 0);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][lockscreen][0], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][lockscreen][0], 0);

	PhoneTextdraw[playerid][lockscreen][1] = CreatePlayerTextDraw(playerid, 550.000000, 273.000000, "Sel_20_Oktober_2022");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][lockscreen][1], 1);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][lockscreen][1], 0.150000, 1.100000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][lockscreen][1], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][lockscreen][1], 0);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][lockscreen][1], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][lockscreen][1], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][lockscreen][1], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][lockscreen][1], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][lockscreen][1], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][lockscreen][1], 0);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][lockscreen][1], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][lockscreen][1], 0);

	PhoneTextdraw[playerid][lockscreen][2] = CreatePlayerTextDraw(playerid, 606.000000, 379.000000, "Klik Untuk Membuka Kunci");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][lockscreen][2], 1);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][lockscreen][2], 0.129166, 1.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][lockscreen][2], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][lockscreen][2], 0);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][lockscreen][2], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][lockscreen][2], 3);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][lockscreen][2], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][lockscreen][2], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][lockscreen][2], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][lockscreen][2], 0);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][lockscreen][2], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][lockscreen][2], 0);

	PhoneTextdraw[playerid][lockscreen][3] = CreatePlayerTextDraw(playerid, 537.000000, 236.000000, "_");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][lockscreen][3], 4);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][lockscreen][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][lockscreen][3], 80.000000, 160.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][lockscreen][3], 1);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][lockscreen][3], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][lockscreen][3], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][lockscreen][3], 1687547391);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][lockscreen][3], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][lockscreen][3], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][lockscreen][3], 1);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][lockscreen][3], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][lockscreen][3], 0);

	PhoneTextdraw[playerid][lockscreen][4] = CreatePlayerTextDraw(playerid, 566.000000, 356.000000, "HUD:skipicon");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][lockscreen][4], 4);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][lockscreen][4], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][lockscreen][4], 17.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][lockscreen][4], 1);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][lockscreen][4], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][lockscreen][4], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][lockscreen][4], 255);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][lockscreen][4], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][lockscreen][4], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][lockscreen][4], 1);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][lockscreen][4], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][lockscreen][4], 1);

    // Navigasi
    PhoneTextdraw[playerid][navigasi] = CreatePlayerTextDraw(playerid, 537.000000, 236.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][navigasi], 4);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][navigasi], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][navigasi], 80.000000, 12.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][navigasi], 1);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][navigasi], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][navigasi], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][navigasi], 145);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][navigasi], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][navigasi], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][navigasi], 1);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][navigasi], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][navigasi], 0);

    PhoneTextdraw[playerid][batrai_0] = CreatePlayerTextDraw(playerid, 604.000000, 241.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][batrai_0], 4);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][batrai_0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][batrai_0], 8.500000, 3.500000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][batrai_0], 1);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][batrai_0], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][batrai_0], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][batrai_0], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][batrai_0], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][batrai_0], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][batrai_0], 1);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][batrai_0], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][batrai_0], 0);

	PhoneTextdraw[playerid][batrai_1] = CreatePlayerTextDraw(playerid, 604.000000, 241.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][batrai_1], 4);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][batrai_1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][batrai_1], 8.500000, 3.500000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][batrai_1], 1);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][batrai_1], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][batrai_1], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][batrai_1], 9109759);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][batrai_1], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][batrai_1], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][batrai_1], 1);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][batrai_1], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][batrai_1], 0);

	PhoneTextdraw[playerid][provider] = CreatePlayerTextDraw(playerid, 541.000000, 239.000000, "AXIS");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][provider], 1);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][provider], 0.112500, 0.700000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][provider], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][provider], 0);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][provider], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][provider], 1);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][provider], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][provider], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][provider], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][provider], 0);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][provider], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][provider], 0);

	PhoneTextdraw[playerid][ptime] = CreatePlayerTextDraw(playerid, 575.000000, 239.000000, "06:51_PM");
	PlayerTextDrawFont(playerid, PhoneTextdraw[playerid][ptime], 1);
	PlayerTextDrawLetterSize(playerid, PhoneTextdraw[playerid][ptime], 0.112500, 0.700000);
	PlayerTextDrawTextSize(playerid, PhoneTextdraw[playerid][ptime], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, PhoneTextdraw[playerid][ptime], 0);
	PlayerTextDrawSetShadow(playerid, PhoneTextdraw[playerid][ptime], 0);
	PlayerTextDrawAlignment(playerid, PhoneTextdraw[playerid][ptime], 2);
	PlayerTextDrawColor(playerid, PhoneTextdraw[playerid][ptime], -1);
	PlayerTextDrawBackgroundColor(playerid, PhoneTextdraw[playerid][ptime], 255);
	PlayerTextDrawBoxColor(playerid, PhoneTextdraw[playerid][ptime], 50);
	PlayerTextDrawUseBox(playerid, PhoneTextdraw[playerid][ptime], 0);
	PlayerTextDrawSetProportional(playerid, PhoneTextdraw[playerid][ptime], 1);
	PlayerTextDrawSetSelectable(playerid, PhoneTextdraw[playerid][ptime], 0);
    return 1;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
    if(clickedid == PhoneTextdraw[playerid][main_phone][10])
    {
        CancelSelectTextDraw(playerid);
        ShowPlayerPhone(playerid, false);
    }
}    