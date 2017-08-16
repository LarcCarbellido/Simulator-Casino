#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <math.h>
#include <string.h>
#define MAXROWS 400
#define true 1
#define false 0


typedef unsigned short int bool;

char * csv[312][3];
char * csvcomplete[312][501];
float ConfigMemo[15][12];
double freespinmoney = 0;
unsigned long freespin = 0;
double onlymachine = 0;
int gamesCount = 0;
double gameMoney = 0;
//Puntero de Dinero
double *money;
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

double simulacion(double percent)
{
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
            	   sumatodalalinea(z);
            	   break;
               case 0:
                   life = life+1;
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


void readCSV(int lineas, char *fileName,int arraypos,int freespinactive){
	int contb = 0;
	int azar = 0;
	char * libro[501];
	char *cad;

	if(arraypos >= 79 && arraypos<=299){
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
	contb = atoi(csvcomplete[arraypos][1]);
	int mf;
	for(mf=0; mf<contb; mf++) {
		int sumarmf = mf+2;
		libro[mf] = csvcomplete[arraypos][sumarmf];
	}

	azar = (rand() % contb);
	int contw = contb;
	cad = (char*)malloc(300*sizeof(char));
	strcpy(cad, libro[azar]);
	char *line =cad;
	char* tok;
	contb = 0;
	float ganaste = 0;
	int columna = 0;

	for (tok = strtok(line, "\""); tok && *tok; tok = strtok(NULL, ",\n")) {
		columna++;
		if ( ( columna == 1 ) && ( !debugMode ) ){
			printf("%s\n",tok);
		}
		if(strcmp(fileName,"GRATISx3") == 0 || strcmp(fileName,"GRATISx4") == 0 || strcmp(fileName,"GRATISx5") == 0 || strcmp(fileName,"ANT_GRATISx3") == 0 || strcmp(fileName,"ANT_GRATISx4") == 0 || strcmp(fileName,"ANT_GRATISx5") == 0) {
			if(columna == 2){
				if(atoi(tok)!=0){
					
					if(freespinactive){
						freespinmoney = freespinmoney+atoi(tok);
					}else{
						onlymachine = onlymachine+atoi(tok);
					}
					//Dinero 1
					printf("Antes de Dinero 1 %.2f\n",*money);
					*money = *money + atoi(tok);
					printf("Despues de Dinero 1 %.2f\n",*money);
					
				}
			}
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
					//Dinero 2
					*money = *money + simulacionPremio;
					
					gamesCount = gamesCount+1;
					juegoEnOtro = juegoEnOtro+1;
					varoEnOtro = varoEnOtro+simulacionPremio;
				}
			}
		}else if(strcmp(fileName,"JUEGOx3") == 0 || strcmp(fileName,"JUEGOx4") == 0 || strcmp(fileName,"JUEGOx5") == 0){
			if(columna == 2){
				if(atoi(tok)!=0){
					if(freespinactive){
						freespinmoney = freespinmoney+atoi(tok);
					}else{
						onlymachine = onlymachine+atoi(tok);
					}
					//Dinero 3
					*money = *money + atoi(tok);
					
				}
			}
			if(columna == 3){
				if(atoi(tok)==3){					
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][2];
						iteraciones += (unsigned long)ConfigMemo[1][2];
						girosFree++;
						girosGratisJuego++;
					}
				}else if(atoi(tok)==4){					
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][3];
						iteraciones += (unsigned long)ConfigMemo[1][3];
						girosFree++;
						girosGratisJuego++;
					}
				}else if(atoi(tok)==5){					
					if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][4];
						iteraciones += (unsigned long)ConfigMemo[1][4];
						girosFree++;
						girosGratisJuego++;
					}
				}
			}
		}else{			
			if(columna == (lineasmax+3)){
				if(atoi(tok)!=0){					
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
			if(columna == (lineasmax+4)){			
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
							//Dinero 4
							*money = *money + simulacionPremio;
							
							gamesCount = gamesCount+1;
						}
					}
				}

			}			
	    	if(columna==2 && debugMode){
				if(strcmp(fileName,"JUEGOx5") != 0 && strcmp(fileName,"JUEGOx4") != 0 && strcmp(fileName,"JUEGOx3") != 0 && strcmp(fileName,"GRATISx5") != 0 && strcmp(fileName,"GRATISx4") != 0 && strcmp(fileName,"GRATISx3") != 0 && strcmp(fileName,"CEROCASIx3") != 0 && strcmp(fileName,"CEROCASIx4") != 0 && strcmp(fileName,"ANT_GRATISx2") != 0  && strcmp(fileName,"ANT_GRATISx3") != 0  && strcmp(fileName,"ANT_GRATISx4") != 0  && strcmp(fileName,"ANT_GRATISx5") != 0) {
					if(atoi(tok) == 4){						
						fourhilo++;						
					}
					if(atoi(tok) == 5){						
						fivehilo++;
					}
				}

	    	}
		}
    	/*if(contb>=2){
	    	
	    	ganaste += atof(tok);
	    	if(contb==(lineas+1)){
	    		break;
	    	}
	    }*/
    }
	free(cad);
}

