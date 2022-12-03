#include <YSI_Coding\y_hooks>

new PlayerText:ICON_TEXTDRAW[MAX_PLAYERS][4];
new PlayerText:TEXTDRAW_HUD[MAX_PLAYERS][10];
new PlayerText:TEXTDRAW_DARAH[MAX_PLAYERS];
new PlayerText:TEXTDRAW_ARMOUR[MAX_PLAYERS];
new PlayerText:TEXTDRAW_LAPAR[MAX_PLAYERS];
new PlayerText:TEXTDRAW_HAUS[MAX_PLAYERS];
new PlayerText:SPEED_0[MAX_PLAYERS];
new PlayerText:SPEED_1[MAX_PLAYERS];
new PlayerText:BENSIN_0[MAX_PLAYERS];
new PlayerText:BENSIN_1[MAX_PLAYERS];
new PlayerText:CARTIME[MAX_PLAYERS];
new PlayerText:CRUISE[MAX_PLAYERS];
new PlayerText:SEATBELT[MAX_PLAYERS];
new PlayerText:CAR_GPS[MAX_PLAYERS];

hook OnPlayerConnect(playerid)
{
	TEXTDRAW_DARAH[playerid] = CreatePlayerTextDraw(playerid, 15.000000, 430.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_DARAH[playerid], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_DARAH[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_DARAH[playerid], 28.000000, 13.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_DARAH[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_DARAH[playerid], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_DARAH[playerid], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_DARAH[playerid], -16776961);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_DARAH[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_DARAH[playerid], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_DARAH[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_DARAH[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_DARAH[playerid], 0);

	TEXTDRAW_ARMOUR[playerid] = CreatePlayerTextDraw(playerid, 43.000000, 430.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_ARMOUR[playerid], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_ARMOUR[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_ARMOUR[playerid], 28.000000, 13.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_ARMOUR[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_ARMOUR[playerid], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_ARMOUR[playerid], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_ARMOUR[playerid], -1061109505);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_ARMOUR[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_ARMOUR[playerid], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_ARMOUR[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_ARMOUR[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_ARMOUR[playerid], 0);

	TEXTDRAW_LAPAR[playerid] = CreatePlayerTextDraw(playerid, 75.000000, 444.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_LAPAR[playerid], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_LAPAR[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_LAPAR[playerid], 18.000000, -14.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_LAPAR[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_LAPAR[playerid], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_LAPAR[playerid], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_LAPAR[playerid], 9109759);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_LAPAR[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_LAPAR[playerid], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_LAPAR[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_LAPAR[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_LAPAR[playerid], 0);

	TEXTDRAW_HAUS[playerid] = CreatePlayerTextDraw(playerid, 93.000000, 443.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_HAUS[playerid], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HAUS[playerid], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HAUS[playerid], 18.000000, -13.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HAUS[playerid], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HAUS[playerid], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HAUS[playerid], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HAUS[playerid], 1097458175);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HAUS[playerid], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HAUS[playerid], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HAUS[playerid], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HAUS[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HAUS[playerid], 0);

	SPEED_0[playerid] = CreatePlayerTextDraw(playerid, 140.000000, 389.000000, "000");
	PlayerTextDrawFont(playerid, SPEED_0[playerid], 1);
	PlayerTextDrawLetterSize(playerid, SPEED_0[playerid], 0.354166, 2.699999);
	PlayerTextDrawTextSize(playerid, SPEED_0[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, SPEED_0[playerid], 0);
	PlayerTextDrawSetShadow(playerid, SPEED_0[playerid], 0);
	PlayerTextDrawAlignment(playerid, SPEED_0[playerid], 2);
	PlayerTextDrawColor(playerid, SPEED_0[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, SPEED_0[playerid], 255);
	PlayerTextDrawBoxColor(playerid, SPEED_0[playerid], 50);
	PlayerTextDrawUseBox(playerid, SPEED_0[playerid], 0);
	PlayerTextDrawSetProportional(playerid, SPEED_0[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, SPEED_0[playerid], 0);

	SPEED_1[playerid] = CreatePlayerTextDraw(playerid, 155.000000, 401.000000, "KM/H");
	PlayerTextDrawFont(playerid, SPEED_1[playerid], 1);
	PlayerTextDrawLetterSize(playerid, SPEED_1[playerid], 0.183333, 1.099999);
	PlayerTextDrawTextSize(playerid, SPEED_1[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, SPEED_1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, SPEED_1[playerid], 0);
	PlayerTextDrawAlignment(playerid, SPEED_1[playerid], 1);
	PlayerTextDrawColor(playerid, SPEED_1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, SPEED_1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, SPEED_1[playerid], 50);
	PlayerTextDrawUseBox(playerid, SPEED_1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, SPEED_1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, SPEED_1[playerid], 0);

	BENSIN_0[playerid] = CreatePlayerTextDraw(playerid, 192.000000, 389.000000, "000");
	PlayerTextDrawFont(playerid, BENSIN_0[playerid], 1);
	PlayerTextDrawLetterSize(playerid, BENSIN_0[playerid], 0.354166, 2.699999);
	PlayerTextDrawTextSize(playerid, BENSIN_0[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, BENSIN_0[playerid], 0);
	PlayerTextDrawSetShadow(playerid, BENSIN_0[playerid], 0);
	PlayerTextDrawAlignment(playerid, BENSIN_0[playerid], 2);
	PlayerTextDrawColor(playerid, BENSIN_0[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, BENSIN_0[playerid], 255);
	PlayerTextDrawBoxColor(playerid, BENSIN_0[playerid], 50);
	PlayerTextDrawUseBox(playerid, BENSIN_0[playerid], 0);
	PlayerTextDrawSetProportional(playerid, BENSIN_0[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, BENSIN_0[playerid], 0);

	BENSIN_1[playerid] = CreatePlayerTextDraw(playerid, 207.000000, 400.000000, "BENSIN");
	PlayerTextDrawFont(playerid, BENSIN_1[playerid], 1);
	PlayerTextDrawLetterSize(playerid, BENSIN_1[playerid], 0.183333, 1.099999);
	PlayerTextDrawTextSize(playerid, BENSIN_1[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, BENSIN_1[playerid], 0);
	PlayerTextDrawSetShadow(playerid, BENSIN_1[playerid], 0);
	PlayerTextDrawAlignment(playerid, BENSIN_1[playerid], 1);
	PlayerTextDrawColor(playerid, BENSIN_1[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, BENSIN_1[playerid], 255);
	PlayerTextDrawBoxColor(playerid, BENSIN_1[playerid], 50);
	PlayerTextDrawUseBox(playerid, BENSIN_1[playerid], 0);
	PlayerTextDrawSetProportional(playerid, BENSIN_1[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, BENSIN_1[playerid], 0);

	CARTIME[playerid] = CreatePlayerTextDraw(playerid, 129.000000, 415.000000, "06:18_AM");
	PlayerTextDrawFont(playerid, CARTIME[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CARTIME[playerid], 0.183333, 1.099999);
	PlayerTextDrawTextSize(playerid, CARTIME[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CARTIME[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CARTIME[playerid], 0);
	PlayerTextDrawAlignment(playerid, CARTIME[playerid], 1);
	PlayerTextDrawColor(playerid, CARTIME[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CARTIME[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CARTIME[playerid], 50);
	PlayerTextDrawUseBox(playerid, CARTIME[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CARTIME[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CARTIME[playerid], 0);

	CRUISE[playerid] = CreatePlayerTextDraw(playerid, 169.000000, 415.000000, "CRUISE");
	PlayerTextDrawFont(playerid, CRUISE[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CRUISE[playerid], 0.183333, 1.099999);
	PlayerTextDrawTextSize(playerid, CRUISE[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CRUISE[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CRUISE[playerid], 0);
	PlayerTextDrawAlignment(playerid, CRUISE[playerid], 1);
	PlayerTextDrawColor(playerid, CRUISE[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CRUISE[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CRUISE[playerid], 50);
	PlayerTextDrawUseBox(playerid, CRUISE[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CRUISE[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CRUISE[playerid], 0);

	SEATBELT[playerid] = CreatePlayerTextDraw(playerid, 202.000000, 415.000000, "~R~SEATBELT");
	PlayerTextDrawFont(playerid, SEATBELT[playerid], 1);
	PlayerTextDrawLetterSize(playerid, SEATBELT[playerid], 0.183333, 1.099999);
	PlayerTextDrawTextSize(playerid, SEATBELT[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, SEATBELT[playerid], 0);
	PlayerTextDrawSetShadow(playerid, SEATBELT[playerid], 0);
	PlayerTextDrawAlignment(playerid, SEATBELT[playerid], 1);
	PlayerTextDrawColor(playerid, SEATBELT[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, SEATBELT[playerid], 255);
	PlayerTextDrawBoxColor(playerid, SEATBELT[playerid], 50);
	PlayerTextDrawUseBox(playerid, SEATBELT[playerid], 0);
	PlayerTextDrawSetProportional(playerid, SEATBELT[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, SEATBELT[playerid], 0);

	CAR_GPS[playerid] = CreatePlayerTextDraw(playerid, 128.000000, 428.000000, "E I Idlewood I Los Santos");
	PlayerTextDrawFont(playerid, CAR_GPS[playerid], 1);
	PlayerTextDrawLetterSize(playerid, CAR_GPS[playerid], 0.204167, 1.399999);
	PlayerTextDrawTextSize(playerid, CAR_GPS[playerid], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, CAR_GPS[playerid], 0);
	PlayerTextDrawSetShadow(playerid, CAR_GPS[playerid], 0);
	PlayerTextDrawAlignment(playerid, CAR_GPS[playerid], 1);
	PlayerTextDrawColor(playerid, CAR_GPS[playerid], -1);
	PlayerTextDrawBackgroundColor(playerid, CAR_GPS[playerid], 255);
	PlayerTextDrawBoxColor(playerid, CAR_GPS[playerid], 50);
	PlayerTextDrawUseBox(playerid, CAR_GPS[playerid], 0);
	PlayerTextDrawSetProportional(playerid, CAR_GPS[playerid], 1);
	PlayerTextDrawSetSelectable(playerid, CAR_GPS[playerid], 0);

	ICON_TEXTDRAW[playerid][0] = CreatePlayerTextDraw(playerid, 19.000000, 434.000000, "HUD:radar_girlfriend");
	PlayerTextDrawFont(playerid, ICON_TEXTDRAW[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, ICON_TEXTDRAW[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ICON_TEXTDRAW[playerid][0], 5.500000, 6.000000);
	PlayerTextDrawSetOutline(playerid, ICON_TEXTDRAW[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ICON_TEXTDRAW[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, ICON_TEXTDRAW[playerid][0], 1);
	PlayerTextDrawColor(playerid, ICON_TEXTDRAW[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, ICON_TEXTDRAW[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, ICON_TEXTDRAW[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, ICON_TEXTDRAW[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ICON_TEXTDRAW[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, ICON_TEXTDRAW[playerid][0], 0);

	ICON_TEXTDRAW[playerid][1] = CreatePlayerTextDraw(playerid, 47.000000, 434.000000, "HUD:radar_tshirt");
	PlayerTextDrawFont(playerid, ICON_TEXTDRAW[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, ICON_TEXTDRAW[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ICON_TEXTDRAW[playerid][1], 5.500000, 6.000000);
	PlayerTextDrawSetOutline(playerid, ICON_TEXTDRAW[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ICON_TEXTDRAW[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, ICON_TEXTDRAW[playerid][1], 1);
	PlayerTextDrawColor(playerid, ICON_TEXTDRAW[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, ICON_TEXTDRAW[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, ICON_TEXTDRAW[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, ICON_TEXTDRAW[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ICON_TEXTDRAW[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, ICON_TEXTDRAW[playerid][1], 0);

	ICON_TEXTDRAW[playerid][2] = CreatePlayerTextDraw(playerid, 80.000000, 434.000000, "HUD:radar_pizza");
	PlayerTextDrawFont(playerid, ICON_TEXTDRAW[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, ICON_TEXTDRAW[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ICON_TEXTDRAW[playerid][2], 5.500000, 6.000000);
	PlayerTextDrawSetOutline(playerid, ICON_TEXTDRAW[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ICON_TEXTDRAW[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, ICON_TEXTDRAW[playerid][2], 1);
	PlayerTextDrawColor(playerid, ICON_TEXTDRAW[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, ICON_TEXTDRAW[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, ICON_TEXTDRAW[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, ICON_TEXTDRAW[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ICON_TEXTDRAW[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, ICON_TEXTDRAW[playerid][2], 0);

	ICON_TEXTDRAW[playerid][3] = CreatePlayerTextDraw(playerid, 99.000000, 434.000000, "HUD:radar_centre");
	PlayerTextDrawFont(playerid, ICON_TEXTDRAW[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, ICON_TEXTDRAW[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ICON_TEXTDRAW[playerid][3], 5.500000, 6.000000);
	PlayerTextDrawSetOutline(playerid, ICON_TEXTDRAW[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ICON_TEXTDRAW[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, ICON_TEXTDRAW[playerid][3], 1);
	PlayerTextDrawColor(playerid, ICON_TEXTDRAW[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, ICON_TEXTDRAW[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, ICON_TEXTDRAW[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, ICON_TEXTDRAW[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ICON_TEXTDRAW[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, ICON_TEXTDRAW[playerid][3], 0);

	TEXTDRAW_HUD[playerid][0] = CreatePlayerTextDraw(playerid, 14.000000, 443.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][0], 57.000000, 1.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][0], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][0], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][0], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][0], 0);

	TEXTDRAW_HUD[playerid][1] = CreatePlayerTextDraw(playerid, 16.000000, 429.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][1], 56.500000, 1.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][1], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][1], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][1], 0);

	TEXTDRAW_HUD[playerid][2] = CreatePlayerTextDraw(playerid, 41.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][2], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][2], 0.283333, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][2], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][2], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][2], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][2], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][2], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][2], 0);

	TEXTDRAW_HUD[playerid][3] = CreatePlayerTextDraw(playerid, 13.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][3], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][3], 0.258332, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][3], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][3], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][3], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][3], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][3], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][3], 0);

	TEXTDRAW_HUD[playerid][4] = CreatePlayerTextDraw(playerid, 69.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][4], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][4], 0.258332, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][4], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][4], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][4], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][4], 0);

	TEXTDRAW_HUD[playerid][5] = CreatePlayerTextDraw(playerid, 91.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][5], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][5], 0.275000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][5], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][5], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][5], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][5], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][5], 0);

	TEXTDRAW_HUD[playerid][6] = CreatePlayerTextDraw(playerid, 73.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][6], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][6], 0.258332, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][6], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][6], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][6], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][6], 0);

	TEXTDRAW_HUD[playerid][7] = CreatePlayerTextDraw(playerid, 74.000000, 443.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][7], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][7], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][7], 37.000000, 1.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][7], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][7], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][7], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][7], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][7], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][7], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][7], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][7], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][7], 0);

	TEXTDRAW_HUD[playerid][8] = CreatePlayerTextDraw(playerid, 75.000000, 429.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][8], 4);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][8], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][8], 38.000000, 1.500000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][8], 1);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][8], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][8], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][8], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][8], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][8], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][8], 1);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][8], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][8], 0);

	TEXTDRAW_HUD[playerid][9] = CreatePlayerTextDraw(playerid, 109.000000, 426.000000, "/");
	PlayerTextDrawFont(playerid, TEXTDRAW_HUD[playerid][9], 1);
	PlayerTextDrawLetterSize(playerid, TEXTDRAW_HUD[playerid][9], 0.283333, 2.000000);
	PlayerTextDrawTextSize(playerid, TEXTDRAW_HUD[playerid][9], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, TEXTDRAW_HUD[playerid][9], 0);
	PlayerTextDrawSetShadow(playerid, TEXTDRAW_HUD[playerid][9], 0);
	PlayerTextDrawAlignment(playerid, TEXTDRAW_HUD[playerid][9], 1);
	PlayerTextDrawColor(playerid, TEXTDRAW_HUD[playerid][9], -1);
	PlayerTextDrawBackgroundColor(playerid, TEXTDRAW_HUD[playerid][9], 255);
	PlayerTextDrawBoxColor(playerid, TEXTDRAW_HUD[playerid][9], 50);
	PlayerTextDrawUseBox(playerid, TEXTDRAW_HUD[playerid][9], 0);
	PlayerTextDrawSetProportional(playerid, TEXTDRAW_HUD[playerid][9], 1);
	PlayerTextDrawSetSelectable(playerid, TEXTDRAW_HUD[playerid][9], 0);
	return 1;
}

stock ShowPlayerHud(playerid, status)
{
    if(status)
    {
		PlayerTextDrawShow(playerid, TEXTDRAW_DARAH[playerid]);
		PlayerTextDrawShow(playerid, TEXTDRAW_ARMOUR[playerid]);
		PlayerTextDrawShow(playerid, TEXTDRAW_LAPAR[playerid]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HAUS[playerid]);

		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][0]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][1]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][2]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][3]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][4]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][5]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][6]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][7]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][8]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HUD[playerid][9]);

		PlayerTextDrawShow(playerid, ICON_TEXTDRAW[playerid][0]);
		PlayerTextDrawShow(playerid, ICON_TEXTDRAW[playerid][1]);
		PlayerTextDrawShow(playerid, ICON_TEXTDRAW[playerid][2]);
		PlayerTextDrawShow(playerid, ICON_TEXTDRAW[playerid][3]);

    }
    else {
		PlayerTextDrawHide(playerid, TEXTDRAW_DARAH[playerid]);
		PlayerTextDrawHide(playerid, TEXTDRAW_ARMOUR[playerid]);
		PlayerTextDrawHide(playerid, TEXTDRAW_LAPAR[playerid]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HAUS[playerid]);

		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][0]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][1]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][2]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][3]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][4]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][5]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][6]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][7]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][8]);
		PlayerTextDrawHide(playerid, TEXTDRAW_HUD[playerid][9]);

		PlayerTextDrawHide(playerid, ICON_TEXTDRAW[playerid][0]);
		PlayerTextDrawHide(playerid, ICON_TEXTDRAW[playerid][1]);
		PlayerTextDrawHide(playerid, ICON_TEXTDRAW[playerid][2]);
		PlayerTextDrawHide(playerid, ICON_TEXTDRAW[playerid][3]);
    }
    return 1;
}

