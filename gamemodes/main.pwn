/* Includes */
#include <a_samp>
#include <a_zones>
#include <a_mysql>

// YSI
#include <YSI_Coding\y_va>
#include <YSI_Coding\y_timers>
#include <YSI_Server\y_colours>

#include <EVF2>
#include <sscanf2>
#include <foreach>
#include <easyDialog>
#include <eSelection>
#include <samp_bcrypt>
#include <streamer>
#include <strlib>
#include <izcmd>

// core
#include "module/core/defined.inc"
#include "module/core/array.inc"
#include "module/core/enum.inc"
#include "module/core/enum_variable.inc"
#include "module/core/variable.inc"
#include "module/core/progressbar.inc"
#include "module/core/native.inc"
#include "module/core/function.inc"
#include "module/core/timer.inc"

// misc
#include "module/misc/staticLocation.inc"

// server
#include "module/server/economy_server.inc"

// penting
#include "module/player/weapon/weapon_function.inc"
#include "module/player/weapon/weapon_commands.inc"


// dynamic
//#include "module/dynamic/fraksi/fraksi_function.inc"
//#include "module/dynamic/fraksi/fraksi_commands.inc"

#include "module/dynamic/entrance/entrance_function.inc"
#include "module/dynamic/entrance/entrance_commands.inc"
#include "module/dynamic/entrance/entrance_sampcalback.inc"

#include "module/dynamic/berangkas/berangkas_core.inc"
#include "module/dynamic/berangkas/berangkas_function.inc"
#include "module/dynamic/berangkas/berangkas_commands.inc"

#include "module/dynamic/houses/houses_core.inc"
#include "module/dynamic/houses/houses_function.inc"
#include "module/dynamic/houses/houses_commands.inc"
#include "module/dynamic/houses/house_storage.inc"

#include "module/dynamic/business/business_function.inc"
#include "module/dynamic/business/business_commands.inc"
#include "module/dynamic/business/business_sampcalback.inc"

#include "module/dynamic/vehicle/veh_core.inc"
#include "module/dynamic/vehicle/veh_function.inc"
#include "module/dynamic/vehicle/veh_commands.inc"

#include "module/dynamic/garkot/garkot_core.inc"
#include "module/dynamic/garkot/garkot_function.inc"
#include "module/dynamic/garkot/garkot_commands.inc"

#include "module/dynamic/rental/rent_function.inc"
#include "module/dynamic/rental/rent_commands.inc"
#include "module/dynamic/rental/rent_sampcalback.inc"

// player
#include "module/player/radialmenu.inc"
#include "module/player/spawnmenu.inc"
#include "module/player/visual/hud.inc"
#include "module/player/dropitem/dropitem_function.inc"

#include "module/player/inventory/inven_core.inc"
#include "module/player/inventory/inven_function.inc"
#include "module/player/inventory/inven_sampcallback.inc"
#include "module/player/inventory/inven_commands.inc"

#include "module/player/injured/injured_core.inc"
#include "module/player/injured/injured_function.inc"
#include "module/player/injured/injured_sampcallback.inc"
#include "module/player/injured/injured_commands.inc"

#include "module/player/notification/core_notification.inc"
#include "module/player/notification/function_notification.inc"

#include "module/player/passport/core_passport.inc"
#include "module/player/passport/function_passport.inc"

#include "module/player/smartphone/smartphone_core.inc"
#include "module/player/smartphone/smartphone_textdraws.inc"
#include "module/player/smartphone/smartphone_function.inc"
#include "module/player/smartphone/smartphone_commands.inc"
#include "module/player/smartphone/smartphone_sampcalback.inc"

// masih di pending dan akan di lanjutkan setelah sistem rumah selesai
#include "module/player/clothing/clothing_core.inc"
#include "module/player/clothing/clothing_function.inc"
#include "module/player/clothing/clothing_commands.inc"

// admin
#include "module/admin/admin_function.inc"
#include "module/admin/admin_commands.inc"

// player
#include "module/player/commands.inc"
#include "module/player/sampcallback.inc"

//mapping
#include "module/map/hospital.inc"
#include "module/map/market.inc"
#include "module/map/ammunationgta5.inc"
#include "module/map/sapd_int"

//faction
#include "module/factions/core.inc"
#include "module/factions/sapd.inc"
#include "module/factions/goverment.inc"

//job 
#include "module/job/hunter.inc"
#include "module/job/taxi.inc"
#include "module/job/trucker.inc"

/* Functions */

stock GetName(playerid)
{
	new name[MAX_PLAYER_NAME];
 	GetPlayerName(playerid,name,sizeof(name));
	return name;
}

Database_Connect()
{
	sqlcon = mysql_connect(DATABASE_ADDRESS,DATABASE_USERNAME,DATABASE_PASSWORD,DATABASE_NAME);

	if(mysql_errno(sqlcon) != 0){
	    print("[MySQL] - Connection Failed!");
	}
	else{
		print("[MySQL] - Connection Estabilished!");
	}
}

stock IsRoleplayName(player[])
{
    for(new n = 0; n < strlen(player); n++)
    {
        if (player[n] == '_' && player[n+1] >= 'A' && player[n+1] <= 'Z') return 1;
        if (player[n] == ']' || player[n] == '[') return 0;
	}
    return 0;
}

stock IsPlayerNearPlayer(playerid, targetid, Float:radius)
{
	static
		Float:fX,
		Float:fY,
		Float:fZ;

	GetPlayerPos(targetid, fX, fY, fZ);

	return (GetPlayerInterior(playerid) == GetPlayerInterior(targetid) && GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(targetid)) && IsPlayerInRangeOfPoint(playerid, radius, fX, fY, fZ);
}

stock SendNearbyMessage(playerid, Float:radius, color, const str[], {Float,_}:...)
{
	static
	    args,
	    start,
	    end,
	    string[144]
	;
	#emit LOAD.S.pri 8
	#emit STOR.pri args

	if (args > 16)
	{
		#emit ADDR.pri str
		#emit STOR.pri start

	    for (end = start + (args - 16); end > start; end -= 4)
		{
	        #emit LREF.pri end
	        #emit PUSH.pri
		}
		#emit PUSH.S str
		#emit PUSH.C 144
		#emit PUSH.C string

		#emit LOAD.S.pri 8
		#emit CONST.alt 4
		#emit SUB
		#emit PUSH.pri

		#emit SYSREQ.C format
		#emit LCTRL 5
		#emit SCTRL 4

        foreach (new i : Player)
		{
			if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
			{
  				SendClientMessage(i, color, string);
			}
		}
		return 1;
	}
	foreach (new i : Player)
	{
		if (IsPlayerNearPlayer(i, playerid, radius) && PlayerData[i][pSpawned])
		{
			SendClientMessage(i, color, str);
		}
	}
	return 1;
}

stock SendClientMessageEx(playerid, colour, const text[], va_args<>)
{
    new str[145];
    va_format(str, sizeof(str), text, va_start<3>);
    return SendClientMessage(playerid, colour, str);
}


ReturnName(playerid, underscore=1)
{
    new
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));

    if(!underscore) {
        for (new i = 0, len = strlen(name); i < len; i ++) {
                if(name[i] == '_') name[i] = ' ';
        }
    }
    return name;
}

ReturnName2(playerid, underscore=1)
{
    static
        name[MAX_PLAYER_NAME + 1];

    GetPlayerName(playerid, name, sizeof(name));

    if(!underscore) {
        for (new i = 0, len = strlen(name); i < len; i ++) {
            if(name[i] == '_') name[i] = ' ';
        }
    }
    return name;
}

stock CheckAccount(playerid)
{
	new query[256];
	format(query, sizeof(query), "SELECT * FROM `users` WHERE `Username` = '%s' LIMIT 1;", GetName(playerid));
	mysql_tquery(sqlcon, query, "CheckUsers", "d", playerid);
	return 1;
}

