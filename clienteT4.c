#include <stdio.h>
#include <atmi.h>
#include <fml32.h>	
#include <string.h>
#include "bib_T4.fml.h"	

typedef struct Autos{
   int autoID;
   int marcaID;
   char modelo[51];
   char anio[10];
   double precio;
   int stock;
}Autos;


typedef struct marca{
   int marcaID;
   char nombre[50];
   char Orig_Pais[50];
}marca;


typedef struct clientes{
    int clienteID;
    char nombre[50];
    char apellido [50];
    char direccion[100];
    char telefono[15];
}clientes; 

typedef struct ventas{
   int ventaID;
   int clienteID;
   int autoID;
   double precio; 
}ventas;


 

	

int main(int argc, char **argv){
   int opc;

   /* Menu de opciones que se pueden realizar en el codigo*/
   printf("\n*************************************************\n");
   printf("Menu de opciones\n");
   printf("\n*************************************************\n");
   printf("1. Tabla de marcas (SELECT)\n");
   printf("2. Tabla de autos (INSERT)\n");
   printf("3. Tabla de clientes(UPDATE)\n");
   printf("4. Tabla de ventas (DELETE)\n");
   printf("\n*************************************************\n");
   printf("Opción: "); scanf("%d",&opc);
   switch(opc){
      case 1:
      	printf("Seleccion - Lista de marcas(SELECT).\n");
	clientSelect_AgenciaAutos();
      	break;
      case 2:
      	printf("Seleccion - Lista autos(INSERT)\n");
	clientInsert_AgenciaAutos();
      	break;
      case 3:
      	printf("Seleccion - Lista de clientes(UPDATE).\n");
        clientUpdate_AgenciaAutos();
      	break;
      case 4:
      	printf("Seleccion - Lista de ventas(DELETE).\n");
        clientDelete_AgenciaAutos();
      	break;

   }
   return 0;
}

int clientSelect_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];
   char pais_marca[51];
   marca *marcaRegis;
   marca marcas;
   int ivL_numOcurr;
   int ivl_iterador;

   printf("*************************************************\n");
   printf("Se imprimiran las marcas del pais que ingrese \n");
   printf("Pais : "); scanf("%s", pais_marca);
   printf("*************************************************\n");

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n");
   if (tpinit((TPINIT *) NULL) == -1){
       printf("Error en la conexion, tperrno = %d \n", tperrno);
       return (1);
   }

   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("Error Reservando espacio para Buffer fbfr\n");
       tpterm();
       return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
       printf("ErrorReservando espacio para Buffer recv\n");
       tpterm();
       return(1);
   }
   /* Manejo del Buffer FML */
   if(Fadd32 (fbfr, PAIS, pais_marca, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOR)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   // Invocamos el servicio 
   printf("Llamada al servicio 'SELECT_AgenciaAutos'\n");
   if(tpcall("SELECT_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L)==-1){
      printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1);
   }

   if((ivL_numOcurr = Foccur32(recv, MARCAID)) < 0) {
      printf("Error en Foccur32\n");
      tpfree((char *)fbfr);
      tpfree((char *)recv);
      tpterm();
      return (1); 
   }

   printf("Numero de ocurrencias: %d\n", ivL_numOcurr);
   marcaRegis = (marca *) malloc(sizeof(marca) * ivL_numOcurr);

  flen = sizeof(msgbuf);
  printf("Respuesta del servidor para el pais: %s\n", pais_marca);
  printf("***************************************************\n");
  for(ivl_iterador = 0;ivl_iterador < ivL_numOcurr; ivl_iterador++) {
      Fget32(recv, MARCAID, ivl_iterador, (char *)&marcaRegis[ivl_iterador].marcaID,0);
      printf("Nombre de la marca : %d\n", marcaRegis[ivl_iterador].marcaID);
      Fget32(recv, NOMBRE, ivl_iterador, (char *)marcaRegis[ivl_iterador].nombre,0);
      printf("NOmbre del pais de origen : %s\n", marcaRegis[ivl_iterador].nombre);
      Fget32(recv, PAIS, ivl_iterador, (char *)marcaRegis[ivl_iterador].Orig_Pais,0);
      printf("NOmbre del pais de origen : %s\n", marcaRegis[ivl_iterador].Orig_Pais);

   }
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}

