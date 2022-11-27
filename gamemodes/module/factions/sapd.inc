//#include <YSI_Coding\y_hooks>

/*
hook OnGameModeInit()
{
    CellPickup[0] = CreateDynamicPickup(1313, 2, 2262.1304, 1251.0757, 863.8434, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[1] = CreateDynamicPickup(1313, 2, 2265.8972, 1251.0757, 863.7908, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[2] = CreateDynamicPickup(1313, 2, 2269.5806, 1251.0757, 863.7393, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[3] = CreateDynamicPickup(1313, 2, 2273.1025, 1251.0757, 863.6912, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[4] = CreateDynamicPickup(1313, 2, 2273.2744, 1260.8147, 863.6888, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[5] = CreateDynamicPickup(1313, 2, 2269.7317, 1260.8147, 863.7372, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[6] = CreateDynamicPickup(1313, 2, 2265.9805, 1260.8147, 863.7896, LSPD_VW, LSPD_INTERIOR, -1);
    CellPickup[7] = CreateDynamicPickup(1313, 2, 2262.1453, 1260.8147, 863.8431, LSPD_VW, LSPD_INTERIOR, -1);
    return 1;
}*/

stock IsACruiser(vehicleid)
{
	switch (GetVehicleModel(vehicleid)) {
	    case 523, 427, 490, 528, 596..599, 601: return 1;
	}
	return 0;
}


stock GetCellSAPDPoint(playerid)
{
	if(GetPlayerInterior(playerid) == LSPD_INTERIOR && GetPlayerVirtualWorld(playerid) == LSPD_VW){
		if(IsPlayerInRangeOfPoint(playerid, 3.0, 2262.1304,1251.0757,863.8434)){
			return 1;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2265.8972,1251.0751,863.7908)){
			return 2;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2269.5806,1251.0753,863.7393)){
			return 3;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2273.1025,1251.0760,863.6912)){
			return 4;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2273.2744,1260.8147,863.6888)){
			return 5;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2269.7317,1260.8146,863.7372)){
			return 6;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2265.9805,1260.8149,863.7896)){
			return 7;
		}else if(IsPlayerInRangeOfPoint(playerid, 3.0, 2262.1453,1260.8148,863.8431)){
			return 8;
		}else{
			return 0;
		}
	}
	return 0;
}

SetPlayerArrest(playerid, type, cellid, time)
{
    switch(type){
        case 1:{// Type SAPD NORMAL 
            switch(cellid){
                case 1:{
                    SetPlayerPos(playerid, 2262.1453, 1248.5530, 863.8431);
                }
                case 2:{
                    SetPlayerPos(playerid, 2265.5984, 1248.9556, 863.7949);
                }  
                case 3:{  
                    SetPlayerPos(playerid, 2269.2888, 1249.1511, 863.7434);
                }  
                case 4:{  
                    SetPlayerPos(playerid, 2273.3872, 1249.0813, 863.6872);
                }  
                case 5:{  
                    SetPlayerPos(playerid, 2273.5281, 1262.9569, 863.6852);
                }  
                case 6:{  
                    SetPlayerPos(playerid, 2270.1294, 1262.6925, 863.7317);
                }  
                case 7:{  
                    SetPlayerPos(playerid, 2266.2761, 1262.7576, 863.7855);
                }  
                case 8:{  
                    SetPlayerPos(playerid, 2262.4827, 1262.6815, 863.8384);
                }
            }
			PlayerData[playerid][pJailType] = type;
			PlayerData[playerid][pJailTime] = time;
            CellPrisoners[cellid] += 1;
	        SetPlayerVirtualWorld(playerid, LSPD_VW);
	        SetPlayerInterior(playerid, LSPD_INTERIOR);
	        ShowPlayerDialog(playerid, -1, DIALOG_STYLE_LIST, "Close", "Close", "Close", "Close");
	        SetPlayerWantedLevel(playerid, 0);
	        PlayerPlaySound(playerid, 1186, 0, 0, 0);
            SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
        }
    }    
}

