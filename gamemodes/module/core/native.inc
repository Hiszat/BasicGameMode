stock SendTextDrawMessageEx(playerid, type = NOTIFICATION_INFO, const text[], va_args<>)
{
	PlayerPlaySound(playerid, 1057 , 0.0, 0.0, 0.0);
	ShowTDN(playerid, type, sprintf("%s", text));
	return 1;
}

stock UpdatePlayerSkin(playerid, skinid)
{
	SetPlayerSkin(playerid, skinid);
	PlayerData[playerid][pSkin] = skinid;
}

stock ResetPlayerData(playerid)
{
	if (PlayerData[playerid][pFreeze])
	    KillTimer(PlayerData[playerid][pFreezeTimer]);

	if(PlayerData[playerid][pPressBtn])
		KillTimer(PlayerData[playerid][pPressBtnTime]);	

	foreach (new i : Player)
	{
		if (PlayerData[i][pBusinessSeller] == playerid) {
		    PlayerData[i][pBusinessSeller] = INVALID_PLAYER_ID;
		    PlayerData[i][pBusinessOffered] = -1;
		}
	}

	if (PlayerData[playerid][pEditPump] != -1)
	{
		Pump_Refresh(PlayerData[playerid][pEditPump]);
		PlayerData[playerid][pGasStation] = -1;
	}

    PlayerData[playerid][pInjuredTime] = 600;
    PlayerData[playerid][pInjured] = false;
    PlayerData[playerid][pGender] = -1;
    PlayerData[playerid][pMoney] = 0;
    PlayerData[playerid][pBank] = 0;
    PlayerData[playerid][pLevel] = 1;
    PlayerData[playerid][pHealth] = 100;
    PlayerData[playerid][pArmor] = 100;
	PlayerData[playerid][pListitem] = -1;
	PlayerData[playerid][pInventory] = 0;
	PlayerData[playerid][pEntrance] = -1;
	PlayerData[playerid][pFreeze] = 0;
	PlayerData[playerid][pPressBtn] = false;
	PlayerData[playerid][pBusiness] = -1;
	PlayerData[playerid][pBusinessSeller] = INVALID_PLAYER_ID;
	PlayerData[playerid][pBusinessOffered] = -1;
	PlayerData[playerid][pBusinessValue] = 0;
	PlayerData[playerid][pRefill] = INVALID_VEHICLE_ID;
	PlayerData[playerid][pRefillPrice] = 0;
	PlayerData[playerid][pGasPump] = -1;
	PlayerData[playerid][pGasStation] = -1;
	PlayerData[playerid][pFurnitureType] = 0;
	PlayerData[playerid][pProductModify] = 0;
	PlayerData[playerid][pFaction] = 0;
	PlayerData[playerid][pFacRank] = 0;
	PlayerData[playerid][pDuty] = 0;
	PlayerData[playerid][pFacDiv] = 0;
	PlayerData[playerid][pWanted] = 0;
	PlayerData[playerid][pCuffed] = 0;
	PlayerData[playerid][pJob] = 0;
	PlayerData[playerid][pJob2] = 0;
	PlayerData[playerid][pJailTime] = 0;
	PlayerData[playerid][pJailType] = 0;
	PlayerData[playerid][pAJailTime] = 0;
	Pagessss[playerid] = 0;
	NAMAORANGGILA[playerid] = "";
	//format(NAMAORANGGILA[playerid], sizeof(NAMAORANGGILA[playerid]), "");
	// Temp Variable
	SellLastSpawn[playerid] = -1;

	forex(inv, 20)
	{
		PlayerTextDrawSetPreviewModel(playerid, ITEM[inv][playerid], -1);
		PlayerTextDrawSetString(playerid, ITEMTXT[inv][playerid], "_");
		PlayerTextDrawSetString(playerid, INVJUMLAH[playerid][inv], "_");
	}
}

