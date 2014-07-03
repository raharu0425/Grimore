CREATE TABLE IF NOT EXISTS `data_magic`
   (`id` INTEGER PRIMARY KEY AUTOINCREMENT,
    `rank` int(2) NOT NULL ,
    `name` varchar(256) NOT NULL,
    `param_attack` int(8) NOT NULL DEFAULT '0',
    `param_cure` int(8) NOT NULL DEFAULT '0',
    `param_stan` int(8) NOT NULL DEFAULT '0',
    `created_at` int(11) NOT NULL DEFAULT '0',
    `updated_at` int(11) NOT NULL DEFAULT '0',
    `deleted_at` int(11) NOT NULL DEFAULT '0',
    `active` int(2) NOT NULL DEFAULT '1')
;
