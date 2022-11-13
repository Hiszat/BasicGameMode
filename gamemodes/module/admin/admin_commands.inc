CMD:setplayer(playerid, params[])
{
	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	static
	    userid,
	    type[16],
	    amount[32];

	if (sscanf(params, "us[16]S()[32]", userid, type, amount))
 	{
	 	SendSyntaxMessage(playerid, "/setplayer [playerid/name] [name]");
	 	SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION: {FFFFFF} hunger, thirst");
		return 1;
	}
	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "Anda telah menentukan pemain yang tidak valid.");

	else if (!strcmp(type, "hunger", true))
	{
	    if (isnull(amount))
	        return SendSyntaxMessage(playerid, "/setplayer [playerid/name] [hunger] [amount]");

		if (strval(amount) < 0 || strval(amount) > 100)
		    return SendErrorMessage(playerid, "Anda tidak dapat menentukan jumlah di bawah 0 atau di atas 100.");

		PlayerData[userid][pHunger] = strval(amount);
		SendServerMessage(playerid, sprintf("Anda telah menetapkan %s's hunger ke %s.", GetName(userid), FormatNumber(strval(amount))));
	}
	else if (!strcmp(type, "thirst", true))
	{
	    if (isnull(amount))
	        return SendSyntaxMessage(playerid, "/setplayer [playerid/name] [thirst] [amount]");

        if (strval(amount) < 0 || strval(amount) > 100)
		    return SendErrorMessage(playerid, "Anda tidak dapat menentukan jumlah di bawah 0 atau di atas 100.");

		PlayerData[userid][pThirst] = strval(amount);
		SendServerMessage(playerid, sprintf("Anda telah menetapkan %s Thirst ke %s.", GetName(userid), FormatNumber(strval(amount))));
	}
	return 1;
}

CMD:slap(playerid, params[])
{
	static
	    userid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/aslap [playerid/name]");

    if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(userid, x, y, z);
	SetPlayerPos(userid, x, y, z + 5);

	PlayerPlaySound(userid, 1130, 0.0, 0.0, 0.0);
	SendAdminAction(playerid, "%s melakukan slap kepada %s.", GetName(playerid), GetName(userid));
	return 1;
}

CMD:gotoco(playerid, params[]){
	if(PlayerData[playerid][pAdmin] > 5){
		new Float:a,Float:b,Float:c;
		if(sscanf(params, "fff", a,b,c)) return SendSyntaxMessage(playerid, "/gotocoord [x] [y] [z]");

		SetPlayerPos(playerid, a,b,c);
	}
	return 1;
}

CMD:setworld(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] > 5){
		new a,b,c;
		if(sscanf(params, "udd", a,b,c)) return SendSyntaxMessage(playerid, "/setworld [playerid] [interior] [vw]");
		SetPlayerInterior(a,b);
		SetPlayerVirtualWorld(a,c);
	}
	return 1;
}
CMD:getcar(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);
	    
	new vehicleid;
	if(sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/getcar [vehicle id]");
	    
	new Float:Pos[3];
	GetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]);
	SetVehiclePos(vehicleid, Pos[0], Pos[1], Pos[2]);
	SetPlayerPos(playerid, Pos[0], Pos[1], Pos[2]+1.5);
	LinkVehicleToInterior(vehicleid, GetPlayerInterior(playerid));
	SetVehicleVirtualWorld(vehicleid, GetPlayerVirtualWorld(playerid));
	SendAdminAction(playerid," %s telah menarik kendaraan ID %d", GetName(playerid), vehicleid);
	return 1;
}

CMD:gotocar(playerid, params[])
{
	new vehicleid;

    if (PlayerData[playerid][pAdmin] < 1)
	    return PermissionError(playerid);

	if (sscanf(params, "d", vehicleid))
	    return SendSyntaxMessage(playerid, "/gotocar [vehicle id]");

	if (vehicleid < 1 || vehicleid > MAX_VEHICLES || !IsValidVehicle(vehicleid))
		return SendErrorMessage(playerid, "You have specified an invalid vehicle ID.");

	static
	    Float:x,
	    Float:y,
	    Float:z;

	GetVehiclePos(vehicleid, x, y, z);
	SetPlayerPos(playerid, x, y - 2, z + 2);

	return 1;
}

