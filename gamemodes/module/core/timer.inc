ptask secondsTimer[999](playerid) 
{
	if(IsPlayerConnected2(playerid)){
    	if(PlayerData[playerid][pThirst] >= 101)
		{
			PlayerData[playerid][pThirst] = 100;
		}
		if(PlayerData[playerid][pHunger] >= 101)
		{
			PlayerData[playerid][pHunger] = 100;
		}
		if(PlayerData[playerid][pThirst] <= 0)
		{
			PlayerData[playerid][pThirst] = 0;
		}
		if(PlayerData[playerid][pHunger] <= 0)
		{
			PlayerData[playerid][pHunger] = 0;
		}
    	if(PlayerData[playerid][pHunger] < 14 || PlayerData[playerid][pThirst] < 15)
		{
			SetPlayerDrunkLevel(playerid, 4000);
		}
		else{
			SetPlayerDrunkLevel(playerid, 0);
		}

		if(PlayerData[playerid][pJailType] > 0 && PlayerData[playerid][pAJailTime] >= 1){// Selesaikan dulu jail ooc nya
			PlayerData[playerid][pAJailTime] --;
		}else if(PlayerData[playerid][pJailType] > 0 && PlayerData[playerid][pJailTime] >= 1){
			PlayerData[playerid][pJailTime] --;
		}else if(PlayerData[playerid][pJailType] > 0 && PlayerData[playerid][pAJailTime] <= 0){
			if(PlayerData[playerid][pJailTime] > 0 ){
				if(GetLSPDEmptyCell() > 0){
					SetPlayerArrest(playerid, 1, GetLSPDEmptyCell(), PlayerData[playerid][pJailTime]);
				}
			}else{
				SetPlayerPos(playerid, 0,0,0); // Jangan Lupa Di ganti nanti habis di ajail tele ke blueberry ga lucu
			}
		}else if(PlayerData[playerid][pJailType] > 0 && PlayerData[playerid][pJailTime] <= 0){
			PlayerData[playerid][pJailType] = 0;
			PlayerData[playerid][pJailTime] = 0;
			SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
			SetPlayerInterior(playerid, 0);
			SetPlayerPos(playerid, 1542.3409, -1675.6566, 13.5543);
			SetPlayerVirtualWorld(playerid, 0);
		}

		if (PlayerData[playerid][pTrackTime] > 0 && IsPlayerConnectedEx(GetPVarInt(playerid, "MDC")))
		{
		    PlayerData[playerid][pTrackTime]--;

		    if (PlayerData[playerid][pTrackTime] == 1)
		    {
		        /*f ((id = House_Inside(PlayerData[i][pMDCPlayer])) != -1)
				{
				    PlayerData[i][pCP] = 1;

				    SetPlayerCheckpoint(i, HouseData[id][housePos][0], HouseData[id][housePos][1], HouseData[id][housePos][2], 3.0);
		            SendServerMessage(i, "%s's last reported location was at \"%s\" (marked on radar).", ReturnName(PlayerData[i][pMDCPlayer], 0), HouseData[id][houseAddress]);
		        }
		        else if ((id = Business_Inside(PlayerData[i][pMDCPlayer])) != -1)
		        {
		            PlayerData[i][pCP] = 1;

		            SetPlayerCheckpoint(i, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2], 3.0);
		            SendServerMessage(i, "%s's last reported location was at \"%s\" (marked on radar).", ReturnName(PlayerData[i][pMDCPlayer], 0), BusinessData[id][bizName]);
		        }*/
		        if (GetPlayerInterior(GetPVarInt(playerid, "MDC")) == 0)
		        {
		            static
		                Float:fX,
		                Float:fY,
		                Float:fZ;

					new string[512];
		            GetPlayerPos(GetPVarInt(playerid, "MDC"), fX, fY, fZ);
		            PlayerData[playerid][pCP] = 1;
					PlayCrimeReportForPlayer(playerid, GetPVarInt(playerid, "MDC"), 12);
                    SetPlayerCheckpoint(playerid, fX, fY, fZ, 3.0);
					format(string, sizeof(string), "%s's last reported location was at \"%s\" ", ReturnName(GetPVarInt(playerid, "MDC"), 0), GetLocation(fX, fY, fZ));
		            SendServerMessage(playerid, string);
		        }
		        else
		        {
		            SendServerMessage(playerid, "Unable to locate %s; the target is out of range (inside an interior).", ReturnName(GetPVarInt(playerid, "MDC"), 0));
				}
				PlayerData[playerid][pTrackTime] = 0;
			}
			if(GetPlayerSpecialAction(playerid) != SPECIAL_ACTION_CUFFED && PlayerData[playerid][pCuffed] == 1){
				if(!PlayerData[playerid][pInjured]){
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_CUFFED);
				}else{
					PlayerData[playerid][pCuffed] = 0;
					SetPlayerSpecialAction(playerid, SPECIAL_ACTION_NONE);
					RemovePlayerAttachedObject(playerid, ACTION_SLOT_ATT);
				}	
			}
		}
	}

}