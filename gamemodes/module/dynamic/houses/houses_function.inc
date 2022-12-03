Function:KickHouse(playerid, id)
{
	if ( PlayerData[playerid][pFaction] != 1 || House_Nearest(playerid) != id)
	    return 0;

	switch (random(6))
	{
	    case 0..2:
	    {
	        SendInfoMessage(playerid, "You have ~r~failed~w~ to kick the door down.");
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has failed to kick the door down.", ReturnName(playerid, 0));
		}
		default:
		{
		    HouseData[id][houseLocked] = 0;
		    House_Save(id);

		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has successfully kicked the door down.", ReturnName(playerid, 0));
		    SendInfoMessage(playerid, "Press ~y~'F'~w~ to enter the house.");
		}
	}
	return 1;
}

Function:House_Load()
{
	static
		str[128];

	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            HouseData[i][houseExists] = true;
            HouseData[i][houseLights] = false;

            cache_get_value_name_int(i, "houseID", HouseData[i][houseID]);
            cache_get_value_name_int(i, "houseOwner", HouseData[i][houseOwner]);
            cache_get_value_name_int(i, "housePrice", HouseData[i][housePrice]);

            cache_get_value_name(i, "houseAddress", HouseData[i][houseAddress]);

            cache_get_value_name_float(i, "housePosX", HouseData[i][housePos][0]);
            cache_get_value_name_float(i, "housePosY", HouseData[i][housePos][1]);
            cache_get_value_name_float(i, "housePosZ", HouseData[i][housePos][2]);
            cache_get_value_name_float(i, "housePosA", HouseData[i][housePos][3]);
            cache_get_value_name_float(i, "houseIntX", HouseData[i][houseInt][0]);
            cache_get_value_name_float(i, "houseIntY", HouseData[i][houseInt][1]);
            cache_get_value_name_float(i, "houseIntZ", HouseData[i][houseInt][2]);
            cache_get_value_name_float(i, "houseIntA", HouseData[i][houseInt][3]);
            cache_get_value_name_int(i, "houseInterior", HouseData[i][houseInterior]);
            cache_get_value_name_int(i, "houseExterior", HouseData[i][houseExterior]);
            cache_get_value_name_int(i, "houseExteriorVW", HouseData[i][houseExteriorVW]);
            cache_get_value_name_int(i, "houseLocked", HouseData[i][houseLocked]);
            cache_get_value_name_int(i, "houseMoney", HouseData[i][houseMoney]);

            for (new j = 0; j < 10; j ++)
            {
                format(str, 24, "houseWeapon%d", j + 1);
                cache_get_value_name_int(i, str, HouseData[i][houseWeapons][j]);

                format(str, 24, "houseAmmo%d", j + 1);
                cache_get_value_name_int(i, str, HouseData[i][houseAmmo][j]);
            }
			for (new j = 0; j < 5; j ++)
            {
				format(str, 24, "houseClothing%d", j + 1);
                cache_get_value_name_int(i, str, HouseData[i][houseClothing][j]);

			}

            House_Refresh(i);
        }
        for (new i = 0; i < MAX_HOUSES; i ++) if (HouseData[i][houseExists]) {
            format(str, sizeof(str), "SELECT * FROM `housestorage` WHERE `ID` = '%d'", HouseData[i][houseID]);

            mysql_tquery(sqlcon, str, "OnLoadStorage", "d", i);
        }
    }
    printf("[HOUSE] Loaded %d House from database.", rows);
	return 1;
}

Function:OnLoadStorage(houseid)
{
	static
		str[32];

	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            HouseStorage[houseid][i][hItemExists] = true;
            cache_get_value_name_int(i, "itemID", HouseStorage[houseid][i][hItemID]);
            cache_get_value_name_int(i, "itemModel", HouseStorage[houseid][i][hItemModel]);
            cache_get_value_name_int(i, "itemQuantity", HouseStorage[houseid][i][hItemQuantity]);

            cache_get_value_name(i, "itemName", str);
            strpack(HouseStorage[houseid][i][hItemName], str, 32 char);
        }
	}
	return 1;
}

