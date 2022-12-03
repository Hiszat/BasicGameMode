CMD:createberangkas(playerid, params[])
{
    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	// if (isnull(params) || strlen(params) > 32)
	//     return SendSyntaxMessage(playerid, "/createberangkas");

	new id = Berangkas_Create(playerid);

	if (id == -1)
	    return SendErrorMessage(playerid, "Server telah mencapai batas berangkas.");

	SendServerMessage(playerid, sprintf("Anda telah berhasil membuat berangkas ID: %d.", id));
	return 1;
}

CMD:destroyberangkas(playerid, params[])
{
	static
	    id = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", id))
	    return SendSyntaxMessage(playerid, "/destroyberangkas [berangkas id]");

	if ((id < 0 || id >= MAX_DYNAMIC_BERANGKAS) || !BerangkasData[id][bExists])
	    return SendErrorMessage(playerid, "Anda telah menentukan ID berangkas yang tidak valid.");

	Berangkas_Delete(id);
	SendServerMessage(playerid, sprintf("Kamu berhasil menghapus berangkas id: %d.", id));
	return 1;
}

CMD:berangkaspos(playerid, params[])
{
    static
	    bid = 0;

    if (PlayerData[playerid][pAdmin] < 5)
	    return SendErrorMessage(playerid, "You don't have permission to use this command.");

	if (sscanf(params, "d", bid))
	    return SendSyntaxMessage(playerid, "/destroyberangkas [berangkas id]");

	if ((bid < 0 || bid >= MAX_DYNAMIC_BERANGKAS) || !BerangkasData[bid][bExists])
	    return SendErrorMessage(playerid, "Anda telah menentukan ID berangkas yang tidak valid.");

    GetPlayerPos(playerid, BerangkasData[bid][bPos][0], BerangkasData[bid][bPos][1], BerangkasData[bid][bPos][2]);

	Berangkas_Refresh(bid);
	Berangkas_Save(bid);

	SendAdminAction(playerid, "%s telah menyesuaikan lokasi berangkas id: %d.", ReturnName(playerid, 0), bid);
    return 1;
}