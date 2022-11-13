Function:UseSnack(playerid)
{
    PlayerData[playerid][pHunger] += 10;
	Inventory_Remove(playerid, "Snack", 1);

    SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Makanan telah di habis di makan"));
}

Function:UseWater(playerid)
{
    PlayerData[playerid][pThirst] += 10;
	Inventory_Remove(playerid, "Water", 1);

    SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Minuman telah di habis di minum"));
}

Function:UseMilk(playerid)
{
    PlayerData[playerid][pThirst] += 14;
	Inventory_Remove(playerid, "Milk", 1);

    SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Susu telah di habis di minum"));
}

Function:UsePizza(playerid)
{
    PlayerData[playerid][pHunger] += 35;
	Inventory_Remove(playerid, "Pizza", 1);
}

Function:UseBurger(playerid)
{
    PlayerData[playerid][pHunger] += 35;
	Inventory_Remove(playerid, "Burger", 1);
}

Function:UseAyamGoreng(playerid)
{
    PlayerData[playerid][pHunger] += 35;
	Inventory_Remove(playerid, "Fried Chicken", 1);
}

IsNumeric(const str[])
{
	for (new i = 0, l = strlen(str); i != l; i ++)
	{
	    if (i == 0 && str[0] == '-')
			continue;

	    else if (str[i] < '0' || str[i] > '9')
			return 0;
	}
	return 1;
}

ReturnDate()
{
	static
	    date[36];

	getdate(date[2], date[1], date[0]);
	gettime(date[3], date[4], date[5]);

	format(date, sizeof(date), "%02d/%02d/%d, %02d:%02d", date[0], date[1], date[2], date[3], date[4]);
	return date;
}

stock GetPlayerID(name[], underscore = 1)
{
	foreach (new i : Player) if (!strcmp(ReturnName(i, underscore), name, true)) {
	    return i;
	}
	return INVALID_PLAYER_ID;
}

stock IsPlayerConnected2(playerid){
    if(IsPlayerConnected(playerid) && PlayerData[playerid][pLoggedIn] == true){
        return 1;
    }
    return 0;
}

stock IsPlayerConnectedEx(playerid){
    if(IsPlayerConnected(playerid) && PlayerData[playerid][pLoggedIn] == true && PlayerData[playerid][pSpawned] == true){
        return 1;
    }
    return 0;
}