
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

        Mail* newMail = new Mail;
        newMail->body = "There's a new";
        newMail->subject = "A new threat!";
        player->AddMail(newMail);
    }

    void OnPlayerCompleteQuest(Player* player, Quest const* quest) override
    {
        if (cDebugging) {
            LOG_ERROR("module", "{}: A player completed a quest: {}", debuggingPrefix, player->GetName());
        }

        if (!cModuleEnabled) {
            return;
        }

        // We ignore certain quest types
        if (quest->IsDailyOrWeekly() || quest->IsRepeatable()) {
            return;
        }

        uint32 count = 1;

        if (cDungeonDifficultyNormalEnabled && quest->IsRaidQuest(DUNGEON_DIFFICULTY_NORMAL))
        {
            count += 1;
        }
        else if (cDungeonDifficultyHeroicEnabled && quest->IsRaidQuest(DUNGEON_DIFFICULTY_HEROIC))
        {
            count += 2;
        }
        else if (cDungeonDifficultyEpicEnabled && quest->IsRaidQuest(DUNGEON_DIFFICULTY_EPIC)) {
            count += 3;
        }

        player->AddItem(emblemOfValor, count);
        informPlayerOfPrize(player, MSG_QUEST_COMPLETE);
    }

    void OnCreatureKill(Player* player, Creature* victim) override
    {
        if (cDebugging) {
            LOG_ERROR("module", "{}: A player killed a creature: {} vs. {}", debuggingPrefix, player->GetName(), victim->GetName());
        }

        if (!player->isHonorOrXPTarget(victim)) {
            if (cDebugging) {
                LOG_ERROR("module", "{}: kill did not yield experience. ignoring", debuggingPrefix);
            }
            return; // has to yield XP or (PVP) honor
        }

        bool winner = false;

        // Well the player can never lose
        if (cDropChanceAfterKill >= 100) {
            winner = true;
        }

        // The player can never win
        if (!winner && cDropChanceAfterKill <= 0) {
            return;
        }

        // Roll for it
        if (!winner && !diceRollWinner(cDropChanceAfterKill)) {
            return; // loser
        }

        // Winner!
        // TODO: work on creature types to improve
        player->AddItem(emblemOfValor, 1);
        informPlayerOfPrize(player, MSG_CREATURE_KILL);
    }
};

class WoSMechanicChickenPet : public CreatureScript
{
public:
    WoSMechanicChickenPet() : CreatureScript("npc_wos_mechanical_chicken") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);

        uint32 oil_count;
        bool player_can_afford_service;
        std::tie(player_can_afford_service, oil_count) = playerHasEnoughOil(player, cCostOfMechanicalChickenOilPerTeleport);

        if (!player_can_afford_service)
        {
            SendGossipMenuFor(player, WOS_MC_GOSSIP_GREETING_NO_OIL, creature->GetGUID());
        }
        else
        {
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
        }

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

class WoSManabonkNPC : public CreatureScript
{
public:

