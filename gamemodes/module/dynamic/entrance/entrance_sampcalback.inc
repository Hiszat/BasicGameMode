#include <YSI_Coding\y_hooks>

hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
    static
	    id = -1;

    if (newkeys & KEY_SECONDARY_ATTACK)
    {
        if ((id = Entrance_Nearest(playerid)) != -1)
	    {
	        if (EntranceData[id][entranceLocked])
	            return SendErrorMessage(playerid, "This entrance is locked at the moment.");

			if (EntranceData[id][entranceCustom])
				SetPlayerPosEx(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);

			else
			    SetPlayerPos(playerid, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]);

			SetPlayerFacingAngle(playerid, EntranceData[id][entranceInt][3]);

			SetPlayerInterior(playerid, EntranceData[id][entranceInterior]);
			SetPlayerVirtualWorld(playerid, EntranceData[id][entranceWorld]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pEntrance] = EntranceData[id][entranceID];
			return 1;
		}
		if ((id = Entrance_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, EntranceData[id][entranceInt][0], EntranceData[id][entranceInt][1], EntranceData[id][entranceInt][2]))
	    {
	        if (EntranceData[id][entranceCustom])
				SetPlayerPosEx(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);

			else
			    SetPlayerPosEx(playerid, EntranceData[id][entrancePos][0], EntranceData[id][entrancePos][1], EntranceData[id][entrancePos][2]);

			SetPlayerFacingAngle(playerid, EntranceData[id][entrancePos][3] - 180.0);

			SetPlayerInterior(playerid, EntranceData[id][entranceExterior]);
			SetPlayerVirtualWorld(playerid, EntranceData[id][entranceExteriorVW]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pEntrance] = Entrance_GetLink(playerid);
			return 1;
		}
		if ((id = Business_Nearest(playerid)) != -1)
	    {
	        if (BusinessData[id][bizLocked])
	            return SendErrorMessage(playerid, "This business is closed by the owner.");

			SetPlayerPos(playerid, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]);
			SetPlayerFacingAngle(playerid, BusinessData[id][bizInt][3]);

			SetPlayerInterior(playerid, BusinessData[id][bizInterior]);
			SetPlayerVirtualWorld(playerid, BusinessData[id][bizID] + 6000);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pBusiness] = BusinessData[id][bizID];

			if (strlen(BusinessData[id][bizMessage]) && strcmp(BusinessData[id][bizMessage], "NULL", true)) {
			    SendClientMessage(playerid, X11_LIGHTBLUE, BusinessData[id][bizMessage]);
			}
			return 1;
		}
		if ((id = Business_Inside(playerid)) != -1 && IsPlayerInRangeOfPoint(playerid, 2.5, BusinessData[id][bizInt][0], BusinessData[id][bizInt][1], BusinessData[id][bizInt][2]))
	    {
			SetPlayerPos(playerid, BusinessData[id][bizPos][0], BusinessData[id][bizPos][1], BusinessData[id][bizPos][2]);
			SetPlayerFacingAngle(playerid, BusinessData[id][bizPos][3] - 180.0);

			SetPlayerInterior(playerid, BusinessData[id][bizExterior]);
			SetPlayerVirtualWorld(playerid, BusinessData[id][bizExteriorVW]);

			SetCameraBehindPlayer(playerid);
			PlayerData[playerid][pBusiness] = -1;
			return 1;
		}
    }
    return 1;
}

CMD:lockentrance(playerid, params[])
{
	static
	    id = -1;
    
    if (!IsPlayerInAnyVehicle(playerid) && (id = (Entrance_Inside(playerid) == -1) ? (Entrance_Nearest(playerid)) : (Entrance_Inside(playerid))) != -1)
	{
		if (strlen(EntranceData[id][entrancePass]))
		{
			Dialog_Show(playerid, EntrancePass, DIALOG_STYLE_INPUT, "Entrance Pass", "Please enter the password for this entrance:", "Submit", "Cancel");
		}
	}
    return 1;
}
