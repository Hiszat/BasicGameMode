
stock Tax_Percent(price)
{
	return floatround((float(price) / 100) * Tax);
}

stock Tax_AddMoney(amount)
{
	TaxVault += amount;

	//Server_Save();

	return 0;
}

stock Tax_AddPercent(price)
{
	new money = (price - Tax_Percent(price));

	TaxVault  += money;

	//Server_Save();
	return 1;
}

// Server_Save()
// {
// 	new
// 	    File:file = fopen("server.ini", io_write),
// 	    str[128];

// 	format(str, sizeof(str), "TaxMoney = %d\n", g_TaxVault);
// 	return (fwrite(file, str), fclose(file));
// }

// Server_Load()
// {
// 	new File:file = fopen("server.ini", io_read);

// 	if (file) {
// 		g_TaxVault = file_parse_int(file, "TaxMoney");

// 		fclose(file);
// 	}
// 	return 1;
// }