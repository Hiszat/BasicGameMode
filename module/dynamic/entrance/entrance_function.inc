GetClosestEntrance(playerid, type)
{
	new
	    Float:fDistance[2] = {99999.0, 0.0},
	    iIndex = -1
	;
	for (new i = 0; i < MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceType] == type && GetPlayerInterior(playerid) == EntranceData[i][entranceExterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceExteriorVW])
	{
		fDistance[1] = GetPlayerDistanceFromPoint(playerid, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]);

		if (fDistance[1] < fDistance[0])
		{
		    fDistance[0] = fDistance[1];
		    iIndex = i;
		}
	}
	return iIndex;
}

forward Entrance_Load();
public Entrance_Load()
{
    new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            EntranceData[i][entranceExists] = true;
            cache_get_value_name_int(i, "entranceID", EntranceData[i][entranceID]);

            cache_get_value_name(i, "entranceName", EntranceData[i][entranceName]);
            cache_get_value_name(i, "entrancePass", EntranceData[i][entrancePass]);

            cache_get_value_name_int(i, "entranceIcon", EntranceData[i][entranceIcon]);
            cache_get_value_name_int(i, "entranceLocked", EntranceData[i][entranceLocked]);

            cache_get_value_name_float(i, "entrancePosX", EntranceData[i][entrancePos][0]);
            cache_get_value_name_float(i, "entrancePosY", EntranceData[i][entrancePos][1]);
            cache_get_value_name_float(i, "entrancePosZ", EntranceData[i][entrancePos][2]);
            cache_get_value_name_float(i, "entrancePosA", EntranceData[i][entrancePos][3]);
            cache_get_value_name_float(i, "entranceIntX", EntranceData[i][entranceInt][0]);
            cache_get_value_name_float(i, "entranceIntY", EntranceData[i][entranceInt][1]);
            cache_get_value_name_float(i, "entranceIntZ", EntranceData[i][entranceInt][2]);
            cache_get_value_name_float(i, "entranceIntA", EntranceData[i][entranceInt][3]);

            cache_get_value_name_int(i, "entranceInterior", EntranceData[i][entranceInterior]);
            cache_get_value_name_int(i, "entranceExterior", EntranceData[i][entranceExterior]);
            cache_get_value_name_int(i, "entranceExteriorVW", EntranceData[i][entranceExteriorVW]);

            cache_get_value_name_int(i, "entranceType", EntranceData[i][entranceType]);
            cache_get_value_name_int(i, "entranceCustom", EntranceData[i][entranceCustom]);
            cache_get_value_name_int(i, "entranceWorld", EntranceData[i][entranceWorld]);

            Entrance_Refresh(i);
        }
	}
    printf("[ENTRANCE] Loaded %d Entrance from database.", rows);
	return 1;
}

Entrance_Delete(entranceid)
{
	if (entranceid != -1 && EntranceData[entranceid][entranceExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `entrances` WHERE `entranceID` = '%d'", EntranceData[entranceid][entranceID]);
		mysql_tquery(sqlcon, string);

        if (IsValidDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]))
		    DestroyDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickup]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickup]);

		if (IsValidDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]))
		    DestroyDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]);


	    EntranceData[entranceid][entranceExists] = false;
	    EntranceData[entranceid][entranceID] = 0;
	}
	return 1;
}

Entrance_Save(entranceid)
{
	static
	    query[1024];

	format(query, sizeof(query), "UPDATE `entrances` SET `entranceName` = '%s', `entrancePass` = '%s', `entranceIcon` = '%d', `entranceLocked` = '%d', `entrancePosX` = '%.4f', `entrancePosY` = '%.4f', `entrancePosZ` = '%.4f', `entrancePosA` = '%.4f', `entranceIntX` = '%.4f', `entranceIntY` = '%.4f', `entranceIntZ` = '%.4f', `entranceIntA` = '%.4f', `entranceInterior` = '%d', `entranceExterior` = '%d', `entranceExteriorVW` = '%d', `entranceType` = '%d'",
	    EntranceData[entranceid][entranceName],
	    EntranceData[entranceid][entrancePass],
	    EntranceData[entranceid][entranceIcon],
	    EntranceData[entranceid][entranceLocked],
	    EntranceData[entranceid][entrancePos][0],
	    EntranceData[entranceid][entrancePos][1],
	    EntranceData[entranceid][entrancePos][2],
	    EntranceData[entranceid][entrancePos][3],
	    EntranceData[entranceid][entranceInt][0],
	    EntranceData[entranceid][entranceInt][1],
	    EntranceData[entranceid][entranceInt][2],
	    EntranceData[entranceid][entranceInt][3],
	    EntranceData[entranceid][entranceInterior],
	    EntranceData[entranceid][entranceExterior],
	    EntranceData[entranceid][entranceExteriorVW],
	    EntranceData[entranceid][entranceType]
	);
	format(query, sizeof(query), "%s, `entranceCustom` = '%d', `entranceWorld` = '%d' WHERE `entranceID` = '%d'",
	    query,
	    EntranceData[entranceid][entranceCustom],
	    EntranceData[entranceid][entranceWorld],
	    EntranceData[entranceid][entranceID]
	);
	return mysql_tquery(sqlcon, query);
}

IsPlayerInCityHall(playerid)
{
	new
		id = -1;

	if ((id = Entrance_Inside(playerid)) != -1 && EntranceData[id][entranceType] == 4)
	    return 1;

	return 0;
}

IsPlayerInWarehouse(playerid)
{
	new
		id = -1;

	if ((id = Entrance_Inside(playerid)) != -1 && EntranceData[id][entranceType] == 3)
	    return 1;

	return 0;
}

