stock GetFreeObjectID()
{
	new id = -1;
	for(new i; i < MAX_COP_OBJECTS; i++)
	{
	    if(!CopObjectData[i][ObjCreated])
	    {
	        id = i;
	        break;
	    }
	}

	return id;
}