House_Save(houseid)
{
	static
	    query[1536];

	format(query, sizeof(query), "UPDATE `houses` SET `houseOwner` = '%d', `housePrice` = '%d', `houseAddress` = '%s', `housePosX` = '%.4f', `housePosY` = '%.4f', `housePosZ` = '%.4f', `housePosA` = '%.4f', `houseIntX` = '%.4f', `houseIntY` = '%.4f', `houseIntZ` = '%.4f', `houseIntA` = '%.4f', `houseInterior` = '%d', `houseExterior` = '%d', `houseExteriorVW` = '%d'",
	    HouseData[houseid][houseOwner],
	    HouseData[houseid][housePrice],
	    HouseData[houseid][houseAddress],
	    HouseData[houseid][housePos][0],
	    HouseData[houseid][housePos][1],
	    HouseData[houseid][housePos][2],
	    HouseData[houseid][housePos][3],
	    HouseData[houseid][houseInt][0],
	    HouseData[houseid][houseInt][1],
	    HouseData[houseid][houseInt][2],
	    HouseData[houseid][houseInt][3],
        HouseData[houseid][houseInterior],
        HouseData[houseid][houseExterior],
        HouseData[houseid][houseExteriorVW]
	);
	for (new i = 0; i < 10; i ++) {
		format(query, sizeof(query), "%s, `houseWeapon%d` = '%d', `houseAmmo%d` = '%d'", query, i + 1, HouseData[houseid][houseWeapons][i], i + 1, HouseData[houseid][houseAmmo][i]);
	}
	for (new i = 0; i < 5; i ++) {
		format(query, sizeof(query), "%s, `houseClothing%d` = '%d'", query, i + 1, HouseData[houseid][houseClothing][i]);
	}
	format(query, sizeof(query), "%s, `houseLocked` = '%d', `houseMoney` = '%d' WHERE `houseID` = '%d'",
	    query,
	    HouseData[houseid][houseLocked],
	    HouseData[houseid][houseMoney],
        HouseData[houseid][houseID]
	);
	return mysql_tquery(sqlcon, query);
}

House_Inside(playerid)
{
	if (PlayerData[playerid][pHouse] != -1)
	{
	    for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && HouseData[i][houseID] == PlayerData[playerid][pHouse] && GetPlayerInterior(playerid) == HouseData[i][houseInterior] && GetPlayerVirtualWorld(playerid) > 0) {
	        return i;
		}
	}
	return -1;
}

House_Nearest(playerid)
{
    for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && IsPlayerInRangeOfPoint(playerid, 2.5, HouseData[i][housePos][0], HouseData[i][housePos][1], HouseData[i][housePos][2]))
	{
		if (GetPlayerInterior(playerid) == HouseData[i][houseExterior] && GetPlayerVirtualWorld(playerid) == HouseData[i][houseExteriorVW])
			return i;
	}
	return -1;
}

House_Refresh(houseid)
{
	if (houseid != -1 && HouseData[houseid][houseExists])
	{
		if (IsValidDynamic3DTextLabel(HouseData[houseid][houseText3D]))
		    DestroyDynamic3DTextLabel(HouseData[houseid][houseText3D]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickup]))
		    DestroyDynamicPickup(HouseData[houseid][housePickup]);

		if (IsValidDynamicMapIcon(HouseData[houseid][houseMapIcon]))
		    DestroyDynamicMapIcon(HouseData[houseid][houseMapIcon]);

		static
		    string[128];

		if (!HouseData[houseid][houseOwner]) {
			format(string, sizeof(string), "[%s]\n%s", FormatNumber(HouseData[houseid][housePrice]), HouseData[houseid][houseAddress]);
            HouseData[houseid][houseText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
		}
		// else {
		// 	format(string, sizeof(string), "%s", HouseData[houseid][houseAddress]);
		// 	HouseData[houseid][houseText3D] = CreateDynamic3DTextLabel(string, X11_WHITE, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
		// }
        HouseData[houseid][housePickup] = CreateDynamicPickup(19132, 23, HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
        HouseData[houseid][houseMapIcon] = CreateDynamicMapIcon(HouseData[houseid][housePos][0], HouseData[houseid][housePos][1], HouseData[houseid][housePos][2], (HouseData[houseid][houseOwner] != 0) ? (32) : (31), 0, HouseData[houseid][houseExteriorVW], HouseData[houseid][houseExterior]);
	}
	return 1;
}

House_GetCount(playerid)
{
	new
		count = 0;

	for (new i = 0; i != MAX_HOUSES; i ++)
	{
		if (HouseData[i][houseExists] && House_IsOwner(playerid, i))
   		{
   		    count++;
		}
	}
	return count;
}

