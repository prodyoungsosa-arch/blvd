//Timer para usar comando /ext
new DopTimer[MAX_PLAYERS];
//Timer para usar el /cambiarpersonaje
new PersonajeTiempo[MAX_PLAYERS];
//Casco
new Seatbelt[MAX_PLAYERS];
//Soga y venda
new Blinded[MAX_PLAYERS], Tied[MAX_PLAYERS];

//Reportes
enum reportinfo
{
	HasBeenUsed,
	Report[128],
	ReportFrom,
	CheckingReport,
 	TimeToExpire,
	BeingUsed,
	ReportExpireTimer,
	ReplyTimerr
}
new Reports[MAX_REPORTS][reportinfo];

new JustReported[MAX_PLAYERS];
new JustDuda[MAX_PLAYERS];

new Rope[MAX_PLAYERS];
new JetPack[MAX_PLAYERS];
new PuedeD[MAX_PLAYERS];
