VerificarPersonaje(account[])
{
	new query[256];
	mysql_format(db_samp, query, sizeof query, "SELECT * FROM personajes WHERE Nombre_Apellido = '%e'", account);
	new Cache:result;
	result = mysql_query(db_samp, query);
	if (cache_num_rows() > 0) return 1;
	cache_delete(result);
	return 0;
}

enum personajeInfo
{
	pID,								// ID en base de datos
	pNombre_Apellido[MAX_PLAYER_NAME],	// Nombre_Apellido
	pCodigo[24],			// Código
    pCuentaID,                          // ID en cuentas
	Float: pPosicionX,      			// Posición x
	Float: pPosicionY,      			// Posición y
	Float: pPosicionZ,      			// Posición z
	Float: pPosicionR,      			// Posición angulo
	pInterior,              			// Interior
	pVirtualWorld,          			// VirtualWorld
	Float: pVida,           			// Vida
	Float: pChaleco,        			// Chaleco
	pSkin,                          	// Skin actual
	pHorasOn,               			// Horas conectado
	pSexo,       	          			// Sexo
	pEdad,                  			// Edad
	pCiudad,                			// Ciudad
	pPeso, 								// Peso
	pEstiloPelea,                   	// Estilo de pelea
	pDinero,                			// Dinero en bolsillos
	pBanco,                 			// Dinero en banco
	pLider,								// Lider de facción
	pMiembro,							// Miembro de facción
	pRango,                 			// Rango de facción
	pBolsillo[9],						// Bolsillos
	pBolsilloCant[9],					// Cantidad en bolsillos
	pManoDerecha,						// Mano derecha
	pManoDerechaCant,					// Cantidad en mano derecha
	pManoIzquierda,						// Mano izquierda
	pManoIzquierdaCant,					// Cantidad en mano izquierda
	pEspalda,							// Espalda
	pEspaldaCant,						// Cantidad en espalda
	pMuerto,                			// Estado muerto
	pJails,                 			// Cantidad de jails ooc
	pArrestos,              			// Cantidad de jails ic
	pSancionado,						// Si está en jail
	pTiempoSancion,						// Tiempo Jail
	pBySancion[MAX_PLAYER_NAME],		// Jaileado por
	pRazonSancion[128],					// Razón del jail
	pTelefono,                      	// Número de teléfono
	pTogVelocimetro,                   	// Activo velocimetro
	pLicencia[5],						// Licencias: 0(conducir) 1(vuelo) 2(bote) 3(armas) 4(taxi)
	pBaneo,                         	// Baneado: 0(desbloqueado) 1(temporal) 2(permanente)
	pTiempoBaneo,
	pCulpableBaneo[MAX_PLAYER_NAME],
	pRazonBaneo[256],
	pFechaBaneo[256],
	pBlockBug,                      	// Bloqueo de /reportarbug
	pTogGraffiti,						// Bloqueo de graffitis
	pDocumento,                     	// Documento nacional
	pHabilidad[6],                  	// Habilidades: 0(granjero) 1(repartidor) 2(aserrador) 3(basurero) 4(-)
	pPayday,                        	// Tiempo PayDay
	pEstrellas,                     	// Estrellas
	pLimiteRobos,                   	// Limite de robar piezas
	pFrecuencia_radio,              	// Frecuencia de radio portatil
	pSpawnTipo,                     	// Tipo spawn: 0(hospital) 1(casa)
	pEstadoYo[128],						// Estado /yo
	Text3D: pNameTag,					// Estado label (27/04/2020)
	pNumeroContacto[20],            	// Número de contacto
	pJobSkin,                       	// Skin normal
	pRestriccionRobo,               	// Restricción robo
	pFechaRegistro[256],                // Fecha de registro
	pUltimaConexion[256],               // Última conexión
    ptModelo[10],                       // toys
	ptHueso[10],
    Float: ptPosX[10],
	Float: ptPosY[10],
	Float: ptPosZ[10],
	Float: ptRotX[10],
	Float: ptRotY[10],
	Float: ptRotZ[10],
	Float: ptScaleX[10],
	Float: ptScaleY[10],
	Float: ptScaleZ[10],
	ptColocado[10],
	pCinturon[6],						// Cinturon
	pCinturonCant[6],					// Cantidad en cinturon
	ptColor[10],                        // color toys
	pTrabajo1,                          // trabajo 1
	pTrabajo2,                          // trabajo 2
	pTrabajo3,                          // trabajo 3 (vip)
	pTogManos,                          // 1 puede mover | 0 no mueve
	pTogCajero,							// Restricción de retirar del cajero
	pTogAnuncios,                       // 0 visibles | ocultos
	pTogTelefono,                       // 1 encendido | 0 apagado
	pTimerAnuncios,                     // tiempo de anuncios
	pTogOOC,                            // Mensajes administrativos
	pTogMusic,                          // Musíca
	pTogRadio,                          // Radio o wsp
	pTogPortatil,                       // Radio portatil
	pTogFaccion,                        // Mensajes de facciones
	pEstiloManos,                       // estilo manos
	pTiempoMolotov,
	pAccesoGraffiti,
	pComprarNegocio,
	//no saved
	pViendoMenu,
	pServiceTime,
	pTriageTime,
	pModoAfk,
	pEditingMode,
	Checkpoint,
	pEstado,							// Estado de muerte
};
new InfoPersonaje[MAX_PLAYERS][personajeInfo];

