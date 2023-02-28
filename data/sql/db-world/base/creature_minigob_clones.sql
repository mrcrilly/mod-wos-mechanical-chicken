
SET
@Entry := 9100000,
@Model := 28315,
@Name  := "Minigob Manabonk",
@Subname := "Clone #",
@Icon  := "Speak",
@GossipMenu := 0,
@MinLevel := 80,
@MaxLevel := 80,
@Faction  := 35,
@NPCFlag  := 1,
@Scale    := 1.0,
@Rank     := 2,
@Type     := 7,
@TypeFlags := 0,
@FlagsExtra := 16777218,
@Script     := "npc_wos_minigob_manabonk";

-- Clear the creature otherwise we get duplicates
DELETE FROM `creature` WHERE `id1`=@Entry + 1;
DELETE FROM `creature` WHERE `id1`=@Entry + 2;
DELETE FROM `creature` WHERE `id1`=@Entry + 3;
DELETE FROM `creature` WHERE `id1`=@Entry + 4;
DELETE FROM `creature` WHERE `id1`=@Entry + 5;
DELETE FROM `creature` WHERE `id1`=@Entry + 6;
DELETE FROM `creature` WHERE `id1`=@Entry + 7;
DELETE FROM `creature` WHERE `id1`=@Entry + 8;
DELETE FROM `creature` WHERE `id1`=@Entry + 9;
DELETE FROM `creature` WHERE `id1`=@Entry + 10;
DELETE FROM `creature` WHERE `id1`=@Entry + 11;

DELETE FROM `creature_template` WHERE `entry`=@Entry + 1;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 2;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 3;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 4;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 5;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 6;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 7;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 8;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 9;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 10;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 11;

-- ### CLONES ###

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 1, @Model, @Name, CONCAT(@Subname, "420"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 2, @Model, @Name, CONCAT(@Subname, "68"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 3, @Model, @Name, CONCAT(@Subname, "Z"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 4, @Model, @Name, "asdasdf.txt", @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 5, @Model, @Name, CONCAT(@Subname, "809"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 6, @Model, @Name, CONCAT(@Subname, "42"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 7, @Model, @Name, CONCAT(@Subname, "42.1"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 8, @Model, @Name, CONCAT(@Subname, "X"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 9, @Model, @Name, CONCAT(@Subname, "13"), @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 10, @Model, @Name, "Final Version", @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (@Entry + 11, @Model, @Name, "Final Version 2", @Icon, @GossipMenu, @MinLevel, @MaxLevel, @Faction, @NPCFlag, 1, 1, @Scale, @Rank, 1, 2, @Type, @TypeFlags, 1, @FlagsExtra, @Script);

-- ### LOCATIONS ###

SET
@MAP_EASTERN_KINGDOMS := 0,
@MAP_KALIMDOR := 1,
@MAP_OUTLAND := 530,
@MAP_NORTHREND := 571;

INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 1, @MAP_OUTLAND, -4047.368, -11569.892, -138.48938, 0.349499); -- Exodar
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 2, @MAP_OUTLAND, -1923.5654, 5164.2104, -37.793854, 0.999771); -- Shattrath
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 3, @MAP_OUTLAND, 9985.889, -7112.2866, 47.704704, 0.899436); -- Silvermoon City

INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 4, @MAP_NORTHREND, 5705.358, 748.7633, 644.86084, 6.046065); -- Dalaran (Alliance)
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 5, @MAP_NORTHREND, 5935.226, 561.7121, 639.57434, 3.115754); -- Dalaran (Horde)

INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 6, @MAP_KALIMDOR, 9639.297, 2509.855, 1333.473, 0.848170); -- Darnassus
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 7, @MAP_KALIMDOR, 1476.4816, -4202.749, 43.8331, 4.493981); -- Orgrimmar
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 8, @MAP_KALIMDOR, -949.1484, 256.04608, 97.34436, 4.143632); -- Thunder Bluff

INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 9, @MAP_EASTERN_KINGDOMS, -9002.942, 874.0727, 129.69243, 4.782641); -- Stormwind
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 10, @MAP_EASTERN_KINGDOMS, -4620.027, -938.0188, 502.76572, 2.065092); -- Ironforge
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry + 11, @MAP_EASTERN_KINGDOMS, 1777.4889, 83.023926, -59.315, 3.091523); -- Undercity
