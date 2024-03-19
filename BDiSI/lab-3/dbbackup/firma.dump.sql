-- MariaDB dump 10.19  Distrib 10.9.4-MariaDB, for Linux (x86_64)
--
-- Host: localhost    Database: firma
-- ------------------------------------------------------
-- Server version	10.9.4-MariaDB

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `Ludzie`
--

DROP TABLE IF EXISTS `Ludzie`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Ludzie` (
  `PESEL` varchar(11) NOT NULL,
  `Imie` varchar(30) NOT NULL,
  `Nazwisko` varchar(30) NOT NULL,
  `Data_urodzenia` date NOT NULL,
  `Plec` enum('M','K') NOT NULL,
  PRIMARY KEY (`PESEL`),
  KEY `Plec` (`Plec`,`Imie`),
  CONSTRAINT `CONSTRAINT_1` CHECK (`PESEL` regexp '^[0-9]{11}$')
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Ludzie`
--

LOCK TABLES `Ludzie` WRITE;
/*!40000 ALTER TABLE `Ludzie` DISABLE KEYS */;
INSERT INTO `Ludzie` VALUES
('01061844288','Anna','Kowalska','2001-06-18','K'),
('01072158460','Anna','Kowalska','2001-07-21','K'),
('02010475351','Jan','Kowalski','2002-01-04','M'),
('02121840099','Jan','Kowalski','2002-12-18','M'),
('03061152246','Anna','Kowalska','2003-06-11','K'),
('03092041582','Anna','Kowalska','2003-09-20','K'),
('04031074173','Jan','Kowalski','2004-03-10','M'),
('04071099895','Jan','Kowalski','2004-07-10','M'),
('05232378312','Jadek','Kowblski','2005-03-23','M'),
('05251178211','Jacek','Kowalski','2005-05-11','M'),
('06273078413','Jagek','Kowclski','2006-07-30','M'),
('07300178514','Jahek','Kowdlski','2007-10-01','M'),
('08311478715','Jaiek','Kowelski','2008-11-14','M'),
('46051804767','Anna','Kowalska','1946-05-18','K'),
('50011370045','Anna','Kowalska','1950-01-13','K'),
('50031447745','Anna','Kowalska','1950-03-14','K'),
('53121593043','Anna','Kowalska','1953-12-15','K'),
('59041816624','Anna','Kowalska','1959-04-18','K'),
('63061910853','Jan','Kowalski','1963-06-19','M'),
('63070533962','Anna','Kowalska','1963-07-05','K'),
('64100287543','Anna','Kowalska','1964-10-02','K'),
('66101725350','Jan','Kowalski','1966-10-17','M'),
('66110704744','Anna','Kowalska','1966-11-07','K'),
('67050833488','Anna','Kowalska','1967-05-08','K'),
('67110117837','Jan','Kowalski','1967-11-01','M'),
('69063097332','Jan','Kowalski','1969-06-30','M'),
('69110487086','Anna','Kowalska','1969-11-04','K'),
('71101919762','Anna','Kowalska','1971-10-19','K'),
('72030318453','Jan','Kowalski','1972-03-03','M'),
('73031447515','Jan','Kowalski','1973-03-14','M'),
('74050446408','Anna','Kowalska','1974-05-04','K'),
('76031863707','Anna','Kowalska','1976-03-18','K'),
('77122450442','Anna','Kowalska','1977-12-24','K'),
('78101417283','Anna','Kowalska','1978-10-14','K'),
('79070355899','Jan','Kowalski','1979-07-03','M'),
('79121048475','Jan','Kowalski','1979-12-10','M'),
('80022030469','Anna','Kowalska','1980-02-20','K'),
('81051684348','Anna','Kowalska','1981-05-16','K'),
('81060554412','Jan','Kowalski','1981-06-05','M'),
('81060939037','Jan','Kowalski','1981-06-09','M'),
('81101590584','Anna','Kowalska','1981-10-15','K'),
('82070405877','Jan','Kowalski','1982-07-04','M'),
('87021521172','Jan','Kowalski','1987-02-15','M'),
('89021461980','Anna','Kowalska','1989-02-14','K'),
('90123047958','Jan','Kowalski','1990-12-30','M'),
('91011474469','Anna','Kowalska','1991-01-14','K'),
('92020600504','Anna','Kowalska','1992-02-06','K'),
('92120320403','Anna','Kowalska','1992-12-03','K'),
('93011860716','Jan','Kowalski','1993-01-18','M'),
('93030984020','Anna','Kowalska','1993-03-09','K'),
('93081998915','Jan','Kowalski','1993-08-19','M'),
('95123075516','Jan','Kowalski','1995-12-30','M'),
('96102902849','Anna','Kowalska','1996-10-29','K'),
('97092026498','Jan','Kowalski','1997-09-20','M'),
('99101217857','Jan','Kowalski','1999-10-12','M');
/*!40000 ALTER TABLE `Ludzie` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Pracownicy`
--

DROP TABLE IF EXISTS `Pracownicy`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Pracownicy` (
  `PESEL` char(11) NOT NULL,
  `zawod_id` int(11) NOT NULL,
  `pensja` float NOT NULL,
  KEY `PESEL` (`PESEL`),
  KEY `zawod_id` (`zawod_id`),
  KEY `pensja` (`pensja`),
  CONSTRAINT `Pracownicy_ibfk_1` FOREIGN KEY (`PESEL`) REFERENCES `Ludzie` (`PESEL`),
  CONSTRAINT `Pracownicy_ibfk_2` FOREIGN KEY (`zawod_id`) REFERENCES `Zawody` (`zawod_id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Pracownicy`
--

LOCK TABLES `Pracownicy` WRITE;
/*!40000 ALTER TABLE `Pracownicy` DISABLE KEYS */;
INSERT INTO `Pracownicy` VALUES
('01061844288',3,20437.3),
('01072158460',3,7255.84),
('02121840099',2,3167.36),
('03061152246',3,14098.6),
('03092041582',2,3932.94),
('04031074173',3,28899.1),
('04071099895',1,13873.4),
('46051804767',1,21134.2),
('50011370045',1,5003.54),
('50031447745',2,3062.32),
('53121593043',1,23953.2),
('59041816624',1,18551.7),
('63061910853',1,20751.5),
('63070533962',2,3836.99),
('64100287543',4,12698.5),
('66101725350',2,3485.51),
('66110704744',3,18262.8),
('67050833488',2,3197.66),
('67110117837',1,5384.31),
('69063097332',2,2546.21),
('69110487086',2,3013.84),
('71101919762',4,9079.96),
('72030318453',3,9720.24),
('73031447515',3,10763.6),
('74050446408',3,30179.8),
('76031863707',4,15042),
('77122450442',3,29965.7),
('78101417283',4,15323.1),
('79070355899',4,15283.2),
('79121048475',1,22274.5),
('80022030469',1,4159.18),
('81051684348',4,11240.2),
('81060554412',2,3725.89),
('81060939037',1,14747),
('81101590584',1,22629.1),
('82070405877',1,3336.03),
('87021521172',3,14574.3),
('89021461980',3,7403.3),
('90123047958',2,3077.47),
('92020600504',1,5910.52),
('92120320403',2,2767.4),
('93030984020',4,13054),
('93081998915',1,3629.94),
('95123075516',3,23042.1),
('97092026498',4,14260.2),
('99101217857',3,15924.7);
/*!40000 ALTER TABLE `Pracownicy` ENABLE KEYS */;
UNLOCK TABLES;

--
-- Table structure for table `Zawody`
--

DROP TABLE IF EXISTS `Zawody`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `Zawody` (
  `zawod_id` int(11) NOT NULL AUTO_INCREMENT,
  `nazwa` varchar(50) NOT NULL,
  `pensja_min` float NOT NULL,
  `pensja_max` float NOT NULL,
  PRIMARY KEY (`zawod_id`),
  CONSTRAINT `CONSTRAINT_1` CHECK (`pensja_min` < `pensja_max`)
) ENGINE=InnoDB AUTO_INCREMENT=5 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `Zawody`
--

LOCK TABLES `Zawody` WRITE;
/*!40000 ALTER TABLE `Zawody` DISABLE KEYS */;
INSERT INTO `Zawody` VALUES
(1,'polityk',3000,25000),
(2,'nauczyciel',2500,4000),
(3,'informatyk',7000,30000),
(4,'lekarz',5000,12000);
/*!40000 ALTER TABLE `Zawody` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2022-12-14 15:50:32
