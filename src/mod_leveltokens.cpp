/*
 * Copyright (C) 2016+ AzerothCore <www.azerothcore.org>, released under GNU AGPL v3 license: https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3
 */

#include "ScriptMgr.h"
#include "Player.h"
#include "Config.h"
#include "Chat.h"

const std::vector<int> fortune_cookies{
    19229, // Sayge's Fortune #1
    19256, // Sayge's Fortune #2
    19238, // Sayge's Fortune #3
    19239, // Sayge's Fortune #4
    19240, // Sayge's Fortune #5
    19241, // Sayge's Fortune #6
    19242, // Sayge's Fortune #7
    19243, // Sayge's Fortune #8
    19244, // Sayge's Fortune #9
    19245, // Sayge's Fortune #10
    19246, // Sayge's Fortune #11
    19247, // Sayge's Fortune #12
    19248, // Sayge's Fortune #13
    19249, // Sayge's Fortune #14
    19250, // Sayge's Fortune #15
    19251, // Sayge's Fortune #16
    // Change is order NOT a mistake - don't "fix"
    19253, // Sayge's Fortune #17
    19252, // Sayge's Fortune #18
    19237, // Sayge's Fortune #19
    19266, // Sayge's Fortune #20
    19254, // Sayge's Fortune #21
    19255, // Sayge's Fortune #22
    19423, // Sayge's Fortune #23
    19424, // Sayge's Fortune #24
    19443, // Sayge's Fortune #25
    19451, // Sayge's Fortune #26
    19452, // Sayge's Fortune #27
    19453, // Sayge's Fortune #28
    19454, // Sayge's Fortune #29
};

// Emblem of Heroism
const uint32 questCompleteItem = 40752;

// Debugging
bool cDebugging = true;

// Configuration
bool cModuleEnabled = true;
bool cDailyQuestsEnabled = true;
bool cWeeklyQuestsEnabled = true;
bool cDungeonDifficultyNormalEnabled = true;
bool cDungeonDifficultyHeroicEnabled = true;
bool cDungeonDifficultyEpicEnabled = true;
uint32 cChanceForCreatureKill = 10;

const std::string MSG_QUEST_COMPLETE = "You've earned a Sayge Fortune Token! Complete the quest, or trade it in for other prizes.";
const std::string MSG_CREATURE_KILL = "Nice kill! Have a Sayge Fortune Token for your trobules.";

// Add player scripts
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
            ChatHandler(player->GetSession()).SendSysMessage("This realm uses the Sayge Fortune Token System - you lucky bastard!");
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

        player->AddItem(questCompleteItem, count);
        informPlayerOfPrize(player, MSG_QUEST_COMPLETE);
    }

    void OnCreatureKill(Player* player, Creature* victim) override
    {
        if (cDebugging) {
            LOG_ERROR("module", "Level Tokens (DEBUGGING): A player killed a creature: {} vs. {}", player->GetName(), victim->GetName());
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
        player->AddItem(questCompleteItem, 1);
        informPlayerOfPrize(player, MSG_CREATURE_KILL);
    }
};

class LevelTokensConfiguration : public WorldScript
{

public:
    LevelTokensConfiguration() : WorldScript("LevelTokensConfiguration") {}

    void OnStartup() override
    {
        LOG_INFO("server.loading", "Initialize Level Tokens...");
    }

    void OnAfterConfigLoad(bool reload) override
    {
        // Meta
        cModuleEnabled = sConfigMgr->GetOption<bool>("LevelTokens.Enable", 1);

        if (cModuleEnabled) {
            LOG_ERROR("module", "Level Tokens (DEBUGGING): cModuleEnabled: {}", cModuleEnabled);
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
        cChanceForCreatureKill = sConfigMgr->GetOption<uint32>("LevelTokens.Chance.CreatureKill", 1);

        if (cDebugging) {
            // Report to admin our configuration
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDailyQuestsEnabled: {}", cDailyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cWeeklyQuestsEnabled: {}", cWeeklyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyNormalEnabled: {}", cDungeonDifficultyNormalEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyHeroicEnabled: {}", cWeeklyQuestsEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cDungeonDifficultyEpicEnabled: {}", cDungeonDifficultyEpicEnabled);
            LOG_INFO("module", "Level Tokens (DEBUGGING): cChanceForCreatureKill: {}", cChanceForCreatureKill);
        }
    }
};

// Add all scripts in one
void AddLevelTokensScripts()
{
    new LevelTokensConfiguration();
    new LevelTokens();
}