Float:DistanceCameraTargetToLocation(Float:CamX, Float:CamY, Float:CamZ, Float:ObjX, Float:ObjY, Float:ObjZ, Float:FrX, Float:FrY, Float:FrZ)
{
	new Float:TGTDistance;
	TGTDistance = floatsqroot((CamX - ObjX) * (CamX - ObjX) + (CamY - ObjY) * (CamY - ObjY) + (CamZ - ObjZ) * (CamZ - ObjZ));
	new Float:tmpX, Float:tmpY, Float:tmpZ;
	tmpX = FrX * TGTDistance + CamX;
	tmpY = FrY * TGTDistance + CamY;
	tmpZ = FrZ * TGTDistance + CamZ;
	return floatsqroot((tmpX - ObjX) * (tmpX - ObjX) + (tmpY - ObjY) * (tmpY - ObjY) + (tmpZ - ObjZ) * (tmpZ - ObjZ));
}

stock Float:GetPointAngleToPoint(Float:x2, Float:y2, Float:X, Float:Y)
{
	new Float:DX, Float:DY;
	new Float:angle;
	DX = floatabs(floatsub(x2,X));
	DY = floatabs(floatsub(y2,Y));
	if (DY == 0.0 || DX == 0.0)
	{
	if(DY == 0 && DX > 0) angle = 0.0;
	else if(DY == 0 && DX < 0) angle = 180.0;
	else if(DY > 0 && DX == 0) angle = 90.0;
	else if(DY < 0 && DX == 0) angle = 270.0;
	else if(DY == 0 && DX == 0) angle = 0.0;
	}
	else
	{
	angle = atan(DX/DY);
	if(X > x2 && Y <= y2) angle += 90.0;
	else if(X <= x2 && Y < y2) angle = floatsub(90.0, angle);
	else if(X < x2 && Y >= y2) angle -= 90.0;
	else if(X >= x2 && Y > y2) angle = floatsub(270.0, angle);
	}
	return floatadd(angle, 90.0);
}

stock IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius)
{
	new Float:camera_x,Float:camera_y,Float:camera_z,Float:vector_x,Float:vector_y,Float:vector_z;
	GetPlayerCameraPos(playerid, camera_x, camera_y, camera_z);
	GetPlayerCameraFrontVector(playerid, vector_x, vector_y, vector_z);
	new Float:vertical, Float:horizontal;
	switch (GetPlayerWeapon(playerid))
	{
		case 34,35,36:
		{
			if (DistanceCameraTargetToLocation(camera_x, camera_y, camera_z, x, y, z, vector_x, vector_y, vector_z) < radius)
			{
				return true;
			}
			return false;
		}
		case 30,31: { vertical = 4.0; horizontal = -1.6; }
		case 33: { vertical = 2.7; horizontal = -1.0; }
		default: { vertical = 6.0; horizontal = -2.2; }
	}
	new Float:angle = GetPointAngleToPoint(0, 0, floatsqroot(vector_x*vector_x+vector_y*vector_y), vector_z) - 270.0;
	new Float:resize_x, Float:resize_y, Float:resize_z = floatsin(angle+vertical, degrees);
	GetXYInFrontOfPoint(resize_x, resize_y, GetPointAngleToPoint(0, 0, vector_x, vector_y)+horizontal, floatcos(angle+vertical, degrees));
	if (DistanceCameraTargetToLocation(camera_x, camera_y, camera_z, x, y, z, resize_x, resize_y, resize_z) < radius)
	{
		return true;
	}
	return false;
}

stock GetXYInFrontOfPoint(&Float:x, &Float:y, Float:angle, Float:distance)
{
	x += (distance * floatsin(-angle, degrees));
	y += (distance * floatcos(-angle, degrees));
}

stock GetXYZInFrontOfPlayer(playerid, &Float:x, &Float:y, &Float:z, Float:distance)
{
	new Float:a;
	GetPlayerPos(playerid, x, y, z);
	GetPlayerFacingAngle(playerid, a);
	if (GetPlayerVehicleID(playerid))
	{
	    GetVehicleZAngle(GetPlayerVehicleID(playerid), a);
	}
	x += (distance * floatsin(-a, degrees));
	y += (distance * floatcos(-a, degrees));
}

