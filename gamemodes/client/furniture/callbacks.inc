forward OnCreateMueble(is_clon);
public OnCreateMueble(is_clon)
{
	totalmuebles++;
	new clon = totalmuebles;
	InfoMueble[clon][mID_sql] = cache_insert_id();
	cache_unset_active();
	if (is_clon)
	{
		new offquery[2048], onquery[5000];
		//primer
		format(offquery, sizeof offquery, "UPDATE muebles SET Tipo = '%d', Propiedad = '%d', Modelo = '%d', PotX = '%f', \
		PotY = '%f', PotZ = '%f', RotX = '%f', RotY = '%f', RotZ = '%f', Interior = '%d', VirtualWorld = '%d', Precio = '%d', Puerta = '%d',",
		InfoMueble[clon][mTipo], InfoMueble[clon][mPropiedad], InfoMueble[clon][mModelo], InfoMueble[clon][mPotX], InfoMueble[clon][mPotY], InfoMueble[clon][mPotZ],
		InfoMueble[clon][mRotX], InfoMueble[clon][mRotY], InfoMueble[clon][mRotZ], InfoMueble[clon][mInterior], InfoMueble[clon][mVirtualWorld], InfoMueble[clon][mPrecio], InfoMueble[clon][mPuerta]);

		//segundo
		format(offquery, sizeof offquery, "%s TxtMaterial1 = '%d', TxtModelo1 = '%d', TxtColor1 = '%d', TxtMaterial2 = '%d', TxtModelo2 = '%d', \
		TxtColor2 = '%d', TxtMaterial3 = '%d', TxtModelo3 = '%d', TxtColor3 = '%d', TxtMaterial4 = '%d', TxtModelo4 = '%d', TxtColor4 = '%d',",
		offquery, InfoMueble[clon][mTxtMaterial1], InfoMueble[clon][mTxtModelo1], InfoMueble[clon][mTxtColor1], InfoMueble[clon][mTxtMaterial2], InfoMueble[clon][mTxtModelo2],
		InfoMueble[clon][mTxtColor2], InfoMueble[clon][mTxtMaterial3], InfoMueble[clon][mTxtModelo3], InfoMueble[clon][mTxtColor3], InfoMueble[clon][mTxtMaterial4], InfoMueble[clon][mTxtModelo4], InfoMueble[clon][mTxtColor4]);

		//tercero
		mysql_format(db_samp, onquery, sizeof onquery, "%s TxtMaterial5 = '%d', TxtModelo5 = '%d', TxtNombre1 = '%e', TxtNombreTextura1 = '%e', TxtNombre2 = '%e', TxtNombreTextura2 = '%e', \
		TxtNombre3 = '%e', TxtNombreTextura3 = '%e', TxtNombre4 = '%e', TxtNombreTextura4 = '%e', TxtNombre5 = '%e', TxtNombreTextura5 = '%e', TxtColor5 = '%d', Nombre = '%e' WHERE ID = '%d'",
		offquery, InfoMueble[clon][mTxtMaterial5], InfoMueble[clon][mTxtModelo5], InfoMueble[clon][mTxtNombre1], InfoMueble[clon][mTxtNombreTextura1], InfoMueble[clon][mTxtNombre2], InfoMueble[clon][mTxtNombreTextura2],
		InfoMueble[clon][mTxtNombre3], InfoMueble[clon][mTxtNombreTextura3], InfoMueble[clon][mTxtNombre4], InfoMueble[clon][mTxtNombreTextura4], InfoMueble[clon][mTxtNombre5], InfoMueble[clon][mTxtNombreTextura5], InfoMueble[clon][mTxtColor5], InfoMueble[clon][mNombre], InfoMueble[clon][mID_sql]);
		mysql_tquery(db_samp, onquery);
	}
    return 1;
}

