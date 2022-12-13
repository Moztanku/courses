-- 1)

CREATE DATABASE firma;

CREATE TABLE firma.Ludzie (
    PESEL VARCHAR(11) PRIMARY KEY NOT NULL, --  Pesel to dobry klucz ponieważ jest unikalny
    Imie VARCHAR(30) NOT NULL,
    Nazwisko VARCHAR(30) NOT NULL,
    Data_urodzenia DATE NOT NULL,
    Plec ENUM('M', 'K') NOT NULL,
    CHECK (PESEL REGEXP '^[0-9]{11}$')
);

CREATE TABLE firma.Zawody (
    zawod_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
    nazwa VARCHAR(50) NOT NULL,
    pensja_min float NOT NULL,
    pensja_max float NOT NULL,
    CHECK (pensja_min < pensja_max)
);

CREATE TABLE firma.Pracownicy (
    PESEL CHAR(11) NOT NULL,
    zawod_id INT NOT NULL,
    pensja float NOT NULL,
    FOREIGN KEY (PESEL) REFERENCES firma.Ludzie(PESEL),
    FOREIGN KEY (zawod_id) REFERENCES firma.Zawody(zawod_id)
);

-- Insert into Ludzie 5 records
INSERT INTO firma.Ludzie (PESEL, Imie, Nazwisko, Data_urodzenia, Plec)
VALUES ('05251178211', 'Jacek', 'Kowalski', '2005-05-11', 'M'),
       ('05232378312', 'Jadek', 'Kowblski', '2005-03-23', 'M'),
       ('06273078413', 'Jagek', 'Kowclski', '2006-07-30', 'M'),
       ('07300178514', 'Jahek', 'Kowdlski', '2007-10-01', 'M'),
       ('08311478715', 'Jaiek', 'Kowelski', '2008-11-14', 'M');


DELIMITER $$
DROP procedure IF EXISTS `firma`.`generateCzlowiek`$$
CREATE PROCEDURE `firma`.`generateCzlowiek`(a INT, b INT)
BEGIN
    DECLARE p VARCHAR(11);
    DECLARE i VARCHAR(30);
    DECLARE n VARCHAR(30);
    DECLARE d DATE;
    DECLARE pl ENUM('M', 'K');

    -- pl as M or K
    SET pl = IF(RAND() < 0.5, 'M', 'K');
    SET i = IF(pl = 'M', 'Jan', 'Anna');
    SET n = IF(pl = 'M', 'Kowalski', 'Kowalska');
    -- between 18 and 60 years old
    SET d = DATE_ADD(NOW(), INTERVAL -FLOOR(RAND() * 365 * (b-a) + 365 * a) DAY);
    -- PESEL
    SET p = CONCAT(
        DATE_FORMAT(d, '%y%m%d'),
        LPAD(FLOOR(RAND() * 999), 3, '0'),
        IF(pl = 'M', FLOOR(RAND() * 5) * 2 + 1, FLOOR(RAND() * 5) * 2)
    );
    -- PESEL checksum
    SET p = CONCAT(p, MOD(
        9 * SUBSTRING(p, 1, 1) +
        7 * SUBSTRING(p, 2, 1) +
        3 * SUBSTRING(p, 3, 1) +
        1 * SUBSTRING(p, 4, 1) +
        9 * SUBSTRING(p, 5, 1) +
        7 * SUBSTRING(p, 6, 1) +
        3 * SUBSTRING(p, 7, 1) +
        1 * SUBSTRING(p, 8, 1) +
        9 * SUBSTRING(p, 9, 1) +
        7 * SUBSTRING(p, 10, 1), 10)
    );    
    -- insert into table
    INSERT INTO firma.Ludzie (PESEL, Imie, Nazwisko, Data_urodzenia, Plec)
    VALUES (p, i, n, d, pl);
END$$
DELIMITER ;

-- Create method calling generateCzlowiek n times
DELIMITER $$
DROP procedure IF EXISTS `firma`.`generateLudzie`$$
CREATE PROCEDURE `firma`.`generateLudzie`(n INT, a INT, b INT)
BEGIN
    DECLARE i INT DEFAULT 0;
    WHILE i < n DO
        CALL firma.generateCzlowiek(a,b);
        SET i = i + 1;
    END WHILE;
END$$
DELIMITER ;

-- Insert into Zawody polityk, nauczyciel, lekarz, informatyk
INSERT INTO firma.Zawody (nazwa, pensja_min, pensja_max)
VALUES ('polityk', 3000, 25000),
       ('nauczyciel', 2500, 4000),
       ('lekarz', 5000, 12000),
       ('informatyk', 7000, 30000);

-- Create cursor for Ludzie