CMD:arrest(playerid, params[]){
	if(PlayerData[playerid][pFaction] == 1){
		new otherid,jailtime,denda;
		if (sscanf(params, "ui", otherid, jailtime, denda))
	    	return SendSyntaxMessage(playerid, "/arrest [playerid/nama] [waktu (menit)] [denda]");

		if(otherid == playerid)
			return SendErrorMessage(playerid, "Kamu tidak bisa menangkap dirimu.");

		if (!IsPlayerNearPlayer(playerid, otherid, 3.0))
			return SendErrorMessage(playerid, "Player terlalu jauh.");

		if(jailtime > 10080)
			return SendErrorMessage(playerid, "Waktu tidak boleh lebih dari 10080 menit ((1 Minggu Dunia Nyata [kasian anjir yang main]))");
		
		if(jailtime < 1)
			return SendErrorMessage(playerid, "Waktu tidak boleh kurang dari 1 menit");

		if(denda > 5000000)
			return SendErrorMessage(playerid, "Denda tidak boleh diatas $50,000.00");

		if(denda < 1)
			return SendErrorMessage(playerid, "Denda tidak boleh dibawah $0.01");

		if(PlayerData[otherid][pWanted] == 0)
			return SendErrorMessage(playerid, "Player tidak memiliki status kriminal.");

		if(GetCellSAPDPoint(otherid) > 0){
			PlayerData[otherid][pCuffed] = 0;
			SendClientMessage(playerid, 0xFFFFFFFF, "System: Kamu telah masuk penjara.");
			SetPlayerArrest(otherid, 1, GetCellSAPDPoint(otherid), jailtime);
			PlayerData[otherid][pWanted] = 0;
			GivePlayerMoney(otherid, -denda);
		}else return SendErrorMessage(playerid, "Player harus berada didepan sel.");
	}
	return 1;
}

CMD:mdc(playerid, params[]){

    if (PlayerData[playerid][pFaction] != 1 && IsPlayerInRangeOfPoint(playerid, 5.0, MDC_COORD))
		return SendErrorMessage(playerid, "Kamu bukan seorang polisi.");

	if (IsACruiser(GetPlayerVehicleID(playerid)) || IsPlayerInRangeOfPoint(playerid, 5.0, MDC_COORD)){  
        Dialog_Show(playerid, MainMDC, DIALOG_STYLE_LIST, "Mobile Data Computer", "Daftar Buronan\nMenetapkan Buronan\nDaftar Kriminal Penduduk", "Pilih", "Batal");
    }
    else return SendErrorMessage(playerid, "Kamu harus berada di kantor / mobil polisi.");
	return 1;
}

