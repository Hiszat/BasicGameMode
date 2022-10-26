#include <YSI_Coding\y_hooks>

Dialog:DIALOG_RENTTIME(playerid, response, listitem, inputtext[])
{
	if(response)
	{
	    new id = PlayerData[playerid][pRenting];
	    new slot = PlayerData[playerid][pListitem];
		new time = strval(inputtext);
		if(time < 1 || time > 4)
		{
			new str[256];
			format(str, sizeof(str), "{FFFFFF}Berapa jam kamu ingin menggunakan kendaraan Rental ini ?\n{FFFFFF}Maksimal adalah {FFFF00}4 jam\n\n{FFFFFF}Harga per Jam: {009000}$%s", FormatNumber(RentData[id][rentPrice][listitem]));
			Dialog_Show(playerid, DIALOG_RENTTIME, DIALOG_STYLE_INPUT, "{FFFFFF}Rental Time", str, "Rental", "Close");
			return 1;
		}
		GiveMoney(playerid, -RentData[id][rentPrice][slot] * time, "Sewa kendaraan");
		SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Kamu telah menyewa %s untuk %d Jam seharga %s", GetVehicleModelName(RentData[id][rentModel][slot]), time, FormatNumber(RentData[id][rentPrice][slot] * time)));
        VehicleRental_Create(PlayerData[playerid][pID], RentData[id][rentModel][slot], RentData[id][rentSpawn][0], RentData[id][rentSpawn][1], RentData[id][rentSpawn][2], RentData[id][rentSpawn][3], time*3600, PlayerData[playerid][pRenting]);
	}
    return 1;
}

Dialog:RentalMenu(playerid, response, listitem, inputtext[])
{
	if(!response) return SendTextDrawMessageEx(playerid, NOTIFICATION_ERROR, "Kamu membatakan pilihan!...");

	switch(listitem)
	{
		case 0: 
		{
			if(VehicleRental_Count(playerid) > 0)
				return SendErrorMessage(playerid, "Kamu hanya bisa memiliki 1 kendaraan Rental!");
				
			forex(i, MAX_RENTAL) if(RentData[i][rentExists])
			{
				if(IsPlayerInRangeOfPoint(playerid, 3.0, RentData[i][rentPos][0], RentData[i][rentPos][1], RentData[i][rentPos][2]))
				{
					if(RentData[i][rentSpawn][0] == 0)
						return SendErrorMessage(playerid, "Rental Point ini belum memiliki Spawn Point!");

					new dstr[400];
					strcat(dstr, "Nama Kendaraan\tHarga Kendaraan / jam\n");
					forex(z, 2)
					{
						strcat(dstr, sprintf("%s\t%s\n", GetVehicleModelName(RentData[i][rentModel][z]), FormatNumber(RentData[i][rentPrice][z])));
					}
					ShowPlayerDialog(playerid, DIALOG_RENTAL, DIALOG_STYLE_TABLIST_HEADERS, "Penyewaan Kendaraan", dstr, "Select", "Close");
					PlayerData[playerid][pRenting] = i;
				}
			}
		}
		case 1: 
		{
			new pvid = Vehicle_Nearest(playerid, 4.5);
			new vehicleid = GetNearestVehicle(playerid, 5.0);
			
			if(VehicleRental_Count(playerid) < 1)
				return SendErrorMessage(playerid, "Kamu tidak memiliki kendaraan Rental!");
	    
			forex(i, MAX_RENTAL) if(RentData[i][rentExists])
			{
				if(IsPlayerInRangeOfPoint(playerid, 5.0, RentData[i][rentPos][0], RentData[i][rentPos][1], RentData[i][rentPos][2]))
				{			
					if(Vehicle_IsOwner(playerid, vehicleid))
						return SendErrorMessage(playerid, "Kamu harus di dekat kendaraan Rental milikmu!");	
						
					if(pvid == -1)
						return SendErrorMessage(playerid, "Kamu harus di dekat kendaraan Rental milikmu!");

					if(!Vehicle_IsOwner(playerid, pvid))
						return SendErrorMessage(playerid, "Kamu harus di dekat kendaraan Rental milikmu!");
					
					if(VehicleData[pvid][vRental] != i)
						return SendErrorMessage(playerid, "Disini bukan tempat penyewaan kendaraan ini.");

					SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("Kamu telah mengembalikan %s Rental milikmu!", GetVehicleName(vehicleid)));

					Vehicle_Delete(pvid);

				}
			}
		}
	}
	return 1;
}