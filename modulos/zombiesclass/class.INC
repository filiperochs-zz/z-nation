// Zombies Classes enum

#define max_classes 75

new index_class = 0;
new index_bandidos = 0;

enum {
	zombie_class_normal,
	zombie_class_shovel,
	zombie_class_knifer,
	zombie_class_serra,
	zombie_class_bomber,
	zombie_class_bandido,
	zombie_class_tanker,
	zombie_class_wolf,
	zombie_class_flamer,
}

enum zombieClassEnumInfo {

	// Class id
	zombie_class_id,
	
	// Skin da class
	zombie_class_skin,
	
	// Resistencia do zombie
	Float:zombie_class_resistence,
	
	// Visão do zombie
	Float:zombie_class_detection,
	
	// Alcance do zombie/bandido
	Float:zombie_class_rangeattack,
	
	// Delay tiro
	zombie_class_shootdelay,
	
	// Arma do zombie
	zombie_class_weapon,
	
	// type movement
	zombie_class_movtype,
	
	// Velocidade movimento
	Float:zombie_class_movspeed,
	
	// Damage
	Float:zombie_class_damage,
	
	// walk anim
	zombie_class_wanimlib[9],
	zombie_class_wanimname[20],
	
	// run anim
	zombie_class_ranimlib[9],
	zombie_class_ranimname[20],
	
	// exp
	zombie_class_exp,
}
new ZombieClassInfo[max_classes][zombieClassEnumInfo];
	
stock AddZombieClass(
	classid,
	skinid,
	Float:resistence,
	weaponid,
	Float:detection = 30.0,
	Float:rangeattack = 0.6,
	shootdelay = 100,
	movtype = MOVE_TYPE_RUN,
	Float:movspeed = 0.28444,
	Float:damage = 3.4000,
	wanimlib[] = "PED",
	wanimname[] = "WALK_old",
	ranimlib[] = "PED",
	ranimname[] = "run_old",
	experience = 250)
{
    ZombieClassInfo[index_class][zombie_class_id] = classid;
    ZombieClassInfo[index_class][zombie_class_resistence] = resistence;
    ZombieClassInfo[index_class][zombie_class_skin] = skinid;
    ZombieClassInfo[index_class][zombie_class_weapon] = weaponid;
    ZombieClassInfo[index_class][zombie_class_detection] = detection;
    ZombieClassInfo[index_class][zombie_class_rangeattack] = rangeattack;
    ZombieClassInfo[index_class][zombie_class_shootdelay] = shootdelay;
    ZombieClassInfo[index_class][zombie_class_movtype] = movtype;
    ZombieClassInfo[index_class][zombie_class_movspeed] = movspeed;
    ZombieClassInfo[index_class][zombie_class_damage] = damage;
    ZombieClassInfo[index_class][zombie_class_exp] = experience;
    format(ZombieClassInfo[index_class][zombie_class_wanimlib], 9, wanimlib);
    format(ZombieClassInfo[index_class][zombie_class_wanimname], 20, wanimname);
    format(ZombieClassInfo[index_class][zombie_class_ranimlib], 9, ranimlib);
    format(ZombieClassInfo[index_class][zombie_class_ranimname], 20, ranimname);

	index_class ++;
	
	if (classid == zombie_class_bandido) {
	    index_bandidos ++;
	}
}


//ZombieInfo[npcid][zombie_class_defalt]

