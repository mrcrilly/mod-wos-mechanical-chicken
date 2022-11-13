SET
@Entry := 9100000,
@Model := 28315,
@Name  := "Minigob Manabonk",
@Title := "The Mischievous Mage",
@Icon  := "Speak",
@GossipMenu := 0,
@MinLevel := 80,
@MaxLevel := 80,
@Faction  := 35,
@NPCFlag  := 129,
@Scale    := 1.0,
@Rank     := 2,
@Type     := 7,
@TypeFlags := 0,
@FlagsExtra := 16777218,
@Script     := "leveltokens_npc",
@StartingPositionX := -8823.121,
@StartingPositionY := 646.99866,
@StartingPositionZ := 94.477486,
@StartingPositionO := 4.148044;

-- Creature template
DELETE FROM `creature_template` WHERE `entry`=@Entry;
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry, @Model, @Name, @Title, @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

-- Clear the creature otherwise we get duplicates
DELETE FROM `creature` WHERE `id1`=@Entry;

-- Stormwind
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`)
  VALUES (@Entry, 0, @StartingPositionX, @StartingPositionY, @StartingPositionZ, @StartingPositionO);
