/*************************************************************
*
* Solution   : Mafia 2 Multiplayer
* Project    : Shared Library
* File       : CGame.cpp
* Developers : AaronLad <aaron@m2-multiplayer.com>
*			   h0pk1nz <> (Vehicle Model names)
*			   Tyldar <tyldar@mafia2-online.com> (Weapon names)
*
***************************************************************/

#include "CGame.h"
#include "CLogFile.h"
#include "Math/CMaths.h"
#include "SharedUtility.h"

static char * PlayerModels[][2] =
{
	// Player
	{ "/sds/player/", "vitarmy" },		{ "/sds/player/", "vitksl" },		{ "/sds/player/", "vitksl2" },
	{ "/sds/player/", "vitnah_t" },		{ "/sds/player/", "vitod1" },		{ "/sds/player/", "vitod1neup" },
	{ "/sds/player/", "vitod2" },		{ "/sds/player/", "vitol1" },		{ "/sds/player/", "vitol2" },
	{ "/sds/player/", "vitoveral" },	{ "/sds/player/", "vitpra" },		{ "/sds/player/", "vitspo" },
	{ "/sds/player/", "vittel" },		{ "/sds/player/", "vitukl" },		{ "/sds/player/", "vitukl_kn" },
	{ "/sds/player/", "vitvez" },		{ "/sds/player/", "vitvop" },		{ "/sds/player/", "vitvov" },
	{ "/sds/player/", "vitvov2i" },		{ "/sds/player/", "vitvov3" },

	// Mission Characters
	{ "/sds/hchar/", "albert" },		{ "/sds/hchar/", "brianc" },		{ "/sds/hchar/", "consig" },
	{ "/sds/hchar/", "derek" },			{ "/sds/hchar/", "desmond" },		{ "/sds/hchar/", "joeoblf" },
	{ "/sds/hchar/", "eddies" },		{ "/sds/hchar/", "franca" },		{ "/sds/hchar/", "frank" },
	{ "/sds/hchar/", "joebryl" },		{ "/sds/hchar/", "joeciv" },		{ "/sds/hchar/", "joeneup" },
	{ "/sds/hchar/", "joeobl" },		{ "/sds/hchar/", "leospo" },		{ "/sds/hchar/", "steve" },
	{ "/sds/hchar/", "joeruka" },		{ "/sds/hchar/", "marty" },

	// Traffic
	{ "/sds/traffic/", "cbarma" },		{ "/sds/traffic/", "cbarma2" },		{ "/sds/traffic/", "ccerb1" },
	{ "/sds/traffic/", "ccerb2" },		{ "/sds/traffic/", "ccerb3" },		{ "/sds/traffic/", "ccerml" },
	{ "/sds/traffic/", "ccerml2" },		{ "/sds/traffic/", "ccerml3" },		{ "/sds/traffic/", "ccermz" },
	{ "/sds/traffic/", "ccerzl" },		{ "/sds/traffic/", "ccerzl1" },		{ "/sds/traffic/", "ccinbg1" },
	{ "/sds/traffic/", "ccinbg2" },		{ "/sds/traffic/", "ccinbl" },		{ "/sds/traffic/", "ccinga" },
	{ "/sds/traffic/", "ccinga2" },		{ "/sds/traffic/", "ccinku" },		{ "/sds/traffic/", "ccinml" },
	{ "/sds/traffic/", "ccinri" },		{ "/sds/traffic/", "ccinzl" },		{ "/sds/traffic/", "ccinzl2" },
	{ "/sds/traffic/", "ccinzz" },		{ "/sds/traffic/", "ccinzz2" },		{ "/sds/traffic/", "ccisni" },
	{ "/sds/traffic/", "ccisni2" },		{ "/sds/traffic/", "cdel1" },		{ "/sds/traffic/", "cdel2" },
	{ "/sds/traffic/", "cdel3" },		{ "/sds/traffic/", "cdel4" },		{ "/sds/traffic/", "cdel5" },
	{ "/sds/traffic/", "cdelje" },		{ "/sds/traffic/", "cdete2" },		{ "/sds/traffic/", "cdetek" },
	{ "/sds/traffic/", "cerzz" },		{ "/sds/traffic/", "cfetak1" },		{ "/sds/traffic/", "cfetak2" },
	{ "/sds/traffic/", "cguard1" },		{ "/sds/traffic/", "cguard2" },		{ "/sds/traffic/", "chlid1" },
	{ "/sds/traffic/", "chlid2" },		{ "/sds/traffic/", "chudrz" },		{ "/sds/traffic/", "chudrz2" },
	{ "/sds/traffic/", "chudrz3" },		{ "/sds/traffic/", "cinfge" },		{ "/sds/traffic/", "cirand" },
	{ "/sds/traffic/", "cirand" },		{ "/sds/traffic/", "cirga1" },		{ "/sds/traffic/", "cirga2" },
	{ "/sds/traffic/", "cirinf" },		{ "/sds/traffic/", "cirjoh" },		{ "/sds/traffic/", "cirpat" },
	{ "/sds/traffic/", "cirsea" },		{ "/sds/traffic/", "citant" },		{ "/sds/traffic/", "citga1c" },
	{ "/sds/traffic/", "citga1f" },		{ "/sds/traffic/", "citga1v" },		{ "/sds/traffic/", "citga2c" },
	{ "/sds/traffic/", "citga2f" },		{ "/sds/traffic/", "citga2v" },		{ "/sds/traffic/", "citga3c" },
	{ "/sds/traffic/", "citga3f" },		{ "/sds/traffic/", "citga3v" },		{ "/sds/traffic/", "citga4c" },
	{ "/sds/traffic/", "citga4f" },		{ "/sds/traffic/", "citga4v" },		{ "/sds/traffic/", "citga5v" },
	{ "/sds/traffic/", "citga8" },		{ "/sds/traffic/", "citga9" },		{ "/sds/traffic/", "citga10c" },
	{ "/sds/traffic/", "citga11f" },	{ "/sds/traffic/", "citga12f" },	{ "/sds/traffic/", "citga13c" },
	{ "/sds/traffic/", "citkas" },		{ "/sds/traffic/", "citklav" },		{ "/sds/traffic/", "citseb" },
	{ "/sds/traffic/", "citukl" },		{ "/sds/traffic/", "citvov1" },		{ "/sds/traffic/", "citvov2" },
	{ "/sds/traffic/", "citzst" },		{ "/sds/traffic/", "cjoan" },		{ "/sds/traffic/", "cmesmz" },
	{ "/sds/traffic/", "cmeszl" },		{ "/sds/traffic/", "cmeszl2" },		{ "/sds/traffic/", "cmeszz" },
	{ "/sds/traffic/", "cmeszz2" },		{ "/sds/traffic/", "cmeszz3" },		{ "/sds/traffic/", "cmot1" },
	{ "/sds/traffic/", "cmot2" },		{ "/sds/traffic/", "cmot3" },		{ "/sds/traffic/", "cmot4" },
	{ "/sds/traffic/", "cmotbo" },		{ "/sds/traffic/", "cmrtvl" },		{ "/sds/traffic/", "cpr1ce" },
	{ "/sds/traffic/", "cpr2st" },		{ "/sds/traffic/", "cpr3zm" },		{ "/sds/traffic/", "cpr4" },
	{ "/sds/traffic/", "cpr5" },		{ "/sds/traffic/", "cpr7" },		{ "/sds/traffic/", "cpros1l" },
	{ "/sds/traffic/", "cpros1n_low" },	{ "/sds/traffic/", "cpros1z" },		{ "/sds/traffic/", "cpros2l" },
	{ "/sds/traffic/", "cpros2z" },		{ "/sds/traffic/", "cpros3l" },		{ "/sds/traffic/", "cpros3z" },
	{ "/sds/traffic/", "cpros6l" },		{ "/sds/traffic/", "cpros6z" },		{ "/sds/traffic/", "cpump1" },
	{ "/sds/traffic/", "csicde" },		{ "/sds/traffic/", "csicde2" },		{ "/sds/traffic/", "csicde3" },
	{ "/sds/traffic/", "csicmu" },		{ "/sds/traffic/", "csicmu3" },		{ "/sds/traffic/", "csicze" },
	{ "/sds/traffic/", "csicze2" },		{ "/sds/traffic/", "csicze3" },		{ "/sds/traffic/", "csomra" },
	{ "/sds/traffic/", "csomra2" },		{ "/sds/traffic/", "cvez1" },		{ "/sds/traffic/", "cvez2" },
	{ "/sds/traffic/", "cvez3" },		{ "/sds/traffic/", "cvez4" },		{ "/sds/traffic/", "cvez5" },
	{ "/sds/traffic/", "cvez6" },		{ "/sds/traffic/", "cvez7" },		{ "/sds/traffic/", "cvezci1" },
	{ "/sds/traffic/", "cvezci2" },		{ "/sds/traffic/", "cvezci3" },		{ "/sds/traffic/", "cvezedv" },
	{ "/sds/traffic/", "cvezga1" },		{ "/sds/traffic/", "cvezga2" },		{ "/sds/traffic/", "cvezjim" },
	{ "/sds/traffic/", "cvezjon" },		{ "/sds/traffic/", "cvezvin" },		{ "/sds/traffic/", "driver" },

	// NEW Skins
	{ "/sds/skins_m2o/", "vitreb" },
	{ "/sds/skins_m2o/", "vitschool" },
	{ "/sds/skins_m2o/", "vitstar" },
	{ "/sds/skins_m2o/", "vitsuit" },
	{ "/sds/skins_m2o/", "vittel_kab" },
	{ "/sds/skins_m2o/", "vittux" },
	{ "/sds/skins_m2o/", "vitvezo" },
	{ "/sds/skins_m2o/", "vitvezoc" },
	{ "/sds/skins_m2o/", "williams" },
	{ "/sds/skins_m2o/", "witness" },
	{ "/sds/skins_m2o/", "wong" },
	{ "/sds/skins_m2o/", "amvoj1" },
	{ "/sds/skins_m2o/", "amvoj2" },
	{ "/sds/skins_m2o/", "amvojs" },
	{ "/sds/skins_m2o/", "balls" },
	{ "/sds/skins_m2o/", "bpvest1" },
	{ "/sds/skins_m2o/", "bpvest2" },
	{ "/sds/skins_m2o/", "brianv" },
	{ "/sds/skins_m2o/", "brianvz" },
	{ "/sds/skins_m2o/", "bruno" },
	{ "/sds/skins_m2o/", "butcher" },
	{ "/sds/skins_m2o/", "carlo" },
	{ "/sds/skins_m2o/", "carloz" },
	{ "/sds/skins_m2o/", "cat" },
	{ "/sds/skins_m2o/", "ccerb4" },
	{ "/sds/skins_m2o/", "ccerml4" },
	{ "/sds/skins_m2o/", "ccertl" },
	{ "/sds/skins_m2o/", "ccertl_kabat" },
	{ "/sds/skins_m2o/", "ccertl_kabatkrev" },
	{ "/sds/skins_m2o/", "ccindo" },
	{ "/sds/skins_m2o/", "ccinfet1" },
	{ "/sds/skins_m2o/", "ccinfet2" },
	{ "/sds/skins_m2o/", "cdete3" },
	{ "/sds/skins_m2o/", "cdozo1" },
	{ "/sds/skins_m2o/", "cdozo2" },
	{ "/sds/skins_m2o/", "cdozte" },
	{ "/sds/skins_m2o/", "celgre" },
	{ "/sds/skins_m2o/", "chem1" },
	{ "/sds/skins_m2o/", "chlid3" },
	{ "/sds/skins_m2o/", "chlid4" },
	{ "/sds/skins_m2o/", "chlid5" },
	{ "/sds/skins_m2o/", "cirhar" },
	{ "/sds/skins_m2o/", "citeri" },
	{ "/sds/skins_m2o/", "citeriz" },
	{ "/sds/skins_m2o/", "citga6fz" },
	{ "/sds/skins_m2o/", "citga7fz" },
	{ "/sds/skins_m2o/", "citga10z" },
	{ "/sds/skins_m2o/", "citgiu" },
	{ "/sds/skins_m2o/", "citklav2" },
	{ "/sds/skins_m2o/", "cmech1" },
	{ "/sds/skins_m2o/", "cmech2" },
	{ "/sds/skins_m2o/", "cmrtvlo" },
	{ "/sds/skins_m2o/", "corporal" },
	{ "/sds/skins_m2o/", "cpol5bp" },
	{ "/sds/skins_m2o/", "cpolfal1" },
	{ "/sds/skins_m2o/", "cpolfal2" },
	{ "/sds/skins_m2o/", "cpoli1" },
	{ "/sds/skins_m2o/", "cpoli2" },
	{ "/sds/skins_m2o/", "cpoli3" },
	{ "/sds/skins_m2o/", "cpoli4" },
	{ "/sds/skins_m2o/", "cpr4z" },
	{ "/sds/skins_m2o/", "cpr6" },
	{ "/sds/skins_m2o/", "cpradl" },
	{ "/sds/skins_m2o/", "cpros1nzad" },
	{ "/sds/skins_m2o/", "cpros2n" },
	{ "/sds/skins_m2o/", "cpros3f" },
	{ "/sds/skins_m2o/", "cpros3nak" },
	{ "/sds/skins_m2o/", "cpros3z_fmv" },
	{ "/sds/skins_m2o/", "cpros4n" },
	{ "/sds/skins_m2o/", "cpros5" },
	{ "/sds/skins_m2o/", "cpros6f" },
	{ "/sds/skins_m2o/", "cpros7n" },
	{ "/sds/skins_m2o/", "cpump3" },
	{ "/sds/skins_m2o/", "csicmu2" },
	{ "/sds/skins_m2o/", "csicmu4" },
	{ "/sds/skins_m2o/", "cvez1n_t" },
	{ "/sds/skins_m2o/", "cvez2n_t" },
	{ "/sds/skins_m2o/", "cvez3n_t" },
	{ "/sds/skins_m2o/", "cvez8" },
	{ "/sds/skins_m2o/", "cvez9" },
	{ "/sds/skins_m2o/", "cvez10" },
	{ "/sds/skins_m2o/", "cvez11" },
	{ "/sds/skins_m2o/", "cvez12" },
	{ "/sds/skins_m2o/", "cvez13" },
	{ "/sds/skins_m2o/", "cvez14" },
	{ "/sds/skins_m2o/", "cvezci1n_t" },
	{ "/sds/skins_m2o/", "cvezci2n_t" },
	{ "/sds/skins_m2o/", "doncal" },
	{ "/sds/skins_m2o/", "eddieo" },
	{ "/sds/skins_m2o/", "faluct" },
	{ "/sds/skins_m2o/", "franca_naked" },
	{ "/sds/skins_m2o/", "gorntl" },
	{ "/sds/skins_m2o/", "gorntlz" },
	{ "/sds/skins_m2o/", "hen40s" },
	{ "/sds/skins_m2o/", "hen40sz" },
	{ "/sds/skins_m2o/", "itcam1" },
	{ "/sds/skins_m2o/", "itcam2" },
	{ "/sds/skins_m2o/", "itvoj1" },
	{ "/sds/skins_m2o/", "itvoj2" },
	{ "/sds/skins_m2o/", "izak" },
	{ "/sds/skins_m2o/", "joed1" },
	{ "/sds/skins_m2o/", "joed2" },
	{ "/sds/skins_m2o/", "joeksl" },
	{ "/sds/skins_m2o/", "joeksl2" },
	{ "/sds/skins_m2o/", "joel1" },
	{ "/sds/skins_m2o/", "joel2" },
	{ "/sds/skins_m2o/", "joeobd" },
	{ "/sds/skins_m2o/", "joeobld" },
	{ "/sds/skins_m2o/", "joeobld2" },
	{ "/sds/skins_m2o/", "joepra" },
	{ "/sds/skins_m2o/", "joespo" },
	{ "/sds/skins_m2o/", "joetel" },
	{ "/sds/skins_m2o/", "joeukl" },
	{ "/sds/skins_m2o/", "joeukl_knirek" },
	{ "/sds/skins_m2o/", "joeup" },
	{ "/sds/skins_m2o/", "joevez" },
	{ "/sds/skins_m2o/", "joezml" },
	{ "/sds/skins_m2o/", "kungfu" },
	{ "/sds/skins_m2o/", "leoobd" },
	{ "/sds/skins_m2o/", "leovez" },
	{ "/sds/skins_m2o/", "lucca" },
	{ "/sds/skins_m2o/", "luccaz" },
	{ "/sds/skins_m2o/", "marco" },
	{ "/sds/skins_m2o/", "marco2" },
	{ "/sds/skins_m2o/", "martydeath" },
	{ "/sds/skins_m2o/", "mgngstr1" },
	{ "/sds/skins_m2o/", "mgngstr2" },
	{ "/sds/skins_m2o/", "mike" },
	{ "/sds/skins_m2o/", "owner" },
	{ "/sds/skins_m2o/", "ownerz" },
	{ "/sds/skins_m2o/", "panchu" },
	{ "/sds/skins_m2o/", "parker" },
	{ "/sds/skins_m2o/", "pepeob" },
	{ "/sds/skins_m2o/", "pepeve" },
	{ "/sds/skins_m2o/", "pepevez" },
	{ "/sds/skins_m2o/", "pes_cerny" },
	{ "/sds/skins_m2o/", "pes_hnedy" },
	{ "/sds/skins_m2o/", "pete" },
	{ "/sds/skins_m2o/", "pietro" },
	{ "/sds/skins_m2o/", "polchief" },
	{ "/sds/skins_m2o/", "rtrvez" },
	{ "/sds/skins_m2o/", "sailor1" },
	{ "/sds/skins_m2o/", "sailor2" },
	{ "/sds/skins_m2o/", "tomang" },
	{ "/sds/skins_m2o/", "tomangd" },
	{ "/sds/skins_m2o/", "vitbik" },
	{ "/sds/skins_m2o/", "vitcow" },
	{ "/sds/skins_m2o/", "vitm1" },
	{ "/sds/skins_m2o/", "vitmat" },
	{ "/sds/skins_m2o/", "vitnaho" },
};

