
// C++ stdlib
#include <tuple>

// AzerothCore and beyond
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

// Level Tokens
#include "WoS.h"

class WoS: public PlayerScript
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

class WoSNPC : public CreatureScript
{
public:

    WoSNPC() : CreatureScript("npc_leveltokens") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player);
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "I want to trade Emblems of Valor", GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR);
        SendGossipMenuFor(player, WOS_GOSSIP_TEXT, creature->GetGUID());
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
        else if (action == WOS_GOSSIP_VALOR) {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to boost my level", GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_LEVEL);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I need to get to Dalaran!", GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_DALARAN_TELEPORT);
            SendGossipMenuFor(player, WOS_GOSSIP_TEXT, creature->GetGUID());
        }

        // ###############
        // LEVELLING MENU
        // ###############
        else if (action == WOS_GOSSIP_VALOR_LEVEL) {
            if (cDebugging) {
                LOG_INFO("module", "{}: player opted to sell Emblem of Honor for a level...", debuggingPrefix);
            }

            const std::string itemOneLevelBoost = "I'd like 1 magic level boost, please! (x" + std::to_string(cEmblemOfValorPerLevel) + " Emblem of Valor)";
            const std::string itemTwoLevelBoost = "I'd like 2 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 2) + " Emblem of Valor)";
            const std::string itemThreeLevelBoost = "I'd like 3 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 3) + " Emblem of Valor)";
            const std::string itemFiveLevelBoost = "I'd like 5 magic level boosts, please! (x" + std::to_string(cEmblemOfValorPerLevel * 5) + " Emblem of Valor)";

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemOneLevelBoost, GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_LEVEL_ONE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemTwoLevelBoost, GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_LEVEL_TWO);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemThreeLevelBoost, GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_LEVEL_THREE);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, itemFiveLevelBoost, GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_LEVEL_FIVE);
            SendGossipMenuFor(player, WOS_GOSSIP_CHITCHAT_LEVEL, creature->GetGUID());
        }
        else if (action == WOS_GOSSIP_VALOR_LEVEL_ONE) {
            if (!provideLevelingService(player, 1)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_ONE", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_GOSSIP_VALOR_LEVEL_TWO) {
            if (!provideLevelingService(player, 2)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_TWO", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_GOSSIP_VALOR_LEVEL_THREE) {
            if (!provideLevelingService(player, 3)) {
                if (cDebugging) {
                    LOG_ERROR("{}: something went wrong trying to level {} via LEVELTOKEN_GOSSIP_VALOR_LEVEL_THREE", debuggingPrefix, player->GetName());
                }

                CloseGossipMenuFor(player);
            }
        }
        else if (action == WOS_GOSSIP_VALOR_LEVEL_FIVE) {
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
        else if (action == WOS_GOSSIP_VALOR_DALARAN_TELEPORT) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cEmblemOfValorDalaranTeleport);

            ClearGossipMenuFor(player);

            if (!player_can_afford_service) {
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I'll pay you later, OK? Please?", GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_DALARAN_TELEPORT_BEG);
            }
            else {
                const std::string dalaranTransportConfirm = "I'm good for it... (x" + std::to_string(cEmblemOfValorDalaranTeleport) + " Emblem of Valor)";
                AddGossipItemFor(player, GOSSIP_ICON_CHAT, dalaranTransportConfirm, GOSSIP_SENDER_MAIN, WOS_GOSSIP_VALOR_DALARAN_TELEPORT_CONFIRM);
            }

            SendGossipMenuFor(player, WOS_GOSSIP_CHITCHAT_DALARAN_TELEPORT, creature->GetGUID());
        }
        else if (action == WOS_GOSSIP_VALOR_DALARAN_TELEPORT_BEG) {
            srand(time(NULL));
            uint32 where_to = (rand() % 5) + 1;

            if (cDebugging) {
              LOG_ERROR("module", "{}: player begged, rolled a {}", debuggingPrefix, where_to);
            }

            switch (where_to)
            {
            case 1:
                player->TeleportTo(0, -8853.722, 620.6209, 104.26269, 5.261751);
                break;
            case 2:
                player->TeleportTo(0, -8680.91, 578.11426, 96.94911, 1.008821);
                break;
            case 3:
                player->TeleportTo(0, -8719.025, 552.00916, 88.73485, 0.686802);
                break;
            case 4:
                player->TeleportTo(0, -8630.377, 884.2247, 103.18133, 2.434313);
                break;
            case 5:
                player->TeleportTo(0, -8881.17, 566.129, 99.54935, 4.515613);
                break;
            default:
                break;
            }
            CloseGossipMenuFor(player);
        }
        else if (action == WOS_GOSSIP_VALOR_DALARAN_TELEPORT_CONFIRM) {
            uint32 emblem_count;
            bool player_can_afford_service;
            std::tie(player_can_afford_service, emblem_count) = playerHasEnoughEmblems(player, cEmblemOfValorDalaranTeleport);

            if (!player_can_afford_service) {
                ChatHandler(player->GetSession()).SendSysMessage("What? Get out of here. I aint no charity! I got clones to, ya know... clone!");
            }
            else {
                CloseGossipMenuFor(player);

                // Dalaran standard location from in-game `.teleport` GM command.
                player->TeleportTo(571, 5799.4863, 628.659, 647.4058, 1.171117);
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
    }
};

// Add all scripts in one
void AddWoSScripts()
{
    new WoSConfiguration();
    new WoSNPC();
    new WoS();
}
