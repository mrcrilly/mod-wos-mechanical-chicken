
#include "ScriptMgr.h"
#include "ScriptedGossip.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

// Customer header file
#include "LevelTokens.h"

class LevelTokens : public PlayerScript
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
            LOG_ERROR("module", "Level Tokens (DEBUGGING): Chance: {} vs. Roll: {}", chance, roll);
        }

        return roll <= chance;
    }

public:
    LevelTokens() : PlayerScript("LevelTokens") { }

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
            LOG_ERROR("module", "A player completed a quest: {}", player->GetName());
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
            LOG_ERROR("module", "Level Tokens (DEBUGGING): A player killed a creature: {} vs. {}", player->GetName(), victim->GetName());
        }

        if (!player->isHonorOrXPTarget(victim)) {
            return; // has to yield XP or (PVP) honor
        }

        bool winner = false;

        // Well the player can never lose
        if (cChanceForCreatureKill >= 100) {
            winner = true;
        }

        // The player can never win
        if (!winner && cChanceForCreatureKill <= 0) {
            return;
        }

        // Roll for it
        if (!winner && !diceRollWinner(cChanceForCreatureKill)) {
            return; // loser
        }

        // Winner!
        // TODO: work on creature types to improve
        player->AddItem(emblemOfValor, 1);
        informPlayerOfPrize(player, MSG_CREATURE_KILL);
    }
};

class LevelTokensNPC : public CreatureScript
{
public:

    LevelTokensNPC() : CreatureScript("npc_leveltokens") {}

    bool OnGossipHello(Player* player, Creature* creature)
    {
        ClearGossipMenuFor(player); 
        AddGossipItemFor(player, GOSSIP_ICON_TALK, "I want to trade Emblems of Honor", GOSSIP_SENDER_MAIN, LEVELTOKEN_GOSSIP_HONOR);
        SendGossipMenuFor(player, LEVELTOKEN_GOSSIP_TEXT, creature->GetGUID());
        return true;
    }

    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action)
    {
        if (sender != GOSSIP_SENDER_MAIN)
            return false;

        if (action == 1) {
            OnGossipHello(player, creature);
        }

        else if (action == LEVELTOKEN_GOSSIP_HONOR) {
            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I want to level", GOSSIP_SENDER_MAIN, LEVELTOKEN_GOSSIP_HONOR_LEVEL);
            SendGossipMenuFor(player, LEVELTOKEN_GOSSIP_TEXT, creature->GetGUID());
        }

        else if (action == LEVELTOKEN_GOSSIP_HONOR_LEVEL) {
            if (cDebugging) {
                LOG_INFO("module", "Level Tokens (DEBUGGING): player opted to sell Emblem of Honor for a level...");
            }

            ClearGossipMenuFor(player);
            AddGossipItemFor(player, GOSSIP_ICON_CHAT, "I'd like one magic level boost, please! (3xEmblem of Valor)", GOSSIP_SENDER_MAIN, LEVELTOKEN_GOSSIP_HONOR_LEVEL_ONE);
            SendGossipMenuFor(player, LEVELTOKEN_GOSSIP_TEXT, creature->GetGUID());
        }

        else if (action == LEVELTOKEN_GOSSIP_HONOR_LEVEL_ONE) {
            uint32 emblem_count = player->GetItemCount(emblemOfValor, true);
            LOG_INFO("module", "Level Tokens (DEBUGGING): the player has {} emblems", emblem_count);

            if (emblem_count < 3) {
                ChatHandler(player->GetSession()).SendSysMessage("You need more Emblems for that service, sorry!");
                CloseGossipMenuFor(player);
                return true;
            }

            uint32 player_level = player->getLevel();

            if (player_level == 80) {
                ChatHandler(player->GetSession()).SendSysMessage("You can't level anymore! You're already at max cap. Maybe buy a trinket?");
                CloseGossipMenuFor(player);
                return true;
            }

            player->DestroyItemCount(emblemOfValor, 3, true);
            player->GiveLevel(player_level + 1);
            CloseGossipMenuFor(player);
        }

        return true;
    }

};


class LevelTokensConfiguration : public WorldScript
{

public:
    LevelTokensConfiguration() : WorldScript("LevelTokensConfiguration") {}

    void OnStartup() override
    {
        if (cDebugging) {
            // Report to admin our configuration
            LOG_INFO("server.loading", "Initialize Level Tokens...");
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDailyQuestsEnabled: {}", cDailyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cWeeklyQuestsEnabled: {}", cWeeklyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyNormalEnabled: {}", cDungeonDifficultyNormalEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyHeroicEnabled: {}", cWeeklyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyEpicEnabled: {}", cDungeonDifficultyEpicEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cChanceForCreatureKill: {}", cChanceForCreatureKill);
        }
    }

    void OnAfterConfigLoad(bool reload) override
    {
        // Meta
        cModuleEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Enable", 1);

        if (cModuleEnabled) {
            if (cDebugging) {
                LOG_INFO("module", "Level Tokens (DEBUGGING): cModuleEnabled: {}", cModuleEnabled);
            }
        }
        else {
            return;
        }

        // Quest types
        cDailyQuestsEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Daily.Enabled", 1);
        cWeeklyQuestsEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Weekly.Enabled", 1);

        // Dungeon difficulties
        cDungeonDifficultyNormalEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Dungeon.Difficulty.Normal.Enabled", 1);
        cDungeonDifficultyHeroicEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Dungeon.Difficulty.Heroic.Enabled", 1);
        cDungeonDifficultyEpicEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Dungeon.Difficulty.Epic.Enabled", 1);

        // Chance
        cChanceForCreatureKill = sConfigMgr->GetOption<uint32>("LevelTokens.Chance.CreatureKill", 5);
    }
};

// Add all scripts in one
void AddLevelTokensScripts()
{
    new LevelTokensConfiguration();
    new LevelTokensNPC();
    new LevelTokens();
}
