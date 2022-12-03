CMD:createfaction(playerid, params[])
{
	static
	    id = -1,
		type,
		name[32];

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[32]", type, name))
	{
	    SendSyntaxMessage(playerid, "/createfaction [type] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "TYPE:{FFFFFF} 1: Police | 2: News | 3: Medical | 4: Government | 5: Gang");
		return 1;
	}
	if (type < 1 || type > 5)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 5.");

	id = Faction_Create(name, type);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for factions.");

	SendServerMessage(playerid, "You have successfully created faction ID: %d.", id);
	return 1;
}

CMD:destroyfaction(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroyfaction [faction id]");

	if ((id < 0 || id >= MAX_FACTIONS) || !FactionData[id][factionExists])
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	Faction_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed faction ID: %d.", id);
	return 1;
}

CMD:flist(playerid, params[])
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists]) {
	    SendClientMessageEx(playerid, X11_WHITE, "[ID: %d] {%06x}%s", i, FactionData[i][factionColor] >>> 8, FactionData[i][factionName]);
	}
	return 1;
}

CMD:editfaction(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/editfaction [id] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} name, color, type, models, locker, ranks, maxranks");
		return 1;
	}
	if ((id < 0 || id >= MAX_FACTIONS) || !FactionData[id][factionExists])
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

    if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendSyntaxMessage(playerid, "/editfaction [id] [name] [new name]");

	    format(FactionData[id][factionName], 32, name);

	    Faction_Save(id);
		SendAdminAction(playerid, "%s has adjusted the name of faction ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	else if (!strcmp(type, "maxranks", true))
	{
	    new ranks;

	    if (sscanf(string, "d", ranks))
	        return SendSyntaxMessage(playerid, "/editfaction [id] [maxranks] [maximum ranks]");

		if (ranks < 1 || ranks > 15)
		    return SendErrorMessage(playerid, "The specified ranks can't be below 1 or above 15.");

	    FactionData[id][factionRanks] = ranks;

	    Faction_Save(id);
		SendAdminAction(playerid, "%s has adjusted the maximum ranks of faction ID: %d to %d.", ReturnName(playerid, 0), id, ranks);
	}
	else if (!strcmp(type, "ranks", true))
	{
	    Faction_ShowRanks(playerid, id);
	}
	else if (!strcmp(type, "color", true))
	{
	    new color;

	    if (sscanf(string, "h", color))
	        return SendSyntaxMessage(playerid, "/editfaction [id] [color] [hex color]");

	    FactionData[id][factionColor] = color;
	    Faction_Update(id);

	    Faction_Save(id);
		SendAdminAction(playerid, "%s has adjusted the {%06x}color{FF6347} of faction ID: %d.", ReturnName(playerid, 0), color >>> 8, id);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
     	{
		 	SendSyntaxMessage(playerid, "/editfaction [id] [type] [faction type]");
            SendClientMessage(playerid, X11_LIGHTBLUE, "TYPE:{FFFFFF} 1: Police | 2: News | 3: Medical | 4: Government | 5: Gang");
            return 1;
		}
		if (typeint < 1 || typeint > 5)
		    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 5.");

	    FactionData[id][factionType] = typeint;

	    Faction_Save(id);
		SendAdminAction(playerid, "%s has adjusted the type of faction ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	else if (!strcmp(type, "models", true))
	{
	    static
	        skins[8];

		for (new i = 0; i < sizeof(skins); i ++)
		    skins[i] = (FactionData[id][factionSkins][i]) ? (FactionData[id][factionSkins][i]) : (19300);

	    PlayerData[playerid][pFactionEdit] = id;
		ShowModelSelectionMenu(playerid, "Faction Skins", MODEL_SELECTION_SKINS, skins, sizeof(skins), -16.0, 0.0, -55.0);
	}
	else if (!strcmp(type, "locker", true))
	{
        PlayerData[playerid][pFactionEdit] = id;
		Dialog_Show(playerid, FactionLocker, DIALOG_STYLE_LIST, "Faction Locker", "Set Location\nLocker Weapons", "Select", "Cancel");
	}
	return 1;
}

CMD:setleader(playerid, params[])
{
	static
		userid,
		id;

    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", userid, id))
	    return SendSyntaxMessage(playerid, "/setleader [playerid/name] [faction id] (Use -1 to unset)");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

    if ((id < -1 || id >= MAX_FACTIONS) || (id != -1 && !FactionData[id][factionExists]))
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	if (id == -1)
	{
	    ResetFaction(userid);

	    SendServerMessage(playerid, "You have removed %s's faction leadership.", ReturnName(userid, 0));
    	SendServerMessage(userid, "%s has removed your faction leadership.", ReturnName(playerid, 0));
	}
	else
	{
		SetFaction(userid, id);
		PlayerData[userid][pFactionRank] = FactionData[id][factionRanks];

		SendServerMessage(playerid, "You have made %s the leader of \"%s\".", ReturnName(userid, 0), FactionData[id][factionName]);
    	SendServerMessage(userid, "%s has made you the leader of \"%s\".", ReturnName(playerid, 0), FactionData[id][factionName]);
	}
    return 1;
}

CMD:asetfaction(playerid, params[])
{
	static
		userid,
		id;

    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", userid, id))
	    return SendSyntaxMessage(playerid, "/asetfaction [playerid/name] [faction id] (Use -1 to unset)");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

    if ((id < -1 || id >= MAX_FACTIONS) || (id != -1 && !FactionData[id][factionExists]))
	    return SendErrorMessage(playerid, "You have specified an invalid faction ID.");

	if (id == -1)
	{
	    ResetFaction(userid);

	    SendServerMessage(playerid, "You have removed %s from their faction.", ReturnName(userid, 0));
    	SendServerMessage(userid, "%s has removed you from your faction.", ReturnName(playerid, 0));
	}
	else
	{
		SetFaction(userid, id);

		if (!PlayerData[userid][pFactionRank])
	    	PlayerData[userid][pFactionRank] = 1;

		SendServerMessage(playerid, "You have set %s's faction to \"%s\".", ReturnName(userid, 0), FactionData[id][factionName]);
    	SendServerMessage(userid, "%s has set your faction to \"%s\".", ReturnName(playerid, 0), FactionData[id][factionName]);
	}
    return 1;
}

CMD:asetrank(playerid, params[])
{
	static
		userid,
		rank,
		factionid;

    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ud", userid, rank))
	    return SendSyntaxMessage(playerid, "/asetrank [playerid/name] [rank id]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "You have specified an invalid player.");

	if ((factionid = PlayerData[userid][pFaction]) == -1)
	    return SendErrorMessage(playerid, "That player is not a member of any faction.");

    if (rank < 1 || rank > FactionData[factionid][factionRanks])
        return SendErrorMessage(playerid, "Invalid rank. Ranks for this faction range from 1 to %d.", FactionData[factionid][factionRanks]);

	PlayerData[userid][pFactionRank] = rank;

	SendServerMessage(playerid, "You have set %s's faction rank to %d.", ReturnName(userid, 0), rank);
    SendServerMessage(userid, "%s has set your faction rank to %d.", ReturnName(playerid, 0), rank);

    return 1;
}

CMD:online(playerid, params[])
{
	new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	SendClientMessage(playerid, X11_LIGHTBLUE, "Online Members:");

	foreach (new i : Player) if (PlayerData[i][pFaction] == factionid) {
		SendClientMessageEx(playerid, X11_WHITE, "[ID: %d] %s - %s (%d)", i, ReturnName(i, 0), Faction_GetRank(i), PlayerData[i][pFactionRank]);
	}
	return 1;
}

CMD:fac(playerid, params[])
{
    new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/(f)ac [message]");

    if (PlayerData[playerid][pDisableFaction])
	    return SendErrorMessage(playerid, "You must enable faction chat first.");

	SendFactionMessage(factionid, X11_WHITE, "(( (%d) %s %s: %s ))", PlayerData[playerid][pFactionRank], Faction_GetRank(playerid), ReturnName(playerid, 0), params);
	printf("[%s] %s %s: %s", ReturnDate(), Faction_GetRank(playerid), ReturnName(playerid, 0), params);
	return 1;
}

CMD:fquit(playerid, params[])
{
	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (GetFactionType(playerid) == FACTION_POLICE)
	{
	    SetPlayerArmour(playerid, 0);
	    ResetWeapons(playerid);
	}
	SendServerMessage(playerid, "You have quit the \"%s\" faction (rank %d).", Faction_GetName(playerid), PlayerData[playerid][pFactionRank]);
    ResetFaction(playerid);

    return 1;
}

CMD:finvite(playerid, params[])
{
	new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/finvite [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (PlayerData[userid][pFaction] == PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is already part of your faction.");

    if (PlayerData[userid][pFaction] != -1)
	    return SendErrorMessage(playerid, "That player is already part of another faction.");

	PlayerData[userid][pFactionOffer] = playerid;
    PlayerData[userid][pFactionOffered] = PlayerData[playerid][pFaction];

    SendServerMessage(playerid, "You have requested %s to join \"%s\".", ReturnName(userid, 0), Faction_GetName(playerid));
    SendServerMessage(userid, "%s has offered you to join \"%s\" (type \"/approve faction\").", ReturnName(playerid, 0), Faction_GetName(playerid));

	return 1;
}

CMD:fremove(playerid, params[])
{
    new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/fremove [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (PlayerData[userid][pFaction] != PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is not part of your faction.");

    SendServerMessage(playerid, "You have removed %s from \"%s\".", ReturnName(userid, 0), Faction_GetName(playerid));
    SendServerMessage(userid, "%s has removed you from the \"%s\" faction.", ReturnName(playerid, 0), Faction_GetName(playerid));

    ResetFaction(userid);

	return 1;
}

CMD:frank(playerid, params[])
{
    new
	    userid,
		rankid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);

	if (sscanf(params, "ud", userid, rankid))
	    return SendSyntaxMessage(playerid, "/frank [playerid/name] [rank (1-%d)]", FactionData[PlayerData[playerid][pFaction]][factionRanks]);

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

	if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot set your own rank.");

	if (PlayerData[userid][pFaction] != PlayerData[playerid][pFaction])
	    return SendErrorMessage(playerid, "That player is not part of your faction.");

	if (rankid < 0 || rankid > FactionData[PlayerData[playerid][pFaction]][factionRanks])
	    return SendErrorMessage(playerid, "Invalid rank specified. Ranks range from 1 to %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks]);

	PlayerData[userid][pFactionRank] = rankid;

    SendServerMessage(playerid, "You have promoted %s to %s (%d).", ReturnName(userid, 0), Faction_GetRank(userid), rankid);
    SendServerMessage(userid, "%s has promoted you to %s (%d).", ReturnName(playerid, 0), Faction_GetRank(userid), rankid);

	return 1;
}

// CMD:spawnpoint(playerid, params[])
// {
// 	new point;
// 	if(sscanf(params, "i", point)) return SendErrorMessage(playerid, "/spawnpoint [0-2] (0 = Airport, 1 = Faction, 2 = Last logged)");
// 	if(point == 0)
// 	{
// 	    SendClientMessage(playerid, X11_WHITE, "You've changed your spawn point to airport.");
// 		PlayerData[playerid][pSpawnPoint] = 0;
// 		return 1;
// 	}
// 	if(point == 1)
// 	{
// 	    if(PlayerData[playerid][pFactionID] == -1)
// 	    {
// 	        SendErrorMessage(playerid, "You're not apart of a faction.");
// 	        return 1;
// 		}
// 		SendClientMessage(playerid, X11_WHITE, "You've changed your spawn to faction.");
// 		PlayerData[playerid][pSpawnPoint] = 1;
// 		return 1;
// 	}
// 	if(point == 2)
// 	{
// 	    SendClientMessage(playerid, X11_WHITE, "You've changed your spawn to your last logged off.");
// 		PlayerData[playerid][pSpawnPoint] = 2;
// 		return 1;
// 	}
// 	return 1;
// }
CMD:fspawn(playerid, params[])
{
	new faction = PlayerData[playerid][pFactionID];

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction leader.");

	if (PlayerData[playerid][pFactionRank] < FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1)
	    return SendErrorMessage(playerid, "You must be at least rank %d.", FactionData[PlayerData[playerid][pFaction]][factionRanks] - 1);
	new Float:X, Float:Y, Float:Z;
	GetPlayerPos(playerid, X, Y, Z);
	FactionData[faction][SpawnX] = X;
	FactionData[faction][SpawnY] = Y;
	FactionData[faction][SpawnZ] = Z;
	FactionData[faction][SpawnInterior] = GetPlayerInterior(playerid);
	FactionData[faction][SpawnVW] = GetPlayerVirtualWorld(playerid);
	Faction_Save(faction);
	return 1;
}