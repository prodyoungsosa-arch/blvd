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
				
				//Pescado
				case 87..91: SetPlayerAttachedObject(playerid, 7, modelo, 6, 0.069998, 0.057998, -0.008000, 0.000000, 0.000000, 0.000000, 1.116000, 1.000000, 1.254999);
				//Ca�a
				case 92: SetPlayerAttachedObject(playerid, 7, modelo, 5, 0.049000, 0.042999, -0.027000, 17.399976, -34.500000, 175.000015, 1.000000, 1.000000, 1.000000);
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
				
				//pescados
				case 87..91: SetPlayerAttachedObject(playerid, 8, modelo, 5, 0.024999, 0.000000, -0.005999, 0.000000, 0.000000, 0.000000, 1.000000, 1.000000, 1.000000); //nudillera
                //ca�a
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
				//
				switch (ObjetoID)
				{
					case 1..5: { rotx = 85; roty = 1; rotz = 8; Z += 0; } //nudillera, palo de golf, porra, cuchillo y bate
					case 6: { rotx = 8.5; roty = 90; rotz = -82; Z += 0.1; } //pala
					case 7,8: { rotx = 85; roty = 1; rotz = 8; Z += 0; } //palo de billar, sable
					case 9: { rotx = 95; roty = -69; rotz = 8; Z += 0.08; } //motosierra
					case 10..13: { rotx = 90; roty = 1; rotz =  8; Z+= 0; } //consoladores
					case 14: { rotx = 70; roty = 1; rotz =  8; Z+= 0; } //flores
					case 15: { rotx = 87; roty = 1; rotz =  8; Z+= 0; } //bastón
					case 16: { rotx = 0; roty = -17; rotz = 0; Z += 0.05; } //granada
					case 17: { rotx = 0; roty = 0.3; rotz = -7; Z += 0.06; } //granada de humo
					case 18: { rotx = -5.5; roty = -1.8; rotz = -7; Z += 0.2; } //molotov
					case 19: { rotx = -85; roty = 3; rotz = 3; Z += 0.04; } //9mm
					case 20: { rotx = -85; roty = 3; rotz = 3; Z += 0.05; } //9mm con silenciador
					case 21: { rotx = -85; roty = 3; rotz = 3; Z += 0.04; } //desert eagle
					case 22: { rotx = -82; roty = 58; rotz = 64; Z += 0.06; } //escopeta
					case 23: { rotx = -90; roty = 58; rotz =  64; Z += 0.05; } //recortada
					case 24: { rotx = -82; roty = 58; rotz =  64; Z += 0.05; } //combate
					case 25,26: { rotx = -90; roty = 0; rotz = 0; Z += 0.04; } //uzi, mp5k
					case 27,28: { rotx = -92.6; roty = 0.8; rotz = -3.1; Z += 0.06; } //ak47, m4a1
					case 29: { rotx = -90; roty = 0; rotz = 0; Z += 0.05; } //tec9
					case 30: { rotx = -112; roty = -150; rotz = -159; Z += 0.04; } //rifle de caza
					case 31: { rotx = -105; roty = -150; rotz = -159; Z += 0.04; } //rifle de francotirador
					case 32,33,34: { rotx = -90; roty = 0; rotz = 0; Z += 0.07; } //cohete, rpg, lanzallamas
					case 35: {  rotx = -4.4; roty = 27.5; rotz = 0; Z += 0.315; } //minigun
					case 36: {  rotx = 0.5; roty = -5.5; rotz = -4.7; Z += 0.15; } //spray
					case 37: { rotx = -3.2; roty = 40.3; rotz = 0; Z += 0.59; } //extintor
					case 38: { rotx = 0; roty = -1.8; rotz = -30; Z += 0.02; } //camara
					case 39: { rotx = 0; roty = 0; rotz = 9.7; Z += 0.19; } //paracaidas
					case 40: { rotx = -85; roty = 3; rotz = 3; Z += 0.05; } //taser
					case 41: { rotx = 0; roty = 0; rotz = 0; Z += 0.1; } //encendedor
					case 42: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; } //paquete de cigarros
					case 43..46: { rotx = 0; roty = 0; rotz = 0; Z += 0.12; } //marihuana, crack, metanfetamina, cocaína
					case 47: { rotx = 0; roty = -90; rotz = 0; Z += 0.02; } //canuto de marihuana
					case 48: { rotx = 0; roty = 0; rotz = 90; Z += 0.05; } //blunt de marihuana
					case 49: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; } //cigarro
					case 50: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; } //teléfono s10
					case 51: { rotx = 0; roty = 0; rotz = 0; Z += 0; } //boombox
					case 52: { rotx = 0; roty = 0; rotz = 0; Z += 0.2; } //dinamita
					case 53: { rotx = 0; roty = 0; rotz = 0; Z += 0.06; } //botiquin
					case 54: { rotx = -82; roty = 58; rotz = 64; Z += 0.06; } //escopeta no-letal
					case 55: { rotx = 0; roty = 0; rotz = 0; Z += 0.08; } //caja
					case 56..60: { rotx = 0; roty = 90; rotz = 0; Z += 0.02; } //cargadores 9mm, eagle, uzi, mp5 y tec9
					case 61..64: { rotx = 0; roty = 0; rotz = 0; Z += 0.06; } //cargadores ak47, m4a1, rifles y cartucho de escopeta
					case 65: { rotx = 0; roty = 0; rotz = 0; Z += 0.15; } //cerveza
					case 66: { rotx = 0; roty = 0; rotz = 0; Z += 0.15; } //chaleco
					case 67: { rotx = 0; roty = 0; rotz = 0; Z += 0; } //sixpack de cerveza
					case 86: { rotx = -89; roty = 0; rotz = 357; Z += 0; } //mochila
					default: { rotx = 0; roty = 0; rotz = 0; Z += 0.02; }
				}
				//label
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

