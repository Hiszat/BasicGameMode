CMD:buy(playerid, params[])
{
	static
		id = -1;

	if ((id = Business_Nearest(playerid)) != -1)
	{
	    if (Business_GetCount(playerid) >= MAX_OWNABLE_BUSINESSES)
			return SendErrorMessage(playerid, "You can only own %d businesses at a time.", MAX_OWNABLE_BUSINESSES);

		if (BusinessData[id][bizOwner] != 0)
		    return SendErrorMessage(playerid, "This business is already owned at the moment.");

		if (BusinessData[id][bizPrice] > GetMoney(playerid))
		    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

	    BusinessData[id][bizOwner] = GetPlayerSQLID(playerid);

		Business_Refresh(id);
		Business_Save(id);

	    GiveMoney(playerid, -BusinessData[id][bizPrice]);
	    SendServerMessage(playerid, "You have purchased \"%s\" for %s!", BusinessData[id][bizName], FormatNumber(BusinessData[id][bizPrice]));

		// SendInfoMessage(playerid, "You have ~g~purchased~w~ a business!");
	    printf("[%s] %s has purchased business ID: %d for %s.", ReturnDate(), ReturnName(playerid), id, FormatNumber(BusinessData[id][bizPrice]));
	}
	if ((id = House_Nearest(playerid)) != -1)
	{
		if (House_GetCount(playerid) >= MAX_OWNABLE_HOUSES)
			return SendErrorMessage(playerid, "You can only own %d houses at a time.", MAX_OWNABLE_HOUSES);

		if (HouseData[id][houseOwner] != 0)
		    return SendErrorMessage(playerid, "This house is already owned at the moment.");

		if (HouseData[id][housePrice] > GetMoney(playerid))
		    return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

	    HouseData[id][houseOwner] = GetPlayerSQLID(playerid);

		House_Refresh(id);
		House_Save(id);

	    GiveMoney(playerid, -HouseData[id][housePrice]);
	    SendServerMessage(playerid, "You have purchased \"%s\" for %s!", HouseData[id][houseAddress], FormatNumber(HouseData[id][housePrice]));

		SendInfoMessage(playerid, "You have ~g~purchased~w~ a house!");
	    printf("[%s] %s has purchased house ID: %d for %s.", ReturnDate(), ReturnName(playerid), id, FormatNumber(HouseData[id][housePrice]));
	}
	else if ((id = Business_Inside(playerid)) != -1)
	{
		if (BusinessData[id][bizLocked] != 0 || !BusinessData[id][bizOwner])
		    return SendErrorMessage(playerid, "This business is closed!");

		Business_PurchaseMenu(playerid, id);

	}
	return 1;
}

CMD:abandon(playerid, params[])
{
	static
	    id = -1;

    if (!IsPlayerInAnyVehicle(playerid) && (id = Business_Nearest(playerid)) != -1 && Business_IsOwner(playerid, id))
	{
	    if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
	    {
	        SendSyntaxMessage(playerid, "/abandon [confirm]");
	        SendClientMessage(playerid, X11_RED, "[WARNING]:{FFFFFF} You are about to abandon your business with no refund.");
		}
		else if (!strcmp(params, "confirm", true))
		{
			BusinessData[id][bizOwner] = 0;

			Business_Refresh(id);
			Business_Save(id);

			SendServerMessage(playerid, "You have abandoned your business: %s.", BusinessData[id][bizName]);
			printf("[%s] %s has abandoned business ID: %d.", ReturnDate(), ReturnName(playerid), id);
		}
	}
	if (!IsPlayerInAnyVehicle(playerid) && (id = House_Nearest(playerid)) != -1 && House_IsOwner(playerid, id))
	{
	    if (isnull(params) || (!isnull(params) && strcmp(params, "confirm", true) != 0))
	    {
	        SendSyntaxMessage(playerid, "/abandon [confirm]");
	        SendClientMessage(playerid, X11_RED, "[WARNING]:{FFFFFF} You are about to abandon your house with no refund.");
		}
		else if (!strcmp(params, "confirm", true))
		{
			HouseData[id][houseOwner] = 0;

			House_Refresh(id);
			House_Save(id);

			SendServerMessage(playerid, "You have abandoned your house: %s.", HouseData[id][houseAddress]);
			printf("[%s] %s has abandoned house ID: %d.", ReturnDate(), ReturnName(playerid), id);
		}
	}
	else SendErrorMessage(playerid, "You are not in range of anything you can abandon.");
	return 1;
}

