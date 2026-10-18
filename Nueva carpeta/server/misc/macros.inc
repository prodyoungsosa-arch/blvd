//macros
#define INVALID                     (-1)
#define funcion%0(%1)				forward %0(%1); public %0(%1)
#define	GetVehicleName(%0)			VehicleName[GetVehicleModel(%0)-400]
#define	SetPVarInt(%0,%1,0);		DeletePVar(%0,%1);
#define Loop(%0,%1,%2)				for(new %0 = %2; %0 < %1; %0++)
#define GetNameVehicle(%0) 			VehicleName[%0-400]
#define PRESSED(%0) \ 
(((newkeys & (%0)) == (%0)) && ((oldkeys & (%0)) != (%0)))
#define RELEASED(%0) \ 
(((newkeys & (%0)) != (%0)) && ((oldkeys & (%0)) == (%0)))