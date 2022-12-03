stock GetClothingName(id)
{
	new returnClothesName[MAX_PLAYER_NAME] = "Unkown", query[200];

	mysql_format(sqlcon, query, sizeof(query), "SELECT Name FROM toys WHERE id = %i LIMIT 1", id);
	new Cache:result = mysql_query(sqlcon, query);

	if(cache_num_rows() > 0) cache_get_value_name(0, "Name", returnClothesName);
	cache_delete(result);
	return returnClothesName;
}

stock House_ClothingStorage(playerid, houseid)
{
	if (houseid == -1 || !HouseData[houseid][houseExists])
	    return 0;

	static
	    string[320];

	string[0] = 0;

	for (new i = 0; i < 5; i ++)
	{
	    if (!HouseData[houseid][houseClothing][i])
	        format(string, sizeof(string), "%sRuang Tersedia\n", string);

		else
			format(string, sizeof(string), "%sPakaian %s\t(%d)\n", string, GetClothingName(HouseData[houseid][houseClothing][i]), HouseData[houseid][houseClothing][i]);
	}
	Dialog_Show(playerid, HouseClothing, DIALOG_STYLE_LIST, "Lemari Baju", string, "Select", "Cancel");
	return 1;
}

Dialog:HouseClothing(playerid, response, listitem, inputtext[])
{
	static
	    houseid = -1;

    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || PlayerData[playerid][pFaction] == 1))
	{
		if (response)
		{
			PlayerData[playerid][pListitem] = listitem;
		    if (HouseData[houseid][houseClothing][listitem] != 0)
		    {
				Dialog_Show(playerid, BajuOption, DIALOG_STYLE_LIST, "Pilihan Lemari", "Pakai Baju\nBuang Baju", "Select", "Cancel");
			}
			else
			{
				forex(i, 5)
				{
					if(HouseData[houseid][houseClothing][i] == PlayerData[playerid][pClothing]) return House_ClothingStorage(playerid, houseid);
				}
				SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah menyimpan pakaian %s ke dalam lemari pakaian.", ReturnName(playerid, 0), pToys[PlayerData[playerid][pClothing]][0][toy_name]);
                printf("[%s] %s has store a \"%s\"clothing from house ID: %d (owner: %s).", ReturnDate(), ReturnName(playerid, 0), GetClothingName(HouseData[houseid][houseClothing][listitem]), HouseData[houseid][houseID], (House_IsOwner(playerid, houseid)) ? ("Yes") : ("No"));

                HouseData[houseid][houseClothing][listitem] = PlayerData[playerid][pClothing];


				House_Save(houseid);
				House_ClothingStorage(playerid, houseid);
			}
		}
		else
		{
		    House_OpenStorage(playerid, houseid);
		}
	}
	return 1;
}

Dialog:BajuOption(playerid, response, listitem, inputtext[])
{
    if(!response) return 1;

    static
	    houseid = -1,
		string[300];

    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid) || PlayerData[playerid][pFaction] == 1))
	{
        if(listitem == 0)
        {
            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah mengambil pakaian %s dari dalam lemari pakaian.", ReturnName(playerid, 0), GetClothingName(HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]]));

            PlayerData[playerid][pClothing] = HouseData[houseid][houseClothing][listitem];

            // HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]] = 0;

            House_Save(houseid);
            House_ClothingStorage(playerid, houseid);
            LoadPlayerToys(playerid);
        }
        else if(listitem == 1)
        {
			if(HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]] == PlayerData[playerid][pClothing]) return SendErrorMessage(playerid, "Tidak bisa membuang baju yang sedang di gunakan");
			SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s telah mmembuang pakaian %s dari dalam lemari pakaian.", ReturnName(playerid, 0), GetClothingName(HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]]));

            HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]] = 0;

			format(string, sizeof(string), "DELETE FROM `toys` WHERE `houseID` = '%d'", HouseData[houseid][houseClothing][PlayerData[playerid][pListitem]]);
			mysql_tquery(sqlcon, string);

            House_Save(houseid);
            House_ClothingStorage(playerid, houseid);

        }
    }
    return 1;
}