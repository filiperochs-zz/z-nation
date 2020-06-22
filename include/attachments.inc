#include <a_samp>


enum E_ENUM_ATTACH {
		E_PLAYER_ATTACH_MODEL,
		E_PLAYER_ATTACH_BONE,
Float:  E_PLAYER_ATTACH_X,
Float:  E_PLAYER_ATTACH_Y,
Float:  E_PLAYER_ATTACH_Z,
Float:  E_PLAYER_ATTACH_RX,
Float:  E_PLAYER_ATTACH_RY,
Float:  E_PLAYER_ATTACH_RZ,
Float:  E_PLAYER_ATTACH_SX,
Float:  E_PLAYER_ATTACH_SY,
Float:  E_PLAYER_ATTACH_SZ,
		E_PLAYER_ATTACH_COLOR1,
		E_PLAYER_ATTACH_COLOR2,
}
new
	p_AttachmentsInfo[MAX_PLAYERS][10][E_ENUM_ATTACH];
	
stock s_SetPlayerAttachedObject(playerid, index, modelid, bone, Float:fOffsetX = 0.0, Float:fOffsetY = 0.0, Float:fOffsetZ = 0.0, Float:fRotX = 0.0, Float:fRotY = 0.0, Float:fRotZ = 0.0, Float:fScaleX = 1.0, Float:fScaleY = 1.0, Float:fScaleZ = 1.0, materialcolor1 = 0, materialcolor2 = 0)
{
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_MODEL] = modelid;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_BONE] = bone;
    
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_X] = fOffsetX;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_Y] = fOffsetY;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_Z] = fOffsetZ;
    
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RX] = fRotX;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RY] = fRotY;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RZ] = fRotZ;
    
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SX] = fScaleX;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SY] = fScaleY;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SZ] = fScaleZ;
    
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_COLOR1] = materialcolor1;
    p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_COLOR2] = materialcolor2;
    
	return SetPlayerAttachedObject(playerid, index, modelid, bone, fOffsetX, fOffsetY, fOffsetZ, fRotX, fRotY, fRotZ, fScaleX, fScaleY, fScaleZ, materialcolor1, materialcolor2);
}

stock GetPlayerAttachedObject(playerid, index, &modelid, &bone, &Float:fX, &Float:fY, &Float:fZ, &Float:fRotX, &Float:fRotY, &Float:fRotZ, &Float:fScaleX, &Float:fScaleY, &Float:fScaleZ, &materialcolor1, &materialcolor2)
{
    modelid = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_MODEL];
    bone = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_BONE];

    fX = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_X];
    fY = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_Y];
    fZ = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_Z];

    fRotX = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RX];
    fRotY = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RY];
    fRotZ = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_RZ];

    fScaleX = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SX];
    fScaleY = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SY];
    fScaleZ = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_SZ];

    materialcolor1 = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_COLOR1];
    materialcolor2 = p_AttachmentsInfo[playerid][index][E_PLAYER_ATTACH_COLOR2];
}

#define exSetPlayerAttachedObject SetPlayerAttachedObject

#if defined _ALS_SetPlayerAttachedObject
	#undef SetPlayerAttachedObject
#else
	#define _ALS_SetPlayerAttachedObject
#endif
#define SetPlayerAttachedObject s_SetPlayerAttachedObject


