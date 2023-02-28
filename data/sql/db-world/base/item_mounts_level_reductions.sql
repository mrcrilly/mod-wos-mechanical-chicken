
-- These are all the basics race mounts. The cheap, 60% ones.
SET
@mountAllianceHumanBasic := 2411,
@mountAllianceDwarfBasic := 5864,
@mountAllianceNightElfBasic := 8629,
@mountAllianceGnomeBasic := 13322,
@mountAllianceDraineiBasic := 28481,
@mountHordeOrcBasic := 5665,
@mountHordeUndeadBasic := 13331,
@mountHordeTaurenBasic := 15277,
@mountHordeTrollBasic := 8588,
@mountHordeBloodElfBasic := 29221;

-- Update these basic mounts to be usable at level 1
-- Riding skill 75 will be taught to the player, so leaving
-- that alone here.
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountAllianceHumanBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountAllianceDwarfBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountAllianceNightElfBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountAllianceGnomeBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountAllianceDraineiBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountHordeOrcBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountHordeUndeadBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountHordeTaurenBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountHordeTrollBasic;
UPDATE item_template SET RequiredLevel=1 WHERE entry=@mountHordeBloodElfBasic;
