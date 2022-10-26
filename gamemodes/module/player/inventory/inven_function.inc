#include <YSI\y_hooks>

Function:InventoryTD_Hide(playerid)
{
  	PlayerTextDrawHide(playerid, iNotification[playerid][0]);
	PlayerTextDrawHide(playerid, iNotification[playerid][1]);
	PlayerTextDrawHide(playerid, iNotification[playerid][2]);
	return 1;
}

stock InventoryTD_Add(playerid, modelid, name[], amount)
{
	// model id
	PlayerTextDrawSetPreviewModel(playerid, iNotification[playerid][0], modelid);

    // Item name
    new nstr[300]; 
	format(nstr, sizeof(nstr), "%s", name);
    PlayerTextDrawSetString(playerid, iNotification[playerid][1], nstr);


	// Ammount
	new astr[300];
	format(astr, sizeof(astr), "Received %dx", amount);
	PlayerTextDrawSetString(playerid, iNotification[playerid][2], astr);

  	PlayerTextDrawShow(playerid, iNotification[playerid][0]);
	PlayerTextDrawShow(playerid, iNotification[playerid][1]);
	PlayerTextDrawShow(playerid, iNotification[playerid][2]);
	SetTimerEx("InventoryTD_Hide", 7000, false, "d", playerid);
	return 1;
}

stock InventoryTD_Remove(playerid, modelid, name[], amount)
{
	// model id
	PlayerTextDrawSetPreviewModel(playerid, iNotification[playerid][0], modelid);

    // Item name
    new nstr[300]; 
	format(nstr, sizeof(nstr), "%s", name);
    PlayerTextDrawSetString(playerid, iNotification[playerid][1], nstr);


	// Ammount
	new astr[300];
	format(astr, sizeof(astr), "Remove %dx", amount);
	PlayerTextDrawSetString(playerid, iNotification[playerid][2], astr);

  	PlayerTextDrawShow(playerid, iNotification[playerid][0]);
	PlayerTextDrawShow(playerid, iNotification[playerid][1]);
	PlayerTextDrawShow(playerid, iNotification[playerid][2]);
	SetTimerEx("InventoryTD_Hide", 7000, false, "d", playerid);
	return 1;
}

Function:RefrestItemTextdraw(playerid, index)
{
	forex(i, 20)
	{
		PlayerTextDrawShow(playerid, ITEM[i][playerid]);
	}
}

stock ShowINVTD(playerid)
{
	forex(i, 10)
	{
	    TextDrawShowForPlayer(playerid, INV_TD[i]);
	}
	forex(i, 20)
	{
		PlayerTextDrawShow(playerid, ITEMTXT[i][playerid]);
		PlayerTextDrawShow(playerid, ITEM[i][playerid]);
		PlayerTextDrawShow(playerid, INVJUMLAH[playerid][i]);
	}
	PlayerTextDrawShow(playerid, INVNAME[playerid]);
	PlayerTextDrawShow(playerid, INVBAR[playerid]);
}
stock ShowInventoryTextdraw(playerid, s)
{
	if(s == 1)
	{
		PlayerData[playerid][pInventory] = 1;
		SelectTextDraw(playerid, X11_RED);
		ShowINVTD(playerid);
	} else {
		PlayerData[playerid][pInventory] = 0;
		PlayerData[playerid][pListitem] = -1;
		CancelSelectTextDraw(playerid);
		forex(i, 10)
		{
		    TextDrawHideForPlayer(playerid, INV_TD[i]);
		}
		forex(i, 20)
		{
			PlayerTextDrawHide(playerid, ITEMTXT[i][playerid]);
			PlayerTextDrawHide(playerid, ITEM[i][playerid]);
			PlayerTextDrawHide(playerid, INVJUMLAH[playerid][i]);
		}
		PlayerTextDrawHide(playerid, INVNAME[playerid]);
		PlayerTextDrawHide(playerid, INVBAR[playerid]);
	}
}

stock Inventory_Clear(playerid)
{
	static
	    string[64];

	forex(i, MAX_INVENTORY)
	{
	    if (InventoryData[playerid][i][invExists])
	    {
	        InventoryData[playerid][i][invExists] = 0;
	        InventoryData[playerid][i][invModel] = 0;
	        InventoryData[playerid][i][invQuantity] = 0;
		}
	}
	mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	return mysql_tquery(sqlcon, string);
}