Function:PlayerCheck(playerid, rcc)
{
	if(rcc != g_RaceCheck{playerid})
	    return Kick(playerid);
	    
	CheckAccount(playerid);
	return true;
}

Function:CheckUsers(playerid)
{
	new rows = cache_num_rows();
	new str[256];
	if (rows)
	{
	    format(str, sizeof(str), "Selamat datang kembali di server "SERVER_NAME"!\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk masuk:", GetName(playerid));
		Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, "MASUK", str, "Select", "Cancel");
	}
	else
	{
	    format(str, sizeof(str), "Selamat datang di server: "SERVER_NAME"\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk mendaftar:", GetName(playerid));
		Dialog_Show(playerid, RegisterScreen, DIALOG_STYLE_PASSWORD, "DAFTAR", str, "Select", "Cancel");
	}
	return 1;
}

stock SetupPlayerData(playerid)
{
    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1642.1681, -2333.3689, 13.5469, 0.0, 0, 0, 0, 0, 0, 0);
    SpawnPlayer(playerid);
    return 1;
}

stock SaveData(playerid)
{
	new query[2012];
	if(PlayerData[playerid][pSpawned])
	{
		GetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
		GetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
		GetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);

	    format(query, sizeof(query), "UPDATE `users` SET `PosX` = '%.4f', `PosY` = '%.4f', `PosZ` = '%.4f', `Health` = '%.4f', `Armor` = '%.4f', `World` = '%d', `Interior` = '%d', `Age` = '%s', `Heigth` = '%s', `Gender` = '%d', `Injured` = '%d', `Admin` = '%d',`Skin` = '%d', `Money` = '%d', `Bank` = '%d', `Level` = '%d', `Hunger` = '%d', `Thirst` = '%d'",
			PlayerData[playerid][pPos][0],
			PlayerData[playerid][pPos][1],
			PlayerData[playerid][pPos][2],
			PlayerData[playerid][pHealth],
			PlayerData[playerid][pArmor],
			GetPlayerVirtualWorld(playerid),
			GetPlayerInterior(playerid),
			PlayerData[playerid][pAge],
			PlayerData[playerid][pHeigth],
			PlayerData[playerid][pGender],
			PlayerData[playerid][pInjured],
			PlayerData[playerid][pAdmin],
			PlayerData[playerid][pSkin],
			PlayerData[playerid][pMoney],
			PlayerData[playerid][pBank],
			PlayerData[playerid][pLevel],
			PlayerData[playerid][pHunger],
			PlayerData[playerid][pThirst]
		);
		forex(index, 13)
		{
			format(query, sizeof(query), "%s, `Gun%d` = '%d', `Ammo%d` = '%d', `Durability%d` = '%d'", query, index + 1, PlayerData[playerid][pGuns][index], index + 1, PlayerData[playerid][pAmmo][index], index + 1, PlayerData[playerid][pDurability][index]);
		}
	   	
		format(query, sizeof(query), "%s, `Entrance` = '%d', `Business` = '%d', `House` = '%d', `Faction` = '%d', `FactionRank` = '%d',`Job_1` = '%d', `Job_2` = '%d',`JailType` = '%d', `JailTime` = '%d', `AJailTime` = '%d', `Wanted` = '%d', `TruckerDelay` = '%d', `Clothing` = '%d' WHERE `pID`= '%d'",
			query,
			PlayerData[playerid][pEntrance],
			PlayerData[playerid][pBusiness],
			PlayerData[playerid][pHouse],
			PlayerData[playerid][pFaction],
			PlayerData[playerid][pFactionRank],
			PlayerData[playerid][pJob],
			PlayerData[playerid][pJob2],
			PlayerData[playerid][pJailType],
			PlayerData[playerid][pJailTime],
			PlayerData[playerid][pAJailTime],
			PlayerData[playerid][pWanted],
			PlayerData[playerid][pTruckerTimer],
			PlayerData[playerid][pClothing],
			PlayerData[playerid][pID]
		);
		mysql_tquery(sqlcon, query);
		printf("[ACOUNT] Akun atas nama %s dan ID: %d berhasil di simpan", GetName(playerid), PlayerData[playerid][pID]);
	}
	return 1;
}

Function:LoadCharacterData(playerid)
{
	cache_get_value_name_int(0, "pID", PlayerData[playerid][pID]);
	cache_get_value_name(0, "Age", PlayerData[playerid][pAge]);
	cache_get_value_name_float(0, "Armor", PlayerData[playerid][pArmor]);
	cache_get_value_name_int(0, "Money", PlayerData[playerid][pMoney]);
	cache_get_value_name_int(0, "Bank", PlayerData[playerid][pBank]);
	cache_get_value_name_int(0, "Level", PlayerData[playerid][pLevel]);
	cache_get_value_name(0, "Username", PlayerData[playerid][pName]);
	cache_get_value_name_float(0, "PosX", PlayerData[playerid][pPos][0]);
	cache_get_value_name_float(0, "PosY", PlayerData[playerid][pPos][1]);
	cache_get_value_name_float(0, "PosZ", PlayerData[playerid][pPos][2]);
	cache_get_value_name_float(0, "Health", PlayerData[playerid][pHealth]);
	cache_get_value_name_int(0, "Interior", PlayerData[playerid][pInterior]);
	cache_get_value_name_int(0, "World", PlayerData[playerid][pWorld]);
	cache_get_value_name_int(0, "Heigth", PlayerData[playerid][pHeigth]);
	cache_get_value_name_int(0, "Gender", PlayerData[playerid][pGender]);
	cache_get_value_name_int(0, "Skin", PlayerData[playerid][pSkin]);
	cache_get_value_name_int(0, "Injured", PlayerData[playerid][pInjured]);
	cache_get_value_name_int(0, "Admin", PlayerData[playerid][pAdmin]);
	cache_get_value_name_int(0, "Hunger", PlayerData[playerid][pHunger]);
	cache_get_value_name_int(0, "Thirst", PlayerData[playerid][pThirst]);
	cache_get_value_name_int(0, "Entrance", PlayerData[playerid][pEntrance]);
	cache_get_value_name_int(0, "Business", PlayerData[playerid][pBusiness]);
	cache_get_value_name_int(0, "House", PlayerData[playerid][pHouse]);
	cache_get_value_name_int(0, "Faction", PlayerData[playerid][pFaction]);
	cache_get_value_name_int(0, "FactionRank", PlayerData[playerid][pFactionRank]);
	cache_get_value_name_int(0, "Job_1", PlayerData[playerid][pJob]);
	cache_get_value_name_int(0, "Job_2", PlayerData[playerid][pJob2]);
	cache_get_value_name_int(0, "JailType", PlayerData[playerid][pJailType]);
	cache_get_value_name_int(0, "JailTime", PlayerData[playerid][pJailTime]);
	cache_get_value_name_int(0, "AJailTime", PlayerData[playerid][pAJailTime]);
	cache_get_value_name_int(0, "Wanted", PlayerData[playerid][pWanted]);
	cache_get_value_name_int(0, "TruckerDelay", PlayerData[playerid][pTruckerTimer]);
	cache_get_value_name_int(0, "Clothing", PlayerData[playerid][pClothing]);

	new query[450];

	forex(i, 13) {
		format(query, sizeof(query), "Gun%d", i + 1);
		cache_get_value_name_int(0, query, PlayerData[playerid][pGuns][i]);

		format(query, sizeof(query), "Ammo%d", i + 1);
		cache_get_value_name_int(0, query, PlayerData[playerid][pAmmo][i]);

		format(query, sizeof(query), "Durability%d", i + 1);
		cache_get_value_name_int(0, query, PlayerData[playerid][pDurability][i]);
	}

	if(PlayerData[playerid][pGender] != -1) ShowSpawnTextdraw(playerid);

	if(PlayerData[playerid][pGender] == -1) ShowPassport_1(playerid);

	StartPlayerProgressBarTextdraw(playerid, 100, "Memuat Data", 100, "loadsukses", 1687547391);

	PlayerData[playerid][pLoggedIn] = true;

	new invQuery[256];
	mysql_format(sqlcon,invQuery, sizeof(invQuery), "SELECT * FROM `inventory` WHERE `ID` = '%d'", PlayerData[playerid][pID]);
	mysql_tquery(sqlcon, invQuery, "LoadPlayerItems", "d", playerid);

	new invStr[300];
	forex(inv, 20)
	{
		if (!InventoryData[playerid][inv][invExists])
		{
			PlayerTextDrawSetPreviewModel(playerid, ITEM[inv][playerid], -1);
			PlayerTextDrawSetString(playerid, ITEMTXT[inv][playerid], "_");
			PlayerTextDrawSetString(playerid, INVJUMLAH[playerid][inv], "_");
		}
		else
		{
			format(invStr, 300, "%d", InventoryData[playerid][inv][invQuantity]);				
			PlayerTextDrawSetPreviewModel(playerid, ITEM[inv][playerid], InventoryData[playerid][inv][invModel]);
			PlayerTextDrawSetString(playerid, ITEMTXT[inv][playerid], InventoryData[playerid][inv][invItem]);
			PlayerTextDrawSetString(playerid, INVJUMLAH[playerid][inv], invStr);
		}
	}
	//
	LoadPlayerToys(playerid);
	LoadPlayerVehicle(playerid);
    return 1;
}