int clientInsert_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   Autos carro;
  
   printf("\n*************************************************\n");
   printf("Auto ID : "); scanf("%d", &carro.autoID);
   printf("Marca ID : "); scanf("%d", &carro.marcaID);
   printf("Modelo : "); scanf("%s", carro.modelo);
   printf("Anio : "); scanf("%s", carro.anio);
   printf("Precio : "); scanf("%lf", &carro.precio);
   printf("Stock : "); scanf("%d", &carro.stock);
   printf("\n*************************************************\n");


   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, AUTOID, (char *)&carro.autoID, 0) < 0) {
      printf ("\n\tError insertando campo FML (AUTOID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MARCAID, (char *)&carro.marcaID, 0) < 0) {
      printf ("\n\tError insertando campo FML (MARCA)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, MODELO, (char *)&carro.modelo, 0) < 0) {
      printf ("\n\tError insertando campo FML (MODELO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, ANIO, (char *)&carro.anio, 0) < 0) {
      printf ("\n\tError insertando campo FML (ANIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, PRECIO, (char *)&carro.precio, 0) < 0) {
      printf ("\n\tError insertando campo FML (PRECIO)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, STOCK, (char *)&carro.stock, 0) < 0) {
      printf ("\n\tError insertando campo FML (STOCK)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }


   //Invocamos el servicio
   printf("Llamada al servicio 'INSERT_AgenciaAutos'\n");
   if (tpcall("INSERT_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}


int clientUpdate_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   clientes client;
  
   printf("\n*************************************************\n");
   printf("Ingrese su ID de cliente: "); scanf("%d", &client.clienteID);
   printf("Cual es la direccion que desea actualizar. ");
   printf("Dirección: "); scanf("%s", client.direccion);
   printf("\n*************************************************\n");


   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, CLIENTE, (char *)&client.clienteID, 0) < 0) {
      printf ("\n\tError insertando campo FML (CLIENTE ID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   if(Fadd32 (fbfr, DIRECC, (char *)&client.direccion, 0) < 0) {
      printf ("\n\tError insertando campo FML (DIRECCION)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   
   //Invocamos el servicio
   printf("Llamada al servicio 'UPDATE_AgenciaAutos'\n");
   if (tpcall("UPDATE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}


int clientDelete_AgenciaAutos(){
   int ivL_resLlamd;
   long lvL_tamLongt;
   float fvL_recValor;
   FBFR32 *fbfr;
   FBFR32 *recv;
   FLDLEN32 flen;
   char msgbuf[64];

   /* Inicializamos una referencia bibliografica */
   ventas venta;
  
   printf("\n*************************************************\n");
   printf("Ingrese su ID de la venta que desea eliminar: \n");
   printf("ID Venta: "); scanf("%d", &venta.ventaID);
   printf("\n*************************************************\n");

   /* Conectamos con la aplicacion Tuxedo Server */
   printf ("Conectamos con la aplicacion\n") ;
   if (tpinit((TPINIT *) NULL) == -1){
      printf("Error en la conexion, tperrno = %d \n", tperrno);
      return (1) ;
   }
   // Reservamos espacio para el buffer FML
   printf ("Reservamos Espacio para los buffers FML\n");
   if ((fbfr = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer fbfr\n");
      tpterm();
      return(1);
   }
   if ((recv = (FBFR32 *) tpalloc("FML32", NULL, 1024)) == NULL){
      printf("Error Reservando espacio para Buffer recv\n");
      tpterm();
      return(1);
   }
   /* Manejo del Buffer FML */
   printf ("\nInsertamos datos en buffer FML.");
   if(Fadd32 (fbfr, VENTA, (char *)&venta.ventaID, 0) < 0) {
      printf ("\n\tError insertando campo FML (VENTA ID)");
      tpfree((char*)fbfr);
      tpterm();
      return (0);
   }
   
   //Invocamos el servicio
   printf("Llamada al servicio 'DELETE_AgenciaAutos'\n");
   if (tpcall("DELETE_AgenciaAutos", (char *)fbfr, 0, (char **)&recv, &lvL_tamLongt, 0L) == -1){
       printf("Error en la llamada al servicio: tperrno = %d\n", tperrno);
       tpfree((char *)fbfr);
       tpfree((char *)recv);
       tpterm();
       return (1);
   }
   flen = sizeof(msgbuf);
   Fget32(recv, OUTPUT, 0, (char *)msgbuf, &flen);
   printf("Respuesta del servidor: %s\n", msgbuf);
   
   // Liberamos el buffer y desconectamos de la aplicacion
   printf("Liberamos Buffer y desconectamos de la aplicacion\n");
   tpfree((char *)fbfr);
   tpfree((char *)recv);
   tpterm();
   return 0;
}
