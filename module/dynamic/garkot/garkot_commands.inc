CMD:setparkpos(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 4) return PermissionError(playerid);

	new id;
	if(sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/setparkpos [id]");
	if(!Iter_Contains(Parks, id)) return SendErrorMessage(playerid, "Invalid ID.");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerFacingAngle(playerid, ang);
	GetPlayerPos(playerid, x, y, z);
	GarkotData[id][parkX] = x;
	GarkotData[id][parkY] = y;
	GarkotData[id][parkZ] = z;
	GarkotData[id][parkA] = ang;
	GarkotData[id][parkInt] = GetPlayerInterior(playerid);
	GarkotData[id][parkWorld] = GetPlayerVirtualWorld(playerid);

	if(IsValidDynamicActor(GarkotData[id][parkActor]))
		DestroyDynamicActor(GarkotData[id][parkActor]);

	if(IsValidDynamic3DTextLabel(GarkotData[id][parkLabel]))
		DestroyDynamic3DTextLabel(GarkotData[id][parkLabel]), GarkotData[id][parkLabel] = Text3D: INVALID_3DTEXT_ID;

	if(IsValidDynamicMapIcon(GarkotData[id][parkMap]))	
		DestroyDynamicMapIcon(GarkotData[id][parkMap]);

	
	new str[128];
	format(str, sizeof(str), "[[ GARASI KOTA ]]", id, GetLocation(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ]));
	GarkotData[id][parkActor] = CreateDynamicActor(g_aMaleSkins[random(sizeof(g_aMaleSkins))], GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], GarkotData[id][parkA], 1, 40.0, 0, 0, -1, 50.0, -1, 0);
	GarkotData[id][parkLabel] = CreateDynamic3DTextLabel(str, X11_LIGHTBLUE, GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ] + 1.0, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, GarkotData[id][parkWorld], GarkotData[id][parkInt], -1, 10.0);
	GarkotData[id][parkMap] = CreateDynamicMapIcon(GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], 55, -1, -1, -1, -1, 100.0);
	Park_Save(id);
	return 1;
}

CMD:setparkspawn(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 4) return PermissionError(playerid);

	new id;
	if(sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/setparkspawn [id]");
	if(!Iter_Contains(Parks, id)) return SendErrorMessage(playerid, "Invalid ID.");
	new Float:x, Float:y, Float:z, Float:ang;
	GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, ang);
	GarkotData[id][spawn][0] = x;
	GarkotData[id][spawn][1] = y;
	GarkotData[id][spawn][2] = z;
    GarkotData[id][spawn][3] = ang;
	GarkotData[id][parkInt] = GetPlayerInterior(playerid);
	GarkotData[id][parkWorld] = GetPlayerVirtualWorld(playerid);

	Park_Save(id);
	return 1;
}

CMD:removepark(playerid, params[])
{
    if(PlayerData[playerid][pAdmin] < 4) return PermissionError(playerid);
		
	new id, query[512];
	if(sscanf(params, "i", id)) return SendSyntaxMessage(playerid, "/removepark [id]");
	if(!Iter_Contains(Parks, id)) return SendErrorMessage(playerid, "Invalid ID.");

	DestroyDynamicActor(GarkotData[id][parkActor]);
	DestroyDynamic3DTextLabel(GarkotData[id][parkLabel]);
	DestroyDynamicPickup(GarkotData[id][parkActor]);
	DestroyDynamicMapIcon(GarkotData[id][parkMap]);
	
	GarkotData[id][parkX] = GarkotData[id][parkY] = GarkotData[id][parkZ] = 0.0;
	GarkotData[id][parkInt] = GarkotData[id][parkWorld] = 0;
	GarkotData[id][parkActor] = -1;
	GarkotData[id][parkLabel] = Text3D: -1;
	Iter_Remove(Parks, id);
	
	mysql_format(sqlcon, query, sizeof(query), "DELETE FROM parks WHERE id=%d", id);
	mysql_tquery(sqlcon, query);
	SendServerMessage(playerid, "Menghapus ID Park Point %d.", id);
	return 1;
}

CMD:gotopark(playerid, params[])
{
	new id;
	if(PlayerData[playerid][pAdmin] < 4)
		
	if(sscanf(params, "d", id))
		return SendSyntaxMessage(playerid, "/gotopark [id]");
	if(!Iter_Contains(Parks, id)) return SendErrorMessage(playerid, "Park Point ID tidak ada.");
	
	SetPlayerPosEx(playerid, GarkotData[id][parkX], GarkotData[id][parkY], GarkotData[id][parkZ], 2000);
    SetPlayerInterior(playerid, GarkotData[id][parkInt]);
    SetPlayerVirtualWorld(playerid, GarkotData[id][parkWorld]);
	SendServerMessage(playerid, "Teleport ke ID Park Point %d", id);
	return 1;
}