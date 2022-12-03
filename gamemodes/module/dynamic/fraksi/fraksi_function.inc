stock ViewFactions(playerid)
{
	new string[1040];
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists]) {
 		format(string, sizeof(string), "%s{FFFFFF}Faction ({FFBF00}%i{FFFFFF}) | %s\n", string, i, FactionData[i][factionName]);
	}
	Dialog_Show(playerid, FactionsList, DIALOG_STYLE_MSGBOX, "Factions List", string, "Close", "");
	return 1;
}

Faction_GetName(playerid)
{
    new
		factionid = PlayerData[playerid][pFaction],
		name[32] = "None";

 	if (factionid == -1)
	    return name;

	format(name, 32, FactionData[factionid][factionName]);
	return name;
}

Faction_GetRank(playerid)
{
    new
		factionid = PlayerData[playerid][pFaction],
		rank[32] = "None";

 	if (factionid == -1)
	    return rank;

	format(rank, 32, FactionRanks[factionid][PlayerData[playerid][pFactionRank] - 1]);
	return rank;
}

Function:Faction_Load()
{
	static
		str[32];

	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            FactionData[i][factionExists] = true;
            cache_get_value_name_int(i, "factionID", FactionData[i][factionID]);

            cache_get_value_name(i, "factionName", FactionData[i][factionName]);

            cache_get_value_name_int(i, "factionColor", FactionData[i][factionColor]);
            cache_get_value_name_int(i, "factionType", FactionData[i][factionType]);
            cache_get_value_name_int(i, "factionRanks", FactionData[i][factionRanks]);

            cache_get_value_name_float(i, "factionLockerX", FactionData[i][factionLockerPos][0]);
            cache_get_value_name_float(i, "factionLockerY", FactionData[i][factionLockerPos][1]);
            cache_get_value_name_float(i, "factionLockerZ", FactionData[i][factionLockerPos][2]);

            cache_get_value_name_int(i, "factionLockerInt", FactionData[i][factionLockerInt]);
            cache_get_value_name_int(i, "factionLockerWorld", FactionData[i][factionLockerWorld]);

            //Spawning
            cache_get_value_name_float(i, "SpawnX", FactionData[i][SpawnX]);
            cache_get_value_name_float(i, "SpawnY", FactionData[i][SpawnY]);
            cache_get_value_name_float(i, "SpawnZ", FactionData[i][SpawnZ]);
            cache_get_value_name_int(i, "SpawnInterior", FactionData[i][SpawnInterior]);
            cache_get_value_name_int(i, "SpawnVW", FactionData[i][SpawnVW]);

            for (new j = 0; j < 8; j ++) {
                format(str, sizeof(str), "factionSkin%d", j + 1);

                cache_get_value_name_int(i, str, FactionData[i][factionSkins][j]);
            }
            for (new j = 0; j < 10; j ++) {
                format(str, sizeof(str), "factionWeapon%d", j + 1);

                cache_get_value_name_int(i, str, FactionData[i][factionWeapons][j]);

                format(str, sizeof(str), "factionAmmo%d", j + 1);

                cache_get_value_name_int(i, str, FactionData[i][factionAmmo][j]);
            }
            for (new j = 0; j < 15; j ++) {
                format(str, sizeof(str), "factionRank%d", j + 1);

                cache_get_value_name(i, str, FactionRanks[i][j]);
            }
            Faction_Refresh(i);
        }
    }
    printf("[FACTION] Loaded %d Faction from database.", rows);
	return 1;
}

stock IsNearFactionLocker(playerid)
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1)
	    return 0;

	if (IsPlayerInRangeOfPoint(playerid, 3.0, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2]) && GetPlayerInterior(playerid) == FactionData[factionid][factionLockerInt] && GetPlayerVirtualWorld(playerid) == FactionData[factionid][factionLockerWorld])
	    return 1;

	return 0;
}

stock GetFactionByID(sqlid)
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (FactionData[i][factionExists] && FactionData[i][factionID] == sqlid)
	    return i;

	return -1;
}

SetFaction(playerid, id)
{
	if (id != -1 && FactionData[id][factionExists])
	{
		PlayerData[playerid][pFaction] = id;
		PlayerData[playerid][pFactionID] = FactionData[id][factionID];
	}
	return 1;
}

