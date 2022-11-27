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
#define SendCustomMessage(%0,%1,%2)     SendClientMessageEx(%0, X11_LIGHT_SKY_BLUE_1, %1": "WHITE""%2)
#define SendSyntaxMessage(%0,%1)        SendTextDrawMessageEx(%0, NOTIFICATION_INFO, %1)
#define SendErrorMessage(%0,%1)         SendTextDrawMessageEx(%0, NOTIFICATION_ERROR, %1)
#define SendAdminAction(%0,%1)          SendClientMessageEx(%0, X11_TOMATO, "AdmCmd | "%1)
	
#define PermissionError(%0)				SendTextDrawMessageEx(%0, NOTIFICATION_ERROR, "ERROR: Kamu tidak diizinkan menggunakan perintah ini!")

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

//================================ STARTPACK ===============================
#define START_PLAYER_MONEY        (25000)
#define START_PLAYER_BANK         (50000)

//================================ MAX OWNTABLE ===============================
#define MAX_OWNABLE_BUSINESSES (3)

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


//============================== WORLD ==========================================
#define LSPD_INTERIOR		3
#define LSPD_VW				1000
#define EMS_INTERIOR		3
#define EMS_VW				1001
#define GOV_INTERIOR		3
#define GOV_VW				1002