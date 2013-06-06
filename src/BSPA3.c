/*
 ============================================================================
 Name        : BSPA3.c
 Author      : xyncon
 Version     :
 Copyright   : 
 Description : lru test bench
 ============================================================================
 */

#include "BSPA3.h"

struct vmem_struct *vmem = NULL;

int j, i, k, l;
int sum;
int multi;
int smallest;
int frame = 0;
int bitMatrix[PAGESIZE*PAGESIZE];

int main(void)
{
	// init bitMatrix
	memset(bitMatrix, 0, sizeof(bitMatrix));

	printf("DEBUG: num of frames: %d\nDEBUG: num of loops: %d\n\n", PAGESIZE, LOOPS);

	// schleife fuer wiederholung des algo
	for(l = 0; l < LOOPS; l++)
	{
		 smallest = -1; // kleinster wert
		 frame = 0; //zu nutzender frame

		 for(i = 0; i < sizeof(bitMatrix) / sizeof(int); i += PAGESIZE)
		 {
			 multi = 1;//multiplikator fuer dualumrechnung
			 sum = 0; //zeilen summen in dezimalform

			//summerierung der betrage der zeilen
			for(j = PAGESIZE - 1; j >= 0; j--)
			{
				sum += bitMatrix[j + i] * multi;
				multi *= 2;
			}

			//debugausgabe
			printf("DEBUG: %d   sum: %d\n", i, sum);
			printf("DEBUG: %d   smallest: %d\n", i, smallest);

			//aktuallisierung der kleinsten zeilensumme und des zu nutzenden frames
			if(sum < smallest || smallest < 0)
			{
				smallest = sum;
				frame = i / PAGESIZE;
			}

			//debugausgabe
			printf("DEBUG: %d   frame: %d\n--------------------\n", i, frame);

			// ueberschreibt mitten im betrieb eine zeile und eine spalte der bitmatrix
			// AUF DIMENSIONEN DER BITMATRIX ACHTEN!!
//			if(l==4)
//			{
//				//n-te zeile mit 1 beschreiben
//				bitMatrix[0] = 1;
//				bitMatrix[1] = 1;
//				bitMatrix[2] = 1;
//				bitMatrix[3] = 1;
//
//				bitMatrix[4] = 1;
//				bitMatrix[5] = 1;
//				bitMatrix[6] = 1;
//				bitMatrix[7] = 1;
//
//				bitMatrix[8] = 1;
//				bitMatrix[9] = 1;
//				bitMatrix[10] = 1;
//				bitMatrix[11] = 1;
//
//				bitMatrix[12] = 1;
//				bitMatrix[13] = 1;
//				bitMatrix[14] = 1;
//				bitMatrix[15] = 1;
//
//				//n-te spalte mit 0 beschreiben
//				bitMatrix[0] = 0;
//				bitMatrix[16] = 0;
//				bitMatrix[32] = 0;
//				bitMatrix[48] = 0;
//
//				bitMatrix[64] = 0;
//				bitMatrix[80] = 0;
//				bitMatrix[96] = 0;
//				bitMatrix[112] = 0;
//
//				bitMatrix[128] = 0;
//				bitMatrix[144] = 0;
//				bitMatrix[160] = 0;
//				bitMatrix[176] = 0;
//
//				bitMatrix[192] = 0;
//				bitMatrix[208] = 0;
//				bitMatrix[224] = 0;
//				bitMatrix[240] = 0;
//			}//endif
		 }//endforl

		//debugausgabe: matrix alt
		printf("DEBUG: matrix alt\n--------------------\n");
		for(k = 0; k < PAGESIZE*PAGESIZE; k++)
		{
			printf("%d", bitMatrix[k]);
			printf("%c", ((k + 1) % PAGESIZE) ? ' ' : '\n');
		}
		printf("\n");

		//zeile d zu ersetzenden frames m 1 beschreiben
		for(i = frame * PAGESIZE; i < (frame + 1) * PAGESIZE; i++)
		{
			bitMatrix[i] = 1;
		}

		//spalte d entsprechenden frames m 0 beschreiben
		for(i = frame; i < PAGESIZE * PAGESIZE; i += PAGESIZE)
		{
			bitMatrix[i] = 0;
		}

		//debugausgabe: matrix neu
		printf("DEBUG: matrix neu\n--------------------\n");
		for(k = 0; k < PAGESIZE*PAGESIZE; k++)
		{
			printf("%d", bitMatrix[k]);
			printf("%c", ((k + 1) % PAGESIZE) ? ' ' : '\n');
		}
		printf("\n");
	}

	printf("done\n");

	return EXIT_SUCCESS;
}
