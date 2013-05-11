
CREATE SCHEMA `Buddy` DEFAULT CHARACTER SET utf8 ;
CREATE  TABLE `buddy`.`Login` (
  `id` INT NOT NULL AUTO_INCREMENT ,
  `user` VARCHAR(45) NULL ,
  `pswd` VARCHAR(45) NULL ,
  `time` DATETIME NULL ,
  PRIMARY KEY (`id`) )
DEFAULT CHARACTER SET = utf8;

CREATE TABLE buddy.user(
  user VARCHAR(45) NOT NULL ,
  pwd VARCHAR(45) NOT NULL ,
  gpsTable VARCHAR(45) NULL,
  contactTable VARCHAR(45) NULL,
  PRIMARY KEY (user) 
)
DEFAULT charset = utf8;

CREATE  TABLE buddy.userInfo (
  user VARCHAR(45) NOT NULL ,
  nickName VARCHAR(45) NOT NULL ,
  signature VARCHAR(300) NULL,
  PRIMARY KEY (user) )
DEFAULT charset = utf8;

CREATE  TABLE buddy.gpsINfo (
	id INT NOT NULL AUTO_INCREMENT,
	user VARCHAR(45) NOT NULL ,
	utcTime BIGINT NOT NULL,
	latitude INT NOT NULL,
	longitude INT NOT NULL,
	address VARCHAR(45) NOT NULL ,
	PRIMARY KEY (id))
DEFAULT charset = utf8;

CREATE  TABLE buddy.contact (
	id INT NOT NULL AUTO_INCREMENT,
	friend VARCHAR(45) NOT NULL,
	PRIMARY KEY (id))
DEFAULT charset = utf8;