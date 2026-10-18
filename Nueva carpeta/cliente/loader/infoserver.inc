LoadServerInfo()
{
	mysql_tquery(db_samp, "SELECT * FROM `vehiculos` ORDER BY `ID` ASC", "CargarVehiculos");
	mysql_tquery(db_samp, "SELECT * FROM `casas` ORDER BY `ID` ASC", "CargarCasas");
	mysql_tquery(db_samp, "SELECT * FROM `negocios` ORDER BY `ID` ASC", "CargarNegocios");
	mysql_tquery(db_samp, "SELECT * FROM `puertas` ORDER BY `ID` ASC", "CargarPuertas");
	mysql_tquery(db_samp, "SELECT * FROM `facciones` ORDER BY `ID` ASC", "CargarFacciones");				// (15/02/2020)
	mysql_tquery(db_samp, "SELECT * FROM `actores` ORDER BY `ID` ASC", "CargarActores");					// (02/03/2020)
	mysql_tquery(db_samp, "SELECT * FROM `objetos_admin` ORDER BY `ID` ASC", "CargarObjetosAdmin");			// (06/03/2020)
	mysql_tquery(db_samp, "SELECT * FROM `cajeros` ORDER BY `ID` ASC", "CargarCajeros");					// (14/03/2020)
	mysql_tquery(db_samp, "SELECT * FROM `graffitis` ORDER BY `ID` ASC", "CargarGraffitis");				// (20/04/2020)
	mysql_tquery(db_samp, "SELECT * FROM `bidones` ORDER BY `ID` ASC", "CargarBidones");					// (02/06/2020)
	mysql_tquery(db_samp, "SELECT * FROM `muebles` ORDER BY `ID` ASC"	, "CargarMuebles");              	// (10/06/2020)
	mysql_tquery(db_samp, "SELECT * FROM `cajas` ORDER BY `ID` ASC", "CargarCajas");						// (10/06/2020)
	mysql_tquery(db_samp, "SELECT * FROM `incendios` ORDER BY `ID` ASC", "CargarIncendios");				// (21/07/2020)
	mysql_tquery(db_samp, "SELECT * FROM `plantas` ORDER BY `ID` ASC", "CargarPlantas");
	mysql_tquery(db_samp, "SELECT * FROM `mochilas` ORDER BY `ID` ASC", "CargarMochilas");                  // (20/03/2022)
	mysql_tquery(db_samp, "SELECT * FROM `ubicaciones` ORDER BY `ID` ASC", "CargarUbicaciones");			// (6/04/2020)
	mysql_tquery(db_samp, "SELECT * FROM `contenedores` ORDER BY `ID` ASC", "CargarContenedores");			// (6/04/2020)

	alm(AnunceString1, "none");
	alm(AnunceString2, "none");
	alm(AnunceString3, "none");
	alm(AnunceString4, "none");
	
	ClearReports();
	
	RoadblockList = LoadModelSelectionMenu("RoadblockList.txt");
	SignList = LoadModelSelectionMenu("SignList.txt");
	ob_muebles = LoadModelSelectionMenu("ob_muebles.txt");

	Loop(v, MAX_VEHICLES, 0) { veh_gasolina[v] = 200; }
	Loop(i, MAX_OBJETOS_S, 0) { InfoSuelo[i][DropLabel] = CreateDynamic3DTextLabel("dropid", -1, -1178.1569, 58.9069, 1.9609, 1.0, .worldid = 1+777, .interiorid = i); }
	return 1;
}