
// fortune_cookies are handed at random when you kill a creature,
// complete quest, or some other conditions are met. This is just
// a bit of fun, in short.
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

// The emblems are the end-game currency being awarded
// to the player earlier on in the game for actions like
// killing creatures, completing quests, etc.

// The Emblem of Heroism is handed out for completing quests
// and killing normal creatures.
const uint32 emblemOfHeroism = 40752;

// The Emblem of Valor is handed out for killing Elite
// creatures (of any kind, anywhere.)
const uint32 emblemOfValor = 40753;

// Configuration
bool cDebugging = true;
bool cModuleEnabled;
bool cDailyQuestsEnabled;
bool cWeeklyQuestsEnabled;
bool cDungeonDifficultyNormalEnabled;
bool cDungeonDifficultyHeroicEnabled;
bool cDungeonDifficultyEpicEnabled;
uint32 cChanceForCreatureKill;

// The messages used to inform the player of actions taken
// against their currency/bank.
const std::string MSG_QUEST_COMPLETE = "You've earned a token! Trade it in for other prizes.";
const std::string MSG_CREATURE_KILL = "Nice kill! Have a token for your troubles.";

enum GossipId
{
    LEVELTOKEN_GOSSIP_TEXT = 68,
    LEVELTOKEN_GOSSIP_HONOR = 1000,
    LEVELTOKEN_GOSSIP_HONOR_LEVEL = 1001,
    LEVELTOKEN_GOSSIP_HONOR_LEVEL_ONE = 1002,
};
