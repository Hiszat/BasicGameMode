CMD:createhouse(playerid, params[])
{
	static
	    price,
	    id,
	    address[32];

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[32]", price, address))
	    return SendSyntaxMessage(playerid, "/createhouse [price] [address]");

	for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && !strcmp(HouseData[i][houseAddress], address, true)) {
	    return SendErrorMessage(playerid, "The address \"%s\" is already in use (ID: %d).", address, i);
	}
	id = House_Create(playerid, address, price);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for houses.");

	SendServerMessage(playerid, "You have successfully created house ID: %d.", id);
	return 1;
}

CMD:destroyhouse(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroyhouse [house id]");

	if ((id < 0 || id >= MAX_HOUSES) || !HouseData[id][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	House_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed house ID: %d.", id);
	return 1;
}

CMD:edithouse(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/edithouse [id] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} location, interior, price, address, type");
		return 1;
	}
	if ((id < 0 || id >= MAX_HOUSES) || !HouseData[id][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	if (!strcmp(type, "location", true))
	{
		GetPlayerPos(playerid, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][housePos][3]);

		HouseData[id][houseExterior] = GetPlayerInterior(playerid);
		HouseData[id][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

		House_Refresh(id);
		House_Save(id);

		SendAdminAction(playerid, "%s has adjusted the location of house ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "interior", true))
	{
	    GetPlayerPos(playerid, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
		GetPlayerFacingAngle(playerid, HouseData[id][houseInt][3]);

		HouseData[id][houseInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pHouse] == HouseData[id][houseID])
			{
				SetPlayerPos(i, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
				SetPlayerFacingAngle(i, HouseData[id][houseInt][3]);

				SetPlayerInterior(i, HouseData[id][houseInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		House_Save(id);
		SendAdminAction(playerid, "%s has adjusted the interior spawn of house ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "price", true))
	{
	    new price;

	    if (sscanf(string, "d", price))
	        return SendSyntaxMessage(playerid, "/edithouse [id] [price] [new price]");

	    HouseData[id][housePrice] = price;

	    House_Refresh(id);
	    House_Save(id);

		SendAdminAction(playerid, "%s has adjusted the price of house ID: %d to %s.", ReturnName(playerid, 0), id, FormatNumber(price));
	}
	else if (!strcmp(type, "address", true))
	{
	    new address[32];

	    if (sscanf(string, "s[32]", address))
	        return SendSyntaxMessage(playerid, "/edithouse [id] [address] [new address]");

	    format(HouseData[id][houseAddress], 32, address);

	    House_Refresh(id);
	    House_Save(id);

		SendAdminAction(playerid, "%s has adjusted the address of house ID: %d to \"%s\".", ReturnName(playerid, 0), id, address);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	        return SendSyntaxMessage(playerid, "/edithouse [id] [type] [interior type]");

		if (typeint < 1 || typeint > sizeof(arrHouseInteriors))
			return SendErrorMessage(playerid, "The specified type must be between 1 and %d.", sizeof(arrHouseInteriors));

	    HouseData[id][houseInt][0] = arrHouseInteriors[typeint][eHouseX];
	    HouseData[id][houseInt][1] = arrHouseInteriors[typeint][eHouseY];
	    HouseData[id][houseInt][2] = arrHouseInteriors[typeint][eHouseZ];
	    HouseData[id][houseInt][3] = arrHouseInteriors[typeint][eHouseAngle];
        HouseData[id][houseInterior] = arrHouseInteriors[typeint][eHouseInterior];

		foreach (new i : Player)
		{
			if (PlayerData[i][pHouse] == HouseData[id][houseID])
			{
				SetPlayerPos(i, HouseData[id][houseInt][0], HouseData[id][houseInt][1], HouseData[id][houseInt][2]);
				SetPlayerFacingAngle(i, HouseData[id][houseInt][3]);

				SetPlayerInterior(i, HouseData[id][houseInterior]);
				SetCameraBehindPlayer(i);
			}
		}
	    House_Save(id);
		SendAdminAction(playerid, "%s has adjusted the type of house ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	return 1;
}

CMD:asellhouse(playerid, params[])
{
	new houseid = -1;

    if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", houseid))
	    return SendSyntaxMessage(playerid, "/asellhouse [house ID]");

	if ((houseid < 0 || houseid >= MAX_HOUSES) || !HouseData[houseid][houseExists])
	    return SendErrorMessage(playerid, "You have specified an invalid house ID.");

	HouseData[houseid][houseOwner] = 0;

	House_Refresh(houseid);
	House_Save(houseid);

	SendServerMessage(playerid, "You have sold house ID: %d.", houseid);
	return 1;
}