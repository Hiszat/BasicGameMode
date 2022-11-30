#include <YSI\y_hooks>

hook OnGameModeInit(){
    for(new i; i < MAX_DEERS; i ++)
	{
	    for(new j; j < MAX_DEER_TRACKS; j++)
		{
			DeerTrack[i][j] = Create3DTextLabel("Deer Track", COLOR_GRAD1, 0.0, 0.0, -1000.0, 15.0, EXTERIOR, 1);
		}
		DeerInfo[i][dObject] = CreateObject(19315, DeerInfo[i][dPosX], DeerInfo[i][dPosY], DeerInfo[i][dPosZ],  dRotX[i], dRotY[i], DeerInfo[i][dAngle]);
		SpawnDeer(i);
	}
    return 1;
}

Dialog:DeerKnife(playerid, response, listitem, inputtext[])
{
	if(response){//Playing Hours - 0(not looted), 1(skinned), 2(meat taken), 3(horns taken), 4(all taken)
	    if(GetPlayerAnimationIndex(playerid) == 754)//Already doing something (slicing shit)
		{
		    SendErrorMessage(playerid, "Finish the current action first.");
		}
		else
		{
			new itemid = Inventory_GetFreeID(playerid);
			switch(listitem)
			{//1. Skin the deer.\n2. Remove and take the Meat.\n3. Remove and take the Deer Antlers.
			    case 0:
			    {
			        if(itemid >= MAX_INVENTORY && Inventory_Count(playerid, "Deer Hide") >= 5)
				    {
				        SendErrorMessage(playerid, "Inventory sudah penuh.");
				    }
			        else if(!DeerInfo[GetPVarInt(playerid, "Deer")][dCondition])
			        {//speed: 2.7; lockx: 1; locky 1; freeze 0; time 0;
			            ApplyAnimation(playerid,"KNIFE","KNIFE_G",1.1,1,1,1,0,0,1);//(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
			            SetTimerEx("HunterAction", 1000, false, "iiii", playerid, GetPVarInt(playerid, "Deer"), 1, 30);
						return GameTextForPlayer(playerid, "~g~Skinning...~n~~w~30 seconds remaining", 2000, 4);
					}
					else
					{
						SendErrorMessage(playerid, "Rusa telah di kuliti.");
					}
				}
			    case 1:
			    {
			        if(itemid >= MAX_INVENTORY && Inventory_Count(playerid, "Deer Meat") >= 50)
				    {
				        SendErrorMessage(playerid, "Inventory sudah penuh.");
				    }
			        else if(DeerInfo[GetPVarInt(playerid, "Deer")][dCondition] == 1 || DeerInfo[GetPVarInt(playerid, "Deer")][dCondition] == 3)
			        {
			            ApplyAnimation(playerid,"KNIFE","KNIFE_G",1.1,1,1,1,0,0,1);//(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
			            SetTimerEx("HunterAction", 1000, false, "iiii", playerid, GetPVarInt(playerid, "Deer"), 2, 30);
						return GameTextForPlayer(playerid, "~g~Cutting the Meat...~n~~w~30 seconds remaining", 2000, 4);
					}
					else if(!DeerInfo[GetPVarInt(playerid, "Deer")][dCondition])
					{
					    SendErrorMessage(playerid, "Kamu harus menguliti rusanya terlebih dahulu sebelum mengambil dagingnya.");
					}
					else
					{
						SendErrorMessage(playerid, "Daging rusa telah diambil");
					}
				}
			    case 2:
			    {
			        if(itemid >= MAX_INVENTORY && Inventory_Count(playerid, "Deer Antlers") >= 32)
				    {
				        SendErrorMessage(playerid, "Inventory sudah penuh.");
				    }
			        else if(DeerInfo[GetPVarInt(playerid, "Deer")][dAntlers] && (DeerInfo[GetPVarInt(playerid, "Deer")][dCondition] == 1 || DeerInfo[GetPVarInt(playerid, "Deer")][dCondition] == 2))
			        {
			            ApplyAnimation(playerid,"KNIFE","KNIFE_G",1.1,1,1,1,0,0,1);//(playerid, animlib[], animname[], Float:fDelta, loop, lockx, locky, freeze, time, forcesync)
			            SetTimerEx("HunterAction", 1000, false, "iiii", playerid,  GetPVarInt(playerid, "Deer"), 3, 30);
						return GameTextForPlayer(playerid, "~g~Removing the Deer Antlers...~n~~w~30 seconds remaining", 2000, 4);
					}
					else if(!DeerInfo[GetPVarInt(playerid, "Deer")][dCondition])
					{
					    SendErrorMessage(playerid, "Kamu harus menguliti rusa nya terlebih dahulu");
					}
					else if(DeerInfo[GetPVarInt(playerid, "Deer")][dCondition] > 2)
					{
						SendErrorMessage(playerid, "Tanduk rusa telah diambil.");
					}
					else
					{
					    SendErrorMessage(playerid, "Rusa ini tidak memiliki tanduk.");
					}
				}
			}
		}
		ShowSkinningKnifeDialog(playerid);
	}
	return 1;
}




hook OnPlayerKeyStateChange(playerid, newkeys, oldkeys)
{//IsPlayerAimingAt(playerid, Float:x, Float:y, Float:z, Float:radius)
    if((newkeys & KEY_FIRE) && !(oldkeys & KEY_FIRE))//Deer Script && (oldkeys & KEY_AIM)
    {
	    if(GetPlayerWeapon(playerid) == 34)//Hunting Rifle
	    {
	        if(newkeys & KEY_AIM)
	        {
		        new Float: x, Float: y, Float: z;
		        for(new i; i < MAX_DEERS; i++)
		        {
		            if(!DeerInfo[i][dType])
		            {
		                GetObjectPos(DeerInfo[i][dObject], x, y, z);//attached object
		                if(IsPlayerAimingAt(playerid, x, y, z+0.17, 0.15))
		                {
		                    OnDeerDeath(i);
		                    return 0;
						}
					}
				}
			}
		}
	}
    return 1;
}
Function:HunterAction(playerid, deerid, action, time)
{
    if(IsPlayerConnected2(playerid))
	{
	    /*if(GetPlayerAnimationIndex(playerid) != 754)
	    {
	        //ShowSkinningKnifeDialog(playerid);
	        RemovePlayerAttachedObject(playerid, ACTION_SLOT_ATT);
	        //ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Crouch_Out", 4.0, 0, 0, 0, 0, 0, 1);
	        //ApplyAnimation(playerid, "CARRY", "crry_prtial", 4.0, 0, 0, 0, 0, 0, 1);//Resetanim
	        return GameTextForPlayer(playerid, "~r~Canceled", 2000, 4);
	    }*/
	    time--;
	    new string[66];
		if(!time)
		{
		    switch(action)
		    {//dCondition - 0(not looted), 1(skinned), 2(meat taken), 3(horns taken), 4(all taken)
		        case 1://Skinning
		        {
		            if(DeerInfo[deerid][dCondition])
		            {
		                GameTextForPlayer(playerid, "~r~Canceled", 2000, 4);
		              	SendErrorMessage(playerid, "That deer is already skinned.");
					}
					else
					{
						GameTextForPlayer(playerid, "~g~Deer Skinned", 2000, 4);
						if(InvenAdd(playerid, "Deer Hide", 1))
						{
							SendServerMessage(playerid, "Deer Hide (1) has been added to your inventory.");
						}
						else
						{
						    SendErrorMessage(playerid, "You couldn't recieve Deer Hide (1). Your inventory is full.");
						}
						new amount = 2+random(3);//2-4
						if(InvenAdd(playerid, "Animal Blood Pack", amount))
						{
						    format(string, sizeof(string), "SERVER: Animal Blood Pack (%d) has been added to your inventory.", amount);
							SendServerMessage(playerid, string);
						}
						else
						{
						    format(string, sizeof(string), "You couldn't recieve Animal Blood Pack (%d). Your inventory is full.", amount);
						    SendErrorMessage(playerid, string);
						}
						DeerInfo[deerid][dCondition] = 1;
					}
					SetPVarInt(playerid, "Deer", deerid);
				}
				case 2://Cutting Meat
		        {
		            if(DeerInfo[deerid][dCondition] == 2 || DeerInfo[deerid][dCondition] == 4)
		            {
		                GameTextForPlayer(playerid, "~r~Canceled", 2000, 4);
		                SendErrorMessage(playerid, "There is no Meat to take.");
					}
					else
					{
						GameTextForPlayer(playerid, "~g~Meat Cut", 2000, 4);
						new amount = 5+random(6);//5-10
						if(InvenAdd(playerid, "Deer Meat", amount))
						{
						    format(string, sizeof(string), "SERVER: Meat (%d) has been added to your inventory.", amount);
							SendServerMessage(playerid, string);
						}
						else
						{
						    format(string, sizeof(string), "You couldn't recieve Meat (%d). Your inventory is full.", amount);
						   	SendErrorMessage(playerid, string);
						}
						if(DeerInfo[deerid][dCondition] == 1)
						{
						    DeerInfo[deerid][dCondition] = 2;
						}
						else
						{
						    DeerInfo[deerid][dCondition] = 4;
						}
					}
					SetPVarInt(playerid, "Deer", deerid);
				}
				case 3://Removing Antlers
		        {
		            if(DeerInfo[deerid][dCondition] > 2)
		            {
		                GameTextForPlayer(playerid, "~r~Canceled", 2000, 4);
		                SendErrorMessage(playerid, "The Deer Antlers are already removed.");
					}
					else
					{
						GameTextForPlayer(playerid, "~g~Deer Antlers Removed", 2000, 4);
						if(InvenAdd(playerid, "Deer Antler", 2))
						{
							SendServerMessage(playerid, "Deer Antler (2) has been added to your inventory.");
						}
						else
						{
						    SendErrorMessage(playerid, "You couldn't recieve Deer Antler (2). Your inventory is full.");
						}
						if(DeerInfo[deerid][dCondition] == 1)
						{
						    DeerInfo[deerid][dCondition] = 3;
						}
						else
						{
						    DeerInfo[deerid][dCondition] = 4;
						}
					}
					SetPVarInt(playerid, "Deer", deerid);
				}
		    }
		    return 1;
		}
		SetTimerEx("HunterAction", 1000, false, "iiii", playerid, deerid, action, time);
		switch(action)
		{
		    case 1: format(string, sizeof(string), "~g~Skinning...~n~~w~%d seconds remaining", time);
		    case 2: format(string, sizeof(string), "~g~Cutting the Meat...~n~~w~%d seconds remaining", time);
		    case 3: format(string, sizeof(string), "~g~Removing the Deer Antlers...~n~~w~%d seconds remaining", time);
		}
		GameTextForPlayer(playerid, string, 2000, 4);
	}
	return 1;
}


Function:SpawnDeer(deerid)
{
    GetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
    SetTimerEx("SpawnDeer", 60000, false, "i", deerid);
	DeerInfo[deerid][dCurrPos] = random(MAX_DEER_POSITIONS);
	if(!IsAreaClear(deerid))
	{
	    return SetTimerEx("SpawnDeer", 60000, false, "i", deerid);
	}
 	GetDeerNextPosition(deerid);
 	DeerInfo[deerid][dDirection] = random(2);//Current Direction
	DeerInfo[deerid][dType] = 0;//Deer spawned and alive
	DeerInfo[deerid][dAlert] = 0;//Deer not in danger
	DeerInfo[deerid][dCondition] = 0;//Not skinned, with meat and antlers
	DeerInfo[deerid][dMovedVar] = 0;//Didn't Rotate
	if(!random(4))
	{
		DeerInfo[deerid][dAntlers] = true;//Has Antlers
	}
	if(random(2))
	{
	    DeerInfo[deerid][dFinalDest] = true;//Final Dest
	}
	//DestroyObject(DeerInfo[deerid][dObject]);
	DeerInfo[deerid][dTimerArea] = SetTimerEx("DeerPerception", 1000, true, "i", deerid);
	SetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
	SetObjectRot(DeerInfo[deerid][dObject],  dRotX[deerid], dRotY[deerid], DeerInfo[deerid][dAngle]);
	DeerInfo[deerid][dTimer] =  SetTimerEx("PreMoveDeer", random(15000), false, "i", deerid);
	return 1;
}