CMD:detain(playerid, params[])
{
	new
		userid,
		vehicleid = GetNearestVehicle(playerid, 3.5);

	if (PlayerData[playerid][pFaction] != 1 )
		return SendErrorMessage(playerid, "You must be a police officer.");

	if (sscanf(params, "u", userid))
	    return SendSyntaxMessage(playerid, "/detain [playerid/name]");

	if (userid == INVALID_PLAYER_ID)
	    return SendErrorMessage(playerid, "That player is disconnected.");

    if (userid == playerid)
	    return SendErrorMessage(playerid, "You cannot detained yourself.");

    if (!IsPlayerNearPlayer(playerid, userid, 5.0))
	    return SendErrorMessage(playerid, "You must be near this player.");

    if (GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED)
        return SendErrorMessage(playerid, "The player is not cuffed at the moment.");

	if (vehicleid == INVALID_VEHICLE_ID)
	    return SendErrorMessage(playerid, "You are not near any vehicle.");

	if (GetVehicleMaxSeats(vehicleid) < 2)
  	    return SendErrorMessage(playerid, "You can't detain that player in this vehicle.");

	if (IsPlayerInVehicle(userid, vehicleid))
	{
		TogglePlayerControllable(userid, 1);

		RemovePlayerFromVehicle(userid);
		SendNearbyMessage(playerid, 30.0, 0xD0AEEBFF, "** %s membuka pintu, mengeluarkan %s dari kendaraan.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	else
	{
		new seatid = GetAvailableSeat(vehicleid, 2);

		if (seatid == -1)
		    return SendErrorMessage(playerid, "Tidak ada tempat duduk tersisa.");

		/*new
		    string[64];

		format(string, sizeof(string), "You've been ~r~detained~w~ by %s.", ReturnName(playerid, 0));*/
		TogglePlayerControllable(userid, 0);

		PutPlayerInVehicle(userid, vehicleid, seatid);

		SendNearbyMessage(playerid, 30.0, 0xD0AEEBFF, "** %s membuka pintu, memasukkan %s ke dalam kendaraan.", ReturnName(playerid, 0), ReturnName(userid, 0));
	}
	return 1;
}

CMD:cuff(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 1)
	{
		new otherid;
		if(sscanf(params, "u", otherid))
			return SendSyntaxMessage(playerid, "/cuff [playerid/PartOfName]");

		if(PlayerData[playerid][pInjured])
			return SendErrorMessage(playerid, "Player sedang sekarat.");

		if(otherid == playerid)
			return SendErrorMessage(playerid, "Kamu tidak bisa memborgol dirimu sendiri");
		
		if(ProxDetectorS(4.5, playerid, otherid)){
			PlayerData[otherid][pCuffed] = 1;
			SetPlayerSpecialAction(otherid, SPECIAL_ACTION_CUFFED);
			SetPlayerAttachedObject(otherid, ACTION_SLOT_ATT, 19418, 6, -0.011000, 0.028000, -0.022000, -15.600012, -33.699977, -81.700035, 0.891999, 1.000000, 1.168000);
		}else return SendErrorMessage(playerid, "Kamu terlalu jauh dari dia.");
	}
    return 1;
}

CMD:createvehlic(playerid, params[]) // KANG INI BUAT FUNCTION SIM
{
	if(PlayerData[playerid][pFaction] == 1){
		new otherid;
		if(sscanf(params, "d", otherid))
		{
			SendSyntaxMessage(playerid, "/createvehlic [playerid]");
			return 1;
		}
		if(IsPlayerNearPlayer(playerid, otherid, 4.0)){
			SendClientMessage(playerid, 0xFFFFFFFF, "Kamu telah membuatkan sim");
			SendClientMessage(otherid, 0xFFFFFFFF, "Kamu telah dibuatkan sim");
		}
	}
	return 1;
}


CMD:uncuff(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 1)
	{
		new otherid;
		if(sscanf(params, "u", otherid))
			return SendSyntaxMessage(playerid, "/cuff [playerid/PartOfName]");

		if(otherid == playerid)
			return SendErrorMessage(playerid, "Kamu tidak bisa membuka borgol dirimu sendiri.");
			
		if(PlayerData[otherid][pCuffed] != 1)
			return SendErrorMessage(playerid, "Player tidak terborgol.");

		if(ProxDetectorS(4.5, playerid, otherid)){
			PlayerData[otherid][pCuffed] = 0 ;
			SetPlayerSpecialAction(otherid, SPECIAL_ACTION_NONE);
			RemovePlayerAttachedObject(otherid, ACTION_SLOT_ATT);
		}else return SendErrorMessage(playerid, "Kamu terlalu jauh dari dia.");
	}
    return 1;
}


Dialog:Warrants(playerid, response, listitem, inputtext[])
{
	if (IsACruiser(GetPlayerVehicleID(playerid))||IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD))
	{
	    if (response)
	    {
	        static
	            name[64],
	    		targetid = INVALID_PLAYER_ID;

	    	strmid(name, inputtext, 0, strfind(inputtext, "(") - 1);

	    	if ((targetid = GetPlayerID(name, 0)) == INVALID_PLAYER_ID)
	    	    return SendErrorMessage(playerid, "The player is no longer connected.");

	    	if (PlayerData[targetid][pWanted] < 1)
	    	    return SendErrorMessage(playerid, "Player tidak memiliki tingkat kriminal aktif .");

	    	SetPVarInt(playerid, "MDC", targetid);

	    	format(name, sizeof(name), "MDC: %s", name);
	    	Dialog_Show(playerid, WarrantList, DIALOG_STYLE_LIST, name, "Melacak DPO\nMembersihkan Status Kriminal", "Select", "Back");
	    }
	    else cmd_mdc(playerid, "\1");
    }
	return 1;
}

