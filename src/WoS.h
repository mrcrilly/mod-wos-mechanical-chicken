
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

// For debugging messages
const std::string debuggingPrefix = "WOS (DEBUGGING)";

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
// Simple on/off switches
bool cDebugging = true;
bool cModuleEnabled;
bool cDailyQuestsEnabled;
bool cWeeklyQuestsEnabled;
bool cDungeonDifficultyNormalEnabled;
bool cDungeonDifficultyHeroicEnabled;
bool cDungeonDifficultyEpicEnabled;

// Costs and odds/chances
uint32 cDropChanceAfterKill;
uint32 cDropChanceAfterKillElite;
uint32 cEmblemOfValorPerLevel;
uint32 cEmblemOfValorDalaranTeleport;
uint32 cEmblemOfValorFlightPaths;

// The messages used to inform the player of actions taken
// against their currency/bank.
const std::string MSG_QUEST_COMPLETE = "You've earned a token! Trade it in for other prizes.";
const std::string MSG_CREATURE_KILL = "Nice kill! Have a token for your troubles.";

enum GossipId
{
    // The basic "Greetings, $n"
    WOS_GOSSIP_TEXT = 68,

    // Custom greetings/text
    WOS_GOSSIP_CHITCHAT_DALARAN_TELEPORT = 3000000,
    WOS_GOSSIP_CHITCHAT_FLIGHT_PATHS = 3000001,
    WOS_GOSSIP_CHITCHAT_LEVEL = 3000002,

    // The Emblem of Honor gossip menus
    // Top level menu:
    WOS_GOSSIP_VALOR = 1000,

    // I want to boost my level as the grind it too much
    WOS_GOSSIP_VALOR_LEVEL = 1100,
    WOS_GOSSIP_VALOR_LEVEL_ONE = 1101,
    WOS_GOSSIP_VALOR_LEVEL_TWO = 1102,
    WOS_GOSSIP_VALOR_LEVEL_THREE = 1103,
    WOS_GOSSIP_VALOR_LEVEL_FIVE = 1104,

    // I want to learn about flight master locations
    WOS_GOSSIP_VALOR_FLIGHT_PATHS = 1200,
    WOS_GOSSIP_VALOR_FLIGHT_PATHS_CONFIRM = 1201,

    // I need a quick get away to Dalaran, stat!
    WOS_GOSSIP_VALOR_DALARAN_TELEPORT = 1300,
    WOS_GOSSIP_VALOR_DALARAN_TELEPORT_CONFIRM = 1301,
    WOS_GOSSIP_VALOR_DALARAN_TELEPORT_BEG = 1302,
};
