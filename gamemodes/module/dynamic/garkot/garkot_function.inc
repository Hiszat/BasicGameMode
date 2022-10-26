GetClosestParks(playerid, Float: range = 4.3)
{
	new id = -1, Float: dist = range, Float: tempdist;
	foreach(new i : Parks)
	{
	    tempdist = GetPlayerDistanceFromPoint(playerid, GarkotData[i][parkX], GarkotData[i][parkY], GarkotData[i][parkZ]);

	    if(tempdist > range) continue;
		if(tempdist <= dist && GetPlayerInterior(playerid) == GarkotData[i][parkInt] && GetPlayerVirtualWorld(playerid) == GarkotData[i][parkWorld])
		{
			dist = tempdist;
			id = i;
		}
	}
	return id;
}

ReturnAnyPark(slot)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_PARKPOINT) return -1;
	foreach(new id : Parks)
	{
		tmpcount++;
		if(tmpcount == slot)
		{
			return id;
		}
	}
	return -1;
}

GetAnyPark()
{
	new tmpcount;
	foreach(new id : Parks)
	{
		tmpcount++;
	}
	return tmpcount;
}

Function:Garkot_Load()
{
	new rows;
	cache_get_row_count(rows);
	if(rows)
  	{
 		new id, i = 0, str[528];
		while(i < rows)
		{
			format(str, sizeof(str), "[[ GARASI KOTA ]]", id, GetLocation(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ]));
		    cache_get_value_name_int(i, "id", id);
			cache_get_value_name_float(i, "posx", GarkotData[id][parkX]);
			cache_get_value_name_float(i, "posy", GarkotData[id][parkY]);
			cache_get_value_name_float(i, "posz", GarkotData[id][parkZ]);
			cache_get_value_name_float(i, "posa", GarkotData[id][parkA]);
			cache_get_value_name_float(i, "spawnx", GarkotData[id][spawn][0]);
			cache_get_value_name_float(i, "spawny", GarkotData[id][spawn][1]);
			cache_get_value_name_float(i, "spawnz", GarkotData[id][spawn][2]);
			cache_get_value_name_float(i, "spawna", GarkotData[id][spawn][3]);
			cache_get_value_name_int(i, "interior", GarkotData[id][parkInt]);
			cache_get_value_name_int(i, "world", GarkotData[id][parkWorld]);
			GarkotData[id][parkActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], GarkotData[id][parkA], 1, 40.0, 0, 0, -1, 50.0, -1, 0);
			GarkotData[id][parkLabel] = CreateDynamic3DTextLabel(str, X11_LIGHTBLUE, GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ]+1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GarkotData[id][parkWorld], GarkotData[id][parkInt], -1, 10.0);
			GarkotData[id][parkMap] = CreateDynamicMapIcon(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], 55, -1, -1, -1, -1, 100.0);
			Iter_Add(Parks, id);
	    	i++;
		}
		printf("[GARKOT] Loaded %d Public Garage from database.", i);
	}
}

Park_Save(id)
{
	new cQuery[512];
	format(cQuery, sizeof(cQuery), "UPDATE parks SET posx='%f', posy='%f', posz='%f', posa='%f', spawnx='%f', spawny='%f', spawnz='%f', spawna='%f', interior=%d, world=%d WHERE id=%d",
	GarkotData[id][parkX],
	GarkotData[id][parkY],
	GarkotData[id][parkZ],
	GarkotData[id][parkA],
	GarkotData[id][spawn][0],
	GarkotData[id][spawn][1],
	GarkotData[id][spawn][2],
	GarkotData[id][spawn][3],
	GarkotData[id][parkInt],
	GarkotData[id][parkWorld],
	id
	);
	return mysql_tquery(sqlcon, cQuery);
}


GetNearbyGarkot(playerid)
{
	for(new i = 0; i < MAX_PARKPOINT; i ++)
	{
	    if(IsPlayerInRangeOfPoint(playerid, 3.0, GarkotData[i][parkX], GarkotData[i][parkY], GarkotData[i][parkZ]))
	    {
	        return i;
	    }
	}
	return -1;
}

