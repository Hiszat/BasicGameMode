ptask secondsTimer[1000](playerid) 
{
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
}