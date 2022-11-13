#define COLOR_SAPD		0x004BFFFF

GetFactionRank(playerid)
{
	new rank[24];
	if(PlayerData[playerid][pFaction] == 1)
	{
		switch(PlayerData[playerid][pFacRank]){
			case 1: rank = "BHARADA";
			case 2: rank = "BHARATU";
			case 3: rank = "BHARAKA";
			case 4: rank = "BRIPKA";
			case 5: rank = "AIPTU";
			case 6: rank = "IPDA";
			case 7: rank = "IPTU";
			case 8: rank = "KOMPOL";
			case 9: rank = "AKBP";
			case 10: rank = "KOMBESPOL";
			case 11: rank = "BRIGJENPOL";
			case 12: rank = "IRJENPOL";
			case 13: rank = "KOMJENPOL";
			case 14: rank = "Jenderal Polisi";
			default: rank = "Training";
		}
	}
	return rank;
}

GetFactionName(facid)
{
	new name[52];
	switch(facid){
		case 1: name = "San Andreas Police Deparment";
		case 2: name = "Emergency Services";
		case 3: name = "Goverment";
		default: name = "Unknown";
	}
	return name;
}

SendFactionMessage(factionid, color, const str[], {Float,_}:...)
{
    static
        args,
        start,
        end,
        string[144]
    ;
    #emit LOAD.S.pri 8
    #emit STOR.pri args

    if(args > 12)
    {
        #emit ADDR.pri str
        #emit STOR.pri start

        for (end = start + (args - 12); end > start; end -= 4)
        {
            #emit LREF.pri end
            #emit PUSH.pri
        }
        #emit PUSH.S str
        #emit PUSH.C 144
        #emit PUSH.C string
        #emit PUSH.C args

        #emit SYSREQ.C format
        #emit LCTRL 5
        #emit SCTRL 4

        foreach (new i : Player) if(PlayerData[i][pFaction] == factionid) {
                SendClientMessage(i, color, string);
        }
        return 1;
    }
    foreach (new i : Player) if(PlayerData[i][pFaction] == factionid) {
        SendClientMessage(i, color, str);
    }
    return 1;
}

SetFactionColor(playerid)
{
    new factionid = PlayerData[playerid][pFaction];

	switch(factionid){
		case 1: SetPlayerColor(playerid, COLOR_SAPD);
		default: SetPlayerColor(playerid, 0xFFFFFFFF);
	}
	return 1;
}

CMD:d(playerid, params[])
{
    new text[128], mstr[512];
    
    if(PlayerData[playerid][pFaction] == 0)
        return SendErrorMessage(playerid, "You must in faction member to use this command.");
            
    if(sscanf(params,"s[128]",text))
        return SendSyntaxMessage(playerid, "/d(epartement) [text]");

    if(strval(text) > 128)
        return SendErrorMessage(playerid,"Text too long.");
	
	for(new fid = 1; fid < 5; fid++)
	{
		if(PlayerData[playerid][pFaction] == 1) 
		{
			SendFactionMessage(fid, 0xFFD7004A, "** [SAPD Departement] %s %s: %s", GetFactionRank(playerid),PlayerData[playerid][pName], text);
			format(mstr, sizeof(mstr), "[<DEPARTEMENT>]\n* %s *", text);
			SetPlayerChatBubble(playerid, mstr, 0xFFD7004A, 10.0, 3000);
		}
		else
				return SendErrorMessage(playerid, "You aren't in any faction");
	}
    return 1;
}

CMD:gov(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 0)
		return SendErrorMessage(playerid, "You are not faction!");
	
	if(PlayerData[playerid][pFacRank] < 5)
		return SendErrorMessage(playerid, "Only Faction Rank 5 or above");
		
	if(PlayerData[playerid][pFaction] == 1)
	{
		new lstr[1024];
		format(lstr, sizeof(lstr), "** %s **", params);
		SendClientMessageToAll( 0xFFFFFFFFF, "|___________ SAPD News Announcement ___________|");
		SendClientMessageToAll(COLOR_SAPD, lstr);
	}
	return 1;
}


CMD:setrank(playerid, params[])
{
	new rank, otherid;
	if(PlayerData[playerid][pFaction] == 0)
		return SendErrorMessage(playerid, "You must joining faction!");

	if(/*PlayerData[playerid][pFaction] == 1 && */PlayerData[playerid][pFacRank] < 11) // Jika Faction LSPD dan Tapi Rank dibawah 11
		return SendErrorMessage(playerid, "You must faction leader!");
		
	if(sscanf(params, "ud", otherid, rank))
        return SendSyntaxMessage(playerid, "/setrank [playerid/PartOfName] [rank 1-14]");
		
	if(otherid == INVALID_PLAYER_ID)
		return SendErrorMessage(playerid, "Invalid ID.");
	
	if(otherid == playerid)
		return SendErrorMessage(playerid, "Invalid ID.");
	
	if(PlayerData[otherid][pFaction] != PlayerData[playerid][pFaction])
		return SendErrorMessage(playerid, "This player is not in your faction!");
	
	if(PlayerData[otherid][pFacRank] >= PlayerData[playerid][pFacRank])
		return SendErrorMessage(playerid, "This player rank is higher than you!");

	if(rank >= PlayerData[playerid][pFacRank])
		return SendErrorMessage(playerid, "You can't set this player rank higher than you!");	

	if(rank < 1 || rank > 14)
		return SendErrorMessage(playerid, "Rank must 1 - 14 only");
	
	PlayerData[otherid][pFacRank] = rank;
	new infoo[256];
	format(infoo, sizeof(infoo), "You has set %s faction rank to level %d", PlayerData[otherid][pName], rank);
	SendServerMessage(playerid, infoo);
	format(infoo, sizeof(infoo), "%s has set your faction rank to level %d", PlayerData[playerid][pName], rank);
	SendServerMessage(otherid, infoo);
	return 1;
}


/*
GetFactionDiv(playerid)
{
	new division[24];
	if(PlayerData[playerid][pFaction] == 1)
	{
		switch(PlayerData[playerid][pFacDiv]){
			case 1: division = "DENSUS 88";
			case 2: division = "SATLANTAS";
			case 3: division = "BARESKRIM";
			case 4: division = "MABES";
			case 5: division = "HUMAS";
			case 6: division = "CYBER";
			default: rank = "Training";
		}
	}
	return rank;
}
*/
