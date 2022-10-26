/*public OnModelSelectionResponse(playerid, extraid, index, modelid, response)
{
    if ((response) && (extraid == MODEL_SELECTION_CLOTHES))
	{
	    new
			bizid = -1,
			price;

	    if ((bizid = Business_Inside(playerid)) == -1 || BusinessData[bizid][bizType] != 3)
	        return 0;

		if (BusinessData[bizid][bizProducts] < 1)
		    return SendErrorMessage(playerid, "This business is out of stock.");

	    price = BusinessData[bizid][bizPrices][PlayerData[playerid][pClothesType] - 1];

	    if (GetMoney(playerid) < price)
	        return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

		GiveMoney(playerid, -price);

		BusinessData[bizid][bizProducts]--;
		BusinessData[bizid][bizVault] += Tax_Percent(price);

		Business_Save(bizid);
		Tax_AddPercent(price);

	    switch (PlayerData[playerid][pClothesType])
	    {
	        case 1:
	        {
	            PlayerData[playerid][pSkin] = modelid;
	            SetPlayerSkin(playerid, modelid);

	            SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some clothes.", ReturnName(playerid, 0), FormatNumber(price));
			}
			case 2:
			{
			    PlayerData[playerid][pEditType] = 1;
                PlayerData[playerid][pGlasses] = modelid;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received some glasses.", ReturnName(playerid, 0), FormatNumber(price));
				RemovePlayerAttachedObject(playerid, 0);

                SetPlayerAttachedObject(playerid, 0, modelid, 2, 0.094214, 0.044044, -0.007274, 89.675476, 83.514060, 0.000000);
				EditAttachedObject(playerid, 0);
			}
			case 3:
			{
			    PlayerData[playerid][pHat] = modelid;
			    PlayerData[playerid][pEditType] = 2;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a hat.", ReturnName(playerid, 0), FormatNumber(price));
                RemovePlayerAttachedObject(playerid, 1);

				SetPlayerAttachedObject(playerid, 1, modelid, 2, 0.1565, 0.0273, -0.0002, -7.9245, -1.3224, 15.0999);
				EditAttachedObject(playerid, 1);
			}
			case 4:
			{
			    PlayerData[playerid][pBandana] = modelid;
			    PlayerData[playerid][pEditType] = 3;

			    SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has paid %s and received a bandana.", ReturnName(playerid, 0), FormatNumber(price));
			    RemovePlayerAttachedObject(playerid, 2);

			    SetPlayerAttachedObject(playerid, 2, modelid, 2, 0.099553, 0.044356, -0.000285, 89.675476, 84.277572, 0.000000);
				EditAttachedObject(playerid, 2);
			}
	    }
	}
	if ((response) && (extraid == MODEL_SELECTION_DEALER))
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
 	    {
	        if (!DealershipCars[id][index][vehModel])
	        {
	            Dialog_Show(playerid, AddVehicle, DIALOG_STYLE_LIST, "Add Vehicle", "Add by Name\nAdd by Thumbnail", "Select", "Cancel");
			}
			else
			{
			    PlayerData[playerid][pDealerCar] = index;
			    Dialog_Show(playerid, CarOptions, DIALOG_STYLE_LIST, "Dealership Vehicle", "Set Price (%s)\nRemove Vehicle", "Select", "Cancel", FormatNumber(DealershipCars[id][index][vehPrice]));
			}
	    }
	}
	if ((response) && (extraid == MODEL_SELECTION_DEALER_ADD))
	{
	    new id = PlayerData[playerid][pDealership];

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
	        for (new i = 0; i != MAX_DEALERSHIP_CARS; i ++)
			{
				if (DealershipCars[id][i][vehModel] == modelid)
	            	return SendErrorMessage(playerid, "This vehicle is already sold at this dealership.");
			}
			PlayerData[playerid][pDealerCar] = modelid;
			Dialog_Show(playerid, DealerCarPrice, DIALOG_STYLE_INPUT, "Enter Price", "Please enter a price for '%s':", "Submit", "Cancel", ReturnVehicleModelName(PlayerData[playerid][pDealerCar]));
		}
	}
	if ((response) && (extraid == MODEL_SELECTION_BUY_CAR))
	{
	    new id = Business_Inside(playerid);

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 5)
	    {
		    if (!DealershipCars[id][index][vehModel])
		        return SendErrorMessage(playerid, "There is no model in the selected slot.");

		    if (GetMoney(playerid) < DealershipCars[id][index][vehPrice])
	    	    return SendErrorMessage(playerid, "You can't afford this vehicle (%s).", FormatNumber(DealershipCars[id][index][vehPrice]));

			PlayerData[playerid][pDealerCar] = index;
			Dialog_Show(playerid, ConfirmCarBuy, DIALOG_STYLE_MSGBOX, "Confirm Purchase", "Are you sure you want to buy this '%s'?\n\nNote: This vehicle costs %s at this dealership.", "Yes", "No", ReturnVehicleModelName(modelid), FormatNumber(DealershipCars[id][index][vehPrice]));
		}
	}
	if ((response) && (extraid == MODEL_SELECTION_FURNITURE))
	{
        new
			id = Business_Inside(playerid),
			type = PlayerData[playerid][pFurnitureType],
			price;

	    if (id != -1 && BusinessData[id][bizExists] && BusinessData[id][bizType] == 7)
	    {
	        price = BusinessData[id][bizPrices][type];

	        if (GetMoney(playerid) < price)
	            return SendErrorMessage(playerid, "You have insufficient funds for the purchase.");

			if (BusinessData[id][bizProducts] < 1)
		    	return SendErrorMessage(playerid, "This business is out of stock.");

			new item = Inventory_Add(playerid, GetFurnitureNameByModel(modelid), modelid);

            if (item == -1)
   	        	return SendErrorMessage(playerid, "You don't have any inventory slots left.");

			GiveMoney(playerid, -price);
			SendServerMessage(playerid, "You have purchased a \"%s\" for %s.", GetFurnitureNameByModel(modelid), FormatNumber(price));

			BusinessData[id][bizProducts]--;
			BusinessData[id][bizVault] += Tax_Percent(price);

			Business_Save(id);
			Tax_AddPercent(price);
	    }
	}
}*/