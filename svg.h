

// buildcrimes.h

#ifndef BUILDCRIMES_H
#define BUILDCRIMES_H

char * unfinish(char * originalfile);
int exhaust(char * flag, char key);

// show filter options
void ops(char * flag);
void fine_ops(void);

// crime filter by flags
int groupfilter(struct crime * c, char * flag);
int singlefilter(struct crime * c, char * flag);
int crimefilter(struct crime * c, char ** flags);

// legend, also operates on svg
char * startbox(double x, double y, double width, double height);
char * makeword(double x, double y, char * color, char * fontsize, char * word);
char * parseflag(char * flag);
char * getcolor(char * flag);
double labelsingle(char * flag, double x, double y, double width, double height, FILE * fp);
double labelglob(char * flag, double x, double y, double width, double height, FILE * fp);
void to_legend(char ** flags, double x, double y, double width, double height, FILE * fp);

// operate on svg
char * add_to_file(struct crime * c);
void build_svg(struct crimelist * cs, FILE * fp, char ** flag);


#endif
