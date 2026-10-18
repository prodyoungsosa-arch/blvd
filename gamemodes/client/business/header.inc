new totalnegocios = 1;			//negocios dinámicos
//renovación de sistema de negocios en sql, by EdinsonWalker (23/01/2020)

new neg_automatico[11]; //sistema de cobro productos-ganancia

enum negocioInfo
{
	nID_sql,								// id sql
	nNombre[32],                            // nombre
	nPropietario[MAX_PLAYER_NAME],          // propietario
	nVenta,                                 // venta
	nTipo,                                  // tipo
	nPrecio,                                // precio
	Float: nExteriorX,                      // exterior x
	Float: nExteriorY,                      // exterior y
	Float: nExteriorZ,                      // exterior z
	Float: nExteriorR,                      // exterior r
	nExteriorInt,                           // exterior int
	nExteriorVW,                            // exterior vw
	Float: nInteriorX,                      // interior x
	Float: nInteriorY,                      // interior y
	Float: nInteriorZ,                      // interior z
	Float: nInteriorR,                      // interior r
	nInteriorInt,                           // interior int
	nInteriorVW,                            // interior vw
	Float: nLugarCompraX,                   // lugar de comprar x
	Float: nLugarCompraY,                   // lugar de comprar y
	Float: nLugarCompraZ,                   // lugar de comprar z
	nSeguro,                                // seguro
	nDinero,                                // dinero
	nProductos,                             // productos
	nMapIcon,                               // mapicon
	Float: nActorX,                         // actor x
	Float: nActorY,                         // actor y
	Float: nActorZ,                         // actor z
	Float: nActorR,                         // actor r
	nActorSkin,                             // actor skin
	//concesionario
	Float: nVehicleX,                       // entrega vehiculo x
	Float: nVehicleY,                       // entrega vehiculo y
	Float: nVehicleZ,                       // entrega vehiculo z
	Float: nVehicleR,                       // entrega vehiculo r
	//mecánico
	nPrecioPintura,
	nPrecioPaintJob,
	nPrecioReparacion,
	nPrecioGasolina,
	nPrecioLlantas,
	nPrecioNitro,
	nPrecioHyd,
	nPrecioTuneo,
	nTiempoDisponible,
	//llaves
	nCompartida1[MAX_PLAYER_NAME],
	nCompartida2[MAX_PLAYER_NAME],
	nCompartida3[MAX_PLAYER_NAME],
	//dynamic
	Text3D: nExteriorLabel,                 // exterior label
	nExteriorPickup,                        // exterior pickup
	nExteriorMapIcon,                       // exterior mapicon
	Text3D: nInteriorLabel,                 // interior label
	nInteriorPickup,                        // interior pickup
	nInteriorActor,                         // interior actor
	Text3D: nLugarCompraLabel,              // lugar de comprar label
	nVeh1SinUso,
	nVeh2SinUso,
	EnLlamas,                           // Con incendio
}
new InfoNegocio[MAX_NEGOCIOS][negocioInfo];