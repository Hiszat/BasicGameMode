#define MAX_DYNAMIC_BERANGKAS           (100)

enum e_berangkas_data
{
    bID,
    Float:bPos[3],
    bPickup,
    bModel,
    bool:bExists
}

new BerangkasData[MAX_DYNAMIC_BERANGKAS][e_berangkas_data];
