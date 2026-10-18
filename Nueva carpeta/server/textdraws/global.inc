new Text:INV_base, Text:INV_2base, Text:INV_info, Text:INV_2info, Text:INV_IeD, Text:INV_exit;
new Text:Velocimetro_Nice[9];
new Text:TD_Anuncio[5];
new Text:CocheVS[3];
new Text:g_tdKeyGame[4];

CreateTextDraws()
{
	g_tdKeyGame[0] = TextDrawCreate(319.000000, 377.000000, "_");
	TextDrawFont(g_tdKeyGame[0], 1);
	TextDrawLetterSize(g_tdKeyGame[0], 0.600000, 0.700003);
	TextDrawTextSize(g_tdKeyGame[0], 298.500000, 118.000000);
	TextDrawSetOutline(g_tdKeyGame[0], 1);
	TextDrawSetShadow(g_tdKeyGame[0], 0);
	TextDrawAlignment(g_tdKeyGame[0], 2);
	TextDrawColor(g_tdKeyGame[0], -1);
	TextDrawBackgroundColor(g_tdKeyGame[0], 255);
	TextDrawBoxColor(g_tdKeyGame[0], 168430335);
	TextDrawUseBox(g_tdKeyGame[0], 1);
	TextDrawSetProportional(g_tdKeyGame[0], 1);
	TextDrawSetSelectable(g_tdKeyGame[0], 0);

    g_tdKeyGame[1] = TextDrawCreate(319.200012, 379.000000, "_");
	TextDrawFont(g_tdKeyGame[1], 1);
	TextDrawLetterSize(g_tdKeyGame[1], 0.600000, 0.270000);
	TextDrawTextSize(g_tdKeyGame[1], 298.500000, 115.000000);
	TextDrawSetOutline(g_tdKeyGame[1], 1);
	TextDrawSetShadow(g_tdKeyGame[1], 0);
	TextDrawAlignment(g_tdKeyGame[1], 2);
	TextDrawColor(g_tdKeyGame[1], -1);
	TextDrawBackgroundColor(g_tdKeyGame[1], 255);
	TextDrawBoxColor(g_tdKeyGame[1], -623191347);
	TextDrawUseBox(g_tdKeyGame[1], 1);
	TextDrawSetProportional(g_tdKeyGame[1], 1);
	TextDrawSetSelectable(g_tdKeyGame[1], 0);

	g_tdKeyGame[2] = TextDrawCreate(300.000000, 367.000000, "Preview_Model");
	TextDrawFont(g_tdKeyGame[2], 5);
	TextDrawLetterSize(g_tdKeyGame[2], 0.600000, 2.000000);
	TextDrawTextSize(g_tdKeyGame[2], 37.000000, 42.000000);
	TextDrawSetOutline(g_tdKeyGame[2], 0);
	TextDrawSetShadow(g_tdKeyGame[2], 0);
	TextDrawAlignment(g_tdKeyGame[2], 1);
	TextDrawColor(g_tdKeyGame[2], 255);
	TextDrawBackgroundColor(g_tdKeyGame[2], 0);
	TextDrawBoxColor(g_tdKeyGame[2], 255);
	TextDrawUseBox(g_tdKeyGame[2], 0);
	TextDrawSetProportional(g_tdKeyGame[2], 1);
	TextDrawSetSelectable(g_tdKeyGame[2], 0);
	TextDrawSetPreviewModel(g_tdKeyGame[2], 2252);
	TextDrawSetPreviewRot(g_tdKeyGame[2], -103.000000, 5.000000, -42.000000, 0.790000);
	TextDrawSetPreviewVehCol(g_tdKeyGame[2], 1, 1);

	g_tdKeyGame[3] = TextDrawCreate(300.000000, 367.000000, "Preview_Model");
	TextDrawFont(g_tdKeyGame[3], 5);
	TextDrawLetterSize(g_tdKeyGame[3], 0.600000, 2.000000);
	TextDrawTextSize(g_tdKeyGame[3], 37.000000, 42.000000);
	TextDrawSetOutline(g_tdKeyGame[3], 0);
	TextDrawSetShadow(g_tdKeyGame[3], 0);
	TextDrawAlignment(g_tdKeyGame[3], 1);
	TextDrawColor(g_tdKeyGame[3], 255);
	TextDrawBackgroundColor(g_tdKeyGame[3], 0);
	TextDrawBoxColor(g_tdKeyGame[3], 255);
	TextDrawUseBox(g_tdKeyGame[3], 0);
	TextDrawSetProportional(g_tdKeyGame[3], 1);
	TextDrawSetSelectable(g_tdKeyGame[3], 0);
	TextDrawSetPreviewModel(g_tdKeyGame[3], 2252);
	TextDrawSetPreviewRot(g_tdKeyGame[3], -103.000000, 5.000000, -16.000000, 0.790000);
	TextDrawSetPreviewVehCol(g_tdKeyGame[3], 1, 1);
	
	//velocimetro
	Velocimetro_Nice[0] = TextDrawCreate(613.419433, 374.833160, "box_principal");
	TextDrawLetterSize(Velocimetro_Nice[0], 0.000000, 5.744801);
	TextDrawTextSize(Velocimetro_Nice[0], 538.672241, 0.000000);
	TextDrawAlignment(Velocimetro_Nice[0], 1);
	TextDrawColor(Velocimetro_Nice[0], -1);
	TextDrawUseBox(Velocimetro_Nice[0], 1);
	TextDrawBoxColor(Velocimetro_Nice[0], 572662218);
	TextDrawSetShadow(Velocimetro_Nice[0], 0);
	TextDrawBackgroundColor(Velocimetro_Nice[0], 255);
	TextDrawFont(Velocimetro_Nice[0], 1);
	TextDrawSetProportional(Velocimetro_Nice[0], 1);

	Velocimetro_Nice[1] = TextDrawCreate(538.470458, 358.073455, "box_bici");
	TextDrawLetterSize(Velocimetro_Nice[1], 0.000000, 3.599988);
	TextDrawTextSize(Velocimetro_Nice[1], 613.000000, 0.000000);
	TextDrawAlignment(Velocimetro_Nice[1], 1);
	TextDrawColor(Velocimetro_Nice[1], -1);
	TextDrawUseBox(Velocimetro_Nice[1], 1);
	TextDrawBoxColor(Velocimetro_Nice[1], 572662218);
	TextDrawSetShadow(Velocimetro_Nice[1], 0);
	TextDrawBackgroundColor(Velocimetro_Nice[1], 255);
	TextDrawFont(Velocimetro_Nice[1], 1);
	TextDrawSetProportional(Velocimetro_Nice[1], 1);

	Velocimetro_Nice[2] = TextDrawCreate(594.084777, 380.333404, "KM/h");
	TextDrawLetterSize(Velocimetro_Nice[2], 0.113601, 1.034166);
	TextDrawAlignment(Velocimetro_Nice[2], 1);
	TextDrawColor(Velocimetro_Nice[2], -1);
	TextDrawSetShadow(Velocimetro_Nice[2], 0);
	TextDrawSetOutline(Velocimetro_Nice[2], 1);
	TextDrawBackgroundColor(Velocimetro_Nice[2], 255);
	TextDrawFont(Velocimetro_Nice[2], 2);
	TextDrawSetProportional(Velocimetro_Nice[2], 1);

	Velocimetro_Nice[3] = TextDrawCreate(601.581176, 402.500030, "LD_SPAC:white");
	TextDrawLetterSize(Velocimetro_Nice[3], 0.000000, 0.000000);
	TextDrawTextSize(Velocimetro_Nice[3], 4.685180, 9.333312);
	TextDrawAlignment(Velocimetro_Nice[3], 1);
	TextDrawColor(Velocimetro_Nice[3], -1);
	TextDrawSetShadow(Velocimetro_Nice[3], 0);
	TextDrawSetOutline(Velocimetro_Nice[3], 0);
	TextDrawFont(Velocimetro_Nice[3], 4);

	Velocimetro_Nice[4] = TextDrawCreate(602.986694, 403.083343, "LD_SPAC:white");
	TextDrawLetterSize(Velocimetro_Nice[4], 0.000000, 0.000000);
	TextDrawTextSize(Velocimetro_Nice[4], -3.279602, 2.333333);
	TextDrawAlignment(Velocimetro_Nice[4], 1);
	TextDrawColor(Velocimetro_Nice[4], -1);
	TextDrawSetShadow(Velocimetro_Nice[4], 0);
	TextDrawSetOutline(Velocimetro_Nice[4], 0);
	TextDrawFont(Velocimetro_Nice[4], 4);

	Velocimetro_Nice[5] = TextDrawCreate(602.049682, 403.083343, "ld_dual:black");
	TextDrawLetterSize(Velocimetro_Nice[5], 0.000000, 0.000000);
	TextDrawTextSize(Velocimetro_Nice[5], 3.748184, 4.666666);
	TextDrawAlignment(Velocimetro_Nice[5], 1);
	TextDrawColor(Velocimetro_Nice[5], -1);
	TextDrawSetShadow(Velocimetro_Nice[5], 0);
	TextDrawSetOutline(Velocimetro_Nice[5], 0);
	TextDrawFont(Velocimetro_Nice[5], 4);

	Velocimetro_Nice[6] = TextDrawCreate(544.422180, 399.000152, "~r~!");
	TextDrawLetterSize(Velocimetro_Nice[6], 0.449999, 1.600000);
	TextDrawAlignment(Velocimetro_Nice[6], 1);
	TextDrawColor(Velocimetro_Nice[6], -1);
	TextDrawSetShadow(Velocimetro_Nice[6], 0);
	TextDrawSetOutline(Velocimetro_Nice[6], 1);
	TextDrawBackgroundColor(Velocimetro_Nice[6], 51);
	TextDrawFont(Velocimetro_Nice[6], 1);
	TextDrawSetProportional(Velocimetro_Nice[6], 1);

	Velocimetro_Nice[7] = TextDrawCreate(542.547485, 376.250030, "hud:radar_modgarage");
	TextDrawLetterSize(Velocimetro_Nice[7], 0.000000, 0.000000);
	TextDrawTextSize(Velocimetro_Nice[7], 9.838989, 10.500000);
	TextDrawAlignment(Velocimetro_Nice[7], 1);
	TextDrawColor(Velocimetro_Nice[7], -1);
	TextDrawSetShadow(Velocimetro_Nice[7], 0);
	TextDrawSetOutline(Velocimetro_Nice[7], 0);
	TextDrawFont(Velocimetro_Nice[7], 4);

	Velocimetro_Nice[8] = TextDrawCreate(580.823364, 366.271942, "km/h");
	TextDrawLetterSize(Velocimetro_Nice[8], 0.255939, 1.530820);
	TextDrawAlignment(Velocimetro_Nice[8], 1);
	TextDrawColor(Velocimetro_Nice[8], -1);
	TextDrawSetShadow(Velocimetro_Nice[8], 0);
	TextDrawSetOutline(Velocimetro_Nice[8], 1);
	TextDrawBackgroundColor(Velocimetro_Nice[8], 255);
	TextDrawFont(Velocimetro_Nice[8], 2);
	TextDrawSetProportional(Velocimetro_Nice[8], 1);

	// Textdraw's by EdinsonWalker

	//inventario 20/05/2020
	INV_base = TextDrawCreate(559.000000, 217.000000, "_");
	TextDrawFont(INV_base, 1);
	TextDrawLetterSize(INV_base, 0.595833, 23.450004);
	TextDrawTextSize(INV_base, 296.500000, 128.500000);
	TextDrawSetOutline(INV_base, 1);
	TextDrawSetShadow(INV_base, 0);
	TextDrawAlignment(INV_base, 2);
	TextDrawColor(INV_base, -1);
	TextDrawBackgroundColor(INV_base, 255);
	TextDrawBoxColor(INV_base, 210);
	TextDrawUseBox(INV_base, 1);
	TextDrawSetProportional(INV_base, 1);
	TextDrawSetSelectable(INV_base, 0);

	INV_2base = TextDrawCreate(463.000000, 295.000000, "_");
	TextDrawFont(INV_2base, 1);
	TextDrawLetterSize(INV_2base, 0.545833, 10.950005);
	TextDrawTextSize(INV_2base, 294.500000, 56.000000);
	TextDrawSetOutline(INV_2base, 1);
	TextDrawSetShadow(INV_2base, 0);
	TextDrawAlignment(INV_2base, 2);
	TextDrawColor(INV_2base, -1);
	TextDrawBackgroundColor(INV_2base, 255);
	TextDrawBoxColor(INV_2base, 210);
	TextDrawUseBox(INV_2base, 1);
	TextDrawSetProportional(INV_2base, 1);
	TextDrawSetSelectable(INV_2base, 0);

	INV_info = TextDrawCreate(463.000000, 293.000000, "Inventario");
	TextDrawFont(INV_info, 0);
	TextDrawLetterSize(INV_info, 0.425000, 1.650000);
	TextDrawTextSize(INV_info, 400.000000, 17.000000);
	TextDrawSetOutline(INV_info, 1);
	TextDrawSetShadow(INV_info, 0);
	TextDrawAlignment(INV_info, 2);
	TextDrawColor(INV_info, -1);
	TextDrawBackgroundColor(INV_info, 255);
	TextDrawBoxColor(INV_info, 0);
	TextDrawUseBox(INV_info, 1);
	TextDrawSetProportional(INV_info, 1);
	TextDrawSetSelectable(INV_info, 0);

	INV_2info = TextDrawCreate(486.000000, 358.000000, "-");
	TextDrawFont(INV_2info, 2);
	TextDrawLetterSize(INV_2info, 12.229171, -0.600000);
	TextDrawTextSize(INV_2info, 400.000000, 17.000000);
	TextDrawSetOutline(INV_2info, 1);
	TextDrawSetShadow(INV_2info, 0);
	TextDrawAlignment(INV_2info, 1);
	TextDrawColor(INV_2info, -1724723969);
	TextDrawBackgroundColor(INV_2info, 255);
	TextDrawBoxColor(INV_2info, 0);
	TextDrawUseBox(INV_2info, 1);
	TextDrawSetProportional(INV_2info, 1);
	TextDrawSetSelectable(INV_2info, 0);

	INV_IeD = TextDrawCreate(558.000000, 359.000000, "Izquierda_Espalda_Derecha");
	TextDrawFont(INV_IeD, 1);
	TextDrawLetterSize(INV_IeD, 0.275000, 1.149999);
	TextDrawTextSize(INV_IeD, 400.000000, 17.000000);
	TextDrawSetOutline(INV_IeD, 1);
	TextDrawSetShadow(INV_IeD, 0);
	TextDrawAlignment(INV_IeD, 2);
	TextDrawColor(INV_IeD, -741092353);
	TextDrawBackgroundColor(INV_IeD, 255);
	TextDrawBoxColor(INV_IeD, 0);
	TextDrawUseBox(INV_IeD, 1);
	TextDrawSetProportional(INV_IeD, 1);
	TextDrawSetSelectable(INV_IeD, 0);

	INV_exit = TextDrawCreate(436.000000, 379.000000, "X");
	TextDrawFont(INV_exit, 1);
	TextDrawLetterSize(INV_exit, 0.491665, 1.549999);
	TextDrawTextSize(INV_exit, 449.000000, 26.500000);
	TextDrawSetOutline(INV_exit, 1);
	TextDrawSetShadow(INV_exit, 0);
	TextDrawAlignment(INV_exit, 1);
	TextDrawColor(INV_exit, -1523963137);
	TextDrawBackgroundColor(INV_exit, 255);
	TextDrawBoxColor(INV_exit, 0);
	TextDrawUseBox(INV_exit, 1);
	TextDrawSetProportional(INV_exit, 1);
	TextDrawSetSelectable(INV_exit, 1);

	//anuncios
	TD_Anuncio[0] = TextDrawCreate(510.000000, 405.249786, "");
	TextDrawLetterSize(TD_Anuncio[0], 0.177136, 0.859163);
	TextDrawAlignment(TD_Anuncio[0], 3);
	TextDrawColor(TD_Anuncio[0], -1);
	TextDrawSetShadow(TD_Anuncio[0], 0);
	TextDrawSetOutline(TD_Anuncio[0], 1);
	TextDrawBackgroundColor(TD_Anuncio[0], 255);
	TextDrawFont(TD_Anuncio[0], 1);
	TextDrawSetProportional(TD_Anuncio[0], 1);

	TD_Anuncio[1] = TextDrawCreate(510.000000, 392.999877, "");
	TextDrawLetterSize(TD_Anuncio[1], 0.177136, 0.859163);
	TextDrawAlignment(TD_Anuncio[1], 3);
	TextDrawColor(TD_Anuncio[1], -1);
	TextDrawSetShadow(TD_Anuncio[1], 0);
	TextDrawSetOutline(TD_Anuncio[1], 1);
	TextDrawBackgroundColor(TD_Anuncio[1], 255);
	TextDrawFont(TD_Anuncio[1], 1);
	TextDrawSetProportional(TD_Anuncio[1], 1);

	TD_Anuncio[2] = TextDrawCreate(510.000000, 380.166687, "");
	TextDrawLetterSize(TD_Anuncio[2], 0.177136, 0.859163);
	TextDrawAlignment(TD_Anuncio[2], 3);
	TextDrawColor(TD_Anuncio[2], -1);
	TextDrawSetShadow(TD_Anuncio[2], 0);
	TextDrawSetOutline(TD_Anuncio[2], 1);
	TextDrawBackgroundColor(TD_Anuncio[2], 255);
	TextDrawFont(TD_Anuncio[2], 1);
	TextDrawSetProportional(TD_Anuncio[2], 1);

	TD_Anuncio[3] = TextDrawCreate(510.000000, 367.916625, "");
	TextDrawLetterSize(TD_Anuncio[3], 0.177136, 0.859163);
	TextDrawAlignment(TD_Anuncio[3], 3);
	TextDrawColor(TD_Anuncio[3], -1);
	TextDrawSetShadow(TD_Anuncio[3], 0);
	TextDrawSetOutline(TD_Anuncio[3], 1);
	TextDrawBackgroundColor(TD_Anuncio[3], 255);
	TextDrawFont(TD_Anuncio[3], 1);
	TextDrawSetProportional(TD_Anuncio[3], 1);

	TD_Anuncio[4] = TextDrawCreate(510.000000, 356.249908, "");
	TextDrawLetterSize(TD_Anuncio[4], 0.177136, 0.859163);
	TextDrawAlignment(TD_Anuncio[4], 3);
	TextDrawColor(TD_Anuncio[4], -1);
	TextDrawSetShadow(TD_Anuncio[4], 0);
	TextDrawSetOutline(TD_Anuncio[4], 1);
	TextDrawBackgroundColor(TD_Anuncio[4], 255);
	TextDrawFont(TD_Anuncio[4], 1);
	TextDrawSetProportional(TD_Anuncio[4], 1);

	// CocheVS
	CocheVS[0] = TextDrawCreate(213.000000, 73.000000, "box");
	TextDrawLetterSize(CocheVS[0], 0.000000, 28.962997);
	TextDrawTextSize(CocheVS[0], 423.000000, 0.000000);
	TextDrawAlignment(CocheVS[0], 1);
	TextDrawColor(CocheVS[0], -1);
	TextDrawUseBox(CocheVS[0], 1);
	TextDrawBoxColor(CocheVS[0], 209);
	TextDrawSetShadow(CocheVS[0], 0);
	TextDrawBackgroundColor(CocheVS[0], 135);
	TextDrawFont(CocheVS[0], 1);
	TextDrawSetProportional(CocheVS[0], 1);

	CocheVS[1] = TextDrawCreate(246.666748, 316.493621, "Regresar");
	TextDrawLetterSize(CocheVS[1], 0.319999, 1.409185);
	TextDrawTextSize(CocheVS[1], 20.400000, 49.000000);
	TextDrawAlignment(CocheVS[1], 2);
	TextDrawColor(CocheVS[1], -1);
	TextDrawUseBox(CocheVS[1], 1);
	TextDrawBoxColor(CocheVS[1], 336860415);
	TextDrawSetShadow(CocheVS[1], 0);
	TextDrawSetOutline(CocheVS[1], 1);
	TextDrawBackgroundColor(CocheVS[1], 255);
	TextDrawFont(CocheVS[1], 1);
	TextDrawSetProportional(CocheVS[1], 1);
	TextDrawSetSelectable(CocheVS[1], true);

	CocheVS[2] = TextDrawCreate(389.933349, 316.218139, "Comprar");
	TextDrawLetterSize(CocheVS[2], 0.319999, 1.409185);
	TextDrawTextSize(CocheVS[2], 20.000000, 49.000000);
	TextDrawAlignment(CocheVS[2], 2);
	TextDrawColor(CocheVS[2], -1);
	TextDrawUseBox(CocheVS[2], 1);
	TextDrawBoxColor(CocheVS[2], 336860415);
	TextDrawSetShadow(CocheVS[2], 0);
	TextDrawSetOutline(CocheVS[2], 1);
	TextDrawBackgroundColor(CocheVS[2], 255);
	TextDrawFont(CocheVS[2], 1);
	TextDrawSetProportional(CocheVS[2], 1);
	TextDrawSetSelectable(CocheVS[2], true);
	return 1;
}