Dialog:WarrantList(playerid, response, listitem, inputtext[])
{
	if (IsACruiser(GetPlayerVehicleID(playerid)) || GetPVarInt(playerid, "MDC") != INVALID_PLAYER_ID || IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD)){
	    if (response)
	    {
	        switch (listitem)
	        {
	            case 0:
	            {
                    new string[512];
                    format(string,sizeof(string), "Satelite MDC sedang melacak tersangka %s...", ReturnName(GetPVarInt(playerid, "MDC"), 0));
	                SendServerMessage(playerid, string);
	                PlayerData[playerid][pTrackTime] = 5;
	    		}
	    		case 1:
	    		{
                    if(IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD))
                    {			    
	    		        SendServerMessage(playerid, "Kamu membersihkan status tersangka aktif %s.", ReturnName(GetPVarInt(playerid, "MDC"), 0));
	    		        SendFactionMessage(1, 0x004BFFFF, "RADIO System: {FFFFFF}%s %s telah membersihkan status kriminal %s [Tingkat %d] sebagai DPO.", GetFactionRank(playerid), ReturnName(playerid, 0), ReturnName(GetPVarInt(playerid, "MDC"), 0), PlayerData[GetPVarInt(playerid, "MDC")][pWanted], inputtext);
                        //SendFactionMessage(PlayerData[playerid][pFaction], COLOR_RADIO, "RADIO: %s has cleared %s's active warrants.", ReturnName(playerid, 0), ReturnName(PlayerData[playerid][pMDCPlayer], 0));
                        PlayerData[GetPVarInt(playerid, "MDC")][pWanted] = 0;
                        DeletePVar(playerid, "MDC");
                    }else{
                        SendErrorMessage(playerid, "Kamu hanya bisa melakukan ini di kantor.");
                        cmd_mdc(playerid, "\1");
                    }
	    		}
	        }
	    }
	    else
	    {
            DeletePVar(playerid, "MDC");
	        dialog_MainMDC(playerid, 1, 0, "\1");
	    }
    }else return 0;
	return 1;
}

CMD:sus(playerid,params[])
    {
        PlayCrimeReportForPlayer(playerid, 0, 16);
        SendClientMessage(playerid, 0xFFFFFFFF, "ID 0 committed a crime (10-16).");
        return 1;
    }

Dialog:ChargeName(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFaction] != 1)
	    return 0;

	if (response)
	{
	    new targetid;

	    if (sscanf(inputtext, "u", targetid))
	        return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Membuat DPO", "Error: Tidak valid.\n\nMasukkan Nama atau ID Player:", "Submit", "Back");

		if (targetid == INVALID_PLAYER_ID)
		    return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Membuat DPO", "Error: Tidak ditemukan.\n\nMasukkan Nama atau ID Player:", "Submit", "Back");

        if (PlayerData[targetid][pWanted] > 14)
		    return Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Membuat DPO", "Error: Dia telah memiliki 15 tingkat kriminal.\n\nMasukkan Nama atau ID Player:", "Submit", "Back");

        SetPVarInt(playerid, "MDC", targetid);
		Dialog_Show(playerid, PlaceCharge1, DIALOG_STYLE_INPUT, "Membuat DPO", "Silahkan masukkan deskripsi kriminal yang telah dilakukan oleh %s:", "Submit", "Back", ReturnName(GetPVarInt(playerid, "MDC"), 0));
	}
	else cmd_mdc(playerid, "\1");
	return 1;
}

Dialog:PlaceCharge1(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFaction] != 1 && !IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD) && GetPVarInt(playerid, "MDC") == INVALID_PLAYER_ID )
	    return 0;

	if (response)
	{
	    if (isnull(inputtext))
			return Dialog_Show(playerid, PlaceCharge, DIALOG_STYLE_INPUT, "Membuat DPO", "Silahkan masukkan deskripsi kriminal yang telah dilakukan oleh %s:", "Submit", "Back", ReturnName(GetPVarInt(playerid, "MDC"), 0));    
        if(PlayerData[GetPVarInt(playerid, "MDC")][pWanted] > 10){
            PlayerData[GetPVarInt(playerid, "MDC")][pWanted]++;
            AddWarrant(GetPVarInt(playerid, "MDC"), playerid, inputtext);
            SendFactionMessage(1, 0x004BFFFF, "RADIO System: {FFFFFF}%s %s telah menetapkan %s [Kejahatan Tingkat %d] sebagai buronan karena \"%s\".", GetFactionRank(playerid), ReturnName(playerid, 0), ReturnName(GetPVarInt(playerid, "MDC"), 0), PlayerData[GetPVarInt(playerid, "MDC")][pWanted], inputtext);
            new rand = random(19)+3;
		    for (new i = 0; i < MAX_PLAYERS; i++) {
		    	if (IsPlayerConnectedEx(i) && PlayerData[i][pFaction] == 1 && PlayerData[i][pDuty] == 1){
		    		PlayCrimeReportForPlayer(i, GetPVarInt(playerid, "MDC"), rand);
		    	}
		    }
            cmd_mdc(playerid, "\1");
        }
        else{
            Dialog_Show(playerid, PlaceCharge2, DIALOG_STYLE_LIST, "Tingkat Kejahatan", "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n", "Submit", "Back", ReturnName(GetPVarInt(playerid, "MDC"), 0));
	        SetPVarString(playerid, "Kejahatan", inputtext);
	        //SendFactionMessage(1, 0x8D8DFFFF, "RADIO: %s telat menetapkan %s sebagai buronan karena \"%s\".", ReturnName(playerid, 0), ReturnName(GetPVarInt(playerid, "MDC"), 0), inputtext);
        }
	    //cmd_mdc(playerid, "\1");
	}
	else
	{
        DeletePVar(playerid, "MDC");
	    cmd_mdc(playerid, "\1");
	}
	return 1;
}

