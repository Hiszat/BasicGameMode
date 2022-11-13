-- phpMyAdmin SQL Dump
-- version 5.0.1
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Nov 13, 2022 at 05:46 PM
-- Server version: 10.4.11-MariaDB
-- PHP Version: 7.4.2

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `dewata-new`
--

-- --------------------------------------------------------

--
-- Table structure for table `businesses`
--

CREATE TABLE `businesses` (
  `bizID` int(12) NOT NULL,
  `bizName` varchar(32) DEFAULT NULL,
  `bizOwner` int(12) DEFAULT 0,
  `bizType` int(12) DEFAULT 0,
  `bizPrice` int(12) DEFAULT 0,
  `bizPosX` float DEFAULT 0,
  `bizPosY` float DEFAULT 0,
  `bizPosZ` float DEFAULT 0,
  `bizPosA` float DEFAULT 0,
  `bizIntX` float DEFAULT 0,
  `bizIntY` float DEFAULT 0,
  `bizIntZ` float DEFAULT 0,
  `bizIntA` float DEFAULT 0,
  `bizInterior` int(12) DEFAULT 0,
  `bizExterior` int(12) DEFAULT 0,
  `bizExteriorVW` int(12) DEFAULT 0,
  `bizLocked` int(4) DEFAULT 0,
  `bizVault` int(12) DEFAULT 0,
  `bizProducts` int(12) DEFAULT 0,
  `bizPrice1` int(12) DEFAULT 0,
  `bizPrice2` int(12) DEFAULT 0,
  `bizPrice3` int(12) DEFAULT 0,
  `bizPrice4` int(12) DEFAULT 0,
  `bizPrice5` int(12) DEFAULT 0,
  `bizPrice6` int(12) DEFAULT 0,
  `bizPrice7` int(12) DEFAULT 0,
  `bizPrice8` int(12) DEFAULT 0,
  `bizPrice9` int(12) DEFAULT 0,
  `bizPrice10` int(12) DEFAULT 0,
  `bizSpawnX` float DEFAULT 0,
  `bizSpawnY` float DEFAULT 0,
  `bizSpawnZ` float DEFAULT 0,
  `bizSpawnA` float DEFAULT 0,
  `bizDeliverX` float DEFAULT 0,
  `bizDeliverY` float DEFAULT 0,
  `bizDeliverZ` float DEFAULT 0,
  `bizMessage` varchar(128) DEFAULT NULL,
  `bizPrice11` int(12) DEFAULT 0,
  `bizPrice12` int(12) DEFAULT 0,
  `bizPrice13` int(12) DEFAULT 0,
  `bizPrice14` int(12) DEFAULT 0,
  `bizPrice15` int(12) DEFAULT 0,
  `bizPrice16` int(12) DEFAULT 0,
  `bizPrice17` int(12) DEFAULT 0,
  `bizPrice18` int(12) DEFAULT 0,
  `bizPrice19` int(12) DEFAULT 0,
  `bizPrice20` int(12) DEFAULT 0,
  `bizShipment` int(4) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `businesses`
--

INSERT INTO `businesses` (`bizID`, `bizName`, `bizOwner`, `bizType`, `bizPrice`, `bizPosX`, `bizPosY`, `bizPosZ`, `bizPosA`, `bizIntX`, `bizIntY`, `bizIntZ`, `bizIntA`, `bizInterior`, `bizExterior`, `bizExteriorVW`, `bizLocked`, `bizVault`, `bizProducts`, `bizPrice1`, `bizPrice2`, `bizPrice3`, `bizPrice4`, `bizPrice5`, `bizPrice6`, `bizPrice7`, `bizPrice8`, `bizPrice9`, `bizPrice10`, `bizSpawnX`, `bizSpawnY`, `bizSpawnZ`, `bizSpawnA`, `bizDeliverX`, `bizDeliverY`, `bizDeliverZ`, `bizMessage`, `bizPrice11`, `bizPrice12`, `bizPrice13`, `bizPrice14`, `bizPrice15`, `bizPrice16`, `bizPrice17`, `bizPrice18`, `bizPrice19`, `bizPrice20`, `bizShipment`) VALUES
(1, 'TOKO BABOO', 1, 6, 100, 1833, -1842.6, 13.5781, 254.406, -27.3383, -57.6907, 1003.55, 0, 6, 0, 0, 1, 12, 95, 75, 125, 15, 100, 3, 2, 10, 100, 20, 10, 1833, -1842.6, 13.5781, 254.406, 0, 0, 0, '', 150, 200, 160, 60, 50, 5, 10, 5, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `criminallog`
--

CREATE TABLE `criminallog` (
  `ID` int(3) NOT NULL,
  `Suspect` varchar(24) DEFAULT NULL,
  `Username` varchar(24) DEFAULT NULL,
  `Date` varchar(36) DEFAULT NULL,
  `Description` varchar(128) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `criminallog`
--

INSERT INTO `criminallog` (`ID`, `Suspect`, `Username`, `Date`, `Description`) VALUES
(1, 'Alex_Mike', 'Alex_Mike', '13/11/2022, 23:24', '[10-10] Merampok Toko');

-- --------------------------------------------------------

--
-- Table structure for table `dropped`
--

CREATE TABLE `dropped` (
  `ID` int(12) NOT NULL,
  `itemName` varchar(32) DEFAULT NULL,
  `itemModel` int(12) DEFAULT 0,
  `itemX` float DEFAULT 0,
  `itemY` float DEFAULT 0,
  `itemZ` float DEFAULT 0,
  `itemInt` int(12) DEFAULT 0,
  `itemWorld` int(12) DEFAULT 0,
  `itemQuantity` int(12) DEFAULT 0,
  `itemAmmo` int(12) DEFAULT 0,
  `itemWeapon` int(12) DEFAULT 0,
  `itemPlayer` varchar(24) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `dropped`
--

INSERT INTO `dropped` (`ID`, `itemName`, `itemModel`, `itemX`, `itemY`, `itemZ`, `itemInt`, `itemWorld`, `itemQuantity`, `itemAmmo`, `itemWeapon`, `itemPlayer`) VALUES
(5, 'Water', 2958, 0, 0, -999.405, 0, 0, 1, 0, 0, 'Emmilia Charlotte'),
(6, 'Water', 2958, 0, 0, -999.405, 0, 0, 1, 0, 0, 'Emmilia Charlotte'),
(7, 'Water', 2958, -1431.46, 99.9883, 13.2465, 0, 0, 1, 0, 0, 'Emmilia Charlotte'),
(75, 'Coffe', 19835, 697.91, -507.04, 19.4362, 0, 0, 1, 0, 0, 'SilverZer0'),
(76, 'Fried Chicken', 2663, 697.91, -507.04, 19.4362, 0, 0, 1, 0, 0, 'SilverZer0'),
(79, 'Fish Rod', 18632, 885.425, -1196.09, 16.0765, 0, 0, 1, 0, 0, 'Clay Arthur'),
(129, 'Axe', 19631, 1962.03, -1709.54, 15.0687, 0, 0, 1, 0, 0, 'Alex_Mike');

-- --------------------------------------------------------

--
-- Table structure for table `entrances`
--

CREATE TABLE `entrances` (
  `entranceID` int(12) NOT NULL,
  `entranceName` varchar(32) DEFAULT NULL,
  `entranceIcon` int(12) DEFAULT 0,
  `entrancePosX` float DEFAULT 0,
  `entrancePosY` float DEFAULT 0,
  `entrancePosZ` float DEFAULT 0,
  `entrancePosA` float DEFAULT 0,
  `entranceIntX` float DEFAULT 0,
  `entranceIntY` float DEFAULT 0,
  `entranceIntZ` float DEFAULT 0,
  `entranceIntA` float DEFAULT 0,
  `entranceInterior` int(12) DEFAULT 0,
  `entranceExterior` int(12) DEFAULT 0,
  `entranceExteriorVW` int(12) DEFAULT 0,
  `entranceType` int(12) DEFAULT 0,
  `entrancePass` varchar(32) DEFAULT NULL,
  `entranceLocked` int(12) DEFAULT 0,
  `entranceCustom` int(4) DEFAULT 0,
  `entranceWorld` int(12) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `entrances`
--

INSERT INTO `entrances` (`entranceID`, `entranceName`, `entranceIcon`, `entrancePosX`, `entrancePosY`, `entrancePosZ`, `entrancePosA`, `entranceIntX`, `entranceIntY`, `entranceIntZ`, `entranceIntA`, `entranceInterior`, `entranceExterior`, `entranceExteriorVW`, `entranceType`, `entrancePass`, `entranceLocked`, `entranceCustom`, `entranceWorld`) VALUES
(7, 'San Fierro Roleplay', 45, -1605.49, 711.306, 13.867, 182.47, 1587.61, -1709.62, -36.8138, 182.455, 1, 0, 0, 0, '', 0, 0, 0),
(8, 'Department of Motor Vehicles', 0, -2026.62, -101.736, 35.164, 172.514, -2029.55, -118.8, 1035.17, 0, 3, 0, 0, 1, 'San Fierro Roleplay', 0, 0, 7008),
(10, 'Downtown Bank', 0, -2055.41, 455.282, 35.1718, 141.754, 1456.19, -987.942, 996.105, 90, 6, 0, 0, 2, 'Department of Motor Vehicles', 0, 0, 7010),
(12, 'San Fierro Cityhall', 0, -1493.9, 919.842, 7.1875, 271.94, 390.169, 173.807, 1008.38, 90, 3, 0, 0, 4, 'San Fierro Cityhall', 0, 0, 7012),
(14, 'Downtown Apartment Complex', 0, -1754.19, 962.555, 24.8828, 3.8796, 2214.8, -1150.34, 1025.8, 276.821, 15, 0, 0, 0, 'San Fierro Cityhall', 0, 0, 7014),
(54, 'Master Bedroom', 0, 134.639, 1379.96, 1088.37, 93.0609, 134.639, 1379.96, 11088.4, 0, 0, 5, 5006, 0, '', 0, 0, 7054),
(55, 'Los Santos Stadium', 0, 2695.35, -1704.55, 11.8437, 227.137, -1464.28, 1557.01, 1052.53, 342.974, 14, 0, 0, 0, '', 0, 0, 7055);

-- --------------------------------------------------------

--
-- Table structure for table `inventory`
--

CREATE TABLE `inventory` (
  `ID` int(12) DEFAULT 0,
  `invID` int(12) NOT NULL,
  `invItem` varchar(32) DEFAULT NULL,
  `invModel` int(12) DEFAULT 0,
  `invQuantity` int(12) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `inventory`
--

INSERT INTO `inventory` (`ID`, `invID`, `invItem`, `invModel`, `invQuantity`) VALUES
(1, 2, 'Cellphone', 18867, 1),
(1, 5, 'Snack', 19811, 4),
(1, 8, 'GPS System', 18875, 1),
(1, 9, 'Soda', 1543, 5),
(1, 10, 'Frozen Burger', 2768, 1),
(2, 11, 'Pizza', 1582, 20),
(2, 14, 'GPS', 18875, 1);

-- --------------------------------------------------------

--
-- Table structure for table `parks`
--

CREATE TABLE `parks` (
  `id` int(11) DEFAULT 0,
  `posx` float DEFAULT 0,
  `posy` float DEFAULT 0,
  `posz` float DEFAULT 0,
  `interior` int(11) DEFAULT 0,
  `world` int(11) DEFAULT 0,
  `spawnx` float NOT NULL,
  `spawny` float NOT NULL,
  `spawnz` float NOT NULL,
  `spawna` float NOT NULL,
  `posa` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

--
-- Dumping data for table `parks`
--

INSERT INTO `parks` (`id`, `posx`, `posy`, `posz`, `interior`, `world`, `spawnx`, `spawny`, `spawnz`, `spawna`, `posa`) VALUES
(0, 2115.4, -1776.52, 13.3912, 0, 0, 2115.4, -1770.89, 13.3939, 1.68621, 0),
(1, 1320.01, -863.615, 39.5781, 0, 0, 0, 0, 0, 0, 0),
(2, 1090.48, -1237.86, 15.8203, 0, 0, 0, 0, 0, 0, 0),
(4, 1365.84, -1648.96, 13.3828, 0, 0, 0, 0, 0, 0, 0),
(3, 1019.95, -1438.36, 13.5546, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Table structure for table `pumps`
--

CREATE TABLE `pumps` (
  `ID` int(12) DEFAULT 0,
  `pumpID` int(12) NOT NULL,
  `pumpPosX` float DEFAULT 0,
  `pumpPosY` float DEFAULT 0,
  `pumpPosZ` float DEFAULT 0,
  `pumpPosA` float DEFAULT 0,
  `pumpFuel` int(12) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `pumps`
--

INSERT INTO `pumps` (`ID`, `pumpID`, `pumpPosX`, `pumpPosY`, `pumpPosZ`, `pumpPosA`, `pumpFuel`) VALUES
(67, 15, 655.642, -570.239, 16.4113, 91.5188, 1454),
(67, 16, 655.598, -559.56, 16.4514, 88.9889, 2000),
(16, 17, 1941.36, -1767.12, 14.1428, 273.761, 181133),
(16, 18, 1941.83, -1771.51, 14.1625, -90.7393, 181131),
(16, 20, 1941.89, -1774.31, 14.1511, -91.0074, 179042),
(16, 21, 1941.82, -1777.77, 14.1302, -91.1277, 179743),
(1, 22, 1831.53, -1838.35, 14.0681, 334.789, 2000);

-- --------------------------------------------------------

--
-- Table structure for table `rental`
--

CREATE TABLE `rental` (
  `ID` int(12) NOT NULL,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `SpawnX` float NOT NULL DEFAULT 0,
  `SpawnY` float NOT NULL DEFAULT 0,
  `SpawnZ` float NOT NULL DEFAULT 0,
  `SpawnA` float NOT NULL DEFAULT 0,
  `Vehicle1` int(6) NOT NULL DEFAULT 0,
  `Vehicle2` int(6) NOT NULL DEFAULT 0,
  `Price1` int(6) NOT NULL DEFAULT 0,
  `Price2` int(6) NOT NULL DEFAULT 0,
  `PosA` float NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `rental`
--

INSERT INTO `rental` (`ID`, `PosX`, `PosY`, `PosZ`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnA`, `Vehicle1`, `Vehicle2`, `Price1`, `Price2`, `PosA`) VALUES
(2, 2287.29, -2369.11, 13.3919, 1672.87, -2251.51, 12.8939, 89.9767, 562, 562, 562, 562, 145.686),
(3, 1672.77, -2246.95, 13.5653, 1673.23, -2251.51, 12.8957, 94.6126, 462, 586, 462, 586, 185.659),
(4, 2122.07, -1771.73, 13.3935, 0, 0, 0, 0, 562, 560, 562, 560, 89.219);

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `pID` int(12) NOT NULL,
  `Username` varchar(64) NOT NULL,
  `Password` varchar(200) DEFAULT NULL,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `Health` float NOT NULL DEFAULT 100,
  `Interior` int(8) NOT NULL DEFAULT 0,
  `World` int(8) NOT NULL DEFAULT 0,
  `Age` varchar(50) NOT NULL DEFAULT '0',
  `Gender` int(3) NOT NULL DEFAULT 0,
  `Injured` int(3) NOT NULL DEFAULT 0,
  `Faction` int(2) DEFAULT NULL,
  `FactionRank` int(2) DEFAULT NULL,
  `Skin` int(4) NOT NULL DEFAULT 0,
  `Heigth` int(11) DEFAULT NULL,
  `Admin` int(11) DEFAULT NULL,
  `Armor` float DEFAULT NULL,
  `Level` int(11) DEFAULT NULL,
  `Money` int(11) DEFAULT NULL,
  `Bank` int(11) DEFAULT NULL,
  `Hunger` int(11) DEFAULT NULL,
  `Thirst` int(11) DEFAULT NULL,
  `Entrance` int(11) DEFAULT NULL,
  `Business` int(11) DEFAULT NULL,
  `WantedLevel` int(3) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`pID`, `Username`, `Password`, `PosX`, `PosY`, `PosZ`, `Health`, `Interior`, `World`, `Age`, `Gender`, `Injured`, `Faction`, `FactionRank`, `Skin`, `Heigth`, `Admin`, `Armor`, `Level`, `Money`, `Bank`, `Hunger`, `Thirst`, `Entrance`, `Business`, `WantedLevel`) VALUES
(1, 'Ananta_Wiguna', '$2y$12$lc0bJbX3GjYBhHasblW9M.WzY6LpsG.5lWgDWRm6P8r8xqEoRo10W', 1830.66, -1842.05, 13.5781, 100, 0, 0, '17/06/2004', 1, 0, NULL, NULL, 115, 0, 8, 0, 1, 22815, 50000, 100, 70, -1, -1, NULL),
(2, 'Alex_Mike', '$2y$12$x6Qv8dBQ3mN8Chy8q/4R.uuXG4bSMMYvfVtepzdfq5g7ByjzO9Dj.', 2324.4, 16.7464, 34.4834, 100, 0, 0, '01/01/2000', 1, 0, 1, 0, 29, 0, 8, 0, 1, 18876, 50000, 100, 100, -1, -1, 14);

-- --------------------------------------------------------

--
-- Table structure for table `vehicle`
--

CREATE TABLE `vehicle` (
  `vehID` int(12) NOT NULL,
  `vehModel` int(6) NOT NULL DEFAULT 0,
  `vehOwner` int(12) NOT NULL DEFAULT 0,
  `vehX` float NOT NULL DEFAULT 0,
  `vehY` float NOT NULL DEFAULT 0,
  `vehZ` float NOT NULL DEFAULT 0,
  `vehA` float NOT NULL DEFAULT 0,
  `vehColor1` int(6) NOT NULL DEFAULT 0,
  `vehColor2` int(6) NOT NULL DEFAULT 0,
  `vehWorld` int(8) NOT NULL DEFAULT 0,
  `vehInterior` int(8) NOT NULL DEFAULT 0,
  `vehFuel` int(8) NOT NULL DEFAULT 0,
  `vehDamage1` int(8) NOT NULL DEFAULT 0,
  `vehDamage2` int(8) NOT NULL DEFAULT 0,
  `vehDamage3` int(8) NOT NULL DEFAULT 0,
  `vehDamage4` int(8) NOT NULL DEFAULT 0,
  `vehHealth` int(11) NOT NULL DEFAULT 1000,
  `vehInsurance` int(8) NOT NULL DEFAULT 0,
  `vehInsuTime` int(12) NOT NULL DEFAULT 0,
  `vehLocked` int(3) NOT NULL DEFAULT 0,
  `vehPlate` varchar(16) NOT NULL DEFAULT 'NONE',
  `vehRental` int(4) NOT NULL DEFAULT -1,
  `vehRentalTime` int(8) NOT NULL DEFAULT 0,
  `vehInsuranced` int(3) NOT NULL DEFAULT 0,
  `vehHouse` int(6) NOT NULL DEFAULT -1,
  `vehWood` int(6) NOT NULL DEFAULT 0,
  `toyid0` int(4) NOT NULL DEFAULT 0,
  `toyid1` int(4) NOT NULL DEFAULT 0,
  `toyid2` int(4) NOT NULL DEFAULT 0,
  `toyid3` int(4) NOT NULL DEFAULT 0,
  `toyid4` int(4) NOT NULL DEFAULT 0,
  `toyposx0` float NOT NULL DEFAULT 0,
  `toyposx1` float NOT NULL DEFAULT 0,
  `toyposx2` float NOT NULL DEFAULT 0,
  `toyposx3` float NOT NULL DEFAULT 0,
  `toyposx4` float NOT NULL DEFAULT 0,
  `toyposy0` float NOT NULL DEFAULT 0,
  `toyposy1` float NOT NULL DEFAULT 0,
  `toyposy2` float NOT NULL DEFAULT 0,
  `toyposy3` float NOT NULL DEFAULT 0,
  `toyposy4` float NOT NULL DEFAULT 0,
  `toyposz0` float NOT NULL DEFAULT 0,
  `toyposz1` float NOT NULL DEFAULT 0,
  `toyposz2` float NOT NULL DEFAULT 0,
  `toyposz3` float NOT NULL DEFAULT 0,
  `toyposz4` float NOT NULL DEFAULT 0,
  `toyrotx0` float NOT NULL DEFAULT 0,
  `toyrotx1` float NOT NULL DEFAULT 0,
  `toyrotx2` float NOT NULL DEFAULT 0,
  `toyrotx3` float NOT NULL DEFAULT 0,
  `toyrotx4` float NOT NULL DEFAULT 0,
  `toyroty0` float NOT NULL DEFAULT 0,
  `toyroty1` float NOT NULL DEFAULT 0,
  `toyroty2` float NOT NULL DEFAULT 0,
  `toyroty3` float NOT NULL DEFAULT 0,
  `toyroty4` float NOT NULL DEFAULT 0,
  `toyrotz0` float NOT NULL DEFAULT 0,
  `toyrotz1` float NOT NULL DEFAULT 0,
  `toyrotz2` float NOT NULL DEFAULT 0,
  `toyrotz3` float NOT NULL DEFAULT 0,
  `toyrotz4` float NOT NULL DEFAULT 0,
  `mod0` int(6) NOT NULL DEFAULT 0,
  `mod1` int(6) NOT NULL DEFAULT 0,
  `mod2` int(6) NOT NULL DEFAULT 0,
  `mod3` int(6) NOT NULL DEFAULT 0,
  `mod4` int(6) NOT NULL DEFAULT 0,
  `mod5` int(6) NOT NULL DEFAULT 0,
  `mod6` int(6) NOT NULL DEFAULT 0,
  `mod7` int(6) NOT NULL DEFAULT 0,
  `mod8` int(6) NOT NULL DEFAULT 0,
  `mod9` int(6) NOT NULL DEFAULT 0,
  `mod10` int(6) NOT NULL DEFAULT 0,
  `mod11` int(6) NOT NULL DEFAULT 0,
  `mod12` int(6) NOT NULL DEFAULT 0,
  `mod13` int(6) NOT NULL DEFAULT 0,
  `mod14` int(6) NOT NULL DEFAULT 0,
  `mod15` int(6) NOT NULL DEFAULT 0,
  `mod16` int(6) NOT NULL DEFAULT 0,
  `vehPaintjob` int(3) NOT NULL DEFAULT -1,
  `vehPark` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `vehicle`
--

INSERT INTO `vehicle` (`vehID`, `vehModel`, `vehOwner`, `vehX`, `vehY`, `vehZ`, `vehA`, `vehColor1`, `vehColor2`, `vehWorld`, `vehInterior`, `vehFuel`, `vehDamage1`, `vehDamage2`, `vehDamage3`, `vehDamage4`, `vehHealth`, `vehInsurance`, `vehInsuTime`, `vehLocked`, `vehPlate`, `vehRental`, `vehRentalTime`, `vehInsuranced`, `vehHouse`, `vehWood`, `toyid0`, `toyid1`, `toyid2`, `toyid3`, `toyid4`, `toyposx0`, `toyposx1`, `toyposx2`, `toyposx3`, `toyposx4`, `toyposy0`, `toyposy1`, `toyposy2`, `toyposy3`, `toyposy4`, `toyposz0`, `toyposz1`, `toyposz2`, `toyposz3`, `toyposz4`, `toyrotx0`, `toyrotx1`, `toyrotx2`, `toyrotx3`, `toyrotx4`, `toyroty0`, `toyroty1`, `toyroty2`, `toyroty3`, `toyroty4`, `toyrotz0`, `toyrotz1`, `toyrotz2`, `toyrotz3`, `toyrotz4`, `mod0`, `mod1`, `mod2`, `mod3`, `mod4`, `mod5`, `mod6`, `mod7`, `mod8`, `mod9`, `mod10`, `mod11`, `mod12`, `mod13`, `mod14`, `mod15`, `mod16`, `vehPaintjob`, `vehPark`) VALUES
(3, 586, 3, 1584.95, -2254.26, 13.0048, 91.2054, 106, 38, 0, 0, 100, 0, 0, 0, 0, 1000, 0, 0, 0, 'RENTAL', 1, 3582, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0),
(7, 562, 1, 2286.87, -2374.92, 17.1541, 118.189, 38, 116, 0, 0, 100, 0, 0, 0, 0, 1000, 1, 0, 0, 'NONE', -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1),
(8, 562, 1, 2116.44, -1776.4, 16.9503, 23.3843, 119, 62, 0, 0, 98, 0, 0, 0, 0, 1000, 2, 0, 0, 'NONE', -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1),
(10, 562, 1, 2286.87, -2374.92, 16.5022, 118.196, 68, 116, 0, 0, 100, 0, 0, 0, 0, 1000, 2, 0, 0, 'NONE', -1, 0, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1),
(12, 462, 6, 1589.55, -2200.19, 13.17, 140.242, 34, 115, 0, 0, 99, 0, 0, 0, 0, 1000, 0, 0, 0, 'RENTAL', 1, 3576, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0),
(13, 462, 8, 2112.95, -1777.97, 13.2653, 233.594, 2, 8, 0, 0, 97, 0, 0, 0, 0, 1000, 0, 0, 0, 'RENTAL', 1, 741, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0),
(14, 562, 8, 2088.77, -1832.93, 13.3038, 160.907, 95, 124, 0, 0, 86, 0, 0, 0, 0, 1000, 2, 1666699960, 0, 'NONE', -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0),
(15, 562, 1, 2115.42, -1773.95, 15.2504, 36.3007, 27, 84, 0, 0, 99, 0, 0, 0, 0, 1000, 2, 1666700346, 0, 'NONE', -1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0);

--
-- Indexes for dumped tables
--

--
-- Indexes for table `businesses`
--
ALTER TABLE `businesses`
  ADD PRIMARY KEY (`bizID`);

--
-- Indexes for table `criminallog`
--
ALTER TABLE `criminallog`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `dropped`
--
ALTER TABLE `dropped`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `entrances`
--
ALTER TABLE `entrances`
  ADD PRIMARY KEY (`entranceID`);

--
-- Indexes for table `inventory`
--
ALTER TABLE `inventory`
  ADD PRIMARY KEY (`invID`);

--
-- Indexes for table `pumps`
--
ALTER TABLE `pumps`
  ADD PRIMARY KEY (`pumpID`);

--
-- Indexes for table `rental`
--
ALTER TABLE `rental`
  ADD PRIMARY KEY (`ID`);

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`pID`);

--
-- Indexes for table `vehicle`
--
ALTER TABLE `vehicle`
  ADD PRIMARY KEY (`vehID`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `businesses`
--
ALTER TABLE `businesses`
  MODIFY `bizID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `criminallog`
--
ALTER TABLE `criminallog`
  MODIFY `ID` int(3) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT for table `dropped`
--
ALTER TABLE `dropped`
  MODIFY `ID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=130;

--
-- AUTO_INCREMENT for table `entrances`
--
ALTER TABLE `entrances`
  MODIFY `entranceID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=56;

--
-- AUTO_INCREMENT for table `inventory`
--
ALTER TABLE `inventory`
  MODIFY `invID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=16;

--
-- AUTO_INCREMENT for table `pumps`
--
ALTER TABLE `pumps`
  MODIFY `pumpID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=23;

--
-- AUTO_INCREMENT for table `rental`
--
ALTER TABLE `rental`
  MODIFY `ID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;

--
-- AUTO_INCREMENT for table `users`
--
ALTER TABLE `users`
  MODIFY `pID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

--
-- AUTO_INCREMENT for table `vehicle`
--
ALTER TABLE `vehicle`
  MODIFY `vehID` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=21;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
