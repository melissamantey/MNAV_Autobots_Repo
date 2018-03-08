DROP TABLE IF EXISTS `Registry`;
DROP TABLE IF EXISTS `Users`;
create table if not exists `Registry` (
	`entry_number` integer auto_increment primary key, 
	`user_id` char(40) not null,
	`latitude` varchar(40) not null,
	`longitude` varchar(40) not null,
	`velocity` varchar(40),
	`steering_angle` varchar(40) not null,
	`acceleration` varchar(40) not null,
	`time_stamp` varchar(40) not null,
	`error_message` boolean not null
);
create table if not exists `Users` (
	`user_id` char(40) primary key
);
