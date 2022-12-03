// pshipment belum di tambah PR untuk update selajutnya
Function:KickBusiness(playerid, id)
{
	// if (GetFactionType(playerid) != FACTION_POLICE || Business_Nearest(playerid) != id)
	//     return 0;

    if (Business_Nearest(playerid) != id)
	    return 0;

	switch (random(6))
	{
	    case 0..2:
	    {
            SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Anda telah ~r~gagal~w~ untuk menendang pintu ke bawah.");
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah gagal untuk menendang pintu ke bawah.", ReturnName(playerid, 0));
		}
		default:
		{
		    BusinessData[id][bizLocked] = 0;
		    Business_Save(id);

		    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah berhasil menendang pintu ke bawah.", ReturnName(playerid, 0));
		    SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Tekan ~y~'F'~w~ untuk masuk ke bisnis.");
		}
	}
	return 1;
}

stock IsPumpOccupied(pumpid)
{
	foreach (new i : Player) if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID) {
	    if (PlayerData[i][pGasPump] == pumpid) return 1;
	}
	return 0;
}

StopRefilling(playerid)
{
    PlayerData[playerid][pGasPump] = -1;
    PlayerData[playerid][pGasStation] = -1;
   	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
}

Pump_Nearest(playerid)
{
    for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && IsPlayerInRangeOfPoint(playerid, 4.0, PumpData[i][pumpPos][0], PumpData[i][pumpPos][1], PumpData[i][pumpPos][2]) && PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

GetClosestBusiness(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizType] == type && GetPlayerInterior(playerid) == BusinessData[i][bizExterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][bizExteriorVW])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

forward Business_Load();
public Business_Load()
{
    static
		str[64];

	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            BusinessData[i][bizExists] = true;
            cache_get_value_name_int(i, "bizID", BusinessData[i][bizID]);

            cache_get_value_name(i, "bizName", BusinessData[i][bizName]);
            cache_get_value_name(i, "bizMessage", BusinessData[i][bizMessage]);

            cache_get_value_name_int(i, "bizOwner", BusinessData[i][bizOwner]);
            cache_get_value_name_int(i, "bizType", BusinessData[i][bizType] );
            cache_get_value_name_int(i, "bizPrice", BusinessData[i][bizPrice]);
            cache_get_value_name_float(i, "bizPosX", BusinessData[i][bizPos][0]);
            cache_get_value_name_float(i, "bizPosY", BusinessData[i][bizPos][1]);
            cache_get_value_name_float(i, "bizPosZ", BusinessData[i][bizPos][2]);
            cache_get_value_name_float(i, "bizPosA", BusinessData[i][bizPos][3]);
            cache_get_value_name_float(i, "bizIntX", BusinessData[i][bizActorPosition][0]);
            cache_get_value_name_float(i, "bizIntY", BusinessData[i][bizActorPosition][1]);
            cache_get_value_name_float(i, "bizIntZ", BusinessData[i][bizActorPosition][2]);
            cache_get_value_name_float(i, "bizIntA", BusinessData[i][bizActorPosition][3]);
            cache_get_value_name_float(i, "bizSpawnX", BusinessData[i][bizSpawn][0]);
            cache_get_value_name_float(i, "bizSpawnY", BusinessData[i][bizSpawn][1]);
            cache_get_value_name_float(i, "bizSpawnZ", BusinessData[i][bizSpawn][2]);
            cache_get_value_name_float(i, "bizSpawnA", BusinessData[i][bizSpawn][3]);
            cache_get_value_name_float(i, "bizDeliverX", BusinessData[i][bizDeliver][0]);
            cache_get_value_name_float(i, "bizDeliverY", BusinessData[i][bizDeliver][1]);
            cache_get_value_name_float(i, "bizDeliverZ", BusinessData[i][bizDeliver][2]);
            cache_get_value_name_int(i, "bizShipment", BusinessData[i][bizShipment]);
            cache_get_value_name_int(i, "bizInterior", BusinessData[i][bizInterior]);
            cache_get_value_name_int(i, "bizExterior", BusinessData[i][bizExterior]);
            cache_get_value_name_int(i, "bizExteriorVW", BusinessData[i][bizExteriorVW]);
            cache_get_value_name_int(i, "bizLocked", BusinessData[i][bizLocked]);
            cache_get_value_name_int(i, "bizVault", BusinessData[i][bizVault]);
            cache_get_value_name_int(i, "bizProducts", BusinessData[i][bizProducts]);

            for (new j = 0; j < 20; j ++)
            {
                format(str, 32, "bizPrice%d", j + 1);
                cache_get_value_name_int(i, str, BusinessData[i][bizPrices][j]);
            }
            Business_Refresh(i);
        }
    }
	for (new i = 0; i < MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists])
	{
		if (BusinessData[i][bizType] == 6) {
			format(str, sizeof(str), "SELECT * FROM `pumps` WHERE `ID` = '%d'", BusinessData[i][bizID]);

			mysql_tquery(sqlcon, str, "Pump_Load", "d", i);
		}
	}
    printf("[BUSINESS] Loaded %d Business from database.", rows);
	return 1;
}

Business_GetCount(playerid)
{
	new
		count = 0;

	for (new i = 0; i != MAX_BUSINESSES; i ++)
	{
		if (BusinessData[i][bizExists] && Business_IsOwner(playerid, i))
   		{
   		    count++;
		}
	}
	return count;
}

Function:Pump_Load(bizid)
{
	static
		id = -1;

	new rows = cache_num_rows();

	for (new i = 0; i < rows; i ++) if ((id = Pump_GetFreeID()) != -1)
	{
	    PumpData[id][pumpExists] = true;
	    PumpData[id][pumpBusiness] = bizid;
        cache_get_value_name_int(i, "pumpID", PumpData[id][pumpID]);
	    cache_get_value_name_float(i, "pumpPosX", PumpData[id][pumpPos][0]);
	    cache_get_value_name_float(i, "pumpPosY", PumpData[id][pumpPos][1]);
	    cache_get_value_name_float(i, "pumpPosZ", PumpData[id][pumpPos][2]);
	    cache_get_value_name_float(i, "pumpPosA", PumpData[id][pumpPos][3]);
	    cache_get_value_name_int(i, "pumpFuel", PumpData[id][pumpFuel]);

	    PumpData[id][pumpObject] = CreateDynamicObject(1676, PumpData[id][pumpPos][0], PumpData[id][pumpPos][1], PumpData[id][pumpPos][2], 0.0, 0.0, PumpData[id][pumpPos][3]);
	    Pump_Refresh(id);
	}
	return 1;
}

