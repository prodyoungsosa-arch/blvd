// ==========================================
// FUNCIONES DE OBJETOS (PONER, TIRAR, ETC)
// ==========================================

PonerObjeto(playerid, lugar, objetoid)
{
	new modelo = InfoInventario[objetoid][ModeloObjeto];
	switch (lugar)
	{
		case 1: //mano derecha
		{
			switch (objetoid)
			{
				case 1..40: SetPlayerAttachedObject(playerid, 7, modelo, 6); //weapons
				case 41: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.059000, 0.041000, 0.012999, 0.199999, -21.399997, 0.099999, 0.389000, 0.939000, 0.409999); //encendedor
				case 42: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.057000, 0.035999, 0.003999, -105.099983, -2.200000, -171.699981, 1.000000, 1.000000, 1.000000); //paquete de cigarros
				case 43..46: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.073000, 0.073000, 0.015999, -9.699999, 0.600041, -0.299999, 1.000000, 1.000000, 1.000000); //marihuana, crack, metanfetamina, cocaína
				case 47: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.098000, 0.034000, 0.037999, 111.599998, 19.299999, 8.299999, 1.000000, 1.000000, 1.000000); //canuto de marihuana
				case 48: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.045999, 0.111999, 0.032000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //blunt de marihuana
				case 49: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.121999, -0.004000, 0.004999, 9.599995, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //cigarro
				case 50: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.093999, 0.012000, -0.010999, -81.199974, 10.000000, 179.099945, 0.990999, 0.829000, 0.903000); //teléfono s10
				case 51: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.388999, 0.034000, 0.101999, 0.000000, -100.599998, 0.399999, 1.000000, 1.000000, 1.000000); //boombox
				case 52: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.048000, -0.001999, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //dinamita
				case 53: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.178000, 0.019999, 0.031998, 0.000000, -101.600021, 0.000000, 0.630999, 0.452998, 0.611998); //botiquin
				case 54: SetPlayerAttachedObject(playerid, 7, modelo, 6); //escopetita
				case 55: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.152999, 0.106998, 0.034999, -85.699996, 179.999969, 78.399993, 1.038999, 0.752000, 0.854999); //caja especial
				case 56..60: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.083999, 0.039000, -0.003999, 0.799998, -5.099998, -92.599990, 1.000000, 1.000000, 1.000000); //cargador pequeño
				case 61..64: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.064999, 0.035998, 0.018999, 1.599980, -105.499984, 1.800009, 0.649999, 0.910999, 0.476999); //cargador grande
				case 65: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.042000, 0.055999, -0.085000, 10.800001, 1.100013, 0.000000, 1.000000, 1.000000, 1.000000); //cerveza
				case 66: SetPlayerAttachedObject(playerid, 7, modelo, 6); //chaleco
				case 67: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.359000, 0.000000, 0.051000, 0.000000, -104.400009, -2.099995, 0.898000, 0.936000, 1.000000); //sixpack de cerveza
				case 68..83: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.073000, 0.073000, 0.015999, -9.699999, 0.600041, -0.299999, 1.000000, 1.000000, 1.000000); // drugs
				case 86: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.585001, 0.051998, 0.042997, 2.899997, 176.400024, 0.000000, 1.000000, 1.000000); // mochila
				case 87..91: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.069998, 0.057998, -0.008000, 0.000000, 0.000000, 0.000000, 1.116000, 1.000000, 1.254999); // Pescado
				case 92: SetPlayerAttachedObject(playerid, 7, modelo, 5, 0.049000, 0.042999, -0.027000, 17.399976, -34.500000, 175.000015, 1.000000, 1.000000, 1.000000); //Caña
			}
		}
		case 2: //mano izquierda
		{
			switch (objetoid)
			{
				case 1: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.024999, 0.000000, -0.005999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //nudillera
				case 2: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.040000, 0.067000, -0.003000, -29.899999, 152.000000, 176.000030, 1.000000, 1.000000, 1.000000); //palo de golf
				case 3: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.115999, 0.113999, 0.087999, 0.000000, 44.500000, 0.000000, 1.000000, 1.000000, 1.000000); //porra
				case 4: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.007000, 0.060999, -0.013000, 156.600051, 9.100000, -14.800011, 1.000000, 1.000000, 1.000000); //cuchillo
				case 5: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.135999, 0.030999, 0.053999, -17.900001, 153.800018, 0.000000, 1.000000, 1.000000, 1.000000); //bate
				case 6: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.041999, 0.051999, -0.080000, -27.899986, 155.800018, -167.499938, 1.000000, 1.000000, 1.000000); //pala
				case 7: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.156999, 0.092000, 0.071999, -25.099998, 172.899963, -19.899995, 1.000000, 1.000000, 1.000000); //palo de billar
				case 8: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.058000, 0.008000, -0.109000, -27.999998, 155.100036, 172.699966, 1.000000, 1.000000, 1.000000); //sable
				case 9: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.000000, 0.078999, -0.009000, 155.599990, 7.200000, 4.800000, 1.000000, 1.000000, 1.000000); //motosierra
				case 10: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.015000, 0.041000, -0.068000, -25.599971, 162.900054, -175.300018, 1.000000, 1.000000, 1.000000); //consolador 1
				case 11: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.023999, 0.052999, -0.041999, 157.899978, 2.499999, 0.000000, 1.000000, 1.000000, 1.000000); //consolador 2
				case 12: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.002000, 0.074000, 0.001000, 151.200042, 23.000000, -9.100001, 1.000000, 1.000000, 1.000000); //consolador 3
				case 13: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.017999, 0.003999, -0.047999, 168.200012, 18.300003, -27.900005, 1.000000, 1.000000, 1.000000); //consolador 4
				case 14: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.176000, 0.000000, -0.011000, -23.399999, 160.599990, -6.399995, 1.000000, 1.000000, 1.000000); //flores
				case 15: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.008999, -0.018999, -0.047999, -33.199996, 159.900085, 156.399902, 1.000000, 1.000000, 1.000000); //bastón
				case 16: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.019000, 0.047000, -0.021000, 164.499984, 0.000000, -17.599994, 1.000000, 1.000000, 1.000000); //granada
				case 17: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.034000, 0.063000, -0.037999, 164.500000, 14.599996, -4.700009, 1.000000, 1.000000, 1.000000); //granada de gas
				case 18: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.022999, 0.039000, -0.125999, 165.700012, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //molotov
				case 19: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.033000, 0.057999, -0.017999, 146.299987, 14.999998, -4.700002, 1.000000, 1.000000, 1.000000); //9mm + silenciador
				case 20: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.050999, 0.038000, -0.021999, 144.500015, 9.100000, -11.600002, 1.000000, 1.000000, 1.000000); //9mm
				case 21: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.041000, 0.038000, -0.026999, 173.899963, 0.000000, 1.799999, 1.000000, 1.000000, 1.000000); //desert eagle
				case 22: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.000000, 0.089000, 0.000000, 153.500015, 10.000001, 4.800000, 1.000000, 1.000000, 1.000000); //escopeta
				case 23: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.040000, 0.026000, 0.011000, -156.300003, 0.000000, 2.600000, 1.000000, 1.000000, 1.000000); //recortada
				case 24: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.023000, 0.048999, -0.013000, 172.200012, 14.400005, 0.599999, 1.000000, 1.000000, 1.000000); //escopeta combate
				case 25: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.024999, 0.048000, -0.012000, 172.000076, -3.099988, -2.099991, 1.000000, 1.000000, 1.000000); //UZI
				case 26: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.005000, 0.065000, -0.016000, 162.399963, 9.599999, 8.400000, 1.000000, 1.000000, 1.000000); //MP5K
				case 27: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.057999, 0.076999, -0.023999, 162.799942, 14.399999, 0.000000, 1.000000, 1.000000, 1.000000); //AK47
				case 28: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.043999, 0.028999, -0.038000, 167.499969, 15.999998, 0.000000, 1.000000, 1.000000, 1.000000); //M4
				case 29: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.048000, 0.049999, 0.011000, -172.600006, -2.299995, 5.999999, 1.000000, 1.000000, 1.000000); //tec9
				case 30: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.043000, 0.065999, -0.044999, 167.499954, 17.399999, 0.000000, 1.000000, 1.000000, 1.000000); //rifle de caza
				case 31: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.018000, 0.085000, 0.033000, 167.399978, 12.200000, -0.299997, 1.000000, 1.000000, 1.000000); //rifle de francotirador
				case 32: SetPlayerAttachedObject(playerid, 8, modelo, 5, -0.019999, 0.053999, -0.042000, -33.100013, -174.800018, 171.199890, 0.757999, 0.782000, 0.979999); //cohete
				case 33: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.171999, 0.079999, -0.111999, -124.399993, 166.300018, -93.599990, 1.038999, 0.752000, 0.854999); //RPG
				case 34: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.044999, 0.083999, 0.034999, 47.699974, -79.599967, -89.300102, 0.654999, 0.782000, 0.758000); //lanzallamas
				case 35: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.023000, 0.048999, -0.013000, 172.200012, 14.400005, 0.599999, 1.000000, 1.000000, 1.000000); //minigun
				case 36: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.036999, 0.026999, -0.079999, 152.899993, 14.900004, -0.400000, 1.000000, 1.000000, 1.000000); //spray
				case 37: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.004000, 0.061999, -0.063999, 126.599990, 33.099998, 2.200000, 1.000000, 1.000000, 1.000000); //extintor
				case 38: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.018000, 0.062999, 0.074999, -109.400039, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //cámara fotográfica
				case 39: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.018000, 0.062999, 0.074999, -109.400039, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //paracaidas
				case 40: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.050999, 0.038000, -0.021999, 144.500015, 9.100000, -11.600002, 1.000000, 1.000000, 1.000000); //táser
				case 41: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.084000, 0.026000, -0.014000, 156.000076, -21.299989, -1.399998, 0.389000, 0.939000, 0.409999); //encendedor
				case 42: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.086000, 0.043999, -0.010000, -89.599967, -2.199996, 1.099998, 1.000000, 1.000000, 1.000000); //paquete de cigarros
				case 43..46: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.094000, 0.065000, -0.026000, 0.000000, -177.499969, 0.000000, 1.000000, 1.000000, 1.000000); //marihuana,crack, metanfetamina, cocaína
				case 47: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.116999, 0.034000, -0.037000, 111.599998, 19.299999, 8.299999, 1.000000, 1.000000, 1.000000); //canuto de marihuana
				case 48: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.036000, 0.074000, 0.000000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //blunt de marihuana
				case 49: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.130000, 0.013999, 0.007999, 9.599995, 6.699999, 29.500005, 1.000000, 1.000000, 1.000000); //cigarro
				case 50: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.056000, 0.000000, 0.007000, -97.100006, 0.000000, 0.000000, 0.990999, 0.829000, 0.903000); //teléfono s10
				case 51: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.423000, 0.000000, 0.019999, 6.100001, -101.499984, 36.800006, 1.000000, 1.000000, 1.000000); //boombox
				case 52: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.050999, 0.072000, 0.000000, -34.699996, -21.000000, 1.699999, 1.000000, 1.000000, 1.000000); //dinamita
				case 53: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.193000, 0.029000, -0.001001, 0.000000, -101.600021, 12.900000, 0.630999, 0.452998, 0.611998); //botiquin
				case 54: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.000000, 0.089000, 0.000000, 153.500015, 10.000001, 4.800000, 1.000000, 1.000000, 1.000000); //escopetita
				case 55: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.171999, 0.079999, -0.111999, -124.399993, 166.300018, -93.599990, 1.038999, 0.752000, 0.854999); //caja especial
				case 56..60: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.088999, 0.023000, 0.006000, -9.600001, 178.099945, 92.899978, 1.000000, 1.000000, 1.000000); //cargador pequeño
				case 61..64: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.092000, 0.038000, -0.026000, -37.200008, 82.199996, 3.499996, 0.649999, 0.910999, 0.476999); //cargador grande
				case 65: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.092000, 0.114000, 0.069000, -37.200008, -173.000015, 3.499995, 1.000000, 1.000000, 1.000000); //cerveza
				case 66: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.023000, 0.048999, -0.013000, 172.200012, 14.400005, 0.599999, 1.000000, 1.000000, 1.000000); //chaleco
				case 67: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.366999, 0.000000, 0.000000, -171.600021, -88.899925, -166.500076, 0.898000, 0.936000, 1.000000); //sixpack de cerveza
				case 68..83: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.094000, 0.065000, -0.026000, 0.000000, -177.499969, 0.000000, 1.000000, 1.000000, 1.000000); //marihuana,crack, metanfetamina, cocaína
				case 86: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.562000, 0.197997, 0.003997, 2.899996, 176.400024, -19.299999, 1.000000, 1.000000); //mochila
				case 87..91: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.024999, 0.000000, -0.005999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //nudillera
				case 92: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.023999, 0.052999, -0.041999, 157.899978, 2.499999, 0.000000, 1.000000, 1.000000, 1.000000);
			}
		}
		case 3: //espalda
		{
		    new toy = 7;
			if (InfoPersonaje[playerid][ptPosX][toy] != 0.0)
			{
				if (InfoPersonaje[playerid][ptHueso][toy] == 0) InfoPersonaje[playerid][ptHueso][toy] = 1;
				if (InfoPersonaje[playerid][pEspalda] == 86) SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.129999, -0.067001, -0.011002, 0.000000, -2.699996, 0.000000, 1.000000, 1.000000, 1.000000); //mochila
				else SetPlayerAttachedObject(playerid, 9, modelo, InfoPersonaje[playerid][ptHueso][toy], InfoPersonaje[playerid][ptPosX][toy], InfoPersonaje[playerid][ptPosY][toy], InfoPersonaje[playerid][ptPosZ][toy],
				InfoPersonaje[playerid][ptRotX][toy], InfoPersonaje[playerid][ptRotY][toy], InfoPersonaje[playerid][ptRotZ][toy], 1.000000, 1.000000, 1.000000);
			}
			else
			{
				switch (objetoid)
				{
					case 2,3: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 5,6,7,8: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 9: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.2349, -0.1289, 0.0000, -166.7000, 0.0000, 0.0000, 1.000000, 1.000000, 1.000000);
					case 10: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 11: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 12: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 13: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 14: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 15: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.1061, -0.1544, -0.0411, 0.0000, 60.0000, 60.0000, 1.000000, 1.000000, 1.000000);
					case 22: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.220000, -0.135998, 0.113000, -1.900013, 161.699951, 8.599991, 1.000000, 1.000000, 1.000000); //escopeta
					case 23: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.345999, -0.151998, 0.166000, -1.900013, 161.699951, 8.599991, 1.000000, 1.000000, 1.000000); //recortada
					case 24: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.345999, -0.151998, 0.166000, -1.900013, 161.699951, 8.599991, 1.000000, 1.000000, 1.000000); //escopeta combate
					case 26: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.205000, -0.136998, 0.156000, -1.500012, 152.599945, 5.399990, 1.000000, 1.000000, 1.000000); //MP5K
					case 27: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.251000, -0.130998, 0.135999, -1.500012, 152.599945, 5.399990, 1.000000, 1.000000, 1.000000); //AK47
					case 28: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.251000, -0.130998, 0.135999, -1.500012, 152.599945, 5.399990, 1.000000, 1.000000, 1.000000); //M4
					case 30: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.017999, -0.133999, 0.000000, 11.899997, 32.799995, 9.599994, 1.000000, 1.000000, 1.000000); //rifle de caza
					case 31: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.018000, -0.133999, 0.000000, 11.899998, 32.799995, 9.599995, 1.000000, 1.000000, 1.000000); //rifle de francotirador
					case 32: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.019999, -0.155000, 0.068000, 15.799981, 164.600006, -3.100142, 1.000000, 1.000000, 1.000000); //cohete
					case 33: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.195999, -0.142000, -0.129000, -1.799999, 18.200000, 0.000000, 1.000000, 1.000000, 1.000000); //RPG
					case 34: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.363999, -0.155000, 0.083000, 15.799981, 164.600006, -3.100142, 1.000000, 1.000000, 1.000000); //lanzallamas
					case 35: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.289000, -0.114999, -0.048000, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //minigun
					case 37: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.439999, -0.114999, 0.157000, -27.400011, 134.299942, -2.600011, 1.000000, 1.000000, 1.000000); //extintor
					case 39: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.087999, -0.114999, 0.000000, 11.899997, 86.899993, -18.700014, 1.000000, 1.000000, 1.000000); //paracaidas
					case 40: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.220000, -0.135998, 0.113000, -1.900013, 161.699951, 8.599991, 1.000000, 1.000000, 1.000000); //escopetita
					case 86: SetPlayerAttachedObject(playerid, 9, modelo, 1, -0.129999, -0.067001, -0.011002, 0.000000, -2.699996, 0.000000, 1.000000, 1.000000, 1.000000); //mochila
					default: SetPlayerAttachedObject(playerid, 9, modelo, 1, 0.000000, 0.231000, 0.000000, 10.899998, 0.000000, 175.900009, 1.000000, 1.000000, 1.000000);
				}
				InfoPersonaje[playerid][ptHueso][toy] = 1;
				EditAttachedObject(playerid, 9);
				EditandoObjetoJ[playerid] = 2;
				SendPlayerChatMessage(playerid, -1, "Manten presionado {3E62F4}~k~~PED_SPRINT~{FFFFFF} para cambiar la posición de la cámara.");
			}
		}
	}
	return 1;
}