stock RemoveAlpha(color) {
    return (color & ~0xFF);
}

SetFactionColor(playerid)
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid != -1)
		return SetPlayerColor(playerid, RemoveAlpha(FactionData[factionid][factionColor]));

	return 0;
}

Faction_Update(factionid)
{
	if (factionid != -1 || FactionData[factionid][factionExists])
	{
	    foreach (new i : Player) if (PlayerData[i][pFaction] == factionid)
		{
 			if (GetFactionType(i) == FACTION_GANG || (GetFactionType(i) != FACTION_GANG && PlayerData[i][pOnDuty]))
			 	SetFactionColor(i);
		}
	}
	return 1;
}

Faction_Refresh(factionid)
{
	if (factionid != -1 && FactionData[factionid][factionExists])
	{
	    if (FactionData[factionid][factionLockerPos][0] != 0.0 && FactionData[factionid][factionLockerPos][1] != 0.0 && FactionData[factionid][factionLockerPos][2] != 0.0)
	    {
		    static
		        string[128];

			if (IsValidDynamicPickup(FactionData[factionid][factionPickup]))
			    DestroyDynamicPickup(FactionData[factionid][factionPickup]);

			if (IsValidDynamic3DTextLabel(FactionData[factionid][factionText3D]))
			    DestroyDynamic3DTextLabel(FactionData[factionid][factionText3D]);

			FactionData[factionid][factionPickup] = CreateDynamicPickup(1239, 23, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2], FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);

			format(string, sizeof(string), "[Locker %d]\n{FFFFFF}/flocker to access the locker.", factionid);
	  		FactionData[factionid][factionText3D] = CreateDynamic3DTextLabel(string, X11_DARKBLUE, FactionData[factionid][factionLockerPos][0], FactionData[factionid][factionLockerPos][1], FactionData[factionid][factionLockerPos][2], 15.0, INVALID_VEHICLE_ID, INVALID_PLAYER_ID, 0, FactionData[factionid][factionLockerWorld], FactionData[factionid][factionLockerInt]);
		}
	}
	return 1;
}

Faction_Save(factionid)
{
	static
	    query[2048];

	format(query, sizeof(query), "UPDATE `factions` SET `factionName` = '%s', `factionColor` = '%d', `factionType` = '%d', `factionRanks` = '%d', `factionLockerX` = '%.4f', `factionLockerY` = '%.4f', `factionLockerZ` = '%.4f', `factionLockerInt` = '%d', `factionLockerWorld` = '%d', `SpawnX` = '%f', `SpawnY` = '%f', `SpawnZ` = '%f', `SpawnInterior` = '%d', `SpawnVW` = '%d'",
		FactionData[factionid][factionName],
		FactionData[factionid][factionColor],
		FactionData[factionid][factionType],
		FactionData[factionid][factionRanks],
		FactionData[factionid][factionLockerPos][0],
		FactionData[factionid][factionLockerPos][1],
		FactionData[factionid][factionLockerPos][2],
		FactionData[factionid][factionLockerInt],
		FactionData[factionid][factionLockerWorld],

		FactionData[factionid][SpawnX],
		FactionData[factionid][SpawnY],
		FactionData[factionid][SpawnZ],
		FactionData[factionid][SpawnInterior],
		FactionData[factionid][SpawnVW]
	);
	for (new i = 0; i < 10; i ++)
	{
	    if (i < 8)
			format(query, sizeof(query), "%s, `factionSkin%d` = '%d', `factionWeapon%d` = '%d', `factionAmmo%d` = '%d'", query, i + 1, FactionData[factionid][factionSkins][i], i + 1, FactionData[factionid][factionWeapons][i], i + 1, FactionData[factionid][factionAmmo][i]);

		else
			format(query, sizeof(query), "%s, `factionWeapon%d` = '%d', `factionAmmo%d` = '%d'", query, i + 1, FactionData[factionid][factionWeapons][i], i + 1, FactionData[factionid][factionAmmo][i]);
	}
	format(query, sizeof(query), "%s WHERE `factionID` = '%d'",
		query,
		FactionData[factionid][factionID]
	);
	return mysql_tquery(sqlcon, query);
}

