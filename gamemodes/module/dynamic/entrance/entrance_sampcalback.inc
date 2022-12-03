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