CMD:goto(playerid, params[])
{
	static
	    id,
	    type[24],
		string[64];

	if (PlayerData[playerid][pAdmin] < 1)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "u", id))
 	{
	 	SendSyntaxMessage(playerid, "/goto [player or name]");
		SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} entrance, business");
		return 1;
	}

	if (id == INVALID_PLAYER_ID)
	{
	    if (sscanf(params, "s[24]S()[64]", type, string))
		{
		    SendSyntaxMessage(playerid, "/goto [player or name]");
			SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} entrance, business");
			return 1;
	    }
		else if (!strcmp(type, "entrance", true))
		{
		    if (sscanf(string, "d", id))
		        return SendSyntaxMessage(playerid, "/goto [entrance] [entrance ID]");

			if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
			    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

		    SetPlayerPos(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);
		    SetPlayerInterior(playerid, EntranceData[id][entranceExterior]);

			SetPlayerVirtualWorld(playerid, EntranceData[id][entranceExteriorVW]);
		    SendServerMessage(playerid, sprintf("You have teleported to entrance ID: %d.", id));
		    return 1;
		}
		else if (!strcmp(type, "business", true))
		{
		    if (sscanf(string, "d", id))
		        return SendSyntaxMessage(playerid, "/goto [business] [business ID]");

			if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
			    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

		    SetPlayerPos(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
		    SetPlayerInterior(playerid, BusinessData[id][bizExterior]);

			SetPlayerVirtualWorld(playerid, BusinessData[id][bizExteriorVW]);
		    SendServerMessage(playerid, "You have teleported to business ID: %d.", id);
		    return 1;
		}
	}
	if (!IsPlayerSpawned(id))
		return SendErrorMessage(playerid, "You can't teleport to a player that's not spawned.");

	SendPlayerToPlayer(playerid, id);

	SendAdminAction(playerid, "Kamu telah teleportasi ke player %s dengan id %d", ReturnName(id), id);
	return 1;
}

CMD:asetmember(playerid, params[])
{
	new facid, otherid;
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You must be admin!");
		
	if(sscanf(params, "ud", otherid, facid))
        return SendSyntaxMessage(playerid, "/asetmember [playerid/PartOfName] [Faction 1 - 4]");
		
	if(otherid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Invalid ID.");
	
	/*if(PlayerData[otherid][pFaction] > 0)
		return SendErrorMessage(playerid, "This player is not in any faction!");*/
	
	if(facid < 1 || facid > 4)
		return SendErrorMessage(playerid, "Faction must 1 - 4 only");
	
	PlayerData[otherid][pFaction] = facid;
	PlayerData[otherid][pFacRank] = 0;
	PlayerData[otherid][pFacDiv] = 0;
	new infoo[256];
	format(infoo, sizeof(infoo), "[Admin]You has set %s faction to %d", PlayerData[otherid][pName], facid);
	SendServerMessage(playerid, infoo);
	format(infoo, sizeof(infoo), "[Admin]%s has set your faction to %s", GetName(playerid), GetFactionName(facid));
	SendServerMessage(otherid, infoo);
	return 1;
}

CMD:asetrank(playerid, params[])
{
	new rank, otherid;
	if(PlayerData[playerid][pAdmin] < 6)
		return SendErrorMessage(playerid, "You must be admin!");
		
	if(sscanf(params, "ud", otherid, rank))
        return SendSyntaxMessage(playerid, "/setrank [playerid/PartOfName] [rank 1-14]");
		
	if(otherid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Invalid ID.");
	
	if(PlayerData[otherid][pFaction] == 0)
		return SendErrorMessage(playerid, "This player is not in any faction!");
	
	if(rank < 1 || rank > 14)
		return SendErrorMessage(playerid, "Rank must 1 - 14 only");
	
	PlayerData[otherid][pFacRank] = rank;
	new infoo[256];
	format(infoo, sizeof(infoo), "[Admin]You has set %s faction rank to level %d", PlayerData[otherid][pName], rank);
	SendServerMessage(playerid, infoo);
	format(infoo, sizeof(infoo), "[Admin]%s has set your faction rank to level %d", GetName(playerid), rank);
	SendServerMessage(otherid, infoo);
	return 1;
}