stock Faction_SaveRanks(factionid)
{
	static
	    query[768];

	format(query, sizeof(query), "UPDATE `factions` SET `factionRank1` = '%s', `factionRank2` = '%s', `factionRank3` = '%s', `factionRank4` = '%s', `factionRank5` = '%s', `factionRank6` = '%s', `factionRank7` = '%s', `factionRank8` = '%s', `factionRank9` = '%s', `factionRank10` = '%s', `factionRank11` = '%s', `factionRank12` = '%s', `factionRank13` = '%s', `factionRank14` = '%s', `factionRank15` = '%s' WHERE `factionID` = '%d'",
	    FactionRanks[factionid][0],
	    FactionRanks[factionid][1],
	    FactionRanks[factionid][2],
	    FactionRanks[factionid][3],
	    FactionRanks[factionid][4],
	    FactionRanks[factionid][5],
	    FactionRanks[factionid][6],
	    FactionRanks[factionid][7],
	    FactionRanks[factionid][8],
	    FactionRanks[factionid][9],
	    FactionRanks[factionid][10],
	    FactionRanks[factionid][11],
	    FactionRanks[factionid][12],
	    FactionRanks[factionid][13],
	    FactionRanks[factionid][14],
	    FactionData[factionid][factionID]
	);
	return mysql_tquery(sqlcon, query);
}

Faction_Delete(factionid)
{
	if (factionid != -1 && FactionData[factionid][factionExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `factions` WHERE `factionID` = '%d'", FactionData[factionid][factionID]);
		mysql_tquery(sqlcon, string);

		format(string, sizeof(string), "UPDATE `characters` SET `Faction` = '-1' WHERE `Faction` = '%d'", FactionData[factionid][factionID]);
		mysql_tquery(sqlcon, string);

		foreach (new i : Player)
		{
			if (PlayerData[i][pFaction] == factionid) {
		    	PlayerData[i][pFaction] = -1;
		    	PlayerData[i][pFactionID] = -1;
		    	PlayerData[i][pFactionRank] = -1;
			}
			if (PlayerData[i][pFactionEdit] == factionid) {
			    PlayerData[i][pFactionEdit] = -1;
			}
		}
		if (IsValidDynamicPickup(FactionData[factionid][factionPickup]))
  			DestroyDynamicPickup(FactionData[factionid][factionPickup]);

		if (IsValidDynamic3DTextLabel(FactionData[factionid][factionText3D]))
  			DestroyDynamic3DTextLabel(FactionData[factionid][factionText3D]);

	    FactionData[factionid][factionExists] = false;
	    FactionData[factionid][factionType] = 0;
	    FactionData[factionid][factionID] = 0;
	}
	return 1;
}

stock GetFactionType(playerid)
{
	if (PlayerData[playerid][pFaction] == -1)
	    return 0;

	return (FactionData[PlayerData[playerid][pFaction]][factionType]);
}

Faction_ShowRanks(playerid, factionid)
{
    if (factionid != -1 && FactionData[factionid][factionExists])
	{
		static
		    string[640];

		string[0] = 0;

		for (new i = 0; i < FactionData[factionid][factionRanks]; i ++)
		    format(string, sizeof(string), "%sRank %d: %s\n", string, i + 1, FactionRanks[factionid][i]);

		PlayerData[playerid][pFactionEdit] = factionid;
		Dialog_Show(playerid, EditRanks, DIALOG_STYLE_LIST, FactionData[factionid][factionName], string, "Change", "Cancel");
	}
	return 1;
}

Faction_Create(name[], type)
{
	for (new i = 0; i != MAX_FACTIONS; i ++) if (!FactionData[i][factionExists])
	{
	    format(FactionData[i][factionName], 32, name);

        FactionData[i][factionExists] = true;
        FactionData[i][factionColor] = 0xFFFFFF00;
        FactionData[i][factionType] = type;
        FactionData[i][factionRanks] = 5;

        FactionData[i][factionLockerPos][0] = 0.0;
        FactionData[i][factionLockerPos][1] = 0.0;
        FactionData[i][factionLockerPos][2] = 0.0;
        FactionData[i][factionLockerInt] = 0;
        FactionData[i][factionLockerWorld] = 0;

        for (new j = 0; j < 8; j ++) {
            FactionData[i][factionSkins][j] = 0;
        }
        for (new j = 0; j < 10; j ++) {
            FactionData[i][factionWeapons][j] = 0;
            FactionData[i][factionAmmo][j] = 0;
	    }
	    for (new j = 0; j < 15; j ++) {
			format(FactionRanks[i][j], 32, "Rank %d", j + 1);
	    }
	    mysql_tquery(sqlcon, "INSERT INTO `factions` (`factionType`) VALUES(0)", "OnFactionCreated", "d", i);
	    return i;
	}
	return -1;
}

Function:OnFactionCreated(factionid)
{
	if (factionid == -1 || !FactionData[factionid][factionExists])
	    return 0;

	FactionData[factionid][factionID] = cache_insert_id();

	Faction_Save(factionid);
	Faction_SaveRanks(factionid);

	return 1;
}

Dialog:EditRanks(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (!FactionData[PlayerData[playerid][pFactionEdit]][factionExists])
			return 0;

		PlayerData[playerid][pSelectedSlot] = listitem;
		Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);
	}
	return 1;
}

