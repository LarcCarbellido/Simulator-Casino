#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define true 1
#define false 0

typedef unsigned short int bool;

char * csv[312][3];
char * csvcomplete[312][501];
float ConfigMemo[15][12];

//Contadores de dinero para Giros Gratis y Giros Normales
double freespinmoney = 0;
unsigned long freespin = 0;
double onlymachine = 0;
double money = 0;
int gamesCount = 0;

double gameMoney = 0;
int matrizMiniJuego[12][12];
int numColsMinijuego = 0;
int numRenglonesMatrizMinijuego = 0;
double sumtmp = 0;
float byline = 0;
int fourhilo = 0;
char *csvproba[312];
int fivehilo = 0;
int lineasmax = 0;
unsigned short int debugMode;
unsigned long iteraciones;
unsigned long iteracionesreales = 0;
unsigned long iteratest = 0;


unsigned long girosFree = 0;

int extreFree = 0;

double contadorGames = 0;
double extramoney = 0;

double dineroExtra = 0;

unsigned long juegoEnOtro = 0;
double varoEnOtro = 0;
unsigned long bigwin = 0;
unsigned long superwin = 0;
unsigned long megawin = 0;

unsigned long juegox3 = 0;
unsigned long juegox4 = 0;
unsigned long juegox5 = 0;

double varoEn3 = 0;
double varoEn4 = 0;
double varoEn5 = 0;

unsigned long testvar = 0;

unsigned long girosGratisNormal = 0;
unsigned long girosGratisJuego = 0;
unsigned long girosGratisOrdinario = 0;







//----------------------------------------------------------------------------------

void sumatodalalinea(int val)
{
    int suma = 0;
    int z = 0;
    for(z = 0;z<=numColsMinijuego;z++){
        if(matrizMiniJuego[val][z]>=0){
            suma = suma+matrizMiniJuego[val][z];
        }
    }
    sumtmp = sumtmp+suma;
}
//----------------------------------------------------------------------------------
//Simulacion MicroJuego
double simulacion(double percent)
{
	//printf("\nsimulacion:: numRenglonesMatrizMinijuego:%f",numRenglonesMatrizMinijuego);
    double coins = 0;
    int life = 0;
    int x,z;
    int azar;
    for(x=0;x<1;x++){
    	sumtmp = 0;
        for(z=0;z<numRenglonesMatrizMinijuego;z++){
            azar = (rand() % numColsMinijuego);
            switch(matrizMiniJuego[z][azar]) {
               case -1:
            	   ///Gana toda la linea
            	   sumatodalalinea(z);
            	   break;
               case 0:
                   life = life+1;
                   //Pierde toda la linea
                   break;
               default:
            	   sumtmp += matrizMiniJuego[z][azar];
             };

            if(life==1){
            	life = 0;
                break;
             }
        }

        sumtmp = (sumtmp)*percent;
        coins += sumtmp;
    }
    gameMoney += coins;
    return coins;
}

