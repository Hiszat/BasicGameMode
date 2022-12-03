stock GetWeapon(playerid)
{
	new weaponid = GetPlayerWeapon(playerid);

	if (1 <= weaponid <= 46 && PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] == weaponid)
 		return weaponid;

	return 0;
}

stock ShowWeapon(playerid, targetid)
{
	new mstr[512], lstr[1024], weaponid, ammo;
	format(mstr, sizeof(mstr), "%s Weapon List", ReturnName(targetid));
	strcat(lstr, "Weapon\tAmmo\tDurability\n");
	for(new i = 0; i < 13; i ++)
    {
        GetPlayerWeaponData(targetid, i, weaponid, ammo);

        if(weaponid > 0)
			format(lstr, sizeof(lstr), "%s\n%s\t%d\t%d", lstr, ReturnWeaponName(weaponid), ammo, PlayerData[targetid][pDurability][g_aWeaponSlots[weaponid]]);
    }
    Dialog_Show(playerid, DIALOG_NONE, DIALOG_STYLE_TABLIST_HEADERS, mstr, lstr,"Close","");
    return 1;
}

stock UpdateWeapons(playerid)
{
	forex(i, 13) if (PlayerData[playerid][pGuns][i])
    {
		if ((i == 2))
		    continue;

        GetPlayerWeaponData(playerid, i, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);

        if (PlayerData[playerid][pGuns][i] != 0 && !PlayerData[playerid][pAmmo][i])
		{
            PlayerData[playerid][pGuns][i] = 0;
		}
	}
	return 1;
}

stock PlayerHasWeapon(playerid, weaponid)
{
	new
	    weapon,
	    ammo;

	forex(i, 13) if (PlayerData[playerid][pGuns][i] == weaponid) {
	    GetPlayerWeaponData(playerid, i, weapon, ammo);

	    if (weapon == weaponid && ammo > 0) return 1;
	}
	return 0;
}

stock SetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13) if (PlayerData[playerid][pGuns][i] > 0)
	{
	    GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);
	}
	return 1;
}

stock ResetWeapons(playerid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13)
	{
		PlayerData[playerid][pGuns][i] = 0;
		PlayerData[playerid][pAmmo][i] = 0;
		PlayerData[playerid][pDurability][i] = 0;
	}
	return 1;
}

stock ResetWeapon(playerid, weaponid)
{
	ResetPlayerWeapons(playerid);

	forex(i, 13)
	{
	    if (PlayerData[playerid][pGuns][i] != weaponid)
		{
	        GivePlayerWeapon(playerid, PlayerData[playerid][pGuns][i], PlayerData[playerid][pAmmo][i]);
		}
		else
		{
            PlayerData[playerid][pGuns][i] = 0;
            PlayerData[playerid][pAmmo][i] = 0;
            PlayerData[playerid][pDurability] = 0;
	    }
	}
	return 1;
}

stock PassWeaponToPlayer(playerid, weaponid, ammo, dura)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;

	PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
	PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = ammo;
	PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = dura;
	return GivePlayerWeapon(playerid, weaponid, ammo);
}

stock GiveWeaponToPlayer(playerid, weaponid, ammo = 100, dura = 500)
{
	if (weaponid < 0 || weaponid > 46)
	    return 0;

	PlayerData[playerid][pGuns][g_aWeaponSlots[weaponid]] = weaponid;
	PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]] = ammo;
	PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] = dura;
	return GivePlayerWeapon(playerid, weaponid, ammo);
}