Pump_GetFreeID()
{
	for (new i = 0; i < MAX_GAS_PUMPS; i ++) if (!PumpData[i][pumpExists]) {
	    return i;
	}
	return -1;
}

Pump_Delete(pumpid)
{
	if (pumpid != -1 && PumpData[pumpid][pumpExists])
	{
	    new
	        string[90];

		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `ID` = '%d' AND `pumpID` = '%d'", BusinessData[PumpData[pumpid][pumpBusiness]][bizID], PumpData[pumpid][pumpID]);
		mysql_tquery(sqlcon, string);

        if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D]))
		    DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);

		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]))
		    DestroyDynamicObject(PumpData[pumpid][pumpObject]);

		foreach (new i : Player) if (PlayerData[i][pGasPump] == pumpid) {
		    StopRefilling(i);
		}
	    PumpData[pumpid][pumpExists] = false;
	    PumpData[pumpid][pumpFuel] = 0;
	}
	return 1;
}

Pump_Create(playerid, bizid)
{
    static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle,
		string[64],
		id = -1;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		if ((id = Pump_GetFreeID()) != -1)
  		{
	        x += 5.0 * floatsin(-angle, degrees);
	        y += 5.0 * floatcos(-angle, degrees);

			PumpData[id][pumpExists] = true;
			PumpData[id][pumpBusiness] = bizid;
			PumpData[id][pumpPos][0] = x;
			PumpData[id][pumpPos][1] = y;
			PumpData[id][pumpPos][2] = z;
			PumpData[id][pumpPos][3] = angle;
            PumpData[id][pumpFuel] = 2000;
			PumpData[id][pumpObject] = CreateDynamicObject(1676, x, y, z, 0.0, 0.0, angle);

			format(string, sizeof(string), "INSERT INTO `pumps` (`ID`) VALUES(%d)", BusinessData[bizid][bizID]);
			mysql_tquery(sqlcon, string, "OnPumpCreated", "d", id);
			return id;
		}
	}
	return -1;
}

Pump_Refresh(pumpid)
{
	if (pumpid != -1 && PumpData[pumpid][pumpExists])
	{
	    static
	        string[128];

		format(string, sizeof(string), "[Gas Pump: %d]\n{FFFFFF}Fuel Left: %d liters", pumpid, PumpData[pumpid][pumpFuel]);

        if (IsValidDynamic3DTextLabel(PumpData[pumpid][pumpText3D]))
            DestroyDynamic3DTextLabel(PumpData[pumpid][pumpText3D]);

		if (IsValidDynamicObject(PumpData[pumpid][pumpObject]))
		    DestroyDynamicObject(PumpData[pumpid][pumpObject]);

		PumpData[pumpid][pumpText3D] = CreateDynamic3DTextLabel(string, X11_LIGHTBLUE, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 15.0);
        PumpData[pumpid][pumpObject] = CreateDynamicObject(1676, PumpData[pumpid][pumpPos][0], PumpData[pumpid][pumpPos][1], PumpData[pumpid][pumpPos][2], 0.0, 0.0, PumpData[pumpid][pumpPos][3]);
	}
	return 1;
}

Pump_Save(pumpid)
{
	static
	    query[256];

	format(query, sizeof(query), "UPDATE `pumps` SET `pumpPosX` = '%.4f', `pumpPosY` = '%.4f', `pumpPosZ` = '%.4f', `pumpPosA` = '%.4f', `pumpFuel` = '%d' WHERE `ID` = '%d' AND `pumpID` = '%d'",
	    PumpData[pumpid][pumpPos][0],
	    PumpData[pumpid][pumpPos][1],
	    PumpData[pumpid][pumpPos][2],
		PumpData[pumpid][pumpPos][3],
	    PumpData[pumpid][pumpFuel],
	    BusinessData[PumpData[pumpid][pumpBusiness]][bizID],
	    PumpData[pumpid][pumpID]
	);
	return mysql_tquery(sqlcon, query);
}