// Inicio del simulador
double simulador(int lineas, int maquina){
	// if (argc != 5){
	// 	printf( "Uso: Simulador Iteraciones Numero-de-Lineas Maquina(1-12) modo-simulacion(0-1) \n");
	// 	return 0;
	// }
	debugMode = 1;
	if( debugMode ){

	}
	iteraciones = 1;
	int maxline = lineas;
	lineasmax = maxline;
	int machine = maquina;
	char maquinaString[20];
	sprintf(maquinaString, "%d", maquina);
	double iterabackup = 0;
	char rutaCfg[50] = "machine/";
	char extensionTxt[13] = "/general.txt";
	strcat(rutaCfg,maquinaString);
	strcat(rutaCfg,extensionTxt);
	// printf("\nabrir %s\n",rutaCfg);
	FILE* configFile = fopen(rutaCfg, "r");
	char Configline[5];
	int lineaDeArchivoDeConfig = 0;
	int maxlinLimit = 0;
	char* cfgtok;
	int columnaDeArchivoDeConfig = 0;	
	while (fgets(Configline, 1024, configFile)) {		
		columnaDeArchivoDeConfig = 0;		
		for (cfgtok = strtok(strdup(Configline), ","); cfgtok && *cfgtok; cfgtok = strtok(NULL, ",\n")) {			
			if(lineaDeArchivoDeConfig==0){
				maxlinLimit = atoi(cfgtok);
			
			}else if(lineaDeArchivoDeConfig==1){
				ConfigMemo[(lineaDeArchivoDeConfig-1)][columnaDeArchivoDeConfig] = atof(cfgtok);
			
			}else if(lineaDeArchivoDeConfig==2){
				ConfigMemo[(lineaDeArchivoDeConfig-1)][columnaDeArchivoDeConfig] = atof(cfgtok);
			
			}else{
				matrizMiniJuego[(lineaDeArchivoDeConfig-3)][columnaDeArchivoDeConfig] = atoi(cfgtok);		
				if(lineaDeArchivoDeConfig==3){
					numColsMinijuego++;
				}
			}
			columnaDeArchivoDeConfig++;
		}
		lineaDeArchivoDeConfig++;
	}	
	
	numRenglonesMatrizMinijuego = (lineaDeArchivoDeConfig-3);
	
	char rutaCsv[50] = "machine/";	
	char extensionCsv[12] = "/Table.csv";
	strcat(rutaCsv,maquinaString);
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
	int contadorparcial = 0;
	byline = 1;
	int apuestagral = byline*maxline;	
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
	
	
	while (fgets(lineaTablaProbabilidades, 1024, archivoTablaProbabilidades)) {
		csvproba[contadorGrupos] =  strdup(lineaTablaProbabilidades);
		columnaTablaProbabilidades = 0;
		for (tokProba = strtok(csvproba[contadorGrupos], ","); tokProba && *tokProba; tokProba = strtok(NULL, ",\n")) {
			csv[contadorGrupos][columnaTablaProbabilidades] = tokProba;
			if(columnaTablaProbabilidades==0){
				
				csvcomplete[contadorGrupos][0] = tokProba;
				
				char rutaArchivoGrupo[50] = "machine/";
				strcat(rutaArchivoGrupo,maquinaString);
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

	for(i=0;i<312;i++){
		
		totalAzar += atoi(csv[i][1]);
		totalAzarB += atoi(csv[i][2]);
	}

	if (debugMode) {
		// printf( "totalAzar %d\n",totalAzar);
		// printf( "totalAzarB %d\n",totalAzarB);
	}

	
	unsigned long int x;
	if (!debugMode) {
		iteraciones = 1;
	}
	
	for( x = 1; x <= iteraciones; x++){
		iteracionesreales++;

		/*if(extreFree!=0){
			
			iteraciones += sumando;
			freespin += extreFree;
			extreFree = 0;
			sumando = 0;
		}*/

		if(debugMode){
			contadorparcial++;
			if((contadorparcial%100000)==0 && debugMode){
	
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
		
		acumula = 0;
		int y;
		for(y=0;y<312;y++){
			if(freespinon==false){
				acumula += atoi(csv[y][1]);
			}else{
				acumula += atoi(csv[y][2]);
			}
			
			if(azar<acumula){
				
				 if(strcmp(csv[y][0],"GRATISx3") == 0 || strcmp(csv[y][0],"ANT_GRATISx3") == 0){
					 if(debugMode){
						 freespin += (unsigned long)ConfigMemo[1][2];
						 iteraciones += (unsigned long)ConfigMemo[1][2];
						 girosFree++;
						 girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"GRATISx4") == 0 || strcmp(csv[y][0],"ANT_GRATISx4")== 0){

					 if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][3];
						
					 	iteraciones += (unsigned long)ConfigMemo[1][3];
					 	girosFree++;
					 	girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"GRATISx5") == 0 || strcmp(csv[y][0],"ANT_GRATISx5") == 0){

					 if(debugMode){
						freespin += (unsigned long)ConfigMemo[1][4];
						
					 	iteraciones += (unsigned long)ConfigMemo[1][4];
					 	girosFree++;
					 	girosGratisOrdinario++;
					 }
				 }else if(strcmp(csv[y][0],"JUEGOx3") == 0){
					 
					 if(debugMode){
						double simulacionPremio = simulacion(ConfigMemo[0][2]);
						//Dinero 5
						*money += simulacionPremio;
						
						
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
						 //Dinero 6
						 *money += simulacionPremio;
							
						 
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
						 //Dinero 7
						 *money += simulacionPremio;
						
						 
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
					 
					 if(debugMode){
						 double ganancias = strtod(csv[y][0],NULL);
						 
						 if (ganancias == 0) {
							 ceros++;
						 }

						 int maxa = lineasmax+1;

						 if(freespinon==true){					    
						    freespinmoney = freespinmoney+ganancias;
						 }else{
						    onlymachine += ganancias;
						 }
						 //Dinero 8
						 *money += ganancias;
						
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
				break;
			}
		}
	}
	//Dinero 9
	//printf("Dinero9: %.2f\n", *money);
	return *money;
}

struct rec{
	char *date;
	float *yld;
};

struct rec *readFile();

/* read the input file */
struct rec *readFile(char *filname){
	FILE *fp;
	char *line;
	struct rec rw;
	int i=0;
	struct rec *data[MAXROWS];
	for(i = 0; i < MAXROWS; i++){
		data[i] = (struct rec *)malloc(sizeof(struct rec));
	}
	i = 0;
	rw = *data[0];
	if((fp = fopen(filname, "r")) != NULL){
		while(fscanf(fp, "%s,%f", rw.date, rw.yld) == 2){
			i++;
			rw = *data[i];
		}
		return *data;
	}else{
	
	}
	return NULL;
}

//Main
int main(int argc, char *argv[])
{
	srand(time(NULL));
	int count = 1000;
	int i;
	double dinero;
	for (i = 0; i < count; i++)
	{
		money = (double *)malloc(sizeof (double));
		dinero = simulador(10,1);
		printf("Retorno: %.0f\n",dinero);
		free(money);
	}
	return 0;
}
