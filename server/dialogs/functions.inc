CMD:testdialog(playerid)
{
    new str[128];
    format(str, sizeof(str), "~w~Al follarte a VanNet se te quitaran ~g~$200 ~w~de tu posesion. ~n~Pero a cambio recibiras el culito de ~b~vannet recien depilado y listo para la ~y~accion.");
    CreateDialogTD(playerid, "Deseas follarte a vannet?", str, "Aceptar", "Rechazar", DIALOG_TEST);
    return 1;
}