enum GossipId
{
    WOS_MC_GOSSIP_TEXT = 1041,
    WOS_MC_GOSSIP_TAKE_ME_TO_STORMWIND = 2100,
    WOS_MC_GOSSIP_TAKE_ME_TO_IRONFORGE = 2101,
    WOS_MC_GOSSIP_TAKE_ME_TO_DARNASSUS = 2102,
    WOS_MC_GOSSIP_TAKE_ME_TO_EXODAR = 2103,
    WOS_MC_GOSSIP_TAKE_ME_TO_ORGRIMMAR = 2104,
    WOS_MC_GOSSIP_TAKE_ME_TO_THUNDERBLUFF = 2105,
    WOS_MC_GOSSIP_TAKE_ME_TO_UNDERCITY = 2106,
    WOS_MC_GOSSIP_TAKE_ME_TO_SILVERMOONCITY = 2107,
    WOS_MC_GOSSIP_TAKE_ME_TO_SHATTRATH = 2108,
    WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_ALLIANCE = 2109,
    WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_HORDE = 2110,
};

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

// Mechanical Chicken ID
const uint32 mechanicalChicken = 10398;

void AddWoSScripts();

void Addmod_wosScripts()
{
    AddWoSScripts();
}

// C++ stdlib
#include <tuple>

// AzerothCore and beyond
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

// WoS
#include "mod_wos_general.h"
#include "mod_wos_locations.h"
#include "mod_wos_gossip.h"
#include "mod_wos_config.h"

class WoS : public PlayerScript
{
private:

    void informPlayerOfPrize(Player* player, std::string message) {
        ChatHandler(player->GetSession()).SendSysMessage(message);
    }

    uint32 selectRandomPrize() {
        return fortune_cookies[rand() % fortune_cookies.size()];
    }

    uint32 diceRoll(uint32 chance) {
        srand(time(NULL));
        return (rand() % chance) + 1;
    }

    bool diceRollWinner(uint32 chance) {
        uint32 roll = diceRoll(100);

        if (cDebugging) {
            LOG_ERROR("module", "{}: Chance: {} vs. Roll: {}", debuggingPrefix, chance, roll);
        }

        return roll <= chance;
    }

public:

    WoS() : PlayerScript("WoS") { }

    void OnLogin(Player* player) override
    {
        if (cModuleEnabled)
        {
            ChatHandler(player->GetSession()).SendSysMessage("This realm uses Level Tokens - you lucky bastard!");
        }

        // Mail* newMail = new Mail;
        // newMail->body = "There's a new";
        // newMail->subject = "A new threat!";
        // player->AddMail(newMail);
    }
};

class WoSMechanicChickenPet : public CreatureScript
{
public:
    WoSMechanicChickenPet() : CreatureScript("npc_wos_mechanical_chicken") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);

        TeamId player_team = player->GetTeamId();

        if (player_team == TEAM_ALLIANCE) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Stormwind.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_STORMWIND);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Ironforge.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_IRONFORGE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Darnassus.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_DARNASSUS);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Exodar.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_EXODAR);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Shattrath.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_SHATTRATH);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Dalaran.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_ALLIANCE);
        }
        else if (player_team == TEAM_HORDE) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Orgrimmar.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_ORGRIMMAR);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Thunderbluff.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_THUNDERBLUFF);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Undercity.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_UNDERCITY);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Silvermoon City.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_SILVERMOONCITY);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Shattrath.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_SHATTRATH);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Teleport me to Dalaran.", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_HORDE);
        }

        SendGossipMenuFor(player, WOS_MC_GOSSIP_GREETING, creature->GetGUID());

        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        if (action == 1)
        {
            OnGossipHello(player, creature);
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_STORMWIND)
        {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_STORMWIND.map,
                WOS_PLAYER_TELEPORT_LOC_STORMWIND.x,
                WOS_PLAYER_TELEPORT_LOC_STORMWIND.y,
                WOS_PLAYER_TELEPORT_LOC_STORMWIND.z,
                WOS_PLAYER_TELEPORT_LOC_STORMWIND.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_IRONFORGE) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_IRONFORGE.map,
                WOS_PLAYER_TELEPORT_LOC_IRONFORGE.x,
                WOS_PLAYER_TELEPORT_LOC_IRONFORGE.y,
                WOS_PLAYER_TELEPORT_LOC_IRONFORGE.z,
                WOS_PLAYER_TELEPORT_LOC_IRONFORGE.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_DARNASSUS) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_DARNASSUS.map,
                WOS_PLAYER_TELEPORT_LOC_DARNASSUS.x,
                WOS_PLAYER_TELEPORT_LOC_DARNASSUS.y,
                WOS_PLAYER_TELEPORT_LOC_DARNASSUS.z,
                WOS_PLAYER_TELEPORT_LOC_DARNASSUS.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_EXODAR) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_EXODAR.map,
                WOS_PLAYER_TELEPORT_LOC_EXODAR.x,
                WOS_PLAYER_TELEPORT_LOC_EXODAR.y,
                WOS_PLAYER_TELEPORT_LOC_EXODAR.z,
                WOS_PLAYER_TELEPORT_LOC_EXODAR.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_ORGRIMMAR) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR.map,
                WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR.x,
                WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR.y,
                WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR.z,
                WOS_PLAYER_TELEPORT_LOC_ORGRIMMAR.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_THUNDERBLUFF) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF.map,
                WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF.x,
                WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF.y,
                WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF.z,
                WOS_PLAYER_TELEPORT_LOC_THUNDER_BLUFF.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_UNDERCITY) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_UNDERCITY.map,
                WOS_PLAYER_TELEPORT_LOC_UNDERCITY.x,
                WOS_PLAYER_TELEPORT_LOC_UNDERCITY.y,
                WOS_PLAYER_TELEPORT_LOC_UNDERCITY.z,
                WOS_PLAYER_TELEPORT_LOC_UNDERCITY.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_SILVERMOONCITY) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY.map,
                WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY.x,
                WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY.y,
                WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY.z,
                WOS_PLAYER_TELEPORT_LOC_SILVERMOON_CITY.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_SHATTRATH) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_SHATTRATH.map,
                WOS_PLAYER_TELEPORT_LOC_SHATTRATH.x,
                WOS_PLAYER_TELEPORT_LOC_SHATTRATH.y,
                WOS_PLAYER_TELEPORT_LOC_SHATTRATH.z,
                WOS_PLAYER_TELEPORT_LOC_SHATTRATH.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_ALLIANCE) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.map,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.x,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.y,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.z,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.o
            );
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_DALARAN_HORDE) {
            CloseGossipMenuFor(player);
            player->DestroyItemCount(mechanicalChickenOil, cCostOfMechanicalChickenOilPerTeleport, true);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.map,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.x,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.y,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.z,
                WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.o
            );
        }

        return true;
    }

