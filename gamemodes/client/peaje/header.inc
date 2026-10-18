//<=================================> sistema de peajes
new cierre_p = 0, d_peaje = 50;
#define VELOCITY_PEAJE_TIME			(30)
#define VELOCITY_PEAJE_PORCENT		(2)
enum ppInfo
{
	p_objectid,
	p_modelid,
	Float:pos_X,
	Float:pos_Y,
	Float:pos_Z,
	Float:pos_RotX,
	Float:pos_RotY,
	Float:pos_RotZ,
	Float:pos_Xini,
	Float:pos_Yini,
	Float:pos_Zini,
	Float:pos_RotXini,
	Float:pos_RotYini,
	Float:pos_RotZini,
	Float:pos_cmdX,
	Float:pos_cmdY,
	Float:pos_cmdZ,
	peaje_tipo,
	anim_tipo,
	gratis_p,
};
new MAX_PEAJE, i_Peaje[MAX_PEAJES][ppInfo];