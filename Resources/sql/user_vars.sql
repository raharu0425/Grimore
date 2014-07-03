CREATE TABLE IF NOT EXISTS `user_vars`
   (`id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `key` varchar(256) NOT NULL,
    `value` varchar(256) NOT NULL,
    `value` varchar(256) NOT NULL,
    `created_at` int(11) NOT NULL DEFAULT '0',
    `updated_at` int(11) NOT NULL DEFAULT '0',
    `deleted_at` int(11) NOT NULL DEFAULT '0',
    `active` int(2) NOT NULL DEFAULT '1')
;
