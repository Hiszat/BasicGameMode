enum 
{
	RENTAL_AREA_INDEX
}

enum
{
	DIALOG_LOGIN,
	DIALOG_REGISTER,
	DIALOG_REG_CONFIRM,
	DIALOG_AGE,
	DIALOG_RADIAL,
	DIALOG_RADIAL_U,
	DIALOG_RADIAL_V,
	DIALOG_DATEB,
	DIALOG_GENDER,
	DIALOG_GARKOT,
	DIALOG_LOCK_V,
	DIALOG_KOSONG,
	DIALOG_PICKITEM,
	DIALOG_RENTTIME,
	DIALOG_RENTAL,
	DIALOG_TOY,
	DIALOG_TOYEDIT,
	DIALOG_TOYPOSISI,
	DIALOG_TOYPOSISIBUY,
	DIALOG_TOYBUY,
	DIALOG_TOYVIP,
	DIALOG_TOYPOSX,
	DIALOG_TOYPOSY,
	DIALOG_TOYPOSZ,
	DIALOG_TOYPOSRX,
	DIALOG_TOYPOSRY,
	DIALOG_TOYPOSRZ,
	DIALOG_TOYPOSSX,
	DIALOG_TOYPOSSY,
	DIALOG_TOYPOSSZ
}

enum
{
	MODEL_SELECTION_FURNITURE,
	MODEL_SELECTION_SKINS,
	MODEL_SELECTION_ADD_SKIN,
	MODEL_SELECTION_FACTION_SKIN,
	MODEL_SELECTION_BUYSKIN,
	MODEL_SELECTION_ACC, 
}

enum playerTextraws 
{
	PlayerText:textdraw_petunjuk,
	PlayerText:textdraw_ammo
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
	pFreeze,
	pFreezeTimer,
	bool:pPressBtn,
	pPressBtnTime,
	pEntrance,
	pBusiness,
	pHouse,
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
	pProductModify,
	pSkinPrice,
	pTempModel,
	pIP[16],
	pHouseSeller,
	pHouseOffered,
	pHouseValue,
	pStorageItem,
	pGuns[13],
	pAmmo[13],
	pDurability[13],
	pFactionOffer,
	pFactionOffered,
	pFaction,
	pFactionRank,
	pFacDiv,
	pSelectedSlot,
	pOnDuty,
	pDisableFaction,
	pJetpack,
	pClothing,
	pJailType,
	pJailTime,
	pAJailTime,
	pWanted,
	pCuffed,
	pJob,
	pJob2,
	pTruckerTimer,
	pJobDuty,
	pTrackTime,
	pDuty,
};

enum sStuffData
{
	sId,
	sName[64],
	sAmount
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

enum drInfo{
    Float:dPosX,
    Float:dPosY,
    Float:dPosZ,
    Float:dAngle,
    dObject,
    dCurrPos,
    dType,
    dTimer,
    dDirection,
    dCondition,
    dSkinned,
    bool: dFinalDest,
    bool: dAntlers,
    dTimerArea,
    dAlert,
    dMovedVar
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
	Float:bizActorPosition[4],
	Float:bizSpawn[4],
	Float:bizDeliver[3],
	bizInterior,
	bizExterior,
	bizExteriorVW,
	bizLocked,
	bizVault,
	bizProducts,
	bizPickup,
	bizActor,
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

enum houseData {
	houseID,
	houseExists,
	houseOwner,
	housePrice,
	houseAddress[32],
	Float:housePos[4],
	Float:houseInt[4],
	houseInterior,
	houseExterior,
	houseExteriorVW,
	houseLocked,
	houseMoney,
	houseMapIcon,
	Text3D:houseText3D,
	housePickup,
	houseLights,
	houseWeapons[10],
	houseAmmo[10],
	houseClothing[5],
};

enum houseStorage {
	hItemID,
	hItemExists,
	hItemName[32 char],
	hItemModel,
	hItemQuantity
};

enum factionData {
	factionID,
	factionExists,
	factionName[32],
	factionColor,
	factionType,
	factionRanks,
	Float:factionLockerPos[3],
	factionLockerInt,
	factionLockerWorld,
	factionSkins[8],
	factionWeapons[10],
	factionAmmo[10],
	Text3D:factionText3D,
	factionPickup,
	Float:SpawnX,
	Float:SpawnY,
	Float:SpawnZ,
	SpawnInterior,
	SpawnVW
};

enum e_toy_data
{
	toy_id,
	toy_name[54],
	toy_model,
	toy_skin,
	toy_bone,
	Float:toy_x,
	Float:toy_y,
	Float:toy_z,
	Float:toy_rx,
	Float:toy_ry,
	Float:toy_rz,
	Float:toy_sx,
	Float:toy_sy,
	Float:toy_sz
}

enum e_clothing_data
{
    cID,
    cSkin,
    cOwner
}