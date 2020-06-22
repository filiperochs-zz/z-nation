/*--------------------------------------------------------------------------*\
                *******************************************
                 Round GangZone - Criar GangZones redondas.
                *******************************************
Descricao:

	Esta include é usada pra criar gang zones redondas
	Lembrando que a definição SIZE_GANG_ZONE indica a quantidade
	de GangZones normais que será usada em cada Round GangZone.
	(Não coloque um valor muito alto, pois pode exceder o limite de GangZones)

Natives:

	native CreateRoundGangZone(Float:x, Float:y, Float:size);
	native FlashRoundGangZoneForAll(zoneid, flashcolor);
	native FlashRoundGangZoneForPlayer(playerid, zoneid, flashcolor);
	native StopFlashRoundGangZoneForAll(zoneid);
	native SetRoundGangZonePos(zoneid, Float:x, Float:y);
	native StopFlashRoundGangZoneForPlayer(playerid, zoneid);
	native ShowRoundGangZoneForPlayer(playerid, zoneid, color);
	native HideRoundGangZoneForPlayer(playerid, zoneid);
	native ShowRoundGangZoneForAll(zoneid, color);
	native HideRoundGangZoneForAll(zoneid);
	native IsValidRoundGangZone(zoneid);
	native DestroyRoundGangZone(zoneid);
\*--------------------------------------------------------------------------*/

#if defined roung_gz_include
	#endinput
#endif
#define roung_gz_include

#include <a_samp>

// Numero de GangZones que será usado em cada Round GZ
#define SIZE_GANG_ZONE  	     	(4)
// Numero máximo de Round GZ
#define MAX_ROUND_GANG_ZONES     	(2)
// Round GZ Inválida
#define INVALID_ROUND_GANG_ZONE  	(-1)

enum g_RoundGangZoneEnum {

	rgzValid,
	rgzZones[SIZE_GANG_ZONE],
	Float:rgzSize,
}
static rGangZoneInfo[MAX_ROUND_GANG_ZONES][g_RoundGangZoneEnum];

// Funções

stock CreateRoundGangZone(Float:x, Float:y, Float:size, Float:extrasize = -1.0) {

	for(new zones; zones != MAX_ROUND_GANG_ZONES; zones++) {

	    if (!rGangZoneInfo[zones][rgzValid]) {

			rGangZoneInfo[zones][rgzValid]  = 1;
	        rGangZoneInfo[zones][rgzSize]   = size;

			for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
			    rGangZoneInfo[zones][rgzZones][rzones] = -1;
			}

	        InvRoundGangZone(zones, size, x, y, extrasize);

	        return zones;
	    }
	}
	print("Warning: Excedido o limite de Round Gang Zones!");
	return INVALID_ROUND_GANG_ZONE;
}

stock IsValidRoundGangZone(zoneid) {

	if (zoneid < 0 || zoneid >= MAX_ROUND_GANG_ZONES) {
	    return 0;
	}
	return rGangZoneInfo[zoneid][rgzValid];
}

stock DestroyRoundGangZone(zoneid) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneHideForAll(rGangZoneInfo[zoneid][rgzZones][rzones]);
		    GangZoneDestroy(rGangZoneInfo[zoneid][rgzZones][rzones]);
		}
		rGangZoneInfo[zoneid][rgzValid] = 0;

	    return 1;
	}
	return 0;
}

stock SetRoundGangZonePos(zoneid, Float:x, Float:y) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneDestroy(rGangZoneInfo[zoneid][rgzZones][rzones]);
		}

		RoundGangZone(zoneid, rGangZoneInfo[zoneid][rgzSize], x, y);

	    return 1;
	}
	return 0;
}

stock ShowRoundGangZoneForPlayer(playerid, zoneid, color) {

	if (IsValidRoundGangZone(zoneid) && IsPlayerConnected(playerid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneShowForPlayer(playerid, rGangZoneInfo[zoneid][rgzZones][rzones], color);
		}
	    return 1;
	}
	return 0;
}

stock HideRoundGangZoneForPlayer(playerid, zoneid) {

	if (IsValidRoundGangZone(zoneid) && IsPlayerConnected(playerid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneHideForPlayer(playerid, rGangZoneInfo[zoneid][rgzZones][rzones]);
		}
	    return 1;
	}
	return 0;
}

stock ShowRoundGangZoneForAll(zoneid, color) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneShowForAll(rGangZoneInfo[zoneid][rgzZones][rzones], color);
		}
	    return 1;
	}
	return 0;
}

stock HideRoundGangZoneForAll(zoneid) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneHideForAll(rGangZoneInfo[zoneid][rgzZones][rzones]);
		}
	    return 1;
	}
	return 0;
}

stock FlashRoundGangZoneForAll(zoneid, flashcolor) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneFlashForAll(rGangZoneInfo[zoneid][rgzZones][rzones], flashcolor);
		}
	    return 1;
	}
	return 0;
}

stock FlashRoundGangZoneForPlayer(playerid, zoneid, flashcolor) {

	if (IsValidRoundGangZone(zoneid) && IsPlayerConnected(playerid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneFlashForPlayer(playerid, rGangZoneInfo[zoneid][rgzZones][rzones], flashcolor);
		}
	    return 1;
	}
	return 0;
}

stock StopFlashRoundGangZoneForAll(zoneid) {

	if (IsValidRoundGangZone(zoneid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneStopFlashForAll(rGangZoneInfo[zoneid][rgzZones][rzones]);
		}
	    return 1;
	}
	return 0;
}

stock StopFlashRoundGangZoneForPlayer(playerid, zoneid) {

	if (IsValidRoundGangZone(zoneid) && IsPlayerConnected(playerid)) {

		for(new rzones; rzones != SIZE_GANG_ZONE; rzones++) {
		    GangZoneStopFlashForPlayer(playerid, rGangZoneInfo[zoneid][rgzZones][rzones]);
		}
	    return 1;
	}
	return 0;
}

// Criado por Nero_3D

stock InvRoundGangZone(zoneid, Float: radius, Float: X, Float: Y, Float:extra_size = -1.0, size = SIZE_GANG_ZONE) {

	new Float:minX = X - (radius + extra_size) ;
	new Float:minY = Y - (radius + extra_size) ;
	new Float:maxX = X + (radius + extra_size) ;
	new Float:maxY = Y + (radius + extra_size) ;

	if (extra_size == -1.0) {
		minX = -3100.0 ;
		minY = -3100.0 ;
		maxX = 3100.0 ;
		maxY = 3100.0 ;
	}

	rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X + radius, minY, maxX, maxY);
    rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(minX, minY, X - radius, maxY);

    new
        Float: inc = 360.0 / (size - 1),
        Float: deg = inc,
        Float: cos,
        Float: sin
    ;
    maxX = radius;

    while(size > 5) {

        cos = floatcos(deg, degrees) * radius;
        sin = floatsin(deg, degrees) * radius;

        rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X + cos, Y + sin, X + maxX, maxY);
        rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X + cos, minY, X + maxX, Y - sin);

        rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X - maxX, Y + sin, X - cos, maxY);
        rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X - maxX, minY, X - cos, Y - sin);

        maxX = cos;
        deg += inc;
    }
    rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X - maxX, Y + radius, X + maxX, maxY);
    rGangZoneInfo[zoneid][rgzZones][--size] = GangZoneCreate(X - maxX, minY, X + maxX, Y - radius);

    return size; // if you use an array with base 4 (4 * x) this should be 0, if not than there weren't enough gang zones available
}