Dialog:SetRankName(playerid, response, listitem, inputtext[])
{
	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Rank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

	    if (strlen(inputtext) > 32)
	        return Dialog_Show(playerid, SetRankName, DIALOG_STYLE_INPUT, "Set Rank", "Error: The rank can't exceed 32 characters.\n\nRank: %s (%d)\n\nPlease enter a new name for this rank below:", "Submit", "Back", FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot] + 1);

		format(FactionRanks[PlayerData[playerid][pFactionEdit]][PlayerData[playerid][pSelectedSlot]], 32, inputtext);
		Faction_SaveRanks(PlayerData[playerid][pFactionEdit]);

		Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
		SendServerMessage(playerid, "You have set the name of rank %d to \"%s\".", PlayerData[playerid][pSelectedSlot] + 1, inputtext);
	}
	else Faction_ShowRanks(playerid, PlayerData[playerid][pFactionEdit]);
	return 1;
}

Dialog:Locker(playerid, response, listitem, inputtext[])
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1 || !IsNearFactionLocker(playerid))
		return 0;

	if (response)
	{
	    static
	        skins[8],
	        string[512];

		string[0] = 0;

	    if (FactionData[factionid][factionType] != FACTION_GANG)
	    {
	        switch (listitem)
	        {
	            case 0:
	            {
	                if (!PlayerData[playerid][pOnDuty])
	                {
	                    PlayerData[playerid][pOnDuty] = true;
	                    SetPlayerArmour(playerid, 100.0);

	                    //SetFactionColor(playerid);
	                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has clocked in and is now on duty.", ReturnName(playerid, 0));
	                }
	                else
	                {
	                    PlayerData[playerid][pOnDuty] = false;
	                    SetPlayerArmour(playerid, 0.0);

	                    //SetPlayerColor(playerid, DEFAULT_COLOR);
	                    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);

	                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has clocked out and is now off duty.", ReturnName(playerid, 0));
	                }
				}
				case 1:
				{
				    SetPlayerArmour(playerid, 100.0);
				    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches into the locker and takes out a vest.", ReturnName(playerid, 0));
				}
				case 2:
				{
					for (new i = 0; i < sizeof(skins); i ++)
					    skins[i] = (FactionData[factionid][factionSkins][i]) ? (FactionData[factionid][factionSkins][i]) : (19300);

					ShowModelSelectionMenu(playerid, "Choose Skin", MODEL_SELECTION_FACTION_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
				}
				case 3:
				{
				    for (new i = 0; i < 10; i ++)
					{
				        if (FactionData[factionid][factionWeapons][i])
							format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

						else format(string, sizeof(string), "%sEmpty Slot\n", string);
				    }
				    Dialog_Show(playerid, LockerWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
				}
			}
	    }
	    else
	    {
	        switch (listitem)
	        {
				case 0:
				{
					for (new i = 0; i < sizeof(skins); i ++)
					    skins[i] = (FactionData[factionid][factionSkins][i]) ? (FactionData[factionid][factionSkins][i]) : (19300);

					ShowModelSelectionMenu(playerid, "Choose Skin", MODEL_SELECTION_FACTION_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
				}
				case 1:
				{
				    for (new i = 0; i < 10; i ++)
					{
				        if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) != FACTION_GANG)
							format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]));

						else if (FactionData[factionid][factionWeapons][i] && GetFactionType(playerid) == FACTION_GANG)
							format(string, sizeof(string), "%sWeapon %d: %s (%d ammo)\n", string, i + 1, ReturnWeaponName(FactionData[factionid][factionWeapons][i]), FactionData[factionid][factionAmmo][i]);

						else format(string, sizeof(string), "%sEmpty Slot\n", string);
				    }
				    Dialog_Show(playerid, LockerWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
				}
			}
	    }
	}
	return 1;
}