//----------------------------------------------------------------------------------
//######Incluir despues maxHits en juegox5,juegox4,juegox3,GRATISx5,GRATISx4,GRATISx3,ANT_GRATISx3,ANT_GRATISx4,ANT_GRATISx5
void readCSV(int lineas, char *fileName,int arraypos,int freespinactive){
	int contb = 0;
	int azar = 0;
	char * libro[501];
	char *cad;

	//printf("freespin readcsv:%i\n",freespinactive);

	/*30-49 BuenPremio
	50-79 MegaPremio
	80-300 Premio Mayor*/

	if(arraypos >= 79 && arraypos<=299){
		//printf("freespin readcsv:%s\n",fileName);
		if(freespinactive){
			testvar++;
		}
		megawin++;
	}
	if(arraypos >= 49 && arraypos<=78){
		superwin++;
	}
	if(arraypos >= 29 && arraypos<=48){
		bigwin++;
	}

	/*if(arraypos>=300){
		printf("arraypos :%i\n",arraypos);
		printf("arraypos :%s\n",fileName);
	}*/

	contb = atoi(csvcomplete[arraypos][1]);
	int mf;
	for(mf=0; mf<contb; mf++) {
		int sumarmf = mf+2;
		libro[mf] = csvcomplete[arraypos][sumarmf];

		/*cad = (char*)malloc(100*sizeof(char));
		strcpy(cad, csvcomplete[arraypos][sumarmf]);
		libro[mf] = (char*)cad;*/
	}

	azar = (rand() % contb);

	int contw = contb;
	//char *line = libro[azar];

	cad = (char*)malloc(300*sizeof(char));
	strcpy(cad, libro[azar]);
	char *line =cad;


	char* tok;
	contb = 0;
	float ganaste = 0;
	int columna = 0;
	//printf("filename:%s\n",fileName);

	for (tok = strtok(line, "\""); tok && *tok; tok = strtok(NULL, ",\n")) {
		columna++;
		if ( ( columna == 1 ) && ( !debugMode ) ){
			printf("%s\n",tok);
		}
		//el archivo pertenece3 a giros gratis
		if(strcmp(fileName,"GRATISx3") == 0 || strcmp(fileName,"GRATISx4") == 0 || strcmp(fileName,"GRATISx5") == 0 || strcmp(fileName,"ANT_GRATISx3") == 0 || strcmp(fileName,"ANT_GRATISx4") == 0 || strcmp(fileName,"ANT_GRATISx5") == 0) {
			//es el campo max hits
			//printf("filename:%s\n",fileName);
			//Buscamos si el giro gratis contiene una linea ganadora
			if(columna == 2){
				if(atoi(tok)!=0){
					//dineroExtra = atoi(tok);
					if(freespinactive){
						freespinmoney = freespinmoney+atoi(tok);
					}else{
						onlymachine = onlymachine+atoi(tok);
					}
					money = money+atoi(tok);
				}
			}

			//buscamos si El giro gratis contiene algun juego
			if(columna == 4){
				if(atoi(tok)!=0){
					double simulacionPremio = simulacion(ConfigMemo[0][2+atoi(tok)]);
					if(atoi(tok)==1){
						varoEn3 += simulacionPremio;
						juegox3++;
					}else if(atoi(tok)==2){
						varoEn4 += simulacionPremio;
						juegox4++;
					}else if(atoi(tok)==3){
						varoEn5 += simulacionPremio;
						juegox5++;
					}

					money = money+simulacionPremio;
					gamesCount = gamesCount+1;
					juegoEnOtro = juegoEnOtro+1;
					varoEnOtro = varoEnOtro+simulacionPremio;
				}
			}
		//el archivo pertenece a juegos (ruleta)
		}else if(strcmp(fileName,"JUEGOx3") == 0 || strcmp(fileName,"JUEGOx4") == 0 || strcmp(fileName,"JUEGOx5") == 0){
			//es el campo max hits
			//Buscamos si el Juego contiene una linea ganadora
			if(columna == 2){
				if(atoi(tok)!=0){
					//dineroExtra = atoi(tok);
					if(freespinactive){
						freespinmoney = freespinmoney+atoi(tok);
					}else{
						onlymachine = onlymachine+atoi(tok);
					}
					money = money+atoi(tok);
				}
			}




			//buscamos si el juego contiene algun giro gratis
			if(columna == 3){

				if(atoi(tok)==3){
					//printf( "Giros Gratis X3 %s\n",tok);
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][2];
						iteraciones += (unsigned long)ConfigMemo[1][2];
						girosFree++;
						girosGratisJuego++;
					}
				}else if(atoi(tok)==4){
					//printf( "Giros Gratis X4 %s\n",tok);
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][3];
						iteraciones += (unsigned long)ConfigMemo[1][3];
						girosFree++;
						girosGratisJuego++;
					}
				}else if(atoi(tok)==5){
					//printf( "Giros Gratis X5 %s\n",tok);
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][4];
						iteraciones += (unsigned long)ConfigMemo[1][4];
						girosFree++;
						girosGratisJuego++;
					}
				}
			}

		}else{


			//Giros Gratis Extra en un grupo factor cualquiera, no grupo especial
			if(columna == (lineasmax+3)){
				if(atoi(tok)!=0){
					//printf( "Giros Gratis Extra %s\n",tok);
					if(debugMode){
						if(atoi(tok)==3){
							if(debugMode){
								freespin += (unsigned long)ConfigMemo[1][2];
								iteraciones += (unsigned long)ConfigMemo[1][2];
								girosFree++;
								girosGratisNormal++;
							}
						}else if(atoi(tok)==4){
							if(debugMode){
								freespin += (unsigned long)ConfigMemo[1][3];
								iteraciones += (unsigned long)ConfigMemo[1][3];
								girosFree++;
								girosGratisNormal++;
							}
						}else if(atoi(tok)==5){
							if(debugMode){
								freespin += (unsigned long)ConfigMemo[1][4];
								iteraciones += (unsigned long)ConfigMemo[1][4];
								girosFree++;
								girosGratisNormal++;
							}
						}
					}
				}
			}

			//Juegos gratis
			if(columna == (lineasmax+4)){
			//printf( "Juegos Gratis %s\n",tok);
				if(atoi(tok)!=0){
					if(debugMode){
						if(atoi(tok)!=0){
							double simulacionPremio = simulacion(ConfigMemo[0][2+atoi(tok)]);

							if(atoi(tok)==1){
								varoEn3 += simulacionPremio;
								juegox3++;
							}else if(atoi(tok)==2){
								varoEn4 += simulacionPremio;
								juegox4++;
							}else if(atoi(tok)==3){
								varoEn5 += simulacionPremio;
								juegox5++;
							}

							money = money+simulacionPremio;
							gamesCount = gamesCount+1;
						}
						/*double simulacionPremio = simulacion(atof(tok));
						extramoney += simulacionPremio;
						//printf("JUEGOx3 FIN %f\n\n", simulacionPremio);
						contadorGames = 1;*/
					}
				}

			}


			//######Incluir despues maxHits en juegox5,juegox4,juegox3,GRATISx5,GRATISx4,GRATISx3,ANT_GRATISx3,ANT_GRATISx4,ANT_GRATISx5

			//revisar 4 o 4 hits (al hilo, in a row)
	    	if(columna==2 && debugMode){
				if(strcmp(fileName,"JUEGOx5") != 0 && strcmp(fileName,"JUEGOx4") != 0 && strcmp(fileName,"JUEGOx3") != 0 && strcmp(fileName,"GRATISx5") != 0 && strcmp(fileName,"GRATISx4") != 0 && strcmp(fileName,"GRATISx3") != 0 && strcmp(fileName,"CEROCASIx3") != 0 && strcmp(fileName,"CEROCASIx4") != 0 && strcmp(fileName,"ANT_GRATISx2") != 0  && strcmp(fileName,"ANT_GRATISx3") != 0  && strcmp(fileName,"ANT_GRATISx4") != 0  && strcmp(fileName,"ANT_GRATISx5") != 0) {
					if(atoi(tok) == 4){
						//printf("\n%s .. %s :: columna %d fouralhilo::%s\n",fileName,line,columna,tok);
						fourhilo++;
						//printf("columna %d\n",fourhilo);
					}
					if(atoi(tok) == 5){
						//printf("\n%s ..%s :: columna %d fivealhilo::%s\n",fileName,line,columna,tok);
						fivehilo++;
					}
				}

	    	}
		}

    	//printf( "contb %d\n",contb);
		//columna==1 es la posicion donde viene el maxhits de la linea

    	/*if(contb>=2){
	    	//printf( "El csv tiene %.2f\n",atof(tok));
	    	ganaste += atof(tok);
	    	if(contb==(lineas+1)){
	    		break;
	    	}
	    }*/

    }
	free(cad);
}

