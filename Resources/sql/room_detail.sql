CREATE TABLE IF NOT EXISTS `room_detail`
   (`id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `room_id` int(11) NOT NULL,
    `turn` int(2) NOT NULL DEFAULT '0',
    `my_hp` int(11) NOT NULL DEFAULT '500',
    `my_magic_id` int(11),
    `opp_hp` int(11) NOT NULL DEFAULT '500',
    `opp_magic_id` int(11),
    `created_at` int(11) NOT NULL DEFAULT '0',
    `updated_at` int(11) NOT NULL DEFAULT '0',
    `deleted_at` int(11) NOT NULL DEFAULT '0',
    `active` int(2) NOT NULL DEFAULT '1')
;
