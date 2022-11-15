
SET
@Entry := 9100000,
@Model := 28315,
@Name  := "Minigob Manabonk",
@Title := "Clone #",
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
@Script     := "npc_leveltokens";

-- Clear the creature otherwise we get duplicates
DELETE FROM `creature` WHERE `id1`=@Entry; -- clear me
DELETE FROM `creature` WHERE `id1`=@Entry + 1;
DELETE FROM `creature` WHERE `id1`=@Entry + 2;
DELETE FROM `creature_template` WHERE `entry`=@Entry; -- clear me
DELETE FROM `creature_template` WHERE `entry`=@Entry + 1;
DELETE FROM `creature_template` WHERE `entry`=@Entry + 2;

-- Creature template for "Clone #420"
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (
      @Entry + 1,
      @Model,
      @Name,
      CONCAT(@Title, "420"),
      @Icon,
      @GossipMenu,
      @MinLevel,
      @MaxLevel,
      @Faction,
      @NPCFlag,
      1,
      1,
      @Scale,
      @Rank,
      1,
      2,
      @Type,
      @TypeFlags,
      1,
      @FlagsExtra,
      @Script
 );

-- Creature template for "Clone #68"
INSERT INTO `creature_template` (`entry`, `modelid1`, `name`, `subname`, `IconName`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `speed_walk`, `speed_run`, `scale`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `RegenHealth`, `flags_extra`, `ScriptName`)
  VALUES (
      @Entry + 2,
      @Model,
      @Name,
      CONCAT(@Title, "68"),
      @Icon,
      @GossipMenu,
      @MinLevel,
      @MaxLevel,
      @Faction,
      @NPCFlag,
      1,
      1,
      @Scale - 0.2,
      @Rank,
      1,
      2,
      @Type,
      @TypeFlags,
      1,
      @FlagsExtra,
      @Script
 );


-- ### Locations ###

-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 0, -8824.65, 649.467, 94.5585, 4.47955); -- Stormwind
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 0, -4978.68, -947.674, 501.66, 5.0182); -- Ironforge
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 1, 9949.92, 2498.44, 1317.8, 4.44686); -- Darnassus
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 530, -3911.11, -11606.3, -138.326, 4.73595); -- Exodar
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 1, 1675.72, -4424.67, 18.8421, 2.39778); -- Orgrimmar
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 1, -1271.36, 132.402, 132.023, 4.57086); -- Thunder Bluff
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 0, 1555.03, 246.513, -43.1027, 0.073205); -- Undercity
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 530, 9469.83, -7294.44, 14.3078, 0.105431); -- Silvermoon City
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 530, -1832.44, 5389.19, -12.4279, 2.3428); -- Shattrath
-- INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`) VALUES (@Entry, 571, 5792.65, 636.492, 647.39, 0.00637221); -- Dalaran

-- Stormwind: Clone #420
SET
@StormwindPositionX := -8823.121,
@StormwindPositionY := 646.99866,
@StormwindPositionZ := 94.477486,
@StormwindPositionO := 4.148044;
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`)
  VALUES (@Entry + 1, 0, @StormwindPositionX, @StormwindPositionY, @StormwindPositionZ, @StormwindPositionO);

-- Stormwind: Clone #68
SET
@StormwindPositionX := -8821.058,
@StormwindPositionY := 644.09045,
@StormwindPositionZ := 94.28773,
@StormwindPositionO := 3.900631;
INSERT INTO `creature` (`id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`)
  VALUES (@Entry + 2, 0, @StormwindPositionX, @StormwindPositionY, @StormwindPositionZ, @StormwindPositionO);

