CMD:accessories(playerid, params[])
	return cmd_acc(playerid, "");

CMD:acc(playerid, params[])
{
	if(IsPlayerInAnyVehicle(playerid)) 
		return SendErrorMessage(playerid, "This command can only be used on foot, exit your vehicle!");

	new string[350];
	format(string, sizeof(string), "Index\tAccessory Model\tBone\n");
	forex(i, 4)
	{
		if(pToys[playerid][i][toy_model] != 0)
		{
			format(string, sizeof(string), "%s{FFFFFF}#%d\t%d\t%s\n", string, i, pToys[playerid][i][toy_model], Bone_Name[pToys[playerid][i][toy_bone]]);
		}
		else
		{
			format(string, sizeof(string), "%s{AFAFAF}Empty Slot\n", string);
		}
	}
	ShowPlayerDialog(playerid, DIALOG_TOY, DIALOG_STYLE_TABLIST_HEADERS, "Accessory Menu", string, "Select", "Close");
	SavePlayerToys(playerid);
	return 1;
}

CMD:setclothing(playerid, params[])
{
	AttachPlayerToys(playerid); 
	return 1;
}