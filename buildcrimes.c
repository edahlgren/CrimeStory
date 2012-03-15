
// buildcrimes.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "buildcrimes.h"


char * flush(char * w) {
	char c;
	int i = 0;

	while(c = w[i]) {
		w[i] = 0;
		++i;
	}
	return w;
}

double translate_lon(char * lon) {
	double longitude, nx;

	longitude = strtod(lon, NULL);
	//printf("longitude: %f\n", longitude);
	nx = fabs((longitude+87.645466)*(403.26-451.17)/((-87.642006)-(-87.60238))+398.22);
	//printf("long transformed: %f\n", nx);
	return nx;
}

double translate_lat(char * lat) {
	double latitude, ny, fromtop; 

	latitude = strtod(lat, NULL);
	//printf("latitude: %f\n", latitude);
	ny=fabs((latitude-41.875577)*(485.13-404.00)/(41.896363-41.847199)+450.13);
	fromtop = 792 - ny;	
	//printf("lat transformed: %f\n", fromtop);
	return fromtop;
}

void init_crimes(struct crimelist * cs) {
	cs->crimes = NULL;
	cs->numcrimes = 0;
	return;
}

void init_crime(struct crime * c) {
	c->lat = 0.0;
	c->lon = 0.0;
	c->IUCR = 0;
	c->IUCRname = NULL;
	return;
}

void add_crime(struct crimelist * cs, struct crime * c) {
	int n = cs->numcrimes;
	struct crime current = *c;

	cs->crimes = realloc(cs->crimes, (n+1)*sizeof(struct crime));	
	(cs->crimes)[n] = current;
	cs->numcrimes = n+1; 
	return;
}


void print_crimes(struct crimelist * cs) {
	int i = 0;
	struct crime c;

	while(i < cs->numcrimes) {
		c = (cs->crimes)[i];
		printf("lat %f long %f\n", (&c)->lat, (&c)->lon);
		printf("----------\n");
		printf("IUCR %d IUCR name %s\n", (&c)->IUCR, (&c)->IUCRname);
		printf("----------\n");
		printf("\n\n");	
		++i;	
	}
	return;
}

int full(struct crime * c) {
	int i = 0;

	if((c->lat == 0.0) || (c->lon == 0.0) || (c->IUCR == 0) || (c->IUCRname == NULL)) {
		return i;
	}	
	else {
		i = 1;
		return i;
	}
}




