
SET
@Entry    := 8376,
@NPCFlag  := 1,
@UnitFlags2 := 0,
@FlagsExtra := 16777216,
@Script   := "npc_wos_mechanical_chicken";

UPDATE creature_template SET npcflag = @NPCFlag, unit_flags2=@UnitFlags2, flags_extra=@FlagsExtra, ScriptName = @Script WHERE entry = @Entry;
