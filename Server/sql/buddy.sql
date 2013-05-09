USE buddy
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
	user VARCHAR(45) NOT NULL,
	utcTime BIGINT NOT NULL,
	latitude INT NOT NULL,
	longitude INT NOT NULL,
	accuracy INT NOT NULL,
	altitude INT NOT NULL,
	speed INT NOT NULL,
	PRIMARY KEY (id))
DEFAULT charset = utf8;

CREATE  TABLE buddy.contact (
	id INT NOT NULL AUTO_INCREMENT,
	user VARCHAR(45) NOT NULL ,
	friend VARCHAR(45) NOT NULL,
	PRIMARY KEY (id))
DEFAULT charset = utf8;