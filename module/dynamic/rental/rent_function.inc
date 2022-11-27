stock Rental_Create(playerid, veh1, veh2)
{
	new
	    Float:x,
	    Float:y,
	    Float:z,
		Float:angle
		;

	if (GetPlayerPos(playerid, x, y, z))
	{
		GetPlayerFacingAngle(playerid, angle);
		forex(i, MAX_RENTAL)
		{
		    if(!RentData[i][rentExists])
		    {
		        RentData[i][rentExists] = true;
		        RentData[i][rentModel][0] = veh1;
		        RentData[i][rentModel][1] = veh2;
		        RentData[i][rentPos][0] = x;
		        RentData[i][rentPos][1] = y;
		        RentData[i][rentPos][2] = z;
				RentData[i][rentPos][3] = angle;
		        RentData[i][rentSpawn][0] = 0;
		        RentData[i][rentSpawn][1] = 0;
		        RentData[i][rentSpawn][2] = 0;
		        
		        Rental_Spawn(i);

		        mysql_tquery(sqlcon, "INSERT INTO `rental` (`Vehicle1`) VALUES(0)", "OnRentalCreated", "d", i);
		        return i;
			}
		}
	}
	return -1;
}

Function:OnRentalCreated(id)
{
	if (id == -1 || !RentData[id][rentExists])
	    return 0;

	RentData[id][rentID] = cache_insert_id();
	Rental_Save(id);

	return 1;
}

Function:Rental_Load()
{
	new rows = cache_num_rows();
	if(rows)
	{
	    forex(i, rows)
	    {
	        RentData[i][rentExists] = true;
	        cache_get_value_name_int(i, "ID", RentData[i][rentID]);
	        cache_get_value_name_float(i, "PosX", RentData[i][rentPos][0]);
	        cache_get_value_name_float(i, "PosY", RentData[i][rentPos][1]);
	        cache_get_value_name_float(i, "PosZ", RentData[i][rentPos][2]);
			cache_get_value_name_float(i, "PosA", RentData[i][rentPos][3]);
	        cache_get_value_name_float(i, "SpawnX", RentData[i][rentSpawn][0]);
	        cache_get_value_name_float(i, "SpawnY", RentData[i][rentSpawn][1]);
	        cache_get_value_name_float(i, "SpawnZ", RentData[i][rentSpawn][2]);
	        cache_get_value_name_float(i, "SpawnA", RentData[i][rentSpawn][3]);
	        cache_get_value_name_int(i, "Vehicle1", RentData[i][rentModel][0]);
	        cache_get_value_name_int(i, "Vehicle2", RentData[i][rentModel][1]);
	        cache_get_value_name_int(i, "Price1", RentData[i][rentPrice][0]);
	        cache_get_value_name_int(i, "Price2", RentData[i][rentPrice][1]);
	        
	        Rental_Spawn(i);
		}
		printf("[RENTAL] Loaded %d Rental from database.", rows);
	}
	return 1;
}

stock Rental_Spawn(index)
{
	new string[156];
	format(string, sizeof(string), "[[ RENT KENDARAAN ]]");
	RentData[index][rentActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], RentData[index][rentPos][0], RentData[index][rentPos][1], RentData[index][rentPos][2], RentData[index][rentPos][3], 1, 40.0, 0, 0, -1, 50.0, -1, 0);
    RentData[index][rentText] = CreateDynamic3DTextLabel(string, X11_SKYBLUE, RentData[index][rentPos][0], RentData[index][rentPos][1], RentData[index][rentPos][2] + 1.0, 15.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 0, -1, -1);
    RentData[index][rentIcon] = CreateDynamicMapIcon(RentData[index][rentPos][0], RentData[index][rentPos][1], RentData[index][rentPos][2], 55, -1, -1, -1, -1, SERVER_ICON_DISTANCE);
	return 1;
}

stock Rental_Delete(id)
{
	if(!RentData[id][rentExists])
		return 0;

    if(IsValidDynamic3DTextLabel(RentData[id][rentText]))
        DestroyDynamic3DTextLabel(RentData[id][rentText]);
        
	if(IsValidDynamicActor(RentData[id][rentActor]))
		DestroyDynamicActor(RentData[id][rentActor]);

    if(IsValidDynamicMapIcon(RentData[id][rentIcon]))
        DestroyDynamicMapIcon(RentData[id][rentIcon]);    

	if(IsValidDynamicArea(RentData[id][rentArea]))
		DestroyDynamicArea(RentData[id][rentArea]);	

	new string[64];
	mysql_format(sqlcon, string, sizeof(string), "DELETE FROM `rental` WHERE `ID` = '%d'", RentData[id][rentID]);
	mysql_tquery(sqlcon, string);

	RentData[id][rentArea] = INVALID_STREAMER_ID;
	RentData[id][rentID] = 0;
	RentData[id][rentExists] = false;
	return 1;
}

