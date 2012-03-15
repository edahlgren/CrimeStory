


// buildcrimes.h

#ifndef BUILDCRIMES_H
#define BUILDCRIMES_H

struct crime {
	double lat;
	double lon;
	int IUCR;
	char * IUCRname;
};

struct crimelist {
	int numcrimes;
	struct crime * crimes;
};


char * flush(char * w);
double translate_lat(char * lat);
double translate_lon(char * lon);
void init_crimes(struct crimelist * cs);
void init_crime(struct crime * c);
void add_crime(struct crimelist * cs, struct crime * c);
void print_crimes(struct crimelist * cs);
int full(struct crime * c);

#endif


