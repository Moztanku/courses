--1)
	CREATE DATABASE db_aparaty;
	CREATE USER '268490'@'localhost' IDENTIFIED BY 'Jacek490';
	GRANT SELECT,INSERT,UPDATE ON db_aparaty.* TO '268490'@'localhost';
--2)
--a)
	CREATE TABLE Aparat(
		model varchar(30),
		producent int,
		matryca int,
		obiektyw int,
		typ enum('kompaktowy','lustrzanka','profesjonalny','inny'),
		PRIMARY KEY (model),
		FOREIGN KEY (producent) REFERENCES Producent(ID),
		FOREIGN KEY (matryca) REFERENCES Matryca(ID),
		FOREIGN KEY (obiektyw) REFERENCES Obiektyw(ID),
		CONSTRAINT CHK_Aparat CHECK (producent >= 1 AND producent >= 1 AND matryca >= 100)
	);
--b)
	CREATE TABLE Matryca(
		ID int AUTO_INCREMENT,
		przekatna decimal(4,2),
		rozdzielczosc decimal(3,1),
		typ varchar(10),
		PRIMARY KEY(ID),
		CONSTRAINT CHK_Matryca CHECK (przekatna >= 0 AND rozdzielczosc >= 0)
	) AUTO_INCREMENT=100;
--c)
	CREATE TABLE Obiektyw(
		ID int AUTO_INCREMENT,
		model varchar(30),
		minPrzeslona float,
		maxPrzeslona float,
		PRIMARY KEY(ID),
		CONSTRAINT CHK_Obiektyw CHECK (minPrzeslona >= 0 AND maxPrzeslona >= 0 AND maxPrzeslona > minPrzeslona)
	);
--d)
	CREATE TABLE Producent(
		ID int AUTO_INCREMENT,
		nazwa varchar(50),
		kraj varchar(20),
		PRIMARY KEY(ID)
	);
--3)
	INSERT INTO Producent (nazwa,kraj)
	VALUES ("Nikon","Chiny"),("Sony","Chiny"),("Samsung","Chiny"),
	("Mr. Magic","Chiny"),("Prata","Chiny"),("Nietzsche","Polska"),
	("Kuratowski","Polska"),("Fadiman","Polska"),("Soplica","Polska"),
	("Boos","USA"),("Casio","USA"),("Nokia","USA"),
	("Adobe","USA"),("Wacom","Niemcy"),("Hykker","Izrael");
--
	INSERT INTO Obiektyw (model,minPrzeslona,maxPrzeslona)
	VALUES ("Bateman",0.5,2.0),("Durden",0.5,2.0),("Gosling",0.5,2.0),("Bickle",0.5,2.0),
	("Ford",1.0,16.0),("Walter",2.0,4.0),("White",2.0,16.0),("Skyler",2.0,32.0),("Gus",2.0,64.0),
	("Saul",4.0,128.0),("Finger",4.0,256.0),("Cocainer",4.0,512.0),("Chicanery",1.0,1024.0),("Sunroof",1.0,2048.0),
	("Precious",1.0,999.0);
--
	INSERT INTO Matryca (przekatna,rozdzielczosc,typ)
	VALUES (12.25,50.0,"CMOS"),(35.00,10.8,"CMOS"),(75.25,70.32,"CMOS"),(10.00,70.0,"CMOS"),(25.50,99.0,"CMOS"),
	(12.25,50.0,"CCD"),(35.00,10.8,"CCD"),(75.25,70.32,"CCD"),(10.00,70.0,"CCD"),(25.50,99.0,"CCD"),
	(12.25,50.0,"BSI CMOS"),(35.00,10.8,"BSI CMOS"),(75.25,70.32,"BSI CMOS"),(10.00,70.0,"BSI CMOS"),(25.50,99.0,"BSI CMOS");
--
	INSERT INTO Producent(nazwa,kraj)
	VALUES ("nazwa-nazwa","Demokratyczna Republika Wysp Świętego Tomasza i Książęcej");
--
	INSERT INTO Obiektyw(minPrzeslona,maxPrzeslona)
	VALUES (1.0,-1.0),(-2.0,0.0),(0.0,0.0);
--
	INSERT INTO Matryca(przekatna)
	VALUES (-10.0);
