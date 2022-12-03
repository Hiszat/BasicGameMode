//============================== SERVER CONFIGURATION =============================
#define SERVER_NAME                     "Dewata Roleplay"
#define SERVER_URL                      "ComingSoon"
#define SERVER_DISCORD					"Soon"
#define SERVER_REVISION                 "Dewata 1.0 FiveM Inspiration"

//============================== MYSQL CONFIGURATION =============================
#define DATABASE_ADDRESS "localhost" //Change this to your Database Address
#define DATABASE_USERNAME "root" // Change this to your database username
#define DATABASE_PASSWORD "" //Change this to your database password
#define DATABASE_NAME "dewata-new" // Change this to your database name

//==============================   SERVER MACROS 	=============================
#define Function:%0(%1)                 forward %0(%1); public %0(%1)
#define forex(%0,%1)                    for(new %0 = 0; %0 < %1; %0++)
#define Loop(%0,%1,%2)                  for(new %0 = %2; %0 < %1; %0++)
#define PRESSED(%0) 					(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))

#define SendServerMessage(%0,%1)        SendTextDrawMessageEx(%0, NOTIFICATION_INFO, %1)
#define SendInfoMessage(%0,%1)        	SendTextDrawMessageEx(%0, NOTIFICATION_INFO, %1)
#define SendCustomMessage(%0,%1,%2)     SendClientMessageEx(%0, X11_LIGHT_SKY_BLUE_1, %1": "WHITE""%2)
#define SendSyntaxMessage(%0,%1)        SendTextDrawMessageEx(%0, NOTIFICATION_INFO, %1)
#define SendErrorMessage(%0,%1)         SendTextDrawMessageEx(%0, NOTIFICATION_ERROR, %1)
#define SendAdminAction(%0,%1)          SendClientMessageEx(%0, X11_PINK, "AdmCmd | "%1)
	
#define PermissionError(%0)				SendTextDrawMessageEx(%0, NOTIFICATION_ERROR, "ERROR: Kamu tidak diizinkan menggunakan perintah ini!")
#define SendCursorAlert(%0)             SendClientMessageEx(%0, X11_PINK, "PETUNJUK | Gunakan perintah '"YELLOW"/cursor"PINK"' apabila cursor kamu tiba tiba menghilang")

//================================ NOTIFICATION ID ===============================
#define NOTIFICATION_INFO       1
#define NOTIFICATION_ERROR      2
#define NOTIFICATION_MESSAGE    3

//================================ DYNAMIC SYSTEM ===============================
#define     MAX_PLAYER_VEHICLE 			(1000)
#define     MAX_INVENTORY               (20)
#define     MAX_LISTED_ITEMS 	        (10)
#define     MAX_DROPPED_ITEMS  	        (1000)
#define     MAX_INVENTORY               (20)
#define     MAX_RENTAL                  (20)
#define 	MAX_ENTRANCES 				(100)
#define 	MAX_BUSINESSES 				(500)
#define 	MAX_DEALERSHIP_CARS 		(40)
#define	 	MAX_GAS_PUMPS 				(100)
#define 	MAX_HOUSES 					(500)
#define 	MAX_HOUSE_STORAGE 			(10)
#define 	MAX_FACTIONS 				(15)

//================================ FRAKSI ===============================
#define FACTION_POLICE 					(1)
#define FACTION_NEWS 					(2)
#define FACTION_MEDIC 					(3)
#define FACTION_GOV 					(4)
#define FACTION_GANG 					(5)

//================================ STARTPACK ===============================
#define START_PLAYER_MONEY        (25000)
#define START_PLAYER_BANK         (50000)

//================================ MAX OWNTABLE ===============================
#define MAX_OWNABLE_BUSINESSES (3)
#define MAX_OWNABLE_HOUSES (3)

//================================ BODY SYSTEM ===============================
#define BODY_PART_TORSO (3)
#define BODY_PART_GROIN (4)
#define BODY_PART_LEFT_ARM (5)
#define BODY_PART_RIGHT_ARM (6)
#define BODY_PART_LEFT_LEG (7)
#define BODY_PART_RIGHT_LEG (8)
#define BODY_PART_HEAD (9)

//================================ SAMP BCRYPT ===============================
#if !defined BCRYPT_HASH_LENGTH
	#define BCRYPT_HASH_LENGTH 250
#endif

#if !defined BCRYPT_COST
	#define BCRYPT_COST 12
#endif

//================================ STATIC LOCATION ===============================
#define AREA_EXTRAID_OFFSET   1_000_000
#define MAX_STATIC_LOCATIONS  101
#define INVALID_AREA_ID       -1

#define COLOR_PURPLE      				(0xD0AEEBFF)
#define SERVER_ICON_DISTANCE 			(100.0)

#define GetPlayerSQLID(%0)              PlayerData[%0][pID]
#define GetMoney(%0)                    PlayerData[%0][pMoney]
#define GetBank(%0)                     PlayerData[%0][pBankMoney]


//================================ ANYTHING FOR ROLEPLAY ========================
#define ACTION_SLOT_ATT	9

#define MDC_COORD 2250.0708, 1257.2338, 864.0117

#define EXTERIOR	0
//============================== WORLD ==========================================
#define LSPD_INTERIOR		3
#define LSPD_VW				1000
#define EMS_INTERIOR		3
#define EMS_VW				1001
#define GOV_INTERIOR		3
#define GOV_VW				1002
// ================================ KEY =========================================
#define KEY_AIM 128

// ============================= DEER ===========================================
#define MAX_DEERS 1
#define MAX_DEER_POSITIONS  229
#define MAX_DEER_TRACKS 28

#define COLOR_GRAD1 0xFFFFFFFF
#define COLOR_GRAD2 0xF8F8F8FF
#define COLOR_GRAD3 0xF0F0F0FF
#define COLOR_GRAD4 0xE8E8E8FF
#define COLOR_GRAD5 0xE0E0E0FF
#define COLOR_GRAD6 0xD8D8D8FF
#define COLOR_GRAD7 0xD0D0D0FF
#define COLOR_GRAD8 0xC8C8C8FF
#define COLOR_GRAD9 0xC0C0C0FF
#define COLOR_GRAD10 0xB8B8B8FF
#define COLOR_GRAD11 0xB0B0B0FF
#define COLOR_GRAD12 0xA8A8A8FF
#define COLOR_GRAD13 0xA0A0A0FF
#define COLOR_GRAD14 0x989898FF
#define COLOR_GRAD15 0x909090FF
#define COLOR_GRAD16 0x888888FF
#define COLOR_GRAD17 0x808080FF
#define COLOR_GRAD18 0x787878FF
#define COLOR_GRAD19 0x707070FF
#define COLOR_GRAD20 0x686868FF
#define COLOR_GRAD21 0x606060FF
#define COLOR_GRAD22 0x585858FF
#define COLOR_GRAD23 0x505050FF
#define COLOR_GRAD24 0x484848FF
#define COLOR_GRAD25 0x404040FF
#define COLOR_GRAD26 0x383838FF
#define COLOR_GRAD27 0x303030FF
#define COLOR_GRAD28 0x282828FF