forward MueblesRemoveForPlayer(playerid);
public MueblesRemoveForPlayer(playerid)
{
	//Remove muebles default
	//clase baja
	RemoveBuildingForPlayer(playerid, 2251, 266.4531, 303.3672, 998.9844, 0.25);//int 1
	RemoveBuildingForPlayer(playerid, 14867, 270.2813, 302.5547, 999.6797, 0.25);
	RemoveBuildingForPlayer(playerid, 1720, 272.9063, 304.7891, 998.1641, 0.25);
	RemoveBuildingForPlayer(playerid, 14870, 273.1641, 303.1719, 1000.9141, 0.25);
	RemoveBuildingForPlayer(playerid, 2251, 273.9922, 303.3672, 998.9844, 0.25);
	RemoveBuildingForPlayer(playerid, 14868, 274.1328, 304.5078, 1001.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 948, 266.5703, 306.4453, 998.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 14866, 270.1172, 307.6094, 998.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 14869, 273.8125, 305.0156, 998.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 1535, 2218.8203, -1077.0156, 1049.4688, 0.25);//int 2
	RemoveBuildingForPlayer(playerid, 1567, 2216.6406, -1074.2578, 1049.4688, 0.25);
	RemoveBuildingForPlayer(playerid, 15035, 2205.9375, -1073.9922, 1049.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 1535, 2232.9297, -1115.6797, 1049.8672, 0.25);//int 3
	RemoveBuildingForPlayer(playerid, 1567, 2231.2969, -1111.4609, 1049.8594, 0.25);
	RemoveBuildingForPlayer(playerid, 15039, 2232.3438, -1106.7422, 1049.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 15038, 2235.2891, -1108.1328, 1051.2656, 0.25);
	//clase media-baja
	RemoveBuildingForPlayer(playerid, 1734, 2452.0313, -1702.0234, 1015.9688, 0.25);//int 1
	RemoveBuildingForPlayer(playerid, 14742, 2451.9063, -1701.1875, 1014.8594, 0.25);
	RemoveBuildingForPlayer(playerid, 14763, 2447.7500, -1694.2578, 1014.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 14741, 2447.4219, -1693.4531, 1012.4766, 0.25);
	RemoveBuildingForPlayer(playerid, 14740, 2447.0234, -1686.9922, 1014.8047, 0.25);
	RemoveBuildingForPlayer(playerid, 14761, 2449.9609, -1690.8438, 1014.0547, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 2457.0469, -1697.5391, 1012.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 2458.4531, -1696.8906, 1012.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 2241, 2459.3828, -1691.4766, 1013.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 14745, 2460.2422, -1695.1016, 1012.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 1498, 2469.2656, -1697.5234, 1012.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 293.6953, 1474.5859, 1079.2813, 0.25);//int 2
	RemoveBuildingForPlayer(playerid, 1498, 294.3672, 1471.8047, 1079.2422, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 297.2734, 1474.7500, 1079.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 2523, 284.5078, 1480.5156, 1079.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 288.1406, 1481.2422, 1079.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 2528, 284.4063, 1482.2813, 1079.2500, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 294.5703, 1482.8750, 1079.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 297.2891, 1481.5000, 1079.2813, 0.25);
	RemoveBuildingForPlayer(playerid, 2522, 284.4844, 1484.4219, 1079.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 2520, 287.1328, 1483.4297, 1079.2266, 0.25);
	//clase media
	RemoveBuildingForPlayer(playerid, 1741, 2261.6953, -1223.0781, 1048.0156, 0.25);//int 1
	RemoveBuildingForPlayer(playerid, 2088, 2258.1406, -1220.5859, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2090, 2258.5938, -1221.5469, 1048.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 2249, 2251.3594, -1218.1797, 1048.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 2528, 2254.4063, -1218.2734, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 2260.3672, -1218.9766, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1567, 2263.2266, -1217.5313, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2138, 2247.5547, -1213.9219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2138, 2247.5547, -1212.9375, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2250.3047, -1213.9375, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2526, 2252.4297, -1215.4531, 1048.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 2523, 2254.1953, -1215.4531, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2297, 2255.4219, -1213.5313, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2248, 2262.3906, -1215.5469, 1048.6094, 0.25);
	RemoveBuildingForPlayer(playerid, 1816, 2261.4141, -1213.4531, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2249, 2247.2969, -1212.1641, 1049.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 2249, 2247.2969, -1208.8594, 1049.6250, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2247.5625, -1211.9531, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2136, 2247.5469, -1210.9688, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2303, 2247.5469, -1208.9844, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2138, 2247.5547, -1207.9766, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2305, 2247.5547, -1206.9922, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2109, 2250.2813, -1212.2500, 1048.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2249.2344, -1211.4531, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2250.3047, -1210.8984, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2135, 2248.5234, -1206.9922, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2319, 2250.3438, -1206.9609, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1760, 2261.4609, -1212.0625, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2126, 2258.1094, -1210.3750, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 15044, 2255.0938, -1209.7813, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 2247, 2258.4766, -1209.7891, 1048.9922, 0.25);
	RemoveBuildingForPlayer(playerid, 2099, 2262.8047, -1208.4922, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2254, 2254.1172, -1206.5000, 1050.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 2240, 2254.6328, -1207.2734, 1048.5625, 0.25);
	RemoveBuildingForPlayer(playerid, 2252, 2256.2109, -1206.1016, 1048.8281, 0.25);
	RemoveBuildingForPlayer(playerid, 2235, 2256.2188, -1206.8594, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1760, 2257.6172, -1207.7266, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2235, 2261.4297, -1206.2031, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2252, 2262.1172, -1206.1016, 1048.8281, 0.25);
	RemoveBuildingForPlayer(playerid, 2241, 2194.5469, -1226.4844, 1048.5234, 0.25);//int 2
	RemoveBuildingForPlayer(playerid, 2526, 2191.8750, -1225.3594, 1048.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 2523, 2191.8750, -1223.5938, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2241, 2194.5469, -1221.7969, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2528, 2194.6953, -1223.1172, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2278, 2194.6406, -1221.5859, 1050.3203, 0.25);
	RemoveBuildingForPlayer(playerid, 2095, 2186.2109, -1219.1563, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2186.2500, -1220.3203, 1048.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2189.5000, -1220.3203, 1048.8750, 0.25);
	RemoveBuildingForPlayer(playerid, 2095, 2189.6250, -1219.1563, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1491, 2192.4453, -1220.8828, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2108, 2192.0547, -1219.5234, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2108, 2194.3359, -1219.5234, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2280, 2196.8828, -1219.9688, 1050.1641, 0.25);
	RemoveBuildingForPlayer(playerid, 2088, 2199.1875, -1219.0078, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1717, 2187.2422, -1215.6719, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2090, 2188.4453, -1217.1797, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2088, 2188.4688, -1213.0234, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1491, 2191.0547, -1215.8906, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2076, 2193.1953, -1214.6719, 1051.2422, 0.25);
	RemoveBuildingForPlayer(playerid, 1491, 2195.3984, -1215.8906, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2281, 2196.1484, -1214.6797, 1050.3125, 0.25);
	RemoveBuildingForPlayer(playerid, 2298, 2197.2734, -1216.6250, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2197.2500, -1212.8516, 1048.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 2259, 2198.5859, -1213.1484, 1050.2969, 0.25);
	RemoveBuildingForPlayer(playerid, 2828, 2198.5391, -1212.8359, 1048.8203, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2199.9375, -1212.8516, 1048.5469, 0.25);
	RemoveBuildingForPlayer(playerid, 2832, 2181.5000, -1206.5234, 1049.0625, 0.25);
	RemoveBuildingForPlayer(playerid, 2134, 2181.6250, -1207.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2132, 2181.6328, -1205.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2339, 2181.6250, -1206.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2131, 2184.6250, -1207.8594, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2183.5625, -1204.2344, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2115, 2184.6641, -1204.1719, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 2299, 2187.6250, -1212.1563, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2826, 2186.4531, -1210.5625, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2185.7109, -1209.4063, 1048.7734, 0.25);
	RemoveBuildingForPlayer(playerid, 2259, 2185.3984, -1209.9609, 1050.0859, 0.25);
	RemoveBuildingForPlayer(playerid, 2328, 2186.4375, -1210.1719, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2255, 2188.1563, -1209.1406, 1050.2422, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2185.8047, -1205.2656, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2281, 2187.8516, -1207.1250, 1050.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 2069, 2188.2109, -1207.5703, 1048.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 1491, 2191.0547, -1211.8906, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2328, 2189.4531, -1210.1719, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 1567, 2195.2734, -1209.8672, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2280, 2189.8984, -1207.8438, 1050.1172, 0.25);
	RemoveBuildingForPlayer(playerid, 2249, 2190.2188, -1209.3828, 1049.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 2108, 2192.0547, -1209.7109, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2108, 2194.3359, -1209.7109, 1048.0234, 0.25);
	RemoveBuildingForPlayer(playerid, 2826, 2190.5781, -1204.4297, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1702, 2191.5781, -1206.9375, 1048.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 2857, 2193.0938, -1204.2813, 1048.5078, 0.25);
	RemoveBuildingForPlayer(playerid, 1818, 2193.1250, -1205.1328, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 1702, 2196.1484, -1205.3828, 1048.0391, 0.25);
	RemoveBuildingForPlayer(playerid, 2260, 2196.7188, -1206.4922, 1050.1641, 0.25);
	RemoveBuildingForPlayer(playerid, 2831, 2181.5625, -1203.5000, 1049.0703, 0.25);
	RemoveBuildingForPlayer(playerid, 2134, 2181.6250, -1203.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2141, 2181.6250, -1201.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2339, 2181.6250, -1202.4219, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2831, 2184.6016, -1203.8906, 1048.8438, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2185.8047, -1202.6094, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2121, 2183.3281, -1202.3750, 1048.5234, 0.25);
	RemoveBuildingForPlayer(playerid, 2131, 2183.3750, -1200.8672, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 15043, 2189.1641, -1203.6484, 1048.0313, 0.25);
	RemoveBuildingForPlayer(playerid, 1717, 2190.5469, -1201.5625, 1048.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2244, 2188.0000, -1200.8516, 1048.2891, 0.25);
	RemoveBuildingForPlayer(playerid, 2255, 2188.2656, -1200.8438, 1050.1797, 0.25);
	RemoveBuildingForPlayer(playerid, 2126, 2192.4063, -1200.5234, 1048.0156, 0.25);
	RemoveBuildingForPlayer(playerid, 2811, 2192.8359, -1200.0391, 1048.5391, 0.25);
	RemoveBuildingForPlayer(playerid, 15040, 2193.2031, -1199.1094, 1050.1328, 0.25);
	RemoveBuildingForPlayer(playerid, 2100, 2195.2500, -1200.4844, 1048.0234, 0.25);
	//clase media-alta
	RemoveBuildingForPlayer(playerid, 14753, 74.9531, 1340.7969, 1089.9453, 0.25);//int 1
	RemoveBuildingForPlayer(playerid, 2259, 75.2734, 1337.7188, 1089.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2287, 77.3203, 1343.8281, 1089.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 2259, 81.5547, 1324.5547, 1084.9766, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 80.9844, 1337.5625, 1087.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 2522, 81.5625, 1345.9531, 1087.3516, 0.25);
	RemoveBuildingForPlayer(playerid, 2078, 83.5000, 1331.4688, 1082.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1734, 84.4766, 1324.4922, 1086.7969, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 82.2969, 1342.3750, 1087.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 2287, 85.2969, 1341.8203, 1089.4141, 0.25);
	RemoveBuildingForPlayer(playerid, 1735, 84.0469, 1341.1016, 1082.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 2523, 84.1094, 1345.9453, 1087.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 87.1328, 1335.5625, 1087.3594, 0.25);
	RemoveBuildingForPlayer(playerid, 2281, 89.5547, 1331.2734, 1084.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 89.8359, 1335.9063, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 89.8359, 1337.1250, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 90.9922, 1334.2031, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 2280, 92.5547, 1331.2734, 1084.8672, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 92.1563, 1335.9063, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 2117, 91.0078, 1336.4531, 1082.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 92.1641, 1337.0391, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 89.8359, 1338.2031, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 91.9141, 1338.1328, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 2117, 91.0078, 1338.4531, 1082.8516, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 91.0156, 1339.5469, 1083.7500, 0.25);
	RemoveBuildingForPlayer(playerid, 2285, 94.2188, 1341.4297, 1084.8828, 0.25);
	RemoveBuildingForPlayer(playerid, 2520, 88.3516, 1344.8984, 1087.3438, 0.25);
	RemoveBuildingForPlayer(playerid, 2528, 86.7031, 1345.9453, 1087.3516, 0.25);
    RemoveBuildingForPlayer(playerid, 2259, 2316.3125, -1024.5156, 1051.3203, 0.25);//int 2
	RemoveBuildingForPlayer(playerid, 2242, 2321.4609, -1019.7500, 1049.3672, 0.25);
	RemoveBuildingForPlayer(playerid, 2078, 2318.2578, -1017.6016, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 15063, 2321.6172, -1018.1016, 1053.1484, 0.25);
	RemoveBuildingForPlayer(playerid, 2203, 2312.1641, -1014.5547, 1050.4219, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2312.3750, -1014.5547, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 2830, 2312.1406, -1013.6719, 1050.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2312.3750, -1013.5625, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 2241, 2322.4453, -1026.4453, 1050.5000, 0.25);
	RemoveBuildingForPlayer(playerid, 2244, 2322.3594, -1019.8906, 1049.4844, 0.25);
	RemoveBuildingForPlayer(playerid, 2112, 2322.6563, -1026.4219, 1049.5938, 0.25);
	RemoveBuildingForPlayer(playerid, 2105, 2323.0156, -1026.8594, 1050.4453, 0.25);
	RemoveBuildingForPlayer(playerid, 2224, 2322.6953, -1019.0859, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2281, 2324.3125, -1017.7969, 1051.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 2261, 2322.4609, -1015.4297, 1051.1563, 0.25);
	RemoveBuildingForPlayer(playerid, 2165, 2323.3750, -1015.8984, 1053.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1714, 2323.7500, -1014.8594, 1053.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 2321.8906, -1013.5078, 1053.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 1755, 2325.2734, -1025.0625, 1049.1406, 0.25);
	RemoveBuildingForPlayer(playerid, 2229, 2325.6406, -1017.2813, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2107, 2326.0703, -1016.6719, 1050.6641, 0.25);
	RemoveBuildingForPlayer(playerid, 2088, 2325.5313, -1015.0938, 1053.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 15060, 2326.6641, -1022.1953, 1049.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 2280, 2327.3125, -1017.7969, 1051.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2104, 2327.1719, -1017.2109, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2088, 2327.4766, -1015.0938, 1053.6953, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2312.3750, -1012.5703, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 2303, 2312.3594, -1011.5859, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2313.8906, -1011.5781, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2314.9844, -1012.6797, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 2115, 2314.9922, -1011.4063, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2832, 2315.0547, -1011.2813, 1050.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 1567, 2315.7578, -1011.5156, 1053.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2315.9297, -1011.5859, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 2831, 2312.1875, -1010.6563, 1050.2656, 0.25);
	RemoveBuildingForPlayer(playerid, 2136, 2312.3594, -1010.6094, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2313.8906, -1010.5391, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2315.9297, -1010.5469, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2317.3438, -1009.5938, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2079, 2314.9844, -1009.2969, 1049.8359, 0.25);
	RemoveBuildingForPlayer(playerid, 1822, 2324.3359, -1012.2188, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2333, 2323.4922, -1009.7266, 1053.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2323.7891, -1009.5938, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2324.7813, -1009.5938, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2331, 2323.4453, -1009.2813, 1053.9531, 0.25);
	RemoveBuildingForPlayer(playerid, 2298, 2325.0625, -1010.7188, 1053.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2325.7813, -1009.5938, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 1822, 2326.6250, -1012.2188, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2326.7734, -1009.5938, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2138, 2312.3672, -1008.6094, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2138, 2314.3281, -1007.6328, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2305, 2312.3672, -1007.6250, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2135, 2313.3359, -1007.6250, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2317.3438, -1008.6016, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2139, 2317.3438, -1007.6094, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2287, 2320.0547, -1007.2500, 1055.7578, 0.25);
	RemoveBuildingForPlayer(playerid, 2194, 2322.3594, -1008.4453, 1054.9453, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2325.0391, -1006.9453, 1054.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 1502, 2317.0547, -1006.6953, 1053.7031, 0.25);
	RemoveBuildingForPlayer(playerid, 2528, 2321.2656, -1006.0313, 1053.7266, 0.25);
	RemoveBuildingForPlayer(playerid, 2249, 2323.0156, -1005.8828, 1054.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 2526, 2318.3750, -1003.0703, 1053.7422, 0.25);
	RemoveBuildingForPlayer(playerid, 2523, 2322.2500, -1003.0703, 1053.7188, 0.25);
	RemoveBuildingForPlayer(playerid, 1760, 2327.8047, -1021.0313, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 2295, 2328.7891, -1015.8281, 1049.1953, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 2328.8359, -1023.6016, 1050.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 2329.0469, -1022.6953, 1050.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 2229, 2329.0703, -1017.2813, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 2295, 2329.2578, -1015.8281, 1053.7891, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2327.7578, -1009.5938, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2106, 2327.7266, -1006.9453, 1054.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2329.1875, -1011.0078, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2329.1875, -1011.9922, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2291, 2329.1875, -1010.0234, 1049.2109, 0.25);
	RemoveBuildingForPlayer(playerid, 2285, 2328.9766, -1007.6406, 1051.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 2869, 2329.2891, -1025.8672, 1049.2266, 0.25);
	RemoveBuildingForPlayer(playerid, 2829, 2329.4688, -1023.6250, 1050.0078, 0.25);
	RemoveBuildingForPlayer(playerid, 2868, 2329.7656, -1023.0156, 1050.0000, 0.25);
	RemoveBuildingForPlayer(playerid, 2117, 2329.6953, -1022.5859, 1049.2031, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 2330.3672, -1023.5156, 1050.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 1739, 2330.3672, -1022.6875, 1050.1094, 0.25);
	RemoveBuildingForPlayer(playerid, 2243, 2329.2969, -1018.0313, 1049.3984, 0.25);
	RemoveBuildingForPlayer(playerid, 2096, 2330.2266, -1012.9688, 1053.7109, 0.25);
	RemoveBuildingForPlayer(playerid, 2240, 2330.7422, -1010.7813, 1054.2578, 0.25);
	RemoveBuildingForPlayer(playerid, 2096, 2330.2266, -1009.1875, 1053.7109, 0.25);
}