SaveServerStuff(id,amount)
{
	new query[1024];
	format(query, sizeof(query), "UPDATE `Stuff` SET Amount='%d' WHERE id='%d'", amount, id);
	mysql_tquery(sqlcon, query);
	return 1;
}

Function:LoadServerStuff(){

	new rows;
	cache_get_row_count(rows);
	if(rows)
  	{
 		new id = 0 , i = 0;
		while(i < rows){
			if(i < 2)
			{
				if(i == 0)
				{
					cache_get_value_name_int(i, "ID", id);
					cache_get_value_name_int(i, "Amount", Tax);
					//Iter_Add(Stuff, id);
				}else if(i == 1)
				{
					cache_get_value_name_int(i, "ID", id);
					cache_get_value_name_int(i, "Amount", TaxVault);
					//Iter_Add(Stuff, id);
					
				}
				i++;
			}else{
				cache_get_value_name_int(i, "ID", StuffData[i][sId]);
				cache_get_value_name(i, "Name", StuffData[i][sName]);
				cache_get_value_name_int(i, "Amount", StuffData[i][sAmount]);
				//Iter_Add(Stuff, id);
				i++;
			}
		}
		printf("[STUFF] Loaded %d rows  %d (Tax) %d (Tax Vault) Stuff from database.", rows,Tax,TaxVault);
	}
	return 1;
}

stock Float:GetDistanceBetweenPoints(Float:X, Float:Y, Float:Z, Float:PointX, Float:PointY, Float:PointZ)
{
	new Float:Distance;Distance = floatabs(floatsub(X, PointX)) + floatabs(floatsub(Y, PointY)) + floatabs(floatsub(Z, PointZ));
	return Distance;
}

stock GetLSPDEmptyCell(){
	for(new  i = 1; i < 9; i++){
		if(CellPrisoners[i] < 3){ // Sel Cuman Muat Dua Orang
			return i;
		}
	}
	return 0;
}

stock GetElapsedTime(time, &hours, &minutes, &seconds)
{
	hours = 0;
	minutes = 0;
	seconds = 0;

	if (time >= 3600)
	{
		hours = (time / 3600);
		time -= (hours * 3600);
	}
	while (time >= 60)
	{
	    minutes++;
	    time -= 60;
	}
	return (seconds = time);
}

stock RandomEx(min, max)
{
	new rand = random(max-min)+min;
	return rand;
}

stock GetFuel(vehicleid)
{
	return VehCore[vehicleid][vehFuel];
}

GetEngineStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(engine != 1)
		return 0;

	return 1;
}

stock GetNearestVehicle(playerid, Float:radius)
{
	static
	    Float:fX,
	    Float:fY,
	    Float:fZ;

	for (new i = 1; i != MAX_VEHICLES; i ++) if (IsValidVehicle(i) && GetVehiclePos(i, fX, fY, fZ))
	{
	    if (IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ)) return i;
	}
	return INVALID_VEHICLE_ID;
}

stock LockVehicle(vehicleid,status)
{
	new engine,lights,alarm,doors,bonnet,boot,objective;
	GetVehicleParamsEx(vehicleid,engine,lights,alarm,doors,bonnet,boot,objective);
	SetVehicleParamsEx(vehicleid,engine,lights,alarm,status,bonnet,boot,objective);
}

stock GetTrunkStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(boot != 1)
		return 0;

	return 1;
}

stock IsPlayerNearBoot(playerid, vehicleid)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetVehicleBoot(vehicleid, fX, fY, fZ);

	return (GetPlayerVirtualWorld(playerid) == GetVehicleVirtualWorld(vehicleid)) && IsPlayerInRangeOfPoint(playerid, 3.5, fX, fY, fZ);
}

stock GetVehicleBoot(vehicleid, &Float:x, &Float:y, &Float:z)
{
	if (!GetVehicleModel(vehicleid) || vehicleid == INVALID_VEHICLE_ID)
	    return (x = 0.0, y = 0.0, z = 0.0), 0;

	static
	    Float:pos[7]
	;
	GetVehicleModelInfo(GetVehicleModel(vehicleid), VEHICLE_MODEL_INFO_SIZE, pos[0], pos[1], pos[2]);
	GetVehiclePos(vehicleid, pos[3], pos[4], pos[5]);
	GetVehicleZAngle(vehicleid, pos[6]);

	x = pos[3] - (floatsqroot(pos[1] + pos[1]) * floatsin(-pos[6], degrees));
	y = pos[4] - (floatsqroot(pos[1] + pos[1]) * floatcos(-pos[6], degrees));
 	z = pos[5];

	return 1;
}