static int VehicleFuelTankCapacity[] =
{
	60,								90,									0,
	200,							200,								200,								70,
	70,								70,									70,									70,							58,
	58,								90,									70,
	90,								90,									90,									90,
	80,								150,								150,								70,							60,
	60,								65,									65,									100,
	80,								70,									65,									65,							65,
	65,								100,								100,
	100,							100,								100,
	100,							80,									80,									80,							50,
	65,								70,									80,
	65,								50,
	0,								70,									70,
	80,								40, 
	/*dlc ���� -->*/ 80, 50, 70, 100, 80, 90, 81, 70, 70, 80, 
	50,
	/*����� ���� -->*/70
};

static char * VehicleModels[] =
{
	"ascot_baileys200_pha",			"berkley_kingfisher_pha",			"fuel_tank",
	"gai_353_military_truck",		"hank_b",							"hank_fueltank",					"hot_rod_1",
	"hot_rod_2",					"hot_rod_3",						"houston_wasp_pha",					"isw_508",					"jeep",
	"jeep_civil",					"jefferson_futura_pha",				"jefferson_provincial",
	"lassiter_69",					"lassiter_69_destr",				"lassiter_75_fmv",					"lassiter_75_pha",
	"milk_truck",					"parry_bus",						"parry_prison",						"potomac_indian",			"quicksilver_windsor_pha",
	"quicksilver_windsor_taxi_pha",	"shubert_38",						"shubert_38_destr",					"shubert_armoured",
	"shubert_beverly",				"shubert_frigate_pha",				"shubert_hearse",					"shubert_panel",			"shubert_panel_m14",
	"shubert_taxi",					"shubert_truck_cc",					"shubert_truck_ct",
	"shubert_truck_ct_cigar",		"shubert_truck_qd",					"shubert_truck_sg",
	"shubert_truck_sp",				"sicily_military_truck",			"smith_200_pha",					"smith_200_p_pha",			"smith_coupe",
	"smith_mainline_pha",			"smith_stingray_pha",				"smith_truck",
	"smith_v8",						"smith_wagon_pha",
	"trailer_sg",					"ulver_newyorker",					"ulver_newyorker_p",
	"walker_rocket",				"walter_coupe",
	/*dlc ���� -->*/"delizia_grandeamerica", "chaffeque", "waybar", "roller", "elysium", "desta", "payback", "shubert_pickup", "shubert_34", "trautenberg_grande",
	"smith_coupe_wreck", 
	/*����� ���� -->*/"cadilla_miller_meteor_1959"
};

