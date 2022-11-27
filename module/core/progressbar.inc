#define			 MAX_CALLBACK_STR			34

static  PlayerText:ProgressBarTextdraw[MAX_PLAYERS][7],
        LoadingTimer[MAX_PLAYERS],
        LoadingValue[MAX_PLAYERS],
        LoadingMaxValue[MAX_PLAYERS],
        bool:IsLoading[MAX_PLAYERS],
		LoadingCallback[MAX_PLAYERS][MAX_CALLBACK_STR];

forward OnProgressBarTextdrawFinished(playerid);
forward OnProgressBarTextdrawProgress(playerid, value);

static Loading_Remove(playerid)
{
	for(new i = 0; i < 7; i++)
	{
		PlayerTextDrawDestroy(playerid, ProgressBarTextdraw[playerid][i]);
	}
	LoadingValue[playerid] = 0;
	LoadingMaxValue[playerid] = 0;
	IsLoading[playerid] = false;
	LoadingCallback[playerid][0] = EOS;
	return 1;
}

static Loading_BarUpdate(playerid)
{
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][5], LoadingValue[playerid] * 85 / LoadingMaxValue[playerid], 17.000000);

	PlayerTextDrawShow(playerid, ProgressBarTextdraw[playerid][5]);
}

forward Loading_TimerUpdate(playerid);
public Loading_TimerUpdate(playerid)
{
	if(!IsValidProgressBarTextdraw(playerid))
		return 0;

	if(LoadingValue[playerid] < LoadingMaxValue[playerid])
	{
		LoadingValue[playerid]++;
		Loading_BarUpdate(playerid);
        CallLocalFunction(#OnProgressBarTextdrawProgress, "dd", playerid, LoadingValue[playerid]);
	}
	else
	{
		if(LoadingCallback[playerid][0] != EOS)
		{
			CallLocalFunction(LoadingCallback[playerid], "d", playerid);
		}
        CallLocalFunction(#OnProgressBarTextdrawFinished, "d", playerid);
		StopPlayerProgressBarTextdraw(playerid);	
	}
	return 1;
}

stock IsValidProgressBarTextdraw(playerid)
	return IsLoading[playerid];

stock StartPlayerProgressBarTextdraw(playerid, value = 3, text[] = "_", interval = 1000, const callback[] = EOS, color = 1687547391)
{
	if(IsValidProgressBarTextdraw(playerid))
		StopPlayerProgressBarTextdraw(playerid);
	
	for(new i = 0 ; i < strlen(text); i++)
	{
		if(text[i] == ' ')
		{
			text[i] = '_';
		}
	}

	ProgressBarTextdraw[playerid][0] = CreatePlayerTextDraw(playerid, 273.000000, 374.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][0], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][0], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][0], 87.000000, 17.500000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][0], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][0], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][0], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][0], 100);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][0], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][0], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][0], 1);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][0], 0);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][0], 0);

	ProgressBarTextdraw[playerid][1] = CreatePlayerTextDraw(playerid, 273.000000, 373.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][1], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][1], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][1], 87.000000, 1.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][1], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][1], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][1], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][1], -1);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][1], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][1], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][1], 1);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][1], 0);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][1], 0);

	ProgressBarTextdraw[playerid][2] = CreatePlayerTextDraw(playerid, 273.000000, 391.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][2], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][2], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][2], 87.000000, 1.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][2], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][2], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][2], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][2], -1);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][2], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][2], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][2], 1);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][2], 0);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][2], 0);

	ProgressBarTextdraw[playerid][3] = CreatePlayerTextDraw(playerid, 359.000000, 373.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][3], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][3], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][3], 1.000000, 18.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][3], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][3], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][3], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][3], -1);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][3], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][3], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][3], 1);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][3], 0);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][3], 0);

	ProgressBarTextdraw[playerid][4] = CreatePlayerTextDraw(playerid, 273.000000, 373.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][4], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][4], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][4], 1.000000, 18.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][4], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][4], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][4], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][4], -1);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][4], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][4], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][4], 0);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][4], 1);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][4], 0);

	ProgressBarTextdraw[playerid][5] = CreatePlayerTextDraw(playerid, 274.000000, 374.000000, "ld_dual:white");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][5], 4);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][5], 0.600000, 2.000000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][5], 0.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][5], 1);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][5], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][5], 1);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][5], 1687547391);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][5], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][5], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][5], 0);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][5], 1);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][5], 0);

	ProgressBarTextdraw[playerid][6] = CreatePlayerTextDraw(playerid, 317.000000, 377.000000, "_");
	PlayerTextDrawFont(playerid, ProgressBarTextdraw[playerid][6], 1);
	PlayerTextDrawLetterSize(playerid, ProgressBarTextdraw[playerid][6], 0.166666, 1.100000);
	PlayerTextDrawTextSize(playerid, ProgressBarTextdraw[playerid][6], 400.000000, 17.000000);
	PlayerTextDrawSetOutline(playerid, ProgressBarTextdraw[playerid][6], 0);
	PlayerTextDrawSetShadow(playerid, ProgressBarTextdraw[playerid][6], 0);
	PlayerTextDrawAlignment(playerid, ProgressBarTextdraw[playerid][6], 2);
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][6], -1);
	PlayerTextDrawBackgroundColor(playerid, ProgressBarTextdraw[playerid][6], 255);
	PlayerTextDrawBoxColor(playerid, ProgressBarTextdraw[playerid][6], 50);
	PlayerTextDrawUseBox(playerid, ProgressBarTextdraw[playerid][6], 0);
	PlayerTextDrawSetProportional(playerid, ProgressBarTextdraw[playerid][6], 1);
	PlayerTextDrawSetSelectable(playerid, ProgressBarTextdraw[playerid][6], 0);	

	PlayerTextDrawSetString(playerid, ProgressBarTextdraw[playerid][6], sprintf("%s", text));
	PlayerTextDrawColor(playerid, ProgressBarTextdraw[playerid][5], color);

	for(new i = 0; i < 7; i++)
	{
		PlayerTextDrawShow(playerid, ProgressBarTextdraw[playerid][i]);
	}
	if(callback[0] != EOS)
	{
		format(LoadingCallback[playerid], MAX_CALLBACK_STR, "%s", callback);
	}
	LoadingValue[playerid] = 0;
	IsLoading[playerid] = true;
	LoadingMaxValue[playerid] = value;
	LoadingTimer[playerid] = SetTimerEx(#Loading_TimerUpdate, interval, true, "d", playerid);
	return 1;
}

stock StopPlayerProgressBarTextdraw(playerid)
{
    KillTimer(LoadingTimer[playerid]);
    Loading_Remove(playerid);	
}