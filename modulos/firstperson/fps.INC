
enum
{
    FPS_CAMERA_MODE_NONE,
	CAMERA_MODE_STAND,
	CAMERA_MODE_CROUCH,
	CAMERA_MODE_CROUCH_MOVE
}

new
		fps_ObjectID[MAX_PLAYERS],
		fps_Active[MAX_PLAYERS],
		fps_Timer[MAX_PLAYERS],
		fps_CameraMode[MAX_PLAYERS];

stock ActivePlayerFPS(playerid) {

    if(fps_Active[playerid]) return 0;

	fps_ObjectID[playerid] = CreateObject(19300, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0);
	AttachObjectToPlayer(fps_ObjectID[playerid], playerid, 0.0, 0.18, 0.85, 0.0, 0.0, 0.0);
	SetCameraMode(playerid, CAMERA_MODE_STAND);
	fps_Active[playerid] = true;
	fps_Timer[playerid] = SetTimerEx("UpdateFirstPerson", 200, true, "i", playerid);
	
	return 1;
}

stock DisablePlayerFPS(playerid) {

    if(!fps_Active[playerid]) return 0;

	DestroyObject(fps_ObjectID[playerid]);
	SetCameraBehindPlayer(playerid);
	fps_Active[playerid] = false;
	KillTimer(fps_Timer[playerid]);

	return 1;
}

Float:GetPlayerSpeed(playerid)
{
	new
		Float:vx,
		Float:vy,
		Float:vz;

	GetPlayerVelocity(playerid, vx, vy, vz);

	return floatsqroot( (vx*vx)+(vy*vy)+(vz*vz) );
}

callback UpdateFirstPerson(playerid)
{
	if(GetPlayerSpecialAction(playerid) == SPECIAL_ACTION_DUCK || GetPlayerAnimationIndex(playerid) == 164)
	{
		if(GetPlayerSpeed(playerid) > 0.0)
		{
			SetCameraMode(playerid, CAMERA_MODE_CROUCH_MOVE);
		}
		else
		{
			SetCameraMode(playerid, CAMERA_MODE_CROUCH);
		}
	}
	else
	{
		SetCameraMode(playerid, CAMERA_MODE_STAND);
	}
}

SetCameraMode(playerid, smode)
{
	if(fps_CameraMode[playerid] != smode) {

		fps_CameraMode[playerid] = smode;

		switch(smode)
		{
			case CAMERA_MODE_STAND:
				AttachObjectToPlayer(fps_ObjectID[playerid], playerid, 0.0, 0.18, 0.85, 0.0, 0.0, 0.0);

			case CAMERA_MODE_CROUCH:
				AttachObjectToPlayer(fps_ObjectID[playerid], playerid, 0.1, 0.25, 0.2, 0.0, 0.0, 0.0);

			case CAMERA_MODE_CROUCH_MOVE:
				AttachObjectToPlayer(fps_ObjectID[playerid], playerid, 0.1, 0.3, 0.3, 0.0, 0.0, 0.0);
		}
	}
	
	AttachCameraToObject(playerid, fps_ObjectID[playerid]);

	return 1;
}