CMD:createpark(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 4) return PermissionError(playerid);
		
	new id = Iter_Free(Parks), query[512];
	if(id == -1) return SendErrorMessage(playerid, "Can't add any more Park Point.");
 	new Float: x, Float: y, Float: z, Float:ang;
	GetPlayerFacingAngle(playerid, ang);
 	GetPlayerPos(playerid, x, y, z);
	
	GarkotData[id][parkX] = x;
	GarkotData[id][parkY] = y;
	GarkotData[id][parkZ] = z;
	GarkotData[id][parkA] = ang;
	GarkotData[id][parkInt] = GetPlayerInterior(playerid);
	GarkotData[id][parkWorld] = GetPlayerVirtualWorld(playerid);
	
	new str[128];
	format(str, sizeof(str), "[[ GARASI KOTA ]]", id, GetLocation(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ]));
	GarkotData[id][parkActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], GarkotData[id][parkA], 1, 40.0, 0, 0, -1, 50.0, -1, 0);
	GarkotData[id][parkLabel] = CreateDynamic3DTextLabel(str, X11_LIGHTBLUE, GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ] + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GarkotData[id][parkWorld], GarkotData[id][parkInt], -1, 10.0);
	GarkotData[id][parkMap] = CreateDynamicMapIcon(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], 55, -1, -1, -1, -1, 100.0);
	Iter_Add(Parks, id);
	
	mysql_format(sqlcon, query, sizeof(query), "INSERT INTO parks SET id=%d, posx='%f', posy='%f', posz='%f', interior=%d, world=%d", id, GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], GetPlayerInterior(playerid), GetPlayerVirtualWorld(playerid));
	mysql_tquery(sqlcon, query, "OnParkCreated", "ii", playerid, id);
	return 1;
}

Function:OnParkCreated(playerid, id)
{
	Park_Save(id);
	SendServerMessage(playerid, "You has created Park Point id: %d.", id);
	return 1;
}

ReturnAnyVehiclePark(slot, i)
{
	new tmpcount;
	if(slot < 1 && slot > MAX_PLAYER_VEHICLE) return -1;
	foreach(new id : PlayerVehicle)
	{
	    if(VehicleData[id][vPark] == i && VehicleData[id][vPark] > -1)
	    {
     		tmpcount++;
       		if(tmpcount == slot)
       		{
        		return id;
  			}
	    }
	}
	return -1;
}

GetAnyVehiclePark(i)
{
	new tmpcount;
    foreach(new id : PlayerVehicle)
	{
	    if(VehicleData[id][vPark] == i)
	    {
     		tmpcount++;
		}
	}
	return tmpcount;
}

CountParkedVeh(id)
{
	if(id > -1)
	{
		new count = 0;
		foreach(new i : PlayerVehicle)
		{
			if(VehicleData[i][vPark] == id)
				count++;
		}
		return count;
	}
	return 0;
}

Dialog:DialogGarkot(playerid, response, listitem, inputtext[])
{
	if(!response) return 1; 
	if(listitem == 0)
	{
		if(PlayerData[playerid][pLoggedIn] == false) return SendErrorMessage(playerid, "Kamu harus login!");
		if(PlayerData[playerid][pInjured] >= 1) return SendErrorMessage(playerid, "Kamu tidak bisa melakukan ini!");
		if(!IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "You must be in Vehicle");
		new id = -1;
		id = GetClosestParks(playerid);
			
		if(id > -1)
		{
			if(CountParkedVeh(id) >= 40)
				return SendErrorMessage(playerid, "Garasi Kota sudah memenuhi Kapasitas!");

			new carid = -1,
				found = 0;

			if((carid = Vehicle_Nearest2(playerid)) != -1)
			{
				GetVehiclePos(VehicleData[carid][vVehicle], VehicleData[carid][vPos][0], VehicleData[carid][vPos][1], VehicleData[carid][vPos][2]);
				GetVehicleZAngle(VehicleData[carid][vVehicle], VehicleData[carid][vPos][3]);
				GetVehicleHealth(VehicleData[carid][vVehicle], VehicleData[carid][vHealth]);
				PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
                SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Kendaraan kamu berhasil ke masukan ke garasi kota");
				RemovePlayerFromVehicle(playerid);
				VehicleData[carid][vPark] = id;					
				SetPlayerArmedWeapon(playerid, 0);
				found++;

				if(IsValidVehicle(VehicleData[carid][vVehicle]))
				{
					DestroyVehicle(VehicleData[carid][vVehicle]);
					VehicleData[carid][vVehicle] = INVALID_VEHICLE_ID;
					
				}
				if(!found) return SendErrorMessage(playerid, "Kendaraan ini tidak dapat di Park!");
			}
			return 1;
        }    
	}
    else if(listitem == 1)
	{
		if(PlayerData[playerid][pLoggedIn] == false) return SendErrorMessage(playerid, "Kamu harus login!");
		if(PlayerData[playerid][pInjured] >= 1) return SendErrorMessage(playerid, "Kamu tidak bisa melakukan ini!");
		if(IsPlayerInAnyVehicle(playerid)) return SendErrorMessage(playerid, "You must be not in Vehicle");
		foreach(new i : Parks)
		{
			if(IsPlayerInRangeOfPoint(playerid, 2.3, GarkotData[i][parkX], GarkotData[i][parkY], GarkotData[i][parkZ]))
			{
				PlayerData[playerid][pPark] = i;
				if(GetAnyVehiclePark(i) <= 0) return SendErrorMessage(playerid, "Tidak ada Kendaraan yang diparkirkan disini.");
				new vehid, count = GetAnyVehiclePark(i), location[4080], lstr[596];

				strcat(location,"No\tVehicle\tPlate\tOwner\n",sizeof(location));
				Loop(itt, (count + 1), 1)
				{
					vehid = ReturnAnyVehiclePark(itt, i);
					if(itt == count)
					{
						format(lstr,sizeof(lstr), "%d\t%s\t%s\t%s\n", itt, GetVehicleModelName(VehicleData[vehid][vModel]), VehicleData[vehid][vPlate], GetVehicleOwnerName(vehid));
					}
					else format(lstr,sizeof(lstr), "%d\t%s\t%s\t%s\n", itt, GetVehicleModelName(VehicleData[vehid][vModel]), VehicleData[vehid][vPlate], GetVehicleOwnerName(vehid));
					strcat(location,lstr,sizeof(location));
				}
				Dialog_Show(playerid, DialogGarkotPickup, DIALOG_STYLE_TABLIST_HEADERS,"Parked Vehicle",location,"Pickup","Cancel");
			}
		}
	}
    return 1;
}