Business_ProductMenu(playerid, bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	static
	    string[512];

	switch (BusinessData[bizid][bizType])
	{
	    case 1, 6:
	    {
			format(string, sizeof(string), "Mobile Phone - %s\nGPS System - %s\nSpray Paint - %s\nBackpack - %s\nWater Bottle - %s\nSoda Bottle - %s\nLottery Ticket - %s\nPortable Radio - %s\nCan of Fuel - %s\nCrowbar - %s\nBoombox - %s\nMask - %s\nFirst Aid Kit - %s\nRepair Kit - %s\nNOS Canister - %s\nBaseball Bat - %s\nFrozen Pizza - %s\nFrozen Burger - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6]),
				FormatNumber(BusinessData[bizid][bizPrices][7]),
				FormatNumber(BusinessData[bizid][bizPrices][8]),
				FormatNumber(BusinessData[bizid][bizPrices][9]),
				FormatNumber(BusinessData[bizid][bizPrices][10]),
				FormatNumber(BusinessData[bizid][bizPrices][11]),
				FormatNumber(BusinessData[bizid][bizPrices][12]),
				FormatNumber(BusinessData[bizid][bizPrices][13]),
				FormatNumber(BusinessData[bizid][bizPrices][14]),
				FormatNumber(BusinessData[bizid][bizPrices][15]),
				FormatNumber(BusinessData[bizid][bizPrices][16]),
				FormatNumber(BusinessData[bizid][bizPrices][17])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 2:
	    {
			format(string, sizeof(string), "Magazine - %s\nAmmo Cartridge - %s\nArmored Vest - %s\nDesert Eagle - %s\nRemington 870 - %s\nM14 Rifle - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 3:
	    {
			format(string, sizeof(string), "Clothes - %s\nGlasses - %s\nHats - %s\nBandana - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 4:
	    {
			format(string, sizeof(string), "Water - %s\nSoda - %s\nFrench Fries - %s\nCheeseburger - %s\nChicken Burger - %s\nChicken Nuggets - %s\nSalad - %s",
    			FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6])
			);
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
		case 7:
	    {
	        string[0] = 0;

	        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
	            format(string, sizeof(string), "%s%s - %s\n", string, g_aFurnitureTypes[i], FormatNumber(BusinessData[bizid][bizPrices][i]));
			}
			Dialog_Show(playerid, EditProduct, DIALOG_STYLE_LIST, "Business: Modify Item", string, "Modify", "Cancel");
		}
	}
	return 1;
}

Business_PurchaseMenu(playerid, bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	static
	    string[512];

	switch (BusinessData[bizid][bizType])
	{
	    case 1, 6:
	    {
			format(string, sizeof(string), "Nama Barang\tHarga Barang\nSmartphone\t%s\nEs Teh\t%s\nBurger\t%s\nRokok\t%s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_TABLIST_HEADERS, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 2:
	    {
			format(string, sizeof(string), "Magazine - %s\nAmmo Cartridge - %s\nArmored Vest - %s\nDesert Eagle - %s\nRemington 870 - %s\nM14 Rifle - %s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 3:
	    {
			format(string, sizeof(string), "Nama Barang\tHarga Barang\nClothes\t%s\nToys\nBaju Baru\t%s",
				FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_TABLIST_HEADERS, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 4:
		{
            format(string, sizeof(string), "Water - %s\nSoda - %s\nFrench Fries - %s\nCheeseburger - %s\nChicken Burger - %s\nChicken Nuggets - %s\nSalad - %s",
    			FormatNumber(BusinessData[bizid][bizPrices][0]),
				FormatNumber(BusinessData[bizid][bizPrices][1]),
				FormatNumber(BusinessData[bizid][bizPrices][2]),
				FormatNumber(BusinessData[bizid][bizPrices][3]),
				FormatNumber(BusinessData[bizid][bizPrices][4]),
				FormatNumber(BusinessData[bizid][bizPrices][5]),
				FormatNumber(BusinessData[bizid][bizPrices][6])
			);
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
		case 7:
	    {
	        string[0] = 0;

	        for (new i = 0; i < sizeof(g_aFurnitureTypes); i ++) {
	            format(string, sizeof(string), "%s%s - %s\n", string, g_aFurnitureTypes[i], FormatNumber(BusinessData[bizid][bizPrices][i]));
			}
			Dialog_Show(playerid, BusinessBuy, DIALOG_STYLE_LIST, BusinessData[bizid][bizName], string, "Purchase", "Cancel");
		}
	}
	return 1;
}

Business_Save(bizid)
{
	static
	    query[2048];

	format(query, sizeof(query), "UPDATE `businesses` SET `bizName` = '%s', `bizMessage` = '%s', `bizOwner` = '%d', `bizType` = '%d', `bizPrice` = '%d', `bizPosX` = '%.4f', `bizPosY` = '%.4f', `bizPosZ` = '%.4f', `bizPosA` = '%.4f', `bizIntX` = '%.4f', `bizIntY` = '%.4f', `bizIntZ` = '%.4f', `bizIntA` = '%.4f', `bizInterior` = '%d', `bizExterior` = '%d', `bizExteriorVW` = '%d', `bizLocked` = '%d', `bizVault` = '%d', `bizProducts` = '%d'",
		BusinessData[bizid][bizName],
		BusinessData[bizid][bizMessage],
		BusinessData[bizid][bizOwner],
		BusinessData[bizid][bizType],
		BusinessData[bizid][bizPrice],
		BusinessData[bizid][bizPos][0],
		BusinessData[bizid][bizPos][1],
		BusinessData[bizid][bizPos][2],
		BusinessData[bizid][bizPos][3],
		BusinessData[bizid][bizActorPosition][0],
		BusinessData[bizid][bizActorPosition][1],
		BusinessData[bizid][bizActorPosition][2],
		BusinessData[bizid][bizActorPosition][3],
		BusinessData[bizid][bizInterior],
		BusinessData[bizid][bizExterior],
		BusinessData[bizid][bizExteriorVW],
		BusinessData[bizid][bizLocked],
		BusinessData[bizid][bizVault],
		BusinessData[bizid][bizProducts]
	);
	for (new i = 0; i < 20; i ++) {
		format(query, sizeof(query), "%s, `bizPrice%d` = '%d'", query, i + 1, BusinessData[bizid][bizPrices][i]);
	}
	format(query, sizeof(query), "%s, `bizSpawnX` = '%.4f', `bizSpawnY` = '%.4f', `bizSpawnZ` = '%.4f', `bizSpawnA` = '%.4f', `bizDeliverX` = '%.4f', `bizDeliverY` = '%.4f', `bizDeliverZ` = '%.4f', `bizShipment` = '%d' WHERE `bizID` = '%d'",
		query,
		BusinessData[bizid][bizSpawn][0],
		BusinessData[bizid][bizSpawn][1],
		BusinessData[bizid][bizSpawn][2],
		BusinessData[bizid][bizSpawn][3],
		BusinessData[bizid][bizDeliver][0],
		BusinessData[bizid][bizDeliver][1],
		BusinessData[bizid][bizDeliver][2],
		BusinessData[bizid][bizShipment],
		BusinessData[bizid][bizID]
	);
	mysql_query(sqlcon, query);
    //  mysql_tquery(sqlcon, query);
}

// Business_Inside(playerid)
// {
// 	if (PlayerData[playerid][pBusiness] != -1)
// 	{
// 	    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizID] == PlayerData[playerid][pBusiness] && GetPlayerInterior(playerid) == BusinessData[i][bizInterior] && GetPlayerVirtualWorld(playerid) > 0) {
// 	        return i;
// 		}
// 	}
// 	return -1;
// }

Business_Inside(playerid, Float:radius = 2.5)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, radius, BusinessData[i][bizActorPosition][0], BusinessData[i][bizActorPosition][1], BusinessData[i][bizActorPosition][2]))
	{
		if (GetPlayerInterior(playerid) == BusinessData[i][bizExterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][bizExteriorVW])
			return i;
	}
	return -1;
}

Business_NearestDeliver(playerid)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, 5.0, BusinessData[i][bizDeliver][0], BusinessData[i][bizDeliver][1], BusinessData[i][bizDeliver][2])) {
        return i;
	}
	return -1;
}

Business_Nearest(playerid, Float:radius = 2.5)
{
    for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && IsPlayerInRangeOfPoint(playerid, radius, BusinessData[i][bizPos][0], BusinessData[i][bizPos][1], BusinessData[i][bizPos][2]))
	{
		if (GetPlayerInterior(playerid) == BusinessData[i][bizExterior] && GetPlayerVirtualWorld(playerid) == BusinessData[i][bizExteriorVW])
			return i;
	}
	return -1;
}

Business_Refresh(bizid)
{
	if (bizid != -1 && BusinessData[bizid][bizExists])
	{
		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizText3D]);

		if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizDeliverText3D]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickup]);

        if (IsValidDynamicPickup(BusinessData[bizid][bizDeliverPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizDeliverPickup]);

		if(IsValidDynamicActor(BusinessData[bizid][bizActor]))
			DestroyDynamicActor(BusinessData[bizid][bizActor]);	

		static
		    string[128],
			pickup;

		BusinessData[bizid][bizActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], BusinessData[bizid][bizActorPosition][0], BusinessData[bizid][bizActorPosition][1], BusinessData[bizid][bizActorPosition][2], BusinessData[bizid][bizActorPosition][3], 1, 40.0, 0, 0, -1, 50.0, -1, 0);
		if (!BusinessData[bizid][bizOwner]) {
			format(string, sizeof(string), "[%s]\n%s", FormatNumber(BusinessData[bizid][bizPrice]), BusinessData[bizid][bizName]);
            BusinessData[bizid][bizText3D] = CreateDynamic3DTextLabel(string, 0x33AA33FF, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		else
		{
			if (BusinessData[bizid][bizLocked]) {
			    format(string, sizeof(string), "%s (closed)", BusinessData[bizid][bizName]);
			}
			else {
			    format(string, sizeof(string), "[[ %s Actor ]]", BusinessData[bizid][bizName]);
			}
			BusinessData[bizid][bizText3D] = CreateDynamic3DTextLabel(string, (BusinessData[bizid][bizLocked]) ? (X11_RED) : (X11_WHITE), BusinessData[bizid][bizActorPosition][0], BusinessData[bizid][bizActorPosition][1], BusinessData[bizid][bizActorPosition][2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		switch (BusinessData[bizid][bizType]) {
		    case 1: pickup = 1272;
		    case 2: pickup = 348;
		    case 3: pickup = 1275;
		    case 4: pickup = 19094;
		    case 5: pickup = 1274;
		    case 6: pickup = 1650;
		    case 7: pickup = 2096;
		}
		if (BusinessData[bizid][bizType] == 6) {
        	BusinessData[bizid][bizPickup] = CreateDynamicPickup(pickup, 23, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2] + 0.3, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		else if (BusinessData[bizid][bizType] == 7) {
		    BusinessData[bizid][bizPickup] = CreateDynamicPickup(pickup, 23, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2] - 0.6, BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		else {
            BusinessData[bizid][bizPickup] = CreateDynamicPickup(pickup, 23, BusinessData[bizid][bizPos][0], BusinessData[bizid][bizPos][1], BusinessData[bizid][bizPos][2], BusinessData[bizid][bizExteriorVW], BusinessData[bizid][bizExterior]);
		}
		if (BusinessData[bizid][bizDeliver][0] != 0.0 && BusinessData[bizid][bizDeliver][0] != 0.0 && BusinessData[bizid][bizDeliver][0] != 0.0)
		{
		    format(string, sizeof(string), "%s\n\nDelivery Point", BusinessData[bizid][bizName]);

		    BusinessData[bizid][bizPickup] = CreateDynamicPickup(1239, 23, BusinessData[bizid][bizDeliver][0], BusinessData[bizid][bizDeliver][1], BusinessData[bizid][bizDeliver][2]);
		    BusinessData[bizid][bizDeliverText3D] = CreateDynamic3DTextLabel(string, X11_LIGHTBLUE, BusinessData[bizid][bizDeliver][0], BusinessData[bizid][bizDeliver][1], BusinessData[bizid][bizDeliver][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0);
		}
	}
	return 1;
}

Business_Create(playerid, type, price)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle;

	if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_BUSINESSES; i ++)
		{
	    	if (!BusinessData[i][bizExists])
		    {
    	        BusinessData[i][bizExists] = true;
        	    BusinessData[i][bizOwner] = 0;
            	BusinessData[i][bizPrice] = price;
            	BusinessData[i][bizType] = type;

				format(BusinessData[i][bizName], 32, "Unnamed Business");

    	        BusinessData[i][bizPos][0] = x;
    	        BusinessData[i][bizPos][1] = y;
    	        BusinessData[i][bizPos][2] = z;
    	        BusinessData[i][bizPos][3] = angle;

    	        BusinessData[i][bizSpawn][0] = x;
    	        BusinessData[i][bizSpawn][1] = y;
    	        BusinessData[i][bizSpawn][2] = z;
    	        BusinessData[i][bizSpawn][3] = angle;

    	        BusinessData[i][bizDeliver][0] = 0.0;
    	        BusinessData[i][bizDeliver][1] = 0.0;
    	        BusinessData[i][bizDeliver][2] = 0.0;

				if (type == 1) {
                	BusinessData[i][bizActorPosition][0] = -27.3074;
                	BusinessData[i][bizActorPosition][1] = -30.8741;
                	BusinessData[i][bizActorPosition][2] = 1003.5573;
                	BusinessData[i][bizActorPosition][3] = 0.0000;
					BusinessData[i][bizInterior] = 4;

					BusinessData[i][bizPrices][0] = 75;
		            BusinessData[i][bizPrices][1] = 125;
		            BusinessData[i][bizPrices][2] = 15;
		            BusinessData[i][bizPrices][3] = 100;
		            BusinessData[i][bizPrices][4] = 3;
		            BusinessData[i][bizPrices][5] = 2;
		            BusinessData[i][bizPrices][6] = 10;
		            BusinessData[i][bizPrices][7] = 100;
		            BusinessData[i][bizPrices][8] = 20;
		            BusinessData[i][bizPrices][9] = 10;
		            BusinessData[i][bizPrices][10] = 150;
		            BusinessData[i][bizPrices][11] = 200;
		            BusinessData[i][bizPrices][12] = 160;
                    BusinessData[i][bizPrices][13] = 60;
                    BusinessData[i][bizPrices][14] = 50;
		            BusinessData[i][bizPrices][15] = 5;
		            BusinessData[i][bizPrices][16] = 10;
		            BusinessData[i][bizPrices][17] = 5;
				}
				else if (type == 2) {
                	BusinessData[i][bizActorPosition][0] = 316.3963;
                	BusinessData[i][bizActorPosition][1] = -169.8375;
                	BusinessData[i][bizActorPosition][2] = 999.6010;
                	BusinessData[i][bizActorPosition][3] = 0.0000;
					BusinessData[i][bizInterior] = 6;

                    BusinessData[i][bizPrices][0] = 50;
					BusinessData[i][bizPrices][1] = 100;
		            BusinessData[i][bizPrices][2] = 200;
		            BusinessData[i][bizPrices][3] = 400;
		            BusinessData[i][bizPrices][4] = 600;
		            BusinessData[i][bizPrices][5] = 800;
				}
				else if (type == 3) {
                	BusinessData[i][bizActorPosition][0] = 161.4801;
                	BusinessData[i][bizActorPosition][1] = -96.5368;
                	BusinessData[i][bizActorPosition][2] = 1001.8047;
                	BusinessData[i][bizActorPosition][3] = 0.0000;
					BusinessData[i][bizInterior] = 18;

					BusinessData[i][bizPrices][0] = 25;
		            BusinessData[i][bizPrices][1] = 15;
		            BusinessData[i][bizPrices][2] = 10;
		            BusinessData[i][bizPrices][3] = 10;
				}
				else if (type == 4) {
                	BusinessData[i][bizActorPosition][0] = 363.3402;
                	BusinessData[i][bizActorPosition][1] = -74.6679;
                	BusinessData[i][bizActorPosition][2] = 1001.5078;
                	BusinessData[i][bizActorPosition][3] = 315.0000;
					BusinessData[i][bizInterior] = 10;

					BusinessData[i][bizPrices][0] = 2;
		            BusinessData[i][bizPrices][1] = 5;
		            BusinessData[i][bizPrices][2] = 5;
		            BusinessData[i][bizPrices][3] = 10;
		            BusinessData[i][bizPrices][4] = 10;
		            BusinessData[i][bizPrices][5] = 15;
		            BusinessData[i][bizPrices][6] = 10;
				}
				else if (type == 5) {
				    BusinessData[i][bizActorPosition][0] = 1494.5612;
	            	BusinessData[i][bizActorPosition][1] = 1304.2061;
	            	BusinessData[i][bizActorPosition][2] = 1093.2891;
	            	BusinessData[i][bizActorPosition][3] = 0.0000;
					BusinessData[i][bizInterior] = 3;
				}
				else if (type == 6) {
                	BusinessData[i][bizActorPosition][0] = -27.3383;
                	BusinessData[i][bizActorPosition][1] = -57.6909;
                	BusinessData[i][bizActorPosition][2] = 1003.5469;
                	BusinessData[i][bizActorPosition][3] = 0.0000;
					BusinessData[i][bizInterior] = 6;

					BusinessData[i][bizPrices][0] = 75;
		            BusinessData[i][bizPrices][1] = 115;
		            BusinessData[i][bizPrices][2] = 15;
		            BusinessData[i][bizPrices][3] = 90;
		            BusinessData[i][bizPrices][4] = 3;
		            BusinessData[i][bizPrices][5] = 2;
		            BusinessData[i][bizPrices][6] = 10;
		            BusinessData[i][bizPrices][7] = 90;
		            BusinessData[i][bizPrices][8] = 20;
		            BusinessData[i][bizPrices][9] = 10;
		            BusinessData[i][bizPrices][10] = 140;
		            BusinessData[i][bizPrices][11] = 150;
                    BusinessData[i][bizPrices][12] = 50;
                    BusinessData[i][bizPrices][13] = 40;
		            BusinessData[i][bizPrices][14] = 5;
		            BusinessData[i][bizPrices][15] = 10;
		            BusinessData[i][bizPrices][16] = 5;
				}
				else if (type == 7) {
					BusinessData[i][bizActorPosition][0] = -2240.4954;
   					BusinessData[i][bizActorPosition][1] = 128.3774;
			   		BusinessData[i][bizActorPosition][2] = 1035.4210;
      				BusinessData[i][bizActorPosition][3] = 270.0000;
					BusinessData[i][bizInterior] = 6;

					BusinessData[i][bizPrices][0] = 75;
		            BusinessData[i][bizPrices][1] = 115;
		            BusinessData[i][bizPrices][2] = 15;
		            BusinessData[i][bizPrices][3] = 95;
		            BusinessData[i][bizPrices][4] = 3;
		            BusinessData[i][bizPrices][5] = 2;
		            BusinessData[i][bizPrices][6] = 10;
		            BusinessData[i][bizPrices][7] = 100;
		            BusinessData[i][bizPrices][8] = 20;
		            BusinessData[i][bizPrices][9] = 10;
		            BusinessData[i][bizPrices][10] = 140;
		            BusinessData[i][bizPrices][11] = 190;
		            BusinessData[i][bizPrices][12] = 150;
                    BusinessData[i][bizPrices][13] = 60;
                    BusinessData[i][bizPrices][14] = 50;
		            BusinessData[i][bizPrices][15] = 5;
		            BusinessData[i][bizPrices][16] = 10;
		            BusinessData[i][bizPrices][17] = 5;
				}
				BusinessData[i][bizExterior] = GetPlayerInterior(playerid);
				BusinessData[i][bizExteriorVW] = GetPlayerVirtualWorld(playerid);

				BusinessData[i][bizLocked] = true;
				BusinessData[i][bizVault] = 0;
				BusinessData[i][bizProducts] = 100;
				BusinessData[i][bizShipment] = 0;

				Business_Refresh(i);
				mysql_tquery(sqlcon, "INSERT INTO `businesses` (`bizOwner`) VALUES(0)", "OnBusinessCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

stock Business_RemovePumps(bizid)
{
	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizType] == 6)
	{
	    static
	        string[32];

	    foreach (new i : Player) if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID && PlayerData[i][pGasStation] == bizid)
	    {
	        StopRefilling(i);
	    }
		for (new i = 0; i != MAX_GAS_PUMPS; i ++) if (PumpData[i][pumpExists] && PumpData[i][pumpBusiness] == bizid)
		{
  			DestroyDynamicObject(PumpData[i][pumpObject]);
			DestroyDynamic3DTextLabel(PumpData[i][pumpText3D]);

		    PumpData[i][pumpExists] = 0;
		    PumpData[i][pumpFuel] = 0;
		}
		format(string, sizeof(string), "DELETE FROM `pumps` WHERE `ID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(sqlcon, string);
	}
	return 1;
}

Business_Delete(bizid)
{
	if (bizid != -1 && BusinessData[bizid][bizExists])
	{
	    new
	        string[82];

		format(string, sizeof(string), "DELETE FROM `businesses` WHERE `bizID` = '%d'", BusinessData[bizid][bizID]);
		mysql_tquery(sqlcon, string);

		// foreach (new i : Player) if (PlayerData[i][pShipment] == bizid) {
		// 	PlayerData[i][pShipment] = -1;
		// 	PlayerData[i][pDeliverShipment] = 0;

		// 	DisablePlayerCheckpoint(i);
		// }
        if (IsValidDynamic3DTextLabel(BusinessData[bizid][bizText3D]))
		    DestroyDynamic3DTextLabel(BusinessData[bizid][bizText3D]);

		if (IsValidDynamicPickup(BusinessData[bizid][bizPickup]))
		    DestroyDynamicPickup(BusinessData[bizid][bizPickup]);

		Business_RemovePumps(bizid);
        
	    BusinessData[bizid][bizExists] = false;
	    BusinessData[bizid][bizOwner] = 0;
	    BusinessData[bizid][bizID] = 0;
	}
	return 1;
}

Business_IsOwner(playerid, bizid)
{
	if (!PlayerData[playerid][pLogged] || PlayerData[playerid][pID] == -1)
	    return 0;

	if (BusinessData[bizid][bizExists] && BusinessData[bizid][bizOwner] == 99999999 && PlayerData[playerid][pAdmin] > 0)
		return 1;

    if ((BusinessData[bizid][bizExists] && BusinessData[bizid][bizOwner] != 0) && BusinessData[bizid][bizOwner] == PlayerData[playerid][pID])
		return 1;

	return 0;
}

stock GetBusinessByID(sqlid)
{
	for (new i = 0; i != MAX_BUSINESSES; i ++) if (BusinessData[i][bizExists] && BusinessData[i][bizID] == sqlid)
	    return i;

	return -1;
}

Function:OnBusinessCreated(bizid)
{
	if (bizid == -1 || !BusinessData[bizid][bizExists])
	    return 0;

	BusinessData[bizid][bizID] = cache_insert_id();
	Business_Save(bizid);

	return 1;
}

Function:OnPumpCreated(pumpid)
{
    PumpData[pumpid][pumpID] = cache_insert_id();
	Pump_Save(pumpid);

	return 1;
}

Dialog:BusinessBuy(playerid, response, listitem, inputtext[])
{
	static
	    bizid = -1,
		price;

    if ((bizid = Business_Inside(playerid)) != -1 && response)
    {
        price = BusinessData[bizid][bizPrices][listitem];

        if (GetMoney(playerid) < price)
            return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

		if (BusinessData[bizid][bizProducts] < 1)
		    return SendErrorMessage(playerid, "This business is out of stock.");

		if (BusinessData[bizid][bizType] == 1 || BusinessData[bizid][bizType] == 6)
		{
		    switch (listitem)
		    {
		        /*case 0:
		        {
		            if (Inventory_HasItem(playerid, "Cellphone"))
		                return SendErrorMessage(playerid, "You have a cellphone already.");

					new id = Inventory_Add(playerid, "Cellphone", 330);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					PlayerData[playerid][pPhone] = random(90000) + 10000;

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a cellphone.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);

					format(string, sizeof(string), "Your new number is ~p~%d.", PlayerData[playerid][pPhone]);
					ShowPlayerFooter(playerid, string);

					SendServerMessage(playerid, "Your new number is %d.", PlayerData[playerid][pPhone]);
				}*/
				case 1:
		        {
		            // if (Inventory_HasItem(playerid, "GPS System"))
		            //     return SendErrorMessage(playerid, "You have a GPS system already.");

					new id = Inventory_Add(playerid, "Es Teh", 19835);

					if (id == -1)
        				return SendErrorMessage(playerid, "Anda tidak memiliki slot yang tersisa.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah membayar %s dan menerima Es Teh.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 2:
		        {
		            // if (Inventory_HasItem(playerid, "GPS System"))
		            //     return SendErrorMessage(playerid, "You have a GPS system already.");

					new id = Inventory_Add(playerid, "Burger", 18875);

					if (id == -1)
        				return SendErrorMessage(playerid, "Anda tidak memiliki slot yang tersisa.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah membayar %s dan menerima Burger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 3:
		        {
		            // if (Inventory_HasItem(playerid, "GPS System"))
		            //     return SendErrorMessage(playerid, "You have a GPS system already.");

					new id = Inventory_Add(playerid, "Cigarette", 18875);

					if (id == -1)
        				return SendErrorMessage(playerid, "Anda tidak memiliki slot yang tersisa.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah membayar %s dan menerima Cigarette.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			}
		}
		/*else if (BusinessData[bizid][bizType] == 2)
		{
		    switch (listitem)
	    	{
		        case 0:
		        {
		            if (!Inventory_HasItem(playerid, "Weapon License"))
		                return SendErrorMessage(playerid, "This store only sells to people with a weapon license.");

		            if (Inventory_Count(playerid, "Magazine") >= 10)
		                return SendErrorMessage(playerid, "You have 10 magazines, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Magazine", 2039);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a weapon magazine.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
                case 1:
		        {
		            if (!Inventory_HasItem(playerid, "Weapon License"))
		                return SendErrorMessage(playerid, "This store only sells to people with a weapon license.");

		            if (Inventory_Count(playerid, "Ammo Cartridge") >= 10)
		                return SendErrorMessage(playerid, "You have 10 ammo cartridges, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Ammo Cartridge", 2358);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received an ammo cartridge.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 2:
		        {
		            if (!Inventory_HasItem(playerid, "Weapon License"))
		                return SendErrorMessage(playerid, "This store only sells to people with a weapon license.");

		            if (Inventory_Count(playerid, "Armored Vest") >= 3)
		                return SendErrorMessage(playerid, "You have 3 armored vests, you can't buy anymore.");

					new id = Inventory_Add(playerid, "Armored Vest", 19142);

					if (id == -1)
        				return SendErrorMessage(playerid, "You don't have any inventory slots left.");

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received an armored vest.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 3:
				{
				    if (!Inventory_HasItem(playerid, "Weapon License"))
				        return SendErrorMessage(playerid, "A weapon license is required to purchase from this store.");

				    if (PlayerData[playerid][pPlayingHours] < 5)
				        return SendErrorMessage(playerid, "You need at least 5 playing hours.");

                    if (Inventory_Count(playerid, "Desert Eagle") > 5)
					    return SendErrorMessage(playerid, "You can't carry anymore of this weapon.");

					Inventory_Add(playerid, "Desert Eagle", 348);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a Desert Eagle.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 4:
				{
				    if (!Inventory_HasItem(playerid, "Weapon License"))
				        return SendErrorMessage(playerid, "A weapon license is required to purchase from this store.");

				    if (PlayerData[playerid][pPlayingHours] < 5)
				        return SendErrorMessage(playerid, "You need at least 5 playing hours.");

                    if (Inventory_Count(playerid, "Shotgun") > 5)
					    return SendErrorMessage(playerid, "You can't carry anymore of this weapon.");

					Inventory_Add(playerid, "Shotgun", 349);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a Remington 870.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
				case 5:
				{
				    if (!Inventory_HasItem(playerid, "Weapon License"))
				        return SendErrorMessage(playerid, "A weapon license is required to purchase from this store.");

				    if (PlayerData[playerid][pPlayingHours] < 5)
				        return SendErrorMessage(playerid, "You need at least 5 playing hours.");

					if (Inventory_Count(playerid, "Rifle") > 5)
					    return SendErrorMessage(playerid, "You can't carry anymore of this weapon.");

					Inventory_Add(playerid, "Rifle", 357);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a M14 Rifle.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
		    }
		}*/
		else if (BusinessData[bizid][bizType] == 3)
		{
			PlayerData[playerid][pSkinPrice] = price;
			if(listitem == 0)
			{
				if(PlayerData[playerid][pGender] == 1)
				{
					ShowModelSelectionMenu(playerid, "Male Skins", MODEL_SELECTION_BUYSKIN, g_aMaleSkins, sizeof(g_aMaleSkins), -16.0, 0.0, -55.0);
				}
				else
				{
					ShowModelSelectionMenu(playerid, "Female Skins", MODEL_SELECTION_BUYSKIN, g_aFemaleSkins, sizeof(g_aFemaleSkins), -16.0, 0.0, -55.0);
				}
			}
			if(listitem == 1)
			{
				ShowModelSelectionMenu(playerid, "Purchase Accessory", MODEL_SELECTION_ACC, g_AccList, sizeof(g_AccList), 0.0, 0.0, 0.0);
			}
			if(listitem == 2)
			{
				Dialog_Show(playerid, DialogBajuBaru, DIALOG_STYLE_INPUT, "Buat Baju Baru", "Masukan nama baju yang ingin kamu buat.\n\nCatatan: nama baju hanya untuk mengidentifikasi baju kamu", "Select", "Close");
			}
		}
		else if (BusinessData[bizid][bizType] == 4)
		{
			switch (listitem)
			{
			    case 0:
			    {
			        if (PlayerData[playerid][pThirst] > 90)
			            return SendErrorMessage(playerid, "You are not thirsty right now.");

					PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 10 > 100) ? (100) : (PlayerData[playerid][pThirst] + 10);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some water.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 1:
			    {
			        if (PlayerData[playerid][pThirst] > 90)
			            return SendErrorMessage(playerid, "You are not thirsty right now.");

					PlayerData[playerid][pThirst] = (PlayerData[playerid][pThirst] + 20 > 100) ? (100) : (PlayerData[playerid][pThirst] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some soda.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 2:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 20 > 100) ? (100) : (PlayerData[playerid][pHunger] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some french fries.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 3:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 25 > 100) ? (100) : (PlayerData[playerid][pHunger] + 25);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a cheeseburger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 4:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 30 > 100) ? (100) : (PlayerData[playerid][pHunger] + 30);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a chicken burger.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 5:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 25 > 100) ? (100) : (PlayerData[playerid][pHunger] + 25);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some chicken nuggets.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			    case 6:
			    {
			        if (PlayerData[playerid][pHunger] > 90)
			            return SendErrorMessage(playerid, "You are not hungry right now.");

					PlayerData[playerid][pHunger] = (PlayerData[playerid][pHunger] + 20 > 100) ? (100) : (PlayerData[playerid][pHunger] + 20);

					GiveMoney(playerid, -price);
					SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a salad.", ReturnName(playerid, 0), FormatNumber(price));

					BusinessData[bizid][bizProducts]--;
					BusinessData[bizid][bizVault] += Tax_Percent(price);

					Business_Save(bizid);
					Tax_AddPercent(price);
			    }
			}
		}
		else if (BusinessData[bizid][bizType] == 7)
		{
		    new
				items[50] = {-1, ...},
				count;

		    for (new i = 0; i < sizeof(g_aFurnitureData); i ++) if (g_aFurnitureData[i][e_FurnitureType] == listitem + 1) {
				items[count++] = g_aFurnitureData[i][e_FurnitureModel];
		    }
		    PlayerData[playerid][pFurnitureType] = listitem;

			if (listitem == 3) {
				ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count, -12.0, 0.0, 0.0);
			}
			else {
			    ShowModelSelectionMenu(playerid, "Furniture", MODEL_SELECTION_FURNITURE, items, count);
			}
		}
	}
    return 1;
}



Dialog:EditProduct(playerid, response, listitem, inputtext[])
{
	static
	    bizid = -1;

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid))
	{
		if (response)
		{
		    static
		        item[24];

		    strmid(item, inputtext, 0, strfind(inputtext, "-") - 1);
		    strpack(PlayerData[playerid][pEditingItem], item, 32 char);

            PlayerData[playerid][pProductModify] = listitem;
      		Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\":", "Modify", "Back", item);
		}
	}
	return 1;
}

Dialog:PriceSet(playerid, response, listitem, inputtext[])
{
    static
	    bizid = -1,
		item[32];

	if ((bizid = Business_Inside(playerid)) != -1 && Business_IsOwner(playerid, bizid))
	{
		if (response)
		{
		    strunpack(item, PlayerData[playerid][pEditingItem]);

			if (isnull(inputtext))
			    return Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\":", "Modify", "Back", item);

			if (strval(inputtext) < 1 || strval(inputtext) > 2000)
			    return Dialog_Show(playerid, PriceSet, DIALOG_STYLE_INPUT, "Business: Set Price", "Please enter the new product price for \"%s\" ($1 to $2,000):", "Modify", "Back", item);

			BusinessData[bizid][bizPrices][PlayerData[playerid][pProductModify]] = strval(inputtext);
			Business_Save(bizid);

			SendServerMessage(playerid, "You have adjusted the price of \"%s\" to: %s!", item, FormatNumber(strval(inputtext)));
			Business_ProductMenu(playerid, bizid);
		}
		else
		{
		    Business_ProductMenu(playerid, bizid);
		}
	}
	return 1;
}

Function:RefuelCheck()
{
	new
	    string[128];

	foreach (new i : Player)
	{
	    if (!PlayerData[i][pLogged] || PlayerData[i][pRefill] == INVALID_VEHICLE_ID)
	        continue;

        if (PlayerData[i][pRefill] != INVALID_VEHICLE_ID && PlayerData[i][pGasPump] != -1)
		{
		    PlayerData[i][pRefillPrice]++;

		    VehCore[PlayerData[i][pRefill]][vehFuel] ++;
		    PumpData[PlayerData[i][pGasPump]][pumpFuel] --;

		    if (PumpData[PlayerData[i][pGasPump]][pumpExists])
			{
			    format(string, sizeof(string), "[Gas Pump: %d]\n{FFFFFF}Fuel Left: %d liters", PlayerData[i][pGasPump], PumpData[PlayerData[i][pGasPump]][pumpFuel]);
			    UpdateDynamic3DTextLabelText(PumpData[PlayerData[i][pGasPump]][pumpText3D], X11_LIGHTBLUE, string);
			}
			if (VehCore[PlayerData[i][pRefill]][vehFuel] >= 100 || GetEngineStatus(PlayerData[i][pRefill]) || !PumpData[PlayerData[i][pGasPump]][pumpExists] || PumpData[PlayerData[i][pGasPump]][pumpFuel] < 0)
			{
			    VehCore[PlayerData[i][pRefill]][vehFuel] = 100;

			    GiveMoney(i, -PlayerData[i][pRefillPrice]);
			    SendServerMessage(i, "You have refilled your vehicle for $%d.", PlayerData[i][pRefillPrice]);

			    if (PumpData[PlayerData[i][pGasPump]][pumpExists])
				{
					if (PumpData[PlayerData[i][pGasPump]][pumpFuel] < 0)
						PumpData[PlayerData[i][pGasPump]][pumpFuel] = 0;

					BusinessData[PlayerData[i][pGasStation]][bizVault] += PlayerData[i][pRefillPrice];
					Business_Save(PlayerData[i][pGasStation]);

					Pump_Save(PlayerData[i][pGasPump]);
				}
				StopRefilling(i);
			}
		}
	}
	return 1;
}

Function:FuelUpdate()
{
	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsEngineVehicle(i) && GetEngineStatus(i))
	{
	    if (VehCore[i][vehFuel] > 0)
	    {
	        VehCore[i][vehFuel]--;

			if (VehCore[i][vehFuel] >= 1 && VehCore[i][vehFuel] <= 5)
			{
			    SendClientMessage(GetVehicleDriver(i), X11_RED, "[WARNING]:{FFFFFF} This vehicle is low on fuel. You must visit a fuel station!");
			}
		}
		if (VehCore[i][vehFuel] <= 0)
		{
		    VehCore[i][vehFuel] = 0;
		    SwitchVehicleEngine(i, false);
		}
	}
}

Dialog:DialogBajuBaru(playerid, response, listitem, inputtext[])
{
	if(!response) return 1;

	GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
	SendInfoMessage(playerid, "Berhasil membeli baju baru");
	GivePlayerNewClothing(playerid, inputtext);
	return 1;
}