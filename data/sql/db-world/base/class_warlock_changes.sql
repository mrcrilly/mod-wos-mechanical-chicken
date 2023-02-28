
-- Allowing Warlocks to stack Soul Shards into stacks of 10.
DELETE FROM `item_template` WHERE entry = 6265;
INSERT INTO `item_template` (`entry`, `name`, `stackable`) VALUES (6265, 'Soul Shard', 10);