SetPlayerInventario(playerid, type)
{
	if (InfoCuenta[playerid][jEstiloBolsillos] != 0) return 1;
	new gformat[170];
	//type: 1 (mostrar) 2 (remover) 3 (actualizar)
	switch (type)
	{
		case 1: //mostrar
		{
			if(IsPlayerFishing[playerid] == true) return 1;
			if (Act_Inventario[playerid] != 0) return 1;
			if (InfoPersonaje[playerid][pTogVelocimetro] != 0 && GetPlayerVehicleID(playerid) != 0)
			{
				hide_velocimetro(playerid);
			}
			SetPlayerAnuncio(playerid, 2);
			
			//indice
			TextDrawShowForPlayer(playerid, INV_base);
			TextDrawShowForPlayer(playerid, INV_2base);
			
			//nombre
			format(gformat, sizeof gformat, "%s", InfoPersonaje[playerid][pNombre_Apellido]);
			PlayerTextDrawSetStringEx(playerid, INV_nombre[playerid], gformat);
			PlayerTextDrawShow(playerid, INV_nombre[playerid]);
			
			//skin
			PlayerTextDrawSetPreviewModel(playerid, INV_skin[playerid], InfoPersonaje[playerid][pSkin]);
			PlayerTextDrawShow(playerid, INV_skin[playerid]);
			
			//slots de inventario
			new old1 = 0, old2 = 1;
			Loop(id, 9, 0)
			{
				new obj = InfoPersonaje[playerid][pBolsillo][id], cantidad = InfoPersonaje[playerid][pBolsilloCant][id]; //esto es el número cantidad
				if (InfoPersonaje[playerid][pBolsillo][id] != 0) // ocupada
				{
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][old1], 125);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][old1], InfoInventario[obj][ModeloObjeto]);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][old1], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
					//unidades
					format(gformat, sizeof gformat, "%d", cantidad);
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][old2], gformat);
				}
				else // vacía
				{
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][old1], 1296911741);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][old1], 346);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][old1], 0.0, 0.0, 0.0, 0.0);
					//unidades
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][old2], "vacío");
				}
				PlayerTextDrawShow(playerid, INV_obj[playerid][old1]);
				PlayerTextDrawShow(playerid, INV_obj[playerid][old2]);
				old1 += 2;
				old2 += 2;
			}
			//mano izquierda
			if (InfoPersonaje[playerid][pManoIzquierda] != 0) // ocupada
			{
				new obj = InfoPersonaje[playerid][pManoIzquierda];
				new cantidad = InfoPersonaje[playerid][pManoIzquierdaCant];
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][18], 125);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][18], InfoInventario[obj][ModeloObjeto]);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][18], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
				//unidades
				format(gformat, sizeof gformat, "%d", cantidad);
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][19], gformat);
			}
			else // vacía
			{
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][18], 1296911741);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][18], 346);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][18], 0.0, 0.0, 0.0, 0.0);
				//unidades
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][19], "vacío");
			}
			PlayerTextDrawShow(playerid, INV_obj[playerid][18]);
			PlayerTextDrawShow(playerid, INV_obj[playerid][19]);
			//espalda
			if (InfoPersonaje[playerid][pEspalda] != 0) // ocupada
			{
				new obj = InfoPersonaje[playerid][pEspalda];
				new cantidad = InfoPersonaje[playerid][pEspaldaCant];
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][20], 125);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][20], InfoInventario[obj][ModeloObjeto]);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][20], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
				//unidades
				format(gformat, sizeof gformat, "%d", cantidad);
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][21], gformat);
			}
			else // vacía
			{
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][20], 1296911741);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][20], 346);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][20], 0.0, 0.0, 0.0, 0.0);
				//unidades
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][21], "vacío");
			}
			PlayerTextDrawShow(playerid, INV_obj[playerid][20]);
			PlayerTextDrawShow(playerid, INV_obj[playerid][21]);
			//mano derecha
			if (InfoPersonaje[playerid][pManoDerecha] != 0) // ocupada
			{
				new obj = InfoPersonaje[playerid][pManoDerecha];
				new cantidad = InfoPersonaje[playerid][pManoDerechaCant];
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][22], 125);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][22], InfoInventario[obj][ModeloObjeto]);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][22], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
				//unidades
				format(gformat, sizeof gformat, "%d", cantidad);
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][23], gformat);
			}
			else // vacía
			{
				//modelo
				PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][22], 1296911741);
				PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][22], 346);
				PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][22], 0.0, 0.0, 0.0, 0.0);
				//unidades
				PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][23], "vacío");
			}
			PlayerTextDrawShow(playerid, INV_obj[playerid][22]);
			PlayerTextDrawShow(playerid, INV_obj[playerid][23]);
			TextDrawShowForPlayer(playerid, INV_info);
			TextDrawShowForPlayer(playerid, INV_2info);
			TextDrawShowForPlayer(playerid, INV_IeD);
			TextDrawShowForPlayer(playerid, INV_exit);
			SelectTextDraw(playerid, 0xd63417BB);
			Act_Inventario[playerid] = 1;
		}
		case 2: //remover
		{
			if (Act_Inventario[playerid] != 1) return 1;
			TextDrawHideForPlayer(playerid, INV_base);
			TextDrawHideForPlayer(playerid, INV_2base);
			TextDrawHideForPlayer(playerid, INV_info);
			TextDrawHideForPlayer(playerid, INV_2info);
			TextDrawHideForPlayer(playerid, INV_IeD);
			TextDrawHideForPlayer(playerid, INV_exit);
			PlayerTextDrawHide(playerid, INV_nombre[playerid]);
			Loop(x, 24, 0) { PlayerTextDrawHide(playerid, INV_obj[playerid][x]); }
			PlayerTextDrawHide(playerid, INV_skin[playerid]);
			Act_Inventario[playerid] = 0;
			if (InfoPersonaje[playerid][pTogVelocimetro] != 0 && GetPlayerVehicleID(playerid) != 0)
			{
				mostrar_velocimetro(playerid, GetPlayerVehicleID(playerid));
			}
			SetPlayerAnuncio(playerid, 1);
		}
		case 3: //actualizar
		{
			if (Act_Inventario[playerid] != 0)
			{
				Loop(x, 24, 0) { PlayerTextDrawHide(playerid, INV_obj[playerid][x]); }
				//slots de inventario
				new old1 = 0, old2 = 1;
				Loop(id, 9, 0)
				{
					new obj = InfoPersonaje[playerid][pBolsillo][id], cantidad = InfoPersonaje[playerid][pBolsilloCant][id]; //esto es el número cantidad
					if (InfoPersonaje[playerid][pBolsillo][id] != 0) // ocupada
					{
						//modelo
						PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][old1], 125);
						PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][old1], InfoInventario[obj][ModeloObjeto]);
						PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][old1], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
						//unidades
						format(gformat, sizeof gformat, "%d", cantidad);
						PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][old2], gformat);
					}
					else // vacía
					{
						//modelo
						PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][old1], 1296911741);
						PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][old1], 346);
						PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][old1], 0.0, 0.0, 0.0, 0.0);
						//unidades
						PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][old2], "vacío");
					}
					PlayerTextDrawShow(playerid, INV_obj[playerid][old1]);
					PlayerTextDrawShow(playerid, INV_obj[playerid][old2]);
					old1 += 2;
					old2 += 2;
				}
				//mano izquierda
				if (InfoPersonaje[playerid][pManoIzquierda] != 0) // ocupada
				{
					new obj = InfoPersonaje[playerid][pManoIzquierda];
					new cantidad = InfoPersonaje[playerid][pManoIzquierdaCant];
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][18], 125);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][18], InfoInventario[obj][ModeloObjeto]);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][18], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
					//unidades
					format(gformat, sizeof gformat, "%d", cantidad);
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][19], gformat);
				}
				else // vacía
				{
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][18], 1296911741);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][18], 346);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][18], 0.0, 0.0, 0.0, 0.0);
					//unidades
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][19], "vacío");
				}
				PlayerTextDrawShow(playerid, INV_obj[playerid][18]);
				PlayerTextDrawShow(playerid, INV_obj[playerid][19]);
				//espalda
				if (InfoPersonaje[playerid][pEspalda] != 0) // ocupada
				{
					new obj = InfoPersonaje[playerid][pEspalda];
					new cantidad = InfoPersonaje[playerid][pEspaldaCant];
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][20], 125);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][20], InfoInventario[obj][ModeloObjeto]);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][20], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
					//unidades
					format(gformat, sizeof gformat, "%d", cantidad);
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][21], gformat);
				}
				else // vacía
				{
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][20], 1296911741);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][20], 346);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][20], 0.0, 0.0, 0.0, 0.0);
					//unidades
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][21], "vacío");
				}
				PlayerTextDrawShow(playerid, INV_obj[playerid][20]);
				PlayerTextDrawShow(playerid, INV_obj[playerid][21]);
				//mano derecha
				if (InfoPersonaje[playerid][pManoDerecha] != 0) // ocupada
				{
					new obj = InfoPersonaje[playerid][pManoDerecha];
					new cantidad = InfoPersonaje[playerid][pManoDerechaCant];
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][22], 125);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][22], InfoInventario[obj][ModeloObjeto]);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][22], InfoInventario[obj][invRotX], InfoInventario[obj][invRotY], InfoInventario[obj][invRotZ], InfoInventario[obj][invZoom]);
					//unidades
					format(gformat, sizeof gformat, "%d", cantidad);
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][23], gformat);
				}
				else // vacía
				{
					//modelo
					PlayerTextDrawBackgroundColor(playerid, INV_obj[playerid][22], 1296911741);
					PlayerTextDrawSetPreviewModel(playerid, INV_obj[playerid][22], 346);
					PlayerTextDrawSetPreviewRot(playerid, INV_obj[playerid][22], 0.0, 0.0, 0.0, 0.0);
					//unidades
					PlayerTextDrawSetStringEx(playerid, INV_obj[playerid][23], "vacío");
				}
				PlayerTextDrawShow(playerid, INV_obj[playerid][22]);
				PlayerTextDrawShow(playerid, INV_obj[playerid][23]);
			}
		}
	}
	return 1;
}

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
		    if(InfoInventario[x_bol][IDArma] > 0) //- Si es arma
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
				if (InfoSuelo[x][DropID] != 0)
				{
					id = x;
					ObjetoExiste = 1;
				}
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
				if (InfoSuelo[id][DropID] != 0)
				{
					ObjetoExiste = 1;
				}
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