House_Create(playerid, address[], price)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_HOUSES; i ++)
		{
	    	if (!HouseData[i][houseExists])
		    {
    	        HouseData[i][houseExists] = true;
        	    HouseData[i][houseOwner] = 0;
            	HouseData[i][housePrice] = price;
            	HouseData[i][houseMoney] = 0;

				format(HouseData[i][houseAddress], 32, address);

    	        HouseData[i][housePos][0] = x;
    	        HouseData[i][housePos][1] = y;
    	        HouseData[i][housePos][2] = z;
    	        HouseData[i][housePos][3] = angle;

                HouseData[i][houseInt][0] = 2269.8772;
                HouseData[i][houseInt][1] = -1210.3240;
                HouseData[i][houseInt][2] = 1047.5625;
                HouseData[i][houseInt][3] = 90.0000;

				HouseData[i][houseInterior] = 10;
				HouseData[i][houseExterior] = GetPlayerInterior(playerid);
				HouseData[i][houseExteriorVW] = GetPlayerVirtualWorld(playerid);

				HouseData[i][houseLights] = false;
				HouseData[i][houseLocked] = false;

				House_Refresh(i);
				mysql_tquery(sqlcon, "INSERT INTO `houses` (`houseOwner`) VALUES(0)", "OnHouseCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

House_Delete(houseid)
{
	if (houseid != -1 && HouseData[houseid][houseExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `houses` WHERE `houseID` = '%d'", HouseData[houseid][houseID]);
		mysql_tquery(sqlcon, string);

        if (IsValidDynamic3DTextLabel(HouseData[houseid][houseText3D]))
		    DestroyDynamic3DTextLabel(HouseData[houseid][houseText3D]);

		if (IsValidDynamicPickup(HouseData[houseid][housePickup]))
		    DestroyDynamicPickup(HouseData[houseid][housePickup]);

		if (IsValidDynamicMapIcon(HouseData[houseid][houseMapIcon]))
		    DestroyDynamicMapIcon(HouseData[houseid][houseMapIcon]);

		House_RemoveAllItems(houseid);

	    HouseData[houseid][houseExists] = false;
	    HouseData[houseid][houseOwner] = 0;
	    HouseData[houseid][houseID] = 0;
	}
	return 1;
}

House_IsOwner(playerid, houseid)
{
	if (!PlayerData[playerid][pLogged] || PlayerData[playerid][pID] == -1)
	    return 0;

    if ((HouseData[houseid][houseExists] && HouseData[houseid][houseOwner] != 0) && HouseData[houseid][houseOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

stock House_WeaponStorage(playerid, houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[320];

	string[0] = 0;

	for (new i = 0; i < 10; i ++)
	{
	    if (!HouseData[houseid][houseWeapons][i])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else
			format(string, sizeof(string), "%s%s (Ammo: %d)\n", string, ReturnWeaponName(HouseData[houseid][houseWeapons][i]), HouseData[houseid][houseAmmo][i]);
	}
	Dialog_Show(playerid, HouseWeapons, DIALOG_STYLE_LIST, "Weapon Storage", string, "Select", "Cancel");
	return 1;
}

stock House_ShowItems(playerid, houseid)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[MAX_HOUSE_STORAGE * 32],
		name[32];

	string[0] = 0;

	for (new i = 0; i != MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        format(string, sizeof(string), "%sEmpty Slot\n", string);

		else {
			strunpack(name, HouseStorage[houseid][i][hItemName]);

			if (HouseStorage[houseid][i][hItemQuantity] == 1) {
			    format(string, sizeof(string), "%s%s\n", string, name);
			}
			else format(string, sizeof(string), "%s%s (%d)\n", string, name, HouseStorage[houseid][i][hItemQuantity]);
		}
	}
	Dialog_Show(playerid, HouseItems, DIALOG_STYLE_LIST, "Item Storage", string, "Select", "Cancel");
	return 1;
}

stock House_OpenStorage(playerid, houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		items[2],
		string[MAX_HOUSE_STORAGE * 32];

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++) if (HouseStorage[houseid][i][hItemExists]) {
	    items[0]++;
	}
	for (new i = 0; i < 10; i ++) if (HouseData[houseid][houseWeapons][i]) {
	    items[1]++;
	}
	if (!House_IsOwner(playerid, houseid))
	    format(string, sizeof(string), "Jenis Berangkas\tJumlah Barang\nBerangkas Barang\t(%d/%d)\nBerangkas Senjata\t(%d/10)", items[0], MAX_HOUSE_STORAGE, items[1]);

	else
		format(string, sizeof(string), "Jenis Berangkas\tJumlah Barang\nBerangkas Barang\t(%d/%d)\nBerangkas Senjata\t(%d/10)\nBerangkas Uang\t(%s)\n"YELLOW"Berangkas Baju", items[0], MAX_HOUSE_STORAGE, items[1], FormatNumber(HouseData[houseid][houseMoney]));

	Dialog_Show(playerid, HouseStorage, DIALOG_STYLE_TABLIST_HEADERS, "BERANGKAS RUMAH", string, "Select", "Cancel");
	return 1;
}

stock House_GetItemID(houseid, item[])
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        continue;

		if (!strcmp(HouseStorage[houseid][i][hItemName], item)) return i;
	}
	return -1;
}

stock House_GetFreeID(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	for (new i = 0; i < MAX_HOUSE_STORAGE; i ++)
	{
	    if (!HouseStorage[houseid][i][hItemExists])
	        return i;
	}
	return -1;
}

stock House_AddItem(houseid, item[], model, quantity = 1, slotid = -1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = House_GetFreeID(houseid);

	    if (itemid != -1)
	    {
	        if (slotid != -1)
	            itemid = slotid;

	        HouseStorage[houseid][itemid][hItemExists] = true;
	        HouseStorage[houseid][itemid][hItemModel] = model;
	        HouseStorage[houseid][itemid][hItemQuantity] = quantity;

	        strpack(HouseStorage[houseid][itemid][hItemName], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `housestorage` (`ID`, `itemName`, `itemModel`, `itemQuantity`) VALUES('%d', '%s', '%d', '%d')", HouseData[houseid][houseID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnStorageAdd", "dd", houseid, itemid);

	        return itemid;
		}
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` + %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	    mysql_tquery(sqlcon, string);

	    HouseStorage[houseid][itemid][hItemQuantity] += quantity;
	}
	return itemid;
}

stock House_RemoveItem(houseid, item[], quantity = 1)
{
    if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	new
		itemid = House_GetItemID(houseid, item),
		string[128];

	if (itemid != -1)
	{
	    if (HouseStorage[houseid][itemid][hItemQuantity] > 0)
	    {
	        HouseStorage[houseid][itemid][hItemQuantity] -= quantity;
		}
		if (quantity == -1 || HouseStorage[houseid][itemid][hItemQuantity] < 1)
		{
		    HouseStorage[houseid][itemid][hItemExists] = false;
		    HouseStorage[houseid][itemid][hItemModel] = 0;
		    HouseStorage[houseid][itemid][hItemQuantity] = 0;

		    format(string, sizeof(string), "DELETE FROM `housestorage` WHERE `ID` = '%d' AND `itemID` = '%d'", HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && HouseStorage[houseid][itemid][hItemQuantity] > 0)
		{
			format(string, sizeof(string), "UPDATE `housestorage` SET `itemQuantity` = `itemQuantity` - %d WHERE `ID` = '%d' AND `itemID` = '%d'", quantity, HouseData[houseid][houseID], HouseStorage[houseid][itemid][hItemID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

House_RemoveAllItems(houseid)
{
	static
	    query[64];

	for (new i = 0; i != MAX_HOUSE_STORAGE; i ++) {
        HouseStorage[houseid][i][hItemExists] = false;
        HouseStorage[houseid][i][hItemModel] = 0;
        HouseStorage[houseid][i][hItemQuantity] = 0;
	}
	format(query, 64, "DELETE FROM `housestorage` WHERE `ID` = '%d'", HouseData[houseid][houseID]);
	mysql_tquery(sqlcon, query);

	for (new i = 0; i < 10; i ++) {
	    HouseData[houseid][houseWeapons][i] = 0;
	    HouseData[houseid][houseAmmo][i] = 0;
	}

	for (new i = 0; i < 5; i ++) {
	    HouseData[houseid][houseClothing][i] = 0;
	}
	return 1;
}

stock GetHouseByID(sqlid)
{
	for (new i = 0; i != MAX_HOUSES; i ++) if (HouseData[i][houseExists] && HouseData[i][houseID] == sqlid)
	    return i;

	return -1;
}

Function:OnHouseCreated(houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	HouseData[houseid][houseID] = cache_insert_id();
	House_Save(houseid);

	return 1;
}

Function:OnStorageAdd(houseid, itemid)
{
	HouseStorage[houseid][itemid][hItemID] = cache_insert_id();
	return 1;
}