static char * VehicleWheelModels[] =
{
	"wheel_civ04",		"wheel_civ05",		"wheel_civ07",		"wheel_civ08",		"wheel_civ09",
	"wheel_civ01",		"wheel_civ02",		"wheel_civ03",		"wheel_civ06",		"wheel_civ10",
	"wheel_civ11",		"wheel_sport",		"wheel_jeep",		"wheel_hank_f",		"wheel_truckciv01",
	"wheel_truckciv02",	"wheel_civ09_hot",  "wheel_hank_r",		"wheel_civ11_hot"
};

static char * WeaponName[] =
{
	"Model 12 Revolver", "Mauser C96", "Colt M1911A1", "Colt M1911 Special", "Model 19 Revolver",
	"Remington Model 870 Field gun", "M3 Grease Gun", "MP40", "	Thompson 1928", "M1A1 Thompson", "Beretta Model 38A",
	"MG42", "M1 Garand", "Kar98k", "MK2 Frag Grenade", "Molotov Cocktail"
};

static int WeaponNameID[] =
{
	2, 3, 4, 5, 6, 8, 9,
	10, 11, 12, 13, 14, 15,
	17, 20, 21
};

static char * Doors[] =
{
	"GS_door",				"GS_door00",		"GS_door01",
	"Wash_gate00",			"Wash_gate01",
	"GUNSHOP_Door_Glass00",
	"C_Door",				"C_Door00",			"C_Door01",
	"GIUSH_Door_Vstup00",
	"GIUSH_Door00",
	"RS_vrata01",
	"EntryDoor"
};