IsPlayerInBank(playerid)
{
	new
		id = -1;

	if ((id = Entrance_Inside(playerid)) != -1 && EntranceData[id][entranceType] == 2)
	    return 1;

	return 0;
}

Entrance_Inside(playerid)
{
	if (PlayerData[playerid][pEntrance] != -1)
	{
	    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceID] == PlayerData[playerid][pEntrance] && GetPlayerInterior(playerid) == EntranceData[i][entranceInterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceWorld])
	        return i;
	}
	return -1;
}

Entrance_GetLink(playerid)
{
	if (GetPlayerVirtualWorld(playerid) > 0)
	{
	    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceID] == GetPlayerVirtualWorld(playerid) - 7000)
			return EntranceData[i][entranceID];
	}
	return -1;
}

Entrance_Nearest(playerid)
{
    for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && IsPlayerInRangeOfPoint(playerid, 2.5, EntranceData[i][entrancePos][0], EntranceData[i][entrancePos][1], EntranceData[i][entrancePos][2]))
	{
		if (GetPlayerInterior(playerid) == EntranceData[i][entranceExterior] && GetPlayerVirtualWorld(playerid) == EntranceData[i][entranceExteriorVW])
			return i;
	}
	return -1;
}

Entrance_Refresh(entranceid)
{
	if (entranceid != -1 && EntranceData[entranceid][entranceExists])
	{
		if (IsValidDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]))
		    DestroyDynamic3DTextLabel(EntranceData[entranceid][entranceText3D]);

		if (IsValidDynamicPickup(EntranceData[entranceid][entrancePickup]))
		    DestroyDynamicPickup(EntranceData[entranceid][entrancePickup]);

		if (IsValidDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]))
		    DestroyDynamicMapIcon(EntranceData[entranceid][entranceMapIcon]);

		EntranceData[entranceid][entranceText3D] = CreateDynamic3DTextLabel(EntranceData[entranceid][entranceName], X11_LIGHTBLUE, EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2], 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);
        EntranceData[entranceid][entrancePickup] = CreateDynamicPickup(1559, 23, EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2] + 0.7, EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);

		if (EntranceData[entranceid][entranceIcon] != 0)
			EntranceData[entranceid][entranceMapIcon] = CreateDynamicMapIcon(EntranceData[entranceid][entrancePos][0], EntranceData[entranceid][entrancePos][1], EntranceData[entranceid][entrancePos][2], EntranceData[entranceid][entranceIcon], 0, EntranceData[entranceid][entranceExteriorVW], EntranceData[entranceid][entranceExterior]);
	}
	return 1;
}

Entrance_Create(playerid, name[])
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

    if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_ENTRANCES; i ++)
		{
	    	if (!EntranceData[i][entranceExists])
		    {
    	        EntranceData[i][entranceExists] = true;
        	    EntranceData[i][entranceIcon] = 0;
        	    EntranceData[i][entranceType] = 0;
        	    EntranceData[i][entranceCustom] = 0;
        	    EntranceData[i][entranceLocked] = 0;

				format(EntranceData[i][entranceName], 32, name);
				EntranceData[i][entrancePass][0] = 0;

    	        EntranceData[i][entrancePos][0] = x;
    	        EntranceData[i][entrancePos][1] = y;
    	        EntranceData[i][entrancePos][2] = z;
    	        EntranceData[i][entrancePos][3] = angle;

                EntranceData[i][entranceInt][0] = x;
                EntranceData[i][entranceInt][1] = y;
                EntranceData[i][entranceInt][2] = z + 10000;
                EntranceData[i][entranceInt][3] = 0.0000;

				EntranceData[i][entranceInterior] = 0;
				EntranceData[i][entranceExterior] = GetPlayerInterior(playerid);
				EntranceData[i][entranceExteriorVW] = GetPlayerVirtualWorld(playerid);

				Entrance_Refresh(i);
				mysql_tquery(sqlcon, "INSERT INTO `entrances` (`entranceType`) VALUES(0)", "OnEntranceCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

stock GetEntranceByID(sqlid)
{
	for (new i = 0; i != MAX_ENTRANCES; i ++) if (EntranceData[i][entranceExists] && EntranceData[i][entranceID] == sqlid)
	    return i;

	return -1;
}

forward OnEntranceCreated(entranceid);
public OnEntranceCreated(entranceid)
{
	if (entranceid == -1 || !EntranceData[entranceid][entranceExists])
	    return 0;

	EntranceData[entranceid][entranceID] = cache_insert_id();
	EntranceData[entranceid][entranceWorld] = EntranceData[entranceid][entranceID] + 7000;

	Entrance_Save(entranceid);

	return 1;
}

Dialog:EntrancePass(playerid, response, listitem, inputtext[])
{
	if (response)
	{
		new id = (Entrance_Inside(playerid) == -1) ? (Entrance_Nearest(playerid)) : (Entrance_Inside(playerid));

		if (id == -1)
		    return SendErrorMessage(playerid, "You are not in range of any entrance.");

		if (strcmp(EntranceData[id][entrancePass], inputtext) != 0)
            return SendErrorMessage(playerid, "Invalid password specified.");

	    if (!EntranceData[id][entranceLocked])
		{
			EntranceData[id][entranceLocked] = true;
			Entrance_Save(id);

			SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "You have ~r~locked~w~ the entrance!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
		else
		{
			EntranceData[id][entranceLocked] = false;
			Entrance_Save(id);

			SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "You have ~g~unlocked~w~ the entrance!");
			PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
		}
	}
	return 1;
}