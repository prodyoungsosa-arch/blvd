#define MAX_COP_OBJECTS     		(300)
enum e_object_data
{
	Owner[MAX_PLAYER_NAME],
	Type,
	ObjData,
	ObjModel,
	Float: ObjXb,
	Float: ObjYb,
	Float: ObjZb,
	Float: ObjRX,
	Float: ObjRY,
	Float: ObjRZ,
	ObjInterior,
	ObjVirtualWorld,
	ObjID,
	Text3D: ObjLabel,
	ObjArea,
	bool: ObjCreated
}
new
	CopObjectData[MAX_COP_OBJECTS][e_object_data],
	EditingCopObjectID[MAX_PLAYERS] = {-1, ...},
	RoadblockList = mS_INVALID_LISTID,
	SignList = mS_INVALID_LISTID;

new
    Float: zOffsets[5] = {1.35, 3.25, 0.35, 0.4, 5.35};

enum _:e_object_types
{
	OBJECT_TYPE_ROADBLOCK,
	OBJECT_TYPE_SIGN,
	OBJECT_TYPE_POLICELINE,
	OBJECT_TYPE_SPIKE
}