unsigned int Game::GetIdFromDoorName(String doorName)
{
	int returnId = -1;
	for (unsigned int i = 0; i < sizeof(Doors) / sizeof(*Doors); i++)
	{
		if (doorName.Compare(Doors[i]))
		{
			returnId = i;
			break;
		}
	}
	return (returnId);
}

String Game::GetDoorNameFromId(unsigned int doorId)
{
	String retnName = "Unknow";

	for (unsigned int i = 0; i < sizeof(Doors) / sizeof(*Doors); i++)
	{
		if (i == doorId)
		{
			retnName.Set(Doors[i]);
			break;
		}
	}
	return (retnName);
}

unsigned int Game::GetWeaponIdFromName(String strName)
{
	int foundId = -1;
	int found = 0;

	// Name not in array ?
	for (unsigned int i = 0; i < sizeof(WeaponName) / sizeof(*WeaponName); i++)
	{
		if (!strName.Compare(WeaponName[i])){
			found = 1;
			break;
		}
	}
	if (found == 0)
		return (0);

	// Loop each name
	for (unsigned int i = 0; i < sizeof(WeaponName); i++)
	{
		// Name match ?
		if (!strName.Compare(WeaponName[i])){
			foundId = i;
			break;
		}
	}

	// Found weapon ?
	if (foundId == -1)
		return (0);
	else {
		return (WeaponNameID[foundId]);
	}
}