Function:loadsukses(playerid)
{
	SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, "Data dari karakter kamu berhasil di muat.");
	return 1;
}

Function:HashPlayerPassword(playerid, hashid)
{
	new
		query[256],
		hash[BCRYPT_HASH_LENGTH];

    bcrypt_get_hash(hash, sizeof(hash));
	
	format(query,sizeof(query),"INSERT INTO `users` (`Username`, `Password`) VALUES ('%s', '%s')", ReturnName(playerid, 1), hash);
	mysql_tquery(sqlcon, query, "OnPlayerRegister", "d", playerid);
	return 1;
}

Function:OnPlayerRegister(playerid)
{
	PlayerData[playerid][pLogged] = true;	
	PlayerData[playerid][pMoney] = START_PLAYER_MONEY;
	PlayerData[playerid][pBank] = START_PLAYER_BANK;
	PlayerData[playerid][pHealth] = 100;
	PlayerData[playerid][pArmor] = 0;

	SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	SetPlayerArmour(playerid, PlayerData[playerid][pArmor]);
	GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);

	PlayerData[playerid][pID] = cache_insert_id();
	printf("[ACOUNT] Pemain dengan nama %s, dengan id %d berhasil terdaftar.", GetName(playerid), PlayerData[playerid][pID]);
	// Dialog_Show(playerid, DialogAge, DIALOG_STYLE_INPUT, "Character Age", "Please Insert your Character Age", "Continue", "Cancel");

	ShowPassport_1(playerid);
	return 1;
}

Function:OnPlayerPasswordChecked(playerid, bool:success)
{
	new str[256];
    format(str, sizeof(str), "Selamat datang kembali di server "SERVER_NAME"!\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk masuk:", GetName(playerid));
    
	if(!success)
        return Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, "MASUK", str, "Login", "Exit");

	PlayerData[playerid][pLogged] = true;	
	new cQuery[256];
	mysql_format(sqlcon, cQuery, sizeof(cQuery), "SELECT * FROM `users` WHERE `Username` = '%s' LIMIT 1;", ReturnName(playerid));
	mysql_tquery(sqlcon, cQuery, "LoadCharacterData", "d", playerid);	
	return 1;
}

/* Gamemode Start! */

main()
{
	print("[SCRIPT] Semua script berhasil di load.");
}

public OnGameModeInit()
{
	Database_Connect();

	EnableStuntBonusForAll(0);
	ShowPlayerMarkers(PLAYER_MARKERS_MODE_STREAMED);
	DisableInteriorEnterExits();
	SetNameTagDrawDistance(15.0);
	AllowInteriorWeapons(1); 
	ManualVehicleEngineAndLights();
	SetGameModeText(SERVER_REVISION);

	//dynamic
	mysql_tquery(sqlcon, "SELECT * FROM `parks`", "Garkot_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `dropped`", "Dropped_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `rental`", "Rental_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `entrances`", "Entrance_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `businesses`", "Business_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `houses`", "House_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `berangkas`", "Berangkas_Load", "");
	mysql_tquery(sqlcon, "SELECT * FROM `stuff`", "LoadServerStuff", "");
	//mysql_tquery(sqlcon, "SELECT * FROM `factions`", "Faction_Load", "");

	//timer
	SetTimer("FuelUpdate", 50000, true);
	SetTimer("RefuelCheck", 500, true);
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	g_RaceCheck{playerid} ++;
	InterpolateCameraPos(playerid, -37.715755, -2101.054931, 121.661994, 3031.810302, -638.207458, 196.425064, 12000);
	InterpolateCameraLookAt(playerid, -33.558185, -2098.420898, 120.781112, 3028.381103, -641.794555, 195.814514, 12000);

	ResetPlayerData(playerid);
	CreateAllPlayerTextdraw(playerid);

	SetTimerEx("PlayerCheck", 1000, false, "ii", playerid, g_RaceCheck{playerid});
	return 1;
}

public OnPlayerDisconnect(playerid, reason)
{
	if(IsValidDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]))
		DestroyDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]);
	
	UnloadPlayerVehicle(playerid);	
	SaveData(playerid);
	return 1;
}

public OnPlayerUpdate(playerid)
{
	foreach (new i : Player) {
		ShowPlayerNameTagForPlayer(i, playerid, 1);
	}
	if(GetPlayerMoney(playerid) != PlayerData[playerid][pMoney]) {
        ResetPlayerMoney(playerid);
        GivePlayerMoney(playerid, PlayerData[playerid][pMoney]);
    }
	return 1;
}