CMD:flocker(playerid, params[])
{
	new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (!IsNearFactionLocker(playerid))
	    return SendErrorMessage(playerid, "You are not in range of your faction's locker.");

 	if (FactionData[factionid][factionType] != FACTION_GANG)
		Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Toggle Duty\nArmored Vest\nLocker Skins\nLocker Weapons", "Select", "Cancel");

	else Dialog_Show(playerid, Locker, DIALOG_STYLE_LIST, "Faction Locker", "Locker Skins\nLocker Weapons", "Select", "Cancel");
	return 1;
}

Dialog:LockerWeapons(playerid, response, listitem, inputtext[])
{
	new factionid = PlayerData[playerid][pFaction];

	if (factionid == -1 || !IsNearFactionLocker(playerid))
		return 0;

	if (response)
	{
	    new
	        weaponid = FactionData[factionid][factionWeapons][listitem],
	        ammo = FactionData[factionid][factionAmmo][listitem];

	    if (weaponid)
		{
	        if (PlayerHasWeapon(playerid, weaponid))
	        	return SendErrorMessage(playerid, "You have this weapon equipped already.");

	        GiveWeaponToPlayer(playerid, weaponid, ammo);
	        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s reaches inside the locker and equips a %s.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));

			if (GetFactionType(playerid) == FACTION_GANG)
		    {
		        FactionData[factionid][factionWeapons][listitem] = 0;
		        FactionData[factionid][factionAmmo][listitem] = 0;

		        Faction_Save(factionid);
			}
		}
		else
		{
		    if (GetFactionType(playerid) == FACTION_GANG)
		    {
		        if ((weaponid = GetWeapon(playerid)) == 0)
		            return SendErrorMessage(playerid, "You are not holding any weapon.");

		        FactionData[factionid][factionWeapons][listitem] = weaponid;
		        FactionData[factionid][factionAmmo][listitem] = GetPlayerAmmo(playerid);

		        Faction_Save(factionid);

                ResetWeapon(playerid, weaponid);
		        SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s takes out a %s and stores it in the locker.", ReturnName(playerid, 0), ReturnWeaponName(weaponid));
			}
			else
			{
			    SendErrorMessage(playerid, "The selected weapon slot is empty.");
			}
	    }
	}
	else {
	    cmd_flocker(playerid, "\1");
	}
	return 1;
}

Dialog:FactionLocker(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
			    static
			        Float:x,
			        Float:y,
			        Float:z;

				GetPlayerPos(playerid, x, y, z);

				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][0] = x;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][1] = y;
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerPos][2] = z;

				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerInt] = GetPlayerInterior(playerid);
				FactionData[PlayerData[playerid][pFactionEdit]][factionLockerWorld] = GetPlayerVirtualWorld(playerid);

				Faction_Refresh(PlayerData[playerid][pFactionEdit]);
				Faction_Save(PlayerData[playerid][pFactionEdit]);
				SendServerMessage(playerid, "You have adjusted the locker position of faction ID: %d.", PlayerData[playerid][pFactionEdit]);
			}
			case 1:
			{
				static
				    string[512];

				string[0] = 0;

			    for (new i = 0; i < 10; i ++)
				{
			        if (FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i])
						format(string, sizeof(string), "%sWeapon %d: %s\n", string, i + 1, ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][i]));

					else format(string, sizeof(string), "%sEmpty Slot\n", string);
			    }
			    Dialog_Show(playerid, FactionWeapons, DIALOG_STYLE_LIST, "Locker Weapons", string, "Select", "Cancel");
			}
		}
	}
	return 1;
}