String Game::GetWeaponNameFromId(unsigned int uiModel)
{
	String retn = "";
	int found = -1;

	// Loop each weapon
	for (unsigned int i = 0; i < sizeof(WeaponNameID); i++)
	{
		// ID match ?
		if (WeaponNameID[i] == uiModel){
			found = i;
			break;
		}
	}

	// Found weapon ?
	if (found == -1)
		return (retn);
	else {
		retn.Set(WeaponName[found]);
		return (retn);
	}
}

unsigned int Game::GetFuelTankCapacityFromModel(unsigned int uiModel)
{
	uiModel = Math::Clamp< unsigned int >(0, uiModel, ((sizeof(VehicleFuelTankCapacity) / sizeof(VehicleFuelTankCapacity[0])) - 1));

	return VehicleFuelTankCapacity[uiModel];
}

unsigned int Game::GetIdFromPlayerModel( String strModel )
{
	// Loop over each model
	for( unsigned int i = 0; i < (sizeof(PlayerModels) / sizeof(PlayerModels[0])); i++ )
	{
		// Is the model the one we're looking for?
		if( !strModel.Compare( PlayerModels[ i ][ 1 ] ) )
			return i;
	}

	return 0;
}

void Game::GetPlayerModelFromId( unsigned int uiModel, String * strModel, String * strDirectory )
{
	//  Clamp the model id
	uiModel = Math::Clamp< unsigned int >( 0, uiModel, ((sizeof(PlayerModels) / sizeof(PlayerModels[0])) - 1) );

	// Set the model string
	strModel->Set( PlayerModels[ uiModel ][ 1 ] );

	// Set the directory string
	strDirectory->Set( PlayerModels[ uiModel ][ 0 ] );
}

