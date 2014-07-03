CREATE TABLE IF NOT EXISTS `data_boss`
   (`id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `name` varchar(256) NOT NULL,
    `element_identifer` int(11) NOT NULL,
    `stage_id` int(11) NOT NULL,
    `message_start` varchar(256) NOT NULL,
    `message_win` varchar(256) NOT NULL,
    `message_lose` varchar(256) NOT NULL,
    `created_at` int(11) NOT NULL DEFAULT '0',
    `updated_at` int(11) NOT NULL DEFAULT '0',
    `deleted_at` int(11) NOT NULL DEFAULT '0',
    `active` int(2) NOT NULL DEFAULT '1')
;