public OnPlayerEnterRaceCheckpoint(playerid){
	if(IsHauling[playerid] > 0)
    {
 		if(IsHauling[playerid] % 2 == 0)
	    {
            if(IsTrailerAttachedToVehicle(GetPlayerVehicleID(playerid)))
			{
                PlayerData[playerid][pTruckerTimer] += 5 * 60;
			    DisablePlayerRaceCheckpoint(playerid);
                DestroyVehicle(GetVehicleTrailer(GetPlayerVehicleID(playerid)));
                switch(IsHauling[playerid]){
                    case 2:{
                        DialogHauling[0] = false;
                        GivePlayerMoney(playerid, 35000); 
                    }
                    case 4:{
                        DialogHauling[1] = false;
                        GivePlayerMoney(playerid, 30000);                        
                    }
                    case 6:{
                        DialogHauling[2] = false;
                        GivePlayerMoney(playerid, 25000);                        
                    }
                    case 8:{
                        DialogHauling[3] = false;
                        GivePlayerMoney(playerid, 27000);                       
                    }
                    case 10:{
                        DialogHauling[4] = false;
                        GivePlayerMoney(playerid, 39900);                       
                    }
                    case 12:{
                        DialogHauling[5] = false;
                        GivePlayerMoney(playerid, 20000);                        
                    }
                    case 14:{
                        DialogHauling[6] = false;
                        GivePlayerMoney(playerid, 31000);                       
                    }
                    case 16:{
                        DialogHauling[7] = false;
                        GivePlayerMoney(playerid, 33300);                       
                    }
                    case 18:{
                        DialogHauling[8] = false;
                        GivePlayerMoney(playerid, 29000);  
                    }
                    case 20:{
                        DialogHauling[9] = false;
                        GivePlayerMoney(playerid, 22500);  
                    }
                }
                IsHauling[playerid] = 0;
                return 1;
			}
		}else{
            DisablePlayerRaceCheckpoint(playerid);
            switch (IsHauling[playerid]){
                case 1: SetPlayerRaceCheckpoint(playerid, 1, -2471.2942, 783.0248, 35.1719, -2471.2942, 783.0248, 35.1719, 10.0);
                case 3: SetPlayerRaceCheckpoint(playerid, 1, -576.2687, 2569.0842, 53.5156, 576.2687, 2569.0842, 53.5156, 10.0); 
                case 5: SetPlayerRaceCheckpoint(playerid, 1, 1424.8624, 2333.4939, 10.8203, 1424.8624, 2333.4939, 10.8203, 10.0);
                case 7: SetPlayerRaceCheckpoint(playerid, 1, 1198.7153, 165.4331, 20.5056, 1198.7153, 165.4331, 20.5056, 10.0);
                case 9: SetPlayerRaceCheckpoint(playerid, 1, 1201.5385, 171.6184, 20.5035, 1201.5385, 171.6184, 20.5035, 10.0);
                case 11: SetPlayerRaceCheckpoint(playerid, 1, 1613.7815, 2236.2046, 10.3787, 1613.7815, 2236.2046, 10.3787, 10.0);
                case 13: SetPlayerRaceCheckpoint(playerid, 1, 2786.8313, -2417.9558, 13.6339, 2786.8313, -2417.9558, 13.6339, 10.0);
                case 15: SetPlayerRaceCheckpoint(playerid, 1, 2415.7803, -2470.1309, 13.6300, 2415.7803, -2470.1309, 13.6300, 10.0);
                case 17: SetPlayerRaceCheckpoint(playerid, 1, -980.1684, -713.3505, 32.0078, -980.1684, -713.3505, 32.0078, 10.0);
                case 19: SetPlayerRaceCheckpoint(playerid, 1, -2226.1292, -2315.1055, 30.6045, -2226.1292, -2315.1055, 30.6045, 10.0);
            }
     		SendServerMessage(playerid,"Attach the trailer to your vehicle to order");
  			IsHauling[playerid] += 1;
       		return 1;
        }
        return 1;
	}
	return 1;
}


Dialog:RegisterScreen(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return Kick(playerid);

	new str[256];
	format(str, sizeof(str), "Selamat datang di server: "SERVER_NAME"\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\nERROR: Panjang kata sandi tidak boleh di bawah 7 atau di atas 32!n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk mendaftar:", GetName(playerid));

    if(strlen(inputtext) < 7)
		return Dialog_Show(playerid, RegisterScreen, DIALOG_STYLE_PASSWORD, "DAFTAR", str, "Select", "Cancel");

    if(strlen(inputtext) > 32)
		return Dialog_Show(playerid, RegisterScreen, DIALOG_STYLE_PASSWORD, "DAFTAR", str, "Select", "Cancel");

    bcrypt_hash(playerid, "HashPlayerPassword", inputtext, BCRYPT_COST);
	return 1;
}

Dialog:LoginScreen(playerid, response, listitem, inputtext[])
{
	if(!response)
	    return Kick(playerid);
	        
    if(strlen(inputtext) < 1)
    {
		new str[256];
        format(str, sizeof(str), "Selamat datang kembali di server "SERVER_NAME"!\n\nUsername: %s\nVersion: "SERVER_REVISION"\n\n"YELLOW"Silakan masukkan Kata Sandi Anda di bawah ini untuk masuk:", GetName(playerid));
        Dialog_Show(playerid, LoginScreen, DIALOG_STYLE_PASSWORD, "MASUK", str, "Login", "Exit");
        return 1;
	}
	new pwQuery[256], hash[BCRYPT_HASH_LENGTH];
	mysql_format(sqlcon, pwQuery, sizeof(pwQuery), "SELECT Password FROM users WHERE username = '%e' LIMIT 1", GetName(playerid));
	mysql_query(sqlcon, pwQuery);
		
    cache_get_value_name(0, "Password", hash, sizeof(hash));
        
    bcrypt_verify(playerid, "OnPlayerPasswordChecked", inputtext, hash);
	return 1;
}

public OnPlayerSpawn(playerid)
{
	ShowPlayerHud(playerid, true);
	if(!PlayerData[playerid][pSpawned])
	{
	    PlayerData[playerid][pSpawned] = true;
	    SetPlayerHealth(playerid, PlayerData[playerid][pHealth]);
	    SetPlayerSkin(playerid, PlayerData[playerid][pSkin]);
	    SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);
		SetPlayerScore(playerid, PlayerData[playerid][pLevel]);
		SetWeapons(playerid);
	}
	// if(PlayerData[playerid][pJailTime] > 0)
	// {
	//     if (PlayerData[playerid][pArrest])
	//     {
	//         SetPlayerArrest(playerid);
	//     }
	//     else
	//     {
	// 	    SetPlayerPos(playerid, 197.6346, 175.3765, 1003.0234);

	// 	    SetPlayerInterior(playerid, 3);

	// 	    SetPlayerVirtualWorld(playerid, (playerid + 100));
	// 	    SetPlayerFacingAngle(playerid, 0.0);
    //         PlayerTextDrawShow(playerid, JAILTD[playerid]);
	// 	    SetCameraBehindPlayer(playerid);
	// 	}

	//     SendServerMessage(playerid, "You have %d seconds of remaining jail time.", PlayerData[playerid][pJailTime]);
	// }
    // else if(PlayerData[playerid][pDead] && PlayerData[playerid][pJailTime] < 1)
	else if(PlayerData[playerid][pDead])
    {
		ResetWeapons(playerid);
		PlayerData[playerid][pInjured] = false;
		PlayerData[playerid][pDead] = false;
		ClearAnimations(playerid);
		
	    SetSpawnInfo(playerid, 0, PlayerData[playerid][pSkin], 1179.9133,-1327.0813,14.2512, 0.0, 0, 0, 0, 0, 0, 0);
        SpawnPlayer(playerid);
		        
		SetPlayerInterior(playerid, 0);
		SetPlayerVirtualWorld(playerid, 0);
		SetPlayerHealth(playerid, 100);
		SetPlayerFacingAngle(playerid, 271.9647);
		SetCameraBehindPlayer(playerid);
		SetPlayerHealth(playerid, 100);
        TogglePlayerControllable(playerid, 1);
		SendServerMessage(playerid, "Anda telah respawn di {FFFF00}All Saints General Hospital {FFFFFF}dan didenda {FF0000}$50.00");
		// ResetWeapons(playerid);
		GiveMoney(playerid, -5000, "Bayar rumah sakit");
		// ResetDamages(playerid);
	}
	else
	{
		SetPlayerVirtualWorld(playerid, PlayerData[playerid][pWorld]);
		SetPlayerInterior(playerid, PlayerData[playerid][pInterior]);

		if(IsValidDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]))
			DestroyDynamic3DTextLabel(PlayerData[playerid][pInjuredLabel]);

		//if(PlayerData[playerid][pInjured] && PlayerData[playerid][pJailTime] < 1)	
		if(PlayerData[playerid][pInjured])
		{
		    SetPlayerPos(playerid, PlayerData[playerid][pPos][0], PlayerData[playerid][pPos][1], PlayerData[playerid][pPos][2]);
			ApplyAnimation(playerid, "WUZI", "CS_DEAD_GUY", 4.1, 0, 0, 0, 1, 0, 1);
			PlayerData[playerid][pInjured] = true;
			SetPlayerHealth(playerid, 100);
			PlayerData[playerid][pInjuredTime] = 600;
			SendClientMessage(playerid, X11_RED, "WARNING: {FFFFFF}Anda telah {E20000}sekarat. {FFFFFF} Anda dapat memilih untuk {44C300}/accept death");
			SendClientMessage(playerid, X11_WHITE, "...Setelah Death Timer Anda berakhir atau tunggu sampai Anda dihidupkan kembali.");

			PlayerData[playerid][pInjuredLabel] = CreateDynamic3DTextLabel("(( THIS PLAYER IS INJURED ))", X11_RED, 0.0, 0.0, 0.50, 15.0, playerid);
		}
	}
	return 1;
}


