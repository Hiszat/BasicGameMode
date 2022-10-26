//============================== MYSQL =============================
new MySQL:sqlcon;
new g_RaceCheck[MAX_PLAYERS char];

//============================ TEXTDRAW =============================
new PlayerText:PassportTD_1[MAX_PLAYERS][15];
new PlayerText:PassportTD_2[MAX_PLAYERS][46];

//INVENTORY TEXTDRAW
new PlayerText:INVBAR[MAX_PLAYERS];
new PlayerText:INVNAME[MAX_PLAYERS];
new PlayerText:ITEM[20][MAX_PLAYERS];
new PlayerText:ITEMTXT[20][MAX_PLAYERS];
new PlayerText:INVJUMLAH[MAX_PLAYERS][20];
new Text:INV_TD[10];
new PlayerText:iNotification[MAX_PLAYERS][3];

//============================ TEMP PLAYER =============================
new SellLastSpawn[MAX_PLAYERS];