Function:DeerPerception(deerid)
{
    GetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
    if(IsAreaClear(deerid))
    {
        DeerInfo[deerid][dAlert] = 0;
	}
	else
	{
	    if(!DeerInfo[deerid][dAlert])
	    {
	        KillTimer(DeerInfo[deerid][dTimer]);
	        PreMoveDeer(deerid);
		}
	    DeerInfo[deerid][dAlert] = 1;
	}
}

stock IsAreaClear(deerid)
{
	GetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
    for(new i; i<MAX_PLAYERS; i++)
	{
	    if(IsPlayerConnected(i))
	    {
	        if(IsPlayerInRangeOfPoint(i, 80.0, DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]))
	        {
	            switch(GetPlayerAnimationIndex(i))
	            {
	                case 1274, 1159, 1069, 1070, 1365, 1160, 1161, 1162, 1163, 1158, 1167:
	                {
	                    if(IsPlayerInRangeOfPoint(i, 40.0, DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]))
		                {
		                    //SendClientMessage(2, COLOR_GREEN, "DANGER (crouching)");
		                    return false;
						}
					}
					default:
					{
					    //SendClientMessage(2, COLOR_RED, "DANGER (not crouching)");
	            		return false;
					}
				}
			}
		}
	}
	return true;
}

Function:PreMoveDeer(deerid)
{
	new speed = DeerInfo[deerid][dCurrPos];
	new finaldestination = random(10);
	if(DeerInfo[deerid][dAlert])//Danger
	{
	    finaldestination = 4;
	}
	if(!DeerInfo[deerid][dFinalDest])//Backwards
	{
	    finaldestination += 4;//4-13 (7)
	}
	if(finaldestination > 6)//Backwards
	{
    	DeerInfo[deerid][dCurrPos]--;
    	if(DeerInfo[deerid][dCurrPos] < 0)
		{
            DeerInfo[deerid][dCurrPos] += 2;
            DeerInfo[deerid][dFinalDest] = true;//Change of final destination
		}
	}
	else//Backwards
	{
	    DeerInfo[deerid][dCurrPos]++;
	    if(DeerInfo[deerid][dCurrPos] > MAX_DEER_POSITIONS-1)
		{
            DeerInfo[deerid][dCurrPos] -= 2;
            DeerInfo[deerid][dFinalDest] = false;
		}
	}
	if(speed < DeerInfo[deerid][dCurrPos] )//New direction is Forward
	{
	    if(DeerInfo[deerid][dDirection] != 1)//Old direction was back
	    {
	        return FinalMoveDeer(deerid);//Change direction
		}
	}
	else//New direction is back
	{
	    if(DeerInfo[deerid][dDirection] == 1)//Old direction was forward
	    {
	        return FinalMoveDeer(deerid);//Change direction CONFUSED but it works!
		}
	}
	DeerInfo[deerid][dMovedVar] = 1;//Changed Direction
 	ChangeDirection(deerid);
	return 1;
}

Function:FinalMoveDeer(deerid)
{
	new Float: x, Float: y, Float: z;
	x = DeerInfo[deerid][dPosX];
	y = DeerInfo[deerid][dPosY];
	z = DeerInfo[deerid][dPosZ];
	GetDeerNextPosition(deerid);
	GetObjectPos(DeerInfo[deerid][dObject], x, y, z);
    z = GetDistanceBetweenPoints(x, y, z, DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);//DEER_MOVEMENT_SPEED
	//new time;
	x = 1.4;
	if(!DeerInfo[deerid][dAlert])//Not In Danger
	{
	    //time += random(15000);
	    x = 15.0+random(30);
    	x /= 100.0;
	}
	z *= x;
	DeerInfo[deerid][dMovedVar] = 0;
	/*time += */
	MoveObject(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ], z, dRotX[deerid], dRotY[deerid], DeerInfo[deerid][dAngle]);
	//DeerInfo[deerid][dTimer] =  SetTimerEx("PreMoveDeer", time, false, "i", deerid);
	return 1;
}

stock ChangeDirection(deerid)
{
    DeerInfo[deerid][dAngle] -= 180;
    dRotX[deerid] *= -1;
    dRotY[deerid] *= -1;
    //new Float: x, Float: y, Float: z;
    GetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
	if(DeerInfo[deerid][dDirection])
	{
	    DeerInfo[deerid][dDirection] = 0;
	}
	else
	{
	    DeerInfo[deerid][dDirection] = 1;
	}
	//new time;
	/*new Float: speed;
	if(!DeerInfo[deerid][dAlert])
    {
        speed = 0.007;
        if(!random(4))
        {
        	time += random(10000);
		}
	}
	else
	{
	    speed = 0.009;
	}*/
	/*if(!random(4))//!DeerInfo[deerid][dAlert] &&
    {
    	time += random(10000);
	}
    time += */
	MoveObject(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]+0.008, 0.007, dRotX[deerid], dRotY[deerid], DeerInfo[deerid][dAngle]);
    //DeerInfo[deerid][dTimer] =  SetTimerEx("FinalMoveDeer", time, false, "i", deerid);
    //printf("time: %d", time);
    return 1;
}

stock OnDeerDeath(deerid)
{
	KillTimer(DeerInfo[deerid][dTimer]);
	KillTimer(DeerInfo[deerid][dTimerArea]);
    StopObject(DeerInfo[deerid][dObject]);
    DeerInfo[deerid][dType] = 1;//Deer spawned and dead, on the ground
    GetObjectPos(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]);
    new Float: z;
    GetObjectRot(DeerInfo[deerid][dObject], dRotX[deerid], dRotY[deerid], z);
    MoveObject(DeerInfo[deerid][dObject], DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]-0.42, 1.0, -90.00, dRotY[deerid]-180.0, z-180.0);
    SetTimerEx("SpawnDeer", 180000, false, "i", deerid);//3 minutes
}

stock UpdateDeerTracks(deerid)
{//new Text3D: DeerTrack[MAX_DEERS][MAX_DEER_TRACKS];
    Delete3DTextLabel(DeerTrack[deerid][MAX_DEER_TRACKS-1]);//Delete the last track
	for(new i = MAX_DEER_TRACKS-2; i > -1; i--)
	{
	    DeerTrack[deerid][i+1] = DeerTrack[deerid][i];
	    Update3DTextLabelText(DeerTrack[deerid][i+1], GetDeerTrackColor(i+1), "Deer Track");
	}
	DeerTrack[deerid][0] = Create3DTextLabel("Deer Track", COLOR_GRAD1, DeerInfo[deerid][dPosX], DeerInfo[deerid][dPosY], DeerInfo[deerid][dPosZ]-0.5, 15.0, EXTERIOR, 0);
}

stock GetDeerTrackColor(i)
{
	switch(i)
	{
	    case 1: return COLOR_GRAD2;
	    case 2: return COLOR_GRAD3;
	    case 3: return COLOR_GRAD4;
	    case 4: return COLOR_GRAD5;
	    case 5: return COLOR_GRAD6;
	    case 6: return COLOR_GRAD7;
	    case 7: return COLOR_GRAD8;
	    case 8: return COLOR_GRAD9;
	    case 9: return COLOR_GRAD10;
	    case 10: return COLOR_GRAD11;
	    case 11: return COLOR_GRAD12;
	    case 12: return COLOR_GRAD13;
	    case 13: return COLOR_GRAD14;
	    case 14: return COLOR_GRAD15;
	    case 15: return COLOR_GRAD16;
	    case 16: return COLOR_GRAD17;
	    case 17: return COLOR_GRAD18;
	    case 18: return COLOR_GRAD19;
	    case 19: return COLOR_GRAD20;
	    case 20: return COLOR_GRAD21;
	    case 21: return COLOR_GRAD22;
	    case 22: return COLOR_GRAD23;
	    case 23: return COLOR_GRAD24;
	    case 24: return COLOR_GRAD25;
	    case 25: return COLOR_GRAD26;
	    case 26: return COLOR_GRAD27;
	    case 27: return COLOR_GRAD28;
	}
	return COLOR_GRAD1;
}

hook OnObjectMoved(objectid)
{
	for(new i; i<MAX_DEERS; i++)
	{
	    if(DeerInfo[i][dObject] == objectid)//Deer
	    {
	        if(!DeerInfo[i][dType])//Alive
	        {
	            if(DeerInfo[i][dMovedVar])//What to call (FinalMoveDeer) The deer has rotated
		        {
		            if(!DeerInfo[i][dAlert])
		            {
		            	DeerInfo[i][dTimer] =  SetTimerEx("FinalMoveDeer", random(15000), false, "i", i);
					}
					else
					{
					    FinalMoveDeer(i);
					}
		        }
		        else//What to call (PreMoveDeer)
		        {
		        	UpdateDeerTracks(i);
		            if(!DeerInfo[i][dAlert])
		            {
		            	DeerInfo[i][dTimer] =  SetTimerEx("PreMoveDeer", random(15000), false, "i", i);
					}
					else
					{
					    PreMoveDeer(i);
					}
				}
			}
		}
	}
}