stock Inventory_GetItemID(playerid, item[])
{
	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        continue;

		if (!strcmp(InventoryData[playerid][i][invItem], item)) return i;
	}
	return -1;
}

stock Inventory_GetFreeID(playerid)
{
	if (Inventory_Items(playerid) >= 20)
		return -1;

	forex(i, MAX_INVENTORY)
	{
	    if (!InventoryData[playerid][i][invExists])
	        return i;
	}
	return -1;
}

stock Inventory_Items(playerid)
{
    new count;

    forex(i, MAX_INVENTORY) if (InventoryData[playerid][i][invExists]) {
        count++;
	}
	return count;
}

stock Inventory_Count(playerid, item[])
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid != -1)
	    return InventoryData[playerid][itemid][invQuantity];

	return 0;
}

stock Inventory_HasItem(playerid, item[])
{
	return (Inventory_GetItemID(playerid, item) != -1);
}

stock Inventory_Set(playerid, item[], model, amount)
{
	new itemid = Inventory_GetItemID(playerid, item);

	if (itemid == -1 && amount > 0)
		Inventory_Add(playerid, item, model, amount);

	else if (amount > 0 && itemid != -1)
	    Inventory_SetQuantity(playerid, item, amount);

	else if (amount < 1 && itemid != -1)
	    Inventory_Remove(playerid, item, -1);

	return 1;
}

stock Inventory_SetQuantity(playerid, item[], quantity)
{
	new
	    itemid = Inventory_GetItemID(playerid, item),
	    string[128];

	if (itemid != -1)
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(sqlcon, string);

	    InventoryData[playerid][itemid][invQuantity] = quantity;
	}
	return 1;
}

