stock InjuredPlayer(playerid, killerid, weaponid)
{
	if(PlayerData[playerid][pInjured])
		return 0;

	foreach(new i : Player) if(PlayerData[i][pAdmin] > 0)
	{
		SendDeathMessageToPlayer(i, killerid, playerid, weaponid);
	}

	GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
	
	if (IsPlayerInAnyVehicle(playerid))
 		SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2] + 0.7);

	PlayerData[playerid][pInjured] = true;
	SetPlayerHealth(playerid, 100);
	PlayerData[playerid][pInjuredTime] = 600;
	SendClientMessage(playerid, X11_RED, "WARNING: {FFFFFF}Anda telah {E20000}sekarat. {FFFFFF} Anda dapat memilih untuk {44C300}/accept death");
	SendClientMessage(playerid, X11_WHITE, "...Setelah Death Timer Anda berakhir atau tunggu sampai Anda dihidupkan kembali.");

	ApplyAnimation(playerid, "PED", "KO_SHOT_STOM", 4.0, 1, 0, 0, 0, 0, 1);

	PlayerData[playerid][pInjuredLabel] = CreateDynamic3DTextLabel("(( THIS PLAYER IS INJURED ))", X11_RED, 0.0, 0.0, 0.50, 15.0, playerid);

	SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "SEKARATT!");
	return 1;
}

ptask InjuredUpdate[1000](playerid) 
{
    if(GetPlayerAnimationIndex(playerid) != 1701 && PlayerData[playerid][pInjured])
	{
		ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, 0, 0, 0, 1, 0, 1);
	}
    if(PlayerData[playerid][pInjuredTime] > 0)
	{
		PlayerData[playerid][pInjuredTime]--;
	}
}