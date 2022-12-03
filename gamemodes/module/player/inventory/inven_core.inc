enum e_temp_inventory
{
	iHouseID,
	iAmount,
	iItemName[45]
}
new InventoryTemp[MAX_PLAYERS][e_temp_inventory];

new const g_aInventoryItems[][e_InventoryItems] =
{
	{"GPS", 18875},
	{"Cellphone", 18867},
	{"Medkit", 1580},
	{"Portable Radio", 19942},
	{"Mask", 19036},
	{"Snack", 19811},
	{"Es Teh", 19835},
	{"Milk", 19570},
	{"Coffe", 19835},
	{"Juice", 19564},
	{"Cigarette", 19897},
	{"Pizza", 1582},
	{"Burger", 2768},
	{"Fried Chicken", 2663},
	{"Rolling Paper", 19873},
	{"Rolled Weed", 3027},
	{"Weed", 1578},
	{"Component", 19627},
	{"Weed Seed", 1279},
	{"9mm Luger", 19995},
	{"12 Gauge", 19995},
	{"9mm Silenced Schematic", 3111},
	{"Shotgun Schematic", 3111},
	{"9mm Silenced Material", 3052},
	{"Shotgun Material", 3052},
	{"Axe", 19631},
	{"Fish Rod", 18632},
	{"Bait", 19566},
	{"Driving License", 1581},
	{"Idcard", 1581},
	{"Bibit Kentang", 1575},
	{"Bibit Gandum", 1575},
	{"Gandum", 2912},
	{"Kentang", 2912},
	{"Deer Antler", 19314},
	{"Animal Blood Pack", 1580},
	{"Deer Hide", 19315},
	{"Pisau", 335},
	{"Deer Meat", 2806},
	{"Senapan Berburu", 2036}
};