forward CreatePlayerCharacter(playerid);
public CreatePlayerCharacter(playerid)
{
	InfoPersonaje[playerid][pID] = cache_insert_id();
	cache_unset_active();
	InfoPersonaje[playerid][pDocumento] = 2000000+InfoPersonaje[playerid][pID];
	InfoPersonaje[playerid][pTelefono] = 500000+InfoPersonaje[playerid][pID];
	new query[512];
	mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Telefono = '%d', Documento = '%d', Mano_izquierda = 50, Cantidad_mano_izquierda = 1 WHERE ID = '%d'", InfoPersonaje[playerid][pTelefono], InfoPersonaje[playerid][pDocumento], InfoPersonaje[playerid][pID]);
	mysql_tquery(db_samp, query);
	InfoPersonaje[playerid][pManoIzquierda] = 50;
	InfoPersonaje[playerid][pManoIzquierdaCant] = 1;
	PonerObjeto(playerid, 2, 50);
	return 1;
}

reset_InfoPersonaje(playerid)
{
	TiempoTecla[playerid] = 0;
	InfoPersonaje[playerid][pModoAfk] = 0;
	InfoPersonaje[playerid][pEstado] = -1;
	InfoPersonaje[playerid][pID] = -1;
	InfoPersonaje[playerid][pCuentaID] = -1;
	alm(InfoPersonaje[playerid][pNombre_Apellido], "");
	alm(InfoPersonaje[playerid][pCodigo], "");
	InfoPersonaje[playerid][pPosicionX] = 0.0;
	InfoPersonaje[playerid][pPosicionY] = 0.0;
	InfoPersonaje[playerid][pPosicionZ] = 0.0;
	InfoPersonaje[playerid][pPosicionR] = 0.0;
	InfoPersonaje[playerid][pInterior] = 0;
	InfoPersonaje[playerid][pVirtualWorld] = 0;
	InfoPersonaje[playerid][pVida] = 100.0;
	InfoPersonaje[playerid][pChaleco] = 0.0;
	InfoPersonaje[playerid][pSkin] = 289;
	InfoPersonaje[playerid][pHorasOn] = -1;
	InfoPersonaje[playerid][pSexo] = 1;
	InfoPersonaje[playerid][pEdad] = 16;
	InfoPersonaje[playerid][pCiudad] = 1;
	InfoPersonaje[playerid][pEstiloPelea] = 4;
	InfoPersonaje[playerid][pDinero] = 0;
	InfoPersonaje[playerid][pBanco] = 0;
	InfoPersonaje[playerid][pLider] = 0;
	InfoPersonaje[playerid][pMiembro] = 0;
	InfoPersonaje[playerid][pRango] = 0;
	Loop(x, 9, 0)
	{
		InfoPersonaje[playerid][pBolsillo][x] = 0;
		InfoPersonaje[playerid][pBolsilloCant][x] = 0;
	}
	Loop(x, 10, 0)
	{
        InfoPersonaje[playerid][ptModelo][x] = 0;
        InfoPersonaje[playerid][ptHueso][x] = 0;
        InfoPersonaje[playerid][ptPosX][x] = 0.0;
        InfoPersonaje[playerid][ptPosY][x] = 0.0;
        InfoPersonaje[playerid][ptPosZ][x] = 0.0;
        InfoPersonaje[playerid][ptRotX][x] = 0.0;
        InfoPersonaje[playerid][ptRotY][x] = 0.0;
        InfoPersonaje[playerid][ptRotZ][x] = 0.0;
        InfoPersonaje[playerid][ptScaleX][x] = 1;
        InfoPersonaje[playerid][ptScaleY][x] = 1;
        InfoPersonaje[playerid][ptScaleZ][x] = 1;
        InfoPersonaje[playerid][ptColocado][x] = 0;
        InfoPersonaje[playerid][ptColor][x] = -1;
	}
	InfoPersonaje[playerid][pManoDerecha] = 0;
	InfoPersonaje[playerid][pManoDerechaCant] = 0;
	InfoPersonaje[playerid][pManoIzquierda] = 0;
	InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
	InfoPersonaje[playerid][pEspalda] = 0;
	InfoPersonaje[playerid][pEspaldaCant] = 0;
	InfoPersonaje[playerid][pMuerto] = 0;
	InfoPersonaje[playerid][pJails] = 0;
	InfoPersonaje[playerid][pArrestos] = 0;
	InfoPersonaje[playerid][pSancionado] = 0;
	InfoPersonaje[playerid][pTiempoSancion] = 0;
	alm(InfoPersonaje[playerid][pBySancion], "none");
	alm(InfoPersonaje[playerid][pRazonSancion], "none");
	InfoPersonaje[playerid][pTelefono] = 0;
	InfoPersonaje[playerid][pTogVelocimetro] = 1;
	Loop(x, 5, 0) { InfoPersonaje[playerid][pLicencia][x] = 0; }
	InfoPersonaje[playerid][pBaneo] = 0;
	InfoPersonaje[playerid][pTiempoBaneo] = 0;
	alm(InfoPersonaje[playerid][pCulpableBaneo], "server");
	alm(InfoPersonaje[playerid][pRazonBaneo], "abuso");
	alm(InfoPersonaje[playerid][pFechaBaneo], "antes del 07 de mayo del 2020");
	InfoPersonaje[playerid][pBlockBug] = 0;
	InfoPersonaje[playerid][pTogGraffiti] = 0;
	InfoPersonaje[playerid][pDocumento] = 0;
	Loop(x, 5, 0) { InfoPersonaje[playerid][pHabilidad][x] = 0; }
	InfoPersonaje[playerid][pPayday] = 30;
	InfoPersonaje[playerid][pEstrellas] = 0;
	InfoPersonaje[playerid][pLimiteRobos] = 0;
	InfoPersonaje[playerid][pFrecuencia_radio] = 0;
	InfoPersonaje[playerid][pSpawnTipo] = 0;
	alm(InfoPersonaje[playerid][pEstadoYo], "");
	Loop(x, 20, 0)
	{
		alm(nombre_contacto[playerid][x], "none");
		InfoPersonaje[playerid][pNumeroContacto][x] = 0;
	}
	InfoPersonaje[playerid][pJobSkin] = 0;
	InfoPersonaje[playerid][pRestriccionRobo] = 0;
	alm(InfoPersonaje[playerid][pFechaRegistro], "none");
	alm(InfoPersonaje[playerid][pUltimaConexion], "none");
	Loop(x, 6, 0)
	{
		InfoPersonaje[playerid][pCinturon][x] = 0;
		InfoPersonaje[playerid][pCinturonCant][x] = 0;
	}
	InfoPersonaje[playerid][pTrabajo1] = -1;
	InfoPersonaje[playerid][pTrabajo2] = -1;
	InfoPersonaje[playerid][pTrabajo3] = -1;
	InfoPersonaje[playerid][pTogTelefono] = 1;
	InfoPersonaje[playerid][pTogManos] = 1;
	InfoPersonaje[playerid][pTogCajero] = 0;
	InfoPersonaje[playerid][pTogAnuncios] = 0;
	InfoPersonaje[playerid][pTogTelefono] = 1;
	InfoPersonaje[playerid][pTimerAnuncios] = 0;
	InfoPersonaje[playerid][pTogOOC] = 1;
	InfoPersonaje[playerid][pTogMusic] = 1;
	InfoPersonaje[playerid][pTogRadio] = 1;
	InfoPersonaje[playerid][pTogPortatil] = 1;
	InfoPersonaje[playerid][pTogFaccion] = 1;
	InfoPersonaje[playerid][pEstiloManos] = 1;
	InfoPersonaje[playerid][pTiempoMolotov] = 0;
	InfoPersonaje[playerid][pAccesoGraffiti] = 0;
	InfoPersonaje[playerid][pComprarNegocio] = 0;
	InfoPersonaje[playerid][pViendoMenu] = 0;
}