Dialog:PlaceCharge2(playerid, response, listitem, inputtext[])
{
	if (PlayerData[playerid][pFaction] != 1 && !IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD) && GetPVarInt(playerid, "MDC") == INVALID_PLAYER_ID )
	    return 0;

	if (response)
	{
        new kejahatan[512];
	    if (isnull(inputtext))
			return Dialog_Show(playerid, PlaceCharge2, DIALOG_STYLE_LIST, "Tingkat Kejahatan", "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n", "Submit", "Back", ReturnName(GetPVarInt(playerid, "MDC"), 0));
        GetPVarString(playerid, "Kejahatan", kejahatan, sizeof(kejahatan));
	    PlayerData[GetPVarInt(playerid, "MDC")][pWanted] += listitem+1;
        if(PlayerData[GetPVarInt(playerid, "MDC")][pWanted] > 15){
            PlayerData[GetPVarInt(playerid, "MDC")][pWanted] = 15;
        }
        new rand = random(19)+3;
		for (new i = 0; i < MAX_PLAYERS; i++) {
			if (IsPlayerConnectedEx(i) && PlayerData[i][pFaction] == 1 && PlayerData[i][pDuty] == 1){
				PlayCrimeReportForPlayer(i, GetPVarInt(playerid, "MDC"), rand);
			}
		}
	    AddWarrant(GetPVarInt(playerid, "MDC"), playerid, kejahatan);
	    SendFactionMessage(1, 0x004BFFFF, "RADIO System: {FFFFFF}%s %s telah menetapkan %s [Kejahatan Tingkat %d] sebagai buronan karena \"%s\".", GetFactionRank(playerid) ,ReturnName(playerid, 0), ReturnName(GetPVarInt(playerid, "MDC"), 0), PlayerData[GetPVarInt(playerid, "MDC")][pWanted], kejahatan);

	    cmd_mdc(playerid, "\1");
	}
	else
	{
        DeletePVar(playerid, "MDC");
	    cmd_mdc(playerid, "\1");
	}
	return 1;
}

Dialog:MainMDC(playerid, response, listitem, inputtext[])
{
	if (!IsACruiser(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD))
	    return 0;
    DeletePVar(playerid, "MDC");
    DeletePVar(playerid, "Kejahatan");
	if (response)
	{
	    switch (listitem)
	    {
	        case 0:
	        {
	            static
	                string[512];

				string[0] = 0;

				foreach (new i : Player) if (PlayerData[i][pWanted] > 0) {
				    format(string, sizeof(string), "%s%s (Tingkat Kriminal %d)\n", string, ReturnName(i, 0), PlayerData[i][pWanted]);
				}
				if (!strlen(string)){
                    cmd_mdc(playerid, "\1");
                    return SendServerMessage(playerid, "Belum ada buronan.");
                }

				Dialog_Show(playerid, Warrants, DIALOG_STYLE_LIST, "Daftar Buronan", string, "Select", "Back");
    		}
    		case 1:
    		{
                if(IsPlayerInRangeOfPoint(playerid, 4.0, MDC_COORD)){
    		        Dialog_Show(playerid, ChargeName, DIALOG_STYLE_INPUT, "Menetapkan Tersangka", "Masukkan Nama atau ID Player:", "Submit", "Back");
                }else{
                    SendErrorMessage(playerid, "Kamu tidak bisa menggunakannya diluar kantor.");
                    
                }
            }
			case 2:
    		{
    		    Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "Daftar Kriminal Penduduk", "Masukkan Nama atau ID Player:", "Submit", "Back");
			}
	    }
	}
	return 1;
}