    WoSManabonkNPC() : CreatureScript("npc_wos_minigob_manabonk") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to trade Emblems of Valor", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR);
        SendGossipMenuFor(player, WOS_MM_GOSSIP_TEXT, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        if (action == 1) {
            OnGossipHello(player, creature);
        }

        // #############
        // Gossip Entry
        // #############
        else if (action == WOS_MM_GOSSIP_VALOR) {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to boost my level...", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_LEVEL);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I need to get to Dalaran!", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I'd kill for a mount...", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_BUY_MOUNT);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "About these mechanical chickens...", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN);
            SendGossipMenuFor(player, WOS_MM_GOSSIP_TEXT, creature->GetGUID());
        }

        // ###############
        // LEVELLING MENU
        // ###############
        else if (action == WOS_MM_GOSSIP_VALOR_LEVEL) {
            if (cDebugging) {
                LOG_INFO("module", "{}: player opted to sell Emblem of Honor for a level...", debuggingPrefix);
            }

            const std::string itemOneLevelBoost = "I'd like 1 magic level boost, please! (x" + std::to_string(cEmblemOfValorPerLevel) + " Emblem of Valor)";
            const std::string itemTwoLevelBoost = "I'd like 2 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 2) + " Emblem of Valor)";
            const std::string itemThreeLevelBoost = "I'd like 3 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 3) + " Emblem of Valor)";
            const std::string itemFiveLevelBoost = "I'd like 5 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 5) + " Emblem of Valor)";

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemOneLevelBoost, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_LEVEL_ONE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemTwoLevelBoost, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_LEVEL_TWO);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemThreeLevelBoost, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_LEVEL_THREE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemFiveLevelBoost, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_LEVEL_FIVE);
            SendGossipMenuFor(player, WOS_MM_GOSSIP_CHITCHAT_LEVEL, creature->GetGUID());
        }
        else if (action == WOS_MM_GOSSIP_VALOR_LEVEL_ONE) {
            if (!provideLevelingService(player, 1)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_ONE", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_MM_GOSSIP_VALOR_LEVEL_TWO) {
            if (!provideLevelingService(player, 2)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_TWO", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_MM_GOSSIP_VALOR_LEVEL_THREE) {
            if (!provideLevelingService(player, 3)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_THREE", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_MM_GOSSIP_VALOR_LEVEL_FIVE) {
            if (!provideLevelingService(player, 5)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_FIVE", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }

        // ######################
        // DALARAN TELEPORT MENU
        // ######################
        else if (action == WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cEmblemOfValorDalaranTeleport);

            ClearGossipMenuFor(player);

            if (!player_can_afford_service) {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I'll pay you later, OK? Please?", GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT_BEG);
            }
            else {
                const std::string dalaranTransportConfirm = "I'm good for it... (x" + std::to_string(cEmblemOfValorDalaranTeleport) + " Emblem of Valor)";
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, dalaranTransportConfirm, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT_CONFIRM);
            }

            SendGossipMenuFor(player, WOS_MM_GOSSIP_CHITCHAT_DALARAN_TELEPORT, creature->GetGUID());
        }
        else if (action == WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT_BEG) {
            ChatHandler(player->GetSession()).SendSysMessage("No way! Get out of here!!");
            creature->CastSpell(player, 61834);
            CloseGossipMenuFor(player);
        }
        else if (action == WOS_MM_GOSSIP_VALOR_DALARAN_TELEPORT_CONFIRM) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cEmblemOfValorDalaranTeleport);

            if (!player_can_afford_service) {
                CloseGossipMenuFor(player);
                ChatHandler(player->GetSession()).SendSysMessage("What? Get out of here. I aint no charity! I got clones to, ya know... clone!");
            }
            else {
                CloseGossipMenuFor(player);

                if (player->GetTeamId() == TEAM_ALLIANCE) {
                    player->TeleportTo(
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.map,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.x,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.y,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.z,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_ALLIANCE.o
                    );
                }
                else {
                    player->TeleportTo(
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.map,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.x,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.y,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.z,
                        WOS_PLAYER_TELEPORT_LOC_DALARAN_HORDE.o
                    );
                }
            }
        }

        // ##################
        // MECHANICAL CHICKEN
        // ##################
        else if (action == WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN) {
            if (cDebugging) {
                LOG_INFO("module", "{}: player opted to sell Emblem of Honor for a mechanical chicken (oil)...", debuggingPrefix);
            }

            const std::string chicken = "Sounds great! I'll take one chicken, please! (x" + std::to_string(cCostOfMechanicalChicken) + " Emblem of Valor)";
            const std::string chickenOil = "I need to oil this thing, it's squeaking! (x" + std::to_string(cCostOfMechanicalChickenOil) + " Emblem of Valor)";

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, chicken, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN_BUY);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, chickenOil, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN_OIL_BUY);
            SendGossipMenuFor(player, WOS_MM_GOSSIP_CHITCHAT_MECHANICAL_CHICKEN, creature->GetGUID());
        }

        else if (action == WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN_BUY) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cCostOfMechanicalChicken);

            if (!player_can_afford_service) {
                ChatHandler(player->GetSession()).SendSysMessage("Do you know how COMPLEX these chickens are to make?! NO FREEBIES!!");
                CloseGossipMenuFor(player);
            }
            else {
                CloseGossipMenuFor(player);
                player->DestroyItemCount(emblemOfValor, cCostOfMechanicalChicken, true);
                player->AddItem(mechanicalChickenOil, 5);
                player->AddItem(mechanicalChicken, 1);
            }
        }

        else if (action == WOS_MM_GOSSIP_VALOR_MECHANICAL_CHICKEN_OIL_BUY) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cCostOfMechanicalChickenOil);

            if (!player_can_afford_service) {
                ChatHandler(player->GetSession()).SendSysMessage("Look buddy, that oil is a pain to bottle up, and you want it for FREE? Get a grip!");
                CloseGossipMenuFor(player);
            }
            else {
                CloseGossipMenuFor(player);
                player->DestroyItemCount(emblemOfValor, cCostOfMechanicalChickenOil, true);
                player->AddItem(mechanicalChickenOil, 5);
            }
        }

        // #####
        // MOUNT
        // #####

        else if (action == WOS_MM_GOSSIP_VALOR_BUY_MOUNT) {
            if (cDebugging) {
                LOG_INFO("module", "{}: player opted to sell Emblem of Honor for a mount and training...", debuggingPrefix);
            }

            const std::string chicken = "Sounds great! I'll take one mount, please! (x" + std::to_string(cCostOfMount) + " Emblem of Valor)";

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, chicken, GOSSIP_SENDER_MAIN, WOS_MM_GOSSIP_VALOR_BUY_MOUNT_BUY);
            SendGossipMenuFor(player, WOS_MM_GOSSIP_CHITCHAT_MOUNT, creature->GetGUID());
        }

        else if (action == WOS_MM_GOSSIP_VALOR_BUY_MOUNT_BUY) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cCostOfMount);

            if (!player_can_afford_service) {
                ChatHandler(player->GetSession()).SendSysMessage("Look buddy, that oil is a pain to bottle up, and you want it for FREE? Get a grip!");
                CloseGossipMenuFor(player);
            }
            else {
                CloseGossipMenuFor(player);
                player->DestroyItemCount(emblemOfValor, cCostOfMount, true);

                // Teach the player how-to ride this mount if their skill level
                // is < 75
                if (!(player->GetSkillValue(SKILL_RIDING) >= 75)) {
                    player->SetSkill(SKILL_RIDING, 0, 75, 75);
                }

                uint32 playerTeam = player->GetTeamId();
                uint32 playerRace = player->getRace();

                if (playerTeam == TEAM_ALLIANCE) {
                    switch (playerRace) {
                    case RACE_HUMAN:
                        player->AddItem(mountAllianceHumanBasic, 1);
                        break;
                    case RACE_DWARF:
                        player->AddItem(mountAllianceDwarfBasic, 1);
                        break;
                    case RACE_NIGHTELF:
                        player->AddItem(mountAllianceNightElfBasic, 1);
                        break;
                    case RACE_GNOME:
                        player->AddItem(mountAllianceGnomeBasic, 1);
                        break;
                    case RACE_DRAENEI:
                        player->AddItem(mountAllianceDraeneiBasic, 1);
                        break;
                    }
                }

                else if (playerTeam == TEAM_HORDE) {
                    switch (playerRace) {
                    case RACE_ORC:
                        player->AddItem(mountHordeOrcBasic, 1);
                        break;
                    case RACE_UNDEAD_PLAYER:
                        player->AddItem(mountHordeUndeadBasic, 1);
                        break;
                    case RACE_TAUREN:
                        player->AddItem(mountHordeTaurenBasic, 1);
                        break;
                    case RACE_TROLL:
                        player->AddItem(mountHordeTrollBasic, 1);
                        break;
                    case RACE_BLOODELF:
                        player->AddItem(mountHordeBloodElfBasic, 1);
                        break;
                    }
                }
            }
        }

        // #####
        // Fin.
        // #####

        return true;
    }

