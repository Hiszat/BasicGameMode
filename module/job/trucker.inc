#include <YSI\y_hooks>

hook OnPlayerDisconnect(playerid)
{
	switch(IsHauling[playerid]){
		case 1,2:{
			DialogHauling[0] = false;
		}
		case 3,4:{
			DialogHauling[1] = false;
		}
		case 5,6:{
			DialogHauling[2] = false;
		}
		case 7,8:{
			DialogHauling[3] = false;
		}
		case 9,10:{
			DialogHauling[4] = false;
		}
		case 11,12:{
			DialogHauling[5] = false;
		}
		case 13,14:{
			DialogHauling[6] = false;
		}
		case 15,16:{
			DialogHauling[7] = false;
		}
		case 17,18:{
			DialogHauling[8] = false;
		}
		case 19,20:{
			DialogHauling[9] = false;
		}
	}
	IsHauling[playerid] = 0;
	DestroyVehicle(TrailerHauling[playerid]);
	return 1;
}

CMD:hauling(playerid,params[])
{
    new String2[3000], String[3000];
	if(PlayerData[playerid][pJob] == 2 || PlayerData[playerid][pJob2] == 2)
	{
	    if(PlayerData[playerid][pTruckerTimer] > 0 )
		{
	    	format(String, sizeof(String),"Kamu harus menunggu %d menit untuk memulai Trucking Mission kembali", PlayerData[playerid][pTruckerTimer]/60);
            SendErrorMessage(playerid,  String);
	    	return 1;
		}
		if(IsHauling[playerid] >= 1) { SendServerMessage(playerid,"Kamu sedang dalam pengiriman."); return 1; }
	    if(GetVehicleModel(GetPlayerVehicleID(playerid)) == 403 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 514 || GetVehicleModel(GetPlayerVehicleID(playerid)) == 515)
		{
			strcat(String2, "Order\tPrice\n");
			format(String, sizeof(String), "Ocean Dock Imports\t%s\n", (DialogHauling[0] == true) ? ("{FF0000}Taken") : ("{33AA33}$350.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Ocean Dock Imports\t%s\n", (DialogHauling[1] == true) ? ("{FF0000}Taken") : ("{33AA33}$300.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Angel Pine Exports\t%s\n", (DialogHauling[2] == true) ? ("{FF0000}Taken") : ("{33AA33}$250.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Angel Pine Exports\t%s\n", (DialogHauling[3] == true) ? ("{FF0000}Taken") : ("{33AA33}$270.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Chilliad Deport\t%s\n", (DialogHauling[4] == true) ? ("{FF0000}Taken") : ("{33AA33}$399.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Chilliad Deport\t%s\n", (DialogHauling[5] == true) ? ("{FF0000}Taken") : ("{33AA33}$200.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Easter Import\t%s\n", (DialogHauling[6] == true) ? ("{FF0000}Taken") : ("{33AA33}$310.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Blueberry Export\t%s\n", (DialogHauling[7] == true) ? ("{FF0000}Taken") : ("{33AA33}$333.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Las Venturas Deport\t%s\n", (DialogHauling[8] == true) ? ("{FF0000}Taken") : ("{33AA33}$290.00"));
			strcat(String2, String);
			format(String, sizeof(String), "Las Venturas Fuel & Gas\t%s", (DialogHauling[9] == true) ? ("{FF0000}Taken") : ("{33AA33}$255.00"));
			strcat(String2, String);
		   	//format(String2, sizeof(String2), "%sMissions 1\t$350.00\nMissions 2\t$300.00\nMissions 3\t$250.00\nMissions 4\t$270.00\nMissions 5\t$399.00\nMissions 6\t$200.00\nMissions 7\t$310.00\nMissions 8\t$333.00\nMissions 9\t$290.00\nMissions 10\t$225.00", S3MP4K);
			Dialog_Show(playerid, Hauling, DIALOG_STYLE_TABLIST_HEADERS, "Hauling Missions", String2, "Select", "Cancel");
			return 1;
		}
		SendErrorMessage(playerid, "Kamu tidak berada di truck pengangkut.");
		return 1;
	}
	SendErrorMessage(playerid, "Kamu bukan seorang trucker.");
	return 1;
}

Dialog:Hauling(playerid, response, listitem, inputtext[]){
	if(response){
		switch(listitem){
			case 0://Ocean Dock 1
			{
			    if(DialogHauling[0] == false) 
			    {
				    DialogHauling[0] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, 2791.4016, -2494.5452, 14.2522, 2791.4016, -2494.5452, 14.2522, 10.0);
					TrailerHauling[playerid] = CreateVehicle(435, 2791.4016, -2494.5452, 14.2522, 89.5366, 1, 1, -1);
					IsHauling[playerid] = 1;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 1://Ocean Dock 2
			{
			    if(DialogHauling[1] == false)
                { 
				    DialogHauling[1] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, 2784.3132, -2456.6299, 14.2415, 2784.3132, -2456.6299, 14.2415, 10.0);
					TrailerHauling[playerid] = CreateVehicle(591, 2784.3132, -2456.6299, 14.2415, 89.4938, 1, 1, -1);
					IsHauling[playerid] = 3;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 2://Angel Pine 1
			{
			    if(DialogHauling[2] == false)
			    {
				    DialogHauling[2] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1,-1963.0142, -2436.3079, 31.2311, -1963.0142, -2436.3079, 31.2311, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, -1963.0142, -2436.3079, 31.2311, 226.1548, 1, 1, -1);
					IsHauling[playerid] = 5;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 3://Angel Pine 2
			{
			    if(DialogHauling[3] == false) 
			    {
				    DialogHauling[3] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, -1966.5603, -2439.9380, 31.2306, -1966.5603, -2439.9380, 31.2306, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, -1966.5603, -2439.9380, 31.2306, 225.5799, 1, 1, -1);
					IsHauling[playerid] = 7;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 4:
			{
			    if(DialogHauling[4] == false) 
			    {
				    DialogHauling[4] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, -1863.1541, -1720.5603, 22.3558, -1863.1541, -1720.5603, 22.3558, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, -1863.1541, -1720.5603, 22.3558, 122.1463, 1, 1, -1);
					IsHauling[playerid] = 9;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 5:
			{
			    if(DialogHauling[5] == false) 
			    {
				    DialogHauling[5] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, -1855.7255, -1726.0389, 22.3566, -1855.7255, -1726.0389, 22.3566, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, -1855.7255, -1726.0389, 22.3566, 124.4187, 1, 1, -1);
					IsHauling[playerid] = 11;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 6:
			{
			    if(DialogHauling[6] == false) 
			    {
				    DialogHauling[6] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, -1053.6145, -658.6473, 32.6319, -1053.6145, -658.6473, 32.6319, 10.0);
					TrailerHauling[playerid] = CreateVehicle(584, -1053.6145, -658.6473, 32.6319, 260.6392, 1, 1, -1);
					IsHauling[playerid] = 13;
				}
				else
				    SendClientMessage(playerid,-1,"ERROR: Trucking Missions already taken by Someone");
			}
			case 7://Blueberry Atas
			{
			    if(DialogHauling[7] == false) 
			    {
				    DialogHauling[7] = true; 
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, -459.3511, -48.3457, 60.5507, -459.3511, -48.3457, 60.5507, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, -459.3511, -48.3457, 60.5507, 182.7280, 1, 1, -1);
					IsHauling[playerid] = 15;
				}
				else
				    SendClientMessage(playerid,-1, "ERROR: Trucking Missions already taken by Someone");
			}
			case 8://LV Tanah
			{
			    if(DialogHauling[8] == false) 
			    {
				    DialogHauling[8] = true; 
				  
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, 847.0450, 921.0422, 13.9579, 847.0450, 921.0422, 13.9579, 10.0);
					TrailerHauling[playerid] = CreateVehicle(450, 847.0450, 921.0422, 13.9579, 201.2555, 1, 1, -1);
					IsHauling[playerid] = 17;
				}
				else
				    SendClientMessage(playerid,-1, "ERROR: Trucking Missions already taken by Someone");
			}
			case 9://LV Pabrik
			{
			    if(DialogHauling[9] == false) 
			    {
				    DialogHauling[9] = true;
				    
					SendServerMessage(playerid,"Go to marked checkpoint on your map");
					SetPlayerRaceCheckpoint(playerid, 1, 249.6713, 1395.7150, 11.1923, 249.6713, 1395.7150, 11.1923, 10.0);
					TrailerHauling[playerid] = CreateVehicle(584, 249.6713, 1395.7150, 11.1923, 269.0699, 1, 1, -1);
					IsHauling[playerid] = 19;
				}
				else
				    SendClientMessage(playerid,-1, "ERROR: Trucking Missions already taken by Someone");
			}
        }        
    }
    return 1;
}            
             
