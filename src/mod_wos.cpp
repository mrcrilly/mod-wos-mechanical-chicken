
// C++ stdlib
#include <tuple>

// AzerothCore and beyond
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"
#include "World.h"
#include "DatabaseEnv.h"

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

        Mail* newMail = new Mail;
        newMail->body = "There's a new";
        newMail->subject = "A new threat!";
        player->AddMail(newMail);
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

        // Get player's account details
        auto playerID = player->GetSession()->GetAccountId();
        auto charID = player->GetGUID().GetRawValue();

        // Check the player's progress in the database
        uint32 playerStage = 1;
        QueryResult qResult = CharacterDatabase.Query("SELECT stage FROM `mod_wos_mechanical_chicken_stages` WHERE `playerID`={} AND `charID`={}", playerID, charID);
        
        if (qResult) {
            Field* fields = qResult->Fetch();
            uint32 stage = fields[0].Get<int64>(); // stage
            playerStage = stage;
        } else {
            CharacterDatabase.Query("INSERT INTO `mod_wos_mechanical_chicken_stages` (playerID, charID, stage) VALUES ({}, {}, {})", playerID, charID, 1);
        }

        // Progress them through the options
        if (playerStage == 1) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "?", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_ONE);
        }
        else if (playerStage == 2) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "??", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_TWO);
        }
        else if (playerStage == 3) {
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "Stormwind", GOSSIP_SENDER_MAIN, WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_THREE);
        }
        else if (playerStage > 3) {
            // Once they're on stage 3, they get the normal gossip, below
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
        }

        SendGossipMenuFor(player, WOS_MC_GOSSIP_GREETING, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        auto playerID = player->GetSession()->GetAccountId();
        auto charID = player->GetGUID().GetRawValue();

        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        if (action == 1)
        {
            OnGossipHello(player, creature);
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_ONE) {
            CloseGossipMenuFor(player);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_STAGE_ONE.map,
                WOS_PLAYER_TELEPORT_LOC_STAGE_ONE.x,
                WOS_PLAYER_TELEPORT_LOC_STAGE_ONE.y,
                WOS_PLAYER_TELEPORT_LOC_STAGE_ONE.z,
                WOS_PLAYER_TELEPORT_LOC_STAGE_ONE.o
            );
            CharacterDatabase.Query("UPDATE `mod_wos_mechanical_chicken_stages` SET `stage`=2 WHERE `playerID`={} AND `charID`={}", playerID, charID);
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_TWO) {
            CloseGossipMenuFor(player);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_STAGE_TWO.map,
                WOS_PLAYER_TELEPORT_LOC_STAGE_TWO.x,
                WOS_PLAYER_TELEPORT_LOC_STAGE_TWO.y,
                WOS_PLAYER_TELEPORT_LOC_STAGE_TWO.z,
                WOS_PLAYER_TELEPORT_LOC_STAGE_TWO.o
            );
            CharacterDatabase.Query("UPDATE `mod_wos_mechanical_chicken_stages` SET `stage`=3 WHERE `playerID`={} AND `charID`={}", playerID, charID);
        }

        else if (action == WOS_MC_GOSSIP_TAKE_ME_TO_STAGE_THREE) {
            CloseGossipMenuFor(player);
            player->PlayDirectSound(CHICKEN_TELEPORT_SOUND);
            player->TeleportTo(
                WOS_PLAYER_TELEPORT_LOC_STAGE_THREE.map,
                WOS_PLAYER_TELEPORT_LOC_STAGE_THREE.x,
                WOS_PLAYER_TELEPORT_LOC_STAGE_THREE.y,
                WOS_PLAYER_TELEPORT_LOC_STAGE_THREE.z,
                WOS_PLAYER_TELEPORT_LOC_STAGE_THREE.o
            );
            CharacterDatabase.Query("UPDATE `mod_wos_mechanical_chicken_stages` SET `stage`=4 WHERE `playerID`={} AND `charID`={}", playerID, charID);
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

class WoSConfigurationMechanicalChicken : public WorldScript
{

public:
    WoSConfigurationMechanicalChicken() : WorldScript("WoSConfigurationMechanicalChicken") {}

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
    }
};

// Add all scripts in one
void AddWoSScripts()
{
    new WoSConfigurationMechanicalChicken();
    new WoSMechanicChickenPet();
    new WoS();
}
