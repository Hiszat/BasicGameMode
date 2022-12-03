CMD:myweapon(playerid, params[])
{
    ShowWeapon(playerid, playerid);
    return 1;
}

CMD:givewep(playerid, params[])
{
	new
	    userid,
	    weaponid,
	    ammo;

    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "udI(100)", userid, weaponid, ammo))
	    return SendSyntaxMessage(playerid, "/givewep [playerid/name] [weaponid] [ammo]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You cannot give weapons to disconnected players.");

	if (weaponid <= 0 || weaponid > 46 || (weaponid >= 19 && weaponid <= 21))
		return SendErrorMessage(playerid, "You have specified an invalid weapon.");
	    
	GiveWeaponToPlayer(userid, weaponid, ammo, 500);
	SendServerMessage(playerid, sprintf("Anda telah memberikan %s weapon id%d dengan amunisi%d.", ReturnName(userid), weaponid, ammo));
	return 1;
}