MuestraBloqueoPJ(playerid)
{
	new string[1028];
	switch (InfoPersonaje[playerid][pBaneo])
	{
		case 1: //temporal
		{
			if (InfoPersonaje[playerid][pTiempoBaneo] < gettime())
			{
				SendPlayerChatMessage(playerid, COLOR_GREY, "El bloqueo de tu personaje ha terminado, ya puedes jugar.");
				InfoPersonaje[playerid][pTiempoBaneo] = 0;
				InfoPersonaje[playerid][pBaneo] = 0;
				new list[32];
				alm(list, "ninguno");
				mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET OtakuN_N = 0, TimeBanUwU = 0, FueBan = '%e', ReasonBanUwU = '%e', MomentBan = '%e' WHERE ID = '%d'", list, list, list, InfoPersonaje[playerid][pID]);
				mysql_tquery(db_samp, string);
				CargarCuenta(playerid);
			}
			else
			{
				format(string, sizeof string, "{FFFFFF}Personaje: {F5DEB3}%s\n\n{FFFFFF}Encargado: {FFBF00}%s\n{FFFFFF}Razón: {b42d2d}%s\n{FFFFFF}Fecha: {F5DEB3}%s\n{FFFFFF}Tiempo: {F5DEB3}%s\n",
				InfoPersonaje[playerid][pNombre_Apellido], InfoPersonaje[playerid][pCulpableBaneo], InfoPersonaje[playerid][pRazonBaneo], InfoPersonaje[playerid][pFechaBaneo], Segundos_tiempo(InfoPersonaje[playerid][pTiempoBaneo] - gettime()));
				Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Información del bloqueo temporal", string, "", "");
				SetTimerEx("TimerKICK", 1500, false, "d", playerid);
			}
		}
		case 2: //permanente
		{
			format(string, sizeof string, "{FFFFFF}Personaje: {F5DEB3}%s\n\n{FFFFFF}Encargado: {FFBF00}%s\n{FFFFFF}Razón: {b42d2d}%s\n{FFFFFF}Fecha: {F5DEB3}%s\n",
			InfoPersonaje[playerid][pNombre_Apellido], InfoPersonaje[playerid][pCulpableBaneo], InfoPersonaje[playerid][pRazonBaneo], InfoPersonaje[playerid][pFechaBaneo]);
			Dialog_Show(playerid, ShowInvalido, DIALOG_STYLE_MSGBOX, "Información del bloqueo", string, "", "");
			SetTimerEx("TimerKICK", 1500, false, "d", playerid);
		}
		default: //limpio
		{
			Kick(playerid);
		}
	}
	return 1;
}
