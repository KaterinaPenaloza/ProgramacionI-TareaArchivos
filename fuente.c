//Katerina Peñaloza Caballeria	Paralelo 1
//Raul Arteaga Nuñez Paralelo 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Declaracion de Funciones
float porcentaje(int a,int b);
int lineas(FILE *archivo);
int main(){
//variables
int si=1;
int n, m;
int lugar;
int tiempo;
int dias=0;
int tarifa=0;
int fraccion=0;
int total_dinero=0;
int total_autos=0;
int total_motos=0;
int total_camiones=0;
int total_vehiculos=0;
int mayor_dinero=0;
int mayor_dinero_aux=0;
int mejor_cliente;
//Archivo de entrada
FILE *simulacion;
simulacion = fopen("simulacion.in", "r");
//Contador de lineas
int num_lineas = lineas(simulacion);
//Estructura en la que se guardaran los datos del archivo
struct tiempo{
	int hora;
	int minuto;
	int segundo;
};
struct entrada{
	char ESN[2];				//entrada, salida o next day
	char AMC[2];				//auto, moto o camion
	char PATENTE[7];			//6 digitos alfanumericos
	struct tiempo horas;		//hora en formato militar
};
struct entrada entrada[num_lineas];
//Introduccion de n y m
printf("Ingrese el numero de puestos para camiones:\n");
scanf("%i", &n);
printf("Ingrese el numero de pisos:\n");
scanf("%i", &m);
if(n<=0 || m<=0) printf("Debe ingresar un numero mayor a 0");
else{
	//Numero de puestos
	int puestos_camiones = n;
	int puestos_autos = n*m;
	int puestos_motos = n*3;
	//Bienvenida
	printf("Bienvenido al estacionamiento APARCAME\n");
	if(simulacion != NULL){
		/*****Creacion del estacionamiento*****/
		//Archivo Salida
		FILE *ocupacion;
		ocupacion = fopen("ocupacion.out", "w");
		//Estructura estacionamiento
		struct estacionamiento{
			int puesto;
			int piso;
			char patente[7];
			struct tiempo;
			int days;
		};
		struct estacionamiento estacionamiento_motos[n*3];
		struct estacionamiento estacionamiento_autos[n][m];
		struct estacionamiento estacionamiento_camiones[n];
		//Creacion de puestos y pisos
		for(int a=0;a<n;a++){
			estacionamiento_camiones[a].puesto = a;
			estacionamiento_camiones[a].piso = 0;
			strcpy(estacionamiento_camiones[a].patente,"D ");
		}
		int b;
		for(int a=0;a<n;a++){
			for(int b=0;b<m;b++){
				estacionamiento_autos[a][b].piso = b;
				estacionamiento_autos[a][b].puesto= a;
				strcpy(estacionamiento_autos[a][b].patente,"D ");
				
			}
		}
		for(int a=0;a<(n*3);a++){
			estacionamiento_motos[a].puesto = a;
			estacionamiento_motos[a].piso = n-1;
			strcpy(estacionamiento_motos[a].patente,"D ");
		}

		for(int i=0;i<num_lineas;i++){
			//Escanear los datos
			fscanf(simulacion, "%s", entrada[i].ESN);
			//Si hay nuevo dia
				if(entrada[i].ESN[0] == 'N'){
					dias+=24;
					printf("**********************************************\n");
					printf("Nuevo Dia\n");
					printf("Hay %i autos estacionados\n", ((n*m)-puestos_autos));
					printf("Hay %i camiones estacionados\n", ((n)-puestos_camiones));
					printf("Hay %i motos estacionadas\n", ((n*3)-puestos_motos));
					printf("Monto total hasta el momento: %i pesos\n", total_dinero);
					printf("**********************************************\n");
					system("pause");			
					continue;
				}
			fscanf(simulacion, "%s", entrada[i].AMC);
			fscanf(simulacion, "%s", entrada[i].PATENTE);
			fscanf(simulacion, "%i:%i:%i\n", &entrada[i].horas.hora, &entrada[i].horas.minuto, &entrada[i].horas.segundo);

			//Salida de vehiculos
			if(entrada[i].ESN[0] == 'S'){
				//Verificar la patente
				for(int j=0; j<i;j++){
					if((entrada[i].PATENTE[0] == entrada[j].PATENTE[0])
					&&(entrada[i].PATENTE[1] == entrada[j].PATENTE[1])
					&&(entrada[i].PATENTE[2] == entrada[j].PATENTE[2])
					&&(entrada[i].PATENTE[3] == entrada[j].PATENTE[3])
					&&(entrada[i].PATENTE[4] == entrada[j].PATENTE[4])
					&&(entrada[i].PATENTE[5] == entrada[j].PATENTE[5])
					&&(entrada[i].PATENTE[6] == entrada[j].PATENTE[6])){
						si=1;
						lugar=j;
						break;
					}
					else{
						si=-1;
					}
				}
				if(si==1){
					printf("Adios %s\n", entrada[i].PATENTE);
					//liberar el espacio en el estacionamiento y cobrar
					if(entrada[i].AMC[0] == 'A'){
						tarifa= 2000;
						//tiempo en el lugar
						if((entrada[i].horas.minuto)>=30){
							fraccion=1;
						}
						else{
							fraccion=0;
						}
						tiempo = ((entrada[i].horas.hora) - (entrada[lugar].horas.hora)) + dias + fraccion;
						tarifa *= tiempo;
						printf("Horas transcurridas: %i \n", tiempo);
						printf("Su tarifa es: %i pesos\n", tarifa);
						tiempo=0;
						//Calculo del mejor cliente
						mayor_dinero_aux = tarifa;
						if(mayor_dinero_aux > mayor_dinero){
							mayor_dinero = mayor_dinero_aux;
							mejor_cliente = i;
						}
						puestos_autos++;
						total_dinero+=tarifa;
					}
					if(entrada[i].AMC[0] == 'M'){
						tarifa=500;
						//tiempo en el lugar
						if((entrada[i].horas.minuto)>=30){
							fraccion=1;
						}
						else{
							fraccion=0;
						}
						tiempo = ((entrada[i].horas.hora) - (entrada[lugar].horas.hora)) + dias + fraccion;
						tarifa *= tiempo;
						printf("Horas transcurridas: %i \n", tiempo);
						printf("Su tarifa es: %i pesos\n", tarifa);
						tiempo=0;
						//Calculo del mejor cliente
						mayor_dinero_aux = tarifa;
						if(mayor_dinero_aux > mayor_dinero){
							mayor_dinero = mayor_dinero_aux;
							mejor_cliente = i;
						}
						puestos_motos++;
						total_dinero+=tarifa;
					}
					if(entrada[i].AMC[0] == 'C'){ 
						tarifa=1000;
						//tiempo en el lugar
						if((entrada[i].horas.minuto)>=30){
							fraccion=1;
						}
						else{
							fraccion=0;
						}
						tiempo = ((entrada[i].horas.hora) - (entrada[lugar].horas.hora)) + dias + fraccion;
						tarifa *= tiempo;
						printf("Horas transcurridas: %i \n", tiempo);
						printf("Su tarifa es: %i pesos\n", tarifa);
						tiempo=0;
						//Calculo del mejor cliente
						mayor_dinero_aux = tarifa;
						if(mayor_dinero_aux > mayor_dinero){
							mayor_dinero = mayor_dinero_aux;
							mejor_cliente = i;
						}
						puestos_camiones++;
						total_dinero+=tarifa;
					}
				}
				else{
					printf("El vehiculo no se encuentra en el estacionamiento\n");
				}
			}
			//Verificar disponibilidad
			if(puestos_camiones==0 && entrada[i].AMC[0] == 'C'){
				printf("No hay disponibilidad por el momento\n");
				continue;
			}
			if(puestos_autos==0 && entrada[i].AMC[0] == 'A'){
				printf("No hay disponibilidad por el momento\n");
				continue;
			}
			if(puestos_motos==0 && entrada[i].AMC[0] == 'M'){
				printf("No hay disponibilidad por el momento\n");
				continue;
			}
			//Entrada de vehiculos
			else{
				if(entrada[i].ESN[0] == 'E'){
					printf("Bienvenido %s \n", entrada[i].PATENTE);
					if(entrada[i].AMC[0] == 'C'){
						printf("Quedan %i puestos disponibles para camiones\n", puestos_camiones);
						//entrar al estacionamiento
						for(int z=0;z<n;z++){
							if(estacionamiento_camiones[z].patente[0] == 'D' && estacionamiento_camiones[z].patente[1] == ' '){
								printf("Su puesto es el %i \n", z);
								strcpy(estacionamiento_camiones[z].patente,entrada[i].PATENTE);
								break;
							}
							else{
								continue;
							}
						}
						puestos_camiones--;
						total_camiones++;
						total_vehiculos++;
					}
					if(entrada[i].AMC[0] == 'A'){
						printf("Quedan %i puestos disponibles para autos\n", puestos_autos);
						puestos_autos--;
						total_autos++;
						total_vehiculos++;
					}
					if(entrada[i].AMC[0] == 'M'){
						printf("Quedan %i puestos disponibles para motos\n", puestos_motos);
						//entrar al estacionamiento
						for(int z=0;z<(n*3);z++){
							if(estacionamiento_motos[z].patente[0] == 'D' && estacionamiento_motos[z].patente[1] == ' '){
								printf("Su puesto es el %i \n", z);
								strcpy(estacionamiento_motos[z].patente,entrada[i].PATENTE);
								break;
							}
							else{
								continue;
							}
						}
						puestos_motos--;
						total_motos++;
						total_vehiculos++;
					}	
				}
			}
			printf("\n");
			system("pause");
			printf("\n");

			//Escritura del archivo de salida
			for(int a=0;a<n;a++){
				fprintf (ocupacion, "%i " , estacionamiento_camiones[a].puesto);
				fprintf(ocupacion, "%s ", estacionamiento_camiones[a].patente);
				fprintf(ocupacion, "\n");
			}
			for(int b=0;b<m;b++){
				for(int a=0;a<n;a++){
					fprintf(ocupacion, "%i ", estacionamiento_autos[a][b].piso);
					fprintf(ocupacion, "%i ", estacionamiento_autos[a][b].puesto);
					fprintf(ocupacion, "%s ", estacionamiento_autos[a][b].patente);
					fprintf(ocupacion, "\n");
				}
			}
			for(int a=0;a<(n*3);a++){
				fprintf(ocupacion, "%i ", estacionamiento_motos[a].puesto);
				fprintf(ocupacion, "%s ", estacionamiento_motos[a].patente);
				fprintf(ocupacion, "\n");
			}
			fclose(ocupacion);
		}
	}
	else printf("Hubo un error en la lectura del archivo");
	}
fclose(simulacion);
//Estadisticas
printf("Fin de la simulacion.\n\n");
printf("********** Estadisticas generales **********\n\n");
printf("Total dinero recaudado: %i\n", total_dinero);
printf("Total de vehiculos estacionados: %i\n", total_vehiculos);
printf("Total de autos estacionados: %i\n", total_autos);
printf("Proporcion: %i de %i, un %.1f%%\n", total_autos, total_vehiculos, porcentaje(total_autos,total_vehiculos));
printf("Total de camiones estacionados: %i\n", total_camiones);
printf("Proporcion: %i de %i, un %.1f%%\n", total_camiones, total_vehiculos, porcentaje(total_camiones,total_vehiculos));
printf("Total de motos estacionados: %i\n", total_motos);
printf("Proporcion: %i de %i, un %.1f%%\n", total_motos, total_vehiculos, porcentaje(total_motos,total_vehiculos));
printf("El mejor es: %s \n", entrada[mejor_cliente].PATENTE);
//Mostrar la ocupacion en pantalla
printf("Estado de ocupacion\n");
FILE *ocupacion_r;
ocupacion_r = fopen("ocupacion.out", "r");
char texto;
while ((texto = getc(ocupacion_r)) != EOF){
    printf("%c", texto);
}
return 0;
}
//Cuerpo de las Funciones
float porcentaje(int a,int b){
	float porcentaje;
	porcentaje = (float)a/(float)b;
	porcentaje*=100;
	return porcentaje;
}
int lineas(FILE *archivo) {
  int lineas = 1;
  char c;
  while ((c = getc(archivo)) != EOF) {
    if (c == '\n')
      lineas++;
  }
  rewind(archivo);
  return lineas;
}