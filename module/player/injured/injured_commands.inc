CMD:arevive(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 3) return PermissionError(playerid);
	    
	new targetid;
	if(sscanf(params, "u", targetid))
	    return SendSyntaxMessage(playerid, "/arevive [playerid]");

	if(targetid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Invalid Player ID!");
	    
	if(!PlayerData[targetid][pInjured])
	    return SendErrorMessage(playerid, "That player is not injured!");
	    
	PlayerData[targetid][pInjured] = false;
	PlayerData[targetid][pDead] = false;
	PlayerData[targetid][pInjuredTime] = 0;
	ClearAnimations(targetid, 1);
	SendClientMessageEx(playerid, -1, "You've healing %s", GetName(targetid));

	if(IsValidDynamic3DTextLabel(PlayerData[targetid][pInjuredLabel]))
		DestroyDynamic3DTextLabel(PlayerData[targetid][pInjuredLabel]);
	return 1;
}

CMD:sethp(playerid, params[])
{
	new
		userid,
	    Float:amount;

	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "uf", userid, amount))
		return SendSyntaxMessage(playerid, "/sethp [playerid/PartOfName] [amount]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	if(amount <= 7.0)
	{
		InjuredPlayer(userid, INVALID_PLAYER_ID, WEAPON_COLLISION);
	}
	else
	{
		SetPlayerHealth(userid, amount);
	}
	SendServerMessage(playerid, sprintf("You have set %s's health to %.2f.", GetName(userid), amount));
	return 1;
}

CMD:accept(playerid, params[])
{
	if(isnull(params))
		return SendSyntaxMessage(playerid, "/accept [Options]"), SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION: {FFFFFF}death, frisk");

	if(!strcmp(params, "death", true))
	{
		new hours, minutes, seconds;
		GetElapsedTime(PlayerData[playerid][pInjuredTime], hours, minutes, seconds);

		if(!PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "You are not injured at the moment.");

		if(PlayerData[playerid][pInjuredTime] > 0 && PlayerData[playerid][pAdmin] < 7)
			return SendErrorMessage(playerid, sprintf("Kamu harus menunggu %02d menit dan %02d detik untuk accept death!", minutes, seconds));

		PlayerData[playerid][pInjured] = false;
		PlayerData[playerid][pDead] = false;
		ClearAnimations(playerid, 1);
		
	    SetPlayerPos(playerid, 1179.9133,-1327.0813,14.2512);
		     
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerHealth(playerid, 100);
		SetPlayerFacingAngle(playerid, 271.9647);
		SetCameraBehindPlayer(playerid);
		SetPlayerHealth(playerid, 100);
        TogglePlayerControllable(playerid, 1);
		SendServerMessage(playerid, "You have been respawned at All Saints General Hospital and fined $50.00");
		// ResetWeapons(playerid);
		GiveMoney(playerid, -5000, "Bayar rumah sakit");
		// ResetDamages(playerid);

		if(IsValidDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]))
			DestroyDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]);

	}
	return 1;
}