private:
    std::tuple<bool, uint32> playerHasEnoughOil(Player* player, uint32 required) {
        uint32 oil_count = player->GetItemCount(mechanicalChickenOil, true);

        if (cDebugging) {
            LOG_INFO("module", "{}: the player has {} oil(s)", oil_count);
        }

        return std::make_tuple(oil_count >= required, oil_count);
    }
};

class WoSConfiguration : public WorldScript
{

public:
    WoSConfiguration() : WorldScript("WoSConfiguration") {}

    void OnStartup() override
    {
        if (cDebugging) {
            // Report to admin our configuration
            LOG_INFO("module", "{}: cDailyQuestsEnabled: {}", debuggingPrefix, cDailyQuestsEnabled);
            LOG_INFO("module", "{}: cWeeklyQuestsEnabled: {}", debuggingPrefix, cWeeklyQuestsEnabled);
            LOG_INFO("module", "{}: cDungeonDifficultyNormalEnabled: {}", debuggingPrefix, cDungeonDifficultyNormalEnabled);
            LOG_INFO("module", "{}: cDungeonDifficultyHeroicEnabled: {}", debuggingPrefix, cWeeklyQuestsEnabled);
            LOG_INFO("module", "{}: cDungeonDifficultyEpicEnabled: {}", debuggingPrefix, cDungeonDifficultyEpicEnabled);
            LOG_INFO("module", "{}: cDropChanceAfterKill: {}", debuggingPrefix, cDropChanceAfterKill);
        }
    }

    void OnAfterConfigLoad(bool reload) override
    {
        // Meta
        cModuleEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Enable", 1);
        cDebugging = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Debugging", 1);

        if (cModuleEnabled) {
            if (cDebugging) {
                LOG_INFO("module", "{}: module enabled with debugging", debuggingPrefix, cModuleEnabled);
            }
        }
        else {
            return;
        }

        // Quest types
        cDailyQuestsEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Daily.Enabled", 1);
        cWeeklyQuestsEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Weekly.Enabled", 1);

        // Dungeon difficulties
        cDungeonDifficultyNormalEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Dungeon.Difficulty.Normal.Enabled", 1);
        cDungeonDifficultyHeroicEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Dungeon.Difficulty.Heroic.Enabled", 1);
        cDungeonDifficultyEpicEnabled = sConfigMgr->GetOption<bool>("WorldOfSolocraft.Dungeon.Difficulty.Epic.Enabled", 1);

        // Chance
        cDropChanceAfterKill = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Chance.Kill", 5);
        cDropChanceAfterKillElite = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Chance.KillElite", 10);

        // Emblem of Valor costs
        cEmblemOfValorPerLevel = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.Leveling", 1);
        cEmblemOfValorDalaranTeleport = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.DalaranTeleport", 5);
        cEmblemOfValorFlightPaths = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.Leveling", 5);
        cCostOfMechanicalChicken = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.MechanicalChicken", 20);
        cCostOfMechanicalChickenOil = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.MechanicalChickenOil", 2);
        cCostOfMount = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.Costs.Valor.Mount", 15);

        // Mechanical Chicken related
        cCostOfMechanicalChickenOilPerTeleport = sConfigMgr->GetOption<uint32>("WorldOfSolocraft.MechanicalChicken.OilCostPerTeleport", 1);
    }
};

// Add all scripts in one
void AddWoSScripts()
{
    new WoSConfiguration();
    new WoSMechanicChickenPet();
    new WoS();
}