stock Rental_Refresh(index)
{
	if(index != -1 && RentData[index][rentExists])
	{		    
		Streamer_SetFloatData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_X, RentData[index][rentPos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_Y, RentData[index][rentPos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_Z, RentData[index][rentPos][2]);
		Streamer_SetFloatData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_R_Z, RentData[index][rentPos][3]);

		Streamer_SetIntData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_INTERIOR_ID, -1);
		Streamer_SetIntData(STREAMER_TYPE_ACTOR, RentData[index][rentActor], E_STREAMER_WORLD_ID, -1);

		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, RentData[index][rentText], E_STREAMER_X, RentData[index][rentPos][0]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, RentData[index][rentText], E_STREAMER_Y, RentData[index][rentPos][1]);
		Streamer_SetFloatData(STREAMER_TYPE_3D_TEXT_LABEL, RentData[index][rentText], E_STREAMER_Z, RentData[index][rentPos][2]);

        Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, RentData[index][rentIcon], E_STREAMER_X, RentData[index][rentPos][0]);
        Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, RentData[index][rentIcon], E_STREAMER_Y, RentData[index][rentPos][1]);
        Streamer_SetFloatData(STREAMER_TYPE_MAP_ICON, RentData[index][rentIcon], E_STREAMER_Z, RentData[index][rentPos][2]);

		if(IsValidDynamicArea(RentData[index][rentArea]))
		{
			Streamer_SetFloatData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_X, RentData[index][rentPos][0]);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_Y, RentData[index][rentPos][1]);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_MIN_Z, RentData[index][rentPos][2] - 1.0);
			Streamer_SetFloatData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_MAX_Z, RentData[index][rentPos][2] + 3.0);

			Streamer_SetIntData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_INTERIOR_ID, -1);
		}
		else
		{			
			RentData[index][rentArea] = CreateDynamicCylinder(RentData[index][rentPos][0], RentData[index][rentPos][1], RentData[index][rentPos][2] - 1.0, RentData[index][rentPos][2] + 3.0, 1.0, -1, -1);

			new streamer_info[2];

			streamer_info[0] = RENTAL_AREA_INDEX;
			streamer_info[1] = index;
			Streamer_SetArrayData(STREAMER_TYPE_AREA, RentData[index][rentArea], E_STREAMER_EXTRA_ID, streamer_info);
		}
	}
	return 1;
}

stock GetNearbyRental(playerid)
{
	for(new index = 0; index < MAX_RENTAL; index ++)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 3.0, RentData[index][rentPos][0], RentData[index][rentPos][1], RentData[index][rentPos][2]))
	    {
	        return index;
	    }
	}
	return -1;
}

stock Rental_Save(id)
{
    new query[500];
    
	mysql_format(sqlcon, query, sizeof(query), "UPDATE `rental` SET ");
	mysql_format(sqlcon, query, sizeof(query), "%s`PosX`='%f', ", query, RentData[id][rentPos][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosY`='%f', ", query, RentData[id][rentPos][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosZ`='%f', ", query, RentData[id][rentPos][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`PosA`='%f', ", query, RentData[id][rentPos][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnX`='%f', ", query, RentData[id][rentSpawn][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnY`='%f', ", query, RentData[id][rentSpawn][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnZ`='%f', ", query, RentData[id][rentSpawn][2]);
	mysql_format(sqlcon, query, sizeof(query), "%s`SpawnA`='%f', ", query, RentData[id][rentSpawn][3]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Vehicle1`='%d', ", query, RentData[id][rentModel][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Vehicle2`='%d', ", query, RentData[id][rentModel][1]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Price1`='%d', ", query, RentData[id][rentModel][0]);
	mysql_format(sqlcon, query, sizeof(query), "%s`Price2`='%d' ", query, RentData[id][rentModel][1]);
	mysql_format(sqlcon, query, sizeof(query), "%sWHERE `ID` = '%d'", query, RentData[id][rentID]);
	mysql_query(sqlcon, query, true);
	return 1;
}

stock VehicleRental_Count(playerid)
{
	new count = 0;
	foreach(new i : PlayerVehicle) if(VehicleData[i][vRental] != -1 && VehicleData[i][vOwner] == PlayerData[playerid][pID])
	{
	    count++;
	}
	return count;
}

stock VehicleRental_Create(ownerid, modelid, Float:x, Float:y, Float:z, Float:angle, time, rentid)
{

	new i = Iter_Free(PlayerVehicle);

	if(i == INVALID_ITERATOR_SLOT)
		return print("Unable to create rental vehicle!");

	VehicleData[i][vExists] = true;

    VehicleData[i][vModel] = modelid;
    VehicleData[i][vOwner] = ownerid;

	format(VehicleData[i][vPlate], 16, "RENTAL");

    VehicleData[i][vPos][0] = x;
    VehicleData[i][vPos][1] = y;
    VehicleData[i][vPos][2] = z;
    VehicleData[i][vPos][3] = angle;

	VehicleData[i][vInsurance] = 0;
	VehicleData[i][vInsuTime] = 0;

    VehicleData[i][vColor][0] = random(126);

    VehicleData[i][vColor][1] = random(126);
    VehicleData[i][vInsuranced] = false;

    VehicleData[i][vLocked] = false;

	VehicleData[i][vFuel] = 100;
	VehicleData[i][vHealth] = 1000.0;

	VehicleData[i][vRental] = rentid;
	VehicleData[i][vRentTime] = time;
	VehicleData[i][vHouse] = -1;

	VehicleData[i][vVehicle] = CreateVehicle(VehicleData[i][vModel], VehicleData[i][vPos][0], VehicleData[i][vPos][1], VehicleData[i][vPos][2], VehicleData[i][vPos][3], VehicleData[i][vColor][0], VehicleData[i][vColor][1], 60000);
    VehCore[VehicleData[i][vVehicle]][vehFuel] = VehicleData[i][vFuel];
    VehCore[VehicleData[i][vVehicle]][vehWood] = 0;

    SetVehicleNumberPlate(VehicleData[i][vVehicle], VehicleData[i][vPlate]);

    Iter_Add(PlayerVehicle, i);

    mysql_tquery(sqlcon, "INSERT INTO `vehicle` (`vehModel`) VALUES(0)", "OnPlayerVehicleCreated", "d", i);
    return 1;
}