stock ShowPlayerSpeedometer(playerid, status)
{
    if(status)
    {
        PlayerTextDrawShow(playerid, SPEED_0[playerid]);
		PlayerTextDrawShow(playerid, SPEED_1[playerid]);
		PlayerTextDrawShow(playerid, BENSIN_0[playerid]);
		PlayerTextDrawShow(playerid, BENSIN_1[playerid]);
		PlayerTextDrawShow(playerid, CARTIME[playerid]);
		PlayerTextDrawShow(playerid, CRUISE[playerid]);
		PlayerTextDrawShow(playerid, SEATBELT[playerid]);
		PlayerTextDrawShow(playerid, CAR_GPS[playerid]);
    }
    else
    {
        PlayerTextDrawHide(playerid, SPEED_0[playerid]);
		PlayerTextDrawHide(playerid, SPEED_1[playerid]);
		PlayerTextDrawHide(playerid, BENSIN_0[playerid]);
		PlayerTextDrawHide(playerid, BENSIN_1[playerid]);
		PlayerTextDrawHide(playerid, CARTIME[playerid]);
		PlayerTextDrawHide(playerid, CRUISE[playerid]);
		PlayerTextDrawHide(playerid, SEATBELT[playerid]);
		PlayerTextDrawHide(playerid, CAR_GPS[playerid]);
    }
    return 1;
}

