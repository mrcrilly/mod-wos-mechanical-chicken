
-- SET
-- @Entry := 9200000,
-- @Model := 3944, -- undead female, mage like
-- @Name  := "Aimee Woodhouse",
-- @Subname := "Master Explorer",
-- @GossipMenu := 0,
-- @MinLevel := 55,
-- @MaxLevel := 55,
-- @Faction  := 68, -- undead?
-- @NPCFlag  := 3,
-- @Rank     := 4,
-- @Type     := 7,
-- @TypeFlags := 0,
-- @FlagsExtra := 16777218;

-- -- Clear the creature otherwise we get duplicates
-- DELETE FROM `creature` WHERE `id1`=@Entry + 1;
-- DELETE FROM `creature_template` WHERE `entry`=@Entry + 1;

-- INSERT INTO `creature_template` (`
--   entry`,     `modelid1`, `name`, `subname`, `gossip_menu_id`, `minlevel`, `maxlevel`, `faction`, `npcflag`, `rank`, `unit_class`, `unit_flags`, `type`, `type_flags`, `flags_extra`
-- ) VALUES (
--   @Entry + 1, @Model,      @Name,  @Subname,   @GossipMenu,     @MinLevel,  @MaxLevel,  @Faction,  @NPCFlag,  @Rank,  1,            2,            @Type,  @TypeFlags,  @FlagsExtra
-- );

-- SET
-- @MAP_EASTERN_KINGDOMS := 0,
-- @MAP_KALIMDOR := 1,
-- @MAP_OUTLAND := 530,
-- @MAP_NORTHREND := 571;

-- INSERT INTO `creature` (
--   `id1`, `map`, `position_x`, `position_y`, `position_z`, `orientation`
-- ) VALUES (
--   @Entry + 1, @MAP_EASTERN_KINGDOMS, 1874.4473, 1608.9692, 94.03682, 4.477726
-- ); -- Deathknell
