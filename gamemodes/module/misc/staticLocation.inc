#include <YSI_Coding\y_hooks>

// Variables
new gLastStaticLocationID;
new gStaticLocations[MAX_STATIC_LOCATIONS][E_STATIC_LOCATION_DATA];
new gPlayerStaticLocation[MAX_PLAYERS + 1];


// Forwards


// Static functions
IsValidStaticLocationType(E_STATIC_LOCATION_TYPE:type)
{
  if (
    type != LOCATION_BLACKMARKET
    && type != LOCATION_SEEDS_SHOP
  ) {
    return 0;
  }

  return 1;
}

stock AddStaticLocation(E_STATIC_LOCATION_TYPE:type, const text[], Float:x, Float:y, Float:z, pickup_model_id, mapicon_model_id = -1, worldid = 0, interiorid = 0)
{
  if (gLastStaticLocationID >= (MAX_STATIC_LOCATIONS - 1))
  {
    printf("[ERROR] Cannot add static location anymore.");
    return 0;
  }

  if (!IsValidStaticLocationType(type))
  {
    printf("[ERROR] Invalid static location type. Found: %d", _:type);
    return 0;
  }

  gStaticLocations[gLastStaticLocationID][LOCATION_TYPE] = type;
  gStaticLocations[gLastStaticLocationID][AREA_ID] = CreateDynamicSphere(x, y, z, 3.0, worldid, interiorid);
  gStaticLocations[gLastStaticLocationID][PICKUP_ID] = CreateDynamicPickup(pickup_model_id, 1, x, y, z, worldid, interiorid);
  gStaticLocations[gLastStaticLocationID][TEXT3D_ID] = CreateDynamic3DTextLabel(text, 0xFFFFFFFF, x, y, z, 10.0, INVALID_PLAYER_ID, INVALID_VEHICLE_ID, 1, worldid, interiorid);
  Streamer_SetIntData(STREAMER_TYPE_AREA, gStaticLocations[gLastStaticLocationID][AREA_ID], E_STREAMER_EXTRA_ID, AREA_EXTRAID_OFFSET + gLastStaticLocationID);

  if (mapicon_model_id > -1)
  {
    gStaticLocations[gLastStaticLocationID][MAPICON_ID] = CreateDynamicMapIcon(x, y, z, mapicon_model_id, -1, worldid, interiorid, -1, STREAMER_MAP_ICON_SD, MAPICON_LOCAL);
  }

  printf("text: %s, x: %.2f, y: %.2f, z: %.2f, worldid: %d, interiorid: %d", text, x, y, z, worldid, interiorid);
  gLastStaticLocationID += 1;
  return 1;
}



// Public functions
Function:SL_IsPlayerAtLocation(playerid, E_STATIC_LOCATION_TYPE:type)
{
  if (playerid < 0 || playerid >= MAX_PLAYERS)
  {
    return -1;
  }

  new
    player_static_location = gPlayerStaticLocation[playerid]
  ;

  if (player_static_location < 1 || player_static_location > (MAX_STATIC_LOCATIONS - 1))
  {
    return -1;
  }

  new
    E_STATIC_LOCATION_TYPE:static_location_type = gStaticLocations[player_static_location][LOCATION_TYPE]
  ;

  if (static_location_type != type)
  {
    return -1;
  }

  return 1;
}

Function:SL_UpdateLocationLabelsByType(E_STATIC_LOCATION_TYPE:type, const text[])
{
  if (!IsValidStaticLocationType(type))
  {
    return -1;
  }

  for (new i = 0; i < MAX_STATIC_LOCATIONS; i++)
  {
    if (gStaticLocations[i][LOCATION_TYPE] == type)
    {
      UpdateDynamic3DTextLabelText(gStaticLocations[i][TEXT3D_ID], 0xFFFFFFFF, text);
    }
  }

  return 1;
}



// Callbacks
hook OnGameModeInit()
{
  gLastStaticLocationID = 1;

  for (new i = 0; i < MAX_PLAYERS; i++)
  {
    gPlayerStaticLocation[i] = INVALID_AREA_ID;
  }

  // Blackmarket
  AddStaticLocation(LOCATION_BLACKMARKET, "[Black Market]\n\
  "WHITE"Type "YELLOW"/creategun"WHITE" to create illegal items\n\
  "WHITE"Type "YELLOW"/createammo"WHITE" to create ammmo\n\
  "WHITE"Type "YELLOW"/repairgun"WHITE" to repair gun's durability\n\
  "WHITE"Type "YELLOW"/craft"WHITE" to craft illegal items\
  ", -50.3808, -232.8592, 6.7646, 1239);
  // Material store
  // Seeds shop
  AddStaticLocation(LOCATION_SEEDS_SHOP, "[Seeds Shop]\n\
  "WHITE"Type "YELLOW"/buyseeds"WHITE" to buy seeds\n\
  "GREEN"$999/seed\
  ", 870.3907, -25.1175, 63.9701, 1239);
  return 1;
}

hook OnGameModeExit()
{
  for (new i = 0; i < MAX_PLAYERS; i++)
  {
    gPlayerStaticLocation[i] = INVALID_AREA_ID;
  }

  return 1;
}

hook OnPlayerConnect(playerid)
{
  gPlayerStaticLocation[playerid] = INVALID_AREA_ID;
  return 1;
}



