CMD:settax(playerid, params[])
{
	if(PlayerData[playerid][pFaction] != 2)
	{
		SendErrorMessage(playerid, "Kamu bukan bagian dari Pemerintah.");
		return 1;
	}
	if(PlayerData[playerid][pFacRank] != 8)
	{
		SendErrorMessage(playerid, "Kamu bukan presiden.");
		return 1;
	}

	new String[512], pajakanjing;
	if(sscanf(params, "d", pajakanjing)) return SendSyntaxMessage(playerid, "/settax [percentage]");

	if (pajakanjing < 1 || pajakanjing > 51)
	{
		SendServerMessage(playerid, "Perkiraan pajak harus berada diatas 0 dan dibawah 50.");
		return 1;
	}
	Tax = pajakanjing;
	SaveServerStuff(1, Tax);
	format(String, sizeof(String), "Pendapatan pajak telah di set menjadi %d persen (setiap gajian).", Tax);
	SendServerMessage(playerid, String);
	return 1;
}

CMD:taxwithdraw(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 2 && PlayerData[playerid][pFacRank] == 8){
 		new String[1024], amount;
		if(sscanf(params, "d", amount))
		{
			SendSyntaxMessage(playerid, "/taxwithdraw [jumlah]");
			return 1;
		}
		if(amount > TaxVault)
		{
			SendErrorMessage(playerid, "Jumlah yang dimasukkan melebihi Pajak Tersimpan.");
			return 1;
		}
		if(amount < 0) return SendErrorMessage(playerid, "Tidak bisa dibawah $0.00");
   		GivePlayerMoney(playerid,amount);
		TaxVault -= amount;
		format(String, sizeof(String), "Kamu mengambil ~g~$%d~w~ dari uang pajak yang tersimpan. ", amount);
		SendServerMessage(playerid, String);
		format(String, sizeof(String), "Tersisa ~g~$%d", TaxVault);
		SendServerMessage(playerid, String);
	}else return SendErrorMessage(playerid, "Kamu bukan presiden.");
	return 1;
}

CMD:taxwithdraw(playerid, params[])
{
	if(PlayerData[playerid][pFaction] == 2 && PlayerData[playerid][pFacRank] == 8){
 		new String[1024], amount;
		if(sscanf(params, "d", amount))
		{
			SendSyntaxMessage(playerid, "/taxdeposit [jumlah]");
			return 1;
		}
		if(amount > GetPlayerMoney(playerid))
		{
			SendErrorMessage(playerid, "Jumlah yang dimasukkan melebihi Pajak Tersimpan.");
			return 1;
		}
		if(amount < 0) return SendErrorMessage(playerid, "Tidak bisa dibawah $0.00");
   		GivePlayerMoney(playerid,-amount);
		TaxVault += amount;
		format(String, sizeof(String), "Kamu menaruh ~g~$%d~w~ didalam Pajak Tersimpan. ", amount);
		SendServerMessage(playerid, String);
		format(String, sizeof(String), "Tersisa ~g~$%d", TaxVault);
		SendServerMessage(playerid, String);
	}else return SendErrorMessage(playerid, "Kamu bukan presiden.");
	return 1;
}

CMD:createidcard(playerid, params[]) // KANG INI BUAT FUNCTION ID CARD
{
	if(PlayerData[playerid][pFaction] == 2){
		new otherid;
		if(sscanf(params, "d", otherid))
		{
			SendSyntaxMessage(playerid, "/createidcard [playerid]");
			return 1;
		}
		if(IsPlayerNearPlayer(playerid, otherid, 4.0)){
			SendClientMessage(playerid, 0xFFFFFFFF, "Kamu telah membuatkan id card");
			SendClientMessage(otherid, 0xFFFFFFFF, "Kamu telah dibuatkan id card");
		}
	}
	return 1;
}

CMD:settaxmoney(playerid, params[])
{
	if(PlayerData[playerid][pAdmin] < 5)
	{
		SendServerMessage(playerid, "You're not authorised to use this command.");
		return 1;
	}

	new String[1024], amount;
	if(sscanf(params, "d", amount))
	{
		SendSyntaxMessage(playerid, "/settaxmoney [amount]");
		format(String, sizeof(String), "CURRENT VAULT BALANCE: %d.", TaxVault);
		SendServerMessage(playerid, String);
		return 1;
	}

	TaxVault = amount;
	format( String, sizeof( String ), "You have set the tax money amount to %d.", amount);
	SendServerMessage(playerid, String );
	return 1;
}

CMD:checktax(playerid, params[])
{
	new String[1024];
	if(PlayerData[playerid][pFaction] == 2)
	{
		format(String, sizeof(String), "Pajak Potongan %d\nPajak Tersimpan %d.", Tax, TaxVault);
		SendServerMessage(playerid, String);
	}
	return 1;
}

