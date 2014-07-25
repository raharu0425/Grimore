CREATE TABLE IF NOT EXISTS `room`
   (`id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `condition` int(11) NOT NULL DEFAULT '1',
    `boss_id` int(11) NOT NULL DEFAULT '0',
    `stage_id` int(11) NOT NULL DEFAULT '0',
    `turn` int(11) NOT NULL DEFAULT '0',
    `my_name` varchar(256) NOT NULL,
    `opp_name` varchar(256) NOT NULL,
    `created_at` int(11) NOT NULL DEFAULT '0',
    `updated_at` int(11) NOT NULL DEFAULT '0',
    `deleted_at` int(11) NOT NULL DEFAULT '0',
    `active` int(2) NOT NULL DEFAULT '1')
;