CMD:lock(playerid, params[])
{
	static
	    id = -1;

	if (!IsPlayerInAnyVehicle(playerid) && (id = (Business_Inside(playerid) == -1) ? (Business_Nearest(playerid)) : (Business_Inside(playerid))) != -1)
	{
		if (Business_IsOwner(playerid, id))
		{
			if (!BusinessData[id][bizLocked])
			{
				BusinessData[id][bizLocked] = true;

				Business_Refresh(id);
				Business_Save(id);

				SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "You have ~r~locked~w~ the business!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
  			else
			{
				BusinessData[id][bizLocked] = false;

				Business_Refresh(id);
				Business_Save(id);

				SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "You have ~g~unlocked~w~ the business!");
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
			}
		}
	}
	if (!IsPlayerInAnyVehicle(playerid) && (id = (House_Inside(playerid) == -1) ? (House_Nearest(playerid)) : (House_Inside(playerid))) != -1 && House_IsOwner(playerid, id))
	{
		if (!HouseData[id][houseLocked])
		{
			HouseData[id][houseLocked] = true;
			House_Save(id);

			SendInfoMessage(playerid, "You have ~r~locked~w~ your house!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		else
		{
			HouseData[id][houseLocked] = false;
			House_Save(id);

			SendInfoMessage(playerid, "You have ~g~unlocked~w~ your house!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
	}
	else SendErrorMessage(playerid, "You are not in range of anything you can lock.");
	return 1;
}

CMD:sell(playerid, params[])
{
	static
	    targetid,
	    type[24],
	    string[128];

	if (sscanf(params, "us[24]S()[128]", targetid, type, string))
	{
	    SendSyntaxMessage(playerid, "/sell [playerid/name] [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} business");
	    return 1;
	}
	if (targetid == INVALID_PLAYER_ID || !IsPlayerNearPlayer(playerid, targetid, 5.0))
	{
		SendErrorMessage(playerid, "The player is disconnected or not near you.");
		return 1;
	}
	if (targetid == playerid)
	{
		SendErrorMessage(playerid, "You cannot sell to yourself.");
		return 1;
	}
	if (!strcmp(type, "business", true))
	{
		static
		    price,
			bizid = -1;

		if (sscanf(string, "d", price))
			return SendSyntaxMessage(playerid, "/sell [playerid/name] [business] [price]");

		if (price < 1)
		    return SendErrorMessage(playerid, "The price you've entered cannot below the value of $1.");

		if ((bizid = Business_Nearest(playerid)) != -1 && Business_IsOwner(playerid, bizid)) {
			PlayerData[targetid][pBusinessSeller] = playerid;
			PlayerData[targetid][pBusinessOffered] = bizid;
			PlayerData[targetid][pBusinessValue] = price;

		    SendServerMessage(playerid, "You have requested %s to purchase your business (%s).", ReturnName(targetid, 0), FormatNumber(price));
            SendServerMessage(targetid, "%s has offered you their business for %s (type \"/approve business\" to accept).", ReturnName(playerid, 0), FormatNumber(price));
		}
		else SendErrorMessage(playerid, "You are not in range of any of your businesses.");
	}
	return 1;
}

CMD:approve(playerid, params[])
{
	if (isnull(params))
 	{
	 	SendSyntaxMessage(playerid, "/approve [name]");
		SendClientMessage(playerid, X11_LIGHTBLUE, "OPTION:{FFFFFF} business");
		return 1;
	}
	if (!strcmp(params, "business", true) && PlayerData[playerid][pBusinessSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pBusinessSeller],
	        bizid = PlayerData[playerid][pBusinessOffered],
	        price = PlayerData[playerid][pBusinessValue];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds to purchase this business.");

		if (Business_Nearest(playerid) != bizid)
		    return SendErrorMessage(playerid, "You must be near the business to purchase it.");

		if (!Business_IsOwner(sellerid, bizid))
		    return SendErrorMessage(playerid, "This business offer is no longer valid.");

		SendServerMessage(playerid, "You have successfully purchased %s's business for %s.", ReturnName(sellerid, 0), FormatNumber(price));
		SendServerMessage(sellerid, "%s has successfully purchased your business for %s.", ReturnName(playerid, 0), FormatNumber(price));

		BusinessData[bizid][bizOwner] = GetPlayerSQLID(playerid);
		Business_Save(bizid);

		GiveMoney(playerid, -price);
		GiveMoney(playerid, price);

		printf("[%s] %s (%s) has sold a business to %s (%s) for %s.", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnName(sellerid, 0), PlayerData[sellerid][pIP], FormatNumber(price));

		PlayerData[playerid][pBusinessSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pBusinessOffered] = -1;
		PlayerData[playerid][pBusinessValue] = 0;
	}
	if (!strcmp(params, "house", true) && PlayerData[playerid][pHouseSeller] != INVALID_PLAYER_ID)
	{
	    new
	        sellerid = PlayerData[playerid][pHouseSeller],
	        houseid = PlayerData[playerid][pHouseOffered],
	        price = PlayerData[playerid][pHouseValue];

		if (!IsPlayerNearPlayer(playerid, sellerid, 6.0))
		    return SendErrorMessage(playerid, "You are not near that player.");

		if (GetMoney(playerid) < price)
		    return SendErrorMessage(playerid, "You have insufficient funds to purchase this house.");

		if (House_Nearest(playerid) != houseid)
		    return SendErrorMessage(playerid, "You must be near the house to purchase it.");

		if (!House_IsOwner(sellerid, houseid))
		    return SendErrorMessage(playerid, "This house offer is no longer valid.");

		SendServerMessage(playerid, "You have successfully purchased %s's house for %s.", ReturnName(sellerid, 0), FormatNumber(price));
		SendServerMessage(sellerid, "%s has successfully purchased your house for %s.", ReturnName(playerid, 0), FormatNumber(price));

		HouseData[houseid][houseOwner] = GetPlayerSQLID(playerid);
		House_Save(houseid);

		GiveMoney(playerid, -price);
		GiveMoney(playerid, price);

		printf("[%s] %s (%s) has sold a house to %s (%s) for %s.", ReturnDate(), ReturnName(playerid, 0), PlayerData[playerid][pIP], ReturnName(sellerid, 0), PlayerData[sellerid][pIP], FormatNumber(price));

		PlayerData[playerid][pHouseSeller] = INVALID_PLAYER_ID;
		PlayerData[playerid][pHouseOffered] = -1;
		PlayerData[playerid][pHouseValue] = 0;
	}
	return 1;
}