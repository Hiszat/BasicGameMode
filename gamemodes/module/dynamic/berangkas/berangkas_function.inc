Berangkas_Create(playerid)
{
	static
	    Float:x,
	    Float:y,
	    Float:z,
	    Float:angle;

    if (GetPlayerPos(playerid, x, y, z) && GetPlayerFacingAngle(playerid, angle))
	{
		for (new i = 0; i != MAX_DYNAMIC_BERANGKAS; i ++)
		{
	    	if (!BerangkasData[i][bExists])
		    {
                BerangkasData[i][bPos][0] = x;
                BerangkasData[i][bPos][1] = y;
                BerangkasData[i][bPos][2] = z;

                BerangkasData[i][bExists] = true;

				Berangkas_Refresh(i);
				mysql_tquery(sqlcon, "INSERT INTO `berangkas` (`berangkasModel`) VALUES(0)", "OnBerangkasCreated", "d", i);
				return i;
			}
		}
	}
	return -1;
}

Function:OnBerangkasCreated(berangkasid)
{
	if (berangkasid == -1 || !BerangkasData[berangkasid][bExists])
	    return 0;

	BerangkasData[berangkasid][bID] = cache_insert_id();

	Berangkas_Save(berangkasid);
	return 1;
}

Berangkas_Save(berangkasid)
{
	static
	    query[1024];

	format(query, sizeof(query), "UPDATE `berangkas` SET `berangkasModel` = '%d', `berangkasPosX` = '%.4f', `berangkasPosY` = '%.4f', `berangkasPosZ` = '%.4f' WHERE `berangkasID` = '%d'",
        BerangkasData[berangkasid][bModel],
        BerangkasData[berangkasid][bPos][0],
        BerangkasData[berangkasid][bPos][1],
        BerangkasData[berangkasid][bPos][2],
        BerangkasData[berangkasid][bID]
	);
	return mysql_tquery(sqlcon, query);
}

Function:Berangkas_Load()
{
    new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
            BerangkasData[i][bExists] = true;
            cache_get_value_name_int(i, "berangkasID", BerangkasData[i][bID]);

            cache_get_value_name_int(i, "berangkasModel", BerangkasData[i][bModel]);

            cache_get_value_name_float(i, "berangkasPosX", BerangkasData[i][bPos][0]);
            cache_get_value_name_float(i, "berangkasPosY", BerangkasData[i][bPos][1]);
            cache_get_value_name_float(i, "berangkasPosZ", BerangkasData[i][bPos][2]);
        
            Berangkas_Refresh(i);
        }
	}
    printf("[BERANGKAS] Loaded %d Berangkas from database.", rows);
	return 1;
}

Berangkas_Refresh(berangkasid)
{
	if (berangkasid != -1 && BerangkasData[berangkasid][bExists])
	{
		if (IsValidDynamicPickup(BerangkasData[berangkasid][bPickup]))
		    DestroyDynamicPickup(BerangkasData[berangkasid][bPickup]);

        BerangkasData[berangkasid][bPickup] = CreateDynamicPickup(1316, 23, BerangkasData[berangkasid][bPos][0], BerangkasData[berangkasid][bPos][1], BerangkasData[berangkasid][bPos][2], -1, -1);

	}
	return 1;
}

Berangkas_Delete(berangkasid)
{
	if (berangkasid != -1 && BerangkasData[berangkasid][bExists])
	{
	    new
	        string[64];

		format(string, sizeof(string), "DELETE FROM `berangkas` WHERE `berangkasID` = '%d'", BerangkasData[berangkasid][bID]);
		mysql_tquery(sqlcon, string);


		if (IsValidDynamicPickup(BerangkasData[berangkasid][bPickup]))
		    DestroyDynamicPickup(BerangkasData[berangkasid][bPickup]);

	    BerangkasData[berangkasid][bExists] = false;
	    BerangkasData[berangkasid][bID] = 0;
	}
	return 1;
}

Berangkas_Nearest(playerid)
{
    for (new i = 0; i != MAX_DYNAMIC_BERANGKAS; i ++) if (BerangkasData[i][bExists] && IsPlayerInRangeOfPoint(playerid, 2.5, BerangkasData[i][bPos][0], BerangkasData[i][bPos][1], BerangkasData[i][bPos][2]))
	{
		return i;
	}
	return -1;
}