funcion tirar_objeto(ObjetoID, Cantidad, Float: X, Float: Y, Float: Z, world, interior, bomxo)
{
	if (ObjetoID != 0)
	{
		new Float: rotx, Float: roty, Float: rotz;
		for (new i = 0; i < sizeof(InfoSuelo); i++)
		{
			if (InfoSuelo[i][DropPosX] == 0.0)
			{
				InfoSuelo[i][DropID] = ObjetoID;
				InfoSuelo[i][DropCantidad] = Cantidad;
				InfoSuelo[i][DropPosX] = X;
				InfoSuelo[i][DropPosY] = Y;
				InfoSuelo[i][DropPosZ] = Z;
				InfoSuelo[i][DropVWorld] = world;
				InfoSuelo[i][DropInterior] = interior;
				switch (ObjetoID)
				{
					case 1..5: { rotx = 85; roty = 1; rotz = 8; Z += 0; }
					case 6: { rotx = 8.5; roty = 90; rotz = -82; Z += 0.1; }
					case 7,8: { rotx = 85; roty = 1; rotz = 8; Z += 0; }
					case 9: { rotx = 95; roty = -69; rotz = 8; Z += 0.08; }
					case 10..13: { rotx = 90; roty = 1; rotz =  8; Z+= 0; }
					case 14: { rotx = 70; roty = 1; rotz =  8; Z+= 0; }
					case 15: { rotx = 87; roty = 1; rotz =  8; Z+= 0; }
					case 16: { rotx = 0; roty = -17; rotz = 0; Z += 0.05; }
					case 17: { rotx = 0; roty = 0.3; rotz = -7; Z += 0.06; }
					case 18: { rotx = -5.5; roty = -1.8; rotz = -7; Z += 0.2; }
					case 19: { rotx = -85; roty = 3; rotz = 3; Z += 0.04; }
					case 20: { rotx = -85; roty = 3; rotz = 3; Z += 0.05; }
					case 21: { rotx = -85; roty = 3; rotz = 3; Z += 0.04; }
					case 22: { rotx = -82; roty = 58; rotz = 64; Z += 0.06; }
					case 23: { rotx = -90; roty = 58; rotz =  64; Z += 0.05; }
					case 24: { rotx = -82; roty = 58; rotz =  64; Z += 0.05; }
					case 25,26: { rotx = -90; roty = 0; rotz = 0; Z += 0.04; }
					case 27,28: { rotx = -92.6; roty = 0.8; rotz = -3.1; Z += 0.06; }
					case 29: { rotx = -90; roty = 0; rotz = 0; Z += 0.05; }
					case 30: { rotx = -112; roty = -150; rotz = -159; Z += 0.04; }
					case 31: { rotx = -105; roty = -150; rotz = -159; Z += 0.04; }
					case 32,33,34: { rotx = -90; roty = 0; rotz = 0; Z += 0.07; }
					case 35: {  rotx = -4.4; roty = 27.5; rotz = 0; Z += 0.315; }
					case 36: {  rotx = 0.5; roty = -5.5; rotz = -4.7; Z += 0.15; }
					case 37: { rotx = -3.2; roty = 40.3; rotz = 0; Z += 0.59; }
					case 38: { rotx = 0; roty = -1.8; rotz = -30; Z += 0.02; }
					case 39: { rotx = 0; roty = 0; rotz = 9.7; Z += 0.19; }
					case 40: { rotx = -85; roty = 3; rotz = 3; Z += 0.05; }
					case 41: { rotx = 0; roty = 0; rotz = 0; Z += 0.1; }
					case 42: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; }
					case 43..46: { rotx = 0; roty = 0; rotz = 0; Z += 0.12; }
					case 47: { rotx = 0; roty = -90; rotz = 0; Z += 0.02; }
					case 48: { rotx = 0; roty = 0; rotz = 90; Z += 0.05; }
					case 49: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; }
					case 50: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; }
					case 51: { rotx = 0; roty = 0; rotz = 0; Z += 0; }
					case 52: { rotx = 0; roty = 0; rotz = 0; Z += 0.2; }
					case 53: { rotx = 0; roty = 0; rotz = 0; Z += 0.06; }
					case 54: { rotx = -82; roty = 58; rotz = 64; Z += 0.06; }
					case 55: { rotx = 0; roty = 0; rotz = 0; Z += 0.08; }
					case 56..60: { rotx = 0; roty = 90; rotz = 0; Z += 0.02; }
					case 61..64: { rotx = 0; roty = 0; rotz = 0; Z += 0.06; }
					case 65: { rotx = 0; roty = 0; rotz = 0; Z += 0.15; }
					case 66: { rotx = 0; roty = 0; rotz = 0; Z += 0.15; }
					case 67: { rotx = 0; roty = 0; rotz = 0; Z += 0; }
					case 86: { rotx = -89; roty = 0; rotz = 357; Z += 0; }
					default: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; }
				}
				if (IsValidDynamic3DTextLabel(InfoSuelo[i][DropLabel]))
				{
					DestroyDynamic3DTextLabel(InfoSuelo[i][DropLabel]);
					InfoSuelo[i][DropLabel] = Text3D:INVALID_3DTEXT_ID;
				}
				new info_obj[170];
				format(info_obj, sizeof info_obj, "{FFFFFF}%s\n{EBEBEB}Presiona {DAA838}[ALT] {EBEBEB}para recoger", InfoInventario[ObjetoID][NombreObjeto]);
				if (bomxo != 0)
				{
					InfoSuelo[i][DropLabel] = CreateDynamic3DTextLabel(info_obj, 0xEBEBEBFF, X, Y, Z, 3.0, .worldid = world, .interiorid = interior);
					ObjetoCaido[i] = CreateDynamicObject(InfoInventario[ObjetoID][ModeloObjeto], X, Y, Z, rotx, roty, rotz, world, interior);
				}
				else
				{
					InfoSuelo[i][DropLabel] = CreateDynamic3DTextLabel(info_obj, 0xEBEBEBFF, X, Y, Z-1, 3.0, .worldid = world, .interiorid = interior);
					ObjetoCaido[i] = CreateDynamicObject(InfoInventario[ObjetoID][ModeloObjeto], X, Y, Z-1, rotx, roty, rotz, world, interior);
				}
				ObjTimer[i] = SetTimerEx("SueloTime", 3600000*2, false, "i", i);
				return 1;
			}
		}
	}
	return 1;
}