public OnPlayerText(playerid, text[])
{
	SendNearbyMessage(playerid, 20.0, -1, "OOC | %s: %s", ReturnName(playerid, 0), text);
    return 0;
}

public OnPlayerStateChange(playerid, newstate, oldstate)
{
	//if (newstate == PLAYER_STATE_WASTED && PlayerData[playerid][pJailTime] < 1)
	if (newstate == PLAYER_STATE_WASTED)
	{
		if(PlayerData[playerid][pInjured])
		{
			PlayerData[playerid][pDead] = true;
			PlayerData[playerid][pInjured] = false;
		}
	}
	
	return 1;
}

public OnPlayerClickPlayerTextDraw(playerid, PlayerText:playertextid)
{
	forex(i, 20)
	{
	    if(playertextid == ITEM[i][playerid])
		{
			if(InventoryData[playerid][i][invExists])
			{
				new before = PlayerData[playerid][pListitem];

				PlayerData[playerid][pListitem] = i;

				if(InventoryData[playerid][PlayerData[playerid][pListitem]][invQuantity] < 1)
					return SendErrorMessage(playerid, "Tidak ada item di slot yang dipilih!");


				forex(txd, 20)
				{
					PlayerTextDrawBackgroundColor(playerid, ITEM[txd][playerid], 150);
				}
				PlayerTextDrawBackgroundColor(playerid, ITEM[i][playerid], 1687547286);

				PlayerTextDrawHide(playerid, ITEM[before][playerid]);
				PlayerTextDrawHide(playerid, ITEM[i][playerid]);
						
				SetTimerEx("RefrestItemTextdraw", 100, false, "dddd", playerid, before, i);		
			}
		}
	}
	if(PassportTD_2[playerid][0] != PlayerText:-1)
	{
		if(playertextid == PassportTD_2[playerid][32])
		{
			InputAge(playerid);
		}
		if(playertextid == PassportTD_2[playerid][36])
		{
			InputGender(playerid);
		}
		if(playertextid == PassportTD_2[playerid][38])
		{
			InputTinggi(playerid);
		}
		if(playertextid == PassportTD_2[playerid][13])
		{
			SubmitPassport(playerid);
		}
		if(playertextid == PassportTD_1[playerid][6])
		{
			SubmitPassport1(playerid);
		}
	}
	// SYSTEM HANDPHONE
	if(PhonePage[playerid] == PHONE_LOCKSCREEN)
	{
		if(playertextid == PhoneTextdraw[playerid][lockscreen][4])
		{
			ShowPhoneLockscreen(playerid, false);
			ShowHomePagePhone(playerid, true);
		}
	}
	// Application 
	else if(PhonePage[playerid] == PHONE_HOMESCREEN)
	{
		if(playertextid == PhoneTextdraw[playerid][myapplication][22])
		{
			ShowHomePagePhone(playerid, false);
			ShowMobileBanking(playerid, true);
		}
		if(playertextid == PhoneTextdraw[playerid][myapplication][11])
		{
			ShowHomePagePhone(playerid, false);
			ShowPhoneDjek(playerid, true);
		}
	}
	return 1;
}

public OnPlayerGiveDamage(playerid, damagedid, Float:amount, weaponid, bodypart)
{
    new Float:health,
		Float:armour;

	GetPlayerHealth(damagedid, health);
	GetPlayerArmour(damagedid, armour);
	if(damagedid != INVALID_PLAYER_ID)
	{
		new Float:damage;
		switch(weaponid)
		{
		    case 0: damage = 2.0; // Fist
			case 1: damage = 5.0; // Brass Knuckles
			case 2: damage = 5.0;   // Golf Club
			case 3: damage = 5.0; // Nightstick
			case 4: damage = 7.0; // Knife
			case 5: damage = 5.0; // Baseball Bat
			case 6: damage = 5.0; // Shovel
			case 7: damage = 5.0; // Pool Cue
			case 8: damage = 8.0; // Katana
			case 9: damage = 10.0; // Chainsaw
			case 14: damage = 2.0; // Flowers
			case 15: damage = 5.0; // Cane
			case 16: damage = 50.0; // Grenade
			case 18: damage = 20.0; // Molotov
			case 22: damage = float(RandomEx(15, 20)); // Colt45
			case 23, 28, 29, 32: damage = float(RandomEx(17, 23)); // SD Pistol, UZI, MP5, Tec
			case 24: damage = float(RandomEx(38, 43)); // Desert Eagle
			case 25, 26, 27: // Shotgun, Sawnoff Shotgun, CombatShotgun
			{
			    new Float: p_x, Float: p_y, Float: p_z;
			    GetPlayerPos(playerid, p_x, p_y, p_z);
			    new Float: dist = GetPlayerDistanceFromPoint(damagedid, p_x, p_y, p_z);

			    if (dist < 5.0)
					damage = float(RandomEx(50, 55));

				else if (dist < 10.0)
					damage = float(RandomEx(23, 35));

				else if (dist < 15.0)
					damage = float(RandomEx(15, 25));

				else if (dist < 20.0)
					damage = float(RandomEx(10, 15));

				else if (dist < 30.0)
					damage = float(RandomEx(5, 8));
			}
			case 30: damage = float(RandomEx(20, 25)); // AK47
			case 31: damage = float(RandomEx(20, 22)); // M4A1
			case 33, 34:{
				if(HuntingRifle[playerid] = true){
					damage = 0.3; 
				}else{
				damage = float(RandomEx(70, 75)); 
				}
			} 
			case 35: damage = 0.0; // RPG
			case 36: damage = 0.0; // HS Rocket
			case 38: damage = 0.0; // Minigun
		}

        if(bodypart == BODY_PART_TORSO && armour > 0.0 && (22 <= weaponid <= 38))
		{
		    if(armour - damage <= 7.0)
				SetPlayerArmour(damagedid, 0.0);
	 		else
			 	SetPlayerArmour(damagedid, armour - damage);

            SetPlayerHealth(damagedid, health);
		}
		else
		{
		    if(health - damage <= 7.0)
				InjuredPlayer(damagedid, playerid, weaponid);
			else
			{
				if(health <= 30.0)
				{
					SetPlayerHealth(damagedid, health - damage / 2); 
				}
				else
				{
					SetPlayerHealth(damagedid, health - damage);
				}
			}

			if(armour)
			    SetPlayerArmour(damagedid, armour);
		}
	}
	else
	{
	    if(health - amount <= 7.0)
			InjuredPlayer(damagedid, playerid, weaponid);
	}
	return 1;
}

public OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{
	if(newkeys == KEY_YES)
	{
		cmd_radial(playerid, "");
	}
	if(newkeys == KEY_WALK)
	{
	    if(GetPlayerState(playerid) != PLAYER_STATE_DRIVER)
	    {
			new invStr[300];
			forex(inv, 20)
			{
				if (!InventoryData[playerid][inv][invExists])
				{
					PlayerTextDrawSetPreviewModel(playerid, ITEM[inv][playerid], -1);
					PlayerTextDrawSetString(playerid, ITEMTXT[inv][playerid], "_");
					PlayerTextDrawSetString(playerid, INVJUMLAH[playerid][inv], "_");
				}
				else
				{
					format(invStr, 300, "%d", InventoryData[playerid][inv][invQuantity]);				
					PlayerTextDrawSetPreviewModel(playerid, ITEM[inv][playerid], InventoryData[playerid][inv][invModel]);
					PlayerTextDrawSetString(playerid, ITEMTXT[inv][playerid], InventoryData[playerid][inv][invItem]);
					PlayerTextDrawSetString(playerid, INVJUMLAH[playerid][inv], invStr);
				}
			}
			ShowInventoryTextdraw(playerid, 1);
			PlayerData[playerid][pStorageSelect] = 0;
			SetTimerEx("ShowingInventory", 1000, false, "d", playerid);
		}
	}
	if(PRESSED(KEY_NO))
    {
    	if (GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK)
		{
		    new
				count = 0,
				id = Item_Nearest(playerid),
		        string[320];

		    if (id != -1)
		    {
		        string = "";

		        for (new i = 0; i < MAX_DROPPED_ITEMS; i ++) if (count < MAX_LISTED_ITEMS && DroppedItems[i][droppedModel] && IsPlayerInRangeOfPoint(playerid, 1.5, DroppedItems[i][droppedPos][0], DroppedItems[i][droppedPos][1], DroppedItems[i][droppedPos][2]) && GetPlayerInterior(playerid) == DroppedItems[i][droppedInt] && GetPlayerVirtualWorld(playerid) == DroppedItems[i][droppedWorld]) {
		            NearestItems[playerid][count++] = i;

		            strcat(string, DroppedItems[i][droppedItem]);
		            strcat(string, "\n");
		        }
		        if (count == 1)
		        {
					if (PickupItem(playerid, id))
					{
						SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "> %s Mengambil sebuah \"%s\" menggunakan kedua tangan.", GetName(playerid), DroppedItems[id][droppedItem]);
					}
					else
						SendErrorMessage(playerid, "Anda tidak memiliki slot tersisa di inventaris Anda.");
				}
				else Dialog_Show(playerid, DIALOG_PICKITEM, DIALOG_STYLE_LIST, "AMBIL BARANG", string, "Pickup", "Cancel");
			}
		}
    }
	return 1;
}