stock GetDeerNextPosition(deerid)
{//CreateObject(19315, 2615.39307, 2.43468, 29.91000,   -7.08000, -4.92000, -38.82001);//CreateObject(19315, 2624.77393, -6.74257, 33.99693,   6.42000, -17.16000, -137.75995);
	if(!deerid)
	{
	    switch(DeerInfo[deerid][dCurrPos])
		{
		    case 0: { DeerInfo[deerid][dPosX] = 2604.27; DeerInfo[deerid][dPosY] = 3.36; DeerInfo[deerid][dPosZ] = 29.00; dRotX[deerid] = -7.08; dRotY[deerid] = -4.92; DeerInfo[deerid][dAngle] = 0; }
		    case 1: { DeerInfo[deerid][dPosX] = 2615.07; DeerInfo[deerid][dPosY] = 3.06; DeerInfo[deerid][dPosZ] = 29.91; dRotX[deerid] = -7.08; dRotY[deerid] = -4.92; DeerInfo[deerid][dAngle] = 0; }
		    case 2: { DeerInfo[deerid][dPosX] = 2615.39307; DeerInfo[deerid][dPosY] = 2.43468; DeerInfo[deerid][dPosZ] = 29.91000; dRotX[deerid] = -7.08000; dRotY[deerid] = -4.92000; DeerInfo[deerid][dAngle] = -39; }
		    case 3: { DeerInfo[deerid][dPosX] = 2618.24; DeerInfo[deerid][dPosY] = 0.20; DeerInfo[deerid][dPosZ] = 30.32; dRotX[deerid] = -4.08; dRotY[deerid] = -21.72; DeerInfo[deerid][dAngle] = -42; }
		    case 4: { DeerInfo[deerid][dPosX] = 2625.32; DeerInfo[deerid][dPosY] = -6.36; DeerInfo[deerid][dPosZ] = 34.05; dRotX[deerid] = -4.08; dRotY[deerid] = -21.72; DeerInfo[deerid][dAngle] = -42; }
		    case 5: { DeerInfo[deerid][dPosX] = 2624.77393; DeerInfo[deerid][dPosY] = -6.74257; DeerInfo[deerid][dPosZ] = 33.99693; dRotX[deerid] = 6.42000; dRotY[deerid] = -17.16000; DeerInfo[deerid][dAngle] = -138; }
		    case 6: { DeerInfo[deerid][dPosX] = 2623.40; DeerInfo[deerid][dPosY] = -7.88; DeerInfo[deerid][dPosZ] = 34.13; dRotX[deerid] = 6.42; dRotY[deerid] = -17.16; DeerInfo[deerid][dAngle] = -137; }
		    case 7: { DeerInfo[deerid][dPosX] = 2618.52; DeerInfo[deerid][dPosY] = -13.78; DeerInfo[deerid][dPosZ] = 35.07; dRotX[deerid] = 4.02; dRotY[deerid] = -7.14; DeerInfo[deerid][dAngle] = -128; }
	        case 8: { DeerInfo[deerid][dPosX] = 2619.02; DeerInfo[deerid][dPosY] = -15.20; DeerInfo[deerid][dPosZ] = 35.71; dRotX[deerid] = 0.72; dRotY[deerid] = -26.10; DeerInfo[deerid][dAngle] = -73; }
	        case 9: { DeerInfo[deerid][dPosX] = 2627.39; DeerInfo[deerid][dPosY] = -44.76; DeerInfo[deerid][dPosZ] = 47.48; dRotX[deerid] = -1.20; dRotY[deerid] = -23.52; DeerInfo[deerid][dAngle] = -70; }
	        case 10: { DeerInfo[deerid][dPosX] = 2627.58813; DeerInfo[deerid][dPosY] = -45.72799; DeerInfo[deerid][dPosZ] = 47.69829; dRotX[deerid] = -19.32000; dRotY[deerid] = -7.02000; DeerInfo[deerid][dAngle] = -45; }
	        case 11: { DeerInfo[deerid][dPosX] = 2634.69312; DeerInfo[deerid][dPosY] = -52.46413; DeerInfo[deerid][dPosZ] = 48.57130; dRotX[deerid] = -13.01999; dRotY[deerid] = -3.4800; DeerInfo[deerid][dAngle] = -45; }
	        case 12: { DeerInfo[deerid][dPosX] = 2635.70361; DeerInfo[deerid][dPosY] = -52.36076; DeerInfo[deerid][dPosZ] = 48.47740; dRotX[deerid] = -7.67999; dRotY[deerid] = 6.060; DeerInfo[deerid][dAngle] = 12; }
	        case 13: { DeerInfo[deerid][dPosX] = 2645.32056; DeerInfo[deerid][dPosY] = -50.75748; DeerInfo[deerid][dPosZ] = 47.42482; dRotX[deerid] = -7.67999; dRotY[deerid] = 6.06000; DeerInfo[deerid][dAngle] = 12; }
	        case 14: { DeerInfo[deerid][dPosX] = 2646.19800; DeerInfo[deerid][dPosY] = -49.79667; DeerInfo[deerid][dPosZ] = 47.16517; dRotX[deerid] = -3.71999; dRotY[deerid] = 9.30; DeerInfo[deerid][dAngle] = 55; }
	        case 15: { DeerInfo[deerid][dPosX] = 2649.88232; DeerInfo[deerid][dPosY] = -44.42928; DeerInfo[deerid][dPosZ] = 45.72119; dRotX[deerid] = -3.71999; dRotY[deerid] = 9.3000; DeerInfo[deerid][dAngle] = 55; }
	        case 16: { DeerInfo[deerid][dPosX] = 2650.75952; DeerInfo[deerid][dPosY] = -43.82983; DeerInfo[deerid][dPosZ] = 45.50818; dRotX[deerid] = -4.62000; dRotY[deerid] = 11.6400; DeerInfo[deerid][dAngle] = 30; }
	        case 17: { DeerInfo[deerid][dPosX] = 2656.42773; DeerInfo[deerid][dPosY] = -40.52926; DeerInfo[deerid][dPosZ] = 44.17512; dRotX[deerid] = -4.62000; dRotY[deerid] = 11.64000; DeerInfo[deerid][dAngle] = 30; }
	        case 18: { DeerInfo[deerid][dPosX] = 2657.31445; DeerInfo[deerid][dPosY] = -41.04246; DeerInfo[deerid][dPosZ] = 44.28268; dRotX[deerid] = -9.11999; dRotY[deerid] = -9.4800; DeerInfo[deerid][dAngle] = -49; }
	        case 19: { DeerInfo[deerid][dPosX] = 2661.35132; DeerInfo[deerid][dPosY] = -45.31564; DeerInfo[deerid][dPosZ] = 44.98967; dRotX[deerid] = -9.11999; dRotY[deerid] = -9.4800; DeerInfo[deerid][dAngle] = -49; }
	        case 20: { DeerInfo[deerid][dPosX] = 2661.60083; DeerInfo[deerid][dPosY] = -46.11884; DeerInfo[deerid][dPosZ] = 45.16364; dRotX[deerid] = -8.87999; dRotY[deerid] = -11.8800; DeerInfo[deerid][dAngle] = -74; }
	        case 21: { DeerInfo[deerid][dPosX] = 2663.86060; DeerInfo[deerid][dPosY] = -53.38623; DeerInfo[deerid][dPosZ] = 46.40233; dRotX[deerid] = -8.87999; dRotY[deerid] = -11.8800; DeerInfo[deerid][dAngle] = -74; }
	 		case 22: { DeerInfo[deerid][dPosX] = 2664.46606; DeerInfo[deerid][dPosY] = -53.87579; DeerInfo[deerid][dPosZ] = 46.47915; dRotX[deerid] = -9.23999; dRotY[deerid] = 2.58000; DeerInfo[deerid][dAngle] = -13; }
			case 23: { DeerInfo[deerid][dPosX] = 2672.02515; DeerInfo[deerid][dPosY] = -55.22592; DeerInfo[deerid][dPosZ] = 46.12355;   dRotX[deerid] = -9.23999; dRotY[deerid] = 2.58000; DeerInfo[deerid][dAngle] = -13; }
			case 24: { DeerInfo[deerid][dPosX] = 2671.84814; DeerInfo[deerid][dPosY] = -56.05173; DeerInfo[deerid][dPosZ] = 46.18007;   dRotX[deerid] = -3.05999; dRotY[deerid] = -0.24000; DeerInfo[deerid][dAngle] = -84; }
			case 25: { DeerInfo[deerid][dPosX] = 2672.52197; DeerInfo[deerid][dPosY] = -66.99289; DeerInfo[deerid][dPosZ] = 46.44852;   dRotX[deerid] = -3.05999; dRotY[deerid] = -0.24000; DeerInfo[deerid][dAngle] = -84; }
			case 26: { DeerInfo[deerid][dPosX] = 2671.83618; DeerInfo[deerid][dPosY] = -67.53899; DeerInfo[deerid][dPosZ] = 46.53901;   dRotX[deerid] = -3.05999; dRotY[deerid] = -4.68000; DeerInfo[deerid][dAngle] = -127; }
			case 27: { DeerInfo[deerid][dPosX] = 2665.96484; DeerInfo[deerid][dPosY] = -75.82954; DeerInfo[deerid][dPosZ] = 47.71147;   dRotX[deerid] = -3.05999; dRotY[deerid] = -4.68000; DeerInfo[deerid][dAngle] = -127; }
			case 28: { DeerInfo[deerid][dPosX] = 2665.31812; DeerInfo[deerid][dPosY] = -75.95398; DeerInfo[deerid][dPosZ] = 47.78548;   dRotX[deerid] = 1.32001; dRotY[deerid] = -4.68000; DeerInfo[deerid][dAngle] = -169; }
			case 29: { DeerInfo[deerid][dPosX] = 2657.62061; DeerInfo[deerid][dPosY] = -77.27112; DeerInfo[deerid][dPosZ] = 48.43702;   dRotX[deerid] = 1.32001; dRotY[deerid] = -4.68000; DeerInfo[deerid][dAngle] = -169; }
			case 30: { DeerInfo[deerid][dPosX] = 2656.92261; DeerInfo[deerid][dPosY] = -77.73275; DeerInfo[deerid][dPosZ] = 48.53560;   dRotX[deerid] = 1.20001; dRotY[deerid] = -5.28000; DeerInfo[deerid][dAngle] = -135; }
			case 31: { DeerInfo[deerid][dPosX] = 2650.01221; DeerInfo[deerid][dPosY] = -84.61140; DeerInfo[deerid][dPosZ] = 49.63452;   dRotX[deerid] = 1.20001; dRotY[deerid] = -5.28000; DeerInfo[deerid][dAngle] = -135; }
			case 32: { DeerInfo[deerid][dPosX] = 2650.09766; DeerInfo[deerid][dPosY] = -85.42272; DeerInfo[deerid][dPosZ] = 49.58298;   dRotX[deerid] = -2.63999; dRotY[deerid] = 4.49999; DeerInfo[deerid][dAngle] = -105; }
			case 33: { DeerInfo[deerid][dPosX] = 2649.36450; DeerInfo[deerid][dPosY] = -88.53782; DeerInfo[deerid][dPosZ] = 49.45716;   dRotX[deerid] = -2.63999; dRotY[deerid] = 4.49999; DeerInfo[deerid][dAngle] = -105; }
			case 34: { DeerInfo[deerid][dPosX] = 2650.31055; DeerInfo[deerid][dPosY] = -89.54640; DeerInfo[deerid][dPosZ] = 49.31068;   dRotX[deerid] = -1.13999; dRotY[deerid] = 5.21999; DeerInfo[deerid][dAngle] = -39; }
			case 35: { DeerInfo[deerid][dPosX] = 2662.95532; DeerInfo[deerid][dPosY] = -100.45724; DeerInfo[deerid][dPosZ] = 47.58412;   dRotX[deerid] = -1.13999; dRotY[deerid] = 5.21999; DeerInfo[deerid][dAngle] = -39; }
 			case 36: { DeerInfo[deerid][dPosX] = 2662.75391; DeerInfo[deerid][dPosY] = -101.23808; DeerInfo[deerid][dPosZ] = 47.56840;   dRotX[deerid] = -4.49999; dRotY[deerid] = 2.88000; DeerInfo[deerid][dAngle] = -110; }
			case 37: { DeerInfo[deerid][dPosX] = 2661.76172; DeerInfo[deerid][dPosY] = -104.00716; DeerInfo[deerid][dPosZ] = 47.30433;   dRotX[deerid] = -4.49999; dRotY[deerid] = 4.32000; DeerInfo[deerid][dAngle] = -110; }
			case 38: { DeerInfo[deerid][dPosX] = 2661.04980; DeerInfo[deerid][dPosY] = -104.99268; DeerInfo[deerid][dPosZ] = 47.13137;   dRotX[deerid] = -10.43999; dRotY[deerid] = 6.90000; DeerInfo[deerid][dAngle] = -135; }
			case 39: { DeerInfo[deerid][dPosX] = 2657.54395; DeerInfo[deerid][dPosY] = -108.58263; DeerInfo[deerid][dPosZ] = 46.46149;   dRotX[deerid] = -10.43999; dRotY[deerid] = 6.90000; DeerInfo[deerid][dAngle] = -135; }
			case 40: { DeerInfo[deerid][dPosX] = 2656.73145; DeerInfo[deerid][dPosY] = -107.81174; DeerInfo[deerid][dPosZ] = 46.65980;   dRotX[deerid] = -10.37999; dRotY[deerid] = -6.00000; DeerInfo[deerid][dAngle] = -197; }
			case 41: { DeerInfo[deerid][dPosX] = 2649.57544; DeerInfo[deerid][dPosY] = -105.55708; DeerInfo[deerid][dPosZ] = 47.38584;   dRotX[deerid] = -10.37999; dRotY[deerid] = -6.00000; DeerInfo[deerid][dAngle] = -197; }
			case 42: { DeerInfo[deerid][dPosX] = 2648.74707; DeerInfo[deerid][dPosY] = -106.04356; DeerInfo[deerid][dPosZ] = 47.30880;   dRotX[deerid] = -10.07999; dRotY[deerid] = 1.32000; DeerInfo[deerid][dAngle] = -155; }
			case 43: { DeerInfo[deerid][dPosX] = 2641.53638; DeerInfo[deerid][dPosY] = -109.55970; DeerInfo[deerid][dPosZ] = 46.74553;   dRotX[deerid] = -10.07999; dRotY[deerid] = 1.32000; DeerInfo[deerid][dAngle] = -155; }
			case 44: { DeerInfo[deerid][dPosX] = 2640.48022; DeerInfo[deerid][dPosY] = -109.50827; DeerInfo[deerid][dPosZ] = 46.81918;   dRotX[deerid] = -17.27999; dRotY[deerid] = -1.50000; DeerInfo[deerid][dAngle] = -174; }
			case 45: { DeerInfo[deerid][dPosX] = 2631.57617; DeerInfo[deerid][dPosY] = -110.54578; DeerInfo[deerid][dPosZ] = 46.91743;   dRotX[deerid] = -17.27999; dRotY[deerid] = -1.50000; DeerInfo[deerid][dAngle] = -174; }
			case 46: { DeerInfo[deerid][dPosX] = 2630.33398; DeerInfo[deerid][dPosY] = -109.96629; DeerInfo[deerid][dPosZ] = 47.03682;   dRotX[deerid] = -17.09999; dRotY[deerid] = -3.66001; DeerInfo[deerid][dAngle] = -209; }
			case 47: { DeerInfo[deerid][dPosX] = 2625.88232; DeerInfo[deerid][dPosY] = -107.32990; DeerInfo[deerid][dPosZ] = 47.51832;   dRotX[deerid] = -17.09999; dRotY[deerid] = -3.66001; DeerInfo[deerid][dAngle] = -209; }
			case 48: { DeerInfo[deerid][dPosX] = 2624.69971; DeerInfo[deerid][dPosY] = -106.89100; DeerInfo[deerid][dPosZ] = 47.62500;   dRotX[deerid] = -10.19999; dRotY[deerid] = -4.14001; DeerInfo[deerid][dAngle] = -227; }
			case 49: { DeerInfo[deerid][dPosX] = 2619.88794; DeerInfo[deerid][dPosY] = -101.99444; DeerInfo[deerid][dPosZ] = 48.74704;   dRotX[deerid] = -10.97999; dRotY[deerid] = -8.04000; DeerInfo[deerid][dAngle] = -227; }
			case 50: { DeerInfo[deerid][dPosX] = 2619.46899; DeerInfo[deerid][dPosY] = -100.84529; DeerInfo[deerid][dPosZ] = 49.03466; dRotX[deerid] = -4.25999; dRotY[deerid] = -8.39999; DeerInfo[deerid][dAngle] = -262; }
			case 51: { DeerInfo[deerid][dPosX] = 2618.80639; DeerInfo[deerid][dPosY] = -96.51197; DeerInfo[deerid][dPosZ] = 50.01615; dRotX[deerid] = -4.25999; dRotY[deerid] = -8.39999; DeerInfo[deerid][dAngle] = -262; }
			case 52: { DeerInfo[deerid][dPosX] = 2618.00170; DeerInfo[deerid][dPosY] = -95.63500; DeerInfo[deerid][dPosZ] = 50.21295; dRotX[deerid] = -4.25999; dRotY[deerid] = -8.39999; DeerInfo[deerid][dAngle] = -226; }
			case 53: { DeerInfo[deerid][dPosX] = 2610.79028; DeerInfo[deerid][dPosY] = -88.28977; DeerInfo[deerid][dPosZ] = 51.93861; dRotX[deerid] = -4.25999; dRotY[deerid] = -8.39999; DeerInfo[deerid][dAngle] = -226; }
			case 54: { DeerInfo[deerid][dPosX] = 2609.75463; DeerInfo[deerid][dPosY] = -88.54918; DeerInfo[deerid][dPosZ] = 51.93861; dRotX[deerid] = -4.25999; dRotY[deerid] = -8.39999; DeerInfo[deerid][dAngle] = -158; }
			case 55: { DeerInfo[deerid][dPosX] = 2596.15942; DeerInfo[deerid][dPosY] = -94.18435; DeerInfo[deerid][dPosZ] = 50.64329; dRotX[deerid] = -4.25999; dRotY[deerid] = -5.69999; DeerInfo[deerid][dAngle] = -158; }
			case 56: { DeerInfo[deerid][dPosX] = 2594.89208; DeerInfo[deerid][dPosY] = -94.95877; DeerInfo[deerid][dPosZ] = 50.51076; dRotX[deerid] = -4.19998; dRotY[deerid] = 7.85999; DeerInfo[deerid][dAngle] = -121; }
			case 57: { DeerInfo[deerid][dPosX] = 2591.27539; DeerInfo[deerid][dPosY] = -100.88503; DeerInfo[deerid][dPosZ] = 49.16416; dRotX[deerid] = -4.13998; dRotY[deerid] = 10.07999; DeerInfo[deerid][dAngle] = -121; }
			case 58: { DeerInfo[deerid][dPosX] = 2591.28491; DeerInfo[deerid][dPosY] = -102.02220; DeerInfo[deerid][dPosZ] = 49.07587; dRotX[deerid] = -2.87999; dRotY[deerid] = 2.70000; DeerInfo[deerid][dAngle] = -80; }
			case 59: { DeerInfo[deerid][dPosX] = 2593.67553; DeerInfo[deerid][dPosY] = -114.35605; DeerInfo[deerid][dPosZ] = 48.53514; dRotX[deerid] = -2.87999; dRotY[deerid] = 2.70000; DeerInfo[deerid][dAngle] = -80; }
			case 60: { DeerInfo[deerid][dPosX] = 2594.36547; DeerInfo[deerid][dPosY] = -115.02500; DeerInfo[deerid][dPosZ] = 48.47711; dRotX[deerid] = -2.87999; dRotY[deerid] = 2.70000; DeerInfo[deerid][dAngle] = -48; }
			case 61: { DeerInfo[deerid][dPosX] = 2600.59985; DeerInfo[deerid][dPosY] = -120.67787; DeerInfo[deerid][dPosZ] = 47.68722; dRotX[deerid] = -2.87999; dRotY[deerid] = 3.42000; DeerInfo[deerid][dAngle] = -42; }
			case 62: { DeerInfo[deerid][dPosX] = 2601.46752; DeerInfo[deerid][dPosY] = -122.11022; DeerInfo[deerid][dPosZ] = 47.50402; dRotX[deerid] = -2.87999; dRotY[deerid] = 3.42000; DeerInfo[deerid][dAngle] = -71; }
			case 63: { DeerInfo[deerid][dPosX] = 2599.95605; DeerInfo[deerid][dPosY] = -128.64845; DeerInfo[deerid][dPosZ] = 47.26441; dRotX[deerid] = -3.65999; dRotY[deerid] = -0.66000; DeerInfo[deerid][dAngle] = -114; }
			case 64: { DeerInfo[deerid][dPosX] = 2597.58544; DeerInfo[deerid][dPosY] = -134.74188; DeerInfo[deerid][dPosZ] = 47.11605; dRotX[deerid] = -3.65999; dRotY[deerid] = -0.66000; DeerInfo[deerid][dAngle] = -114; }
			case 65: { DeerInfo[deerid][dPosX] = 2596.19970; DeerInfo[deerid][dPosY] = -136.09812; DeerInfo[deerid][dPosZ] = 46.91688; dRotX[deerid] = -3.65999; dRotY[deerid] = 4.07999; DeerInfo[deerid][dAngle] = -134; }
			case 66: { DeerInfo[deerid][dPosX] = 2588.49365; DeerInfo[deerid][dPosY] = -143.51300; DeerInfo[deerid][dPosZ] = 45.80319; dRotX[deerid] = -4.13998; dRotY[deerid] = 6.23999; DeerInfo[deerid][dAngle] = -134; }
			case 67: { DeerInfo[deerid][dPosX] = 2587.63476; DeerInfo[deerid][dPosY] = -145.35188; DeerInfo[deerid][dPosZ] = 45.49325; dRotX[deerid] = -4.13998; dRotY[deerid] = 6.23999; DeerInfo[deerid][dAngle] = -127; }
			case 68: { DeerInfo[deerid][dPosX] = 2582.43872; DeerInfo[deerid][dPosY] = -151.58493; DeerInfo[deerid][dPosZ] = 44.66630; dRotX[deerid] = -4.13998; dRotY[deerid] = 6.23999; DeerInfo[deerid][dAngle] = -127; }
			case 69: { DeerInfo[deerid][dPosX] = 2581.18383; DeerInfo[deerid][dPosY] = -152.63520; DeerInfo[deerid][dPosZ] = 44.65623; dRotX[deerid] = -4.25999; dRotY[deerid] = -1.50000; DeerInfo[deerid][dAngle] = -158; }
			case 70: { DeerInfo[deerid][dPosX] = 2572.95239; DeerInfo[deerid][dPosY] = -155.74723; DeerInfo[deerid][dPosZ] = 44.81050; dRotX[deerid] = -1.79999; dRotY[deerid] = -1.37999; DeerInfo[deerid][dAngle] = -158; }
			case 71: { DeerInfo[deerid][dPosX] = 2571.87084; DeerInfo[deerid][dPosY] = -156.15025; DeerInfo[deerid][dPosZ] = 44.70478; dRotX[deerid] = -1.79999; dRotY[deerid] = 3.41999; DeerInfo[deerid][dAngle] = -188; }
			case 72: { DeerInfo[deerid][dPosX] = 2561.41650; DeerInfo[deerid][dPosY] = -154.31178; DeerInfo[deerid][dPosZ] = 44.60609; dRotX[deerid] = -5.33999; dRotY[deerid] = 2.33998; DeerInfo[deerid][dAngle] = -188; }
			case 73: { DeerInfo[deerid][dPosX] = 2560.50097; DeerInfo[deerid][dPosY] = -154.32893; DeerInfo[deerid][dPosZ] = 44.52899; dRotX[deerid] = -5.33999; dRotY[deerid] = 7.07998; DeerInfo[deerid][dAngle] = -167; }
			case 74: { DeerInfo[deerid][dPosX] = 2549.62353; DeerInfo[deerid][dPosY] = -156.86415; DeerInfo[deerid][dPosZ] = 42.88848; dRotX[deerid] = -5.33999; dRotY[deerid] = 7.07998; DeerInfo[deerid][dAngle] = -167; }
			case 75: { DeerInfo[deerid][dPosX] = 2548.52832; DeerInfo[deerid][dPosY] = -156.63807; DeerInfo[deerid][dPosZ] = 42.81653; dRotX[deerid] = -11.45998; dRotY[deerid] = -6.36001; DeerInfo[deerid][dAngle] = -208; }
			case 76: { DeerInfo[deerid][dPosX] = 2537.63720; DeerInfo[deerid][dPosY] = -150.58784; DeerInfo[deerid][dPosZ] = 42.97932; dRotX[deerid] = -11.45998; dRotY[deerid] = -6.36001; DeerInfo[deerid][dAngle] = -208; }
			case 77: { DeerInfo[deerid][dPosX] = 2537.68237; DeerInfo[deerid][dPosY] = -149.46693; DeerInfo[deerid][dPosZ] = 43.06766; dRotX[deerid] = -3.77999; dRotY[deerid] = -0.05999; DeerInfo[deerid][dAngle] = -255; }
			case 78: { DeerInfo[deerid][dPosX] = 2536.01782; DeerInfo[deerid][dPosY] = -144.08079; DeerInfo[deerid][dPosZ] = 43.08942; dRotX[deerid] = -3.77999; dRotY[deerid] = -0.05999; DeerInfo[deerid][dAngle] = -255; }
			case 79: { DeerInfo[deerid][dPosX] = 2536.35180; DeerInfo[deerid][dPosY] = -143.44023; DeerInfo[deerid][dPosZ] = 43.15948; dRotX[deerid] = -3.77999; dRotY[deerid] = -0.05999; DeerInfo[deerid][dAngle] = -272; }
			case 80: { DeerInfo[deerid][dPosX] = 2536.49316; DeerInfo[deerid][dPosY] = -132.06915; DeerInfo[deerid][dPosZ] = 43.59088; dRotX[deerid] = -3.77999; dRotY[deerid] = -0.05999; DeerInfo[deerid][dAngle] = -272; }
			case 81: { DeerInfo[deerid][dPosX] = 2536.37646; DeerInfo[deerid][dPosY] = -118.17244; DeerInfo[deerid][dPosZ] = 44.08673; dRotX[deerid] = -3.77999; dRotY[deerid] = -0.05999; DeerInfo[deerid][dAngle] = -272; }
			case 82: { DeerInfo[deerid][dPosX] = 2535.77246; DeerInfo[deerid][dPosY] = -116.89807; DeerInfo[deerid][dPosZ] = 44.07228; dRotX[deerid] = -4.19999; dRotY[deerid] = -1.01999; DeerInfo[deerid][dAngle] = -231; }
			case 83: { DeerInfo[deerid][dPosX] = 2532.02246; DeerInfo[deerid][dPosY] = -112.38382; DeerInfo[deerid][dPosZ] = 43.86986; dRotX[deerid] = -4.19999; dRotY[deerid] = -1.01999; DeerInfo[deerid][dAngle] = -231; }
			case 84: { DeerInfo[deerid][dPosX] = 2530.67895; DeerInfo[deerid][dPosY] = -111.24102; DeerInfo[deerid][dPosZ] = 43.59688; dRotX[deerid] = -9.35999; dRotY[deerid] = 3.05999; DeerInfo[deerid][dAngle] = -215; }
			case 85: { DeerInfo[deerid][dPosX] = 2521.71948; DeerInfo[deerid][dPosY] = -104.57465; DeerInfo[deerid][dPosZ] = 41.86584; dRotX[deerid] = -9.35999; dRotY[deerid] = 3.05999; DeerInfo[deerid][dAngle] = -215; }
			case 86: { DeerInfo[deerid][dPosX] = 2520.77001; DeerInfo[deerid][dPosY] = -104.10034; DeerInfo[deerid][dPosZ] = 41.66915; dRotX[deerid] = -9.11999; dRotY[deerid] = 13.31999; DeerInfo[deerid][dAngle] = -180; }
			case 87: { DeerInfo[deerid][dPosX] = 2510.82324; DeerInfo[deerid][dPosY] = -104.02976; DeerInfo[deerid][dPosZ] = 39.17530; dRotX[deerid] = -4.86000; dRotY[deerid] = 13.97999; DeerInfo[deerid][dAngle] = -180; }
			case 88: { DeerInfo[deerid][dPosX] = 2510.01440; DeerInfo[deerid][dPosY] = -104.17993; DeerInfo[deerid][dPosZ] = 38.99980; dRotX[deerid] = 9.11999; dRotY[deerid] = 16.86000; DeerInfo[deerid][dAngle] = -133; }
			case 89: { DeerInfo[deerid][dPosX] = 2505.83349; DeerInfo[deerid][dPosY] = -109.28880; DeerInfo[deerid][dPosZ] = 37.53525; dRotX[deerid] = 8.93999; dRotY[deerid] = 15.42000; DeerInfo[deerid][dAngle] = -133; }
			case 90: { DeerInfo[deerid][dPosX] = 2505.10473; DeerInfo[deerid][dPosY] = -109.58849; DeerInfo[deerid][dPosZ] = 37.34389; dRotX[deerid] = 9.84000; dRotY[deerid] = 7.73999; DeerInfo[deerid][dAngle] = -114; }
			case 91: { DeerInfo[deerid][dPosX] = 2504.03515; DeerInfo[deerid][dPosY] = -112.10675; DeerInfo[deerid][dPosZ] = 37.01488; dRotX[deerid] = 10.08001; dRotY[deerid] = 2.16000; DeerInfo[deerid][dAngle] = -114; }
			case 92: { DeerInfo[deerid][dPosX] = 2503.27612; DeerInfo[deerid][dPosY] = -112.94296; DeerInfo[deerid][dPosZ] = 37.00556; dRotX[deerid] = 10.44001; dRotY[deerid] = 3.00000; DeerInfo[deerid][dAngle] = -139; }
			case 93: { DeerInfo[deerid][dPosX] = 2491.49096; DeerInfo[deerid][dPosY] = -123.14055; DeerInfo[deerid][dPosZ] = 35.51430; dRotX[deerid] = 10.44001; dRotY[deerid] = 3.00000; DeerInfo[deerid][dAngle] = -139; }
			case 94: { DeerInfo[deerid][dPosX] = 2490.78930; DeerInfo[deerid][dPosY] = -124.01080; DeerInfo[deerid][dPosZ] = 35.43439; dRotX[deerid] = 10.44001; dRotY[deerid] = 3.00000; DeerInfo[deerid][dAngle] = -109; }
			case 95: { DeerInfo[deerid][dPosX] = 2487.86743; DeerInfo[deerid][dPosY] = -132.64521; DeerInfo[deerid][dPosZ] = 35.48571; dRotX[deerid] = 10.86001; dRotY[deerid] = 1.08000; DeerInfo[deerid][dAngle] = -109; }
			case 96: { DeerInfo[deerid][dPosX] = 2486.02343; DeerInfo[deerid][dPosY] = -134.34712; DeerInfo[deerid][dPosZ] = 35.29878; dRotX[deerid] = 10.86001; dRotY[deerid] = 1.08000; DeerInfo[deerid][dAngle] = -124; }
			case 97: { DeerInfo[deerid][dPosX] = 2479.69213; DeerInfo[deerid][dPosY] = -143.78703; DeerInfo[deerid][dPosZ] = 34.93877; dRotX[deerid] = 10.86001; dRotY[deerid] = 1.08000; DeerInfo[deerid][dAngle] = -124; }
			case 98: { DeerInfo[deerid][dPosX] = 2478.84277; DeerInfo[deerid][dPosY] = -143.69108; DeerInfo[deerid][dPosZ] = 34.77093; dRotX[deerid] = -7.91999; dRotY[deerid] = 10.43999; DeerInfo[deerid][dAngle] = -206; }
			case 99: { DeerInfo[deerid][dPosX] = 2474.98608; DeerInfo[deerid][dPosY] = -141.78663; DeerInfo[deerid][dPosZ] = 33.95402; dRotX[deerid] = -7.91999; dRotY[deerid] = 10.43999; DeerInfo[deerid][dAngle] = -206; }
			case 100: { DeerInfo[deerid][dPosX] = 2474.44531; DeerInfo[deerid][dPosY] = -140.84849; DeerInfo[deerid][dPosZ] = 33.78915; dRotX[deerid] = -7.85999; dRotY[deerid] = 9.89999; DeerInfo[deerid][dAngle] = -248; }
			case 101: { DeerInfo[deerid][dPosX] = 2470.77661; DeerInfo[deerid][dPosY] = -131.76986; DeerInfo[deerid][dPosZ] = 32.40346; dRotX[deerid] = -7.85999; dRotY[deerid] = 9.89999; DeerInfo[deerid][dAngle] = -248; }
			case 102: { DeerInfo[deerid][dPosX] = 2470.31469; DeerInfo[deerid][dPosY] = -130.70838; DeerInfo[deerid][dPosZ] = 32.21041; dRotX[deerid] = -7.85999; dRotY[deerid] = 9.89999; DeerInfo[deerid][dAngle] = -232; }
			case 103: { DeerInfo[deerid][dPosX] = 2465.53564; DeerInfo[deerid][dPosY] = -124.35212; DeerInfo[deerid][dPosZ] = 30.93375; dRotX[deerid] = -7.85999; dRotY[deerid] = 9.89999; DeerInfo[deerid][dAngle] = -232; }
			case 104: { DeerInfo[deerid][dPosX] = 2464.59936; DeerInfo[deerid][dPosY] = -123.76693; DeerInfo[deerid][dPosZ] = 30.73290; dRotX[deerid] = -7.37999; dRotY[deerid] = 10.14000; DeerInfo[deerid][dAngle] = -205; }
			case 105: { DeerInfo[deerid][dPosX] = 2459.21313; DeerInfo[deerid][dPosY] = -121.78517; DeerInfo[deerid][dPosZ] = 30.09070; dRotX[deerid] = -5.69998; dRotY[deerid] = 10.56000; DeerInfo[deerid][dAngle] = -205; }
			case 106: { DeerInfo[deerid][dPosX] = 2457.70605; DeerInfo[deerid][dPosY] = -121.44214; DeerInfo[deerid][dPosZ] = 30.00490; dRotX[deerid] = -6.23999; dRotY[deerid] = 8.81999; DeerInfo[deerid][dAngle] = -176; }
			case 107: { DeerInfo[deerid][dPosX] = 2449.92407; DeerInfo[deerid][dPosY] = -122.26674; DeerInfo[deerid][dPosZ] = 29.76207; dRotX[deerid] = -4.85999; dRotY[deerid] = 1.74000; DeerInfo[deerid][dAngle] = -176; }
			case 108: { DeerInfo[deerid][dPosX] = 2448.55444; DeerInfo[deerid][dPosY] = -123.24578; DeerInfo[deerid][dPosZ] = 29.92836; dRotX[deerid] = -6.41999; dRotY[deerid] = -6.71999; DeerInfo[deerid][dAngle] = -133; }
			case 109: { DeerInfo[deerid][dPosX] = 2442.79492; DeerInfo[deerid][dPosY] = -129.35693; DeerInfo[deerid][dPosZ] = 30.47867; dRotX[deerid] = -6.35999; dRotY[deerid] = -3.24000; DeerInfo[deerid][dAngle] = -133; }
			case 110: { DeerInfo[deerid][dPosX] = 2442.53881; DeerInfo[deerid][dPosY] = -130.31105; DeerInfo[deerid][dPosZ] = 30.55817; dRotX[deerid] = -0.83999; dRotY[deerid] = -2.09999; DeerInfo[deerid][dAngle] = -107; }
			case 111: { DeerInfo[deerid][dPosX] = 2439.65991; DeerInfo[deerid][dPosY] = -140.33532; DeerInfo[deerid][dPosZ] = 31.44639; dRotX[deerid] = -0.83999; dRotY[deerid] = -2.09999; DeerInfo[deerid][dAngle] = -107; }
			case 112: { DeerInfo[deerid][dPosX] = 2440.38964; DeerInfo[deerid][dPosY] = -140.93861; DeerInfo[deerid][dPosZ] = 31.50333; dRotX[deerid] = -4.37999; dRotY[deerid] = -3.29999; DeerInfo[deerid][dAngle] = -32; }
			case 113: { DeerInfo[deerid][dPosX] = 2446.32348; DeerInfo[deerid][dPosY] = -144.78923; DeerInfo[deerid][dPosZ] = 31.92716; dRotX[deerid] = -4.37999; dRotY[deerid] = -3.29999; DeerInfo[deerid][dAngle] = -32; }
			case 114: { DeerInfo[deerid][dPosX] = 2446.39550; DeerInfo[deerid][dPosY] = -146.02839; DeerInfo[deerid][dPosZ] = 32.05562; dRotX[deerid] = -4.37999; dRotY[deerid] = -6.84000; DeerInfo[deerid][dAngle] = -72; }
			case 115: { DeerInfo[deerid][dPosX] = 2447.27294; DeerInfo[deerid][dPosY] = -148.68705; DeerInfo[deerid][dPosZ] = 32.29579; dRotX[deerid] = -4.37999; dRotY[deerid] = -6.84000; DeerInfo[deerid][dAngle] = -72; }
			case 116: { DeerInfo[deerid][dPosX] = 2447.00903; DeerInfo[deerid][dPosY] = -149.90608; DeerInfo[deerid][dPosZ] = 32.22430; dRotX[deerid] = -4.43999; dRotY[deerid] = -2.16001; DeerInfo[deerid][dAngle] = -119; }
			case 117: { DeerInfo[deerid][dPosX] = 2443.72045; DeerInfo[deerid][dPosY] = -155.84869; DeerInfo[deerid][dPosZ] = 31.54649; dRotX[deerid] = -4.43999; dRotY[deerid] = -2.16001; DeerInfo[deerid][dAngle] = -119; }
			case 118: { DeerInfo[deerid][dPosX] = 2442.21191; DeerInfo[deerid][dPosY] = -156.50488; DeerInfo[deerid][dPosZ] = 31.22656; dRotX[deerid] = -8.27999; dRotY[deerid] = 0.77999; DeerInfo[deerid][dAngle] = -168; }
			case 119: { DeerInfo[deerid][dPosX] = 2425.07177; DeerInfo[deerid][dPosY] = -159.53218; DeerInfo[deerid][dPosZ] = 28.31998; dRotX[deerid] = -8.27999; dRotY[deerid] = 6.53998; DeerInfo[deerid][dAngle] = -168; }
			case 120: { DeerInfo[deerid][dPosX] = 2423.64160; DeerInfo[deerid][dPosY] = -160.02537; DeerInfo[deerid][dPosZ] = 28.02206; dRotX[deerid] = -8.69999; dRotY[deerid] = 7.61998; DeerInfo[deerid][dAngle] = -159; }
			case 121: { DeerInfo[deerid][dPosX] = 2409.44531; DeerInfo[deerid][dPosY] = -165.09223; DeerInfo[deerid][dPosZ] = 25.57662; dRotX[deerid] = -8.21998; dRotY[deerid] = 8.99999; DeerInfo[deerid][dAngle] = -159; }
			case 122: { DeerInfo[deerid][dPosX] = 2408.32031; DeerInfo[deerid][dPosY] = -164.91943; DeerInfo[deerid][dPosZ] = 25.51085; dRotX[deerid] = -8.21998; dRotY[deerid] = 8.99999; DeerInfo[deerid][dAngle] = -171; }
			case 123: { DeerInfo[deerid][dPosX] = 2397.32177; DeerInfo[deerid][dPosY] = -166.53723; DeerInfo[deerid][dPosZ] = 24.24925; dRotX[deerid] = -8.21998; dRotY[deerid] = 9.47999; DeerInfo[deerid][dAngle] = -171; }
			case 124: { DeerInfo[deerid][dPosX] = 2396.09326; DeerInfo[deerid][dPosY] = -166.26344; DeerInfo[deerid][dPosZ] = 24.25414; dRotX[deerid] = -10.13998; dRotY[deerid] = -0.78000; DeerInfo[deerid][dAngle] = -185; }
			case 125: { DeerInfo[deerid][dPosX] = 2388.53369; DeerInfo[deerid][dPosY] = -165.71829; DeerInfo[deerid][dPosZ] = 24.11477; dRotX[deerid] = -10.13998; dRotY[deerid] = -0.78000; DeerInfo[deerid][dAngle] = -185; }
			case 126: { DeerInfo[deerid][dPosX] = 2386.99194; DeerInfo[deerid][dPosY] = -166.04019; DeerInfo[deerid][dPosZ] = 23.99626; dRotX[deerid] = -10.07999; dRotY[deerid] = 1.73998; DeerInfo[deerid][dAngle] = -166; }
			case 127: { DeerInfo[deerid][dPosX] = 2383.84228; DeerInfo[deerid][dPosY] = -166.90702; DeerInfo[deerid][dPosZ] = 23.75530; dRotX[deerid] = -10.07999; dRotY[deerid] = 5.87999; DeerInfo[deerid][dAngle] = -166; }
			case 128: { DeerInfo[deerid][dPosX] = 2382.74584; DeerInfo[deerid][dPosY] = -166.71067; DeerInfo[deerid][dPosZ] = 23.73751; dRotX[deerid] = -10.13998; dRotY[deerid] = 2.45999; DeerInfo[deerid][dAngle] = -168; }
			case 129: { DeerInfo[deerid][dPosX] = 2372.46582; DeerInfo[deerid][dPosY] = -168.65765; DeerInfo[deerid][dPosZ] = 23.05898; dRotX[deerid] = -10.13998; dRotY[deerid] = 2.45999; DeerInfo[deerid][dAngle] = -168; }
			case 130: { DeerInfo[deerid][dPosX] = 2371.47851; DeerInfo[deerid][dPosY] = -168.61965; DeerInfo[deerid][dPosZ] = 23.05898; dRotX[deerid] = -10.13998; dRotY[deerid] = 2.45999; DeerInfo[deerid][dAngle] = -191; }
			case 131: { DeerInfo[deerid][dPosX] = 2365.12866; DeerInfo[deerid][dPosY] = -167.47142; DeerInfo[deerid][dPosZ] = 23.07854; dRotX[deerid] = -10.13998; dRotY[deerid] = 2.45999; DeerInfo[deerid][dAngle] = -191; }
			case 132: { DeerInfo[deerid][dPosX] = 2364.04516; DeerInfo[deerid][dPosY] = -167.75756; DeerInfo[deerid][dPosZ] = 22.99175; dRotX[deerid] = -10.13998; dRotY[deerid] = 2.45999; DeerInfo[deerid][dAngle] = -159; }
			case 133: { DeerInfo[deerid][dPosX] = 2354.81518; DeerInfo[deerid][dPosY] = -171.49359; DeerInfo[deerid][dPosZ] = 22.08930; dRotX[deerid] = -9.95998; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -159; }
			case 134: { DeerInfo[deerid][dPosX] = 2353.49414; DeerInfo[deerid][dPosY] = -171.82061; DeerInfo[deerid][dPosZ] = 22.01137; dRotX[deerid] = -9.95998; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -163; }
			case 135: { DeerInfo[deerid][dPosX] = 2344.24853; DeerInfo[deerid][dPosY] = -174.45986; DeerInfo[deerid][dPosZ] = 21.25470; dRotX[deerid] = -9.95998; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -163; }
			case 136: { DeerInfo[deerid][dPosX] = 2340.77807; DeerInfo[deerid][dPosY] = -176.09478; DeerInfo[deerid][dPosZ] = 20.89743; dRotX[deerid] = -9.95998; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -153; }
			case 137: { DeerInfo[deerid][dPosX] = 2339.30175; DeerInfo[deerid][dPosY] = -176.71565; DeerInfo[deerid][dPosZ] = 20.76782; dRotX[deerid] = -7.73999; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -146; }
			case 138: { DeerInfo[deerid][dPosX] = 2329.28759; DeerInfo[deerid][dPosY] = -183.30232; DeerInfo[deerid][dPosZ] = 18.77449; dRotX[deerid] = -7.73999; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -146; }
			case 139: { DeerInfo[deerid][dPosX] = 2328.14477; DeerInfo[deerid][dPosY] = -183.13330; DeerInfo[deerid][dPosZ] = 18.72977; dRotX[deerid] = -7.73999; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -184; }
			case 140: { DeerInfo[deerid][dPosX] = 2313.44555; DeerInfo[deerid][dPosY] = -182.13671; DeerInfo[deerid][dPosZ] = 17.87009; dRotX[deerid] = -7.73999; dRotY[deerid] = 4.67998; DeerInfo[deerid][dAngle] = -184; }
			case 141: { DeerInfo[deerid][dPosX] = 2312.78784; DeerInfo[deerid][dPosY] = -182.36279; DeerInfo[deerid][dPosZ] = 17.77474; dRotX[deerid] = -8.09998; dRotY[deerid] = 10.73999; DeerInfo[deerid][dAngle] = -152; }
			case 142: { DeerInfo[deerid][dPosX] = 2304.83349; DeerInfo[deerid][dPosY] = -186.08064; DeerInfo[deerid][dPosZ] = 16.42948; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -152; }
			case 143: { DeerInfo[deerid][dPosX] = 2303.89184; DeerInfo[deerid][dPosY] = -186.13243; DeerInfo[deerid][dPosZ] = 16.36981; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -172; }
			case 144: { DeerInfo[deerid][dPosX] = 2296.78173; DeerInfo[deerid][dPosY] = -187.08811; DeerInfo[deerid][dPosZ] = 15.55331; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -172; }
			case 145: { DeerInfo[deerid][dPosX] = 2295.78393; DeerInfo[deerid][dPosY] = -187.17114; DeerInfo[deerid][dPosZ] = 15.43739; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -185; }
			case 146: { DeerInfo[deerid][dPosX] = 2285.97045; DeerInfo[deerid][dPosY] = -186.29956; DeerInfo[deerid][dPosZ] = 14.59988; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -185; }
			case 147: { DeerInfo[deerid][dPosX] = 2285.11669; DeerInfo[deerid][dPosY] = -186.64657; DeerInfo[deerid][dPosZ] = 14.44826; dRotX[deerid] = -7.97999; dRotY[deerid] = 8.09998; DeerInfo[deerid][dAngle] = -149; }
			case 148: { DeerInfo[deerid][dPosX] = 2280.37084; DeerInfo[deerid][dPosY] = -189.51124; DeerInfo[deerid][dPosZ] = 13.65981; dRotX[deerid] = -2.57998; dRotY[deerid] = 12.59998; DeerInfo[deerid][dAngle] = -149; }
			case 149: { DeerInfo[deerid][dPosX] = 2279.67773; DeerInfo[deerid][dPosY] = -190.33743; DeerInfo[deerid][dPosZ] = 13.33889; dRotX[deerid] = -2.75998; dRotY[deerid] = 12.89999; DeerInfo[deerid][dAngle] = -115; }
			case 150: { DeerInfo[deerid][dPosX] = 2278.14648; DeerInfo[deerid][dPosY] = -193.95150; DeerInfo[deerid][dPosZ] = 12.25070; dRotX[deerid] = -2.75998; dRotY[deerid] = 12.89999; DeerInfo[deerid][dAngle] = -115; }
			case 151: { DeerInfo[deerid][dPosX] = 2274.86523; DeerInfo[deerid][dPosY] = -201.07478; DeerInfo[deerid][dPosZ] = 10.05323; dRotX[deerid] = -0.47999; dRotY[deerid] = 16.43998; DeerInfo[deerid][dAngle] = -115; }
			case 152: { DeerInfo[deerid][dPosX] = 2274.49975; DeerInfo[deerid][dPosY] = -202.81599; DeerInfo[deerid][dPosZ] = 9.61373; dRotX[deerid] = 8.64000; dRotY[deerid] = 7.43999; DeerInfo[deerid][dAngle] = -70; }
			case 153: { DeerInfo[deerid][dPosX] = 2275.49389; DeerInfo[deerid][dPosY] = -205.66705; DeerInfo[deerid][dPosZ] = 9.24969; dRotX[deerid] = 8.64000; dRotY[deerid] = 6.23999; DeerInfo[deerid][dAngle] = -70; }
			case 154: { DeerInfo[deerid][dPosX] = 2276.51074; DeerInfo[deerid][dPosY] = -206.64399; DeerInfo[deerid][dPosZ] = 9.52231; dRotX[deerid] = 5.70001; dRotY[deerid] = -16.86001; DeerInfo[deerid][dAngle] = -48; }
			case 155: { DeerInfo[deerid][dPosX] = 2284.78222; DeerInfo[deerid][dPosY] = -216.09704; DeerInfo[deerid][dPosZ] = 11.92792; dRotX[deerid] = 5.76001; dRotY[deerid] = -15.48001; DeerInfo[deerid][dAngle] = -48; }
			case 156: { DeerInfo[deerid][dPosX] = 2284.83959; DeerInfo[deerid][dPosY] = -217.11396; DeerInfo[deerid][dPosZ] = 11.87287; dRotX[deerid] = 5.40002; dRotY[deerid] = -4.14000; DeerInfo[deerid][dAngle] = -98; }
			case 157: { DeerInfo[deerid][dPosX] = 2284.08520; DeerInfo[deerid][dPosY] = -223.15388; DeerInfo[deerid][dPosZ] = 11.16536; dRotX[deerid] = 3.48002; dRotY[deerid] = -4.98001; DeerInfo[deerid][dAngle] = -98; }
			case 158: { DeerInfo[deerid][dPosX] = 2284.28515; DeerInfo[deerid][dPosY] = -224.25152; DeerInfo[deerid][dPosZ] = 11.14900; dRotX[deerid] = 0.96002; dRotY[deerid] = -4.50001; DeerInfo[deerid][dAngle] = -74; }
			case 159: { DeerInfo[deerid][dPosX] = 2288.19873; DeerInfo[deerid][dPosY] = -237.98321; DeerInfo[deerid][dPosZ] = 10.91351; dRotX[deerid] = 0.96002; dRotY[deerid] = -4.50001; DeerInfo[deerid][dAngle] = -74; }
			case 160: { DeerInfo[deerid][dPosX] = 2288.52246; DeerInfo[deerid][dPosY] = -239.09414; DeerInfo[deerid][dPosZ] = 10.75364; dRotX[deerid] = 1.08001; dRotY[deerid] = 11.87998; DeerInfo[deerid][dAngle] = -63; }
			case 161: { DeerInfo[deerid][dPosX] = 2291.86352; DeerInfo[deerid][dPosY] = -245.46980; DeerInfo[deerid][dPosZ] = 9.32501; dRotX[deerid] = 1.08001; dRotY[deerid] = 14.27999; DeerInfo[deerid][dAngle] = -63; }
			case 162: { DeerInfo[deerid][dPosX] = 2292.54101; DeerInfo[deerid][dPosY] = -246.29479; DeerInfo[deerid][dPosZ] = 9.38607; dRotX[deerid] = 1.50002; dRotY[deerid] = -2.22001; DeerInfo[deerid][dAngle] = -46; }
			case 163: { DeerInfo[deerid][dPosX] = 2301.43627; DeerInfo[deerid][dPosY] = -255.46516; DeerInfo[deerid][dPosZ] = 10.18424; dRotX[deerid] = 1.50002; dRotY[deerid] = -2.22001; DeerInfo[deerid][dAngle] = -46; }
			case 164: { DeerInfo[deerid][dPosX] = 2302.77734; DeerInfo[deerid][dPosY] = -255.42829; DeerInfo[deerid][dPosZ] = 10.27311; dRotX[deerid] = 1.50002; dRotY[deerid] = -2.22001; DeerInfo[deerid][dAngle] = 41; }
			case 165: { DeerInfo[deerid][dPosX] = 2305.53735; DeerInfo[deerid][dPosY] = -252.99261; DeerInfo[deerid][dPosZ] = 10.53254; dRotX[deerid] = 1.50002; dRotY[deerid] = -2.22001; DeerInfo[deerid][dAngle] = 41; }
			case 166: { DeerInfo[deerid][dPosX] = 2306.23291; DeerInfo[deerid][dPosY] = -252.01535; DeerInfo[deerid][dPosZ] = 10.69367; dRotX[deerid] = -3.95998; dRotY[deerid] = -3.42001; DeerInfo[deerid][dAngle] = 74; }
			case 167: { DeerInfo[deerid][dPosX] = 2309.06274; DeerInfo[deerid][dPosY] = -242.13209; DeerInfo[deerid][dPosZ] = 11.66335; dRotX[deerid] = -3.95998; dRotY[deerid] = -3.42001; DeerInfo[deerid][dAngle] = 74; }
			case 168: { DeerInfo[deerid][dPosX] = 2309.49487; DeerInfo[deerid][dPosY] = -241.31919; DeerInfo[deerid][dPosZ] = 11.81112; dRotX[deerid] = -3.95998; dRotY[deerid] = -3.00001; DeerInfo[deerid][dAngle] = 58; }
			case 169: { DeerInfo[deerid][dPosX] = 2314.54516; DeerInfo[deerid][dPosY] = -233.36502; DeerInfo[deerid][dPosZ] = 13.28713; dRotX[deerid] = -3.95998; dRotY[deerid] = -3.00001; DeerInfo[deerid][dAngle] = 58; }
			case 170: { DeerInfo[deerid][dPosX] = 2315.03051; DeerInfo[deerid][dPosY] = -232.60914; DeerInfo[deerid][dPosZ] = 13.42173; dRotX[deerid] = -6.77998; dRotY[deerid] = -2.40001; DeerInfo[deerid][dAngle] = 75; }
			case 171: { DeerInfo[deerid][dPosX] = 2317.24438; DeerInfo[deerid][dPosY] = -221.93078; DeerInfo[deerid][dPosZ] = 14.27017; dRotX[deerid] = -6.77998; dRotY[deerid] = -2.40001; DeerInfo[deerid][dAngle] = 75; }
			case 172: { DeerInfo[deerid][dPosX] = 2317.72143; DeerInfo[deerid][dPosY] = -221.38592; DeerInfo[deerid][dPosZ] = 14.39663; dRotX[deerid] = -6.29998; dRotY[deerid] = -10.68000; DeerInfo[deerid][dAngle] = 46; }
			case 173: { DeerInfo[deerid][dPosX] = 2323.34082; DeerInfo[deerid][dPosY] = -215.35737; DeerInfo[deerid][dPosZ] = 16.00658; dRotX[deerid] = -6.29998; dRotY[deerid] = -10.68000; DeerInfo[deerid][dAngle] = 46; }
			case 174: { DeerInfo[deerid][dPosX] = 2324.46435; DeerInfo[deerid][dPosY] = -214.48112; DeerInfo[deerid][dPosZ] = 16.12384; dRotX[deerid] = 0.30002; dRotY[deerid] = -10.20001; DeerInfo[deerid][dAngle] = 34; }
			case 175: { DeerInfo[deerid][dPosX] = 2330.82397; DeerInfo[deerid][dPosY] = -210.06398; DeerInfo[deerid][dPosZ] = 16.77477; dRotX[deerid] = 0.30002; dRotY[deerid] = -10.20001; DeerInfo[deerid][dAngle] = 34; }
			case 176: { DeerInfo[deerid][dPosX] = 2331.60156; DeerInfo[deerid][dPosY] = -209.80049; DeerInfo[deerid][dPosZ] = 16.84456; dRotX[deerid] = 0.30002; dRotY[deerid] = -10.20001; DeerInfo[deerid][dAngle] = 14; }
			case 177: { DeerInfo[deerid][dPosX] = 2339.52807; DeerInfo[deerid][dPosY] = -208.12852; DeerInfo[deerid][dPosZ] = 17.71772; dRotX[deerid] = 0.30002; dRotY[deerid] = -10.20001; DeerInfo[deerid][dAngle] = 14; }
			case 178: { DeerInfo[deerid][dPosX] = 2340.99926; DeerInfo[deerid][dPosY] = -207.38873; DeerInfo[deerid][dPosZ] = 17.75925; dRotX[deerid] = 6.24001; dRotY[deerid] = -1.74001; DeerInfo[deerid][dAngle] = 32; }
			case 179: { DeerInfo[deerid][dPosX] = 2352.38818; DeerInfo[deerid][dPosY] = -200.24063; DeerInfo[deerid][dPosZ] = 17.64896; dRotX[deerid] = 6.24001; dRotY[deerid] = -1.74001; DeerInfo[deerid][dAngle] = 32; }
			case 180: { DeerInfo[deerid][dPosX] = 2353.19995; DeerInfo[deerid][dPosY] = -200.28369; DeerInfo[deerid][dPosZ] = 17.59462; dRotX[deerid] = 6.24001; dRotY[deerid] = 3.17999; DeerInfo[deerid][dAngle] = 1; }
			case 181: { DeerInfo[deerid][dPosX] = 2364.73681; DeerInfo[deerid][dPosY] = -200.35263; DeerInfo[deerid][dPosZ] = 17.47575; dRotX[deerid] = 6.24001; dRotY[deerid] = 3.17999; DeerInfo[deerid][dAngle] = 1; }
			case 182: { DeerInfo[deerid][dPosX] = 2365.70312; DeerInfo[deerid][dPosY] = -200.80313; DeerInfo[deerid][dPosZ] = 17.41793; dRotX[deerid] = 10.14002; dRotY[deerid] = 5.09998; DeerInfo[deerid][dAngle] = -37; }
			case 183: { DeerInfo[deerid][dPosX] = 2372.17187; DeerInfo[deerid][dPosY] = -205.78541; DeerInfo[deerid][dPosZ] = 16.76684; dRotX[deerid] = 10.14002; dRotY[deerid] = 5.09998; DeerInfo[deerid][dAngle] = -37; }
			case 184: { DeerInfo[deerid][dPosX] = 2373.05102; DeerInfo[deerid][dPosY] = -205.57890; DeerInfo[deerid][dPosZ] = 16.82150; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 23; }
			case 185: { DeerInfo[deerid][dPosX] = 2380.65502; DeerInfo[deerid][dPosY] = -202.43377; DeerInfo[deerid][dPosZ] = 17.40903; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 23; }
			case 186: { DeerInfo[deerid][dPosX] = 2381.82226; DeerInfo[deerid][dPosY] = -201.82652; DeerInfo[deerid][dPosZ] = 17.52057; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 48; }
			case 187: { DeerInfo[deerid][dPosX] = 2387.28442; DeerInfo[deerid][dPosY] = -196.14710; DeerInfo[deerid][dPosZ] = 18.65254; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 48; }
			case 188: { DeerInfo[deerid][dPosX] = 2388.37451; DeerInfo[deerid][dPosY] = -195.63960; DeerInfo[deerid][dPosZ] = 18.71246; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 21; }
			case 189: { DeerInfo[deerid][dPosX] = 2397.82690; DeerInfo[deerid][dPosY] = -191.97073; DeerInfo[deerid][dPosZ] = 19.31077; dRotX[deerid] = 10.14002; dRotY[deerid] = -1.62001; DeerInfo[deerid][dAngle] = 21; }
			case 190: { DeerInfo[deerid][dPosX] = 2398.81884; DeerInfo[deerid][dPosY] = -192.08309; DeerInfo[deerid][dPosZ] = 19.31077; dRotX[deerid] = 12.84002; dRotY[deerid] = -2.16001; DeerInfo[deerid][dAngle] = -6; }
			case 191: { DeerInfo[deerid][dPosX] = 2409.09960; DeerInfo[deerid][dPosY] = -193.43937; DeerInfo[deerid][dPosZ] = 19.77042; dRotX[deerid] = 12.84002; dRotY[deerid] = -2.16001; DeerInfo[deerid][dAngle] = -6; }
			case 192: { DeerInfo[deerid][dPosX] = 2418.15039; DeerInfo[deerid][dPosY] = -194.97946; DeerInfo[deerid][dPosZ] = 20.21224; dRotX[deerid] = 12.84002; dRotY[deerid] = -2.16001; DeerInfo[deerid][dAngle] = -6; }
			case 193: { DeerInfo[deerid][dPosX] = 2419.60205; DeerInfo[deerid][dPosY] = -195.14175; DeerInfo[deerid][dPosZ] = 20.29295; dRotX[deerid] = 10.80002; dRotY[deerid] = -7.02000; DeerInfo[deerid][dAngle] = 10; }
			case 194: { DeerInfo[deerid][dPosX] = 2429.98803; DeerInfo[deerid][dPosY] = -193.29344; DeerInfo[deerid][dPosZ] = 21.64151; dRotX[deerid] = 10.80002; dRotY[deerid] = -7.02000; DeerInfo[deerid][dAngle] = 10; }
			case 195: { DeerInfo[deerid][dPosX] = 2431.18188; DeerInfo[deerid][dPosY] = -193.06091; DeerInfo[deerid][dPosZ] = 21.82379; dRotX[deerid] = 10.80002; dRotY[deerid] = -7.02000; DeerInfo[deerid][dAngle] = 19; }
			case 196: { DeerInfo[deerid][dPosX] = 2441.12939; DeerInfo[deerid][dPosY] = -190.02001; DeerInfo[deerid][dPosZ] = 23.46080; dRotX[deerid] = 10.80002; dRotY[deerid] = -7.02000; DeerInfo[deerid][dAngle] = 19; }
			case 197: { DeerInfo[deerid][dPosX] = 2442.20239; DeerInfo[deerid][dPosY] = -189.39601; DeerInfo[deerid][dPosZ] = 23.69249; dRotX[deerid] = 12.48001; dRotY[deerid] = -13.02000; DeerInfo[deerid][dAngle] = 38; }
			case 198: { DeerInfo[deerid][dPosX] = 2449.42456; DeerInfo[deerid][dPosY] = -184.51985; DeerInfo[deerid][dPosZ] = 25.54833; dRotX[deerid] = 12.48001; dRotY[deerid] = -13.02000; DeerInfo[deerid][dAngle] = 38; }
			case 199: { DeerInfo[deerid][dPosX] = 2450.44018; DeerInfo[deerid][dPosY] = -184.39566; DeerInfo[deerid][dPosZ] = 25.68427; dRotX[deerid] = 12.54001; dRotY[deerid] = -6.90001; DeerInfo[deerid][dAngle] = -7; }
			case 200: { DeerInfo[deerid][dPosX] = 2457.45629; DeerInfo[deerid][dPosY] = -184.91279; DeerInfo[deerid][dPosZ] = 26.17804; dRotX[deerid] = 12.54001; dRotY[deerid] = -6.90001; DeerInfo[deerid][dAngle] = -7; }
			case 201: { DeerInfo[deerid][dPosX] = 2458.28564; DeerInfo[deerid][dPosY] = -185.93519; DeerInfo[deerid][dPosZ] = 26.03973; dRotX[deerid] = 12.54001; dRotY[deerid] = 1.55999; DeerInfo[deerid][dAngle] = -53; }
			case 202: { DeerInfo[deerid][dPosX] = 2463.67211; DeerInfo[deerid][dPosY] = -192.92005; DeerInfo[deerid][dPosZ] = 25.67951; dRotX[deerid] = 12.54001; dRotY[deerid] = 1.55999; DeerInfo[deerid][dAngle] = -53; }
			case 203: { DeerInfo[deerid][dPosX] = 2464.77392; DeerInfo[deerid][dPosY] = -194.09690; DeerInfo[deerid][dPosZ] = 25.64105; dRotX[deerid] = 12.72002; dRotY[deerid] = -6.48001; DeerInfo[deerid][dAngle] = -34; }
			case 204: { DeerInfo[deerid][dPosX] = 2475.96875; DeerInfo[deerid][dPosY] = -202.29981; DeerInfo[deerid][dPosZ] = 25.85514; dRotX[deerid] = 12.72002; dRotY[deerid] = -6.48001; DeerInfo[deerid][dAngle] = -34; }
			case 205: { DeerInfo[deerid][dPosX] = 2477.10937; DeerInfo[deerid][dPosY] = -202.61711; DeerInfo[deerid][dPosZ] = 25.95870; dRotX[deerid] = 12.72002; dRotY[deerid] = -6.48001; DeerInfo[deerid][dAngle] = -10; }
			case 206: { DeerInfo[deerid][dPosX] = 2490.87744; DeerInfo[deerid][dPosY] = -205.46015; DeerInfo[deerid][dPosZ] = 26.72550; dRotX[deerid] = 12.72002; dRotY[deerid] = -6.48001; DeerInfo[deerid][dAngle] = -10; }
			case 207: { DeerInfo[deerid][dPosX] = 2492.01464; DeerInfo[deerid][dPosY] = -205.25910; DeerInfo[deerid][dPosZ] = 26.84650; dRotX[deerid] = 9.30002; dRotY[deerid] = -6.30001; DeerInfo[deerid][dAngle] = 22; }
			case 208: { DeerInfo[deerid][dPosX] = 2504.73925; DeerInfo[deerid][dPosY] = -200.48213; DeerInfo[deerid][dPosZ] = 28.64715; dRotX[deerid] = 9.30002; dRotY[deerid] = -6.30001; DeerInfo[deerid][dAngle] = 22; }
			case 209: { DeerInfo[deerid][dPosX] = 2505.59228; DeerInfo[deerid][dPosY] = -199.72883; DeerInfo[deerid][dPosZ] = 28.84613; dRotX[deerid] = 9.60002; dRotY[deerid] = -15.06000; DeerInfo[deerid][dAngle] = 52; }
			case 210: { DeerInfo[deerid][dPosX] = 2512.37890; DeerInfo[deerid][dPosY] = -191.75511; DeerInfo[deerid][dPosZ] = 32.14788; dRotX[deerid] = 2.64002; dRotY[deerid] = -15.30000; DeerInfo[deerid][dAngle] = 52; }
			case 211: { DeerInfo[deerid][dPosX] = 2513.35424; DeerInfo[deerid][dPosY] = -191.37696; DeerInfo[deerid][dPosZ] = 32.31951; dRotX[deerid] = 8.34002; dRotY[deerid] = -6.60000; DeerInfo[deerid][dAngle] = 14; }
			case 212: { DeerInfo[deerid][dPosX] = 2518.54443; DeerInfo[deerid][dPosY] = -189.71998; DeerInfo[deerid][dPosZ] = 33.12514; dRotX[deerid] = 8.34002; dRotY[deerid] = -6.60000; DeerInfo[deerid][dAngle] = 14; }
			case 213: { DeerInfo[deerid][dPosX] = 2520.11938; DeerInfo[deerid][dPosY] = -189.33288; DeerInfo[deerid][dPosZ] = 33.35007; dRotX[deerid] = 8.28003; dRotY[deerid] = -2.70001; DeerInfo[deerid][dAngle] = -9; }
			case 214: { DeerInfo[deerid][dPosX] = 2529.74584; DeerInfo[deerid][dPosY] = -190.90597; DeerInfo[deerid][dPosZ] = 34.02753; dRotX[deerid] = 8.28003; dRotY[deerid] = -2.70001; DeerInfo[deerid][dAngle] = -9; }
			case 215: { DeerInfo[deerid][dPosX] = 2540.48437; DeerInfo[deerid][dPosY] = -192.58911; DeerInfo[deerid][dPosZ] = 34.79064; dRotX[deerid] = 8.28003; dRotY[deerid] = -2.70001; DeerInfo[deerid][dAngle] = -9; }
			case 216: { DeerInfo[deerid][dPosX] = 2540.92407; DeerInfo[deerid][dPosY] = -193.39665; DeerInfo[deerid][dPosZ] = 34.71166; dRotX[deerid] = 7.62002; dRotY[deerid] = 3.71999; DeerInfo[deerid][dAngle] = -85; }
			case 217: { DeerInfo[deerid][dPosX] = 2541.83300; DeerInfo[deerid][dPosY] = -200.48831; DeerInfo[deerid][dPosZ] = 33.51343; dRotX[deerid] = 7.50003; dRotY[deerid] = 10.07999; DeerInfo[deerid][dAngle] = -85; }
			case 218: { DeerInfo[deerid][dPosX] = 2542.65332; DeerInfo[deerid][dPosY] = -201.80635; DeerInfo[deerid][dPosZ] = 33.37802; dRotX[deerid] = 6.36003; dRotY[deerid] = 2.51998; DeerInfo[deerid][dAngle] = -42; }
			case 219: { DeerInfo[deerid][dPosX] = 2547.94628; DeerInfo[deerid][dPosY] = -206.59831; DeerInfo[deerid][dPosZ] = 33.05300; dRotX[deerid] = 6.36003; dRotY[deerid] = 2.51998; DeerInfo[deerid][dAngle] = -42; }
			case 220: { DeerInfo[deerid][dPosX] = 2548.44702; DeerInfo[deerid][dPosY] = -205.69615; DeerInfo[deerid][dPosZ] = 33.27906; dRotX[deerid] = 8.10002; dRotY[deerid] = -12.12001; DeerInfo[deerid][dAngle] = 49; }
			case 221: { DeerInfo[deerid][dPosX] = 2551.11083; DeerInfo[deerid][dPosY] = -202.94970; DeerInfo[deerid][dPosZ] = 33.96543; dRotX[deerid] = 6.12002; dRotY[deerid] = -12.12001; DeerInfo[deerid][dAngle] = 49; }
			case 222: { DeerInfo[deerid][dPosX] = 2552.19335; DeerInfo[deerid][dPosY] = -202.30702; DeerInfo[deerid][dPosZ] = 34.12625; dRotX[deerid] = 6.06002; dRotY[deerid] = -8.64000; DeerInfo[deerid][dAngle] = 20; }
			case 223: { DeerInfo[deerid][dPosX] = 2561.37231; DeerInfo[deerid][dPosY] = -199.39179; DeerInfo[deerid][dPosZ] = 35.06594; dRotX[deerid] = 6.06002; dRotY[deerid] = -8.64000; DeerInfo[deerid][dAngle] = 20; }
			case 224: { DeerInfo[deerid][dPosX] = 2562.42968; DeerInfo[deerid][dPosY] = -199.65046; DeerInfo[deerid][dPosZ] = 35.09960; dRotX[deerid] = 6.24002; dRotY[deerid] = -2.34000; DeerInfo[deerid][dAngle] = -21; }
			case 225: { DeerInfo[deerid][dPosX] = 2577.85205; DeerInfo[deerid][dPosY] = -205.47059; DeerInfo[deerid][dPosZ] = 35.68629; dRotX[deerid] = 8.64002; dRotY[deerid] = -2.10000; DeerInfo[deerid][dAngle] = -21; }
			case 226: { DeerInfo[deerid][dPosX] = 2579.44848; DeerInfo[deerid][dPosY] = -205.32746; DeerInfo[deerid][dPosZ] = 35.93264; dRotX[deerid] = 8.88002; dRotY[deerid] = -9.72000; DeerInfo[deerid][dAngle] = 34; }
			case 227: { DeerInfo[deerid][dPosX] = 2591.52246; DeerInfo[deerid][dPosY] = -198.02142; DeerInfo[deerid][dPosZ] = 38.93613; dRotX[deerid] = 8.88002; dRotY[deerid] = -9.72000; DeerInfo[deerid][dAngle] = 34; }
			case 228: { DeerInfo[deerid][dPosX] = 2592.04345; DeerInfo[deerid][dPosY] = -196.82649; DeerInfo[deerid][dPosZ] = 39.13901; dRotX[deerid] = -5.93997; dRotY[deerid] = -12.24001; DeerInfo[deerid][dAngle] = 91; }
			case 229: { DeerInfo[deerid][dPosX] = 2591.36596; DeerInfo[deerid][dPosY] = -175.54631; DeerInfo[deerid][dPosZ] = 41.52780; dRotX[deerid] = -5.93997; dRotY[deerid] = -12.24001; DeerInfo[deerid][dAngle] = 91; }
		    //case : { DeerInfo[deerid][dPosX] = ; DeerInfo[deerid][dPosY] = ; DeerInfo[deerid][dPosZ] = ; dRotX[deerid] = ; dRotY[deerid] = ; DeerInfo[deerid][dAngle] = ; }
		}
	}
	if(DeerInfo[deerid][dDirection])//Backwards
	{
	    DeerInfo[deerid][dAngle] -= 180;
	    dRotX[deerid] *= -1;
	    dRotY[deerid] *= -1;
	}
}

