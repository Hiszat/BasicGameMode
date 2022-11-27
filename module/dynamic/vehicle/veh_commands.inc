CMD:v(playerid, params[])
{
	new
	    type[24],
	    string[128],
		vehicleid = GetPlayerVehicleID(playerid),
		pvid;

	if (sscanf(params, "s[24]S()[128]", type, string))
	{
	    SendSyntaxMessage(playerid, "/v(ehicle) [name]");
	    SendClientMessage(playerid, X11_LIGHTBLUE, "Names:{FFFFFF} list, lock, engine, hood, trunk, light");
	    return 1;
	}
	if(!strcmp(type, "engine", true))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			pvid = Vehicle_GetID(vehicleid);

			if(!IsEngineVehicle(vehicleid))
				return SendErrorMessage(playerid, "Anda tidak berada di dalam kendaraan mesin apa pun!");

			if(pvid != -1 && !Vehicle_HaveAccess(playerid, pvid))
				return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR,  "~r~ERROR ~w~Kamu tidak memiliki kunci kendaraan ini!", 2);
				
			if(GetEngineStatus(vehicleid))
			{
			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s memasukkan kunci ke dalam kunci kontak dan menghentikan mesin.", ReturnName(playerid));
				EngineStatus(playerid);
			}
			else
			{
				if(VehCore[vehicleid][vehHandbrake])
					return SendErrorMessage(playerid, "Harap nonaktifkan rem tangan kendaraan terlebih dahulu!");

			    SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  "Menyalakan mesin....", 3);
				SetTimerEx("EngineStatus", 3000, false, "i", playerid);
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s memasukkan kunci ke dalam kunci kontak dan menyalakan mesin.", ReturnName(playerid));
			}
		}
	}
	else if(!strcmp(type, "hood", true))
	{
	    if(IsPlayerInAnyVehicle(playerid))
			return SendErrorMessage(playerid, "You must be in front of Vehicle.");

	    new vvehicleid = GetNearestVehicle(playerid, 4.5);

	    if(vvehicleid == INVALID_VEHICLE_ID)
	    	return SendErrorMessage(playerid, "You're not in range of any vehicles.");

	    switch (VehCore[vvehicleid][vehHood])
	    {
	    	case false:
	    	{
	    		SwitchVehicleBonnet(vvehicleid, true);
	    		SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  "Hood ~g~Opened", 1);
	   		 	ApplyAnimation(playerid, "CARRY", "liftup", 3.0, 0, 0, 0, 0, 0);
	   		 	VehCore[vvehicleid][vehHood] = true;
	    	}
	    	case true:
	    	{
	    		SwitchVehicleBonnet(vvehicleid, false);
	    		SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  "Hood ~r~Closed", 1);
	    		ApplyAnimation(playerid, "CARRY", "putdwn", 3.0, 0, 0, 0, 0, 0);
	    		VehCore[vvehicleid][vehHood] = false;
	    	}
	    }
	}
	else if(!strcmp(type, "trunk", true))
	{

		new vvehicleid = GetNearestVehicle(playerid, 4.5);

		if(vvehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You are not in behind of any vehicle!");

		if(!IsPlayerNearBoot(playerid, vvehicleid))
			return SendErrorMessage(playerid, "You are not in behind of any vehicle!");

    	switch (GetTrunkStatus(vvehicleid))
    	{
    		case false:
    		{
    			SwitchVehicleBoot(vvehicleid, true);
    			SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  "Trunk ~g~Opened", 1);
    		}
    		case true:
    		{
    			SwitchVehicleBoot(vvehicleid, false);
    			SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  "Trunk ~r~Closed", 1);
    		}
    	}
	}
	else if(!strcmp(type, "light", true))
	{
		if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
		{
			if(!IsEngineVehicle(vehicleid))
				return SendErrorMessage(playerid, "This vehicle doesn't have a lights!");

			switch(GetLightStatus(vehicleid))
			{
				case false:
				{
					SwitchVehicleLight(vehicleid, true);
					SendClientMessage(playerid, X11_LIGHTBLUE, "VEHICLE: {FFFFFF}Lights {00FF00}ON");
				}
				case true:
				{
					SwitchVehicleLight(vehicleid, false);
					SendClientMessage(playerid, X11_LIGHTBLUE, "VEHICLE: {FFFFFF}Lights {FF0000}OFF");
				}
			}
		}
	}
	else if(!strcmp(type, "lock", true))
	{
		new bool:found = false, carid = -1;

		if(IsPlayerInAnyVehicle(playerid))
		{
			if((carid = Vehicle_Inside(playerid)) != -1)
			{
				if(Vehicle_HaveAccess(playerid, carid))
				{
					PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
					VehicleData[carid][vLocked] = !(VehicleData[carid][vLocked]);
					LockVehicle(VehicleData[carid][vVehicle], VehicleData[carid][vLocked]);

					SendTextDrawMessageEx(playerid, NOTIFICATION_INFO,  sprintf("%s %s", GetVehicleName(VehicleData[carid][vVehicle]), (VehicleData[carid][vLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
				}
				else
					return SendClientMessage(playerid, -1, "You don't have key for this vehicle!");
			}
		}
		else
		{
			new str[512];
			format(str, sizeof(str), "VehiceId\tModel\tStatus\n");
			foreach(new i : PlayerVehicle) if(IsValidVehicle(VehicleData[i][vVehicle]) && Vehicle_HaveAccess(playerid, i))
			{
				format(str, sizeof(str), "%s%d\t%s\t%s\n", str, VehicleData[i][vVehicle], GetVehicleName(VehicleData[i][vVehicle]), (VehicleData[i][vLocked]) ? ("{FF0000}Locked") : ("{00FF00}Unlocked"));
			}
			found = true;
			if(found)
				Dialog_Show(playerid, LockVehicle, DIALOG_STYLE_TABLIST_HEADERS, "Lock Vehicle", str, "Select", "Close");
			else
				SendErrorMessage(playerid, "You don't have any vehicle.");
		}
	}
	else if(!strcmp(type, "handbrake", true))
	{
		if(vehicleid == INVALID_VEHICLE_ID)
			return SendErrorMessage(playerid, "You must driving a vehicle!");

		if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
			return SendErrorMessage(playerid, "You must driving a vehicle!");

		if(!IsDoorVehicle(vehicleid))
			return SendErrorMessage(playerid, "You can't handbrake this vehicle!");
		
		if(GetEngineStatus(vehicleid))
			return SendErrorMessage(playerid, "Turn off your vehicle engine first!");

		VehCore[vehicleid][vehHandbrake] = (!VehCore[vehicleid][vehHandbrake]);
		SendClientMessageEx(playerid, X11_LIGHTBLUE, "VEHICLE: {FFFFFF}You have successfully %s {FFFFFF}vehicle Handbrake!", (VehCore[vehicleid][vehHandbrake]) ? ("{00FF00}engaged") : ("{FF0000}disengaged"));
		GetVehiclePos(vehicleid, VehCore[vehicleid][vehHandbrakePos][0], VehCore[vehicleid][vehHandbrakePos][1], VehCore[vehicleid][vehHandbrakePos][2]);
		GetVehicleZAngle(vehicleid, VehCore[vehicleid][vehHandbrakePos][3]);
	}
	else if(!strcmp(type, "list", true))
	{
	    new bool:have, str[512];
	    format(str, sizeof(str), "Model\tPlate\tInsurance\n");
		foreach(new i : PlayerVehicle)
		{
		    if(Vehicle_IsOwner(playerid, i))
		    {
		        if(VehicleData[i][vInsuTime] != 0)
		        {
		            format(str, sizeof(str), "%s%s(Insurance)\t%s\t%d Left\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPlate], VehicleData[i][vInsurance]);
				}
				else if(VehicleData[i][vRental] != -1)
		        {
		            format(str, sizeof(str), "%s%s(Rental)\t%s\tN/A\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPlate]);
				}
				else if(VehicleData[i][vHouse] != -1)
		        {
		            format(str, sizeof(str), "%s%s(House Parked)\t%s\t%d Left\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPlate], VehicleData[i][vInsurance]);
				}
				else
				{
		            format(str, sizeof(str), "%s%s(ID: %d)\t%s\t%d Left\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vVehicle], VehicleData[i][vPlate], VehicleData[i][vInsurance]);
				}
			}
			have = true;
		}
		if(have)
		    Dialog_Show(playerid, Kosong, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle List", str, "Close", "");
		else
			SendErrorMessage(playerid, "You don't have any Vehicles!");
	}
	return 1;
}

Dialog:LockVehicle(playerid, response, listitem, inputtext[])
{
	new count, Float:pos[3];
	if(response)
	{
		foreach(new i : PlayerVehicle)
		{
			if(IsValidVehicle(VehicleData[i][vVehicle]))
			{
				if(Vehicle_HaveAccess(playerid, i) && count++ == listitem)
				{
					GetVehiclePos(VehicleData[i][vVehicle], pos[0], pos[1], pos[2]);
					if(IsPlayerInRangeOfPoint(playerid, 5.0, pos[0], pos[1], pos[2]))
					{
						PlayerPlaySound(playerid, 1145, 0.0, 0.0, 0.0);
						VehicleData[i][vLocked] = !(VehicleData[i][vLocked]);
						LockVehicle(VehicleData[i][vVehicle], VehicleData[i][vLocked]);
						SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("%s %s", GetVehicleName(VehicleData[i][vVehicle]), (VehicleData[i][vLocked]) ? ("~r~Locked") : ("~g~Unlocked")), 3);
					}
				}
			}
		}
	}
	return 1;
}