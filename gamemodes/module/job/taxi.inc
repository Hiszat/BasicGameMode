#include <YSI\y_hooks>

new TaxiDriver[MAX_VEHICLES] = INVALID_PLAYER_ID;
enum TaxiStat{
    InTaxi,
    FareTimer,
    FareTotal,
    Float:FareNewX,
    Float:FareNewY,
    Float:FareNewZ,
    Float:FareOldX,
    Float:FareOldY,
    Float:FareOldZ,
}
new TaxiInfo[MAX_PLAYERS][TaxiStat];
//Taxi
CMD:taxiduty(playerid)
{
	if(PlayerData[playerid][pJob] == 1 || PlayerData[playerid][pJob2] == 1)
	{
		new modelid = GetVehicleModel(GetPlayerVehicleID(playerid));
		new vehicleid = GetPlayerVehicleID(playerid);
		if(modelid != 438 && modelid != 420)
			return SendErrorMessage(playerid, "Kamu harus mengendarai taxi.");

        if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
            return SendErrorMessage(playerid, "Kamu harus mengendarai taxi.");

		if(PlayerData[playerid][pJobDuty] == 0)
		{
			PlayerData[playerid][pJobDuty] = 1;
			SetPlayerColor(playerid, 0xFFFF00FF);
            TaxiDriver[vehicleid] = playerid;
		}
		else
		{
            TaxiDriver[vehicleid] = INVALID_PLAYER_ID;
			PlayerData[playerid][pJobDuty] = 0;
			SetPlayerColor(playerid, 0xFFFFFFFF);
		}
	}
	else return SendErrorMessage(playerid,   "Anda bukan pekerja taxi driver.");
	return 1;
}

hook OnPlayerConnect(playerid)
{
    TaxiInfo[playerid][InTaxi] = INVALID_VEHICLE_ID;
    TaxiInfo[playerid][FareTotal] = 0;
    TaxiInfo[playerid][FareNewX] = 0;
    TaxiInfo[playerid][FareNewY] = 0;
    TaxiInfo[playerid][FareNewZ] = 0;
    TaxiInfo[playerid][FareOldX] = 0;
    TaxiInfo[playerid][FareOldY] = 0;
    TaxiInfo[playerid][FareOldZ] = 0;
    
    return 1;
}

hook OnPlayerStateChange(playerid, newstate, oldstate)
{
    if(newstate == PLAYER_STATE_ONFOOT)
    {
        new vehicleid = TaxiInfo[playerid][InTaxi];
        if(TaxiInfo[playerid][InTaxi] != INVALID_VEHICLE_ID  && TaxiInfo[playerid][InTaxi] == GetPlayerVehicleID(TaxiDriver[vehicleid])){
            KillTimer(TaxiInfo[TaxiDriver[vehicleid]][FareTimer]);
            GivePlayerMoney(playerid, -TaxiInfo[TaxiDriver[vehicleid]][FareTotal]);
            GivePlayerMoney(TaxiDriver[vehicleid], TaxiInfo[TaxiDriver[vehicleid]][FareTotal]);
            TaxiInfo[TaxiDriver[vehicleid]][FareTotal] = 0;
            TaxiInfo[TaxiDriver[vehicleid]][FareTotal] = 0;
            TaxiInfo[playerid][InTaxi] == INVALID_VEHICLE_ID;
        }
    }

    if(newstate == PLAYER_STATE_PASSENGER){
        new vehicleid = GetPlayerVehicleID(playerid);   
        if(TaxiDriver[vehicleid] != INVALID_PLAYER_ID && vehicleid == GetPlayerVehicleID(TaxiDriver[vehicleid]))
        {
            TaxiInfo[playerid][InTaxi] = vehicleid;
            TaxiInfo[playerid][FareTimer] = SetTimerEx("FareUpdate", 1000, true, "ii", TaxiDriver[vehicleid], playerid);
        }
    }
    return 1;
}

Function:FareUpdate(playerid, passenger)
{	
	//new str[128]; untuk textdraw nanti
	GetPlayerPos(playerid,TaxiInfo[playerid][FareNewX],TaxiInfo[playerid][FareNewY],TaxiInfo[playerid][FareNewZ]);
	new Float:totdistance = GetDistanceBetweenPoints(TaxiInfo[playerid][FareOldX],TaxiInfo[playerid][FareOldY],TaxiInfo[playerid][FareOldZ], TaxiInfo[playerid][FareNewX],TaxiInfo[playerid][FareNewY],TaxiInfo[playerid][FareNewZ]);
    if(totdistance > 100.0)
    {
		new rndom = RandomEx(4, 7);
	    TaxiInfo[playerid][FareTotal] = TaxiInfo[playerid][FareTotal]+rndom;
		GetPlayerPos(playerid, TaxiInfo[playerid][FareOldX], TaxiInfo[playerid][FareOldY], TaxiInfo[playerid][FareOldZ]);
	}
	return 1;
}
