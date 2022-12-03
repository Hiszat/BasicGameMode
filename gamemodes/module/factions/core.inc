#define COLOR_SAPD		0x004BFFFF

GetFactionRank(playerid)
{
	new rank[24];
	if(PlayerData[playerid][pFaction] == 1)
	{
		switch(PlayerData[playerid][pFactionRank]){
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
	if(PlayerData[playerid][pFaction] == 2)
	{
		switch(PlayerData[playerid][pFactionRank]){
			case 1: rank = "PNS";
			case 2: rank = "Pengacara";
			case 3: rank = "Jaksa";
			case 4: rank = "Wakil Hakim";
			case 5: rank = "Hakim";
			case 6: rank = "Walikota";
			case 7: rank = "Gubernur";
			case 8: rank = "Presiden";
			default: rank = "Honor";
		}
	}
	return rank;
}

GetFactionName(facid)
{
	new name[52];
	switch(facid){
		case 1: name = "San Andreas Police Deparment";
		case 2: name = "San Andreas Goverment";
		case 3: name = "Emergency Services";
		default: name = "Unknown";
	}
	return name;
}
/*
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
*/
SetFactionColor(playerid)
{
    new factionid = PlayerData[playerid][pFaction];

	switch(factionid){
		case 1: SetPlayerColor(playerid, COLOR_SAPD);
		case 2: SetPlayerColor(playerid, COLOR_GOV);
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
		switch(PlayerData[playerid][pFaction]){
			case 1:{
				SendFactionMessage(fid, 0xFFD7004A, "** [SAPD] %s %s: %s", GetFactionRank(playerid),PlayerData[playerid][pName], text);
				format(mstr, sizeof(mstr), "[<DEPARTEMENT>]\n* %s *", text);
				SetPlayerChatBubble(playerid, mstr, 0xFFD7004A, 10.0, 3000);
			}
			case 2:{
				SendFactionMessage(fid, 0xFFD7004A, "** [GOV] %s %s: %s", GetFactionRank(playerid),PlayerData[playerid][pName], text);
				format(mstr, sizeof(mstr), "[<DEPARTEMENT>]\n* %s *", text);
				SetPlayerChatBubble(playerid, mstr, 0xFFD7004A, 10.0, 3000);
			}
			default:{
				return SendErrorMessage(playerid, "You aren't in any faction");
			}
		}			
	}
    return 1;
}

CMD:gov(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 0)
		return SendErrorMessage(playerid, "You are not faction!");
	
	if(PlayerData[playerid][pFactionRank] < 5)
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

CMD:online(playerid, params[])
{
	new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	SendClientMessage(playerid, X11_LIGHTBLUE, "Online Members:");

	foreach (new i : Player) if (PlayerData[i][pFaction] == factionid) {
		SendClientMessageEx(playerid, X11_WHITE, "[ID: %d] %s - %s (%d)", i, ReturnName(i, 0), GetFactionRank(PlayerData[i][pFactionRank]), PlayerData[i][pFactionRank]);
	}
	return 1;
}

CMD:fac(playerid, params[])
{
    new factionid = PlayerData[playerid][pFaction];

 	if (factionid == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if (isnull(params))
	    return SendSyntaxMessage(playerid, "/(f)ac [message]");

    if (PlayerData[playerid][pDisableFaction])
	    return SendErrorMessage(playerid, "You must enable faction chat first.");

	SendFactionMessage(factionid, X11_WHITE, "(( (%d) %s %s: %s ))", PlayerData[playerid][pFactionRank], GetFactionRank(PlayerData[playerid][pFactionRank]), ReturnName(playerid, 0), params);
	printf("[%s] %s %s: %s", ReturnDate(), GetFactionRank(PlayerData[playerid][pFactionRank]), ReturnName(playerid, 0), params);
	return 1;
}

CMD:fquit(playerid, params[])
{
	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	SendServerMessage(playerid, "You have quit the \"%s\" faction (rank %s).", GetFactionName(PlayerData[playerid][pFaction]), GetFactionRank(PlayerData[playerid][pFactionRank]));
    ResetFaction(playerid);

    return 1;
}

CMD:finvite(playerid, params[])
{
	new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if(ISACopLeader(playerid) || ISAGovLeader(playerid)){ // Jika Faction LSPD dan Tapi Rank dibawah 11	
		if(sscanf(params, "ud", userid))
			return SendSyntaxMessage(playerid, "/finvite [playerid/PartOfName]");

		if (userid == INVALID_PLAYER_ID)
		    return SendErrorMessage(playerid, "That player is disconnected.");

		if (PlayerData[userid][pFaction] == PlayerData[playerid][pFaction])
		    return SendErrorMessage(playerid, "That player is already part of your faction.");

    	if (PlayerData[userid][pFaction] != -1)
		    return SendErrorMessage(playerid, "That player is already part of another faction.");

		PlayerData[userid][pFactionOffer] = playerid;
    	PlayerData[userid][pFactionOffered] = PlayerData[playerid][pFaction];

    	SendServerMessage(playerid, "You have requested %s to join \"%s\".", ReturnName(userid, 0),  GetFactionName(PlayerData[playerid][pFaction]));
    	SendServerMessage(userid, "%s has offered you to join \"%s\" (type \"/approve faction\").", ReturnName(playerid, 0),  GetFactionName(PlayerData[playerid][pFaction]));
	}
	return 1;
}

CMD:fremove(playerid, params[])
{
    new
	    userid;

	if (PlayerData[playerid][pFaction] == -1)
	    return SendErrorMessage(playerid, "You must be a faction member.");

	if(ISACopLeader(playerid) || ISAGovLeader(playerid)){ // Jika Faction LSPD dan Tapi Rank dibawah 11	
		if(sscanf(params, "u", userid))
			return SendSyntaxMessage(playerid, "/fremove [playerid/PartOfName]");

		if (sscanf(params, "u", userid))
		    return SendSyntaxMessage(playerid, "/fremove [playerid/name]");

		if (userid == INVALID_PLAYER_ID)
		    return SendErrorMessage(playerid, "That player is disconnected.");

		if (PlayerData[userid][pFaction] != PlayerData[playerid][pFaction])
		    return SendErrorMessage(playerid, "That player is not part of your faction.");

		if(PlayerData[userid][pFactionRank] >= PlayerData[playerid][pFactionRank])
				return SendErrorMessage(playerid, "The player rank is higher than you!");	

    	SendServerMessage(playerid, "You have removed %s from \"%s\".", ReturnName(userid, 0),  GetFactionName(PlayerData[playerid][pFaction]));
    	SendServerMessage(userid, "%s has removed you from the \"%s\" faction.", ReturnName(playerid, 0),  GetFactionName(PlayerData[playerid][pFaction]));

    	ResetFaction(userid);
	}
	return 1;
}

CMD:setrank(playerid, params[])
{
	new rank, otherid;
	if(PlayerData[playerid][pFaction] == 0)
		return SendErrorMessage(playerid, "You must joining faction!");

	if(ISACopLeader(playerid) || ISAGovLeader(playerid)){ // Jika Faction LSPD dan Tapi Rank dibawah 11	
		if(sscanf(params, "ud", otherid, rank))
			return SendSyntaxMessage(playerid, "/setrank [playerid/PartOfName] [rank 1-14]");
			
		if(otherid == INVALID_PLAYER_ID)
			return SendErrorMessage(playerid, "Invalid ID.");
		
		if(otherid == playerid)
			return SendErrorMessage(playerid, "Invalid ID.");
		
		if(PlayerData[otherid][pFaction] != PlayerData[playerid][pFaction])
			return SendErrorMessage(playerid, "This player is not in your faction!");
		
		if(PlayerData[otherid][pFactionRank] >= PlayerData[playerid][pFactionRank])
			return SendErrorMessage(playerid, "This player rank is higher than you!");

		if(rank >= PlayerData[playerid][pFactionRank])
			return SendErrorMessage(playerid, "You can't set this player rank higher than you!");	

		new tidakpenting[126];
		format(tidakpenting, sizeof(tidakpenting), "Rank must 0 - %d only", GetFactionMaxRank(PlayerData[playerid][pFaction]));
		if(rank < 1 || rank > GetFactionMaxRank(PlayerData[playerid][pFaction]))
			return SendErrorMessage(playerid, tidakpenting);

		
		PlayerData[otherid][pFactionRank] = rank;
		new infoo[256];
		format(infoo, sizeof(infoo), "You has set %s faction rank to level %d", PlayerData[otherid][pName], rank);
		SendServerMessage(playerid, infoo);
		format(infoo, sizeof(infoo), "%s has set your faction rank to level %d", PlayerData[playerid][pName], rank);
		SendServerMessage(otherid, infoo);
	}
	return 1;
}

ISACopLeader(playerid)
{
	if(PlayerData[playerid][pFaction] == 1 && PlayerData[playerid][pFactionRank] >= 11){
		return 1;
	}
	return 0;
}

ISAGovLeader(playerid)
{
	if(PlayerData[playerid][pFaction] == 2 && PlayerData[playerid][pFactionRank] >= 6){
		return 1;
	}
	return 0;
}

GetFactionMaxRank(factionid)
{
	switch(factionid){
		case 1:{
			return 14;
		}
		case 2:{
			return 8;
		}
	}
	return 0;
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
