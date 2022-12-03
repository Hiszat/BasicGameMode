CMD:radial(playerid, test[])
{
    new str[200], houseid = -1;

    strcat(str, "Umum\n");
    strcat(str, "Dokumen Pribadi\n");
    strcat(str, "Kendaraan\n");
    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid)) && (Berangkas_Nearest(playerid) != -1)) strcat(str, "Berangkas Rumah\n");
    if(GetNearbyGarkot(playerid) >= 0) strcat(str, "Garkot Menu\n");
    if(GetNearbyRental(playerid) >= 0) strcat(str, "Sewa Kendaraan\n");
    Dialog_Show(playerid, RadialMenu, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
    return 1;
}

Dialog:RadialMenu(playerid, response, listitem, inputtext[])
{
	if(response)
	{
        if(strcmp("Umum", inputtext, true) == 0)
        {
            new str[400];
            Dialog_Show(playerid, RadialUmum, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
        }
        if(strcmp("Kendaraan", inputtext, true) == 0)
        {
            new str[400];
            strcat(str, "Mesin\n");
            strcat(str, "Hood\n");
            strcat(str, "Kunci\n");
            strcat(str, "Kepemilikan\n");
            strcat(str, "Bagasi\n");
            strcat(str, "Lampu\n");
            strcat(str, "Rem Tangan\n");
            Dialog_Show(playerid, RadialVehicle, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
        }

        if(strcmp("Berangkas Rumah", inputtext, true) == 0)
        {
            static
                houseid = -1;

            //if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || GetFactionType(playerid) == FACTION_POLICE)) {
            if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid))) {
                House_OpenStorage(playerid, houseid);
                PlayerData[playerid][pStorageSelect] = 1;	
            }
            else SendErrorMessage(playerid, "You are not in range of your house interior.");
        }
		if(strcmp("Garkot Menu", inputtext, true) == 0)
        {
            new gid = GetNearbyGarkot(playerid);
			if(GarkotData[gid][spawn][0] == 0) return SendErrorMessage(playerid, "Tempat spawn untuk garasi belum di atur, hubungi admin");

            Dialog_Show(playerid, DialogGarkot, DIALOG_STYLE_LIST, "Garasi Kota ", "Taruh Kendaraan\nAmbil Kendaraan", "Select", "Close");
        }

        if(strcmp("Sewa Kendaraan", inputtext, true) == 0)
        {
            Dialog_Show(playerid, RentalMenu, DIALOG_STYLE_LIST, "Penyewaan Kendaraan", "Sewa Kendaraan\nKembalikan Kendaraan", "Select", "Close");
        }
    }
    return 1;
}

Dialog:RadialUmum(playerid, response, listitem, inputtext[])
{

    return 1;
}

Dialog:RadialVehicle(playerid, response, listitem, inputtext[])
{
    new
		vehicleid = GetPlayerVehicleID(playerid),
		pvid;

    if(response)
    {
        if(strcmp("Mesin", inputtext, true) == 0)
        {
            if(IsPlayerInAnyVehicle(playerid) && GetPlayerState(playerid) == PLAYER_STATE_DRIVER)
            {
                pvid = Vehicle_GetID(vehicleid);

                if(!IsEngineVehicle(vehicleid))
                    return SendErrorMessage(playerid, "You're not inside of any engine vehicle!");

                if(pvid != -1 && !Vehicle_HaveAccess(playerid, pvid))
                    return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR,  "~r~ERROR ~w~Kamu tidak memiliki kunci kendaraan ini!", 2);
                    
                if(GetEngineStatus(vehicleid))
                {
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s memasukkan kunci ke kunci kontak dan menghentikan mesin.", ReturnName(playerid));
                    EngineStatus(playerid);
                }
                else
                {
                    if(VehCore[vehicleid][vehHandbrake])
                        return SendErrorMessage(playerid, "Harap nonaktifkan rem tangan kendaraan terlebih dahulu!");

                    StartPlayerProgressBarTextdraw(playerid, 100, "Menyalakan Mesin", 60, "EngineStatus", 1687547391);
                    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s memasukkan kunci ke kunci kontak dan menyalakan mesin.", ReturnName(playerid));
                }
            }
        }
        else if(strcmp("Hood", inputtext, true) == 0)
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
        else if(strcmp("Bagasi", inputtext, true) == 0)
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
        else if(strcmp("Lampu", inputtext, true) == 0)
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
        else if(strcmp("Kunci", inputtext, true) == 0)
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
        else if(strcmp("Rem Tangan", inputtext, true) == 0)
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
        else if(strcmp("Kepemilikan", inputtext, true) == 0)
        {
            new bool:have, str[512];
            format(str, sizeof(str), "Model Kendaraan\tNomor Kendaraan\tInfo Kendaraan\n");
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
                        format(str, sizeof(str), "%s%s(Sewa)\t%s\tN/A\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPlate]);
                    }
                    else if(VehicleData[i][vHouse] != -1)
                    {
                        format(str, sizeof(str), "%s%s(House Parked)\t%s\t%d Left\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPlate], VehicleData[i][vInsurance]);
                    }
                    else if(VehicleData[i][vPark] != -1)
                    {
                        format(str, sizeof(str), "%s%s(Garasi Kota ID: %s)\t%s\tN/A\n", str, GetVehicleModelName(VehicleData[i][vModel]), VehicleData[i][vPark]);
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
    }
    return 1;
}