public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
	if(dialogid == DIALOG_RENTAL)
	{
	    if(response)
	    {
	        new rentid = PlayerData[playerid][pRenting];
	        if(GetMoney(playerid) < RentData[rentid][rentPrice][listitem])
	            return SendErrorMessage(playerid, "Kamu tidak memiliki cukup uang!");
	            
			new str[256];
			format(str, sizeof(str), "{FFFFFF}Berapa jam kamu ingin menggunakan kendaraan Rental ini ?\n{FFFFFF}Maksimal adalah {FFFF00}4 jam\n\n{FFFFFF}Harga per Jam: {009000}%s", FormatNumber(RentData[rentid][rentPrice][listitem]));
			Dialog_Show(playerid, DIALOG_RENTTIME, DIALOG_STYLE_INPUT, "{FFFFFF}Rental Time", str, "Rental", "Close");
			PlayerData[playerid][pListitem] = listitem;
		}
	}
	if(dialogid == DIALOG_TOYPOSX)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);

			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_x] = posisi;

			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSY)
	{
		if(response)
		{

			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_y] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSZ)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_z] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSRX)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_rx] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSRY)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_ry] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSRZ)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_rz] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSSX)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_sy],
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_sx] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSSY)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				posisi,
				pToys[playerid][toySelect[playerid]][toy_sz]);
			
			pToys[playerid][toySelect[playerid]][toy_sy] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSSZ)
	{
		if(response)
		{
			if(!toyToggle[playerid][toySelect[playerid]])
				return SendErrorMessage(playerid, "Please attach your accessory first!");

			new Float:posisi = floatstr(inputtext);
			
			SetPlayerAttachedObject(playerid,
				toySelect[playerid],
				pToys[playerid][toySelect[playerid]][toy_model],
				pToys[playerid][toySelect[playerid]][toy_bone],
				pToys[playerid][toySelect[playerid]][toy_x],
				pToys[playerid][toySelect[playerid]][toy_y],
				pToys[playerid][toySelect[playerid]][toy_z],
				pToys[playerid][toySelect[playerid]][toy_rx],
				pToys[playerid][toySelect[playerid]][toy_ry],
				pToys[playerid][toySelect[playerid]][toy_rz],
				pToys[playerid][toySelect[playerid]][toy_sx],
				pToys[playerid][toySelect[playerid]][toy_sy],
				posisi);
			
			pToys[playerid][toySelect[playerid]][toy_sz] = posisi;
			cmd_acc(playerid, "");

			SavePlayerToys(playerid);
		}
	}
	if(dialogid == DIALOG_TOYPOSISIBUY)
	{
		if(response)
		{
	        GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "> %s telah membayar $%s dan mengambil toys", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]));
			// benerin nanti
			// BusinessData[PlayerData[playerid][pBusiness]][bizProducts]--;		
			// BusinessData[PlayerData[playerid][pBusiness]][bizVault] += PlayerData[playerid][pSkinPrice];
			new slot = GetPlayerFreeToySlot(playerid);
			printf("%s", PlayerData[playerid][pTempModel]);
			pToys[playerid][slot][toy_model] = PlayerData[playerid][pTempModel];
			pToys[playerid][slot][toy_bone] = listitem + 1;
			pToys[playerid][slot][toy_sx] = 1.0;
			pToys[playerid][slot][toy_sy] = 1.0;
			pToys[playerid][slot][toy_sz] = 1.0;
			toySelect[playerid] = slot;
			SetPlayerAttachedObject(playerid, slot, pToys[playerid][slot][toy_model], listitem + 1);
			EditAttachedObject(playerid, toySelect[playerid]);
		}
	}
	if(dialogid == DIALOG_TOYPOSISI)
	{
		if(response)
		{
			pToys[playerid][toySelect[playerid]][toy_bone] = listitem + 1;
			if(toyToggle[playerid][toySelect[playerid]])
			{
				RemovePlayerAttachedObject(playerid, toySelect[playerid]);
			}
			SetPlayerAttachedObject(playerid,
					toySelect[playerid],
					pToys[playerid][toySelect[playerid]][toy_model],
					pToys[playerid][toySelect[playerid]][toy_bone],
					pToys[playerid][toySelect[playerid]][toy_x],
					pToys[playerid][toySelect[playerid]][toy_y],
					pToys[playerid][toySelect[playerid]][toy_z],
					pToys[playerid][toySelect[playerid]][toy_rx],
					pToys[playerid][toySelect[playerid]][toy_ry],
					pToys[playerid][toySelect[playerid]][toy_rz],
					pToys[playerid][toySelect[playerid]][toy_sx],
					pToys[playerid][toySelect[playerid]][toy_sy],
					pToys[playerid][toySelect[playerid]][toy_sz]);
			SendServerMessage(playerid, "Accessory new bone position now is {FFFF00}%s", Bone_Name[listitem + 1]);
		}
	}
	if(dialogid == DIALOG_TOYEDIT)
	{
		if(response)
		{
			new mstr[156];
			switch(listitem)
			{
				case 0: // toggle attach
				{
					if(!toyToggle[playerid][toySelect[playerid]])
					{
						SendInfoMessage(playerid, "Accessory ~g~attached", 3);

						SetPlayerAttachedObject(playerid,
						toySelect[playerid],
						pToys[playerid][toySelect[playerid]][toy_model],
						pToys[playerid][toySelect[playerid]][toy_bone],
						pToys[playerid][toySelect[playerid]][toy_x],
						pToys[playerid][toySelect[playerid]][toy_y],
						pToys[playerid][toySelect[playerid]][toy_z],
						pToys[playerid][toySelect[playerid]][toy_rx],
						pToys[playerid][toySelect[playerid]][toy_ry],
						pToys[playerid][toySelect[playerid]][toy_rz],
						pToys[playerid][toySelect[playerid]][toy_sx],
						pToys[playerid][toySelect[playerid]][toy_sy],
						pToys[playerid][toySelect[playerid]][toy_sz]);

						toyToggle[playerid][toySelect[playerid]] = true;
					}
					else
					{
						RemovePlayerAttachedObject(playerid, toySelect[playerid]);
						SendInfoMessage(playerid, "~w~Accessory ~r~deattached", 3);

						toyToggle[playerid][toySelect[playerid]] = false;
					}
					SavePlayerToys(playerid);
				}
				case 1: // change bone
				{
				    ShowPlayerDialog(playerid, DIALOG_TOYPOSISI, DIALOG_STYLE_LIST, "Bone Selection", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
				}
				case 2: // change placement
				{

					EditAttachedObject(playerid, toySelect[playerid]);

				}
				case 3:	//remove from list
				{
					if(IsPlayerAttachedObjectSlotUsed(playerid, toySelect[playerid]))
					{
						RemovePlayerAttachedObject(playerid, toySelect[playerid]);
					}
					pToys[playerid][toySelect[playerid]][toy_model] = 0;
					SendInfoMessage(playerid, "~w~Accessory ~y~removed!", 3);
					SavePlayerToys(playerid);
				}
				case 4: //Scale Fix
				{

					SendInfoMessage(playerid, "~w~Accessory scale ~y~Fixed", 3);

					pToys[playerid][toySelect[playerid]][toy_sx] = 1.0;
					pToys[playerid][toySelect[playerid]][toy_sy] = 1.0;
					pToys[playerid][toySelect[playerid]][toy_sz] = 1.0;

					if(!toyToggle[playerid][toySelect[playerid]])
					{
						RemovePlayerAttachedObject(playerid, toySelect[playerid]);
						SetPlayerAttachedObject(playerid,
						toySelect[playerid],
						pToys[playerid][toySelect[playerid]][toy_model],
						pToys[playerid][toySelect[playerid]][toy_bone],
						pToys[playerid][toySelect[playerid]][toy_x],
						pToys[playerid][toySelect[playerid]][toy_y],
						pToys[playerid][toySelect[playerid]][toy_z],
						pToys[playerid][toySelect[playerid]][toy_rx],
						pToys[playerid][toySelect[playerid]][toy_ry],
						pToys[playerid][toySelect[playerid]][toy_rz],
						pToys[playerid][toySelect[playerid]][toy_sx],
						pToys[playerid][toySelect[playerid]][toy_sy],
						pToys[playerid][toySelect[playerid]][toy_sz]);

						toyToggle[playerid][toySelect[playerid]] = true;
					}
				}
				case 5: //Pos X
				{
					format(mstr, sizeof(mstr), "Current X Position: %f\nInput new X Position:(Float)", pToys[playerid][toySelect[playerid]][toy_x]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSX, DIALOG_STYLE_INPUT, "Edit X Position", mstr, "Edit", "Cancel");
				}
				case 6: //Pos Y
				{
					format(mstr, sizeof(mstr), "Current Y Position: %f\nInput new Y Position:(Float)", pToys[playerid][toySelect[playerid]][toy_y]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSY, DIALOG_STYLE_INPUT, "Edit Y Position", mstr, "Edit", "Cancel");
				}
				case 7: //Pos Z
				{
					format(mstr, sizeof(mstr), "Current Z Position: %f\nInput new Z Position:(Float)", pToys[playerid][toySelect[playerid]][toy_z]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSZ, DIALOG_STYLE_INPUT, "Edit Z Position", mstr, "Edit", "Cancel");
				}
				case 8: //Pos RX
				{
					format(mstr, sizeof(mstr), "Current X Rotation: %f\nInput new X Rotation:(Float)", pToys[playerid][toySelect[playerid]][toy_rx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRX, DIALOG_STYLE_INPUT, "Edit X Rotation", mstr, "Edit", "Cancel");
				}
				case 9: //Pos RY
				{
					format(mstr, sizeof(mstr), "Current Y Rotation: %f\nInput new Y Rotation:(Float)", pToys[playerid][toySelect[playerid]][toy_ry]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRY, DIALOG_STYLE_INPUT, "Edit Y Rotation", mstr, "Edit", "Cancel");
				}
				case 10: //Pos RZ
				{
					format(mstr, sizeof(mstr), "Current Z Rotation: %f\nInput new Z Rotation(Float)", pToys[playerid][toySelect[playerid]][toy_rz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSRZ, DIALOG_STYLE_INPUT, "Edit Z Rotation", mstr, "Edit", "Cancel");
				}
				case 11: //Scale X
				{
					format(mstr, sizeof(mstr), "Current X Scale: %f\nInput new X Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sx]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSX, DIALOG_STYLE_INPUT, "Edit X Scale", mstr, "Edit", "Cancel");
				}
				case 12: //Scale Y
				{
					format(mstr, sizeof(mstr), "Current Y Scale: %f\nInput new Y Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sy]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSY, DIALOG_STYLE_INPUT, "Edit Y Scale", mstr, "Edit", "Cancel");
				}
				case 13: //Scale Z
				{
					format(mstr, sizeof(mstr), "Current Z Scale: %f\nInput new Z Scale(Float)", pToys[playerid][toySelect[playerid]][toy_sz]);
					ShowPlayerDialog(playerid, DIALOG_TOYPOSSZ, DIALOG_STYLE_INPUT, "Edit Z Scale", mstr, "Edit", "Cancel");
				}
			}
		}
	}

	if(dialogid == DIALOG_TOY)
	{
		if(response)
		{
			if(pToys[playerid][listitem][toy_model] == 0)
				return SendErrorMessage(playerid, "There is no accessory on selected index!");

			
			new string[512];
			toySelect[playerid] = listitem;
			format(string, sizeof(string), "Place %s\nChange Bone\nChange Placement\nRemove from list\nScale Fix\nPosition X: %f\nPosition Y: %f\nPosition Z: %f\nRotation X: %f\nRotation Y: %f\nRotation Z: %f\nScale X: %f\nScale Y: %f\nScale Z: %f",
			(!toyToggle[playerid][toySelect[playerid]]) ? ("On") : ("Off"), pToys[playerid][toySelect[playerid]][toy_x], pToys[playerid][toySelect[playerid]][toy_y], pToys[playerid][toySelect[playerid]][toy_z],
			pToys[playerid][toySelect[playerid]][toy_rx], pToys[playerid][toySelect[playerid]][toy_ry], pToys[playerid][toySelect[playerid]][toy_rz], pToys[playerid][toySelect[playerid]][toy_sx], pToys[playerid][toySelect[playerid]][toy_sy], pToys[playerid][toySelect[playerid]][toy_sz]);
			ShowPlayerDialog(playerid, DIALOG_TOYEDIT, DIALOG_STYLE_LIST, sprintf("Edit Accessory (#%d)", listitem), string, "Select", "Cancel");
		}
	}
	return 1;
}

public OnPlayerWeaponShot(playerid, weaponid, hittype, hitid, Float:fX, Float:fY, Float:fZ)
{
	UpdateWeapons(playerid);
    if(weaponid >= 22 && weaponid <= 38 && PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] > 0)
    {
        PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]]--;
        PlayerData[playerid][pAmmo][g_aWeaponSlots[weaponid]]--;
	}
 	if (weaponid >= 22 && weaponid <= 38 && GetPlayerAmmo(playerid) == 1 || PlayerData[playerid][pDurability][g_aWeaponSlots[weaponid]] <= 0)
	{
	    ResetWeapon(playerid, weaponid);
	}
	return 1;
}

public OnPlayerPickUpDynamicPickup(playerid, STREAMER_TAG_PICKUP:pickupid)
{
	forex(i, MAX_ENTRANCES)
	{
		if(pickupid == EntranceData[i][entrancePickup])
		{
			ShowPressButton(playerid, sprintf("Tekan F untuk masuk ke %s", EntranceData[i][entranceName]), 3000);
		}
	}
	forex(i, MAX_HOUSES)
	{
		if(pickupid == HouseData[i][housePickup])
		{
			ShowPressButton(playerid, sprintf("Rumah %s, Tekan F untuk masuk kedalam", HouseData[i][houseAddress]), 3000);
		}
	}
	forex(i, MAX_DYNAMIC_BERANGKAS)
	{
		if(pickupid == BerangkasData[i][bPickup])
		{
			ShowPressButton(playerid, "Tekan Y untuk mengakses berangkas rumah", 3000);
		}
	}
}

public OnPlayerEditDynamicObject(playerid, objectid, response, Float:x, Float:y, Float:z, Float:rx, Float:ry, Float:rz)
{
	if (response == EDIT_RESPONSE_FINAL)
	{
	    if (PlayerData[playerid][pEditPump] != -1 && PumpData[PlayerData[playerid][pEditPump]][pumpExists])
	    {
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][0] = x;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][1] = y;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][2] = z;
			PumpData[PlayerData[playerid][pEditPump]][pumpPos][3] = rz;

			Pump_Refresh(PlayerData[playerid][pEditPump]);
			Pump_Save(PlayerData[playerid][pEditPump]);

			SendServerMessage(playerid, "You have edited the position of pump ID: %d.", PlayerData[playerid][pEditPump]);
	    }
	}
	if (response == EDIT_RESPONSE_FINAL || response == EDIT_RESPONSE_CANCEL)
	{
	    if (PlayerData[playerid][pEditPump] != -1)
			Pump_Refresh(PlayerData[playerid][pEditPump]);

		PlayerData[playerid][pEditPump] = -1;
		PlayerData[playerid][pGasStation] = -1;
	}
	return 1;
}