unsigned int Game::GetIdFromVehicleModel( String strModel )
{
	// Loop over each model
	for( unsigned int i = 0; i < (sizeof(VehicleModels) / sizeof(VehicleModels[0])); i++ )
	{
		// Is the model the one we're looking for?
		if( !strModel.Compare( VehicleModels[ i ] ) )
			return i;
	}

	return 0;
}

void Game::GetVehicleModelFromId( unsigned int uiModel, String * strModel )
{
	// Clamp the model id
	uiModel = Math::Clamp< unsigned int >( 0, uiModel, ((sizeof(VehicleModels) / sizeof(VehicleModels[0])) - 1) );

	// Set the model string
	strModel->Set( VehicleModels[ uiModel ] );
}

unsigned int Game::GetIdFromVehicleWheelModel( String strModel )
{
	// Loop over each model
	for( unsigned int i = 0; i < (sizeof(VehicleWheelModels) / sizeof(VehicleWheelModels[0])); i++ )
	{
		// Is the model the one we're looking for?
		if( !strModel.Compare( VehicleWheelModels[ i ] ) )
			return i;
	}

	return 0xFF;
}

String Game::GetVehicleWheelModelFromId( unsigned int uiModel )
{
	// Clamp the model id
	uiModel = Math::Clamp< unsigned int >( 0, uiModel, ((sizeof(VehicleWheelModels) / sizeof(VehicleWheelModels[0])) - 1) );

	// Set the model string
	return String( VehicleWheelModels[ uiModel ] );
}