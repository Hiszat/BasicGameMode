enum 
{
	RENTAL_AREA_INDEX
}

enum
{
	DIALOG_RENTAL
}

enum
{
	MODEL_SELECTION_FURNITURE
}

enum playerTextraws 
{
	PlayerText:textdraw_petunjuk
};

enum E_STATIC_LOCATION_TYPE
{
  LOCATION_NONE = 0,
  LOCATION_BLACKMARKET,
  LOCATION_SEEDS_SHOP,
};

enum E_STATIC_LOCATION_DATA
{
  ID,
  E_STATIC_LOCATION_TYPE:LOCATION_TYPE,
  Float:POS_X,
  Float:POS_Y,
  Float:POS_Z,
  WORLD_ID,
  INTERIOR_ID,
  // Related to streamer.
  AREA_ID,
  MAPICON_ID,
  Text3D:TEXT3D_ID,
  PICKUP_ID,
  PICKUP_MODEL_ID
};

enum e_player_data
{
	pID,
	pName[MAX_PLAYER_NAME],
	pLogged,
	Float:pPos[3],
	pWorld,
	pInterior,
	pSkin,
	pAge[35],
	pGender,
	bool:pSpawned,
	Float:pHealth,
    Float:pArmor,
    pHeigth,
    pInjured,
    pInjuredTime,
    bool:pDead,
    STREAMER_TAG_3D_TEXT_LABEL:pInjuredLabel,
    pAdmin,
    pLevel,
    pMoney,
    pBank,
    pPark,
    bool:pLoggedIn,
	pListitem,
	pInventory,
	pStorageSelect,
	pTarget,
	pHunger,
	pThirst,
	pRenting,
	pEntrance,
	pFreeze,
	pFreezeTimer,
	bool:pPressBtn,
	pPressBtnTime,
	pBusiness,
	pRefill,
	pRefillPrice,
	pBusinessSeller,
	pBusinessOffered,
	pBusinessValue,
	pGasPump,
	pGasStation,
	pEditPump,
	pFurnitureType,
	pEditingItem[32 char],
	pProductModify
};

enum vCore
{
	vehFuel,
	bool:vehRepair,
	bool:vehAdmin,
	bool:vehHandbrake,
	Float:vehHandbrakePos[4],
	vehWood,
	bool:vehHood,
	bool:vehBoot,
};

enum inventoryData
{
	invExists,
	invID,
	invItem[32 char],
	invModel,
	invQuantity
};

enum e_InventoryItems
{
	e_InventoryItem[32],
	e_InventoryModel
};

enum droppedItems
{
	droppedID,
	droppedItem[32],
	droppedPlayer[24],
	droppedModel,
	droppedQuantity,
	Float:droppedPos[3],
	droppedWeapon,
	droppedAmmo,
	droppedInt,
	droppedWorld,
	droppedObject,
	STREAMER_TAG_3D_TEXT_LABEL:droppedText3D
};

enum e_rental
{
	rentID,
	bool:rentExists,
	Float:rentPos[4],
	Float:rentSpawn[4],
	rentModel[2],
	rentPrice[2],
	STREAMER_TAG_3D_TEXT_LABEL:rentText,
	STREAMER_TAG_ACTOR:rentActor,
	STREAMER_TAG_MAP_ICON:rentIcon,
	rentArea
};

enum entranceData {
	entranceID,
	entranceExists,
	entranceName[32],
	entrancePass[32],
	entranceIcon,
	entranceLocked,
	Float:entrancePos[4],
	Float:entranceInt[4],
	entranceInterior,
	entranceExterior,
	entranceExteriorVW,
	entranceType,
	entranceCustom,
	entranceWorld,
	entranceForklift[7],
	entrancePickup,
	entranceMapIcon,
	Text3D:entranceText3D
};

enum businessData {
	bizID,
	bizExists,
 	bizName[32],
	bizMessage[128],
	bizOwner,
	bizType,
	bizPrice,
	Float:bizPos[4],
	Float:bizInt[4],
	Float:bizSpawn[4],
	Float:bizDeliver[3],
	bizInterior,
	bizExterior,
	bizExteriorVW,
	bizLocked,
	bizVault,
	bizProducts,
	bizPickup,
	bizShipment,
	bizPrices[20],
	Text3D:bizText3D,
	Text3D:bizDeliverText3D,
	bizDeliverPickup
};

enum pumpData {
	pumpID,
	pumpExists,
	pumpBusiness,
	Float:pumpPos[4],
	pumpFuel,
	pumpObject,
	Text3D:pumpText3D
};