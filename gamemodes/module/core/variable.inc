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
new toySlot[MAX_PLAYERS][4];
new toyToggle[MAX_PLAYERS][4];
new toySelect[MAX_PLAYERS];

new Tax;
new TaxVault;

new Pagessss[MAX_PLAYERS];
new NAMAORANGGILA[MAX_PLAYERS][MAX_PLAYER_NAME];
new IsHauling[MAX_PLAYERS];
//============================ SAPD SYSTEM =============================
new CellPrisoners[9];
new CellPickup[8];
//============================ JOB =====================================
new bool:DialogHauling[10];
new TrailerHauling[MAX_PLAYERS];
new bool:HuntingRifle[MAX_PLAYERS];
//============================ DEER ====================================
new Text3D: DeerTrack[MAX_DEERS][MAX_DEER_TRACKS];
new Float: dRotX[MAX_DEERS], Float: dRotY[MAX_DEERS];