Dialog:ViewCharges(playerid, response, listitem, inputtext[])
{
	if (!IsACruiser(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD))
	    return 0;

	if (response)
	{
		if (isnull(inputtext) || strlen(inputtext) > 24)
		    return Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "Daftar Kriminal Penduduk", "Masukkan Nama atau ID Player:", "Submit", "Back");

		if (IsNumeric(inputtext) && IsPlayerConnectedEx(strval(inputtext))) {
	        ViewCharges(playerid, ReturnName(strval(inputtext)), 1 );
			format(NAMAORANGGILA[playerid], MAX_PLAYER_NAME, ReturnName(strval(inputtext)));
		}
	    else if (!IsNumeric(inputtext)) {
	        ViewCharges(playerid, inputtext, 1);
			format(NAMAORANGGILA[playerid], MAX_PLAYER_NAME, inputtext);
		}
		else {
		    Dialog_Show(playerid, ViewCharges, DIALOG_STYLE_INPUT, "Daftar Kriminal Penduduk", "Error: Tidak Ditemukan.\n\nMasukkan Nama atau ID Player:", "Submit", "Back");
		}
	}
	else cmd_mdc(playerid, "\1");
	return 1;
}

Dialog:ChargeList(playerid, response, listitem, inputtext[])
{
	if (!IsACruiser(GetPlayerVehicleID(playerid)) && !IsPlayerInRangeOfPoint(playerid, 3.5, MDC_COORD))
	    return 0;

	if (response)
	{
		if(Pagessss[playerid] == 0){
			cmd_mdc(playerid, "\1");
		}else{
			Pagessss[playerid] += 1;
			ViewCharges(playerid, NAMAORANGGILA[playerid], Pagessss[playerid]);
		}
	}else{
		Pagessss[playerid] -= 1;
		ViewCharges(playerid, NAMAORANGGILA[playerid], Pagessss[playerid]);
	}

	return 1;
}

Function:OnViewCharges(extraid, name[], pages)
{
	static
	    rows;

	//cache_get_value(rows, fields, sqlcon);
    //cache_get_value_index(rows, fields, sqlcon);
    cache_get_row_count(rows);
	if (!rows)
	    return SendErrorMessage(extraid, "Tidak ada hasil kriminal untuk \"%s\".", name);

	static
	    string[1024],
		desc[128],
		date[36];

	string[0] = 0;

	if(rows < 11){
		for (new i = 0; i < 10; i ++) {
	    	cache_get_value_name(i, "Description", desc);
	    	cache_get_value_name(i, "Date", date);
	    	format(string, sizeof(string), "%s%d. %s (%s)\n", string, desc, date);
		}
		format(desc, sizeof(desc), "Nama Penduduk: %s", name);
		Dialog_Show(extraid, ChargeList, DIALOG_STYLE_LIST, desc, string, "Close", "");
		Pagessss[extraid] = 0;
	}else if(rows > 10){
		for (new i = pages*10; i < ((pages+1)*10); i ++) {
	    	cache_get_value_name(i, "Description", desc);
	    	cache_get_value_name(i, "Date", date);
	    	format(string, sizeof(string), "%s%d. %s (%s)\n", string, desc, date);
		}
		format(desc, sizeof(desc), "Nama Penduduk: %s", name);
		Dialog_Show(extraid, ChargeList, DIALOG_STYLE_LIST, desc, string, "Next", "Back");
		Pagessss[extraid] = pages;
	}
	return 1;
}

stock ViewCharges(playerid, name[], pages=1)
{
	new
	    string[128];

	format(string, sizeof(string), "SELECT * FROM `criminallog` WHERE `Suspect` = '%s' ORDER BY `ID` DESC", name);
	mysql_tquery(sqlcon, string, "OnViewCharges", "dsi", playerid, name, pages);
	return 1;
}

stock AddWarrant(targetid, playerid, const description[])
{
	new
	    string[255];

	format(string, sizeof(string), "INSERT INTO `criminallog` (`Suspect`, `Username`, `Date`, `Description`) VALUES('%s', '%s', '%s', '%s')", ReturnName(targetid), ReturnName(playerid), ReturnDate(), description);
	mysql_tquery(sqlcon, string);
}
