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