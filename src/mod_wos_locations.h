
class LocationVector
{
public:
    uint32 map;
    float x;
    float y;
    float z;
    float o;

    LocationVector()
    {
        map = 0;
        x = 0.0;
        y = 0.0;
        z = 0.0;
        o = 0.0;
    }

    LocationVector(float x1, float y1, float z1, float o1, uint32 map1 = 0)
    {
        map = map1;
        x = x1;
        y = y1;
        z = z1;
        o = o1;
    }
};

const uint32 MAP_EASTERN_KINGDOMS = 0;
const uint32 MAP_KALIMDOR = 1;
const uint32 MAP_OUTLAND = 530;
const uint32 MAP_NORTHREND = 571;

// ########
// OUTLANDS
// ########

// Exodar
const LocationVector WOS_CLONE_LOC_EXODAR = LocationVector(-4047.368, -11569.892, -138.48938, 0.349499, MAP_OUTLAND);
const LocationVector WOS_PLAYER_TELEPORT_LOC_EXODAR = LocationVector(-4045.691, -11574.194, -138.48712, 2.057740, MAP_OUTLAND);

// Shattrath
const LocationVector WOS_CLONE_LOC_SHATTRATH = LocationVector(-1923.5654, 5164.2104, -37.793854, 0.999771, MAP_OUTLAND);
const LocationVector WOS_PLAYER_TELEPORT_LOC_SHATTRATH = LocationVector(-1925.417, 5167.18, -40.209145, 5.178087, MAP_OUTLAND);

// Silvermoon City
const LocationVector WOS_CLONE_LOC_SILVERMOON_CITY = LocationVector(9985.889, -7112.2866, 47.704704, 0.899436, MAP_OUTLAND);
const LocationVector WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY = LocationVector(9988.129, -7112.668, 47.704704, 3.009016, MAP_OUTLAND);

// #########
// NORTHREND
// #########

// Dalaran - need two locations for the different factions
const LocationVector WOS_CLONE_LOC_DALARAN_ALLIANCE = LocationVector(5705.358, 748.7633, 644.86084, 6.046065, MAP_NORTHREND);
const LocationVector WOS_CLONE_LOC_DALARAN_HORDE = LocationVector(5935.226, 561.7121, 639.57434, 3.115754, MAP_NORTHREND);

const LocationVector WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE = LocationVector(5708.4775, 746.9489, 641.7563, 2.602095, MAP_NORTHREND);
const LocationVector WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE = LocationVector(5931.35, 561.5224, 639.6005, 0.224705, MAP_NORTHREND);

// ########
// KALIMDOR
// ########

// Darnassus
const LocationVector WOS_CLONE_LOC_DARNASSUS = LocationVector(9639.297, 2509.855, 1333.473, 0.848170, MAP_KALIMDOR);
const LocationVector WOS_PLAYER_TELEPORT_LOC_DARNASSUS = LocationVector(9641.854, 2513.155, 1333.5017, 4.198680, MAP_KALIMDOR);

// Orgrimmar
const LocationVector WOS_CLONE_LOC_ORGRIMMAR = LocationVector(1476.4816, -4202.749, 43.8331, 4.493981, MAP_KALIMDOR);
const LocationVector WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR = LocationVector(1475.0822, -4207.039, 43.18625, 1.077498, MAP_KALIMDOR);

// Thunder Bluff
const LocationVector WOS_CLONE_LOC_THUNDER_BLUFF = LocationVector(-949.1484, 256.04608, 97.34436, 4.143632, MAP_KALIMDOR);
const LocationVector WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF = LocationVector(-952.1207, 251.91531, 97.41911, 1.019322, MAP_KALIMDOR);

// #################
// EASTERN KINGDOMS
// #################

// Stormwind
const LocationVector WOS_CLONE_LOC_STORMWIND = LocationVector(-9002.942, 874.0727, 129.69243, 4.782641, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND = LocationVector(-9003.969, 871.0497, 129.69241, 1.322178, MAP_EASTERN_KINGDOMS);

// Stormwind - silly begging locations
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND_SILLY_1 = LocationVector(-8853.722, 620.6209, 104.26269, 5.261751, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND_SILLY_2 = LocationVector(-8680.91, 578.11426, 96.94911, 1.008821, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND_SILLY_3 = LocationVector(-8719.025, 552.00916, 88.73485, 0.686802, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND_SILLY_4 = LocationVector(-8630.377, 884.2247, 103.18133, 2.434313, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_STORMWIND_SILLY_5 = LocationVector(-8881.17, 566.129, 99.54935, 4.515613, MAP_EASTERN_KINGDOMS);

// Ironforge
const LocationVector WOS_CLONE_LOC_IRONFORGE = LocationVector(-4620.027, -938.0188, 502.76572, 2.065092, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_IRONFORGE = LocationVector(-4621.459, -933.7206, 502.76572, 4.955358, MAP_EASTERN_KINGDOMS);

// Undercity
const LocationVector WOS_CLONE_LOC_UNDERCITY = LocationVector(1777.4889, 83.023926, -59.315, 3.091523, MAP_EASTERN_KINGDOMS);
const LocationVector WOS_PLAYER_TELEPORT_LOC_UNDERCITY = LocationVector(1773.3015, 83.44799, -59.315, 6.076037, MAP_EASTERN_KINGDOMS);


