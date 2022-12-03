CMD:rentinfo(playerid, params[])
{
	new bool:have, str[512], time[3];
	format(str, sizeof(str), "Model(ID)\tDuration\n");
	foreach(new i : PlayerVehicle)
	{
		if(Vehicle_IsOwner(playerid, i) && IsValidVehicle(VehicleData[i][vVehicle]) && VehicleData[i][vRental] != -1)
		{
		    GetElapsedTime(VehicleData[i][vRentTime], time[0], time[1], time[2]);
		    format(str, sizeof(str), "%s%s(%d)\t%02d:%02d:%02d\n", str, GetVehicleModelName(VehicleData[i][vModel]),VehicleData[i][vVehicle], time[0], time[1], time[2]);
			have = true;
		}
	}
	if(have)
		Dialog_Show(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, "Rental Information", str, "Close", "");
	else
		SendErrorMessage(playerid, "Kamu tidak memiliki kendaraan Rental!");
	return 1;
}

CMD:editrental(playerid, params[])
{
    new
        id,
        type[24],
        string[128];

    if(PlayerData[playerid][pAdmin] < 6)
        return SendErrorMessage(playerid, "You don't have permission to use this command!");
        
    if(sscanf(params, "ds[24]S()[128]", id, type, string))
    {
        SendSyntaxMessage(playerid, "/editrental [id] [name]");
        SendClientMessage(playerid, X11_LIGHTBLUE, "Names:{FFFFFF} location, spawn, vehicle(1-2), price(1-2), delete");
        return 1;
    }
    if((id < 0 || id >= MAX_RENTAL))
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

	if(!RentData[id][rentExists])
        return SendErrorMessage(playerid, "You have specified an invalid ID.");

	if(!strcmp(type, "location", true))
	{
	    GetPlayerPos(playerid, RentData[id][rentPos][0], RentData[id][rentPos][1], RentData[id][rentPos][2]);
	    Rental_Save(id);
	    Rental_Refresh(id);
	    
	    SendAdminAction(playerid, "Kamu telah mengubah posisi Rental ID: %d", id);
	}
	else if(!strcmp(type, "vehicle1", true))
	{
	    new val;
	    if(sscanf(string, "d", val))
	        return SendSyntaxMessage(playerid, "/editrental [vehicle1] [model]");
	        
		if(val < 400 || val > 611)
			return SendErrorMessage(playerid, "Vehicle Number can't be below 400 or above 611 !");

		RentData[id][rentModel][0] = val;
		Rental_Save(id);
		SendAdminAction(playerid, "Kamu telah mengubah Vehicle Model 1 Rental ID: %d", id);
	}
	else if(!strcmp(type, "vehicle2", true))
	{
	    new val;
	    if(sscanf(string, "d", val))
	        return SendSyntaxMessage(playerid, "/editrental [vehicle2] [model]");

		if(val < 400 || val > 611)
			return SendErrorMessage(playerid, "Vehicle Number can't be below 400 or above 611 !");

		RentData[id][rentModel][1] = val;
		Rental_Save(id);
		SendAdminAction(playerid, "Kamu telah mengubah Vehicle Model 2 Rental ID: %d", id);
	}
	else if(!strcmp(type, "price1", true))
	{
	    new val[32];
	    if(sscanf(string, "s[32]", val))
	        return SendSyntaxMessage(playerid, "/editrental [price1] [price]");

		RentData[id][rentPrice][0] = strlen(val);
		Rental_Save(id);
		SendAdminAction(playerid, "Kamu telah mengubah Rental Price 1 Rental ID: %d", id);
	}
	else if(!strcmp(type, "price2", true))
	{
	    new val[32];
	    if(sscanf(string, "s", val))
	        return SendSyntaxMessage(playerid, "/editrental [price2] [price]");

		RentData[id][rentPrice][1] = strlen(val);
		Rental_Save(id);
		SendAdminAction(playerid, "Kamu telah mengubah Rental Price 2 Rental ID: %d", id);
	}
	else if(!strcmp(type, "spawn", true))
	{
	        
		GetPlayerPos(GetPlayerVehicleID(playerid), RentData[id][rentSpawn][0], RentData[id][rentSpawn][1], RentData[id][rentSpawn][2]);
		GetPlayerFacingAngle(GetPlayerVehicleID(playerid), RentData[id][rentSpawn][3]);
		
		SendAdminAction(playerid, "Kamu telah mengubah posisi Spawn Rental ID: %d", id);
		Rental_Save(id);
	}
	else if(!strcmp(type, "delete", true))
	{
		Rental_Delete(id);
		SendAdminAction(playerid, " %s has destroyed Rental ID: %d", GetName(playerid), id);
	}
	return 1;
}

CMD:createrental(playerid, params[])
{
	new vehicle[2], id;

    if (PlayerData[playerid][pAdmin] < 6)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if(sscanf(params, "dd", vehicle[0], vehicle[1]))
		return SendSyntaxMessage(playerid, "/createrental [Vehicle 1] [Vehicle 2]");
		
	id = Rental_Create(playerid, vehicle[0], vehicle[1]);
	
	if(id == -1)
	    return SendErrorMessage(playerid, "Kamu tidak bisa membuat lebih banyak Rental!");
	    
	SendServerMessage(playerid, "Kamu telah membuat Rental Point ID: %d", id);
	return 1;
}