--4)
	DELIMITER $$
	DROP PROCEDURE IF EXISTS generateAparat$$
	CREATE PROCEDURE generateAparat()
	BEGIN
		DECLARE pro int;
		DECLARE mat int;
		DECLARE obi int;
		DECLARE t enum('kompaktowy','lustrzanka','profesjonalny','inny');

		SET @n = (SELECT COUNT(*) FROM Aparat);
		SET @mod=CONCAT("Aparat_",@n);
		
		WHILE (EXISTS(SELECT * FROM Aparat WHERE model = @mod)) DO
			SET @n = @n + 1;
			SET @mod=CONCAT("Aparat_",@n);
		END WHILE;

		SET @temp=FLOOR(RAND()*4);
		IF @temp = 0 THEN 
			SET t='kompaktowy';
		ELSEIF @temp = 1 THEN 
			SET t='lustrzanka';
		ELSEIF @temp = 2 THEN
			SET t='profesjonalny';
		ELSE
			SET t='inny';
		END IF;

		SELECT ID INTO pro FROM Producent ORDER BY RAND() LIMIT 1;
		SELECT ID INTO mat FROM Matryca ORDER BY RAND() LIMIT 1;
		SELECT ID INTO obi FROM Obiektyw ORDER BY RAND() LIMIT 1;

		INSERT INTO Aparat (model,producent,matryca,obiektyw,typ)
		VALUES (@mod,pro,mat,obi,t);
	END$$
	DELIMITER ;
--
	DELIMITER $$
	DROP PROCEDURE IF EXISTS generateAparats$$
	CREATE PROCEDURE generateAparats(n INT)
	BEGIN
		WHILE n > 0 DO
			CALL generateAparat();
			SET n = n - 1;
		END WHILE;
	END$$
	DELIMITER ;
--5)
	DELIMITER $$
	CREATE FUNCTION maxMatryca(pro INT)
	RETURNS varchar(30) DETERMINISTIC
	BEGIN
		RETURN (select a.model from Aparat a JOIN Matryca m ON a.matryca = m.ID where producent = pro order by m.przekatna DESC limit 1);
	END$$
	DELIMITER ;
--6)
	DELIMITER $$
	DROP TRIGGER IF EXISTS t1;
	CREATE TRIGGER t1 BEFORE INSERT ON Aparat
	FOR EACH ROW
	BEGIN
		IF New.producent NOT IN (SELECT ID FROM Producent) THEN
			INSERT INTO Producent (ID,nazwa,kraj)
			VALUES (New.producent,CONCAT("Producent ",New.model),"Nie ustalony");
		END IF;
	END$$
	DELIMITER ;
--7)
	DELIMITER $$
	CREATE FUNCTION countAparaty(mat INT)
	RETURNS INT DETERMINISTIC
	BEGIN
		RETURN (SELECT COUNT(*) FROM Aparat WHERE matryca = mat);
	END$$
	DELIMITER ;
--8)
	DELIMITER $$
	DROP TRIGGER IF EXISTS t2;
	CREATE TRIGGER t2 AFTER DELETE ON Aparat
	FOR EACH ROW
	BEGIN
		IF (select count(*) from Aparat where matryca = Old.matryca) = 0 THEN
			DELETE FROM Matryca WHERE ID = Old.matryca;
		END IF;
	END$$
	DELIMITER ;
--9)
	CREATE VIEW view1 as (
		select
			a.model as 'Model',
			p.nazwa as 'Producent',
			m.przekatna as 'Przekątna',
			m.rozdzielczosc as 'Rozdzielczość',
			o.minPrzeslona as 'Przesłona min.',
			o.maxPrzeslona as 'Przesłona max.'
		from(
			((Aparat a join Producent p on a.producent = p.ID) join Matryca m on a.matryca = m.ID) join Obiektyw o on a.obiektyw = o.ID
		)
		where(
			a.typ = 'lustrzanka' AND p.kraj <> "Chiny"
		)
	);
--10)
	CREATE VIEW view2 as (
		select
			a.model as 'Model',
			p.nazwa as 'Producent',
			p.kraj as 'Kraj'
		from 
			Aparat a join Producent p on a.producent = p.ID
	);
--11)
	ALTER TABLE Producent 
	ADD liczbaModeli INT NOT NULL;
--// On insert
	DELIMITER $$
	DROP TRIGGER IF EXISTS t3Ins;
	CREATE TRIGGER t3Ins AFTER INSERT ON Aparat
	FOR EACH ROW
	BEGIN
		update Producent set liczbaModeli = liczbaModeli + 1 where ID = New.producent;
	END$$
	DELIMITER ;
--// On delete
	DELIMITER $$
	DROP TRIGGER IF EXISTS t3Del;
	CREATE TRIGGER t3Del AFTER DELETE ON Aparat
	FOR EACH ROW
	BEGIN
		update Producent set liczbaModeli = liczbaModeli - 1 where ID = Old.producent;
	END$$
	DELIMITER ;
--// On update
	DELIMITER $$
	DROP TRIGGER IF EXISTS t3Upd;
	CREATE TRIGGER t3Upd AFTER UPDATE ON Aparat
	FOR EACH ROW
	BEGIN
		update Producent set liczbaModeli = liczbaModeli - 1 where ID = Old.producent;
		update Producent set liczbaModeli = liczbaModeli + 1 where ID = New.producent;
	END$$
	DELIMITER ;	