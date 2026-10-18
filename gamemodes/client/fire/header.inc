new totalincendios = 1;
enum iInfo
{
	pI_IDsql,
	pI_intensidad,
	pI_propiedad,
	pI_tipo,
	pI_objeto[15],
};
new InfoIncendio[MAX_INCENDIOS][iInfo];

new sel_incendio[MAX_PLAYERS][MAX_INCENDIOS];