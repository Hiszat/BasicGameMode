stock Item_Delete(itemid)
{
    new query[450];
    if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
        DroppedItems[itemid][droppedModel] = 0;
		DroppedItems[itemid][droppedQuantity] = 0;
	    DroppedItems[itemid][droppedPos][0] = 0.0;
	    DroppedItems[itemid][droppedPos][1] = 0.0;
	    DroppedItems[itemid][droppedPos][2] = 0.0;
	    DroppedItems[itemid][droppedInt] = 0;
	    DroppedItems[itemid][droppedWorld] = 0;

	  //  DestroyDynamicObject(DroppedItems[itemid][droppedObject]);
	  	if(DroppedItems[itemid][droppedObject] != INVALID_OBJECT_ID) DestroyDynamicObject(DroppedItems[itemid][droppedObject]);
		DroppedItems[itemid][droppedObject] = INVALID_OBJECT_ID;
	 //   DestroyDynamic3DTextLabel(DroppedItems[itemid][droppedText3D]);
		if(DroppedItems[itemid][droppedText3D] != Text3D:INVALID_3DTEXT_ID) DestroyDynamic3DTextLabel(DroppedItems[itemid][droppedText3D]);
		DroppedItems[itemid][droppedText3D] = Text3D:INVALID_3DTEXT_ID;

	    mysql_format(sqlcon, query, sizeof(query), "DELETE FROM `dropped` WHERE `ID` = '%d'", DroppedItems[itemid][droppedID]);
	    mysql_tquery(sqlcon, query);
	}
	return 1;
}

stock Item_Nearest(playerid)
{
    for (new i = 0; i != MAX_DROPPED_ITEMS; i ++) if (DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]))
	{
	    if (GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld])
	        return i;
	}
	return -1;
}

stock PickupItem(playerid, itemid)
{
	if (itemid != -1 && DroppedItems[itemid][droppedModel])
	{
	    new id = Inventory_Add(playerid, DroppedItems[itemid][droppedItem], DroppedItems[itemid][droppedModel], DroppedItems[itemid][droppedQuantity]);

	    if (id == -1)
	        return SendErrorMessage(playerid, "Slot Inventory kamu FULL.");

	    Item_Delete(itemid);
	}
	return 1;
}

Function:Dropped_Load()
{
	new rows = cache_num_rows(), str[350];
 	if(rows)
  	{
    	forex(i, rows)
		{
		    cache_get_value_name_int(i, "ID", DroppedItems[i][droppedID]);

			cache_get_value_name(i, "itemName", DroppedItems[i][droppedItem]);
			cache_get_value_name(i, "itemPlayer", DroppedItems[i][droppedPlayer]);

			cache_get_value_name_int(i, "itemModel", DroppedItems[i][droppedModel]);
			cache_get_value_name_int(i, "itemQuantity", DroppedItems[i][droppedQuantity]);
			cache_get_value_name_float(i, "itemX", DroppedItems[i][droppedPos][0]);
			cache_get_value_name_float(i, "itemY", DroppedItems[i][droppedPos][1]);
			cache_get_value_name_float(i, "itemZ", DroppedItems[i][droppedPos][2]);
			cache_get_value_name_int(i, "itemInt", DroppedItems[i][droppedInt]);
			cache_get_value_name_int(i, "itemWorld", DroppedItems[i][droppedWorld]);

			DroppedItems[i][droppedObject] = CreateDynamicObject(DroppedItems[i][droppedModel], DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 0.0, 0.0, 0.0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
			format(str, sizeof(str), "[%s]\nquantity: %d", DroppedItems[i][droppedItem], DroppedItems[i][droppedQuantity]);
			DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(str, X11_LIGHTBLUE, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, DroppedItems[i][droppedWorld], DroppedItems[i][droppedInt]);
		}
		printf("[DROPITEM] Loaded %d Dropped items from database.", rows);
	}
	return 1;
}

DropItem(item[], player[], model, quantity, Float:x, Float:y, Float:z, interior, world, weaponid = 0, ammo = 0)
{
	new
	   query[300], str[350];

	forex(i, MAX_DROPPED_ITEMS) if (!DroppedItems[i][droppedModel])
	{
	    format(DroppedItems[i][droppedItem], 32, item);
	    format(DroppedItems[i][droppedPlayer], 24, player);

		DroppedItems[i][droppedModel] = model;
		DroppedItems[i][droppedQuantity] = quantity;
		DroppedItems[i][droppedWeapon] = weaponid;
  		DroppedItems[i][droppedAmmo] = ammo;
		DroppedItems[i][droppedPos][0] = x;
		DroppedItems[i][droppedPos][1] = y;
		DroppedItems[i][droppedPos][2] = z;

		DroppedItems[i][droppedInt] = interior;
		DroppedItems[i][droppedWorld] = world;

		DroppedItems[i][droppedObject] = CreateDynamicObject(model, x, y, z, 0.0, 0.0, 0.0, world, interior);

		format(str, sizeof(str), "[%s]\nquantity: %d", item, quantity);
 		DroppedItems[i][droppedText3D] = CreateDynamic3DTextLabel(str, X11_LIGHTBLUE, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, world, interior);

 		format(query, sizeof(query), "INSERT INTO `dropped` (`itemName`, `itemPlayer`, `itemModel`, `itemQuantity`, `itemWeapon`, `itemAmmo`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`) VALUES('%s', '%s', '%d', '%d', '%d', '%d', '%.4f', '%.4f', '%.4f', '%d', '%d')", item, player, model, quantity, weaponid, ammo, x, y, z, interior, world);
		mysql_tquery(sqlcon, query, "OnDroppedItem", "d", i);
		return i;
	}
	return -1;
}

Function:OnDroppedItem(itemid)
{
	if (itemid == -1 || !DroppedItems[itemid][droppedModel])
	    return 0;

	DroppedItems[itemid][droppedID] = cache_insert_id();
	return 1;
}

DropPlayerItem(playerid, itemid, quantity = 1)
{
	if (itemid == -1 || !InventoryData[playerid][itemid][invExists])
	    return 0;

    new
		Float:x,
  		Float:y,
    	Float:z,
		Float:angle,
		string[32];

	strunpack(string, InventoryData[playerid][itemid][invItem]);

	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, angle);

	DropItem(string, GetName(playerid), InventoryData[playerid][itemid][invModel], quantity, x, y, z - 0.9, GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
 	Inventory_Remove(playerid, string, quantity);

	ApplyAnimation(playerid, "GRENADE", "WEAPON_throwu", 4.1, 0, 0, 0, 0, 0, 1);
 	SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "> %s menaruh %s lalu membuangnya.", GetName(playerid), string);
	return 1;
}