funcion SueloTime(i)
{
	if (IsValidDynamicObject(ObjetoCaido[i])) DestroyDynamicObject(ObjetoCaido[i]);
	ObjetoCaido[i] = 0;
	if (IsValidDynamic3DTextLabel(InfoSuelo[i][DropLabel]))
	{
		DestroyDynamic3DTextLabel(InfoSuelo[i][DropLabel]);
		InfoSuelo[i][DropLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	InfoSuelo[i][DropLabel] = CreateDynamic3DTextLabel("dropid", -1, -1178.1569, 58.9069, 1.9609, 1.0, .worldid = 1+777, .interiorid = i);
	InfoSuelo[i][DropPosX] = 0.0;
	InfoSuelo[i][DropPosY] = 0.0;
	InfoSuelo[i][DropPosZ] = 0.0;
	InfoSuelo[i][DropID] = 0;
	InfoSuelo[i][DropCantidad] = 0;
	KillTimer(ObjTimer[i]);
	return 1;
}

// ==========================================
// NUEVO SISTEMA DE INVENTARIO CEF (REPARADO)
// ==========================================

new bool:QuiereAbrirInv[MAX_PLAYERS];

// Funciones auxiliares robustas para parsear JSON desde el navegador CEF
stock GetJsonInt(const json[], const key[], &val)
{
    new search[64];
    format(search, sizeof(search), "\"%s\":", key);
    new pos = strfind(json, search);
    if (pos == -1) return 0;
    pos += strlen(search);
    while (json[pos] == ' ' || json[pos] == '\t' || json[pos] == '\r' || json[pos] == '\n') pos++;
    val = strval(json[pos]);
    return 1;
}

stock GetJsonString(const json[], const key[], dest[], maxlen)
{
    dest[0] = EOS;
    new search[64];
    format(search, sizeof(search), "\"%s\":\"", key);
    new pos = strfind(json, search);
    if (pos == -1) return 0;
    pos += strlen(search);
    new c = 0;
    while (json[pos] != '"' && json[pos] != EOS && c < maxlen - 1)
    {
        dest[c++] = json[pos++];
    }
    dest[c] = EOS;
    return 1;
}

IsObjectWearable(objectid)
{
	switch (objectid)
	{
		case 2..15: return 1;
		case 19..40: return 1;
		case 54: return 1;
		case 86: return 1;
	}
	return 0;
}

forward OnInvJsReady(playerid, browserid);
forward OnInvJsClose(playerid, browserid);
forward OnInvJsUse(playerid, browserid, slot);
forward OnInvJsMove(playerid, browserid, from, to, amount);
forward OnInvJsDrop(playerid, browserid, slot, amount);
forward OnInvJsGive(playerid, browserid, slot, amount);

stock Inv_Min(a, b) return (a < b) ? a : b;

stock Inv_ValidSlot(slot) return (slot >= 0 && slot < INV_TOTAL_SLOTS);

stock Inv_ValidItem(itemid) return (itemid > 0 && itemid < sizeof(InfoInventario));

stock Inv_Cooldown(playerid)
{
    new now = GetTickCount();
    if (now - gInvLastAction[playerid] < INV_COOLDOWN_MS) return 1;
    gInvLastAction[playerid] = now;
    return 0;
}

stock Inv_IsBig(itemid)
{
    if (!Inv_ValidItem(itemid)) return 0;
    new g = InfoInventario[itemid][Guardable];
    return (g == 2 || g == 3);
}

stock Inv_CanSplit(itemid)
{
    if (!Inv_ValidItem(itemid) || itemid == 55 || itemid == 86) return 0;
    if (InfoInventario[itemid][IDArma] > 0) return 0;
    return (InfoInventario[itemid][MaxCantidad] > 1);
}

stock Inv_StackOf(itemid)
{
    if (!Inv_ValidItem(itemid) || itemid == 55 || itemid == 86) return 1;
    new m = InfoInventario[itemid][MaxCantidad];
    return (m > 1) ? m : 1;
}

stock Inv_CanPlace(slot, itemid)
{
    if (slot >= 0 && slot < INV_BAG_SLOTS) return !Inv_IsBig(itemid);
    if (slot == INV_SLOT_RHAND || slot == INV_SLOT_LHAND) return 1;
    return 0;
}

stock bool:IsStackableItem(obj)
{
    if (obj <= 0 || obj >= sizeof(InfoInventario)) return false;
    if (InfoInventario[obj][MaxCantidad] > 1) return true;
    return false;
}

stock GetSlotItem(playerid, idx, &obj, &cant)
{
    obj = 0; cant = 0;
    if (idx >= 0 && idx <= 8) { obj = InfoPersonaje[playerid][pBolsillo][idx]; cant = InfoPersonaje[playerid][pBolsilloCant][idx]; }
    else if (idx == 9)  { obj = InfoPersonaje[playerid][pManoDerecha]; cant = InfoPersonaje[playerid][pManoDerechaCant]; }
    else if (idx == 10) { obj = InfoPersonaje[playerid][pManoIzquierda]; cant = InfoPersonaje[playerid][pManoIzquierdaCant]; }
    else if (idx == 11) { obj = InfoPersonaje[playerid][pEspalda]; cant = InfoPersonaje[playerid][pEspaldaCant]; }
    return 1;
}

stock Inventory_SyncSlot(playerid, slot)
{
    if (!InventarioAbierto[playerid] || !gInvPageReady[playerid] || !Inv_ValidSlot(slot)) return 0;
    new obj, cant;
    GetSlotItem(playerid, slot, obj, cant);
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:slot", CEF_INT(slot), CEF_INT(obj), CEF_INT(cant));
    return 1;
}

stock SetSlotItem(playerid, idx, obj, cant)
{
    new query[512];
    if (idx >= 0 && idx <= 8)
    {
        if (InfoPersonaje[playerid][pBolsillo][idx] == obj && InfoPersonaje[playerid][pBolsilloCant][idx] == cant) return 0;
        InfoPersonaje[playerid][pBolsillo][idx] = obj;
        InfoPersonaje[playerid][pBolsilloCant][idx] = cant;
        mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = %d, Cantidad_bolsillo_%d = %d WHERE ID = %d", idx + 1, obj, idx + 1, cant, InfoPersonaje[playerid][pID]);
        mysql_tquery(db_samp, query);
    }
    else if (idx == 9) // Mano Derecha
    {
        if (InfoPersonaje[playerid][pManoDerecha] == obj && InfoPersonaje[playerid][pManoDerechaCant] == cant) return 0;
        if (InfoPersonaje[playerid][pManoDerecha] != 0)
        {
            if (InfoInventario[InfoPersonaje[playerid][pManoDerecha]][IDArma] > 0) ResetPlayerWeapons(playerid);
            RemovePlayerAttachedObject(playerid, 7);
        }
        InfoPersonaje[playerid][pManoDerecha] = obj;
        InfoPersonaje[playerid][pManoDerechaCant] = cant;
        if (obj == 0) {
            RemovePlayerAttachedObject(playerid, 7);
            ResetPlayerWeapons(playerid);
        }
        else {
            PonerObjeto(playerid, 1, obj);
            if (InfoInventario[obj][IDArma] > 0 && cant > 0) GivePlayerWeapon(playerid, InfoInventario[obj][IDArma], cant);
        }
        ActualizarManos(playerid, 1);
        mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_derecha = %d, Cantidad_mano_derecha = %d WHERE ID = %d", obj, cant, InfoPersonaje[playerid][pID]);
        mysql_tquery(db_samp, query);
    }
    else if (idx == 10) // Mano Izquierda
    {
        if (InfoPersonaje[playerid][pManoIzquierda] == obj && InfoPersonaje[playerid][pManoIzquierdaCant] == cant) return 0;
        if (InfoPersonaje[playerid][pManoIzquierda] != 0) RemovePlayerAttachedObject(playerid, 8);
        InfoPersonaje[playerid][pManoIzquierda] = obj;
        InfoPersonaje[playerid][pManoIzquierdaCant] = cant;
        if (obj == 0) RemovePlayerAttachedObject(playerid, 8);
        else PonerObjeto(playerid, 2, obj);
        ActualizarManos(playerid, 1);
        mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Mano_izquierda = %d, Cantidad_mano_izquierda = %d WHERE ID = %d", obj, cant, InfoPersonaje[playerid][pID]);
        mysql_tquery(db_samp, query);
    }
    else if (idx == 11) // Espalda
    {
        if (InfoPersonaje[playerid][pEspalda] == obj && InfoPersonaje[playerid][pEspaldaCant] == cant) return 0;
        if (InfoPersonaje[playerid][pEspalda] != 0) RemovePlayerAttachedObject(playerid, 9);
        InfoPersonaje[playerid][pEspalda] = obj;
        InfoPersonaje[playerid][pEspaldaCant] = cant;
        if (obj == 0) RemovePlayerAttachedObject(playerid, 9);
        mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Espalda = %d, Cantidad_espalda = %d WHERE ID = %d", obj, cant, InfoPersonaje[playerid][pID]);
        mysql_tquery(db_samp, query);
    }
    Inventory_SyncSlot(playerid, idx);
    return 1;
}

stock Inventory_SyncAll(playerid)
{
    if (!IsPlayerConnected(playerid) || !InventarioAbierto[playerid] || !gInvPageReady[playerid]) return 0;
    new name[64];
    format(name, sizeof name, "%s", GetNameFormat(playerid));
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:info", CEF_INT(INV_GET_MONEY(playerid)), CEF_STR(name));
    for (new s = 0; s < INV_TOTAL_SLOTS; s++) Inventory_SyncSlot(playerid, s);
    return 1;
}

stock Inventory_Notify(playerid, const text[], type = 0)
{
    if (InventarioAbierto[playerid] && gInvPageReady[playerid])
        CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:notify", CEF_STR(text), CEF_INT(type));
    else
        SendPlayerChatMessage(playerid, (type == 2) ? COLOR_GREY : 0x828BFDFF, text);
    return 1;
}

stock Inventory_Move(playerid, from, to, amount = 0)
{
    if (!Inv_ValidSlot(from) || !Inv_ValidSlot(to) || from == to) return 0;
    if (from == INV_SLOT_BACK || to == INV_SLOT_BACK) return 0;

    new src, srcAmt, dst, dstAmt;
    GetSlotItem(playerid, from, src, srcAmt);
    GetSlotItem(playerid, to, dst, dstAmt);
    if (!Inv_ValidItem(src)) return 0;

    if (!Inv_CanPlace(to, src))
    {
        SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande para guardar en los bolsillos.");
        return 0;
    }

	new bool:canSplitItem = (Inv_CanSplit(src) != 0);
	if (!canSplitItem || amount <= 0 || amount > srcAmt) amount = srcAmt;
    new stack = Inv_StackOf(src);

    if (!dst)
    {
		if (canSplitItem && amount > stack) amount = stack;
        SetSlotItem(playerid, to, src, amount);
        if (amount >= srcAmt) SetSlotItem(playerid, from, 0, 0);
        else SetSlotItem(playerid, from, src, srcAmt - amount);
        return 1;
    }

	if (dst == src && canSplitItem)
    {
        new space = stack - dstAmt;
        if (space <= 0) return 0;
        if (amount > space) amount = space;
        SetSlotItem(playerid, to, src, dstAmt + amount);
        if (amount >= srcAmt) SetSlotItem(playerid, from, 0, 0);
        else SetSlotItem(playerid, from, src, srcAmt - amount);
        return 1;
    }

    if (amount != srcAmt) return 0;
    if (!Inv_CanPlace(from, dst))
    {
        SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande para guardar en los bolsillos.");
        return 0;
    }
    SetSlotItem(playerid, from, dst, dstAmt);
    SetSlotItem(playerid, to, src, srcAmt);
    return 1;
}

stock Inventory_UseSlot(playerid, slot)
{
    if (!Inv_ValidSlot(slot)) return 0;
    new obj, cant;
    GetSlotItem(playerid, slot, obj, cant);
    if (!obj) return 0;

    if (slot < INV_BAG_SLOTS) sacar_inventario(playerid, slot);
    else if (slot == INV_SLOT_RHAND) guardar_inventario(playerid, 1);
    else if (slot == INV_SLOT_LHAND) guardar_inventario(playerid, 2);
    else pc_cmd_qespalda(playerid);

    Inventory_SyncAll(playerid);
    return 1;
}

stock Inventory_DropFromSlot(playerid, slot, amount)
{
    if (!Inv_ValidSlot(slot)) return 0;
    new obj, have;
    GetSlotItem(playerid, slot, obj, have);
    if (!Inv_ValidItem(obj)) return 0;
    if (amount <= 0 || amount > have || !Inv_CanSplit(obj)) amount = have;

    new Float:x, Float:y, Float:z, Float:ang;
    GetPlayerPos(playerid, x, y, z);
    GetPlayerFacingAngle(playerid, ang);
    x += floatsin(-ang, degrees) * 1.2;
    y += floatcos(-ang, degrees) * 1.2;

    tirar_objeto(obj, amount, x, y, z, GetPlayerVirtualWorld(playerid), GetPlayerInterior(playerid), 1);

    if (amount >= have) SetSlotItem(playerid, slot, 0, 0);
    else SetSlotItem(playerid, slot, obj, have - amount);
    ActualizarManos(playerid, 1);
    return 1;
}

stock Inventory_GiveToNearest(playerid, slot)
{
    if (slot != INV_SLOT_RHAND)
    {
        if (slot == INV_SLOT_LHAND) SendPlayerChatMessage(playerid, COLOR_GREY, "Pasa el objeto a tu mano derecha con /mano para poder darlo.");
        else SendPlayerChatMessage(playerid, COLOR_GREY, "Coge el objeto con la mano derecha para poder darlo.");
        return 0;
    }

    new Float:x, Float:y, Float:z;
    GetPlayerPos(playerid, x, y, z);
    new world = GetPlayerVirtualWorld(playerid), interior = GetPlayerInterior(playerid);
    new target = INVALID_PLAYER_ID, Float:best = INV_GIVE_RANGE;

    for (new i = 0; i < MAX_PLAYERS; i++)
    {
        if (i == playerid || !IsPlayerConnected(i)) continue;
        if (GetPlayerVirtualWorld(i) != world || GetPlayerInterior(i) != interior) continue;
        new Float:d = GetPlayerDistanceFromPoint(i, x, y, z);
        if (d <= best)
        {
            best = d;
            target = i;
        }
    }

    if (target == INVALID_PLAYER_ID)
    {
        SendPlayerChatMessage(playerid, COLOR_GREY, "No hay nadie cerca para darle el objeto.");
        return 0;
    }

    new params[8];
    format(params, sizeof params, "%d", target);
    pc_cmd_ceder(playerid, params);
    return 1;
}

stock Inventory_GetAmount(playerid, itemid)
{
    new total = 0, obj, cant;
    for (new s = 0; s < INV_TOTAL_SLOTS; s++)
    {
        GetSlotItem(playerid, s, obj, cant);
        if (obj == itemid) total += cant;
    }
    return total;
}

stock Inventory_HasItem(playerid, itemid, amount = 1)
{
    return (Inventory_GetAmount(playerid, itemid) >= amount);
}

stock Inventory_FindFreeBagSlot(playerid)
{
    for (new s = 0; s < INV_BAG_SLOTS; s++)
        if (InfoPersonaje[playerid][pBolsillo][s] == 0) return s;
    return -1;
}

stock Inventory_AddItem(playerid, itemid, amount = 0)
{
    if (!Inv_ValidItem(itemid) || Inv_IsBig(itemid)) return 0;
    if (amount <= 0) amount = InfoInventario[itemid][DefaultCantidad];
    if (amount <= 0) amount = 1;

    new stack = Inv_StackOf(itemid), remaining = amount, obj, cant;

    if (Inv_CanSplit(itemid))
    {
        for (new s = 0; s < INV_BAG_SLOTS && remaining > 0; s++)
        {
            GetSlotItem(playerid, s, obj, cant);
            if (obj != itemid) continue;
            new space = stack - cant;
            if (space <= 0) continue;
            new add = Inv_Min(space, remaining);
            SetSlotItem(playerid, s, itemid, cant + add);
            remaining -= add;
        }
    }

    for (new s = 0; s < INV_BAG_SLOTS && remaining > 0; s++)
    {
        GetSlotItem(playerid, s, obj, cant);
        if (obj) continue;
        new add = remaining;
        if (Inv_CanSplit(itemid)) add = Inv_Min(stack, remaining);
        SetSlotItem(playerid, s, itemid, add);
        remaining -= add;
    }
    return amount - remaining;
}

stock Inventory_RemoveItem(playerid, itemid, amount = 1)
{
    if (amount <= 0 || Inventory_GetAmount(playerid, itemid) < amount) return 0;
    new remaining = amount, obj, cant;
    for (new s = 0; s < INV_TOTAL_SLOTS && remaining > 0; s++)
    {
        GetSlotItem(playerid, s, obj, cant);
        if (obj != itemid) continue;
        new take = Inv_Min(cant, remaining);
        if (take >= cant) SetSlotItem(playerid, s, 0, 0);
        else SetSlotItem(playerid, s, itemid, cant - take);
        remaining -= take;
    }
    return 1;
}

stock Inventory_Present(playerid)
{
    if (!gInvPageReady[playerid]) return 0;
    Inventory_SyncAll(playerid);
    CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:open");
    return 1;
}

stock Inventory_Open(playerid)
{
    if (!IsPlayerConnected(playerid) || InventarioAbierto[playerid]) return 0;
    if (!CEF_PlayerHasPlugin(playerid))
    {
        SendClientMessage(playerid, -1, "Cargando CEF...");
        return 0;
    }

    InventarioAbierto[playerid] = true;
    CEF_ToggleChatInput(playerid, false);

    if (gCefInvEstado[playerid] == 0)
    {
        gCefInvEstado[playerid] = 1;
        gInvPageReady[playerid] = false;
        CEF_CreateBrowser(playerid, INV_BROWSER_ID, INV_URL, true, true);
    }
    else
    {
        CEF_SetBrowserVisible(playerid, INV_BROWSER_ID, true);
        CEF_FocusBrowser(playerid, INV_BROWSER_ID, true);
        Inventory_Present(playerid);
    }
    return 1;
}

stock Inventory_Close(playerid, bool:notifyJs = true)
{
    if (!InventarioAbierto[playerid]) return 0;
    InventarioAbierto[playerid] = false;

    if (notifyJs && gInvPageReady[playerid]) CEF_EmitEvent(playerid, INV_BROWSER_ID, "inv:close");

    if (gCefInvEstado[playerid] != 0)
    {
        CEF_FocusBrowser(playerid, INV_BROWSER_ID, false);
        CEF_SetBrowserVisible(playerid, INV_BROWSER_ID, false);
    }
    CEF_ToggleChatInput(playerid, true);
    return 1;
}

stock Inventory_Toggle(playerid)
{
    return InventarioAbierto[playerid] ? Inventory_Close(playerid) : Inventory_Open(playerid);
}

stock Inventory_ResetPlayer(playerid)
{
    InventarioAbierto[playerid] = false;
    gCefInvEstado[playerid] = 0;
    gInvPageReady[playerid] = false;
    gInvLastAction[playerid] = 0;
    return 1;
}

stock Inventory_Init()
{
    #if !defined INV_NO_AUTO_RESOURCE
        CEF_AddResource(INV_RESOURCE);
    #endif
    CEF_RegisterEvent("inv:ready", "OnInvJsReady");
    CEF_RegisterEvent("inv:close", "OnInvJsClose");
    CEF_RegisterEvent("inv:use", "OnInvJsUse", Argument_Integer);
    CEF_RegisterEvent("inv:move", "OnInvJsMove", Argument_Integer, Argument_Integer, Argument_Integer);
    CEF_RegisterEvent("inv:drop", "OnInvJsDrop", Argument_Integer, Argument_Integer);
    CEF_RegisterEvent("inv:give", "OnInvJsGive", Argument_Integer, Argument_Integer);
    return 1;
}

SetPlayerInventario(playerid, type)
{
    switch (type)
    {
        case 1: Inventory_Open(playerid);
        case 2: Inventory_Close(playerid);
        case 3: Inventory_SyncAll(playerid);
    }
    return 1;
}

forward EnviarDatosInventario(playerid);
public EnviarDatosInventario(playerid)
{
    return Inventory_SyncAll(playerid);
}

public OnInvJsReady(playerid, browserid)
{
    if (browserid != INV_BROWSER_ID) return 1;
    gInvPageReady[playerid] = true;
    if (InventarioAbierto[playerid]) Inventory_Present(playerid);
    return 1;
}

public OnInvJsClose(playerid, browserid)
{
    Inventory_Close(playerid, false);
    return 1;
}

public OnInvJsUse(playerid, browserid, slot)
{
    if (!InventarioAbierto[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_UseSlot(playerid, slot);
    return 1;
}

public OnInvJsMove(playerid, browserid, from, to, amount)
{
    if (!InventarioAbierto[playerid] || !Inv_ValidSlot(from) || !Inv_ValidSlot(to)) return 1;
    if (Inventory_Move(playerid, from, to, amount)) ActualizarManos(playerid, 1);
    else Inventory_SyncAll(playerid);
    return 1;
}

public OnInvJsDrop(playerid, browserid, slot, amount)
{
    if (!InventarioAbierto[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_DropFromSlot(playerid, slot, amount);
    Inventory_SyncAll(playerid);
    return 1;
}

public OnInvJsGive(playerid, browserid, slot, amount)
{
    if (!InventarioAbierto[playerid] || !Inv_ValidSlot(slot) || Inv_Cooldown(playerid)) return 1;
    Inventory_GiveToNearest(playerid, slot);
    Inventory_SyncAll(playerid);
    return 1;
}

public OnGameModeInit()
{
    Inventory_Init();
    #if defined INVH_OnGameModeInit
        return INVH_OnGameModeInit();
    #else
        return 1;
    #endif
}
#if defined _ALS_OnGameModeInit
    #undef OnGameModeInit
#else
    #define _ALS_OnGameModeInit
#endif
#define OnGameModeInit INVH_OnGameModeInit
#if defined INVH_OnGameModeInit
    forward INVH_OnGameModeInit();
#endif

public OnPlayerConnect(playerid)
{
    Inventory_ResetPlayer(playerid);
    #if defined INVH_OnPlayerConnect
        return INVH_OnPlayerConnect(playerid);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerConnect
    #undef OnPlayerConnect
#else
    #define _ALS_OnPlayerConnect
#endif
#define OnPlayerConnect INVH_OnPlayerConnect
#if defined INVH_OnPlayerConnect
    forward INVH_OnPlayerConnect(playerid);
#endif

public OnPlayerDisconnect(playerid, reason)
{
    Inventory_ResetPlayer(playerid);
    #if defined INVH_OnPlayerDisconnect
        return INVH_OnPlayerDisconnect(playerid, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnPlayerDisconnect
    #undef OnPlayerDisconnect
#else
    #define _ALS_OnPlayerDisconnect
#endif
#define OnPlayerDisconnect INVH_OnPlayerDisconnect
#if defined INVH_OnPlayerDisconnect
    forward INVH_OnPlayerDisconnect(playerid, reason);
#endif

public OnCefInitialize(playerid, bool:success, E_CEF_INIT_REASON:reason, const message[])
{
    #if !defined INV_NO_KEY
        if (success)
        {
            CEF_SetKeyCapture(playerid, true);
            CEF_EnableKey(playerid, INV_OPEN_KEY, true);
        }
    #endif
    #if defined INVH_OnCefInitialize
        return INVH_OnCefInitialize(playerid, success, reason, message);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnCefInitialize
    #undef OnCefInitialize
#else
    #define _ALS_OnCefInitialize
#endif
#define OnCefInitialize INVH_OnCefInitialize
#if defined INVH_OnCefInitialize
    forward INVH_OnCefInitialize(playerid, bool:success, E_CEF_INIT_REASON:reason, const message[]);
#endif

public OnCefBrowserCreated(playerid, browserid, bool:success, E_CEF_CREATE_STATUS:code, const reason[])
{
    if (browserid == INV_BROWSER_ID)
    {
        if (success)
        {
            gCefInvEstado[playerid] = 2;
            if (!InventarioAbierto[playerid])
            {
                CEF_FocusBrowser(playerid, INV_BROWSER_ID, false);
                CEF_SetBrowserVisible(playerid, INV_BROWSER_ID, false);
            }
        }
        else
        {
            gCefInvEstado[playerid] = 0;
            gInvPageReady[playerid] = false;
            if (InventarioAbierto[playerid])
            {
                InventarioAbierto[playerid] = false;
                CEF_ToggleChatInput(playerid, true);
            }
            SendClientMessage(playerid, -1, "No se pudo abrir el inventario (error de CEF).");
        }
    }
    #if defined INVH_OnCefBrowserCreated
        return INVH_OnCefBrowserCreated(playerid, browserid, success, code, reason);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnCefBrowserCreated
    #undef OnCefBrowserCreated
#else
    #define _ALS_OnCefBrowserCreated
#endif
#define OnCefBrowserCreated INVH_OnCefBrowserCreated
#if defined INVH_OnCefBrowserCreated
    forward INVH_OnCefBrowserCreated(playerid, browserid, bool:success, E_CEF_CREATE_STATUS:code, const reason[]);
#endif

public OnCefPressKey(playerid, key, scancode, modifiers, bool:down, bool:repeat)
{
    #if !defined INV_NO_KEY
        if (down && !repeat && key == INV_OPEN_KEY && !InventarioAbierto[playerid] && !CEF_IsChatInputOpen(playerid))
        {
            if (InfoPersonaje[playerid][pID] != 0) Inventory_Open(playerid);
        }
    #endif
    #if defined INVH_OnCefPressKey
        return INVH_OnCefPressKey(playerid, key, scancode, modifiers, down, repeat);
    #else
        return 1;
    #endif
}
#if defined _ALS_OnCefPressKey
    #undef OnCefPressKey
#else
    #define _ALS_OnCefPressKey
#endif
#define OnCefPressKey INVH_OnCefPressKey
#if defined INVH_OnCefPressKey
    forward INVH_OnCefPressKey(playerid, key, scancode, modifiers, bool:down, bool:repeat);
#endif

// ==========================================
// FUNCIONES DE SOPORTE (LEGACY)
// ==========================================

GetNameObjeto(modelo)
{
	new ex_name[64];
	alm(ex_name, InfoInventario[modelo][NombreObjeto]);
	return ex_name;
}

slot_inv(id_objeto, cantidad)
{
	new mensaje[128];
	switch (id_objeto)
	{
		case 19..31: format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d balas{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 40: format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d cargas{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 41: format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d usos{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 43..46: format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d gramos{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 47,48,49: format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d usos{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 55: format(mensaje, sizeof mensaje, "%s ({7b7dfe}ID %d{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		default:
		{
		    if (cantidad >= 2) format(mensaje, sizeof mensaje, "%s ({7b7dfe}%d unidades{FFFFFF})", InfoInventario[id_objeto][NombreObjeto], cantidad);
		    else format(mensaje, sizeof mensaje, "%s", InfoInventario[id_objeto][NombreObjeto]);
		}
	}
	return mensaje;
}

slot_objeto(id_objeto, cantidad)
{
	new mensaje[128];
	switch (id_objeto)
	{
		case 19..31: format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d balas)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 40: format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d cargas)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 41: format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d usos)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 43..46: format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d gramos)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 47,48,49: format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d usos)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		case 55: format(mensaje, sizeof mensaje, "%s {7b7dfe}(ID %d)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		default:
		{
		    if (cantidad >= 2) format(mensaje, sizeof mensaje, "%s {7b7dfe}(%d unidades)", InfoInventario[id_objeto][NombreObjeto], cantidad);
		    else format(mensaje, sizeof mensaje, "%s", InfoInventario[id_objeto][NombreObjeto]);
		}
	}
	return mensaje;
}

sacar_inventario(playerid, id)
{
	new query[1000];
	new Bol = InfoPersonaje[playerid][pBolsillo][id], Cant = InfoPersonaje[playerid][pBolsilloCant][id];
	if(Bol == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes nada en ese slot.");
	if(InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
	    if(InfoPersonaje[playerid][pManoDerecha] == 0)
		{
			if(InfoInventario[Bol][IDArma] > 0)
			{
				new arma = InfoInventario[Bol][IDArma], municion = Cant;
				if(municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
			}
			InfoPersonaje[playerid][pManoDerecha] = Bol;
			InfoPersonaje[playerid][pManoDerechaCant] = Cant;
			PonerObjeto(playerid, 1, Bol);
			InfoPersonaje[playerid][pBolsillo][id] = 0;
			InfoPersonaje[playerid][pBolsilloCant][id] = 0;
			SendClientMessageEx(playerid, 0x828BFDFF, "Coges tu %s en mano derecha.", InfoInventario[Bol][NombreObjeto]);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", id+1, InfoPersonaje[playerid][pBolsillo][id], id+1, InfoPersonaje[playerid][pBolsilloCant][id], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
		else
		{
		    new x_bol = InfoPersonaje[playerid][pManoDerecha], x_cant = InfoPersonaje[playerid][pManoDerechaCant];
		    if(InfoInventario[x_bol][IDArma] > 0)
			{
				if(IntentoChitearBalas(playerid)) return 1;
				x_cant = InfoPersonaje[playerid][pManoDerechaCant];
				RemovePlayerWeapon(playerid, InfoInventario[x_bol][IDArma]);
			}
			InfoPersonaje[playerid][pManoIzquierda] = x_bol;
			InfoPersonaje[playerid][pManoIzquierdaCant] = x_cant;
			PonerObjeto(playerid, 2, x_bol);
			if(InfoInventario[Bol][IDArma] > 0)
			{
				new arma = InfoInventario[Bol][IDArma], municion = Cant;
				if(municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
			}
			InfoPersonaje[playerid][pManoDerecha] = Bol;
			InfoPersonaje[playerid][pManoDerechaCant] = Cant;
			PonerObjeto(playerid, 1, Bol);
			InfoPersonaje[playerid][pBolsillo][id] = 0;
			InfoPersonaje[playerid][pBolsilloCant][id] = 0;
			SendClientMessageEx(playerid, 0x828BFDFF, "Coges tu %s en mano derecha, se pasó tu %s a la otra mano.", InfoInventario[Bol][NombreObjeto], InfoInventario[x_bol][NombreObjeto]);
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'",
			id+1, InfoPersonaje[playerid][pBolsillo][id], id+1, InfoPersonaje[playerid][pBolsilloCant][id], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
	}
	else if(InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		if(InfoInventario[Bol][IDArma] > 0)
		{
			new arma = InfoInventario[Bol][IDArma], municion = Cant;
			if(municion > 0) { GivePlayerWeapon(playerid, arma, municion); }
		}
		InfoPersonaje[playerid][pManoDerecha] = Bol;
		InfoPersonaje[playerid][pManoDerechaCant] = Cant;
		PonerObjeto(playerid, 1, Bol);
		InfoPersonaje[playerid][pBolsillo][id] = 0;
		InfoPersonaje[playerid][pBolsilloCant][id] = 0;
		SendClientMessageEx(playerid, 0x828BFDFF, "Coges tu %s en mano derecha.", InfoInventario[Bol][NombreObjeto]);
		mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", id+1, InfoPersonaje[playerid][pBolsillo][id], id+1, InfoPersonaje[playerid][pBolsilloCant][id], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, query);
		return 1;
	}
	ActualizarManos(playerid, 1);
	EnviarDatosInventario(playerid);
	SendPlayerChatMessage(playerid, COLOR_GREY, "Posees ambas manos ocupadas, guarda o arroja lo que llevas.");
	return 1;
}

guardar_inventario(playerid, mano)
{
	new query[512];
	if (GetPVarInt(playerid, "EstaCrack") == 1) return SendPlayerChatMessage(playerid, COLOR_GREY, "No puedes usar este comando mientras estás herido.");
	if (mano == 1)
	{
		if (InfoPersonaje[playerid][pManoDerecha] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano derecha.");
		new Mano = InfoPersonaje[playerid][pManoDerecha], Cant = InfoPersonaje[playerid][pManoDerechaCant], BolsilloLibre;
		if (InfoInventario[Mano][Guardable] == 2 || InfoInventario[Mano][Guardable] == 3)
		{
			if (IsObjectWearable(Mano)) pc_cmd_espalda(playerid);
			else SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande para guardar en el inventario o colocarse en espalda.");
			return 1;
		}
		Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] == 0)
		{
			InfoPersonaje[playerid][pBolsillo][x] = Mano;
			InfoPersonaje[playerid][pBolsilloCant][x] = Cant;
			RemovePlayerAttachedObject(playerid, 7);
			ResetPlayerWeapons(playerid);
			InfoPersonaje[playerid][pManoDerecha] = 0;
			InfoPersonaje[playerid][pManoDerechaCant] = 0;
			SendClientMessageEx(playerid, 0x828BFDFF, "Guardas tu %s.", InfoInventario[Mano][NombreObjeto]);
			BolsilloLibre = 1;
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", x+1, InfoPersonaje[playerid][pBolsillo][x], x+1, InfoPersonaje[playerid][pBolsilloCant][x], InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
		if (BolsilloLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes espacio en tus bolsillos.");
	}
	else if (mano == 2)
	{
		if (InfoPersonaje[playerid][pManoIzquierda] == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes un objeto en tu mano izquierda.");
		new Mano = InfoPersonaje[playerid][pManoIzquierda], Cant = InfoPersonaje[playerid][pManoIzquierdaCant], BolsilloLibre;
		if (InfoInventario[Mano][Guardable] == 2 || InfoInventario[Mano][Guardable] == 3)
		{
			if (IsObjectWearable(Mano)) pc_cmd_espalda(playerid);
			else SendPlayerChatMessage(playerid, COLOR_GREY, "Este objeto es demasiado grande para guardar en el inventario o colocarse en espalda.");
			return 1;
		}
		Loop(x, 9, 0) if (InfoPersonaje[playerid][pBolsillo][x] == 0)
		{
			InfoPersonaje[playerid][pBolsillo][x] = Mano;
			InfoPersonaje[playerid][pBolsilloCant][x] = Cant;
			RemovePlayerAttachedObject(playerid, 8);
			InfoPersonaje[playerid][pManoIzquierda] = 0;
			InfoPersonaje[playerid][pManoIzquierdaCant] = 0;
			SendClientMessageEx(playerid, 0x828BFDFF, "Guardas tu %s.", InfoInventario[Mano][NombreObjeto]);
			BolsilloLibre = 1;
			mysql_format(db_samp, query, sizeof query, "UPDATE personajes SET Bolsillo_%d = '%d', Cantidad_bolsillo_%d = '%d', Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'", x+1, InfoPersonaje[playerid][pBolsillo][x], x+1, InfoPersonaje[playerid][pBolsilloCant][x], InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
			mysql_tquery(db_samp, query);
			return 1;
		}
		RemovePlayerAttachedObject(playerid, (mano == 1) ? 7 : 8);
		if (mano == 1) ResetPlayerWeapons(playerid);
		ActualizarManos(playerid, 1);
		EnviarDatosInventario(playerid);
		if (BolsilloLibre == 0) return SendPlayerChatMessage(playerid, COLOR_GREY, "No tienes espacio en tus bolsillos.");
	}
	return 1;
}

recoger_objeto(playerid, id)
{
	new ObjetoExiste = 0;
	if (id == -1)
	{
		Loop(x, sizeof InfoSuelo, 0) if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoSuelo[x][DropPosX], InfoSuelo[x][DropPosY], InfoSuelo[x][DropPosZ]))
		{
			if (GetPlayerVirtualWorld(playerid) == InfoSuelo[x][DropVWorld] && GetPlayerInterior(playerid) == InfoSuelo[x][DropInterior])
			{
				if (InfoSuelo[x][DropID] != 0) { id = x; ObjetoExiste = 1; }
				break;
			}
		}
	}
	else
	{
		if (IsPlayerInRangeOfPoint(playerid, 2.0, InfoSuelo[id][DropPosX], InfoSuelo[id][DropPosY], InfoSuelo[id][DropPosZ]))
		{
			if (GetPlayerVirtualWorld(playerid) == InfoSuelo[id][DropVWorld] && GetPlayerInterior(playerid) == InfoSuelo[id][DropInterior])
			{
				if (InfoSuelo[id][DropID] != 0) ObjetoExiste = 1;
			}
		}
	}
	if (ObjetoExiste == 0) return 1;
	new string[256], objeto = InfoSuelo[id][DropID];
	new weaponid = InfoInventario[objeto][IDArma];
	if (InfoPersonaje[playerid][pHorasOn] < 2)
	{
		if (weaponid >= 22 && weaponid <= 34)
		{
			SendPlayerChatMessage(playerid, COLOR_GREY, "Necesitas tener almenos 2 horas de juego para tomar este tipo de arma.");
			return 1;
		}
	}
	if (IsValidDynamicObject(ObjetoCaido[id])) DestroyDynamicObject(ObjetoCaido[id]);
	ObjetoCaido[id] = 0;
	if (IsValidDynamic3DTextLabel(InfoSuelo[id][DropLabel]))
	{
		DestroyDynamic3DTextLabel(InfoSuelo[id][DropLabel]);
		InfoSuelo[id][DropLabel] = Text3D:INVALID_3DTEXT_ID;
	}
	InfoSuelo[id][DropLabel] = CreateDynamic3DTextLabel("dropid", -1, -1178.1569, 58.9069, 1.9609, 1.0, .worldid = 1+777, .interiorid = id);
	if (InfoPersonaje[playerid][pManoDerecha] == 0)
	{
		InfoPersonaje[playerid][pManoDerecha] = objeto, InfoPersonaje[playerid][pManoDerechaCant] = InfoSuelo[id][DropCantidad];
		if (InfoInventario[objeto][IDArma] > 0 && InfoSuelo[id][DropCantidad] > 0) { GivePlayerWeapon(playerid, InfoInventario[objeto][IDArma], InfoSuelo[id][DropCantidad]); }
		PonerObjeto(playerid, 1, objeto);
		mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_derecha = '%d', Cantidad_mano_derecha = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pManoDerecha], InfoPersonaje[playerid][pManoDerechaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, string);
	}
	else if (InfoPersonaje[playerid][pManoIzquierda] == 0)
	{
		InfoPersonaje[playerid][pManoIzquierda] = objeto, InfoPersonaje[playerid][pManoIzquierdaCant] = InfoSuelo[id][DropCantidad];
		PonerObjeto(playerid, 2, objeto);
		mysql_format(db_samp, string, sizeof string, "UPDATE personajes SET Mano_izquierda = '%d', Cantidad_mano_izquierda = '%d' WHERE ID = '%d'", InfoPersonaje[playerid][pManoIzquierda], InfoPersonaje[playerid][pManoIzquierdaCant], InfoPersonaje[playerid][pID]);
		mysql_tquery(db_samp, string);
	}
	format(string, sizeof string, "recoge %s del suelo.", InfoInventario[objeto][NombreObjeto]);
	rol_ame(playerid, string);
	if (InfoInventario[objeto][IDArma] > 0)
	{
		format(string, sizeof string, "%s recoge %s.", GetNameFormat(playerid), InfoInventario[objeto][NombreObjeto]);
		Log("f_logs/Tirar_Recoger.log", string);
	}
	InfoSuelo[id][DropPosX] = 0.0;
	InfoSuelo[id][DropPosY] = 0.0;
	InfoSuelo[id][DropPosZ] = 0.0;
	InfoSuelo[id][DropID] = 0;
	InfoSuelo[id][DropCantidad] = 0;
	KillTimer(ObjTimer[id]);
	Streamer_Update(playerid);
	return 1;
}

stock CEF_CrearInventario(playerid)
{
    if (gCefInvEstado[playerid] != 0) return 1;
    gCefInvEstado[playerid] = 1;
    gInvPageReady[playerid] = false;
    CEF_CreateBrowser(playerid, INV_BROWSER_ID, INV_URL, false, true);
    return 1;
}

stock CEF_AbrirInventario(playerid, bool:abrir)
{
    if (abrir) return Inventory_Open(playerid);
    return Inventory_Close(playerid);
}