ptask UpdatePlayerHUD[1000](playerid) 
{
    if(PlayerData[playerid][pSpawned])
    {
        new
			Float:health,
			Float:armour
		;

		GetPlayerHealth(playerid, health);
		GetPlayerArmour(playerid, armour);

		if(health > 100)
		{
			health = 100;
		}
		if(armour > 100)
		{
			armour = 100;
		}

        PlayerTextDrawTextSize(playerid, TEXTDRAW_DARAH[playerid], 0.28 * health, 13.000000);
 		PlayerTextDrawShow(playerid, TEXTDRAW_DARAH[playerid]);

 		PlayerTextDrawTextSize(playerid, TEXTDRAW_ARMOUR[playerid], 0.28 * armour, 13.000000);
 		PlayerTextDrawShow(playerid, TEXTDRAW_ARMOUR[playerid]);

		PlayerTextDrawTextSize(playerid, TEXTDRAW_LAPAR[playerid], 18.000000, -0.145 * PlayerData[playerid][pHunger]);
		PlayerTextDrawShow(playerid, TEXTDRAW_LAPAR[playerid]);

		PlayerTextDrawTextSize(playerid, TEXTDRAW_HAUS[playerid], 18.000000, -0.135 * PlayerData[playerid][pThirst]);
		PlayerTextDrawShow(playerid, TEXTDRAW_HAUS[playerid]);
    }
	if (IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
	{
		static 
				Float:fDamage, 
				Float:fSpeed, 
				Float:fVelocity[3];
				
		new vehicleid = GetPlayerVehicleID(playerid);
		GetVehicleHealth(vehicleid, fDamage);
		GetVehicleVelocity(vehicleid, fVelocity[0], fVelocity[1], fVelocity[2]);
					
		fSpeed = floatmul(floatsqroot((fVelocity[0] * fVelocity[0]) + (fVelocity[1] * fVelocity[1]) + (fVelocity[2] * fVelocity[2])), 100.0);
			
		PlayerTextDrawSetString(playerid, SPEED_0[playerid], sprintf("%.0f", fSpeed));

		PlayerTextDrawSetString(playerid, BENSIN_0[playerid], sprintf("%d", VehCore[vehicleid][vehFuel]));

		new Float:rz;
		new tempstr[32];
		if(IsPlayerInAnyVehicle(playerid))
		{
			GetVehicleZAngle(GetPlayerVehicleID(playerid), rz);
		}
		else
		{
			GetPlayerFacingAngle(playerid, rz);
		}

		if(rz >= 355.0 || rz < 5.0) tempstr = "N";
		else if(rz >= 265.0 && rz < 275.0) tempstr = "E";
		else if(rz >= 175.0 && rz < 185.0) tempstr = "S";
		else if(rz >= 85.0 && rz < 95.0) tempstr = "W";
		else if(rz >= 225.0 && rz < 235.0) tempstr = "SE";
		else if(rz >= 140.0 && rz < 150.0) tempstr = "SW";
		else if(rz >= 50.0 && rz < 60.0) tempstr = "NW";
		else if(rz >= 317.0 && rz < 327.0) tempstr = "NE";
		else tempstr = "Loading...";

		new zone[28], str[400];
		GetPlayer2DZone(playerid, zone, MAX_ZONE_NAME);
		format(str, sizeof(str), "( %s )", zone);

		PlayerTextDrawSetString(playerid, CAR_GPS[playerid], sprintf("%s_I_%s", tempstr, zone));

		new hour, minute;
		gettime(hour, minute);
		PlayerTextDrawSetString(playerid, CARTIME[playerid], sprintf("%02d:%02d", hour, minute));													
	}
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
	if(newstate == PLAYER_STATE_DRIVER)
	{
		ShowPlayerSpeedometer(playerid, true);
	}
	if(oldstate == PLAYER_STATE_DRIVER)
	{
		ShowPlayerSpeedometer(playerid, false);
	}
}