private:
    std::tuple<bool, uint32> playerHasEnoughEmblems(Player* player, uint32 required) {
        uint32 emblem_count = player->GetItemCount(emblemOfValor, true);

        if (cDebugging) {
            LOG_INFO("module", "{}: the player has {} emblems", emblem_count);
        }

        return std::make_tuple(emblem_count >= required, emblem_count);
    }

    bool provideLevelingService(Player* player, uint32 levels = 1) {
        uint32 emblem_count;
        bool player_can_afford_service;
        std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cEmblemOfValorPerLevel * levels);

        if (!player_can_afford_service) {
            ChatHandler(player->GetSession()).SendSysMessage("You need more Emblems for that service, sorry!");
            CloseGossipMenuFor(player);
            return true;
        }

        uint32 player_level = player->getLevel();

        if (player_level >= 80) {
            ChatHandler(player->GetSession()).SendSysMessage("You can't level anymore! You're already at max cap. Maybe buy a trinket?");
            CloseGossipMenuFor(player);
            return true;
        }

        player->DestroyItemCount(emblemOfValor, cEmblemOfValorPerLevel * levels, true);
        player->GiveLevel(player_level + levels);
        CloseGossipMenuFor(player);
        return true;
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
    new WoSManabonkNPC();
    new WoSMechanicChickenPet();
    new WoS();
}