stock ShowSkinningKnifeDialog(playerid)
{
	ShowInventoryTextdraw(playerid, 0);
	CancelSelectTextDraw(playerid);
	new string[118], deerid = GetPVarInt(playerid, "Deer");
    switch(DeerInfo[deerid][dCondition] )
    {//Playing Hours - 0(not looted), 1(skinned), 2(meat taken), 3(horns taken), 4(all taken)
        case 0: string = "1. Skin the deer.\n2. Remove and take the Meat.\n3. Remove and take the Deer Antlers.";
        case 1: string = "1. Skin the deer. (Skinned)\n2. Remove and take the Meat.\n3. Remove and take the Deer Antlers.";
        case 2: string = "1. Skin the deer. (Skinned)\n2. Remove and take the Meat. (Taken)\n3. Remove and take the Deer Antlers.";
        case 3: string = "1. Skin the deer. (Skinned)\n2. Remove and take the Meat.\n3. Remove and take the Deer Antlers.";
        case 4: string = "1. Skin the deer. (Skinned)\n2. Remove and take the Meat. (Taken)\n3. Remove and take the Deer Antlers.";
	}
	if(!DeerInfo[deerid][dAntlers])
	{
	    strcat(string, " (Not Present)");
	}
	else if(DeerInfo[deerid][dCondition] > 2)
	{
	    strcat(string, " (Taken)");
	}
	Dialog_Show(playerid, DeerKnife, DIALOG_STYLE_LIST, "Pilih yang ingin dilakukan :", string, "Pilih", "Batal");
	if(GetPlayerAnimationIndex(playerid) != 165)
	{
		ApplyAnimation(playerid, "BOMBER", "BOM_Plant_Crouch_In",1.1,0,1,1,1,0,1);
	}
	SetPlayerArmedWeapon(playerid, 0);
}