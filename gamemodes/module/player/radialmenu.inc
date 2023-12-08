CMD:radial(playerid, test[])
{
    new str[200], houseid = -1;

    strcat(str, "Umum\n");
    strcat(str, "Dokumen Pribadi\n");
    strcat(str, "Kendaraan\n");
    if ((houseid = House_Inside(playerid)) != -1 && (House_IsOwner(playerid, houseid)) && (Berangkas_Nearest(playerid) != -1)) strcat(str, "Berangkas Rumah\n");
    if(GetNearbyGarkot(playerid) >= 0) strcat(str, "Garkot Menu\n");
    if(GetNearbyRental(playerid) >= 0) strcat(str, "Sewa Kendaraan\n");
    ShowPlayerDialog(playerid, DIALOG_RADIAL, DIALOG_STYLE_LIST, "Radial Menu", str, "Select", "Close");
    return 1;
}