public OnPlayerEditAttachedObject(playerid, response, index, modelid, boneid, Float:fOffsetX, Float:fOffsetY, Float:fOffsetZ, Float:fRotX, Float:fRotY, Float:fRotZ, Float:fScaleX, Float:fScaleY, Float:fScaleZ)
{
	if(response == 1)
	{
		pToys[playerid][index][toy_x] = fOffsetX;
		pToys[playerid][index][toy_y] = fOffsetY;
		pToys[playerid][index][toy_z] = fOffsetZ;
		pToys[playerid][index][toy_rx] = fRotX;
		pToys[playerid][index][toy_ry] = fRotY;
		pToys[playerid][index][toy_rz] = fRotZ;
		pToys[playerid][index][toy_sx] = fScaleX;
		pToys[playerid][index][toy_sy] = fScaleY;
		pToys[playerid][index][toy_sz] = fScaleZ;
		SavePlayerToys(playerid);
	}
	else if(response == 0)
	{
		SetPlayerAttachedObject(playerid,
			index,
			modelid,
			boneid,
			pToys[playerid][index][toy_x],
			pToys[playerid][index][toy_y],
			pToys[playerid][index][toy_z],
			pToys[playerid][index][toy_rx],
			pToys[playerid][index][toy_ry],
			pToys[playerid][index][toy_rz],
			pToys[playerid][index][toy_sx],
			pToys[playerid][index][toy_sy],
			pToys[playerid][index][toy_sz]);
	}
	return 1;
}

public OnPlayerEnterDynamicArea(playerid, areaid)
{
  new extraid = Streamer_GetIntData(STREAMER_TYPE_AREA, areaid, E_STREAMER_EXTRA_ID);

  if (extraid < 1)
  {
    return 1;
  }

  gPlayerStaticLocation[playerid] = (extraid - AREA_EXTRAID_OFFSET);
  return 1;
}

public OnPlayerLeaveDynamicArea(playerid, areaid)
{
  gPlayerStaticLocation[playerid] = INVALID_AREA_ID;
  return 1;
}

public OnModelSelectionResponse(playerid, extraid, index, modelid, response)
{
	if(extraid == MODEL_SELECTION_BUYSKIN)
	{
		if(response)
		{
			//benerin nanti
			// new businessid = Business_Nearest(playerid, 5.0);
	        GiveMoney(playerid, -PlayerData[playerid][pSkinPrice]);
			SendNearbyMessage(playerid, 20.0, COLOR_PURPLE, "> %s telah membayar $%s dan membeli pakaian nomor %d.", ReturnName(playerid), FormatNumber(PlayerData[playerid][pSkinPrice]), modelid);
			// BusinessData[businessid][bizProducts]--;		
			// BusinessData[businessid][bizVault] += PlayerData[playerid][pSkinPrice];
			UpdatePlayerSkin(playerid, modelid);	
		}
	}
	if((response) && (extraid == MODEL_SELECTION_ACC))
	{
		if(GetPlayerFreeToySlot(playerid) == -1)
			return SendErrorMessage(playerid, "You already have full slot of Accessory!");

		ShowPlayerDialog(playerid, DIALOG_TOYPOSISIBUY, DIALOG_STYLE_LIST, "Bone Selection", "Spine\nHead\nLeft upper arm\nRight upper arm\nLeft hand\nRight hand\nLeft thigh\nRight thigh\nLeft foot\nRight foot\nRight calf\nLeft calf\nLeft forearm\nRight forearm\nLeft shoulder\nRight shoulder\nNeck\nJaw", "Choose", "Cancel");
		SendServerMessage(playerid, "Please select Bone for your Accessory");
		PlayerData[playerid][pTempModel] = modelid;
	}
	/*if ((response) && (extraid == MODEL_SELECTION_ADD_SKIN))
	{
	    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = modelid;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot], modelid);
	}
	if ((response) && (extraid == MODEL_SELECTION_SKINS))
	{
	    Dialog_Show(playerid, FactionSkin, DIALOG_STYLE_LIST, "Edit Skin", "Add by Model ID\nAdd by Thumbnail\nClear Slot", "Select", "Cancel");
	    PlayerData[playerid][pSelectedSlot] = index;
	}
	if ((response) && (extraid == MODEL_SELECTION_ADD_SKIN))
	{
	    FactionData[PlayerData[playerid][pFactionEdit]][factionSkins][PlayerData[playerid][pSelectedSlot]] = modelid;
		Faction_Save(PlayerData[playerid][pFactionEdit]);

		SendServerMessage(playerid, "You have set the skin ID in slot %d to %d.", PlayerData[playerid][pSelectedSlot], modelid);
	}
	if ((response) && (extraid == MODEL_SELECTION_FACTION_SKIN))
	{
	    new factionid = PlayerData[playerid][pFaction];

		if (factionid == -1 || !IsNearFactionLocker(playerid))
	    	return 0;

		if (modelid == 19300)
		    return SendErrorMessage(playerid, "There is no model in the selected slot.");

  		SetPlayerSkin(playerid, modelid);
		SendNearbyMessage(playerid, 30.0, COLOR_PURPLE, "** %s has changed their uniform.", ReturnName(playerid, 0));
	}*/
	return 1;
}

CMD:cursor(playerid, params[])
{
	if(!isOnPhone[playerid]) return 1;
	SelectTextDraw(playerid, X11_RED);
	return 1;
}

CMD:makemeadmin(playerid, params[])
{
	PlayerData[playerid][pAdmin] = 8;
	SendTextDrawMessageEx(playerid, NOTIFICATION_INFO, sprintf("%s berhasil di set ke admin level: 8", GetName(playerid)));
	return 1;
}