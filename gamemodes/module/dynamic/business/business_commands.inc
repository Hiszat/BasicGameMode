CMD:createbiz(playerid, params[])
{
    static
		type,
	    price,
	    id;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "dd", type, price))
 	{
	 	SendSyntaxMessage(playerid, "/createbiz [type] [price]");
    	SendClientMessage(playerid, X11_LIGHTBLUE, "[TYPES]:{FFFFFF} 1: Retail | 2: Weapons | 3: Clothes | 4: Fast Food | 5: Dealership | 6: Gas Station | 7: Furniture");
    	return 1;
	}
	if (type < 1 || type > 7)
	    return SendErrorMessage(playerid, "Invalid type specified. Types range from 1 to 7.");

	id = Business_Create(playerid, type, price);

	if (id == -1)
	    return SendErrorMessage(playerid, "The server has reached the limit for businesses.");

	SendServerMessage(playerid, "You have successfully created business ID: %d.", id);
	return 1;
}

CMD:editbiz(playerid, params[])
{
	static
	    id,
	    type[24],
	    string[128];

	if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "ds[24]S()[128]", id, type, string))
 	{
	 	SendSyntaxMessage(playerid, "/editbiz [id] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} location, actor, deliver, name, price, stock, type, cars, spawn");
		return 1;
	}
	if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	if (!strcmp(type, "location", true))
	{
 		GetPlayerPos(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizPos][3]);

		BusinessData[id][bizExterior] = GetPlayerInterior(playerid);
		BusinessData[id][bizExteriorVW] = GetPlayerVirtualWorld(playerid);

		Business_Refresh(id);
		Business_Save(id);

		SendAdminAction(playerid, "%s has adjusted the location of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "actor", true))
	{
	    GetPlayerPos(playerid, BusinessData[id][bizActorPosition][0], BusinessData[id][bizActorPosition][1], BusinessData[id][bizActorPosition][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizActorPosition][3]);

		BusinessData[id][bizInterior] = GetPlayerInterior(playerid);

        foreach (new i : Player)
		{
			if (PlayerData[i][pBusiness] == BusinessData[id][bizID])
			{
				SetPlayerPos(i, BusinessData[id][bizActorPosition][0], BusinessData[id][bizActorPosition][1], BusinessData[id][bizActorPosition][2]);
				SetPlayerFacingAngle(i, BusinessData[id][bizActorPosition][3]);

				SetPlayerInterior(i, BusinessData[id][bizInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Business_Refresh(id);
		Business_Save(id);
		SendAdminAction(playerid, "%s has adjusted the interior spawn of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "deliver", true))
	{
	    if (BusinessData[id][bizType] == 5)
	        return SendErrorMessage(playerid, "This business doesn't accept deliveries.");

	    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
	        return SendErrorMessage(playerid, "You can only place the delivery point outside interiors.");

	    GetPlayerPos(playerid, BusinessData[id][bizDeliver][0], BusinessData[id][bizDeliver][1], BusinessData[id][bizDeliver][2]);
		Business_Refresh(id);

		Business_Save(id);
		SendAdminAction(playerid, "%s has adjusted the deliver point of business ID: %d.", ReturnName(playerid, 0), id);
	}
	else if (!strcmp(type, "price", true))
	{
	    new price;

	    if (sscanf(string, "d", price))
	        return SendSyntaxMessage(playerid, "/editbiz [id] [price] [new price]");

	    BusinessData[id][bizPrice] = price;

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAction(playerid, "%s has adjusted the price of business ID: %d to %s.", ReturnName(playerid, 0), id, FormatNumber(price));
	}
	else if (!strcmp(type, "stock", true))
	{
	    new amount;

	    if (sscanf(string, "d", amount))
	        return SendSyntaxMessage(playerid, "/editbiz [id] [stock] [product amount]");

	    BusinessData[id][bizProducts] = amount;

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAction(playerid, "%s has adjusted the stock of business ID: %d to %s products.", ReturnName(playerid, 0), id, FormatNumber(amount, ""));
	}
	else if (!strcmp(type, "name", true))
	{
	    new name[32];

	    if (sscanf(string, "s[32]", name))
	        return SendSyntaxMessage(playerid, "/editbiz [id] [name] [new name]");

	    format(BusinessData[id][bizName], 32, name);

	    Business_Refresh(id);
	    Business_Save(id);

		SendAdminAction(playerid, "%s has adjusted the name of business ID: %d to \"%s\".", ReturnName(playerid, 0), id, name);
	}
	else if (!strcmp(type, "type", true))
	{
	    new typeint;

	    if (sscanf(string, "d", typeint))
	    {
	        SendSyntaxMessage(playerid, "/editbiz [id] [type] [business type]");
			SendClientMessage(playerid, X11_LIGHTBLUE, "[TYPES]:{FFFFFF} 1: Retail | 2: Weapons | 3: Clothes | 4: Fast Food | 6: Gas Station | 7: Furniture");
			return 1;
		}
		if (typeint < 1 || typeint > 7)
			return SendErrorMessage(playerid, "The specified type must be between 1 and 7.");

        BusinessData[id][bizType] = typeint;

        switch (typeint) {
            case 1: {
            	BusinessData[id][bizActorPosition][0] = -27.3074;
           		BusinessData[id][bizActorPosition][1] = -30.8741;
            	BusinessData[id][bizActorPosition][2] = 1003.5573;
            	BusinessData[id][bizActorPosition][3] = 0.0000;
				BusinessData[id][bizInterior] = 4;
            }
            case 2: {
            	BusinessData[id][bizActorPosition][0] = 316.3963;
            	BusinessData[id][bizActorPosition][1] = -169.8375;
            	BusinessData[id][bizActorPosition][2] = 999.6010;
            	BusinessData[id][bizActorPosition][3] = 0.0000;
				BusinessData[id][bizInterior] = 6;
			}
			case 3: {
            	BusinessData[id][bizActorPosition][0] = 161.4801;
            	BusinessData[id][bizActorPosition][1] = -96.5368;
            	BusinessData[id][bizActorPosition][2] = 1001.8047;
            	BusinessData[id][bizActorPosition][3] = 0.0000;
				BusinessData[id][bizInterior] = 18;
			}
			case 4: {
            	BusinessData[id][bizActorPosition][0] = 363.3402;
            	BusinessData[id][bizActorPosition][1] = -74.6679;
            	BusinessData[id][bizActorPosition][2] = 1001.5078;
            	BusinessData[id][bizActorPosition][3] = 315.0000;
				BusinessData[id][bizInterior] = 10;
			}
			case 5: {
            	BusinessData[id][bizActorPosition][0] = 1494.5612;
            	BusinessData[id][bizActorPosition][1] = 1304.2061;
            	BusinessData[id][bizActorPosition][2] = 1093.2891;
            	BusinessData[id][bizActorPosition][3] = 0.0000;
				BusinessData[id][bizInterior] = 3;
			}
			case 6: {
				BusinessData[id][bizActorPosition][0] = -27.3383;
   				BusinessData[id][bizActorPosition][1] = -57.6909;
			   	BusinessData[id][bizActorPosition][2] = 1003.5469;
      			BusinessData[id][bizActorPosition][3] = 0.0000;
				BusinessData[id][bizInterior] = 6;
			}
			case 7: {
				BusinessData[id][bizActorPosition][0] = -2240.4954;
   				BusinessData[id][bizActorPosition][1] = 128.3774;
			   	BusinessData[id][bizActorPosition][2] = 1035.4210;
      			BusinessData[id][bizActorPosition][3] = 270.0000;
				BusinessData[id][bizInterior] = 6;
			}
		}
		foreach (new i : Player)
		{
			if (PlayerData[i][pBusiness] == BusinessData[id][bizID])
			{
				SetPlayerPos(i, BusinessData[id][bizActorPosition][0], BusinessData[id][bizActorPosition][1], BusinessData[id][bizActorPosition][2]);
				SetPlayerFacingAngle(i, BusinessData[id][bizActorPosition][3]);

				SetPlayerInterior(i, BusinessData[id][bizInterior]);
				SetCameraBehindPlayer(i);
			}
		}
		Business_Refresh(id);

	    Business_Save(id);
		SendAdminAction(playerid, "%s has adjusted the type of business ID: %d to %d.", ReturnName(playerid, 0), id, typeint);
	}
	else if (!strcmp(type, "spawn", true))
	{
	    if (BusinessData[id][bizType] != 5)
	        return SendErrorMessage(playerid, "This business is not a dealership!");

	    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
	        return SendErrorMessage(playerid, "You can only place the vehicle spawn outside interiors.");

	    GetPlayerPos(playerid, BusinessData[id][bizSpawn][0], BusinessData[id][bizSpawn][1], BusinessData[id][bizSpawn][2]);
		GetPlayerFacingAngle(playerid, BusinessData[id][bizSpawn][3]);

		BusinessData[id][bizExterior] = GetPlayerInterior(playerid);

		Business_Save(id);
		SendAdminAction(playerid, "%s has adjusted the vehicle spawn of business ID: %d.", ReturnName(playerid, 0), id);
	}
	return 1;
}

CMD:products(playerid, params[])
{
	static
	    bizid = -1;

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid)) {
	    Business_ProductMenu(playerid, bizid);
	}
	else SendErrorMessage(playerid, "You are not in range of your business interior.");
	return 1;
}

CMD:bizstate(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/bizstate [biz id]");

	if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	BusinessData[id][bizOwner] = 99999999;

	Business_Refresh(id);
	Business_Save(id);

	SendServerMessage(playerid, "This business is now owned by the state (/bizcmds).", id);
	return 1;
}

CMD:destroybiz(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroybiz [biz id]");

	if ((id < 0 || id >= MAX_BUSINESSES) || !BusinessData[id][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	Business_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed business ID: %d.", id);
	return 1;
}

CMD:vault(playerid, params[])
{
    static
	    bizid = -1,
		type[24],
		str[12],
		amount;

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid))
	{
	    if (sscanf(params, "s[24]S()[12]", type, str))
	    {
			SendSyntaxMessage(playerid, "/vault [name] (%s available)", FormatNumber(BusinessData[bizid][bizVault]));
	        SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} withdraw, deposit, balance");
	        return 1;
		}
		if (!strcmp(type, "withdraw", true))
		{
		    if (sscanf(str, "d", amount))
		        return SendSyntaxMessage(playerid, "/vault [withdraw] [amount]");

			if (amount < 1 || amount > BusinessData[bizid][bizVault])
			    return SendErrorMessage(playerid, "Invalid amount specified!");

            BusinessData[bizid][bizVault] -= amount;
            Business_Save(bizid);

            GiveMoney(playerid, amount);
            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has withdrawn %s from the business vault.", ReturnName(playerid, 0), FormatNumber(amount));
		}
		else if (!strcmp(type, "deposit", true))
		{
		    if (sscanf(str, "d", amount))
		        return SendSyntaxMessage(playerid, "/vault [deposit] [amount]");

			if (amount < 1 || amount > GetMoney(playerid))
			    return SendErrorMessage(playerid, "Invalid amount specified!");

            BusinessData[bizid][bizVault] += amount;
            Business_Save(bizid);

            GiveMoney(playerid, -amount);
            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has deposited %s into the business vault.", ReturnName(playerid, 0), FormatNumber(amount));
		}
		else if (!strcmp(type, "balance", true))
		{
		    SendServerMessage(playerid, "\"%s\" has a total vault balance of: %s.", BusinessData[bizid][bizName], FormatNumber(BusinessData[bizid][bizVault]));
		}
	}
	else SendErrorMessage(playerid, "You are not in range of your business interior.");
	return 1;
}

CMD:createpump(playerid, params[])
{
	static
	    id,
		bizid = -1;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", bizid))
	    return SendSyntaxMessage(playerid, "/createpump [business id]");

	if ((bizid < 0 || bizid >= MAX_BUSINESSES) || !BusinessData[bizid][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	if (BusinessData[bizid][bizType] != 6)
	    return SendErrorMessage(playerid, "This business is not a gas station!");

    if (GetPlayerInterior(playerid) > 0 || GetPlayerVirtualWorld(playerid) > 0)
		return SendErrorMessage(playerid, "You can only create gas pumps outside interiors.");

	id = Pump_Create(playerid, bizid);

	if (id == -1)
	    return SendErrorMessage(playerid, "The business has reached the limit for gas pumps.");

	SendServerMessage(playerid, "You have successfully created gas pump ID: %d.", id);
	EditDynamicObject(playerid, PumpData[id][pumpObject]);

	PlayerData[playerid][pEditPump] = id;
	return 1;
}

CMD:destroypump(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroypump [pump id]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
	    return SendErrorMessage(playerid, "Invalid pump ID.");

	Pump_Delete(id);
	SendServerMessage(playerid, "You have successfully destroyed pump ID: %d.", id);
	return 1;
}

CMD:setpump(playerid, params[])
{
	static
	    id = 0,
		amount;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "dd", id, amount))
	    return SendSyntaxMessage(playerid, "/setpump [pump id] [fuel amount]");

	if ((id < 0 || id >= MAX_GAS_PUMPS) || !PumpData[id][pumpExists])
	    return SendErrorMessage(playerid, "Invalid pump ID.");

	PumpData[id][pumpFuel] = amount;

	Pump_Refresh(id);
	Pump_Save(id);

	SendServerMessage(playerid, "You have set the fuel to %d for pump ID: %d.", amount, id);
	return 1;
}

CMD:refuel(playerid, params[])
{
	new vehicleid = GetPlayerVehicleID(playerid);

	if (PlayerData[playerid][pRefill] != INVALID_VEHICLE_ID)
	{
	    BusinessData[PlayerData[playerid][pGasStation]][bizVault] += PlayerData[playerid][pRefillPrice];
		Business_Save(PlayerData[playerid][pGasStation]);

        GiveMoney(playerid, -PlayerData[playerid][pRefillPrice]);

		SendServerMessage(playerid, "You have refueled your vehicle for $%d.", PlayerData[playerid][pRefillPrice]);
        StopRefilling(playerid);

        return 1;
	}
	if (!vehicleid)
	    return SendErrorMessage(playerid, "You are not inside any vehicle!");

	if (GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    return SendErrorMessage(playerid, "You must be the driver of the vehicle!");

	if (GetEngineStatus(vehicleid))
	    return SendErrorMessage(playerid, "You must turn the engine off first.");

	new id = Pump_Nearest(playerid);

	if (id != -1)
	{
		if (VehCore[vehicleid][vehFuel] > 95)
			return SendErrorMessage(playerid, "This vehicle doesn't need any fuel.");

		if (IsPumpOccupied(id))
		    return SendErrorMessage(playerid, "This fuel pump is already occupied.");

		if (PumpData[id][pumpFuel] < 1)
   			return SendErrorMessage(playerid, "This pump doesn't have enough fuel.");

		PlayerData[playerid][pGasPump] = id;
		PlayerData[playerid][pGasStation] = PumpData[id][pumpBusiness];

		PlayerData[playerid][pRefill] = vehicleid;
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has started refilling their vehicle.", ReturnName(playerid, 0));
	}
	else
	{
		SendErrorMessage(playerid, "You are not in range of any unused gas pump.");
	}
	return 1;
}

CMD:bname(playerid, params[])
{
	new
		id = -1;

    if ((id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1 && Business_IsOwner(playerid, id))
	{
		if (isnull(params))
		    return SendSyntaxMessage(playerid, "/bname [new name]");

		if (strlen(params) > 32)
		    return SendErrorMessage(playerid, "The business name can't exceed 32 characters.");

		format(BusinessData[id][bizName], 32, params);

		Business_Refresh(id);
		Business_Save(id);

		SendServerMessage(playerid, "Business name set to: \"%s\".", params);
	}
	else SendErrorMessage(playerid, "You are not in range of your business.");
	return 1;
}

CMD:bmessage(playerid, params[])
{
	new
		id = -1;

    if ((id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1 && Business_IsOwner(playerid, id))
	{
		if (isnull(params))
		    return SendSyntaxMessage(playerid, "/bmessage [message] - Use \"none\" to disable.");

		if (!strcmp(params, "none", true))
		{
		    BusinessData[id][bizMessage][0] = '\0';

			Business_Save(id);
			SendServerMessage(playerid, "You have removed the business message.");
		}
		else
		{
			format(BusinessData[id][bizMessage], 128, params);

			Business_Save(id);
			SendServerMessage(playerid, "Business message set to: \"%s\".", params);
		}
	}
	else SendErrorMessage(playerid, "You are not in range of your business.");
	return 1;
}

CMD:binfo(playerid, params[])
{
    new
		id = -1;

    if ((id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1 && Business_IsOwner(playerid, id)) {
     	SendClientMessage(playerid, X11_WHITE, sprintf("ID: %d | Business: %s | Products: %d | Vault: %s", id, BusinessData[id][bizName], BusinessData[id][bizProducts], FormatNumber(BusinessData[id][bizVault])));
	}
	else SendClientMessage(playerid, X11_WHITE, "You are not in range of your business.");
	return 1;
}

CMD:asellbiz(playerid, params[])
{
	new bizid = -1;

	if (PlayerData[playerid][pAdmin] < 4)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", bizid))
	    return SendSyntaxMessage(playerid, "/asellbiz [business ID]");

	if ((bizid < 0 || bizid >= MAX_BUSINESSES) || !BusinessData[bizid][bizExists])
	    return SendErrorMessage(playerid, "You have specified an invalid business ID.");

	BusinessData[bizid][bizOwner] = 0;

	Business_Refresh(bizid);
	Business_Save(bizid);

	SendServerMessage(playerid, "You have sold business ID: %d.", bizid);
	return 1;
}

/*CMD:kickdoor(playerid, params[])
{
	static
	    id = -1;

	if (GetFactionType(playerid) != FACTION_POLICE)
	    return SendErrorMessage(playerid, "You must be a police officer.");

	if ((id = Business_Nearest(playerid)) != -1)
	{
		if (!BusinessData[id][bizLocked])
		    return SendErrorMessage(playerid, "This business is already unlocked.");

        ApplyAnimation(playerid, "POLICE", "Door_Kick", 4.0, 0, 0, 0, 0, 0);

		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s attempts to kick the business door down.", ReturnName(playerid, 0));
	    SetTimerEx("KickBusiness", 1500, false, "dd", playerid, id);
	}
	else {
		SendErrorMessage(playerid, "You must be in range of a house or business.");
	}
	return 1;
}*/