stock GetLightStatus(vehicleid)
{
	static
	engine,
	lights,
	alarm,
	doors,
	bonnet,
	boot,
	objective;

	GetVehicleParamsEx(vehicleid, engine, lights, alarm, doors, bonnet, boot, objective);

	if(lights != 1)
		return 0;

	return 1;
}

stock IsEngineVehicle(vehicleid)
{
	static const g_aEngineStatus[] = {
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1,
	    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1,
	    1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0
	};
    new modelid = GetVehicleModel(vehicleid);

    if (modelid < 400 || modelid > 611)
        return 0;

    return (g_aEngineStatus[modelid - 400]);
}

stock IsDoorVehicle(vehicleid)
{
	switch (GetVehicleModel(vehicleid))
	{
		case 400..424, 426..429, 431..440, 442..445, 451, 455, 456, 458, 459, 466, 467, 470, 474, 475:
		    return 1;

		case 477..480, 482, 483, 486, 489, 490..492, 494..496, 498..500, 502..508, 514..518, 524..529, 533..536:
		    return 1;

		case 540..547, 549..552, 554..562, 565..568, 573, 575, 576, 578..580, 582, 585, 587..589, 596..605, 609:
			return 1;
	}
	return 0;
}

FormatNumber(number, prefix[] = "$")
{
	static
		value[32],
		length;

	format(value, sizeof(value), "%d", (number < 0) ? (-number) : (number));

	if ((length = strlen(value)) > 3)
	{
		for (new i = length, l = 0; --i >= 0; l ++) {
		    if ((l > 0) && (l % 3 == 0)) strins(value, ",", i + 1);
		}
	}
	if (prefix[0] != 0)
	    strins(value, prefix, 0);

	if (number < 0)
		strins(value, "-", 0);

	return value;
}

stock GetServerTimeString()
{
	new AmPm[3], TimeStr[16], mn, hr, sec;
	gettime(hr, mn, sec);

	if(hr >= 0 && hr <= 11) AmPm = "AM";
	else if(hr >= 12 && hr <= 23) AmPm = "PM";

	format(TimeStr,sizeof(TimeStr),"%02d:%02d:%02d %s", hr, mn, sec, AmPm);
	return TimeStr;
}

stock GiveMoney(playerid, amount, reason[] = "unknown")
{
	new str[400];
    if(amount > 0)
    {
        format(str, sizeof(str),"[%s] Uang %s bertambah sebesar $%i. (T: $%i) (R: %s). ", GetServerTimeString(), GetName(playerid), amount, PlayerData[playerid][pMoney], reason);

    }
    else 
    {
        format(str, sizeof(str),"[%s] Uang %s berkurang sebesar $%i. (T: $%i) (R: %s). ~", GetServerTimeString(), GetName(playerid), amount, PlayerData[playerid][pMoney], reason);
    }
	GivePlayerMoney(playerid, amount);
    PlayerData[playerid][pMoney] += amount;
	printf("%s",str);
	// AddToLog("cash", gstr);

    return 1;
}

ProxDetectorS(Float:radi, playerid, targetid) {
	new
		Float: fp_playerPos[3];
	GetPlayerPos(targetid, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]);
	if(IsPlayerInRangeOfPoint(playerid, radi, fp_playerPos[0], fp_playerPos[1], fp_playerPos[2]) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid))
	{
		return 1;
	}
	return 0;
}

stock IsPlayerSpawned(playerid)
{
	if (playerid < 0 || playerid >= MAX_PLAYERS)
	    return 0;

	return (GetPlayerState(playerid) != PLAYER_STATE_SPECTATING && GetPlayerState(playerid) != PLAYER_STATE_NONE && GetPlayerState(playerid) != PLAYER_STATE_WASTED);
}

