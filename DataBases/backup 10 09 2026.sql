-- phpMyAdmin SQL Dump
-- version 5.2.1
-- https://www.phpmyadmin.net/
--
-- Servidor: 127.0.0.1
-- Tiempo de generación: 11-09-2026 a las 01:50:07
-- Versión del servidor: 10.4.32-MariaDB
-- Versión de PHP: 8.2.12

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Base de datos: `gtafive`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `actores`
--

CREATE TABLE `actores` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(24) NOT NULL DEFAULT 'ninguno',
  `Skin` int(11) NOT NULL DEFAULT -1,
  `PosX` float NOT NULL DEFAULT 0,
  `PosY` float NOT NULL DEFAULT 0,
  `PosZ` float NOT NULL DEFAULT 0,
  `PosR` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0,
  `Animacion` int(11) NOT NULL DEFAULT 0,
  `Tipo` int(11) NOT NULL DEFAULT 1
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `antecedentes`
--

CREATE TABLE `antecedentes` (
  `ID` int(11) NOT NULL,
  `Documento` int(11) NOT NULL DEFAULT 0,
  `Faccion` varchar(10) NOT NULL DEFAULT 'none',
  `Responsable` varchar(24) NOT NULL DEFAULT 'none',
  `Detalles` varchar(512) NOT NULL DEFAULT 'none',
  `Fecha` varchar(256) NOT NULL DEFAULT 'none'
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `bidones`
--

CREATE TABLE `bidones` (
  `ID` int(11) NOT NULL,
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cajas`
--

CREATE TABLE `cajas` (
  `ID` int(11) NOT NULL,
  `Activo` int(11) NOT NULL DEFAULT 0,
  `Obj1` int(11) NOT NULL DEFAULT 0,
  `ObjCant1` int(11) NOT NULL DEFAULT 0,
  `Obj2` int(11) NOT NULL DEFAULT 0,
  `ObjCant2` int(11) NOT NULL DEFAULT 0,
  `Obj3` int(11) NOT NULL DEFAULT 0,
  `ObjCant3` int(11) NOT NULL DEFAULT 0,
  `Obj4` int(11) NOT NULL DEFAULT 0,
  `ObjCant4` int(11) NOT NULL DEFAULT 0,
  `Obj5` int(11) NOT NULL DEFAULT 0,
  `ObjCant5` int(11) NOT NULL DEFAULT 0,
  `Obj6` int(11) NOT NULL DEFAULT 0,
  `ObjCant6` int(11) NOT NULL DEFAULT 0,
  `Obj7` int(11) NOT NULL DEFAULT 0,
  `ObjCant7` int(11) NOT NULL DEFAULT 0,
  `Obj8` int(11) NOT NULL DEFAULT 0,
  `ObjCant8` int(11) NOT NULL DEFAULT 0,
  `Obj9` int(11) NOT NULL DEFAULT 0,
  `ObjCant9` int(11) NOT NULL DEFAULT 0,
  `Obj10` int(11) NOT NULL DEFAULT 0,
  `ObjCant10` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cajeros`
--

CREATE TABLE `cajeros` (
  `ID` int(11) NOT NULL,
  `Modelo` int(11) NOT NULL DEFAULT 19324,
  `BolosUwU` int(11) NOT NULL DEFAULT 5000000,
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `cajeros`
--

INSERT INTO `cajeros` (`ID`, `Modelo`, `BolosUwU`, `PotX`, `PotY`, `PotZ`, `RotX`, `RotY`, `RotZ`, `Interior`, `VirtualWorld`) VALUES
(1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(2, 19324, 4999716, 1477.38, -1772.24, 18.4157, 0, 0, -178.8, 0, 0),
(3, 19324, 4764087, 1773.97, -1660.37, 14.0174, 0, 0, -50.3, 0, 0),
(4, 19324, 4995829, 1834.24, -1851.04, 12.9981, 0, 0, 0, 0, 0),
(5, 19324, 5100402, 2228.4, -1715.22, 13.1661, 0, 0, -91.3, 0, 0),
(6, 19324, 4895433, 1496.65, -1749.9, 15.0729, -0.5, -1, -178.7, 0, 0),
(7, 19324, 4916386, 2115.84, -1118.37, 24.8972, 0, 0, 163.6, 0, 0),
(8, 19324, 5124437, 2106.02, -1790.72, 13.1908, 0, 0, -179.5, 0, 0),
(9, 19324, 5015850, 1928.58, -1768.79, 13.1222, 0, 0, 89.2, 0, 0),
(10, 19324, 5071431, 1350.6, -1759.24, 13.094, 0, 0, 179.9, 0, 0),
(11, 19324, 5020574, 1176.57, -1342.11, 13.5621, 0, 0, -179.1, 0, 0),
(12, 19324, 4919525, 1279.24, -1127.23, 23.3881, 0, 0, 1.2, 0, 0),
(13, 19324, 5009699, 1316.79, -897.797, 39.1397, 0, 0, 0, 0, 0),
(14, 19324, 5000000, 2423.28, -1219.49, 25.0556, 0, 0, 0, 0, 0),
(15, 19324, 6179683, 2242.99, -1665.12, 15.089, 0, 0, 166.1, 0, 0),
(16, 19324, 4965585, 2747.13, -1448.19, 30.0638, 0, 0, -89.4, 0, 0),
(17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `casas`
--

CREATE TABLE `casas` (
  `ID` int(11) NOT NULL,
  `Propietario` varchar(24) NOT NULL DEFAULT 'none',
  `Tipo` int(11) NOT NULL DEFAULT 0,
  `Venta` int(11) NOT NULL DEFAULT 0,
  `Seguro` int(11) NOT NULL DEFAULT 1,
  `Exterior_X` float NOT NULL DEFAULT 0,
  `Exterior_Y` float NOT NULL DEFAULT 0,
  `Exterior_Z` float NOT NULL DEFAULT 0,
  `Exterior_R` float NOT NULL DEFAULT 0,
  `Exterior_Int` int(11) NOT NULL DEFAULT 0,
  `Exterior_VW` int(11) NOT NULL DEFAULT 0,
  `Interior_X` float NOT NULL DEFAULT 0,
  `Interior_Y` float NOT NULL DEFAULT 0,
  `Interior_Z` float NOT NULL DEFAULT 0,
  `Interior_R` float NOT NULL DEFAULT 0,
  `Interior_Int` int(11) NOT NULL DEFAULT 0,
  `Interior_VW` int(11) NOT NULL DEFAULT 0,
  `BolosUwU` int(11) NOT NULL DEFAULT 0,
  `Precio` int(11) NOT NULL DEFAULT 0,
  `Armario1` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant1` int(11) NOT NULL DEFAULT 0,
  `Armario2` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant2` int(11) NOT NULL DEFAULT 0,
  `Armario3` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant3` int(11) NOT NULL DEFAULT 0,
  `Armario4` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant4` int(11) NOT NULL DEFAULT 0,
  `Armario5` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant5` int(11) NOT NULL DEFAULT 0,
  `Armario6` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant6` int(11) NOT NULL DEFAULT 0,
  `Armario7` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant7` int(11) NOT NULL DEFAULT 0,
  `Armario8` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant8` int(11) NOT NULL DEFAULT 0,
  `Armario9` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant9` int(11) NOT NULL DEFAULT 0,
  `Armario10` int(11) NOT NULL DEFAULT 0,
  `ArmarioCant10` int(11) NOT NULL DEFAULT 0,
  `Premium` int(11) NOT NULL DEFAULT 0,
  `TiempoDisponible` int(11) NOT NULL DEFAULT -1,
  `Compartida1` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida2` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida3` varchar(24) NOT NULL DEFAULT 'none'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `contenedores`
--

CREATE TABLE `contenedores` (
  `ID` int(11) NOT NULL,
  `Modelo` int(11) NOT NULL DEFAULT 19324,
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `contenedores`
--

INSERT INTO `contenedores` (`ID`, `Modelo`, `PotX`, `PotY`, `PotZ`, `RotX`, `RotY`, `RotZ`, `Interior`, `VirtualWorld`) VALUES
(1, 3035, 1214.45, -1129.95, 23.7605, 0, 0, -87.5, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `cuentas`
--

CREATE TABLE `cuentas` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(24) NOT NULL DEFAULT 'none',
  `Clave` varchar(65) NOT NULL DEFAULT 'none',
  `Salt` varchar(11) NOT NULL DEFAULT 'none',
  `Email` varchar(256) NOT NULL DEFAULT '-',
  `IP` varchar(18) NOT NULL DEFAULT '127.0.0.1',
  `JotoOtaku` int(11) NOT NULL DEFAULT 0,
  `EncFac` int(11) NOT NULL DEFAULT 0,
  `EncMap` int(11) NOT NULL DEFAULT 0,
  `PreguntaSeguridad` varchar(256) NOT NULL DEFAULT 'ninguna',
  `RespuestaSeguridad` varchar(256) NOT NULL DEFAULT 'ninguna',
  `VIP` int(11) NOT NULL DEFAULT 0,
  `Expira` int(11) NOT NULL DEFAULT -1,
  `KawaiAwA` int(11) NOT NULL DEFAULT 0,
  `Multicuenta` int(11) NOT NULL DEFAULT 0,
  `OtakuN_N` int(11) NOT NULL DEFAULT 0,
  `TimeBanUwU` int(11) NOT NULL DEFAULT 0,
  `FueBan` varchar(24) NOT NULL DEFAULT '-',
  `ReasonBanUwU` varchar(256) NOT NULL DEFAULT '-',
  `MomentBan` varchar(256) NOT NULL DEFAULT '-',
  `Regalo` int(11) NOT NULL DEFAULT 0,
  `FechaRegistro` varchar(256) NOT NULL DEFAULT 'none',
  `UltimaConexion` varchar(256) NOT NULL DEFAULT 'none',
  `Ranuras` int(11) NOT NULL DEFAULT 3,
  `BloqueoMP` int(11) NOT NULL DEFAULT 0,
  `TogMP` int(11) NOT NULL DEFAULT 0,
  `VerMP` int(11) NOT NULL DEFAULT 0,
  `MaxCasas` int(11) NOT NULL DEFAULT 1,
  `MaxNegocios` int(11) NOT NULL DEFAULT 1,
  `MaxMuebles` int(11) NOT NULL DEFAULT 150,
  `TogPing` int(11) NOT NULL DEFAULT 0,
  `EstiloAnuncio` int(11) NOT NULL DEFAULT 0,
  `EstiloBolsillos` int(11) NOT NULL DEFAULT 0,
  `TogNames` int(11) NOT NULL DEFAULT 0,
  `EncStaff` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `cuentas`
--

INSERT INTO `cuentas` (`ID`, `Nombre`, `Clave`, `Salt`, `Email`, `IP`, `JotoOtaku`, `EncFac`, `EncMap`, `PreguntaSeguridad`, `RespuestaSeguridad`, `VIP`, `Expira`, `KawaiAwA`, `Multicuenta`, `OtakuN_N`, `TimeBanUwU`, `FueBan`, `ReasonBanUwU`, `MomentBan`, `Regalo`, `FechaRegistro`, `UltimaConexion`, `Ranuras`, `BloqueoMP`, `TogMP`, `VerMP`, `MaxCasas`, `MaxNegocios`, `MaxMuebles`, `TogPing`, `EstiloAnuncio`, `EstiloBolsillos`, `TogNames`, `EncStaff`) VALUES
(1, 'VanNet', '7A359F7FE9D3946F220245CA140DD72183D9FB39C17FBA15FC8849CBCA1FF5AB', 'Y9D8\\;WG[n', 'alessblackwood741@gmail.com', '206.0.228.66', 4, 1, 0, '?Cu?l es el apellido de soltera de mi madre?', 'Blackwood', 0, -1, 0, 0, 0, 0, '-', '-', '-', 0, '23:32:32 - 27/10/2025', '02:29:21 - 30/10/2025', 3, 0, 0, 0, 1, 1, 150, 0, 0, 0, 1, 0),
(4, 'jack22', '5759612A6E185B867E8EC3B8374038B333AB62BE19D423A02D94F7FCF2ABCBB9', '?MqX>gT33J', 'jack@gmail.com', '152.202.75.219', 0, 0, 0, 'Â¿CuÃ¡l es el nombre de mi mascota?', 'rocky', 0, -1, 0, 0, 0, 0, '-', '-', '-', 0, '02:24:02 - 30/10/2025', '02:31:12 - 30/10/2025', 3, 0, 0, 0, 1, 1, 150, 0, 0, 0, 0, 0),
(3, 'Altyn', '01BEB650C283836A67C5C25FC298ED65244A262ECDB44F0E0DEB95E058953F07', 'VQbIIvPP@Z', 'Altyn@gmail.com', '127.0.0.1', 4, 1, 0, 'Â¿CuÃ¡l es el apellido de soltera de mi madre?', 'peruanito 202', 0, -1, 500, 0, 0, 0, '-', '-', '-', 0, '18:57:22 - 29/10/2025', '16:31:24 - 07/09/2026', 3, 0, 0, 0, 1, 1, 150, 0, 0, 0, 0, 0),
(5, 'Zeli17', 'B25486F805FABFFEBA9F611BEDF33F904E38BB25BCD0AF6364324449933F3799', '?`FJj<DfhG', 'gcnaigsg@gmail.es', '174.176.204.54', 0, 0, 0, 'Â¿CuÃ¡l es el nombre de mi mascota?', 'Gio es', 0, -1, 0, 0, 0, 0, '-', '-', '-', 0, '03:52:22 - 30/10/2025', '03:58:36 - 30/10/2025', 3, 0, 0, 0, 1, 1, 150, 0, 0, 0, 0, 0),
(6, 'duis1', 'E478A764683C4178AC62B2B3343820AB9944F26D1C61D093F7BD933CB0D6BF57', 'dY^<la3o5H', 'duisq@gmail.com', '127.0.0.1', 0, 0, 0, 'Cual es el nombre de mi mascota?', 'Duiss', 0, -1, 0, 0, 0, 0, '-', '-', '-', 0, '00:53:14 - 07/09/2026', '00:54:45 - 07/09/2026', 3, 0, 0, 0, 1, 1, 150, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `facciones`
--

CREATE TABLE `facciones` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(128) NOT NULL DEFAULT 'none',
  `Logo` varchar(8) NOT NULL DEFAULT 'none',
  `Lider` varchar(24) NOT NULL DEFAULT 'none',
  `SubLider` varchar(24) NOT NULL DEFAULT 'none',
  `Mensaje` varchar(256) NOT NULL DEFAULT 'none',
  `Tipo` int(11) NOT NULL DEFAULT 0,
  `Miembros` int(11) NOT NULL DEFAULT 0,
  `BolosUwU` int(11) NOT NULL DEFAULT 0,
  `Salario` int(11) NOT NULL DEFAULT 0,
  `MaxRangos` int(11) NOT NULL DEFAULT 6,
  `Rango1` varchar(32) NOT NULL DEFAULT 'Rank1',
  `Rango2` varchar(32) NOT NULL DEFAULT 'Rank2',
  `Rango3` varchar(32) NOT NULL DEFAULT 'Rank3',
  `Rango4` varchar(32) NOT NULL DEFAULT 'Rank4',
  `Rango5` varchar(32) NOT NULL DEFAULT 'Rank5',
  `Rango6` varchar(32) NOT NULL DEFAULT 'Rank6',
  `Rango7` varchar(32) NOT NULL DEFAULT 'Rank7',
  `Rango8` varchar(32) NOT NULL DEFAULT 'Rank8',
  `Rango9` varchar(32) NOT NULL DEFAULT 'Rank9',
  `Rango10` varchar(32) NOT NULL DEFAULT 'Rank10',
  `Rango11` varchar(32) NOT NULL DEFAULT 'Rank11',
  `Rango12` varchar(32) NOT NULL DEFAULT 'Rank12',
  `Rango13` varchar(32) NOT NULL DEFAULT 'Rank13',
  `Rango14` varchar(32) NOT NULL DEFAULT 'Rank14',
  `Rango15` varchar(32) NOT NULL DEFAULT 'Rank15',
  `SpawnX` float NOT NULL DEFAULT 0,
  `SpawnY` float NOT NULL DEFAULT 0,
  `SpawnZ` float NOT NULL DEFAULT 0,
  `SpawnR` float NOT NULL DEFAULT 0,
  `SpawnInt` int(11) NOT NULL DEFAULT 0,
  `SpawnVW` int(11) NOT NULL DEFAULT 0,
  `ArmarioX` float NOT NULL DEFAULT 0,
  `ArmarioY` float NOT NULL DEFAULT 0,
  `ArmarioZ` float NOT NULL DEFAULT 0,
  `ArmarioInt` int(11) NOT NULL DEFAULT 0,
  `ArmarioVW` int(11) NOT NULL DEFAULT 0,
  `Materiales` int(11) NOT NULL DEFAULT 0,
  `Equipo1` int(11) NOT NULL DEFAULT 0,
  `Equipo2` int(11) NOT NULL DEFAULT 0,
  `Equipo3` int(11) NOT NULL DEFAULT 0,
  `Equipo4` int(11) NOT NULL DEFAULT 0,
  `Equipo5` int(11) NOT NULL DEFAULT 0,
  `Equipo6` int(11) NOT NULL DEFAULT 0,
  `Equipo7` int(11) NOT NULL DEFAULT 0,
  `Equipo8` int(11) NOT NULL DEFAULT 0,
  `Equipo9` int(11) NOT NULL DEFAULT 0,
  `Equipo10` int(11) NOT NULL DEFAULT 0,
  `Equipo11` int(11) NOT NULL DEFAULT 0,
  `Equipo12` int(11) NOT NULL DEFAULT 0,
  `Equipo13` int(11) NOT NULL DEFAULT 0,
  `Equipo14` int(11) NOT NULL DEFAULT 0,
  `Equipo15` int(11) NOT NULL DEFAULT 0,
  `Equipo16` int(11) NOT NULL DEFAULT 0,
  `Equipo17` int(11) NOT NULL DEFAULT 0,
  `Equipo18` int(11) NOT NULL DEFAULT 0,
  `Equipo19` int(11) NOT NULL DEFAULT 0,
  `Equipo20` int(11) NOT NULL DEFAULT 0,
  `Requiere1` int(11) NOT NULL DEFAULT 0,
  `Requiere2` int(11) NOT NULL DEFAULT 0,
  `Requiere3` int(11) NOT NULL DEFAULT 0,
  `Requiere4` int(11) NOT NULL DEFAULT 0,
  `Requiere5` int(11) NOT NULL DEFAULT 0,
  `Requiere6` int(11) NOT NULL DEFAULT 0,
  `Requiere7` int(11) NOT NULL DEFAULT 0,
  `Requiere8` int(11) NOT NULL DEFAULT 0,
  `Requiere9` int(11) NOT NULL DEFAULT 0,
  `Requiere10` int(11) NOT NULL DEFAULT 0,
  `Requiere11` int(11) NOT NULL DEFAULT 0,
  `Requiere12` int(11) NOT NULL DEFAULT 0,
  `Requiere13` int(11) NOT NULL DEFAULT 0,
  `Requiere14` int(11) NOT NULL DEFAULT 0,
  `Requiere15` int(11) NOT NULL DEFAULT 0,
  `Requiere16` int(11) NOT NULL DEFAULT 0,
  `Requiere17` int(11) NOT NULL DEFAULT 0,
  `Requiere18` int(11) NOT NULL DEFAULT 0,
  `Requiere19` int(11) NOT NULL DEFAULT 0,
  `Requiere20` int(11) NOT NULL DEFAULT 0,
  `Skin1` int(11) NOT NULL DEFAULT 0,
  `Skin2` int(11) NOT NULL DEFAULT 0,
  `Skin3` int(11) NOT NULL DEFAULT 0,
  `Skin4` int(11) NOT NULL DEFAULT 0,
  `Skin5` int(11) NOT NULL DEFAULT 0,
  `Skin6` int(11) NOT NULL DEFAULT 0,
  `Skin7` int(11) NOT NULL DEFAULT 0,
  `Skin8` int(11) NOT NULL DEFAULT 0,
  `Skin9` int(11) NOT NULL DEFAULT 0,
  `Skin10` int(11) NOT NULL DEFAULT 0,
  `Skin11` int(11) NOT NULL DEFAULT 0,
  `Skin12` int(11) NOT NULL DEFAULT 0,
  `Skin13` int(11) NOT NULL DEFAULT 0,
  `Skin14` int(11) NOT NULL DEFAULT 0,
  `Skin15` int(11) NOT NULL DEFAULT 0,
  `Skin16` int(11) NOT NULL DEFAULT 0,
  `Skin17` int(11) NOT NULL DEFAULT 0,
  `Skin18` int(11) NOT NULL DEFAULT 0,
  `Skin19` int(11) NOT NULL DEFAULT 0,
  `Skin20` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `facciones`
--

INSERT INTO `facciones` (`ID`, `Nombre`, `Logo`, `Lider`, `SubLider`, `Mensaje`, `Tipo`, `Miembros`, `BolosUwU`, `Salario`, `MaxRangos`, `Rango1`, `Rango2`, `Rango3`, `Rango4`, `Rango5`, `Rango6`, `Rango7`, `Rango8`, `Rango9`, `Rango10`, `Rango11`, `Rango12`, `Rango13`, `Rango14`, `Rango15`, `SpawnX`, `SpawnY`, `SpawnZ`, `SpawnR`, `SpawnInt`, `SpawnVW`, `ArmarioX`, `ArmarioY`, `ArmarioZ`, `ArmarioInt`, `ArmarioVW`, `Materiales`, `Equipo1`, `Equipo2`, `Equipo3`, `Equipo4`, `Equipo5`, `Equipo6`, `Equipo7`, `Equipo8`, `Equipo9`, `Equipo10`, `Equipo11`, `Equipo12`, `Equipo13`, `Equipo14`, `Equipo15`, `Equipo16`, `Equipo17`, `Equipo18`, `Equipo19`, `Equipo20`, `Requiere1`, `Requiere2`, `Requiere3`, `Requiere4`, `Requiere5`, `Requiere6`, `Requiere7`, `Requiere8`, `Requiere9`, `Requiere10`, `Requiere11`, `Requiere12`, `Requiere13`, `Requiere14`, `Requiere15`, `Requiere16`, `Requiere17`, `Requiere18`, `Requiere19`, `Requiere20`, `Skin1`, `Skin2`, `Skin3`, `Skin4`, `Skin5`, `Skin6`, `Skin7`, `Skin8`, `Skin9`, `Skin10`, `Skin11`, `Skin12`, `Skin13`, `Skin14`, `Skin15`, `Skin16`, `Skin17`, `Skin18`, `Skin19`, `Skin20`) VALUES
(1, 'Los Santos Police Department', 'LSPD', '#QENJ', 'disponible', 'none', 1, 0, 0, 350, 10, 'Police Officer', 'Police Officer II', 'Police Officer III', 'Senior Lead Officer', 'Detective I', 'Detective II', 'Sergeant I', 'Detective III', 'Sergeant II', 'Captain III', 'Sin uso.', 'Sin uso.', 'Sin uso.', 'Sergeant II', 'Jefe de policía', 0, 0, 0, 0, 0, 0, 1578.49, -1682.1, 2110.54, 41, 16, 100, 900, 950, 3, 40, 21, 22, 54, 28, 26, 17, 37, 53, 36, 38, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 3, 1, 8, 6, 2, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 265, 266, 267, 280, 281, 306, 284, 285, 300, 301, 302, 307, 71, 0, 0, 0, 0, 0, 0, 0),
(2, 'Federal Bureau of Investigation', 'FBI', 'disponible', 'disponible', 'none', 2, 0, 0, 350, 15, 'New Agent Trainee', 'Field Agent', 'Federal Agent', 'Forensic Operation Specialist', 'Assistant Agent In Charge', 'Forensic Canine Consultants', 'Special Agent in Charge', 'S.A Attorney General', 'Program Analyst', 'Supervisory Special Agent', 'Agent In Charge', 'Special Agent In Charge', 'Unit S.A Attorney General', 'Unit Chief', 'Section Chief', 1609.7, 1568.9, 10.8359, 116.514, 38, 29, 1606.87, 1580.7, 10.8359, 38, 29, 100, 53, 950, 3, 21, 22, 28, 31, 38, 40, 26, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 2, 2, 6, 11, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 295, 286, 285, 166, 165, 164, 163, 70, 303, 304, 305, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(3, 'United States Marine Corps', 'USMC', 'disponible', 'disponible', 'none', 3, 0, 10000, 800, 15, 'Private(PV.)', 'Corporal(Cpl.)', 'Chief Warrant Officer I', 'Chief Warrant Officer II', 'Chief Warrant Officer III', 'Second Lieutenant', 'First Lieutenant', 'Capitan', 'Mayor', 'Coronel', 'Brigadier General', 'Major General', 'Lieutenant General', 'General', 'General Of The Army', 0, 0, 0, 0, 0, 0, 3130.8, -2166.36, 4164.22, 56, 32, 0, 900, 950, 21, 26, 28, 17, 40, 30, 31, 22, 27, 4, 39, 0, 0, 0, 0, 0, 0, 0, 1, 2, 7, 11, 5, 11, 6, 11, 12, 11, 11, 11, 5, 0, 0, 0, 0, 0, 0, 0, 61, 179, 191, 0, 285, 287, 310, 150, 27, 283, 80, 81, 311, 0, 309, 0, 0, 0, 0, 0),
(4, 'Los Santos County Sheriff\'s Department', 'LSCSD', 'Jayce_Dunham', 'Luis_Martinez', 'none', 4, 0, 0, 350, 9, 'Deputy Sheriff', 'Deputy Sheriff I', 'Deputy Sheriff II', 'Deputy Sheriff III', 'Deputy Sheriff Bonus I', 'Deputy Sheriff Bonus II', 'Sergeant', 'Lieutenant', 'Captain', 'Assistant Sheriff', 'Under Sheriff', 'Sheriff', 'Assistant Sheriff', 'Under Sheriff', 'Sheriff', 1608.47, 1568.17, 10.8359, 295.851, 40, 10, 1607.75, 1580.02, 10.8359, 38, 50, 100, 900, 950, 19, 21, 40, 22, 54, 26, 28, 31, 3, 36, 53, 66, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 2, 5, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 282, 283, 288, 309, 310, 311, 285, 284, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(5, 'Los Santos County Hall of Justice', 'LSHJ', 'disponible', 'disponible', 'none', 5, 0, 0, 350, 6, 'Marshall', 'Secretario', 'Abogado', 'Fiscal', 'Juez', 'Gobernador', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 2558.49, -1431.23, 24.0086, 85.2789, 0, 0, 1293.71, -921.242, 5001.08, 69, 4, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(6, 'Los Santos Fire Department', 'LSFD', 'disponible', 'disponible', 'none', 6, 0, 0, 650, 11, 'Probational Firefighter', 'Firefighter', 'Paramedic', 'Engineer', 'Lieutenant', 'Deputy Batallion Chief', 'Batallion Chief', 'Mayor', 'Deputy Captain', 'Captain', 'Chief ', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 1173.92, -1356.95, 3015.41, 61, 20, 0, 900, 37, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 274, 275, 276, 277, 278, 279, 61, 150, 308, 311, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(7, 'San Andreas Department of Corrections', 'SADOC', 'disponible', 'disponible', 'none', 7, 0, 0, 350, 9, 'Cadet', 'Correctional Officer I', 'Correctional Officer II', 'Seargent', 'Lieutenant', 'Captain', 'Deputy Chief Warden', 'Guardian', 'Associate Director', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 321.749, 303.435, 999.148, 5, 10, 0, 900, 950, 40, 54, 3, 36, 53, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 7, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 282, 283, 288, 309, 310, 311, 191, 179, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(13, 'none', 'none', 'disponible', 'disponible', 'none', 0, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(12, 'none', 'none', 'disponible', 'disponible', 'none', 0, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(9, '/editarfnombre', 'none', 'disponible', 'disponible', 'none', 13, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(10, '/editarfnombre', 'none', 'disponible', 'disponible', 'none', 9, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(11, 'none', 'none', 'disponible', 'disponible', 'none', 0, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(14, 'none', 'none', 'disponible', 'disponible', 'none', 0, 0, 0, 0, 6, 'Rank1', 'Rank2', 'Rank3', 'Rank4', 'Rank5', 'Rank6', 'Rank7', 'Rank8', 'Rank9', 'Rank10', 'Rank11', 'Rank12', 'Rank13', 'Rank14', 'Rank15', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `graffitis`
--

CREATE TABLE `graffitis` (
  `ID` int(11) NOT NULL,
  `Mensaje` varchar(256) NOT NULL DEFAULT 'ninguno',
  `Creador` varchar(24) NOT NULL DEFAULT 'ninguno',
  `Fecha` int(11) NOT NULL DEFAULT 0,
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `incendios`
--

CREATE TABLE `incendios` (
  `ID` int(11) NOT NULL,
  `Tipo` int(11) NOT NULL DEFAULT -1,
  `Propiedad` int(11) NOT NULL DEFAULT -1
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `ips`
--

CREATE TABLE `ips` (
  `ID` int(11) NOT NULL,
  `IP` varchar(18) NOT NULL DEFAULT 'none',
  `Admin` varchar(24) NOT NULL DEFAULT 'none',
  `Fecha` varchar(256) NOT NULL DEFAULT 'none',
  `Razon` varchar(256) NOT NULL DEFAULT 'none'
) ENGINE=InnoDB DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `laboratorios`
--

CREATE TABLE `laboratorios` (
  `ID` int(11) NOT NULL,
  `Activo` int(11) NOT NULL DEFAULT 0,
  `Venta` int(11) DEFAULT 0,
  `EX` float DEFAULT 0,
  `EY` float NOT NULL DEFAULT 0,
  `EZ` float NOT NULL DEFAULT 0,
  `SX` float NOT NULL DEFAULT 0,
  `SY` float NOT NULL DEFAULT 0,
  `SZ` float NOT NULL DEFAULT 0,
  `ENX` float NOT NULL DEFAULT 0,
  `ENY` float NOT NULL DEFAULT 0,
  `ENZ` float NOT NULL DEFAULT 0,
  `Ventilacion` int(11) NOT NULL DEFAULT 0,
  `Extractor` int(11) NOT NULL DEFAULT 0,
  `Provedor` int(11) NOT NULL DEFAULT 0,
  `Equipo` int(11) NOT NULL DEFAULT 0,
  `Quimico` int(11) NOT NULL DEFAULT 0,
  `Triptina` int(11) NOT NULL DEFAULT 0,
  `Ergolina` int(11) NOT NULL DEFAULT 0,
  `Tropano` int(11) NOT NULL DEFAULT 0,
  `Efedrina` int(11) NOT NULL DEFAULT 0,
  `Butano` int(11) NOT NULL DEFAULT 0,
  `Propietario` int(11) NOT NULL DEFAULT 0,
  `Llave1l` int(11) NOT NULL DEFAULT -1,
  `Llave2l` int(11) NOT NULL DEFAULT -1,
  `Llave3l` int(11) NOT NULL DEFAULT -1,
  `Seguro` int(11) NOT NULL DEFAULT 0,
  `EnUso` int(11) NOT NULL DEFAULT 0,
  `EA` float NOT NULL DEFAULT 0,
  `SA` float NOT NULL DEFAULT 0,
  `TiempoCreacion1` int(11) NOT NULL DEFAULT 0,
  `TiempoCreacion2` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `mochilas`
--

CREATE TABLE `mochilas` (
  `ID` int(11) NOT NULL,
  `Activo` int(11) NOT NULL DEFAULT 0,
  `Obj1` int(11) NOT NULL DEFAULT 0,
  `ObjCant1` int(11) NOT NULL DEFAULT 0,
  `Obj2` int(11) NOT NULL DEFAULT 0,
  `ObjCant2` int(11) NOT NULL DEFAULT 0,
  `Obj3` int(11) NOT NULL DEFAULT 0,
  `ObjCant3` int(11) NOT NULL DEFAULT 0,
  `Obj4` int(11) NOT NULL DEFAULT 0,
  `ObjCant4` int(11) NOT NULL DEFAULT 0,
  `Obj5` int(11) NOT NULL DEFAULT 0,
  `ObjCant5` int(11) NOT NULL DEFAULT 0,
  `Obj6` int(11) NOT NULL DEFAULT 0,
  `ObjCant6` int(11) NOT NULL DEFAULT 0,
  `Obj7` int(11) NOT NULL DEFAULT 0,
  `ObjCant7` int(11) NOT NULL DEFAULT 0,
  `Obj8` int(11) NOT NULL DEFAULT 0,
  `ObjCant8` int(11) NOT NULL DEFAULT 0,
  `Obj9` int(11) NOT NULL DEFAULT 0,
  `ObjCant9` int(11) NOT NULL DEFAULT 0,
  `Obj10` int(11) NOT NULL DEFAULT 0,
  `ObjCant10` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `muebles`
--

CREATE TABLE `muebles` (
  `ID` int(11) NOT NULL,
  `Tipo` int(11) NOT NULL DEFAULT 0,
  `Propiedad` int(11) NOT NULL DEFAULT -1,
  `Modelo` int(11) NOT NULL DEFAULT 0,
  `Nombre` varchar(128) NOT NULL DEFAULT 'none',
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0,
  `Precio` int(11) NOT NULL DEFAULT 0,
  `Puerta` int(11) NOT NULL DEFAULT 0,
  `TxtMaterial1` int(11) NOT NULL DEFAULT -1,
  `TxtModelo1` int(11) NOT NULL DEFAULT 0,
  `TxtNombre1` varchar(128) NOT NULL DEFAULT 'none',
  `TxtNombreTextura1` varchar(128) NOT NULL DEFAULT 'none',
  `TxtColor1` int(11) NOT NULL DEFAULT 0,
  `TxtMaterial2` int(11) NOT NULL DEFAULT -1,
  `TxtModelo2` int(11) NOT NULL DEFAULT 0,
  `TxtNombre2` varchar(128) NOT NULL DEFAULT 'none',
  `TxtNombreTextura2` varchar(128) NOT NULL DEFAULT 'none',
  `TxtColor2` int(11) NOT NULL DEFAULT 0,
  `TxtMaterial3` int(11) NOT NULL DEFAULT -1,
  `TxtModelo3` int(11) NOT NULL DEFAULT 0,
  `TxtNombre3` varchar(128) NOT NULL DEFAULT 'none',
  `TxtNombreTextura3` varchar(128) NOT NULL DEFAULT 'none',
  `TxtColor3` int(11) NOT NULL DEFAULT 0,
  `TxtMaterial4` int(11) NOT NULL DEFAULT -1,
  `TxtModelo4` int(11) NOT NULL DEFAULT 0,
  `TxtNombre4` varchar(128) NOT NULL DEFAULT 'none',
  `TxtNombreTextura4` varchar(128) NOT NULL DEFAULT 'none',
  `TxtColor4` int(11) NOT NULL DEFAULT 0,
  `TxtMaterial5` int(11) NOT NULL DEFAULT -1,
  `TxtModelo5` int(11) NOT NULL DEFAULT 0,
  `TxtNombre5` varchar(128) NOT NULL DEFAULT 'none',
  `TxtNombreTextura5` varchar(128) NOT NULL DEFAULT 'none',
  `TxtColor5` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `negocios`
--

CREATE TABLE `negocios` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(32) NOT NULL DEFAULT 'none',
  `Propietario` varchar(24) NOT NULL DEFAULT 'gobielno',
  `Venta` int(11) NOT NULL DEFAULT 0,
  `Tipo` int(11) NOT NULL DEFAULT 0,
  `Precio` int(11) NOT NULL DEFAULT 0,
  `ExteriorX` float NOT NULL DEFAULT 0,
  `ExteriorY` float NOT NULL DEFAULT 0,
  `ExteriorZ` float NOT NULL DEFAULT 0,
  `ExteriorR` float NOT NULL DEFAULT 0,
  `ExteriorInt` int(11) NOT NULL DEFAULT 0,
  `ExteriorVW` int(11) NOT NULL DEFAULT 0,
  `InteriorX` float NOT NULL DEFAULT 0,
  `InteriorY` float NOT NULL DEFAULT 0,
  `InteriorZ` float NOT NULL DEFAULT 0,
  `InteriorR` float NOT NULL DEFAULT 0,
  `InteriorInt` int(11) NOT NULL DEFAULT 0,
  `InteriorVW` int(11) NOT NULL DEFAULT 0,
  `LugarCompraX` float NOT NULL DEFAULT 0,
  `LugarCompraY` float NOT NULL DEFAULT 0,
  `LugarCompraZ` float NOT NULL DEFAULT 0,
  `Seguro` int(11) NOT NULL DEFAULT 0,
  `BolosUwU` int(11) NOT NULL DEFAULT 0,
  `Productos` int(11) NOT NULL DEFAULT 0,
  `MapIcon` int(11) NOT NULL DEFAULT 0,
  `ActorX` float NOT NULL DEFAULT 0,
  `ActorY` float NOT NULL DEFAULT 0,
  `ActorZ` float NOT NULL DEFAULT 0,
  `ActorR` float NOT NULL DEFAULT 0,
  `ActorSkin` int(11) NOT NULL DEFAULT 0,
  `VehicleX` float NOT NULL DEFAULT 0,
  `VehicleY` float NOT NULL DEFAULT 0,
  `VehicleZ` float NOT NULL DEFAULT 0,
  `VehicleR` float NOT NULL DEFAULT 0,
  `Mecanico` varchar(512) NOT NULL DEFAULT '0|0|0|0|0|0|0|0|',
  `TiempoDisponible` int(11) NOT NULL DEFAULT -1,
  `Compartida1` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida2` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida3` varchar(24) NOT NULL DEFAULT 'none'
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `negocios`
--

INSERT INTO `negocios` (`ID`, `Nombre`, `Propietario`, `Venta`, `Tipo`, `Precio`, `ExteriorX`, `ExteriorY`, `ExteriorZ`, `ExteriorR`, `ExteriorInt`, `ExteriorVW`, `InteriorX`, `InteriorY`, `InteriorZ`, `InteriorR`, `InteriorInt`, `InteriorVW`, `LugarCompraX`, `LugarCompraY`, `LugarCompraZ`, `Seguro`, `BolosUwU`, `Productos`, `MapIcon`, `ActorX`, `ActorY`, `ActorZ`, `ActorR`, `ActorSkin`, `VehicleX`, `VehicleY`, `VehicleZ`, `VehicleR`, `Mecanico`, `TiempoDisponible`, `Compartida1`, `Compartida2`, `Compartida3`) VALUES
(1, '24-7', 'gobielno', 0, 1, 250000, -145.752, 1172.39, 19.7422, 179.204, 0, 0, -30.9624, -92.0089, 1003.55, 4.8661, 18, 101, -28.0597, -89.8704, 1003.55, 0, 200, 799, 0, -27.7799, -91.6342, 1003.55, 6.6012, 134, 0, 0, 0, 0, '0|0|0|0|0|0|0|0|', -1, 'none', 'none', 'none'),
(2, 'Concesionario', 'gobielno', 0, 10, 1500000, -19.1711, 1175.23, 19.5634, 172.326, 0, 0, 1494.49, 1303.58, 1093.29, 359.095, 3, 102, 1490.77, 1306.22, 1093.3, 0, 0, 800, 0, 1488.86, 1305.5, 1093.3, 282.809, 11, -28.9784, 1174.08, 19.352, 165.762, '0|0|0|0|0|0|0|0|', -1, 'none', 'none', 'none'),
(3, 'Restaurante', 'gobielno', 0, 3, 100000, -144.139, 1225.22, 19.8992, 357.116, 0, 0, 364.918, -11.7833, 1001.85, 3.0558, 9, 103, 370.922, -6.0173, 1001.86, 0, 0, 800, 0, 370.898, -4.4378, 1001.86, 178.982, 167, 0, 0, 0, 0, '0|0|0|0|0|0|0|0|', -1, 'none', 'none', 'none'),
(4, 'Concesionario', 'gobielno', 0, 10, 1, -187.635, 1210.71, 19.7056, 21.5876, 0, 0, 1827.39, 386.173, 2998.39, 88.379, 0, 104, 1817.06, 386.859, 2998.39, 0, 0, 800, 0, 1815.67, 386.451, 2998.39, 289.999, 3, -178.205, 1217.38, 19.7422, 269.294, '0|0|0|0|0|0|0|0|', -1, 'none', 'none', 'none'),
(5, 'Ropa', 'gobielno', 0, 2, 100000, -180.522, 1063.35, 19.7422, 278.855, 0, 0, 207.655, -111.258, 1005.13, 356.093, 15, 105, 207.562, -100.723, 1005.26, 0, 0, 800, 0, 207.504, -98.7054, 1005.26, 182.986, 2, 0, 0, 0, 0, '0|0|0|0|0|0|0|0|', -1, 'none', 'none', 'none');

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `objetos_admin`
--

CREATE TABLE `objetos_admin` (
  `ID` int(11) NOT NULL,
  `Modelo` int(11) NOT NULL DEFAULT 0,
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0,
  `RotX` float NOT NULL DEFAULT 0,
  `RotY` float NOT NULL DEFAULT 0,
  `RotZ` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `personajes`
--

CREATE TABLE `personajes` (
  `ID` int(11) NOT NULL,
  `Nombre_Apellido` varchar(24) NOT NULL DEFAULT 'none',
  `Codigo` varchar(24) NOT NULL DEFAULT '''none''',
  `CuentaID` int(11) NOT NULL DEFAULT -1,
  `PosicionX` float NOT NULL DEFAULT 0,
  `PosicionY` float NOT NULL DEFAULT 0,
  `PosicionZ` float NOT NULL DEFAULT 0,
  `PosicionR` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0,
  `Vida` float NOT NULL DEFAULT 100,
  `Chaleco` float NOT NULL DEFAULT 0,
  `Skin` int(11) NOT NULL DEFAULT 289,
  `FugaoVicio` int(11) NOT NULL DEFAULT 0,
  `Sexo` int(11) NOT NULL DEFAULT 1,
  `Edad` int(11) NOT NULL DEFAULT 16,
  `Ciudad` int(11) NOT NULL DEFAULT 1,
  `EstiloPelea` int(11) NOT NULL DEFAULT 4,
  `BolosUwU` int(11) NOT NULL DEFAULT 0,
  `BanescoOwO` int(11) NOT NULL DEFAULT 0,
  `LiderFaccion` int(11) NOT NULL DEFAULT 0,
  `MiembroFaccion` int(11) NOT NULL DEFAULT 0,
  `Rango` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_1` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_1` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_2` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_2` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_3` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_3` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_4` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_4` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_5` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_5` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_6` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_6` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_7` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_7` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_8` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_8` int(11) NOT NULL DEFAULT 0,
  `Bolsillo_9` int(11) NOT NULL DEFAULT 0,
  `Cantidad_bolsillo_9` int(11) NOT NULL DEFAULT 0,
  `Mano_derecha` int(11) NOT NULL DEFAULT 0,
  `Cantidad_mano_derecha` int(11) NOT NULL DEFAULT 0,
  `Mano_izquierda` int(11) NOT NULL DEFAULT 0,
  `Cantidad_mano_izquierda` int(11) NOT NULL DEFAULT 0,
  `Espalda` int(11) NOT NULL DEFAULT 0,
  `Cantidad_espalda` int(11) NOT NULL DEFAULT 0,
  `Muerto` int(11) NOT NULL DEFAULT 0,
  `Jails` int(11) NOT NULL DEFAULT 0,
  `Arrestos` int(11) NOT NULL DEFAULT 0,
  `Sancionado` int(11) NOT NULL DEFAULT 0,
  `TiempoSancion` int(11) NOT NULL DEFAULT 0,
  `BySancion` varchar(24) NOT NULL DEFAULT 'none',
  `RazonSancion` varchar(128) NOT NULL DEFAULT 'none',
  `Ganzuas` int(11) NOT NULL DEFAULT 0,
  `Telefono` int(11) NOT NULL DEFAULT 0,
  `Velocimetro` int(11) NOT NULL DEFAULT 1,
  `Licencia1` int(11) NOT NULL DEFAULT 0,
  `Licencia2` int(11) NOT NULL DEFAULT 0,
  `Licencia3` int(11) NOT NULL DEFAULT 0,
  `Licencia4` int(11) NOT NULL DEFAULT 0,
  `Licencia5` int(11) NOT NULL DEFAULT 0,
  `Mascara` int(11) NOT NULL DEFAULT 0,
  `UsoMascara` int(11) NOT NULL DEFAULT 0,
  `OtakuN_N` int(11) NOT NULL DEFAULT 0,
  `TimeBanUwU` int(11) NOT NULL DEFAULT 0,
  `FueBan` varchar(24) NOT NULL DEFAULT 'server',
  `ReasonBanUwU` varchar(256) NOT NULL DEFAULT 'abuso',
  `MomentBan` varchar(256) NOT NULL DEFAULT '-',
  `BlockBug` int(11) NOT NULL DEFAULT 0,
  `BlockG` int(11) NOT NULL DEFAULT 0,
  `Documento` int(11) NOT NULL DEFAULT 0,
  `Habilidad1` int(11) NOT NULL DEFAULT 0,
  `Habilidad2` int(11) NOT NULL DEFAULT 0,
  `Habilidad3` int(11) NOT NULL DEFAULT 0,
  `Habilidad4` int(11) NOT NULL DEFAULT 0,
  `Habilidad5` int(11) NOT NULL DEFAULT 0,
  `Payday` int(11) NOT NULL DEFAULT 30,
  `Estrellas` int(11) NOT NULL DEFAULT 0,
  `LimiteRobos` int(11) NOT NULL DEFAULT 0,
  `Frecuencia_radio` int(11) NOT NULL DEFAULT 0,
  `TipoSpawn` int(11) NOT NULL DEFAULT 0,
  `EstadoYo` varchar(128) NOT NULL DEFAULT '',
  `NombreContacto1` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto1` int(11) NOT NULL DEFAULT 0,
  `NombreContacto2` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto2` int(11) NOT NULL DEFAULT 0,
  `NombreContacto3` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto3` int(11) NOT NULL DEFAULT 0,
  `NombreContacto4` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto4` int(11) NOT NULL DEFAULT 0,
  `NombreContacto5` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto5` int(11) NOT NULL DEFAULT 0,
  `NombreContacto6` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto6` int(11) NOT NULL DEFAULT 0,
  `NombreContacto7` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto7` int(11) NOT NULL DEFAULT 0,
  `NombreContacto8` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto8` int(11) NOT NULL DEFAULT 0,
  `NombreContacto9` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto9` int(11) NOT NULL DEFAULT 0,
  `NombreContacto10` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto10` int(11) NOT NULL DEFAULT 0,
  `NombreContacto11` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto11` int(11) NOT NULL DEFAULT 0,
  `NombreContacto12` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto12` int(11) NOT NULL DEFAULT 0,
  `NombreContacto13` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto13` int(11) NOT NULL DEFAULT 0,
  `NombreContacto14` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto14` int(11) NOT NULL DEFAULT 0,
  `NombreContacto15` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto15` int(11) NOT NULL DEFAULT 0,
  `NombreContacto16` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto16` int(11) NOT NULL DEFAULT 0,
  `NombreContacto17` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto17` int(11) NOT NULL DEFAULT 0,
  `NombreContacto18` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto18` int(11) NOT NULL DEFAULT 0,
  `NombreContacto19` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto19` int(11) NOT NULL DEFAULT 0,
  `NombreContacto20` varchar(24) NOT NULL DEFAULT 'none',
  `NumeroContacto20` int(11) NOT NULL DEFAULT 0,
  `JobSkin` int(11) NOT NULL DEFAULT 0,
  `RestriccionRobo` int(11) NOT NULL DEFAULT 0,
  `FalsoDocumento` int(11) NOT NULL DEFAULT 0,
  `FalsoNombre` varchar(24) NOT NULL DEFAULT 'none',
  `FechaRegistro` varchar(256) NOT NULL DEFAULT 'none',
  `UltimaConexion` varchar(256) NOT NULL DEFAULT 'none',
  `CamaraOculta` int(11) NOT NULL DEFAULT 0,
  `Toy1` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy2` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy3` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy4` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy5` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy6` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy7` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy8` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy9` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Toy10` varchar(512) NOT NULL DEFAULT '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|',
  `Cinturon_1` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_1` int(11) NOT NULL DEFAULT 0,
  `Cinturon_2` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_2` int(11) NOT NULL DEFAULT 0,
  `Cinturon_3` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_3` int(11) NOT NULL DEFAULT 0,
  `Cinturon_4` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_4` int(11) NOT NULL DEFAULT 0,
  `Cinturon_5` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_5` int(11) NOT NULL DEFAULT 0,
  `Cinturon_6` int(11) NOT NULL DEFAULT 0,
  `Cantidad_cinturon_6` int(11) NOT NULL DEFAULT 0,
  `ColorToy1` int(11) NOT NULL DEFAULT -1,
  `ColorToy2` int(11) NOT NULL DEFAULT -1,
  `ColorToy3` int(11) NOT NULL DEFAULT -1,
  `ColorToy4` int(11) NOT NULL DEFAULT -1,
  `ColorToy5` int(11) NOT NULL DEFAULT -1,
  `ColorToy6` int(11) NOT NULL DEFAULT -1,
  `ColorToy7` int(11) NOT NULL DEFAULT -1,
  `ColorToy8` int(11) NOT NULL DEFAULT -1,
  `ColorToy9` int(11) NOT NULL DEFAULT -1,
  `ColorToy10` int(11) NOT NULL DEFAULT -1,
  `Trabajo1` int(11) NOT NULL DEFAULT -1,
  `Trabajo2` int(11) NOT NULL DEFAULT -1,
  `Trabajo3` int(11) NOT NULL DEFAULT -1,
  `Adiccion_1` int(11) NOT NULL DEFAULT 0,
  `Adiccion_2` int(11) NOT NULL DEFAULT 0,
  `Adiccion_3` int(11) NOT NULL DEFAULT 0,
  `Droga_tipo` int(11) NOT NULL DEFAULT 0,
  `Droga_tiempo` int(11) NOT NULL DEFAULT 0,
  `Droga_power` int(11) NOT NULL DEFAULT 0,
  `AbstinenceEffect` int(11) NOT NULL DEFAULT 0,
  `AbstinenceTime` int(11) NOT NULL DEFAULT 0,
  `TogManos` int(11) NOT NULL DEFAULT 1,
  `TogCajero` int(11) NOT NULL DEFAULT 0,
  `TogAnuncios` int(11) NOT NULL DEFAULT 0,
  `TogTelefono` int(11) NOT NULL DEFAULT 1,
  `TimerAnuncios` int(11) NOT NULL DEFAULT 0,
  `TogOOC` int(11) NOT NULL DEFAULT 1,
  `TogMusic` int(11) NOT NULL DEFAULT 1,
  `TogRadio` int(11) NOT NULL DEFAULT 1,
  `TogPortatil` int(11) NOT NULL DEFAULT 1,
  `TogFaccion` int(1) NOT NULL DEFAULT 1,
  `RepartoViajes` int(11) NOT NULL DEFAULT 0,
  `BasureroViajes` int(11) NOT NULL DEFAULT 0,
  `CosechasListas` int(11) NOT NULL DEFAULT 0,
  `EstiloManos` int(11) NOT NULL DEFAULT 1,
  `TiempoMolotov` int(11) NOT NULL DEFAULT 0,
  `AccesoGraffiti` int(11) NOT NULL DEFAULT 0,
  `ComprarNegocio` int(11) NOT NULL DEFAULT 0,
  `trailerAsignado` int(11) NOT NULL DEFAULT -1,
  `PtrailerAsignado` int(11) NOT NULL DEFAULT -1,
  `trailerDistancia` int(11) NOT NULL DEFAULT -1,
  `TipoCarga` int(11) NOT NULL DEFAULT 0,
  `Habilidad6` int(11) NOT NULL DEFAULT 0,
  `trailerIlegal` int(11) NOT NULL DEFAULT 0,
  `trailerTipo` int(11) NOT NULL DEFAULT 0,
  `trailerActivo` int(11) NOT NULL DEFAULT 0,
  `NivelSobredosis` int(11) NOT NULL DEFAULT 0,
  `AdiccionAnfetamina` int(11) NOT NULL DEFAULT 0,
  `AdiccionCocaina` int(11) NOT NULL DEFAULT 0,
  `AdiccionOpioides` int(11) NOT NULL DEFAULT 0,
  `EfectoMetanfetamina` int(11) NOT NULL DEFAULT 0,
  `EfectoCocaina` int(11) NOT NULL DEFAULT 0,
  `EfectoMarihuana` int(11) NOT NULL DEFAULT 0,
  `EfectoLSD` int(11) NOT NULL DEFAULT 0,
  `EfectoMDMA` int(11) NOT NULL DEFAULT 0,
  `EfectoHongo` int(11) NOT NULL DEFAULT 0,
  `EfectoEspecialUWU` int(11) NOT NULL DEFAULT 0,
  `TiempoMetanfetamina` int(11) NOT NULL DEFAULT 0,
  `TiempoCocaina` int(11) NOT NULL DEFAULT 0,
  `TiempoMarihuana` int(11) NOT NULL DEFAULT 0,
  `TiempoHeroina` int(11) NOT NULL DEFAULT 0,
  `TiempoKetamina` int(11) NOT NULL DEFAULT 0,
  `LabID` int(11) NOT NULL DEFAULT -1,
  `LlaveLab` int(11) NOT NULL DEFAULT -1,
  `Sobredosis` int(11) NOT NULL DEFAULT 0,
  `Dispatch` int(11) NOT NULL DEFAULT 0,
  `Peso` int(11) NOT NULL,
  `Estado` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `personajes`
--

INSERT INTO `personajes` (`ID`, `Nombre_Apellido`, `Codigo`, `CuentaID`, `PosicionX`, `PosicionY`, `PosicionZ`, `PosicionR`, `Interior`, `VirtualWorld`, `Vida`, `Chaleco`, `Skin`, `FugaoVicio`, `Sexo`, `Edad`, `Ciudad`, `EstiloPelea`, `BolosUwU`, `BanescoOwO`, `LiderFaccion`, `MiembroFaccion`, `Rango`, `Bolsillo_1`, `Cantidad_bolsillo_1`, `Bolsillo_2`, `Cantidad_bolsillo_2`, `Bolsillo_3`, `Cantidad_bolsillo_3`, `Bolsillo_4`, `Cantidad_bolsillo_4`, `Bolsillo_5`, `Cantidad_bolsillo_5`, `Bolsillo_6`, `Cantidad_bolsillo_6`, `Bolsillo_7`, `Cantidad_bolsillo_7`, `Bolsillo_8`, `Cantidad_bolsillo_8`, `Bolsillo_9`, `Cantidad_bolsillo_9`, `Mano_derecha`, `Cantidad_mano_derecha`, `Mano_izquierda`, `Cantidad_mano_izquierda`, `Espalda`, `Cantidad_espalda`, `Muerto`, `Jails`, `Arrestos`, `Sancionado`, `TiempoSancion`, `BySancion`, `RazonSancion`, `Ganzuas`, `Telefono`, `Velocimetro`, `Licencia1`, `Licencia2`, `Licencia3`, `Licencia4`, `Licencia5`, `Mascara`, `UsoMascara`, `OtakuN_N`, `TimeBanUwU`, `FueBan`, `ReasonBanUwU`, `MomentBan`, `BlockBug`, `BlockG`, `Documento`, `Habilidad1`, `Habilidad2`, `Habilidad3`, `Habilidad4`, `Habilidad5`, `Payday`, `Estrellas`, `LimiteRobos`, `Frecuencia_radio`, `TipoSpawn`, `EstadoYo`, `NombreContacto1`, `NumeroContacto1`, `NombreContacto2`, `NumeroContacto2`, `NombreContacto3`, `NumeroContacto3`, `NombreContacto4`, `NumeroContacto4`, `NombreContacto5`, `NumeroContacto5`, `NombreContacto6`, `NumeroContacto6`, `NombreContacto7`, `NumeroContacto7`, `NombreContacto8`, `NumeroContacto8`, `NombreContacto9`, `NumeroContacto9`, `NombreContacto10`, `NumeroContacto10`, `NombreContacto11`, `NumeroContacto11`, `NombreContacto12`, `NumeroContacto12`, `NombreContacto13`, `NumeroContacto13`, `NombreContacto14`, `NumeroContacto14`, `NombreContacto15`, `NumeroContacto15`, `NombreContacto16`, `NumeroContacto16`, `NombreContacto17`, `NumeroContacto17`, `NombreContacto18`, `NumeroContacto18`, `NombreContacto19`, `NumeroContacto19`, `NombreContacto20`, `NumeroContacto20`, `JobSkin`, `RestriccionRobo`, `FalsoDocumento`, `FalsoNombre`, `FechaRegistro`, `UltimaConexion`, `CamaraOculta`, `Toy1`, `Toy2`, `Toy3`, `Toy4`, `Toy5`, `Toy6`, `Toy7`, `Toy8`, `Toy9`, `Toy10`, `Cinturon_1`, `Cantidad_cinturon_1`, `Cinturon_2`, `Cantidad_cinturon_2`, `Cinturon_3`, `Cantidad_cinturon_3`, `Cinturon_4`, `Cantidad_cinturon_4`, `Cinturon_5`, `Cantidad_cinturon_5`, `Cinturon_6`, `Cantidad_cinturon_6`, `ColorToy1`, `ColorToy2`, `ColorToy3`, `ColorToy4`, `ColorToy5`, `ColorToy6`, `ColorToy7`, `ColorToy8`, `ColorToy9`, `ColorToy10`, `Trabajo1`, `Trabajo2`, `Trabajo3`, `Adiccion_1`, `Adiccion_2`, `Adiccion_3`, `Droga_tipo`, `Droga_tiempo`, `Droga_power`, `AbstinenceEffect`, `AbstinenceTime`, `TogManos`, `TogCajero`, `TogAnuncios`, `TogTelefono`, `TimerAnuncios`, `TogOOC`, `TogMusic`, `TogRadio`, `TogPortatil`, `TogFaccion`, `RepartoViajes`, `BasureroViajes`, `CosechasListas`, `EstiloManos`, `TiempoMolotov`, `AccesoGraffiti`, `ComprarNegocio`, `trailerAsignado`, `PtrailerAsignado`, `trailerDistancia`, `TipoCarga`, `Habilidad6`, `trailerIlegal`, `trailerTipo`, `trailerActivo`, `NivelSobredosis`, `AdiccionAnfetamina`, `AdiccionCocaina`, `AdiccionOpioides`, `EfectoMetanfetamina`, `EfectoCocaina`, `EfectoMarihuana`, `EfectoLSD`, `EfectoMDMA`, `EfectoHongo`, `EfectoEspecialUWU`, `TiempoMetanfetamina`, `TiempoCocaina`, `TiempoMarihuana`, `TiempoHeroina`, `TiempoKetamina`, `LabID`, `LlaveLab`, `Sobredosis`, `Dispatch`, `Peso`, `Estado`) VALUES
(1, 'Dereck_Goodman', 'FMNY', 3, -183.252, 1207.44, 19.6909, 18.6583, 0, 0, 90.1, 100, 7, 5, 1, 25, 1, 4, 3764703, 950, 0, 9, 5, 21, 5, 50, 1, 57, 14, 0, 0, 0, 0, 65, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 0, 500001, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'server', 'abuso', '-', 0, 0, 2000001, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, '', 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 0, 0, 0, 'none', '19:39:28 - 27/04/2026', '16:31:24 - 07/09/2026', 0, '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|1|0.250999|-0.130998|0.135998|-1.500012|152.599945|5.399990|1.000000|1.000000|1.000000|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0),
(2, 'Dewey_Sosa', 'DXGD', 3, 1822.18, 385.734, 2998.39, 272.48, 0, 1, 95.05, 0, 7, 0, 1, 25, 1, 4, 5870, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 1, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 0, 500002, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'server', 'abuso', '-', 0, 0, 2000002, 0, 0, 0, 0, 0, 38, 0, 0, 0, 0, '', 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 0, 0, 0, 'none', '08:15:09 - 28/04/2026', '03:42:20 - 06/09/2026', 0, '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0),
(3, 'Jose_Paredes', 'XIXD', 6, -121.558, 1209.34, 19.6647, 62.7224, 0, 0, 100, 0, 7, 0, 1, 25, 1, 4, 10000, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 50, 1, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 0, 500003, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'server', 'abuso', '-', 0, 0, 2000003, 0, 0, 0, 0, 0, 31, 0, 0, 0, 0, '', 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 'none', 0, 0, 0, 0, 'none', '00:53:34 - 07/09/2026', '00:54:45 - 07/09/2026', 0, '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', '0|0|0.0|0.0|0.0|0.0|0.0|0.0|1|1|1|0|', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `plantas`
--

CREATE TABLE `plantas` (
  `ID` int(11) NOT NULL,
  `Tipo` int(11) DEFAULT 0,
  `Plantador` int(11) NOT NULL DEFAULT 0,
  `TiempoRestante` int(11) NOT NULL DEFAULT 0,
  `X` float NOT NULL DEFAULT 0,
  `Y` float NOT NULL DEFAULT 0,
  `Z` float NOT NULL DEFAULT 0,
  `I` int(11) NOT NULL DEFAULT 0,
  `VW` int(11) NOT NULL DEFAULT 0,
  `Cosechas` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=latin1 COLLATE=latin1_swedish_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `puertas`
--

CREATE TABLE `puertas` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(128) NOT NULL DEFAULT 'none',
  `ExteriorX` float NOT NULL DEFAULT 0,
  `ExteriorY` float NOT NULL DEFAULT 0,
  `ExteriorZ` float NOT NULL DEFAULT 0,
  `ExteriorR` float NOT NULL DEFAULT 0,
  `ExteriorInt` int(11) NOT NULL DEFAULT 0,
  `ExteriorVW` int(11) NOT NULL DEFAULT 0,
  `InteriorX` float NOT NULL DEFAULT 0,
  `InteriorY` float NOT NULL DEFAULT 0,
  `InteriorZ` float NOT NULL DEFAULT 0,
  `InteriorR` float NOT NULL DEFAULT 0,
  `InteriorInt` int(11) NOT NULL DEFAULT 0,
  `InteriorVW` int(11) NOT NULL DEFAULT 0,
  `Modelo` int(11) NOT NULL DEFAULT 0,
  `MapIcon` int(11) NOT NULL DEFAULT 0,
  `Faccion` int(11) NOT NULL DEFAULT 0,
  `Admin` int(11) NOT NULL DEFAULT 0,
  `VIP` int(11) NOT NULL DEFAULT 0,
  `Estrellas` int(11) NOT NULL DEFAULT 0,
  `StatusVehiculo` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `puertas`
--

INSERT INTO `puertas` (`ID`, `Nombre`, `ExteriorX`, `ExteriorY`, `ExteriorZ`, `ExteriorR`, `ExteriorInt`, `ExteriorVW`, `InteriorX`, `InteriorY`, `InteriorZ`, `InteriorR`, `InteriorInt`, `InteriorVW`, `Modelo`, `MapIcon`, `Faccion`, `Admin`, `VIP`, `Estrellas`, `StatusVehiculo`) VALUES
(1, 'LACSD - East Beach Station', 2759.46, -1451.4, 31.5022, 136.905, 0, 0, 1553.3, -1674.01, 2110.54, 273.105, 41, 15, 7, 30, 0, 0, 0, 0, 0),
(2, 'SASD', 627.118, -571.882, 17.9145, 274.764, 0, 0, 1628.77, 1587.04, 10.8359, 94.7877, 40, 10, 0, 0, 0, 0, 0, 0, 0),
(3, 'City Hall (Ayuntamiento)', 1480.83, -1772.12, 18.7958, 359.923, 0, 0, 1466.91, -1744.8, 3910.09, 272.243, 74, 74, 0, 0, 0, 0, 0, 0, 0),
(4, 'Estacionamiento (Ayuntamiento)', -807.973, -1751.82, 46.5406, 358.376, 5, 20, 1482.52, -1731.32, 3910.09, 177.784, 74, 74, 0, 0, 0, 0, 0, 0, 0),
(5, 'Escaleras - LAPD', 1203.88, -1123.29, 32.2333, 76.9995, 0, 0, 1588.25, -1658.92, 2110.54, 79.3907, 41, 16, 0, 0, 1, 0, 0, 0, 0),
(6, 'Azotea (Ayuntamiento)', 1526.16, -1793.99, 33.4297, 269.948, 0, 0, 1474.97, -1732.75, 3910.09, 182.171, 74, 74, 0, 0, 0, 0, 0, 0, 0),
(7, 'Garage - LACSD', 2780.2, -1444.89, 30.4721, 182.543, 0, 0, -843.9, -1722.43, 46.5302, 185.255, 5, 2, 0, 0, 4, 0, 0, 0, 1),
(8, 'La Pención', 2259.75, -1019.45, 59.2944, 47.7895, 0, 0, 1990.23, 1116.51, 22.5186, 9.25776, 43, 50, 0, 32, 0, 0, 0, 0, 0),
(9, 'Bloque Bahamas C', 1909.78, -1597.59, 14.3062, 188.326, 0, 0, 309.367, 2036.69, 8501.7, 87.8039, 39, 45, 0, 0, 0, 0, 0, 0, 0),
(10, 'Gimnasio', 2229.89, -1721.26, 13.5613, 136.869, 0, 0, 772.371, -5.50593, 1000.73, 2.72319, 5, 0, 0, 0, 0, 0, 0, 0, 0),
(11, 'Bloque Bahamas B', 1904.85, -1577.55, 14.6501, 0.66116, 0, 0, 1374.42, 1451.28, 10.8262, 358.499, 49, 55, 0, 0, 0, 0, 0, 0, 0),
(12, 'Bloque Bahamas B', 1863.66, -1597.4, 14.3062, 178.323, 0, 0, 1393.3, 1472.47, 10.8262, 179.584, 49, 55, 0, 0, 0, 0, 0, 0, 0),
(13, 'Oculto', 1369.82, 1462.06, 10.8262, 271.078, 49, 55, 1359.25, 1462.13, 10.8262, 88.7166, 49, 55, 0, 0, 0, 0, 0, 0, 0),
(14, 'Armed Forces Equipment Room', 226.322, 1889.53, 18.3439, 90.0122, 0, 0, 3133.65, -2161.15, 4164.22, 95.5073, 56, 32, 0, 0, 0, 0, 0, 0, 0),
(15, 'Garage', 2233.29, -1159.65, 25.8906, 91.0557, 0, 0, 2214.56, -1150.58, 1025.8, 276.574, 15, 20, 0, 0, 0, 0, 0, 0, 0),
(16, 'Acceso al Faro', 154.3, -1946.62, 5.38925, 2.45981, 0, 0, 151.648, -1962.06, 1660.4, 171.069, 1, 1, 23, 0, 0, 0, 0, 0, 0),
(17, 'Faro - Zona Alta', 154.847, -1965.61, 1685.41, 87.7327, 1, 1, 154.313, -1949.76, 47.875, 0.353877, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(18, 'Torre de control', 263.007, 1956.03, 17.6457, 268.457, 0, 0, 250.465, 1955.63, 57.012, 268.167, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(19, 'Estacionamiento (FBI)', 1602.95, 1566.97, 10.8359, 181.597, 38, 29, -807.878, -1752.3, 46.5406, 3.83706, 5, 19, 0, 0, 0, 0, 0, 0, 0),
(20, 'Banco (Los Santos)', 1690.05, -1250, 14.825, 279.69, 0, 0, -988.611, 1443.98, 1340.63, 356.204, 11, 0, 0, 52, 0, 0, 0, 0, 0),
(21, 'Lounge VIP - Premium', 816.277, -1386.31, 13.6537, 181.474, 0, 0, 812, -1421.09, 1016.47, 1.6541, 0, 1, 17, 0, 0, 0, 1, 0, 0),
(22, 'Dirección general de tráfico', 1219.09, -1811.7, 16.5938, 359.202, 0, 0, 390.765, 173.806, 1008.38, 93.1047, 3, 5, 18, 2, 0, 0, 0, 0, 0),
(23, 'Fuerzas Neonazis', -1425.69, -1529.84, 102.242, 176.605, 0, 0, 2807.66, -1174.75, 1025.57, 180.052, 8, 9, 0, 0, 0, 0, 0, 0, 0),
(24, 'All Saints General Hospital', 1172.08, -1325.39, 15.4075, 270.284, 0, 0, 1172.56, -1324.54, 1015.41, 92.8425, 61, 20, 0, 22, 0, 0, 0, 0, 0),
(25, 'Segunda planta (hospital)', 1151.68, -1333.33, 1015.41, 273.469, 61, 20, 1177.4, -1330.8, 3015.41, 182.77, 61, 20, 0, 0, 0, 0, 0, 0, 0),
(26, 'InterGlobal Television', 649.023, -1360.72, 13.5864, 93.4412, 0, 0, 1442.94, -1069.27, 1718.01, 271.706, 62, 0, 0, 37, 0, 0, 0, 0, 0),
(27, 'Azotea - LACSD', 2787.76, -1432.46, 35.9202, 87.4412, 0, 0, 1602.9, 1566.43, 10.8359, 14.416, 38, 50, 0, 0, 4, 0, 0, 0, 0),
(28, 'Helipuerto - LACSD', 2758.93, -1428.38, 31.4029, 87.3419, 0, 0, 2771.58, -1434.64, 35.9502, 268.43, 0, 0, 0, 0, 4, 0, 0, 0, 0),
(29, 'Estacionamiento - LACSD', 1603.42, -1651.02, 2107.08, 178.277, 41, 15, -808.03, -1751.03, 46.8725, 183.382, 5, 2, 0, 0, 0, 0, 0, 0, 0),
(30, 'Repartidor (Sala)', 2444.52, -2132.64, 17.2712, 179.941, 0, 0, 1033.25, -310.223, 2076.65, 1.79689, 51, 20, 0, 56, 0, 0, 0, 0, 0),
(31, 'Granjero (Sala)', -382.84, -1426.26, 26.2906, 274.214, 0, 0, 1033.28, -310.095, 2076.65, 1.02527, 51, 38, 0, 56, 0, 0, 0, 0, 0),
(32, 'Planta baja', 226.108, 981.027, 1084.02, 0.507449, 40, 541, 493.395, -24.8122, 1000.68, 1.32293, 17, 55, 0, 0, 0, 0, 0, 0, 0),
(33, 'Oficinas (Basurero)', 2075.81, -2040.03, 13.5469, 272.209, 0, 0, 1033.28, -310.095, 2076.65, 1.02527, 51, 24, 0, 56, 0, 0, 0, 0, 0),
(34, 'Motel Idlewood', 2177.14, -1769.96, 13.5391, 269.057, 0, 0, 309.245, 2036.73, 8501.7, 93.2756, 39, 39, 0, 32, 0, 0, 0, 0, 0),
(35, 'Apartamentos Idlewood', 2019.8, -1764.81, 13.5537, 93.2273, 0, 0, 1990.29, 1116.76, 22.5186, 3.3465, 43, 43, 0, 32, 0, 0, 0, 0, 0),
(36, 'Apartamentos East Los Santos', 2521.29, -1281.83, 34.8516, 90.4782, 0, 0, 2522.98, -1272.66, 34.9453, 276.502, 0, 0, 0, 32, 0, 0, 0, 0, 0),
(37, 'Departament Of Corrections', 1797.56, -1578.84, 14.0851, 284.991, 0, 0, 1767.84, -1552.31, -39.8473, 90.6705, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(38, 'Recruit\'s Barracks', 39.4714, 1794.91, 18.6408, 281.826, 0, 0, 3133.56, -2161.03, 4164.22, 89.1942, 55, 10, 0, 0, 0, 0, 0, 0, 0),
(39, 'Enlisted\'s Barracks', 39.3158, 1819.24, 18.3408, 272.257, 0, 0, 3133.56, -2161.03, 4164.22, 89.1942, 55, 12, 0, 0, 0, 0, 0, 0, 0),
(40, 'Officer\'s Barracks', 39.3059, 1874.25, 18.3408, 271.486, 0, 0, 3133.56, -2161.03, 4164.22, 89.1942, 55, 30, 0, 0, 0, 0, 0, 0, 0),
(41, 'Estacionamiento (sadoc)', -807.966, -1751.47, 46.5406, 359.133, 5, 5, 1754.19, -1554.98, -39.8473, 359.536, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(42, 'Zona restringida', 1755.66, -1537.11, -39.8473, 181.8, 60, 60, 1748.53, -1512.01, -39.8473, 358.858, 60, 60, 0, 0, 7, 0, 0, 0, 0),
(43, 'Sala de visitas', 1759.07, -1537.08, -39.8473, 181.028, 60, 60, 1754.87, -1512.09, -39.8473, 359.776, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(44, 'Centro de celdas', 1740.54, -1511.53, -39.8473, 273.149, 60, 60, 1707.11, -1486.68, -39.8473, 90.1607, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(45, 'Casilleros (sadoc)', 1767.39, -1545.36, -39.8473, 1.1732, 60, 60, 322.307, 309.247, 999.148, 181.095, 5, 10, 0, 0, 7, 0, 0, 0, 0),
(46, 'C\' máxima seguridad', 1689.49, -1482.29, -39.8473, 269.052, 60, 60, 1784.26, -1573.4, -17.0173, 3.36651, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(47, 'Enfermería', 1703.27, -1479.45, -39.8473, 183.993, 60, 60, 1697.83, -1452.87, -39.8473, 91.6292, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(48, 'Patio B', 1698.36, -1479.45, -39.8473, 181.173, 60, 60, 1738.9, -1405.12, -39.3088, 179.172, 60, 60, 0, 0, 0, 0, 0, 0, 0),
(49, 'Garage LSFD', -807.97, -1752.13, 46.5406, 359.633, 5, 49, 1175.71, -1308.45, 13.9992, 85.1128, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(50, 'Zona VIP', -222.459, 1411.33, 27.7734, 271.18, 18, 107, -2158.63, 643.061, 1052.38, 181.443, 1, 107, 0, 0, 0, 0, 0, 0, 0),
(51, 'Acceso a Terraza', 1234.11, -819.357, 1084.17, 177.685, 5, 839, 973.077, -1938.57, 13.986, 109.05, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(52, 'Acceso a patio trasero', 974.934, -1943.88, 3.47833, 104.495, 0, 0, 1298.98, -796.863, 1084.01, 4.22702, 5, 839, 0, 0, 0, 0, 0, 0, 0),
(53, 'Almacen', 2769.96, -1611.4, 10.9219, 268.45, 0, 0, 1060.22, 2084.38, 10.8203, 267.197, 0, 902, 0, 0, 8, 0, 0, 0, 1),
(54, 'The Bahamas Apts', 2036.19, -1311.9, 25.2163, 88.8373, 0, 0, 309.22, 2036.72, 8501.7, 84.8856, 39, 912, 0, 32, 0, 0, 0, 0, 0),
(55, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(56, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(57, 'Centro de Inteligencia - LACSD', 1588.34, -1659, 2110.54, 79.7072, 41, 15, 1602.39, 1574.71, 10.8359, 179.077, 38, 50, 0, 0, 0, 0, 0, 0, 0),
(58, 'FBI', 1487.76, -1280.9, 14.5683, 1.73742, 0, 0, 1602.47, 1574.76, 10.8359, 359.857, 38, 29, 0, 0, 0, 0, 0, 0, 0),
(59, 'Garage FBI', 1497.81, -1243.02, 14.5694, 180.486, 0, 0, -843.566, -1722.91, 46.5319, 87.7384, 5, 19, 0, 0, 0, 0, 0, 0, 1),
(60, 'Helipuerto FBI', 1586.82, 1554.45, 10.8394, 176.85, 38, 29, 1515.67, -1257.97, 113.76, 276.895, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(61, 'Garage LSFD', 1139.85, -1329.82, 13.67, 262.19, 0, 0, -843.554, -1723.29, 46.5333, 87.9749, 5, 49, 0, 0, 0, 0, 0, 0, 1),
(62, 'Hogar', 470.753, -1163.56, 67.2178, 11.135, 0, 0, 470.753, -1161.56, 67.2178, 11.135, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(63, 'LAPD - Hollywood Station', 1192.81, -1124.18, 24.7788, 176.652, 0, 0, 1553.19, -1674.06, 2110.54, 272.27, 41, 16, 0, 30, 0, 0, 0, 0, 0),
(64, 'Estacionamiento', 1207.58, -1131.08, 24.0134, 1.21079, 0, 0, -846.774, -1722.03, 46.5406, 183.296, 5, 3, 0, 0, 1, 0, 0, 0, 1),
(65, 'Garage SADOC', 1791.36, -1594.48, 13.5179, 155.389, 0, 0, -845.973, -1722.58, 46.5423, 272.371, 5, 5, 0, 0, 0, 0, 0, 0, 1),
(66, 'Helipuerto', 619.212, -566.732, 26.1484, 268.37, 0, 0, 1618.03, 1566.35, 10.8359, 179.023, 40, 10, 0, 0, 0, 0, 0, 0, 0),
(67, 'Helipuerto - LAPD', 1186.03, -1126.85, 32.1107, 356.75, 0, 0, 1180.23, -1128.89, 24.1752, 80.3164, 0, 0, 0, 0, 1, 0, 0, 0, 0),
(68, 'Garage GOB', 1480.61, -1825.45, 13.5469, 0.592813, 0, 0, -844.346, -1723.14, 46.5328, 92.4149, 5, 20, 0, 0, 0, 0, 0, 0, 0),
(69, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(70, 'Oficina (Uber)', 1803.25, -1897.74, 13.4034, 273.106, 0, 0, 1033.36, -310.332, 2076.65, 6.49706, 51, 70, 0, 0, 0, 0, 0, 0, 0),
(71, 'Oficina (Trailero)', 1293.93, 197.236, 20.2891, 336.507, 0, 0, 1033.27, -310.345, 2076.65, 183.05, 51, 87, 0, 0, 0, 0, 0, 0, 0),
(72, 'Patio A', 1693.56, -1479.38, -39.8473, 177.891, 60, 60, 1772.52, -1548.56, 9.91332, 41.0372, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(73, 'Ascensor - LAPD', -807.893, -1742.99, 46.8725, 358.174, 5, 3, 1603.38, -1651.12, 2107.08, 185.057, 41, 16, 0, 0, 0, 0, 0, 0, 0),
(74, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(75, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(76, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(77, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(78, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(79, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(80, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(81, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(82, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(83, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(84, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(85, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(86, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(87, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(88, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(89, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(90, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(91, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(96, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(92, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(93, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(94, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(95, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(97, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(98, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0),
(99, 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `ubicaciones`
--

CREATE TABLE `ubicaciones` (
  `ID` int(11) NOT NULL,
  `Ubicacion` varchar(128) CHARACTER SET latin1 COLLATE latin1_swedish_ci NOT NULL DEFAULT 'none',
  `PotX` float NOT NULL DEFAULT 0,
  `PotY` float NOT NULL DEFAULT 0,
  `PotZ` float NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `ubicaciones`
--

INSERT INTO `ubicaciones` (`ID`, `Ubicacion`, `PotX`, `PotY`, `PotZ`) VALUES
(1, 'Los Ángeles City Hall', 1480.94, -1749.96, 15.4453),
(2, 'Los Ángeles Sheriff\'s Department', 2746.79, -1457.82, 30.4531),
(3, 'Los Ángeles Police Department', 1192.65, -1131.9, 23.8925),
(4, 'All Saints General Hospital', 1178.64, -1325.51, 14.13),
(5, 'Depósito de Autos', 1620.61, -1864.11, 13.5469);

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `unknowns`
--

CREATE TABLE `unknowns` (
  `code_one` varchar(5) NOT NULL,
  `code_two` varchar(5) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_general_ci;

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `vehiculos`
--

CREATE TABLE `vehiculos` (
  `ID` int(11) NOT NULL,
  `Nombre` varchar(128) NOT NULL DEFAULT 'none',
  `Propietario` varchar(24) NOT NULL DEFAULT 'none',
  `Tipo` int(11) NOT NULL DEFAULT 0,
  `Negocio` int(11) NOT NULL DEFAULT 0,
  `Trabajo` int(11) NOT NULL DEFAULT 0,
  `Modelo` int(11) NOT NULL DEFAULT 0,
  `Posicion_X` float NOT NULL DEFAULT 0,
  `Posicion_Y` float NOT NULL DEFAULT 0,
  `Posicion_Z` float NOT NULL DEFAULT 0,
  `Posicion_R` float NOT NULL DEFAULT 0,
  `Interior` int(11) NOT NULL DEFAULT 0,
  `VirtualWorld` int(11) NOT NULL DEFAULT 0,
  `End_Posicion_X` float NOT NULL DEFAULT 0,
  `End_Posicion_Y` float NOT NULL DEFAULT 0,
  `End_Posicion_Z` float NOT NULL DEFAULT 0,
  `End_Posicion_R` float NOT NULL DEFAULT 0,
  `End_Interior` int(11) NOT NULL DEFAULT 0,
  `End_VirtualWorld` int(11) NOT NULL DEFAULT 0,
  `Vida` float NOT NULL DEFAULT 1000,
  `DanioSuperficie` int(11) NOT NULL DEFAULT 0,
  `DanioPuertas` int(11) NOT NULL DEFAULT 0,
  `DanioLuces` int(11) NOT NULL DEFAULT 0,
  `DanioRuedas` int(11) NOT NULL DEFAULT 0,
  `Gasolina` int(11) NOT NULL DEFAULT 200,
  `Color_1` int(11) NOT NULL DEFAULT 1,
  `Color_2` int(11) NOT NULL DEFAULT 1,
  `PaintJob` int(11) NOT NULL DEFAULT -1,
  `ConSeguro` int(11) NOT NULL DEFAULT 0,
  `Precio` int(11) NOT NULL DEFAULT 0,
  `Embargo` int(11) NOT NULL DEFAULT 0,
  `Multa` int(11) NOT NULL DEFAULT 0,
  `Maletero1` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant1` int(11) NOT NULL DEFAULT 0,
  `Maletero2` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant2` int(11) NOT NULL DEFAULT 0,
  `Maletero3` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant3` int(11) NOT NULL DEFAULT 0,
  `Maletero4` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant4` int(11) NOT NULL DEFAULT 0,
  `Maletero5` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant5` int(11) NOT NULL DEFAULT 0,
  `Maletero6` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant6` int(11) NOT NULL DEFAULT 0,
  `Maletero7` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant7` int(11) NOT NULL DEFAULT 0,
  `Maletero8` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant8` int(11) NOT NULL DEFAULT 0,
  `Maletero9` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant9` int(11) NOT NULL DEFAULT 0,
  `Maletero10` int(11) NOT NULL DEFAULT 0,
  `MaleteroCant10` int(11) NOT NULL DEFAULT 0,
  `MaxMaletero` int(11) NOT NULL DEFAULT 5,
  `Modificacion1` int(11) NOT NULL DEFAULT 0,
  `Modificacion2` int(11) NOT NULL DEFAULT 0,
  `Modificacion3` int(11) NOT NULL DEFAULT 0,
  `Modificacion4` int(11) NOT NULL DEFAULT 0,
  `Modificacion5` int(11) NOT NULL DEFAULT 0,
  `Modificacion6` int(11) NOT NULL DEFAULT 0,
  `Modificacion7` int(11) NOT NULL DEFAULT 0,
  `Modificacion8` int(11) NOT NULL DEFAULT 0,
  `Modificacion9` int(11) NOT NULL DEFAULT 0,
  `Modificacion10` int(11) NOT NULL DEFAULT 0,
  `Modificacion11` int(11) NOT NULL DEFAULT 0,
  `Modificacion12` int(11) NOT NULL DEFAULT 0,
  `Modificacion13` int(11) NOT NULL DEFAULT 0,
  `Modificacion14` int(11) NOT NULL DEFAULT 0,
  `Modificacion15` int(11) NOT NULL DEFAULT 0,
  `CallSign` varchar(40) NOT NULL DEFAULT '',
  `ObjModelo_1` int(11) NOT NULL DEFAULT 0,
  `ObjPosX_1` float NOT NULL DEFAULT 0,
  `ObjPosY_1` float NOT NULL DEFAULT 0,
  `ObjPosZ_1` float NOT NULL DEFAULT 0,
  `ObjRotX_1` float NOT NULL DEFAULT 0,
  `ObjRotY_1` float NOT NULL DEFAULT 0,
  `ObjRotZ_1` float NOT NULL DEFAULT 0,
  `ObjModelo_2` int(11) NOT NULL DEFAULT 0,
  `ObjPosX_2` float NOT NULL DEFAULT 0,
  `ObjPosY_2` float NOT NULL DEFAULT 0,
  `ObjPosZ_2` float NOT NULL DEFAULT 0,
  `ObjRotX_2` float NOT NULL DEFAULT 0,
  `ObjRotY_2` float NOT NULL DEFAULT 0,
  `ObjRotZ_2` float NOT NULL DEFAULT 0,
  `ObjModelo_3` int(11) NOT NULL DEFAULT 0,
  `ObjPosX_3` float NOT NULL DEFAULT 0,
  `ObjPosY_3` float NOT NULL DEFAULT 0,
  `ObjPosZ_3` float NOT NULL DEFAULT 0,
  `ObjRotX_3` float NOT NULL DEFAULT 0,
  `ObjRotY_3` float NOT NULL DEFAULT 0,
  `ObjRotZ_3` float NOT NULL DEFAULT 0,
  `ObjModelo_4` int(11) NOT NULL DEFAULT 0,
  `ObjPosX_4` float NOT NULL DEFAULT 0,
  `ObjPosY_4` float NOT NULL DEFAULT 0,
  `ObjPosZ_4` float NOT NULL DEFAULT 0,
  `ObjRotX_4` float NOT NULL DEFAULT 0,
  `ObjRotY_4` float NOT NULL DEFAULT 0,
  `ObjRotZ_4` float NOT NULL DEFAULT 0,
  `ObjModelo_5` int(11) NOT NULL DEFAULT 0,
  `ObjPosX_5` float NOT NULL DEFAULT 0,
  `ObjPosY_5` float NOT NULL DEFAULT 0,
  `ObjPosZ_5` float NOT NULL DEFAULT 0,
  `ObjRotX_5` float NOT NULL DEFAULT 0,
  `ObjRotY_5` float NOT NULL DEFAULT 0,
  `ObjRotZ_5` float NOT NULL DEFAULT 0,
  `Sirena` int(11) NOT NULL DEFAULT 0,
  `Premium` int(11) NOT NULL DEFAULT 0,
  `Compartida1` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida2` varchar(24) NOT NULL DEFAULT 'none',
  `Compartida3` varchar(24) NOT NULL DEFAULT 'none',
  `Stereo` int(11) NOT NULL DEFAULT 0
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Volcado de datos para la tabla `vehiculos`
--

INSERT INTO `vehiculos` (`ID`, `Nombre`, `Propietario`, `Tipo`, `Negocio`, `Trabajo`, `Modelo`, `Posicion_X`, `Posicion_Y`, `Posicion_Z`, `Posicion_R`, `Interior`, `VirtualWorld`, `End_Posicion_X`, `End_Posicion_Y`, `End_Posicion_Z`, `End_Posicion_R`, `End_Interior`, `End_VirtualWorld`, `Vida`, `DanioSuperficie`, `DanioPuertas`, `DanioLuces`, `DanioRuedas`, `Gasolina`, `Color_1`, `Color_2`, `PaintJob`, `ConSeguro`, `Precio`, `Embargo`, `Multa`, `Maletero1`, `MaleteroCant1`, `Maletero2`, `MaleteroCant2`, `Maletero3`, `MaleteroCant3`, `Maletero4`, `MaleteroCant4`, `Maletero5`, `MaleteroCant5`, `Maletero6`, `MaleteroCant6`, `Maletero7`, `MaleteroCant7`, `Maletero8`, `MaleteroCant8`, `Maletero9`, `MaleteroCant9`, `Maletero10`, `MaleteroCant10`, `MaxMaletero`, `Modificacion1`, `Modificacion2`, `Modificacion3`, `Modificacion4`, `Modificacion5`, `Modificacion6`, `Modificacion7`, `Modificacion8`, `Modificacion9`, `Modificacion10`, `Modificacion11`, `Modificacion12`, `Modificacion13`, `Modificacion14`, `Modificacion15`, `CallSign`, `ObjModelo_1`, `ObjPosX_1`, `ObjPosY_1`, `ObjPosZ_1`, `ObjRotX_1`, `ObjRotY_1`, `ObjRotZ_1`, `ObjModelo_2`, `ObjPosX_2`, `ObjPosY_2`, `ObjPosZ_2`, `ObjRotX_2`, `ObjRotY_2`, `ObjRotZ_2`, `ObjModelo_3`, `ObjPosX_3`, `ObjPosY_3`, `ObjPosZ_3`, `ObjRotX_3`, `ObjRotY_3`, `ObjRotZ_3`, `ObjModelo_4`, `ObjPosX_4`, `ObjPosY_4`, `ObjPosZ_4`, `ObjRotX_4`, `ObjRotY_4`, `ObjRotZ_4`, `ObjModelo_5`, `ObjPosX_5`, `ObjPosY_5`, `ObjPosZ_5`, `ObjRotX_5`, `ObjRotY_5`, `ObjRotZ_5`, `Sirena`, `Premium`, `Compartida1`, `Compartida2`, `Compartida3`, `Stereo`) VALUES
(1, 'none', 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 200, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 'none', 0),
(2, 'none', 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 200, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 'none', 0),
(3, 'none', 'none', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 200, 1, 1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 'none', 0),
(4, 'Voodoo', 'Dewey_Sosa', 0, 0, 0, 412, -178.205, 1217.38, 19.7422, 269.294, 0, 0, 0, 0, 0, 0, 0, 0, 1000, 0, 0, 0, 0, 200, 3, 3, -1, 0, 4130, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 'none', 'none', 'none', 0);

--
-- Índices para tablas volcadas
--

--
-- Indices de la tabla `actores`
--
ALTER TABLE `actores`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `antecedentes`
--
ALTER TABLE `antecedentes`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `bidones`
--
ALTER TABLE `bidones`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `cajas`
--
ALTER TABLE `cajas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `cajeros`
--
ALTER TABLE `cajeros`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `casas`
--
ALTER TABLE `casas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `contenedores`
--
ALTER TABLE `contenedores`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `cuentas`
--
ALTER TABLE `cuentas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `facciones`
--
ALTER TABLE `facciones`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `graffitis`
--
ALTER TABLE `graffitis`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `incendios`
--
ALTER TABLE `incendios`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `ips`
--
ALTER TABLE `ips`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `laboratorios`
--
ALTER TABLE `laboratorios`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `mochilas`
--
ALTER TABLE `mochilas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `muebles`
--
ALTER TABLE `muebles`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `negocios`
--
ALTER TABLE `negocios`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `objetos_admin`
--
ALTER TABLE `objetos_admin`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `personajes`
--
ALTER TABLE `personajes`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `plantas`
--
ALTER TABLE `plantas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `puertas`
--
ALTER TABLE `puertas`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `ubicaciones`
--
ALTER TABLE `ubicaciones`
  ADD PRIMARY KEY (`ID`);

--
-- Indices de la tabla `vehiculos`
--
ALTER TABLE `vehiculos`
  ADD PRIMARY KEY (`ID`);

--
-- AUTO_INCREMENT de las tablas volcadas
--

--
-- AUTO_INCREMENT de la tabla `actores`
--
ALTER TABLE `actores`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `antecedentes`
--
ALTER TABLE `antecedentes`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `bidones`
--
ALTER TABLE `bidones`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `cajas`
--
ALTER TABLE `cajas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `cajeros`
--
ALTER TABLE `cajeros`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=18;

--
-- AUTO_INCREMENT de la tabla `casas`
--
ALTER TABLE `casas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `contenedores`
--
ALTER TABLE `contenedores`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;

--
-- AUTO_INCREMENT de la tabla `cuentas`
--
ALTER TABLE `cuentas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=7;

--
-- AUTO_INCREMENT de la tabla `facciones`
--
ALTER TABLE `facciones`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=15;

--
-- AUTO_INCREMENT de la tabla `graffitis`
--
ALTER TABLE `graffitis`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `incendios`
--
ALTER TABLE `incendios`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `ips`
--
ALTER TABLE `ips`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `laboratorios`
--
ALTER TABLE `laboratorios`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `mochilas`
--
ALTER TABLE `mochilas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `muebles`
--
ALTER TABLE `muebles`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `negocios`
--
ALTER TABLE `negocios`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT de la tabla `objetos_admin`
--
ALTER TABLE `objetos_admin`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `personajes`
--
ALTER TABLE `personajes`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=4;

--
-- AUTO_INCREMENT de la tabla `plantas`
--
ALTER TABLE `plantas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT;

--
-- AUTO_INCREMENT de la tabla `puertas`
--
ALTER TABLE `puertas`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=100;

--
-- AUTO_INCREMENT de la tabla `ubicaciones`
--
ALTER TABLE `ubicaciones`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;

--
-- AUTO_INCREMENT de la tabla `vehiculos`
--
ALTER TABLE `vehiculos`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=5;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
