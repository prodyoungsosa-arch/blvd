//mysql server samp
new MySQL: db_samp;

#if Conexion_MySQL == 1
    #define samp_host       "localhost"
    #define samp_user       "root"
    #define samp_password   ""
    #define samp_database   "gtafive"
#else
    #define samp_host       "gamma.optiklink.com"
    #define samp_user       "u314615_jznxvxRC6F"
    #define samp_password   "r48Okw1TQ^sFXBQU1@oJjJlt"
    #define samp_database   "s314615_asssdd"
#endif

#define rebel_int			cache_get_value_int
#define rebel_float			cache_get_value_float
#define rebel_string		cache_get_value_name

guardar_int_mysql(tabla[], columna[], id, monto)
{
	new query[210];
	mysql_format(db_samp, query, sizeof query, "UPDATE %s SET %s = '%d' WHERE ID = '%d'", tabla, columna, monto, id);
	mysql_tquery(db_samp, query);
	return 1;
}

guardar_float_mysql(tabla[], columna[], id, Float: monto)
{
	new query[210];
	mysql_format(db_samp, query, sizeof query, "UPDATE %s SET %s = '%f' WHERE ID = '%d'", tabla, columna, monto, id);
	mysql_tquery(db_samp, query);
	return 1;
}

guardar_string_mysql(tabla[], columna[], id, monto[])
{
	new query[740];
	mysql_format(db_samp, query, sizeof query, "UPDATE %s SET %s = '%e' WHERE ID = '%d'", tabla, columna, monto, id);
	mysql_tquery(db_samp, query);
	return 1;
}

ConexionMySQL()
{
	//mysql server samp
	db_samp = mysql_connect(samp_host, samp_user, samp_password, samp_database);
	if (mysql_errno(db_samp) != 0)
	{
		print("===================== Server Boot Sequence ====================");
		print(" ");
		print("Servidor: "SERVER_NAME"");
		print("Versión: "SERVER_VERSION"");
		print("Lenguaje: Español | Spanish");		
    	print("Base de datos: error al conectar con la base de datos.");
		print(" ");
		print("===============================================================");
		SendRconCommand("exit");
    	return 1;
	}
	else
	{
		print("===================== Server Boot Sequence ====================");
		print(" ");
		print("Servidor: "SERVER_NAME"");
		print("Version: "SERVER_VERSION"");
		print("Lenguaje: Español | Spanish");
    	print("Base de datos: conexión con la base de datos establecida.");
		print(" ");
		print("===============================================================");		
	}
	return 1;
}