SendPlayerToPlayer(playerid, targetid)
{
	new
	    Float:x,
	    Float:y,
	    Float:z;

	GetPlayerPos(targetid, x, y, z);

	if (IsPlayerInAnyVehicle(playerid))
	{
	    SetVehiclePos(GetPlayerVehicleID(playerid), x, y + 2, z);
		LinkVehicleToInterior(GetPlayerVehicleID(playerid), GetPlayerInterior(targetid));
	}
	else
		SetPlayerPos(playerid, x + 1, y, z);

	SetPlayerInterior(playerid, GetPlayerInterior(targetid));
	SetPlayerVirtualWorld(playerid, GetPlayerVirtualWorld(targetid));

	// PlayerData[playerid][pHouse] = PlayerData[targetid][pHouse];
	PlayerData[playerid][pBusiness] = PlayerData[targetid][pBusiness];
	PlayerData[playerid][pEntrance] = PlayerData[targetid][pEntrance];
	// PlayerData[playerid][pHospitalInt]  = PlayerData[targetid][pHospitalInt];
}

stock SetPlayerPosEx(playerid, Float:x, Float:y, Float:z, time = 2000)
{
	if (PlayerData[playerid][pFreeze])
	{
	    KillTimer(PlayerData[playerid][pFreezeTimer]);

	    PlayerData[playerid][pFreeze] = 0;
	    TogglePlayerControllable(playerid, 1);
	}
	SetPlayerPos(playerid, x, y, z + 0.5);
	TogglePlayerControllable(playerid, 0);

	PlayerData[playerid][pFreeze] = 1;
	PlayerData[playerid][pFreezeTimer] = SetTimerEx("SetPlayerToUnfreeze", time, false, "dfff", playerid, x, y, z);
	return 1;
}

Function:SetPlayerToUnfreeze(playerid, Float:x, Float:y, Float:z)
{
	if (!IsPlayerInRangeOfPoint(playerid, 15.0, x, y, z))
	    return 0;

	PlayerData[playerid][pFreeze] = 0;

	SetPlayerPos(playerid, x, y, z);
	TogglePlayerControllable(playerid, 1);
	return 1;
}

stock ShowPressButton(playerid, text[], interval = 3000)
{
    if(PlayerData[playerid][pPressBtn]) return 1;

    PlayerPlaySound(playerid, 1057 , 0.0, 0.0, 0.0);
    PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], sprintf("%s", text));
    PlayerTextDrawShow(playerid, PlayerTextdraws[playerid][textdraw_petunjuk]);

    PlayerData[playerid][pPressBtn] = true;
    PlayerData[playerid][pPressBtnTime] = SetTimerEx("HidePressButton", interval, false, "d", playerid);
    return 1;
}

Function:HidePressButton(playerid)
{
    PlayerData[playerid][pPressBtn] = false;
    PlayerTextDrawSetString(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], "_");
    PlayerTextDrawHide(playerid, PlayerTextdraws[playerid][textdraw_petunjuk]);
    KillTimer(PlayerData[playerid][pPressBtnTime]);
    return 1;
}

stock CreateAllPlayerTextdraw(playerid)
{
	PlayerTextdraws[playerid][textdraw_petunjuk] = CreatePlayerTextDraw(playerid, 4.000000, 181.000000, "");
	PlayerTextDrawFont(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 1);
	PlayerTextDrawLetterSize(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 0.249999, 1.250000);
	PlayerTextDrawTextSize(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 146.000000, -65.500000);
	PlayerTextDrawSetOutline(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 1);
	PlayerTextDrawSetShadow(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 0);
	PlayerTextDrawAlignment(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 1);
	PlayerTextDrawColor(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], -1);
	PlayerTextDrawBackgroundColor(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 255);
	PlayerTextDrawBoxColor(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 255);
	PlayerTextDrawUseBox(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 1);
	PlayerTextDrawSetProportional(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 1);
	PlayerTextDrawSetSelectable(playerid, PlayerTextdraws[playerid][textdraw_petunjuk], 0);
	return 1;
}