stock Inventory_Remove(playerid, item[], quantity = 1)
{

	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

	InventoryTD_Remove(playerid, InventoryData[playerid][itemid][invModel], item, quantity);
	
	if (itemid != -1)
	{
	    if (InventoryData[playerid][itemid][invQuantity] > 0)
	    {
	        InventoryData[playerid][itemid][invQuantity] -= quantity;
		}
		if (quantity == -1 || InventoryData[playerid][itemid][invQuantity] < 1)
		{
		    InventoryData[playerid][itemid][invExists] = false;
		    InventoryData[playerid][itemid][invModel] = 0;
		    InventoryData[playerid][itemid][invQuantity] = 0;
		    strpack(InventoryData[playerid][itemid][invItem], "", 32 char);

		    mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `inventory` WHERE `ID` = '%d' AND `invID` = '%d'", PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	        mysql_tquery(sqlcon, string);
		}
		else if (quantity != -1 && InventoryData[playerid][itemid][invQuantity] > 0)
		{
			mysql_format(sqlcon, string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` - %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
            mysql_tquery(sqlcon, string);
		}
		return 1;
	}
	return 0;
}

stock Inventory_Add(playerid, item[], model, quantity = 1)
{
	InventoryTD_Add(playerid, model, item, quantity);

	new
		itemid = Inventory_GetItemID(playerid, item),
		string[128];

	if (itemid == -1)
	{
	    itemid = Inventory_GetFreeID(playerid);

		if(itemid >= MAX_INVENTORY) return SendErrorMessage(playerid, "Inventory mu sudah penuh");
	    if (itemid != -1)
	    {
	        InventoryData[playerid][itemid][invExists] = true;
	        InventoryData[playerid][itemid][invModel] = model;
	        InventoryData[playerid][itemid][invQuantity] = quantity;

	        strpack(InventoryData[playerid][itemid][invItem], item, 32 char);

			format(string, sizeof(string), "INSERT INTO `inventory` (`ID`, `invItem`, `invModel`, `invQuantity`) VALUES('%d', '%s', '%d', '%d')", PlayerData[playerid][pID], item, model, quantity);
			mysql_tquery(sqlcon, string, "OnInventoryAdd", "dd", playerid, itemid);
	        return itemid;
		}
		return -1;
	}
	else
	{
	    format(string, sizeof(string), "UPDATE `inventory` SET `invQuantity` = `invQuantity` + %d WHERE `ID` = '%d' AND `invID` = '%d'", quantity, PlayerData[playerid][pID], InventoryData[playerid][itemid][invID]);
	    mysql_tquery(sqlcon, string);

	    InventoryData[playerid][itemid][invQuantity] += quantity;
	}
	return itemid;
}

Function:OnInventoryAdd(playerid, itemid)
{
	InventoryData[playerid][itemid][invID] = cache_insert_id();
	return 1;
}

Function:LoadPlayerItems(playerid)
{
	new name[128];
	new count = cache_num_rows();
	if(count > 0)
	{
	    forex(i, count)
	    {
	        InventoryData[playerid][i][invExists] = true;

	        cache_get_value_name_int(i, "invID", InventoryData[playerid][i][invID]);
	        cache_get_value_name_int(i, "invModel", InventoryData[playerid][i][invModel]);
	        cache_get_value_name_int(i, "invQuantity", InventoryData[playerid][i][invQuantity]);

	        cache_get_value_name(i, "invItem", name);

			strpack(InventoryData[playerid][i][invItem], name, 32 char);
		}
	}
	return 1;
}

Function:OnPlayerUseItem(playerid, itemid, name[])
{
	if(!strcmp(name, "Snack"))
	{
        if (PlayerData[playerid][pHunger] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan makanan saat ini.");
		
		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
    	SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil camilan dan memakannya.", GetName(playerid));
       	StartPlayerProgressBarTextdraw(playerid, 100, "Memakan Snack", 50, "UseSnack", 1687547391);
	}
	else if(!strcmp(name, "Water"))
	{
        if (PlayerData[playerid][pThirst] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan minum saat ini.");

		ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil mineral air dan meminumnya.", GetName(playerid));
		StartPlayerProgressBarTextdraw(playerid, 100, "Minum Air", 50, "UseWater", 1687547391);
	}
	else if(!strcmp(name, "Milk"))
	{
		if (PlayerData[playerid][pThirst] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan minuman saat ini.");

		ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Susu dan meminumnya.", GetName(playerid));
		StartPlayerProgressBarTextdraw(playerid, 100, "Minum Susu", 50, "UseMilk", 1687547391);
	}
	/*else if(!strcmp(name, "Coffe"))
	{
		if (PlayerData[playerid][pThirst] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan minuman saat ini.");

        PlayerData[playerid][pThirst] += 15;
		Inventory_Remove(playerid, "Coffe", 1);
		ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Coffe dan meminumnya.", GetName(playerid));
	}
	else if(!strcmp(name, "Juice"))
	{
		if (PlayerData[playerid][pThirst] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan minuman saat ini.");

        PlayerData[playerid][pThirst] += 12;
		Inventory_Remove(playerid, "Juice", 1);
		ApplyAnimation(playerid, "VENDING", "VEND_DRINK2_P", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Jus dan meminumnya.", GetName(playerid));
	}
	else if(!strcmp(name, "Cigarette"))
	{
		if(PlayerData[playerid][pInjured] == 1) SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You can't do this right now.");

		SetPlayerSpecialAction(playerid,SPECIAL_ACTION_SMOKE_CIGGY);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengeluarkan cerutu dan menyalakannya.", GetName(playerid));
		Inventory_Remove(playerid, "Cigarette", 1);
	}*/
	else if(!strcmp(name, "Pizza"))
	{
		if (PlayerData[playerid][pHunger] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan makanan saat ini.");

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Pizza dan memakannya.", GetName(playerid));
		StartPlayerProgressBarTextdraw(playerid, 100, "Memakan Burger", 85, "UsePizza", 1687547391);
	}
	else if(!strcmp(name, "Burger"))
	{
		if (PlayerData[playerid][pHunger] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan makanan saat ini.");

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Burger dan memakannya.", GetName(playerid));
		StartPlayerProgressBarTextdraw(playerid, 100, "Memakan Burger", 70, "UseBurger", 1687547391);	
	}
	else if(!strcmp(name, "Fried Chicken"))
	{
		if (PlayerData[playerid][pHunger] > 90)
            return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak membutuhkan makanan saat ini.");

		ApplyAnimation(playerid, "FOOD", "EAT_Burger", 4.1, 0, 0, 0, 0, 0, 1);
        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengambil Ayam Goreng dan memakannya.", GetName(playerid));
		StartPlayerProgressBarTextdraw(playerid, 100, "Memakan Ayam Goreng", 70, "UseAyamGoreng", 1687547391);		
	}
	/*else if(!strcmp(name, "Cellphone"))
	{
		cmd_phone(playerid, "");
	}
	else if(!strcmp(name, "GPS"))
	{
		cmd_gps(playerid, "");
	}
	else if(!strcmp(name, "Driving License"))
	{
		cmd_licenses(playerid, "");
	}
	else if(!strcmp(name, "Wheat"))
	{
		cmd_sellplant(playerid, "wheat");
	}
	else if(!strcmp(name, "Mask"))
	{
		cmd_togmask(playerid, "");
	}
	else if(!strcmp(name, "Potato"))
	{
		cmd_sellplant(playerid, "potato");
	}
	else if(!strcmp(name, "9mm Silenced Schematic"))
	{
		if(Inventory_Count(playerid, "9mm Silenced Material") < 1)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki 9mm Silenced Material!");

		if(PlayerHasWeapon(playerid, 23))
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu masih membawa 9mm Silenced!");

		if(PlayerHasWeapon(playerid, 24))
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		if(PlayerHasWeapon(playerid, 22))
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu masih membawa senjata dengan jenis yang sama! (Pistol)");

		Inventory_Remove(playerid, "9mm Silenced Material", 1);
		GiveWeaponToPlayer(playerid, 23, 34, 500);
		SendServerMessage(playerid, "Successfully crafting {FF0000}9mm Silenced");
	}
	else if(!strcmp(name, "Shotgun Schematic"))
	{
		if(Inventory_Count(playerid, "Shotgun Material") < 1)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu tidak memiliki Shotgun Material!");

		if(PlayerHasWeapon(playerid, 25))
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu masih membawa Shotgun!");

		Inventory_Remove(playerid, "Shotgun Material", 1);
		GiveWeaponToPlayer(playerid, 25, 12, 500);
		SendServerMessage(playerid, "Successfully crafting {FF0000}Shotgun");
	}
	else if(!strcmp(name, "9mm Luger"))
	{
		new wep = GetWeapon(playerid);
		if(wep != 23)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You must holding 9mm Silenced!");

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]]+17 > 170)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Total peluru tidak bisa lebih dari 170!");

		PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 17;
		SetPlayerAmmo(playerid, 23, PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]]);
		PlayReloadAnimation(playerid, 23);
		PlayerPlayNearbySound(playerid, 1131);
		Inventory_Remove(playerid, "9mm Luger", 1);
	}
	else if(!strcmp(name, "12 Gauge"))
	{
		new wep = GetWeapon(playerid);
		if(wep != 25)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You must holding Shotgun!");

		if(PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]]+12 > 120)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Total peluru tidak bisa lebih dari 120!");

		PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]] += 12;
		SetPlayerAmmo(playerid, 25, PlayerData[playerid][pAmmo][g_aWeaponSlots[wep]]);
		PlayReloadAnimation(playerid, 25);
		PlayerPlayNearbySound(playerid, 1131);
		Inventory_Remove(playerid, "12 Gauge", 1);
	}
	else if(!strcmp(name, "Rolling Paper"))
	{
		if(GetPlayerState(playerid) != PLAYER_STATE_ONFOOT)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You must be on-foot!");

		if(Inventory_Count(playerid, "Weed") < 1)
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu membutuhkan 1 weed untuk membuat Rolled Weed!");

		//if(IsValidLoading(playerid))
			//return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You can't do this at the moment.");

		//SetTimerEx("Combined", 15000, false, "d", playerid);
		ApplyAnimation(playerid, "CASINO", "dealone", 4.1, 1, 0, 0, 0, 0, 1);
		Inventory_Remove(playerid, "Weed", 1);
		Inventory_Remove(playerid, "Rolling Paper", 1);
	}
	else if(!strcmp(name, "Medkit"))
	{
		if(PlayerData[playerid][pFirstAid])
			return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You already using a Medkit");

		if (ReturnHealth(playerid) > 99)
		    return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You don't need to use a medkit right now.");

		if (!IsPlayerInAnyVehicle(playerid))
		    ApplyAnimation(playerid, "SWAT", "gnstwall_injurd", 4.0, 1, 0, 0, 0, 0);

	    PlayerData[playerid][pFirstAid] = true;
	    PlayerData[playerid][pAidTimer] = SetTimerEx("FirstAidUpdate", 1000, true, "d", playerid);

	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s opens a first aid kit and uses it.", GetName(playerid));
	    Inventory_Remove(playerid, "Medkit");
	}*/
	return 1;
}

CMD:setitem(playerid, params[])
{
	new
	    userid,
		item[32],
		amount;

	if (PlayerData[playerid][pAdmin] < 6)
	    return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "You don't have permission to use this command.");

	if (sscanf(params, "uds[32]", userid, amount, item))
	    return SendSyntaxMessage(playerid, "/setitem [playerid/PartOfName] [amount] [item name]");

	for (new i = 0; i < sizeof(g_aInventoryItems); i ++) if (!strcmp(g_aInventoryItems[i][e_InventoryItem], item, true))
	{
		// if (!strcmp(item, "Cellphone", true)) {
	    //     PlayerData[userid][pPhone] = random(90000) + 10000;
	    // }
		// if (!strcmp(item, "Mask", true)){
	    // 	PlayerData[userid][pMaskcode] = PlayerData[userid][pID]+random(90000) + 10000;
	    // }
		Inventory_Set(userid, g_aInventoryItems[i][e_InventoryItem], g_aInventoryItems[i][e_InventoryModel], amount);
		return SendServerMessage(playerid, "You have set %s's \"%s\" to %d.", GetName(userid), item, amount);
	}
	SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Invalid item name (use /itemlist for a list).");
	return 1;
}

// CMD:items(playerid, params[])
// 	return cmd_inventory(playerid, params);

// CMD:inv(playerid, params[])
// 	return cmd_inventory(playerid, params);


// CMD:inventory(playerid, params[])
// {
// 	PlayerData[playerid][pStorageSelect] = 0;
// 	OpenInventory(playerid);
// 	return 1;
// }

CMD:itemlist(playerid, params[])
{
	new
	    string[1024];

	if (!strlen(string)) {
		for (new i = 0; i < sizeof(g_aInventoryItems); i ++) {
			format(string, sizeof(string), "%s%s\n", string, g_aInventoryItems[i][e_InventoryItem]);
		}
	}
	return Dialog_Show(playerid, DIALOG_NONE, DIALOG_STYLE_LIST, "List of Items", string, "Select", "Cancel");
}

Dialog:DIALOG_INVENTORY(playerid, response, listitem, inputtext[])
{
    if(response)
    {
	    new
	        name[48];//, id, str[156];
        
		strunpack(name, InventoryData[playerid][listitem][invItem]);
        PlayerData[playerid][pListitem] = listitem;

        if(InventoryData[playerid][listitem][invQuantity] < 1)
        	return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Tidak ada item di slot yang dipilih!");
		switch (PlayerData[playerid][pStorageSelect])
		{
		    case 0:
		    {
	            format(name, sizeof(name), "%s (%d)", name, InventoryData[playerid][listitem][invQuantity]);
	            Dialog_Show(playerid, DIALOG_INVACTION, DIALOG_STYLE_LIST, name, "Use Item\nGive Item\nDrop Item", "Select", "Cancel");
			}
			/*case 1:
			{
		    	if ((id = House_Inside(playerid)) != -1 && House_IsOwner(playerid, id))
				{
				    if(!strcmp(name, "Cellphone"))
				        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", name);
				    if(!strcmp(name, "GPS"))
				        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", name);
				    if(!strcmp(name, "Portable Radio"))
				        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", name);
				    if(!strcmp(name, "Mask"))
				        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", name);
				        
					if (InventoryData[playerid][listitem][invQuantity] == 1)
					{
		        		House_AddItem(id, name, InventoryData[playerid][listitem][invModel], 1);
		        		Inventory_Remove(playerid, name);
		        		
		        		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s has stored a \"%s\" into their house storage.", GetName(playerid), name);
				 		House_ShowItems(playerid, id);
					}
					else
					{
						format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", name, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
						Dialog_Show(playerid, DIALOG_HOUSEDEPOSIT, DIALOG_STYLE_INPUT, "House Deposit", str, "Deposit", "Close");
					}
				}
			}*/
		}
	}
	return 1;
}

/*Dialog:DIALOG_HOUSEDEPOSIT(playerid, response, listitem, inputtext[])
{
    new
        houseid = House_Inside(playerid),
        string[32];

    strunpack(string, InventoryData[playerid][PlayerData[playerid][pListitem]][invItem]);
    
	if (response)
	{
		new amount = strval(inputtext);
		if (amount < 1 || amount > InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity])
		{
		    new str[152];
		    format(str, sizeof(str), "Item: %s (Amount: %d)\n\nPlease enter the quantity that you wish to store for this item:", string, InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity]);
			Dialog_Show(playerid, DIALOG_HOUSEDEPOSIT, DIALOG_STYLE_INPUT, "House Deposit", str, "Store", "Back");
			return 1;
		}
		House_AddItem(houseid, string, InventoryData[playerid][PlayerData[playerid][pListitem]][invModel], amount);
		Inventory_Remove(playerid, string, amount);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s has stored a \"%s\" into their house storage.", GetName(playerid), string);
		House_ShowItems(playerid, houseid);
	}
	else House_OpenStorage(playerid, houseid);
}*/
Dialog:DIALOG_INVACTION(playerid, response, listitem, inputtext[])
{
    if(response)
    {
	    new
			itemid = PlayerData[playerid][pListitem],
			string[64],
			str[256];
	    strunpack(string, InventoryData[playerid][itemid][invItem]);
	    switch (listitem)
	    {
	        case 0:
	        {
	            CallLocalFunction("OnPlayerUseItem", "dds", playerid, itemid, string);
	        }
	        case 1:
	        {
			    if(!strcmp(string, "Cellphone"))
			        return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));
		//	    if(!strcmp(string, "GPS"))
			//        return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
			    if(!strcmp(string, "Portable Radio"))
			        return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));
		//	    if(!strcmp(string, "Mask"))
			  //      return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
				PlayerData[playerid][pListitem] = itemid;
				Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "Silakan masukkan nama atau ID pemain:", "Submit", "Cancel");
	        }
	        case 2:
	        {
	            if (IsPlayerInAnyVehicle(playerid))
	                return SendErrorMessage(playerid, "Anda tidak dapat membuang item sekarang.");
			    if(!strcmp(string, "Cellphone"))
			        return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));
			 //   if(!strcmp(string, "GPS"))
			 //       return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
			    if(!strcmp(string, "Portable Radio"))
			        return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));
			//    if(!strcmp(string, "Mask"))
			   //     return SendErrorMessage(playerid, "You can't do that on this item! (%s)", string);
				else if (InventoryData[playerid][itemid][invQuantity] == 1)
				{
					DropPlayerItem(playerid, itemid);
				}
				else
					format(str, sizeof(str), "Item: %s - Quantity: %d\n\nHarap tentukan berapa banyak item ini yang ingin Anda drop:", string, InventoryData[playerid][itemid][invQuantity]),
					Dialog_Show(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "Drop Item", str, "Drop", "Cancel");
			}
		}
	}
	return 1;
}

Dialog:DIALOG_DROPITEM(playerid, response, listitem, inputtext[])
{
    if(response)
    {
		new
		    itemid = PlayerData[playerid][pListitem],
		    string[32],
			str[356];
		strunpack(string, InventoryData[playerid][itemid][invItem]);
		if (response)
		{
		    if (isnull(inputtext))
		        return format(str, sizeof(str), "Drop Item", "Item: %s - Quantity: %d\n\nHarap tentukan berapa banyak item ini yang ingin Anda Drop:", string, InventoryData[playerid][itemid][invQuantity]),
				Dialog_Show(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "DROP", str, "Drop", "Cancel");
			if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
			    return format(str, sizeof(str), "ERROR: Jumlah yang tidak mencukupi yang ditentukan.\n\nItem: %s - Kuantitas: %d\n\nSilakan tentukan berapa banyak item ini yang ingin Anda drop:", string, InventoryData[playerid][itemid][invQuantity]),
				Dialog_Show(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "DROP", str, "Drop", "Cancel");
		
			DropPlayerItem(playerid, itemid, strval(inputtext));
		}
	}
	return 1;
}

Dialog:DIALOG_GIVEITEM(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    static
	        userid = -1,
			itemid = -1,
			string[32];
		if (sscanf(inputtext, "u", userid))
		    return Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "Silakan masukkan nama atau ID pemain:", "Submit", "Cancel");
		if (userid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "ERROR: Pemain yang ditentukan tidak valid.\n\nSilakan masukkan nama atau ID pemain:", "Submit", "Cancel");
	    if (!IsPlayerNearPlayer(playerid, userid, 6.0))
			return Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "ERROR: Anda tidak berada di dekat pemain itu.\n\nSilakan masukkan nama atau ID pemain:", "Submit", "Cancel");
	    if (userid == playerid)
			return Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "ERROR: Anda tidak dapat memberikan item untuk diri sendiri.\n\nSilakan masukkan nama atau ID pemain:", "Submit", "Cancel");
		itemid = PlayerData[playerid][pListitem];
		if (itemid == -1)
		    return 0;
		strunpack(string, InventoryData[playerid][itemid][invItem]);
		if (InventoryData[playerid][itemid][invQuantity] == 1)
		{
		    new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel]);
		    if (id == -1)
				return SendErrorMessage(playerid, "Slot Inventory player tersebut FULL.");
		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengeluarkan %s dan memberikannya kepada %s.", GetName(playerid), string, GetName(userid));
		    SendServerMessage(userid, "%s telah memberi Anda %s (ditambahkan ke inventory).", GetName(playerid), string);
			Inventory_Remove(playerid, string);
		    //Log_Write("logs/give_log.txt", "[%s] %s (%s) has given a %s to %s (%s).", ReturnDate(), GetName(playerid), PlayerData[playerid][pIP], string, GetName(userid, 0), PlayerData[userid][pIP]);
  		}
		else
		{
			new str[152];
			format(str, sizeof(str), "Item: %s (Amount: %d)\n\nSilakan masukkan jumlah item ini yang ingin Anda berikan %s:", string, InventoryData[playerid][itemid][invQuantity], GetName(userid));
		    Dialog_Show(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "GIVE", str, "Give", "Cancel");
		    PlayerData[playerid][pTarget] = userid;
		}
	}
	return 1;
}

Dialog:DIALOG_GIVEAMOUNT(playerid, response, listitem, inputtext[])
{
	if (response && PlayerData[playerid][pTarget] != INVALID_PLAYER_ID)
	{
	    new
	        userid = PlayerData[playerid][pTarget],
	        itemid = PlayerData[playerid][pListitem],
			string[32],
			str[352];
		strunpack(string, InventoryData[playerid][itemid][invItem]);
		if (isnull(inputtext))
			return format(str, sizeof(str), "Item: %s (Amount: %d)\n\nSilakan masukkan jumlah item ini yang ingin Anda berikan %s:", string, InventoryData[playerid][itemid][invQuantity], GetName(userid)),
			Dialog_Show(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "GIVE", str, "Give", "Cancel");
		if (strval(inputtext) < 1 || strval(inputtext) > InventoryData[playerid][itemid][invQuantity])
		    return format(str, sizeof(str), "ERROR: Anda tidak memiliki sebanyak itu.\n\nItem: %s (Jumlah: %d)nnSilakan masukkan jumlah item ini yang ingin Anda berikan %s:", string, InventoryData[playerid][itemid][invQuantity], GetName(userid)),
			Dialog_Show(playerid, DIALOG_GIVEAMOUNT, DIALOG_STYLE_INPUT, "GIVE", str, "Give", "Cancel");
        new id = Inventory_Add(userid, string, InventoryData[playerid][itemid][invModel], strval(inputtext));
	    if (id == -1)
			return SendErrorMessage(playerid, "Slot Inventory player tersebut FULL.");
	    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s mengeluarkan %s  dan memberikannya kepada %s.", GetName(playerid), string, GetName(userid));
	    SendServerMessage(userid, "%s telah memberi Anda  %s  (ditambahkan ke inventory).", GetName(playerid), string);
		Inventory_Remove(playerid, string, strval(inputtext));
	  //  Log_Write("logs/give_log.txt", "[%s] %s (%s) has given %d %s to %s (%s).", ReturnDate(), GetName(playerid), PlayerData[playerid][pIP], strval(inputtext), string, GetName(userid, 0), PlayerData[userid][pIP]);
	}
	return 1;
}

Dialog:DIALOG_PICKITEM(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    new id = NearestItems[playerid][listitem];
		if (id != -1 && DroppedItems[id][droppedModel])
		{
			if(PickupItem(playerid, id))
			{
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah mengambil %s", GetName(playerid), DroppedItems[id][droppedItem]);
			}
			else
				SendErrorMessage(playerid, "Anda tidak memiliki slot di inventaris Anda.");
		}
		else SendErrorMessage(playerid, "Item ini sudah diambil.");
	}
	return 1;
}

stock FriskInventory(playerid, targetID)
{
    if (!IsPlayerConnected(playerid))
	    return 0;

	new
		amounts[MAX_INVENTORY],
		str[712],
		string[256];

	format(str, sizeof(str), "Slot\tName\tAmount\n");
    forex(i, MAX_INVENTORY)
	{
		new count;
	    if (!InventoryData[playerid][i][invExists])
	        format(str, sizeof(str), "%s"LIGHTGREEN"#%d\t"YELLOW"{AFAFAF}Slot Kosong\t-\n", str, i + 1);

		else
		{
			amounts[i] = InventoryData[playerid][i][invQuantity];
			strunpack(string, InventoryData[playerid][i][invItem]);
			format(str, sizeof(str), "%s"LIGHTGREEN"#%d\t"YELLOW"%s\t%d\n", str, i + 1, string, amounts[i]);
		}
		for (new ix = 0; ix < MAX_INVENTORY; ix ++) if (InventoryData[playerid][ix][invExists])
		{
			count++;
			format(gstr, sizeof(gstr), ""ALICEBLUE"Frisk Inventory (%d/%d)", count, MAX_INVENTORY);
		}
	}
	Dialog_Show(targetID, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, gstr, str, "Close", "");
	return 1;
}

stock GetPlayerIDs(playername[])
{
	new playa = -1;
	sscanf(playername, "u", playa);

	if(playa == -1) return INVALID_PLAYER_ID;
	else return playa;
}

hook OnPlayerClickTextDraw(playerid, Text:clickedid)
{
	if(clickedid == INV_TD[9])
	{
		ShowInventoryTextdraw(playerid, 0);
		CancelSelectTextDraw(playerid);
	}
	if(clickedid == INV_TD[8])
	{
		new
			itemid = PlayerData[playerid][pListitem],
			string[64],
			str[256];
		
	    strunpack(string, InventoryData[playerid][itemid][invItem]);

		if (IsPlayerInAnyVehicle(playerid))
		    return SendErrorMessage(playerid, "You can't drop items right now.");

		if(!strcmp(string, "Cellphone"))
	        return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "GPS"))
			return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "Portable Radio"))
			return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "Mask"))
			 return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		else if (InventoryData[playerid][itemid][invQuantity] == 1)
		{
			DropPlayerItem(playerid, itemid);
		}
		else
			format(str, sizeof(str), "Item: %s - Quantity: %d\n\nHarap tentukan berapa banyak item ini yang ingin Anda jatuhkan:", string, InventoryData[playerid][itemid][invQuantity]),
			Dialog_Show(playerid, DIALOG_DROPITEM, DIALOG_STYLE_INPUT, "DROP", str, "Drop", "Cancel");
	}
	if(clickedid == INV_TD[6])
	{
		new
			itemid = PlayerData[playerid][pListitem],
			string[64];

		strunpack(string, InventoryData[playerid][itemid][invItem]);

		CallLocalFunction("OnPlayerUseItem", "dds", playerid, itemid, string);
	}
	if(clickedid == INV_TD[7])
	{
		new
			itemid = PlayerData[playerid][pListitem],
			string[64];

		strunpack(string, InventoryData[playerid][itemid][invItem]);

		if(!strcmp(string, "Cellphone"))
			return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "GPS"))
			 return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "Portable Radio"))
			return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		if(!strcmp(string, "Mask"))
			return SendErrorMessage(playerid, sprintf("Anda tidak dapat melakukannya pada item ini! (%s)", string));

		PlayerData[playerid][pListitem] = itemid;
		Dialog_Show(playerid, DIALOG_GIVEITEM, DIALOG_STYLE_INPUT, "GIVE", "Silakan masukkan nama atau ID pemain:", "Submit", "Cancel");
	}
	return 1;
}