Dialog:FactionWeapons(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    PlayerData[playerid][pSelectedSlot] = listitem;
	    Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);
	}
	return 1;
}

Dialog:FactionWeapon(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        	Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 1:
	            Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

			case 2:
			{
			    FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = 0;
				FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = 0;

				Faction_Save(PlayerData[playerid][pFactionEdit]);

				dialog_FactionLocker(playerid, 1, 1, "\1");
				SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
	    }
	}
	else {
	    dialog_FactionLocker(playerid, 1, 1, "\1");
	}
	return 1;
}

Dialog:FactionWeaponID(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new weaponid = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Current Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (weaponid < 0 || weaponid > 46)
		    return Dialog_Show(playerid, FactionWeaponID, DIALOG_STYLE_INPUT, "Set Weapon", "Error: The weapon ID can't be below 0 or above 46.\n\nCurrent Weapon: %s (%d)\n\nPlease enter the new weapon ID for slot %d:", "Submit", "Cancel", ReturnWeaponName(FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]]), FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]] = weaponid;
        Faction_Save(PlayerData[playerid][pFactionEdit]);

		Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);

	    if (weaponid) {
		    SendServerMessage(playerid, "You have set the weapon in slot %d to %s.", PlayerData[playerid][pSelectedSlot] + 1, ReturnWeaponName(weaponid));
		}
		else {
		    SendServerMessage(playerid, "You have removed the weapon in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
		}
	}
	return 1;
}

Dialog:FactionWeaponAmmo(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new ammo = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Current Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

		if (ammo < 1 || ammo > 15000)
		    return Dialog_Show(playerid, FactionWeaponAmmo, DIALOG_STYLE_INPUT, "Set Ammunition", "Error: The ammo can't be below 1 or above 15,000.\n\nCurrent Ammo: %d\n\nPlease enter the new ammunition for the weapon in slot %d:", "Submit", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]], PlayerData[playerid][pSelectedSlot]);

        FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]] = ammo;
        Faction_Save(PlayerData[playerid][pFactionEdit]);

		Dialog_Show(playerid, FactionWeapon, DIALOG_STYLE_LIST, "Edit Weapon", "Set Weapon (%d)\nSet Ammunition (%d)\nClear Slot", "Select", "Cancel", FactionData[PlayerData[playerid][pFactionEdit]][factionWeapons][PlayerData[playerid][pSelectedSlot]], FactionData[PlayerData[playerid][pFactionEdit]][factionAmmo][PlayerData[playerid][pSelectedSlot]]);
		SendServerMessage(playerid, "You have set the ammunition in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, ammo);
	}
	return 1;
}

Dialog:FactionSkin(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    static
	        skins[299];

		switch (listitem)
		{
		    case 0:
		        Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-299):", "Add", "Cancel");

			case 1:
			{
			    for (new i = 0; i < sizeof(skins); i ++)
			        skins[i] = i + 1;

				ShowModelSelectionMenu(playerid, "Add Skin", MODEL_SELECTION_ADD_SKIN, skins, sizeof(skins), -16.0, 0.0, -55.0);
			}
			case 2:
			{
			    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = 0;

			    Faction_Save(PlayerData[playerid][pFactionEdit]);
			    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
			}
		}
	}
	return 1;
}

Dialog:FactionModel(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFactionEdit] == -1)
	    return 0;

	if (response)
	{
	    new skin = strval(inputtext);

	    if (isnull(inputtext))
	        return Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Please enter the model ID of the skin below (0-299):", "Add", "Cancel");

		if (skin < 0 || skin > 299)
		    return Dialog_Show(playerid, FactionModel, DIALOG_STYLE_INPUT, "Add by Model ID", "Error: The skin ID can't be below 0 or above 299.\n\nPlease enter the model ID of the skin below (0-299):", "Add", "Cancel");

        FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = skin;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		if (skin) {
		    SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot] + 1, skin);
		}
		else {
		    SendServerMessage(playerid, "You have removed the skin ID in slot %d.", PlayerData[playerid][pSelectedSlot] + 1);
		}
	}
	return 1;
}