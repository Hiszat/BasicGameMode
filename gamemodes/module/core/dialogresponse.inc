public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch(dialogid){
		case DIALOG_REG_CONFIRM: {
			if(response){
				new tempAge[24];
				GetPVarString(playerid, "Age", tempAge, sizeof(tempAge));
				format(PlayerData[playerid][pAge], 24, tempAge);
				PlayerData[playerid][pGender] = GetPVarInt(playerid, "Gender");	
				SubmitPassport(playerid);
				DeletePVar(playerid, "Age");
				DeletePVar(playerid, "Gender");
			}else{
				InputAge(playerid);
				DeletePVar(playerid, "Age");
				DeletePVar(playerid, "Gender");
			}
			
		}
        case DIALOG_GENDER: {
            if(!response){
                InputAge(playerid);
            }
			new tempAge[24];
			GetPVarString(playerid, "Age", tempAge, sizeof(tempAge));
			SetPVarInt(playerid, "Gender", listitem + 1);
			new kel[20], str[130];
			format(kel, sizeof(kel), GetPVarInt(playerid, "Gender") == 1 ? "Male | Laki - Laki" : "Female | Perempuan");
			format(str, sizeof(str), "Apakah kamu yakin dengan ketentuan berikut ?\nNama\t\t: %s\nKelamin\t: %s\nUmur \t\t: %s", ReturnName(playerid), kel, tempAge);
			ShowPlayerDialog(playerid, DIALOG_REG_CONFIRM, DIALOG_STYLE_MSGBOX, "Register Confirm", str, "Yakin", "Buat Ulang");
        }
        case DIALOG_DATEB: {
            if (response)
	        {
	            new
	        		iDay,
	        		iMonth,
	        		iYear;

	            static const
	                arrMonthDays[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	            if (sscanf(inputtext, "p</>ddd", iDay, iMonth, iYear)) {
	                ShowPlayerDialog(playerid, DIALOG_DATEB, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid format specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
	        	}
	        	else if (iYear < 1900 || iYear > 2014) {
	        	    ShowPlayerDialog(playerid, DIALOG_DATEB, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid year specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
	        	}
	        	else if (iMonth < 1 || iMonth > 12) {
	        	    ShowPlayerDialog(playerid, DIALOG_DATEB, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid month specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
	        	}
	        	else if (iDay < 1 || iDay > arrMonthDays[iMonth - 1]) {
	        	    ShowPlayerDialog(playerid, DIALOG_DATEB, DIALOG_STYLE_INPUT, "Date of Birth", "Error: Invalid day specified!\n\nPlease enter your date of birth below (DD/MM/YYYY):", "Submit", "Cancel");
	        	}
	        	else {
					SetPVarString(playerid, "Age", inputtext);
                    InputGender(playerid);
	        	}
	        }else{
                Kick(playerid);
            }
	        return 1;
        }
        case DIALOG_RADIAL_U: {
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
                                // DIALOG_LOCK_V(VehicleData[carid][vVehicle], VehicleData[carid][vLocked]);

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
                            ShowPlayerDialog(playerid, DIALOG_LOCK_V, DIALOG_STYLE_TABLIST_HEADERS, "Lock Vehicle", str, "Select", "Close");
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
                        ShowPlayerDialog(playerid, DIALOG_KOSONG, DIALOG_STYLE_TABLIST_HEADERS, "Vehicle List", str, "Close", "");
                    else
                        SendErrorMessage(playerid, "You don't have any Vehicles!");
                }
            }
            return 1;
        }
        case DIALOG_RADIAL: {
            if(response)
	        {
                if(strcmp("Umum", inputtext, true) == 0)
                {
                    new str[400];
                    ShowPlayerDialog(playerid, DIALOG_RADIAL_U, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
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
                    ShowPlayerDialog(playerid, DIALOG_RADIAL_V, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
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
                    ShowPlayerDialog(playerid, DIALOG_GARKOT, DIALOG_STYLE_LIST, "Garasi Kota ", "Taruh Kendaraan\nAmbil Kendaraan", "Select", "Close");
                }
        
                if(strcmp("Sewa Kendaraan", inputtext, true) == 0)
                {
                    ShowPlayerDialog(playerid, DIALOG_RENTAL, DIALOG_STYLE_LIST, "Penyewaan Kendaraan", "Sewa Kendaraan\nKembalikan Kendaraan", "Select", "Close");
                }
            }
            return 1;
        }
        case DIALOG_LOGIN :{
            if(!response)
	            return Kick(playerid);
	        
            if(strlen(inputtext) < 1)
            {
                new str[256];
                format(str, sizeof(str), "Selamat datang kembali di server "SERVER_NAME"!\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk masuk:", GetName(playerid));
                ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "MASUK", str, "Login", "Exit");
                return 1;
            }
            new pwQuery[256], hash[BCRYPT_HASH_LENGTH];
            mysql_format(sqlcon, pwQuery, sizeof(pwQuery), "SELECT Password FROM users WHERE username = '%e' LIMIT 1", GetName(playerid));
            mysql_query(sqlcon, pwQuery);
                
            cache_get_value_name(0, "Password", hash, sizeof(hash));
                
            bcrypt_verify(playerid, "OnPlayerPasswordChecked", inputtext, hash);
            return 1;
        }
        case DIALOG_REGISTER:{
            if(!response)
	            return Kick(playerid);

            new str[256];
            format(str, sizeof(str), "Selamat datang di server: "SERVER_NAME"\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\nERROR: Panjang kata sandi tidak boleh di bawah 7 atau di atas 32!n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk mendaftar:", GetName(playerid));

            if(strlen(inputtext) < 7)
                return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "DAFTAR", str, "Select", "Cancel");

            if(strlen(inputtext) > 32)
                return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "DAFTAR", str, "Select", "Cancel");

            bcrypt_hash(playerid, "HashPlayerPassword", inputtext, BCRYPT_COST);
            return 1;
        }
	    case DIALOG_RENTAL:
	    {
	        if(response)
	        {
	            new rentid = PlayerData[playerid][pRenting];
	            if(GetMoney(playerid) < RentData[rentid][rentPrice][listitem])
	                return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");
    
	    		new str[256];
	    		format(str, sizeof(str), "{FFFFFF}Berapa jam kamu ingin menggunakan kendaraan Rental ini ?\n{FFFFFF}Maksimal adalah {FFFF00}4 jam\n\n{FFFFFF}Harga per Jam: {009000}%s", FormatNumber(RentData[rentid][rentPrice][listitem]));
	    		ShowPlayerDialog(playerid, DIALOG_RENTTIME, DIALOG_STYLE_INPUT, "{FFFFFF}Rental Time", str, "Rental", "Close");
	    		PlayerData[playerid][pListitem] = listitem;
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSX :
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);

	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_x] = posisi;

	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSY:
	    {
	    	if(response)
	    	{

	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_y] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSZ:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_z] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSRX:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_rx] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSRY:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_ry] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSRZ:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_rz] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSSX:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_sx] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSSY:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			posisi,
	    			pToys[playerid][toySelect[playerid]][toy_sz]);
    
	    		pToys[playerid][toySelect[playerid]][toy_sy] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSSZ:
	    {
	    	if(response)
	    	{
	    		if(!toyToggle[playerid][toySelect[playerid]])
	    			return SendErrorMessage(playerid, "Please attach your accessory first!");

	    		new Float:posisi = floatstr(inputtext);
    
	    		SetPlayerAttachedObject(playerid,
	    			toySelect[playerid],
	    			pToys[playerid][toySelect[playerid]][toy_model],
	    			pToys[playerid][toySelect[playerid]][toy_bone],
	    			pToys[playerid][toySelect[playerid]][toy_x],
	    			pToys[playerid][toySelect[playerid]][toy_y],
	    			pToys[playerid][toySelect[playerid]][toy_z],
	    			pToys[playerid][toySelect[playerid]][toy_rx],
	    			pToys[playerid][toySelect[playerid]][toy_ry],
	    			pToys[playerid][toySelect[playerid]][toy_rz],
	    			pToys[playerid][toySelect[playerid]][toy_sx],
	    			pToys[playerid][toySelect[playerid]][toy_sy],
	    			posisi);
    
	    		pToys[playerid][toySelect[playerid]][toy_sz] = posisi;
	    		cmd_acc(playerid, "");

	    		SavePlayerToys(playerid);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSISIBUY:
	    {
	    	if(response)
	    	{
	            GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
	    		SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "> %s telah membayar $%s dan mengambil toys", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]));
	    		// benerin nanti
	    		// BusinessData[PlayerData[playerid][pBusiness]][bizProducts]--;		
	    		// BusinessData[PlayerData[playerid][pBusiness]][bizVault] += PlayerData[playerid][pSkinPrice];
	    		new slot = GetPlayerFreeToySlot(playerid);
	    		printf("%s", PlayerData[playerid][pTempModel]);
	    		pToys[playerid][slot][toy_model] = PlayerData[playerid][pTempModel];
	    		pToys[playerid][slot][toy_bone] = listitem + 1;
	    		pToys[playerid][slot][toy_sx] = 1.0;
	    		pToys[playerid][slot][toy_sy] = 1.0;
	    		pToys[playerid][slot][toy_sz] = 1.0;
	    		toySelect[playerid] = slot;
	    		SetPlayerAttachedObject(playerid, slot, pToys[playerid][slot][toy_model], listitem + 1);
	    		EditAttachedObject(playerid, toySelect[playerid]);
	    	}
            return 1;
	    }
	    case DIALOG_TOYPOSISI:
	    {
	    	if(response)
	    	{
	    		pToys[playerid][toySelect[playerid]][toy_bone] = listitem + 1;
	    		if(toyToggle[playerid][toySelect[playerid]])
	    		{
	    			RemovePlayerAttachedObject(playerid, toySelect[playerid]);
	    		}
	    		SetPlayerAttachedObject(playerid,
	    				toySelect[playerid],
	    				pToys[playerid][toySelect[playerid]][toy_model],
	    				pToys[playerid][toySelect[playerid]][toy_bone],
	    				pToys[playerid][toySelect[playerid]][toy_x],
	    				pToys[playerid][toySelect[playerid]][toy_y],
	    				pToys[playerid][toySelect[playerid]][toy_z],
	    				pToys[playerid][toySelect[playerid]][toy_rx],
	    				pToys[playerid][toySelect[playerid]][toy_ry],
	    				pToys[playerid][toySelect[playerid]][toy_rz],
	    				pToys[playerid][toySelect[playerid]][toy_sx],
	    				pToys[playerid][toySelect[playerid]][toy_sy],
	    				pToys[playerid][toySelect[playerid]][toy_sz]);
	    		SendServerMessage(playerid, "Accessory new bone position now is {FFFF00}%s", Bone_Name[listitem + 1]);
	    	}
            return 1;
	    }
	    case DIALOG_TOYEDIT:
	    {
	    	if(response)
	    	{
	    		new mstr[156];
	    		switch(listitem)
	    		{
	    			case 0: // toggle attach
	    			{
	    				if(!toyToggle[playerid][toySelect[playerid]])
	    				{
	    					SendInfoMessage(playerid, "Accessory ~g~attached", 3);

	    					SetPlayerAttachedObject(playerid,
	    					toySelect[playerid],
	    					pToys[playerid][toySelect[playerid]][toy_model],
	    					pToys[playerid][toySelect[playerid]][toy_bone],
	    					pToys[playerid][toySelect[playerid]][toy_x],
	    					pToys[playerid][toySelect[playerid]][toy_y],
	    					pToys[playerid][toySelect[playerid]][toy_z],
	    					pToys[playerid][toySelect[playerid]][toy_rx],
	    					pToys[playerid][toySelect[playerid]][toy_ry],
	    					pToys[playerid][toySelect[playerid]][toy_rz],
	    					pToys[playerid][toySelect[playerid]][toy_sx],
	    					pToys[playerid][toySelect[playerid]][toy_sy],
	    					pToys[playerid][toySelect[playerid]][toy_sz]);

	    					toyToggle[playerid][toySelect[playerid]] = true;
	    				}
	    				else
	    				{
	    					RemovePlayerAttachedObject(playerid, toySelect[playerid]);
	    					SendInfoMessage(playerid, "~w~Accessory ~r~deattached", 3);

	    					toyToggle[playerid][toySelect[playerid]] = false;
	    				}
	    				SavePlayerToys(playerid);
	    			}
	    			case 1: // change bone
	    			{
	    			    ShowPlayerDialog(playerid, DIALOG_TOYPOSISI, DIALOG_STYLE_LIST, "Bone Selection", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
	    			}
	    			case 2: // change placement
	    			{

	    				EditAttachedObject(playerid, toySelect[playerid]);

	    			}
	    			case 3:	//remove from list
	    			{
	    				if(IsPlayerAttachedObjectSlotUsed(playerid, toySelect[playerid]))
	    				{
	    					RemovePlayerAttachedObject(playerid, toySelect[playerid]);
	    				}
	    				pToys[playerid][toySelect[playerid]][toy_model] = 0;
	    				SendInfoMessage(playerid, "~w~Accessory ~y~removed!", 3);
	    				SavePlayerToys(playerid);
	    			}
	    			case 4: //Scale Fix
	    			{

	    				SendInfoMessage(playerid, "~w~Accessory scale ~y~Fixed", 3);

	    				pToys[playerid][toySelect[playerid]][toy_sx] = 1.0;
	    				pToys[playerid][toySelect[playerid]][toy_sy] = 1.0;
	    				pToys[playerid][toySelect[playerid]][toy_sz] = 1.0;

	    				if(!toyToggle[playerid][toySelect[playerid]])
	    				{
	    					RemovePlayerAttachedObject(playerid, toySelect[playerid]);
	    					SetPlayerAttachedObject(playerid,
	    					toySelect[playerid],
	    					pToys[playerid][toySelect[playerid]][toy_model],
	    					pToys[playerid][toySelect[playerid]][toy_bone],
	    					pToys[playerid][toySelect[playerid]][toy_x],
	    					pToys[playerid][toySelect[playerid]][toy_y],
	    					pToys[playerid][toySelect[playerid]][toy_z],
	    					pToys[playerid][toySelect[playerid]][toy_rx],
	    					pToys[playerid][toySelect[playerid]][toy_ry],
	    					pToys[playerid][toySelect[playerid]][toy_rz],
	    					pToys[playerid][toySelect[playerid]][toy_sx],
	    					pToys[playerid][toySelect[playerid]][toy_sy],
	    					pToys[playerid][toySelect[playerid]][toy_sz]);

	    					toyToggle[playerid][toySelect[playerid]] = true;
	    				}
	    			}
	    			case 5: //Pos X
	    			{
	    				format(mstr, sizeof(mstr), "Current X Position: %f\nInput new X Position:(Float)", pToys[playerid][toySelect[playerid]][toy_x]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSX, DIALOG_STYLE_INPUT, "Edit X Position", mstr, "Edit", "Cancel");
	    			}
	    			case 6: //Pos Y
	    			{
	    				format(mstr, sizeof(mstr), "Current Y Position: %f\nInput new Y Position:(Float)", pToys[playerid][toySelect[playerid]][toy_y]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSY, DIALOG_STYLE_INPUT, "Edit Y Position", mstr, "Edit", "Cancel");
	    			}
	    			case 7: //Pos Z
	    			{
	    				format(mstr, sizeof(mstr), "Current Z Position: %f\nInput new Z Position:(Float)", pToys[playerid][toySelect[playerid]][toy_z]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSZ, DIALOG_STYLE_INPUT, "Edit Z Position", mstr, "Edit", "Cancel");
	    			}
	    			case 8: //Pos RX
	    			{
	    				format(mstr, sizeof(mstr), "Current X Rotation: %f\nInput new X Rotation:(Float)", pToys[playerid][toySelect[playerid]][toy_rx]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSRX, DIALOG_STYLE_INPUT, "Edit X Rotation", mstr, "Edit", "Cancel");
	    			}
	    			case 9: //Pos RY
	    			{
	    				format(mstr, sizeof(mstr), "Current Y Rotation: %f\nInput new Y Rotation:(Float)", pToys[playerid][toySelect[playerid]][toy_ry]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSRY, DIALOG_STYLE_INPUT, "Edit Y Rotation", mstr, "Edit", "Cancel");
	    			}
	    			case 10: //Pos RZ
	    			{
	    				format(mstr, sizeof(mstr), "Current Z Rotation: %f\nInput new Z Rotation(Float)", pToys[playerid][toySelect[playerid]][toy_rz]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSRZ, DIALOG_STYLE_INPUT, "Edit Z Rotation", mstr, "Edit", "Cancel");
	    			}
	    			case 11: //Scale X
	    			{
	    				format(mstr, sizeof(mstr), "Current X Scale: %f\nInput new X Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sx]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSSX, DIALOG_STYLE_INPUT, "Edit X Scale", mstr, "Edit", "Cancel");
	    			}
	    			case 12: //Scale Y
	    			{
	    				format(mstr, sizeof(mstr), "Current Y Scale: %f\nInput new Y Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sy]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSSY, DIALOG_STYLE_INPUT, "Edit Y Scale", mstr, "Edit", "Cancel");
	    			}
	    			case 13: //Scale Z
	    			{
	    				format(mstr, sizeof(mstr), "Current Z Scale: %f\nInput new Z Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sz]);
	    				ShowPlayerDialog(playerid, DIALOG_TOYPOSSZ, DIALOG_STYLE_INPUT, "Edit Z Scale", mstr, "Edit", "Cancel");
	    			}
	    		}
	    	}
            return 1;
	    }

	    case DIALOG_TOY:
	    {
	    	if(response)
	    	{
	    		if(pToys[playerid][listitem][toy_model] == 0)
	    			return SendErrorMessage(playerid, "There is no accessory on selected index!");

    
	    		new string[512];
	    		toySelect[playerid] = listitem;
	    		format(string, sizeof(string), "Place %s\nChange Bone\nChange Placement\nRemove from list\nScale Fix\nPosition X: %f\nPosition Y: %f\nPosition Z: %f\nRotation X: %f\nRotation Y: %f\nRotation Z: %f\nScale X: %f\nScale Y: %f\nScale Z: %f",
	    		(!toyToggle[playerid][toySelect[playerid]]) ? ("On") : ("Off"), pToys[playerid][toySelect[playerid]][toy_x], pToys[playerid][toySelect[playerid]][toy_y], pToys[playerid][toySelect[playerid]][toy_z],
	    		pToys[playerid][toySelect[playerid]][toy_rx], pToys[playerid][toySelect[playerid]][toy_ry], pToys[playerid][toySelect[playerid]][toy_rz], pToys[playerid][toySelect[playerid]][toy_sx], pToys[playerid][toySelect[playerid]][toy_sy], pToys[playerid][toySelect[playerid]][toy_sz]);
	    		ShowPlayerDialog(playerid, DIALOG_TOYEDIT, DIALOG_STYLE_LIST, sprintf("Edit Accessory (#%d)", listitem), string, "Select", "Cancel");
	    	}
            return 1;
	    }
    }
	return 0;
}