Function:GarkotVehicleRespawn(playerid, i)
{
	new garkotid = GetNearbyGarkot(playerid);
	VehicleData[i][vVehicle] = CreateVehicle(VehicleData[i][vModel], GarkotData[garkotid][spawn][0], GarkotData[garkotid][spawn][1], GarkotData[garkotid][spawn][2], GarkotData[garkotid][spawn][3], VehicleData[i][vColor][0], VehicleData[i][vColor][1], 60000);
	SetVehicleNumberPlate(VehicleData[i][vVehicle], VehicleData[i][vPlate]);
	SetVehicleVirtualWorld(VehicleData[i][vVehicle], VehicleData[i][vWorld]);
	LinkVehicleToInterior(VehicleData[i][vVehicle], VehicleData[i][vInterior]);
	VehCore[VehicleData[i][vVehicle]][vehFuel] = VehicleData[i][vFuel];
	VehCore[VehicleData[i][vVehicle]][vehWood] = VehicleData[i][vWood];
	if(VehicleData[i][vHealth] < 350.0)
	{
		SetVehicleHealth(VehicleData[i][vVehicle], 350.0);
	}
	else
	{
		SetVehicleHealth(VehicleData[i][vVehicle], VehicleData[i][vHealth]);
	}
	UpdateVehicleDamageStatus(VehicleData[i][vVehicle], VehicleData[i][vDamage][0], VehicleData[i][vDamage][1], VehicleData[i][vDamage][2], VehicleData[i][vDamage][3]);
	LockVehicle(VehicleData[i][vVehicle], VehicleData[i][vLocked]);
	for(new idx = 0; idx < 5; idx ++)
	{
	    if(VehicleData[i][vToyID][idx] != 0)
	    {
	        VehicleData[i][vToy][idx] = CreateDynamicObject(VehicleData[i][vToyID][idx], VehicleData[i][vToyPosX][idx], VehicleData[i][vToyPosY][idx], VehicleData[i][vToyPosZ][idx], VehicleData[i][vToyRotX][idx], VehicleData[i][vToyRotY][idx], VehicleData[i][vToyRotZ][idx],  -1, -1, -1, 50.0, 0.0);
			AttachDynamicObjectToVehicle(VehicleData[i][vToy][idx], VehicleData[i][vVehicle], VehicleData[i][vToyPosX][idx], VehicleData[i][vToyPosY][idx], VehicleData[i][vToyPosZ][idx], VehicleData[i][vToyRotX][idx], VehicleData[i][vToyRotY][idx], VehicleData[i][vToyRotZ][idx]);
		}
	}

	PutPlayerInVehicle(playerid, VehicleData[i][vVehicle], 0);
    return 1;
}

Dialog:DialogGarkotPickup(playerid, response, listitem, inputtext[])
{
	if(response)
	{
		new vid = ReturnAnyVehiclePark((listitem + 1), PlayerData[playerid][pPark]);

		GetPlayerPos(playerid, VehicleData[vid][vPos][0], VehicleData[vid][vPos][1], VehicleData[vid][vPos][2]);
		GetPlayerFacingAngle(playerid, VehicleData[vid][vPos][3]);
		GarkotVehicleRespawn(playerid, vid);

        SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Kendaraan berhasil di ambil dari garasi kota"));

	}
    return 1;
}