CMD:createentrance(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (isnull(params) || strlen(params) > 32)
	    return SendSyntaxMessage(playerid, "/createentrance [name]");

	new id = Entrance_Create(playerid, params);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for entrances.");

	SendServerMessage(playerid, sprintf("You have successfully created entrance ID: %d.", id));
	return 1;
}

CMD:editentrance(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/editentrance [id] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} location, interior, password, name, locked, mapicon, type, custom, virtual");
		return 1;
	}
	if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
	    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

	if (!strcmp(type, "location", true))
	{
	    GetPlayerPos(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);
		GetPlayerFacingAngle(playerid, EntranceData[id][entrancePos][3]);

		EntranceData[id][entranceExterior] = GetPlayerInterior(playerid);
		EntranceData[id][entranceExteriorVW] = GetPlayerVirtualWorld(playerid);

		Entrance_Refresh(id);
		Entrance_Save(id);

		SendAdminAction(playerid, "%s has adjusted the location of entrance ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
		GetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);

		EntranceData[id][entranceInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pEntrance] == EntranceData[id][entranceID])
			{
				SetPlayerPos(i, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
				SetPlayerFacingAngle(i, EntranceData[id][entranceInt][3]);

				SetPlayerInterior(i, EntranceData[id][entranceInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Entrance_Save(id);
		SendAdminAction(playerid, "%s has adjusted the interior spawn of entrance ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "custom", true))
	{
	    new status;

	    if (sscanf(string, "d", status))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [custom] [0/1]");

		if (status < 0 || status > 1)
		    return SendErrorMessage(playerid, "You must specify at least 0 or 1.");

	    EntranceData[id][entranceCustom] = status;
	    Entrance_Save(id);

	    if (status) {
			SendAdminAction(playerid, "%s has enabled custom interior mode for entrance ID: %d.", ReturnName(playerid, 0), id);
		}
		else {
		    SendAdminAction(playerid, "%s has disabled custom interior mode for entrance ID: %d.", ReturnName(playerid, 0), id);
		}
	}
	else if (!strcmp(type, "virtual", true))
	{
	    new worldid;

	    if (sscanf(string, "d", worldid))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [virtual] [interior world]");

	    EntranceData[id][entranceWorld] = worldid;

		foreach (new i : Player) if (Entrance_Inside(i) == id) {
			SetPlayerVirtualWorld(i, worldid);
		}
		Entrance_Save(id);
		SendAdminAction(playerid, "%s has adjusted the virtual of entrance ID: %d to %d.", ReturnName(playerid, 0), id, worldid);
	}
	else if (!strcmp(type, "mapicon", true))
	{
	    new icon;

	    if (sscanf(string, "d", icon))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [mapicon] [map icon]");

		if (icon < 0 || icon > 63)
		    return SendErrorMessage(playerid, "Invalid map icon! Valid map icons can be found at \"wiki.sa-mp.com/wiki/MapIcons\".");

	    EntranceData[id][entranceIcon] = icon;

	    Entrance_Refresh(id);
	    Entrance_Save(id);

		SendAdminAction(playerid, "%s has adjusted the price of entrance ID: %d to %d.", ReturnName(playerid, 0), id, icon);
	}
	else if (!strcmp(type, "password", true))
	{
	    new password[32];

	    if (sscanf(string, "s[32]", password))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [password] [entrance pass] (use 'none' to disable)");

		if (!strcmp(password, "none", true)) {
			EntranceData[id][entrancePass][0] = 0;
		}
		else {
		    format(EntranceData[id][entrancePass], 32, password);
		}
	    Entrance_Save(id);
		SendAdminAction(playerid, "%s has adjusted the password of entrance ID: %d to \"%s\".", ReturnName(playerid, 0), id, password);
	}
	else if (!strcmp(type, "locked", true))
	{
	    new locked;

	    if (sscanf(string, "d", locked))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [locked] [locked 0/1]");

		if (locked < 0 || locked > 1)
		    return SendErrorMessage(playerid, "Invalid value. Use 0 for unlocked and 1 for locked.");

	    EntranceData[id][entranceLocked] = locked;
	    Entrance_Save(id);

	    if (locked) {
			SendAdminAction(playerid, "%s has locked entrance ID: %d.", ReturnName(playerid, 0), id);
		} else {
		    SendAdminAction(playerid, "%s has unlocked entrance ID: %d.", ReturnName(playerid, 0), id);
		}
	}
	else if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendSyntaxMessage(playerid, "/editentrance [id] [name] [new name]");

	    format(EntranceData[id][entranceName], 32, name);

	    Entrance_Refresh(id);
	    Entrance_Save(id);

		SendAdminAction(playerid, "%s has adjusted the name of entrance ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	    {
	        SendSyntaxMessage(playerid, "/editentrance [id] [type] [entrance type]");
			SendClientMessage(playerid, X11_LIGHTBLUE, "TYPES:{FFFFFF} 0: None | 1: DMV | 2: Bank | 3: Warehouse | 4: City Hall | 5: Shooting Range");
			return 1;
		}
		if (typeint < 0 || typeint > 5)
			return SendErrorMessage(playerid, "The specified type must be between 0 and 5.");

        EntranceData[id][entranceType] = typeint;

        switch (typeint) {
            case 1: {
            	EntranceData[id][entranceInt][0] = -2029.5531;
           		EntranceData[id][entranceInt][1] = -118.8003;
            	EntranceData[id][entranceInt][2] = 1035.1719;
            	EntranceData[id][entranceInt][3] = 0.0000;
				EntranceData[id][entranceInterior] = 3;
            }
			case 2: {
            	EntranceData[id][entranceInt][0] = 1456.1918;
           		EntranceData[id][entranceInt][1] = -987.9417;
            	EntranceData[id][entranceInt][2] = 996.1050;
            	EntranceData[id][entranceInt][3] = 90.0000;
				EntranceData[id][entranceInterior] = 6;
            }
            case 3: {
                EntranceData[id][entranceInt][0] = 1291.8246;
           		EntranceData[id][entranceInt][1] = 5.8714;
            	EntranceData[id][entranceInt][2] = 1001.0078;
            	EntranceData[id][entranceInt][3] = 180.0000;
				EntranceData[id][entranceInterior] = 18;
			}
			case 4: {
			    EntranceData[id][entranceInt][0] = 390.1687;
           		EntranceData[id][entranceInt][1] = 173.8072;
            	EntranceData[id][entranceInt][2] = 1008.3828;
            	EntranceData[id][entranceInt][3] = 90.0000;
				EntranceData[id][entranceInterior] = 3;
			}
			case 5: {
			    EntranceData[id][entranceInt][0] = 304.0165;
           		EntranceData[id][entranceInt][1] = -141.9894;
            	EntranceData[id][entranceInt][2] = 1004.0625;
            	EntranceData[id][entranceInt][3] = 90.0000;
				EntranceData[id][entranceInterior] = 7;
			}
		}
		foreach (new i : Player)
		{
			if (PlayerData[i][pEntrance] == EntranceData[id][entranceID])
			{
				SetPlayerPos(i, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);
				SetPlayerFacingAngle(i, EntranceData[id][entranceInt][3]);

				SetPlayerInterior(i, EntranceData[id][entranceInterior]);
				SetCameraBehindPlayer(i);
			}
		}
	    Entrance_Save(id);
		SendAdminAction(playerid, "%s has adjusted the type of entrance ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	return 1;
}

CMD:destroyentrance(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroyentrance [entrance id]");

	if ((id < 0 || id >= MAX_ENTRANCES) || !EntranceData[id][entranceExists])
	    return SendErrorMessage(playerid, "You have specified an invalid entrance ID.");

	Entrance_Delete(id);
	SendServerMessage(playerid, sprintf("You have successfully destroyed entrance ID: %d.", id));
	return 1;
}