//----------------------------------------------------------------------------------
int main(int argc, char *argv[]){
	if (argc != 5){
		printf( "Uso: Simulador Iteraciones Numero-de-Lineas Maquina(1-12) modo-simulacion(0-1) \n");
		return 0;
	}
	debugMode = atoi(argv[4]);

	if( debugMode ){
		printf( "***** Simulacion en curso ***** \n\n");
	}
	iteraciones = atoi(argv[1]);
	//printf("Iteraciones en curso****** %lu\n",iteraciones);

	int maxline = atoi(argv[2]);
	lineasmax = maxline;
	int machine = atoi(argv[3]);
	double iterabackup = 0;

	//Datos que necesito del usuario para hacer la simulacion freespin,maxline,byline

	char rutaCfg[50] = "machine/";
	char extensionTxt[13] = "/general.txt";

	strcat(rutaCfg,argv[3]);
	strcat(rutaCfg,extensionTxt);

	printf("\nabrir %s\n",rutaCfg);
	FILE* configFile = fopen(rutaCfg, "r");

	char Configline[5];

	int lineaDeArchivoDeConfig = 0;
	int maxlinLimit = 0;
	char* cfgtok;
	int columnaDeArchivoDeConfig = 0;

	//ciclo para leer el archivo de configuracion
	while (fgets(Configline, 1024, configFile)) {
		//printf("Configline ----------%s",Configline);
		columnaDeArchivoDeConfig = 0;
		//ciclo para separar los valores en cada linea, usando la coma como delimitador
		for (cfgtok = strtok(strdup(Configline), ","); cfgtok && *cfgtok; cfgtok = strtok(NULL, ",\n")) {
			//si es la primera linea, contiene unicamente el numero de lineas
			if(lineaDeArchivoDeConfig==0){
				maxlinLimit = atoi(cfgtok);
			//si es la segunda linea, contiene el paytable de los minijuegos
			}else if(lineaDeArchivoDeConfig==1){
				ConfigMemo[(lineaDeArchivoDeConfig-1)][columnaDeArchivoDeConfig] = atof(cfgtok);
			//si es la 3a linea, contiene el paytable de los giros gratis
			}else if(lineaDeArchivoDeConfig==2){
				ConfigMemo[(lineaDeArchivoDeConfig-1)][columnaDeArchivoDeConfig] = atof(cfgtok);
			//es la cuarta linea, contiene la configuracion del minijuego
			}else{
				matrizMiniJuego[(lineaDeArchivoDeConfig-3)][columnaDeArchivoDeConfig] = atoi(cfgtok);
				//printf("matrizMiniJuego1 %i\n",matrizMiniJuego[0][0]);
				//solo en la primera linea del archivo calcula el numero de columnas de los minijuegos
				if(lineaDeArchivoDeConfig==3){
					numColsMinijuego++;
				}
			}
			columnaDeArchivoDeConfig++;
		}
		lineaDeArchivoDeConfig++;
	}
	//fin del ciclo,se leyo el archivo de configuracion, ConfigMemo trae los valores de los paytables
	// y matrizMiniJuego la de los minijuegos

	numRenglonesMatrizMinijuego = (lineaDeArchivoDeConfig-3);
	//printf("Arreglo conteo %d\n",numRenglonesMatrizMinijuego);

	char rutaCsv[50] = "machine/";
	//Table.csv tabla de probabilidades
	char extensionCsv[12] = "/Table.csv";
	strcat(rutaCsv,argv[3]);
	strcat(rutaCsv,extensionCsv);
	FILE* archivoTablaProbabilidades = fopen(rutaCsv, "r");

	if (archivoTablaProbabilidades == NULL){
		printf("Error Al abrir Table %s\n",rutaCsv);
	}

	short payLines[50][5];
	char lineaTablaProbabilidades[1024];
	int totalAzarB = 0;
	int totalAzar = 0;
	int contadorGrupos = 0;
	unsigned long girosGanados = 0;
	//freespin contiene el numero de giros gratis disponibles



	//variable Solo para simulacion

	int contadorparcial = 0;
	byline = 1;

	int apuestagral = byline*maxline;
	//+++++++++++++++
	int acumula = 0;


	int ceroCasitre = 0;
	int ceroCasifour = 0;
	int antgratis2 = 0;


	double dineroperdido = 0;
	unsigned long originalIteracion = iteraciones;
	unsigned long ceros = 0;



	unsigned long juegoEnFreespin = 0;
	unsigned long juegoNoEnFreespin = 0;



	bool freespinon = false;
	char *tokProba;
	int columnaTablaProbabilidades = 0;
	//printf("Error Al abrir Table %s\n",rutaCsv);
	//ciclo para leer la tabla de probabilidades que genera ricardo
	while (fgets(lineaTablaProbabilidades, 1024, archivoTablaProbabilidades)) {
		csvproba[contadorGrupos] =  strdup(lineaTablaProbabilidades);
		columnaTablaProbabilidades = 0;
		for (tokProba = strtok(csvproba[contadorGrupos], ","); tokProba && *tokProba; tokProba = strtok(NULL, ",\n")) {
			csv[contadorGrupos][columnaTablaProbabilidades] = tokProba;
			if(columnaTablaProbabilidades==0){
				//printf("Grupos %s\n", tokProba);
				csvcomplete[contadorGrupos][0] = tokProba;
				//Leer el csv y cargarlo en el arreglo
				char rutaArchivoGrupo[50] = "machine/";
				strcat(rutaArchivoGrupo,argv[3]);
				strcat(rutaArchivoGrupo,"/");
				char extension[5] = ".csv";
				strcat(rutaArchivoGrupo,tokProba);
				strcat(rutaArchivoGrupo,extension);
				FILE* file = fopen( rutaArchivoGrupo, "r");
				char lineaArchivoGrupo[501];

				char * libro[501];
				int contadorLineasGrupo = 0;
				if (file == NULL){
					printf("Error Al abrir %s\n",rutaArchivoGrupo);
				}else{
					//ciclo para cargar archivo de grupo en memoria
					while (fgets(lineaArchivoGrupo, 300, file)) {
						libro[contadorLineasGrupo] = strdup(lineaArchivoGrupo);
						char *cad = (char*)malloc(300*sizeof(char));
						strcpy(cad,lineaArchivoGrupo);
						csvcomplete[contadorGrupos][contadorLineasGrupo+2] = (char*)cad;
						contadorLineasGrupo++;
					}

					int n;
					char* tostring;
					tostring = (char*)malloc(4*sizeof(char));
					sprintf(tostring,"%d",contadorLineasGrupo);
					csvcomplete[contadorGrupos][1] = tostring;
					fclose(file);
				}
			}
			columnaTablaProbabilidades++;
		}
		contadorGrupos++;

	}


	int i;
	//ciclo que recorre los 312 grupos y extrae la probabilidad asignada, el primero es la prob. normal,
	//el segundo es la prob de juego gratis
	for(i=0;i<312;i++){
		//printf("CSV %s\n",csv[i][0]);
		totalAzar += atoi(csv[i][1]);
		totalAzarB += atoi(csv[i][2]);
	}

	if (debugMode) {
		printf( "totalAzar %d\n",totalAzar);
		printf( "totalAzarB %d\n",totalAzarB);
	}

	srand (time(NULL));

	unsigned long int x;
	if (!debugMode) {
		iteraciones = 1;
	}
	//ciclo principal, donde se realizan la simulacion las veces especÃ­ficas
	for( x = 1; x <= iteraciones; x++){
		iteracionesreales++;

		/*if(extreFree!=0){
			//printf( "sumando:::: %d\n",sumando);
			iteraciones += sumando;
			freespin += extreFree;
			extreFree = 0;
			sumando = 0;
		}*/

		if(debugMode){
			contadorparcial++;
			if((contadorparcial%100000)==0 && debugMode){
				//printf("contadorparcial::%d iteraciones::%d",contadorparcial,iteraciones);
				//system("clear");
				printf("Simulacion en curso %.2f", (float)((float)contadorparcial/(float)iteraciones)*100);
				printf(" \n");
			}
		}

		int azar = 0;
		if(freespin==0){
			azar = (rand() % totalAzar);
			if(debugMode){
				dineroperdido += apuestagral;
			}
			freespinon = false;
		}else{
			azar = (rand() % totalAzarB);
			freespin = freespin-1;
			freespinon = true;
		}
		printf("azar %i\n", azar);
		acumula = 0;
		int y;
		for(y=0;y<312;y++){
			if(freespinon==false){
				acumula += atoi(csv[y][1]);
			}else{
				acumula += atoi(csv[y][2]);
			}
			//Si ya encontramos el numero Correcto para azar
			if(azar<acumula){
				//Imprimimos el Grupo que salio seleccionado
				//printf("Grupo Seleccionado %s\n", csv[y][0]);
				//Comparamos si pertenece a un grupo especial

				 if(strcmp(csv[y][0],"GRATISx3") == 0 || strcmp(csv[y][0],"ANT_GRATISx3") == 0){
					 if(debugMode){
						 freespin += (unsigned long)ConfigMemo[1][2];
						 //printf("it1:::%d",ConfigMemo[1][2]);
						 iteraciones += (unsigned long)ConfigMemo[1][2];
						 girosFree++;
						 girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"GRATISx4") == 0 || strcmp(csv[y][0],"ANT_GRATISx4")== 0){

					 if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][3];
						//printf("it2:::%d",ConfigMemo[1][3]);
					 	iteraciones += (unsigned long)ConfigMemo[1][3];
					 	girosFree++;
					 	girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"GRATISx5") == 0 || strcmp(csv[y][0],"ANT_GRATISx5") == 0){

					 if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][4];
						//printf("it3:::%d",ConfigMemo[1][4]);
					 	iteraciones += (unsigned long)ConfigMemo[1][4];
					 	girosFree++;
					 	girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"JUEGOx3") == 0){

					 //Tengo que regresarle al usuario una matriz con el juego En desarrollo
					 if(debugMode){
						double simulacionPremio = simulacion(ConfigMemo[0][2]);
						money += simulacionPremio;
						//printf("JUEGOx3 FIN %f\n\n", simulacionPremio);
						gamesCount = gamesCount+1;
						varoEn3 += simulacionPremio;
						juegox3++;
						if (freespinon){
							juegoEnFreespin++;
						} else {
							juegoNoEnFreespin++;
						}
					 }
				 }else if(strcmp(csv[y][0],"JUEGOx4") == 0){
					 if(debugMode){
						 double simulacionPremio = simulacion(ConfigMemo[0][3]);
						 money += simulacionPremio;
						 //printf("JUEGOx4 FIN %f\n\n", simulacionPremio);
						 gamesCount = gamesCount+1;
						varoEn4 += simulacionPremio;

						juegox4++;
						if (freespinon){
							juegoEnFreespin++;
						} else {
							juegoNoEnFreespin++;
						}

					 }
				 }else if(strcmp(csv[y][0],"JUEGOx5") == 0){
					 if(debugMode){
						 double simulacionPremio = simulacion(ConfigMemo[0][4]);
						 money += simulacionPremio;
						 //printf("JUEGOx5 FIN %f\n\n", simulacionPremio);
						gamesCount = gamesCount+1;
						varoEn5 += simulacionPremio;

						juegox5++;
						if (freespinon){
							juegoEnFreespin++;
						} else {
							juegoNoEnFreespin++;
						}

					 }
				 }else if(strcmp(csv[y][0],"CEROCASIx3") == 0){
					 ceroCasitre++;
				 }else if(strcmp(csv[y][0],"CEROCASIx4") == 0){
					 ceroCasifour++;
				 }else if(strcmp(csv[y][0],"ANT_GRATISx2") == 0){
					 antgratis2++;
				 }else{
					 //Cayo un grupo normal
					 if(debugMode){
						 double ganancias = strtod(csv[y][0],NULL);

						 //sumar a los ceros normales
						 if (ganancias == 0) {
							 ceros++;
						 }

						 int maxa = lineasmax+1;

						 if(freespinon==true){
						    //Dinero de los giros Gratis
						    //freespinon = false;
						    freespinmoney = freespinmoney+ganancias;
						 }else{
						    //Dinero de todas las maquinas

							 onlymachine += ganancias;
						 }
						 money += ganancias;
					 }
				 }

				 readCSV(maxline,csv[y][0],y,freespinon);

				 if(debugMode){
					 if(freespinon==false){
						 iteratest++;
					 }
					 if(strcmp(csv[y][0],"0.00") != 0 && strcmp(csv[y][0],"CEROCASIx3") != 0 && strcmp(csv[y][0],"CEROCASIx4") != 0 && strcmp(csv[y][0],"ANT_GRATISx2") != 0){
						if(freespinon==false){

						   girosGanados++;
						   /*if((girosGanados%100000)==0 && debugMode){
							   printf("girosGanados %d\n", girosGanados);
						   }*/
						 }
					 }
					 if(freespinon==true){
						 freespinon = false;
					 }
				 }

				 //printf("valor de y %i\n", y);

				break;
			}

		}
	}

	//Solo para Modo Simulador
	float payout = ((float)money/(float)dineroperdido)*100;
	float rtpfreespins = ((float)freespinmoney/(float)dineroperdido)*100;
	float rtpgame = ((float)gameMoney/(float)dineroperdido)*100;
	float rtpmachine = ((float)onlymachine/(float)dineroperdido)*100;
	float rtpsum = ((float)rtpfreespins+(float)rtpgame+(float)rtpmachine);
	float percentSpinWin = ((float)girosGanados/(double)originalIteracion)*100;
	float percentFreeSpin = ((double)girosFree/(double)originalIteracion)*100;
	float percentGame = ((float)gamesCount/(float)originalIteracion)*100;
	float percentfourhilo = ((float)fourhilo/(float)originalIteracion)*100;
	float percentfivehilo = ((float)fivehilo/(float)originalIteracion)*100;
	float percentfourhilononcero = ((float)fourhilo/(float)(originalIteracion-ceros))*100;
	float percentfivehilononcero = ((float)fivehilo/(float)(originalIteracion-ceros))*100;
	float percentbuengift = ((double)bigwin/(double)originalIteracion)*100;
	float percentgrangift = ((double)superwin/(double)originalIteracion)*100;
	float percentmegagift = ((double)megawin/(double)originalIteracion)*100;
	float antgratis2fl = ((float)antgratis2/(float)originalIteracion)*100;
	float percentcerotre = ((float)ceroCasitre/(float)originalIteracion)*100;
	float percentcerofour = ((float)ceroCasifour/(float)originalIteracion)*100;



	if (debugMode) {
		printf("------------------- SIMULACIîN ------------------\n");
		printf("testvar %d\n", testvar);
		printf("megawin %d\n", megawin);

		printf("girosGratisNormal %d\n", girosGratisNormal);
		printf("girosGratisJuego %d\n", girosGratisJuego);
		printf("girosGratisOrdinario %d\n", girosGratisOrdinario);

		printf("iteratest %d\n", iteratest);
		printf("OriginalIteracion %d\n", originalIteracion);
		printf("Iteraciones Reales %d\n", iteracionesreales);
		printf("GirosGanados %d\n", girosGanados);

		printf("\n-------------------RTP ------------------\n");
		printf("RTP Machine %.2f\n", rtpmachine);
		printf("RTP Game %.2f %\n", rtpgame);
		printf("RTP  freespins %.2f %\n", rtpfreespins);
		printf("RTP Gral %.2f\n", rtpsum);
		printf("Frecuencia de Juego %.2f %\n", percentGame);
		printf("Frecuencia De Giros Gratis %.2f %\n", percentFreeSpin);
		printf("Giros Ganadores::%f\n",percentSpinWin);

		printf("-------------------JUEGO (RULETA)------------------\n");

		printf("JuegoX3 Total:%d\n",juegox3);
		printf("JuegoX4 Total:%d\n",juegox4);
		printf("JuegoX5 Total:%d\n",juegox5);
		printf("Juego en otro (premio + juego) Total:%d\n",juegoEnOtro);

		printf("JuegoX3 Frecuencia:%.2f%\n",((double)juegox3/(double)originalIteracion)*100);
		printf("JuegoX4 Frecuencia:%.2f%\n",((double)juegox4/(double)originalIteracion)*100);
		printf("JuegoX5 Frecuencia:%.2f%\n",((double)juegox5/(double)originalIteracion)*100);
		printf("Juego en otro (premio + juego) Frecuencia:%.5f%\n",((double)juegoEnOtro/(double)originalIteracion)*100);

		printf("JuegoX3 Money:%.2f\n",varoEn3);
		printf("JuegoX4 Money:%.2f\n",varoEn4);
		printf("JuegoX5 Money:%.2f\n",varoEn5);
		printf("Juego en otro Money:%.2f\n",varoEnOtro);

		printf("Juegos en Modo Freespin:%.d\n",juegoEnFreespin);
		printf("Juegos en Modo Normal:%d\n",juegoNoEnFreespin);



		printf("games money::%.2f\n",gameMoney);
		printf("Juegos Total:%d\n",gamesCount);
		printf("Frecuencia de Juego %.2f %\n", percentGame);
		printf("RTP Game %.2f %\n", rtpgame);
		printf("-------------------GIROS GRATIS------------------\n");
		printf("\nGiros Gratis Money %.2f\n", freespinmoney);
		printf("gratis Total:%d\n",girosFree);
		printf("Frecuencia De Giros Gratis %.2f %\n", percentFreeSpin);
		//printf("Frecuencia de Giros Ganadores %.2f %\n", percentSpinWin);
		printf("RTP  freespins %.2f %\n", rtpfreespins);

		printf("----------------JUEGOS + GIROS--------------------------\n");
		printf("Juegos Total + Gratis Total:%d\n",gamesCount+girosFree);
		printf("Frecuencia de Juego + Gratis: %.2f\n", percentGame + percentFreeSpin);
		printf("------------- AL HILO  -----------------------------\n");
		printf("Total 4 al Hilo %d \n", fourhilo);
		printf("Frecuencia 4 al Hilo %.2f %\n", percentfourhilo);
		printf("Frecuencia 4 al Hilo Solo en non-cero %.2f %\n", percentfourhilononcero);
		printf("Total 5 al Hilo %d\n", fivehilo);
		printf("Frecuencia 5 al Hilo %.2f%\n", percentfivehilo);
		printf("Frecuencia 5 al Hilo solo en non-cero %.2f%\n", percentfivehilononcero);
		printf("------------- PREMIOS-----------------------------\n");
		printf("Buen Premio %.2f\n", percentbuengift);
		printf("Gran Premio %.2f\n", percentgrangift);
		printf("Premio Mayor %.2f\n", percentmegagift);
		printf("Ant Gratis X2 %.2f\n", antgratis2fl);
		printf("Cero Casi x3 %.2f\n", percentcerotre);
		printf("Cero Casi x4 %.2f\n", percentcerofour);

		printf("\nOriginal Itera %i\n", bigwin);
		printf("Money %.2f\n", money);
		printf("OnlyMachine %.2f\n", onlymachine);
		printf("Costo de la maquina %.2f\n", dineroperdido);
		printf("Apuesta General %i\n",apuestagral);
		printf("Original %lu\n",originalIteracion);

		printf("Total Azar A %i\n",totalAzar);
		printf("Total Azar B %i\n",totalAzarB);



	}
}
