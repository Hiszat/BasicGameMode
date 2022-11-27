#include <YSI_Coding\y_hooks>

hook OnPlayerDeath(playerid, killerid, reason)
{
    if(reason == 51 || reason == 255 || reason == 49)
    {
		if(!PlayerData[playerid][pInjured])
		{
			PlayerData[playerid][pInjured] = true;
			GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
		}
		else
		{
			PlayerData[playerid][pDead] = true;
		}
    }
    return 1;
}