SetupZombiesClasses() {

	//                    classid           skin    vida   weap  detection
	// Zombies Normais
    AddZombieClass(zombie_class_normal,     25001,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25002,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25003,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25004,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25005,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25006,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25007,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25008,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25009,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25010,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25011,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25012,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25013,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25014,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25015,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25016,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25019,  75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal,     25020,  75.0, 	0,   30.0);

	// Zombies com Serra
    AddZombieClass(zombie_class_serra,  	25018, 	400.0, 	9, 	 55.0, 		 .damage = 19.0, .experience = 900);
    AddZombieClass(zombie_class_serra,  	25018, 	500.0, 	9, 	 55.0, 		 .damage = 19.0, .experience = 900);
    AddZombieClass(zombie_class_serra,  	25018, 	300.0, 	9, 	 55.0, 		 .damage = 19.0, .experience = 900);

	// Zombie tanque
	AddZombieClass(zombie_class_tanker,  	25021, 	800.0, 	0, 	 40.0, 		 .damage = 9.0, .wanimlib = "PED", 	.wanimname = "WALK_fatold", 	.ranimlib = "PED", 	.ranimname = "run_fatold", .experience = 1000);
	AddZombieClass(zombie_class_tanker,  	25021, 	800.0, 	0, 	 40.0, 		 .damage = 9.0, .wanimlib = "PED", 	.wanimname = "WALK_fatold", 	.ranimlib = "PED", 	.ranimname = "run_fatold", .experience = 1000);

	// Zombie lobos
//	AddZombieClass(zombie_class_wolf,  		25024, 	50.0, 	0,   50.0, 		 .movtype = MOVE_TYPE_RUN, .movspeed = 0.586784, .damage = 12.0, .wanimlib = "PED", .wanimname = "WALK_fatold", .ranimlib = "PED", .ranimname = "woman_runpanic", .experience = 450);

	// Zombie flamer
	AddZombieClass(zombie_class_flamer,  	25023, 	500.0, 	37,  30.0, 		 .rangeattack = 7.0, .damage = 0.04, .experience = 600);

    // Zombies que explodem
    AddZombieClass(zombie_class_bomber, 	25017, 	425.0,  0, 	 45.0,  	 .movtype = MOVE_TYPE_RUN, .movspeed = 0.386784, .experience = 680);
//                                                                           alcance do disparo    shoot delay
    // Bandidos
    AddZombieClass(zombie_class_bandido, 	29, 	70.0,   22,  42.0,     	 .rangeattack = 25.0,  .shootdelay = 150, .experience = 450);
    AddZombieClass(zombie_class_bandido, 	100, 	70.0,   31,  45.0,     	 .rangeattack = 35.0,  .shootdelay = 100, .experience = 450);
    AddZombieClass(zombie_class_bandido, 	29, 	70.0,   30,  45.0,     	 .rangeattack = 33.0,  .shootdelay = 100, .experience = 450);
    AddZombieClass(zombie_class_bandido, 	128, 	70.0,   22,  45.0,     	 .rangeattack = 25.0,  .shootdelay = 150, .experience = 450);
    AddZombieClass(zombie_class_bandido, 	179, 	70.0,   33,  70.0,     	 .rangeattack = 60.0,  .shootdelay = -1, .experience = 450);
}

/*
stock SetupZombiesClasses() {

	//                    classid           skin    vida   weap  detection
	// Zombies Normais
    AddZombieClass(zombie_class_normal,     054,  	75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal, 	077,  	75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal, 	078,  	75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal, 	079,  	75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal, 	197, 	75.0, 	0,   30.0);
    AddZombieClass(zombie_class_normal, 	200, 	75.0, 	0,   30.0);
    
    // Zombies com Shovel
//  AddZombieClass(zombie_class_shovel, 	129, 	100.0,  6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	130, 	100.0,  6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	136, 	100.0, 	6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	159, 	100.0, 	6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	160, 	100.0, 	6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	196, 	100.0, 	6, 	 35.0);
    AddZombieClass(zombie_class_shovel, 	239, 	100.0, 	6, 	 35.0);
    
    // Zombies com Knife
    //AddZombieClass(zombie_class_knifer, 	134, 	150.0, 	4, 	 40.0);
    AddZombieClass(zombie_class_knifer, 	137, 	150.0, 	4, 	 40.0);
    AddZombieClass(zombie_class_knifer, 	162, 	150.0, 	4, 	 40.0);
    
	// Zombies com Serra
    AddZombieClass(zombie_class_serra,  	135, 	400.0, 	9, 	 55.0);
    AddZombieClass(zombie_class_serra,  	168, 	500.0, 	9, 	 55.0);
    AddZombieClass(zombie_class_serra,  	213, 	300.0, 	9, 	 55.0);
    
    // Zombies que explodem
    AddZombieClass(zombie_class_bomber, 	129, 	425.0,  0, 	 45.0,  	 .movtype = MOVE_TYPE_RUN, .movspeed = 0.38444);
//                                                                           alcance do disparo    shoot delay
    // Bandidos
    AddZombieClass(zombie_class_bandido, 	29, 	70.0,   22,  42.0,     	 .rangeattack = 25.0,  .shootdelay = 150);
    AddZombieClass(zombie_class_bandido, 	100, 	70.0,   31,  45.0,     	 .rangeattack = 35.0,  .shootdelay = 100);
    AddZombieClass(zombie_class_bandido, 	29, 	70.0,   30,  45.0,     	 .rangeattack = 33.0,  .shootdelay = 100);
    AddZombieClass(zombie_class_bandido, 	128, 	70.0,   22,  45.0,     	 .rangeattack = 25.0,  .shootdelay = 150);
    AddZombieClass(zombie_class_bandido, 	179, 	70.0,   33,  70.0,     	 .rangeattack = 60.0,  .shootdelay = -1);
}

*/
