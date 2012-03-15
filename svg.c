

// buildsvg.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "buildcrimes.h"
#include "svg.h"



// Intersection of I-94 and I-290
//   Earth : 41.875577,-87.645466
//   Canvas : 398.22,450.13

// Intersection of I-94 and I-55
//   Earth : 41.847199,-87.642006
//   Canvas : 403.26,404.00

// North-East Corner of the Water Plant
//   Earth : 41.896363,-87.60238
//   Canvas : 451.17,485.13



char * unfinish(char * originalfile) {
  int exit;
  char * call = calloc(512, sizeof(char));
  char * newfile = calloc(15, sizeof(char));

  strcpy(newfile, "Chicago.svg");
  strcpy(call, "sed 's/<\\/svg>$//g' ");
  strcat(call, originalfile);
  strcat(call, " > ");
  strcat(call, newfile);	

  exit = system(call);
  if(exit == -1) {
    printf("couldn't do sed\n");
  }
  else {
    exit = system("chmod 755 Chicago.svg");
    if(exit == -1) {
      printf("coudn't do priveledges\n");
   }
    else {
      return newfile;
    }
  }
}


int exhaust(char * flag, char key) {
  char c;
  int i = 0;

  while(c = flag[i]) {
    if(c == key) {
      return 1;
    }		
    ++i;
  }
  return 0;
}

void svg2png(void) {
  int exit;
  char * call = calloc(100, sizeof(char));

  strcpy(call, "inkscape Chicago.svg --export-png=Chicago.png --export-dpi=300");	

  exit = system(call);
  if(exit == -1) {
    printf("couldn't do inkscape transform\n");
  }
  free(call);
  return;
}


void ops(char * flag) {
  if(strcmp(flag, "-all") == 0) {
    strcpy(flag, "-vtpdcs");
  }
  if(exhaust(flag, 'v')) {
    printf("-v\tviolent crime\n");
    printf("\t\thomicide\n");
    printf("\t\tcriminal sexual assault\n");
    printf("\t\tcriminal damage\n");
    printf("\t\tbattery\n");		
  }
  if(exhaust(flag, 't')) {
    printf("-t\ttheft\n");
    printf("\t\tburglary\n");
    printf("\t\ttheft\n");
    printf("\t\tmotor vehicle theft\n");
    printf("\t\trobbery\n");
  }
  if(exhaust(flag, 'p')) {
    printf("-p\tpublic violation\n");
    printf("\t\tpublic indecency\n");
    printf("\t\tobscenity\n");
    printf("\t\tpublic peace violation\n");
  }
  if(exhaust(flag, 'd')) {
    printf("-d\tdrug related crime\n");
    printf("\t\tnarcotics\n");
    printf("\t\tliqour law violation\n");
  }
  if(exhaust(flag, 'c')) {
    printf("-c\tinvolving children\n");
    printf("\t\tkidnapping\n");
    printf("\t\toffense involving children\n");
  }
  if(exhaust(flag, 's')) {
    printf("-s\tsexual\n");
    printf("\t\tcriminal sexual assault\n");
    printf("\t\tsex offense\n");
    printf("\t\tprostitution\n");
  }
}

void fine_ops(void) {
	printf("\n");
 	printf("-v\n");
	printf("\t--homicide\n");
	printf("\t--criminal-sexual-assault\n");
	printf("\t--criminal-damage\n");
	printf("\t--battery\n");

	printf("-t\n");
	printf("\t--burglary\n");
	printf("\t--theft\n");
	printf("\t--motor-vehicle-theft\n");
	printf("\t--robbery\n");

	printf("-p\n");
	printf("\t--public-indecency\n");
	printf("\t--obscenity\n");
	printf("\t--public-peace-violation\n");
		
	printf("-d\n");
	printf("\t--narcotics\n");
	printf("\t--liqour-law-violation\n");

	printf("-c\n");
	printf("\t--kidnapping\n");
	printf("\t--offense-involving-children\n");

  	printf("-s\n");
	printf("\t--criminal-sexual-assault\n");
	printf("\t--sex-offense\n");
	printf("\t--prostitution\n\n");

	printf("--weapons-violation\n");
	printf("--stalking\n");
	printf("--intimidation\n");
	printf("--interference-with-public-officer\n");
	printf("--ritualism\n");
	printf("--arson\n");
	printf("--deceptive-practice\n");
	printf("--gambling\n");
	printf("--assault\n");
	printf("--criminal-trespass\n\n");
	
  return;
}

int groupfilter(struct crime * c, char * flag) {
  int f = 0;

  if(exhaust(flag, 'v')) {
    // violent crime
    if(strcmp(c->IUCRname, "HOMICIDE ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "CRIM SEXUAL ASSAULT ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "CRIMINAL DAMAGE ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "BATTERY ") == 0) {
      f = 1;
    }
  }
  if(exhaust(flag, 't')) {
    // theft crime
    if(strcmp(c->IUCRname, "BURGLARY ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "THEFT ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "MOTOR VEHICLE THEFT ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "ROBBERY ") == 0) {
      f = 1;
    }
  }
  if(exhaust(flag, 'p')) {
    // public crime
    if(strcmp(c->IUCRname, "PUBLIC INDECENCY ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "OBSCENITY ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "PUBLIC PEACE VIOLATION ") == 0) {
      f = 1;
    }
  }
  if(exhaust(flag, 'd')) {
    // drug related crime
    if(strcmp(c->IUCRname, "NARCOTICS ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "LIQUOR LAW VIOLATION ") == 0) {
      f = 1;
    }
  }
  if(exhaust(flag, 'c')) {
    // involving children
    if(strcmp(c->IUCRname, "KIDNAPPING ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "OFFENSE INVOLVING CHILDREN ") == 0) {
      f = 1;
    }
  }
  if(exhaust(flag, 's')) {
    // sexual crime
    if(strcmp(c->IUCRname, "CRIM SEXUAL ASSAULT ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "SEX OFFENSE ") == 0) {
      f = 1;
    }
    if(strcmp(c->IUCRname, "PROSTITUTION ") == 0) {
      f = 1;
    }
  }
  return f;
}

int singlefilter(struct crime * c, char * flag) {
	if(strcmp(flag, "--homicide") == 0) {
		if(strcmp(c->IUCRname, "HOMICIDE ") == 0) {
      			return 1;	
    		}
	}
	if(strcmp(flag, "--criminal-sexual-assault") == 0) {
		if(strcmp(c->IUCRname, "CRIM SEXUAL ASSAULT ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--criminal-damage") == 0) {
		if(strcmp(c->IUCRname, "CRIMINAL DAMAGE ") == 0) {
		      return 1;
    		}
	}
	if(strcmp(flag, "--battery") == 0) {
		if(strcmp(c->IUCRname, "BATTERY ") == 0) {
		      return 1;
		}
	}
	if(strcmp(flag, "--burglary") == 0) {
		if(strcmp(c->IUCRname, "BURGLARY ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--theft") == 0) {
		if(strcmp(c->IUCRname, "THEFT ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--motor-vehicle-theft") == 0) {
		if(strcmp(c->IUCRname, "MOTOR VEHICLE THEFT ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--robbery") == 0) {
		if(strcmp(c->IUCRname, "ROBBERY ") == 0) {	
			return 1;
		}
	}
	if(strcmp(flag, "--public-indecency") == 0) {
		if(strcmp(c->IUCRname, "PUBLIC INDECENCY ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--obscenity") == 0) {
		if(strcmp(c->IUCRname, "OBSCENITY ") == 0) {
      			return 1;
		}    
	}
	if(strcmp(flag, "--public-peace-violation") == 0) {
		if(strcmp(c->IUCRname, "PUBLIC PEACE VIOLATION ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--narcotics") == 0) {
		if(strcmp(c->IUCRname, "NARCOTICS ") == 0) {
		      return 1;
		}
	}
	if(strcmp(flag, "--liqour-law-violation") == 0) {
		if(strcmp(c->IUCRname, "LIQUOR LAW VIOLATION ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--kidnapping") == 0) {
		if(strcmp(c->IUCRname, "KIDNAPPING ") == 0) {
		      return 1;
		}
	}
	if(strcmp(flag, "--offense-involving-children") == 0) {
		if(strcmp(c->IUCRname, "OFFENSE INVOLVING CHILDREN ") == 0) {
		      return 1;
    		}
	}
	if(strcmp(flag, "--sex-offense") == 0) {
		if(strcmp(c->IUCRname, "SEX OFFENSE ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--prostitution") == 0) {
		if(strcmp(c->IUCRname, "PROSTITUTION ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--weapons-violation") == 0) {
		if(strcmp(c->IUCRname, "WEAPONS VIOLATION ") == 0) {
     			return 1;
    		}
	}
	if(strcmp(flag, "--stalking") == 0) {
		if(strcmp(c->IUCRname, "STALKING ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--intimidation") == 0) {
		if(strcmp(c->IUCRname, "INTIMIDATION ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--ritualism") == 0) {
    		if(strcmp(c->IUCRname, "RITUALISM ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--arson") == 0) {
		if(strcmp(c->IUCRname, "ARSON ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--deceptive-practice") == 0) {
		if(strcmp(c->IUCRname, "DECEPTIVE PRACTICE ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--gambling") == 0) {
		if(strcmp(c->IUCRname, "GAMBLING ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--interference-with-public-officer") == 0) {
		if(strcmp(c->IUCRname, "INTERFERENCE WITH A PUBLIC OFFICER ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--assault") == 0) {
		if(strcmp(c->IUCRname, "ASSAULT ") == 0) {
      			return 1;
    		}
	}
	if(strcmp(flag, "--criminal-trespass") == 0) {
		if(strcmp(c->IUCRname, "CRIMINAL TRESPASS ") == 0) {
      			return 1;
    		}
	}
	return 0;
}

int crimefilter(struct crime * c, char ** flags) {
	char * f;
	int i = 0;
	int s, g;
	int final = 0;

	while(f = flags[i]) {
		if(f[1] == '-') {
			s = singlefilter(c, f);
			final = (final || s);
		}
		else {
			g = groupfilter(c, f);
			final = (final || g);
		}		
		++i;
	}
	return final;
}

char * color_crime(char * iucrname) {
  char * color = calloc(8, sizeof(char));	
  // default color
  strcpy(color, "#000000");


  if(strcmp(iucrname, "HOMICIDE ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff0000");
  }
  if(strcmp(iucrname, "CRIM SEXUAL ASSAULT ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cc3366");
  }
  if(strcmp(iucrname, "CRIMINAL DAMAGE ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff0033");
  }
  if(strcmp(iucrname, "BATTERY ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cc0033");
  }
	


  if(strcmp(iucrname, "BURGLARY ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff3300");
  }
  if(strcmp(iucrname, "THEFT ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff6600");
  }
  if(strcmp(iucrname, "MOTOR VEHICLE THEFT ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff6633");
  }
  if(strcmp(iucrname, "ROBBERY ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cc3300");
  }


  if(strcmp(iucrname, "PUBLIC INDECENCY ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ffcc00");
  }
  if(strcmp(iucrname, "OBSCENITY ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ffcc33");
  }
  if(strcmp(iucrname, "PUBLIC PEACE VIOLATION ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ffff00");
  }



  if(strcmp(iucrname, "NARCOTICS ") == 0) {
    // printf("matches\n");
    strcpy(color, "#33cc33");
  }
  if(strcmp(iucrname, "LIQUOR LAW VIOLATION ") == 0) {
    // printf("matches\n");
    strcpy(color, "#006600");
  }



  if(strcmp(iucrname, "KIDNAPPING ") == 0) {
    // printf("matches\n");
    strcpy(color, "#3399ff");
  }
  if(strcmp(iucrname, "OFFENSE INVOLVING CHILDREN ") == 0) {
    // printf("matches\n");
    strcpy(color, "#0066cc");
  }



  if(strcmp(iucrname, "SEX OFFENSE ") == 0) {
    // printf("matches\n");
    strcpy(color, "#9900ff");
  }
  if(strcmp(iucrname, "PROSTITUTION ") == 0) {
    // printf("matches\n");
    strcpy(color, "#660099");
  }

  if(strcmp(iucrname, "WEAPONS VIOLATION ") == 0) {
    // printf("matches\n");
    strcpy(color, "#993300");
  }
  if(strcmp(iucrname, "STALKING ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cc6633");
  }
  if(strcmp(iucrname, "INTIMIDATION ") == 0) {
    // printf("matches\n");
    strcpy(color, "#663300");
  }
  if(strcmp(iucrname, "INTERFERENCE WITH PUBLIC OFFICER ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cccccc");
  }
  if(strcmp(iucrname, "RITUALISM ") == 0) {
    // printf("matches\n");
    strcpy(color, "#999999");
  }
  if(strcmp(iucrname, "ARSON ") == 0) {
    // printf("matches\n");
    strcpy(color, "#666666");
  }	
  if(strcmp(iucrname, "DECEPTIVE PRACTICE ") == 0) {
    // printf("matches\n");
    strcpy(color, "#333333");
  }
  if(strcmp(iucrname, "GAMBLING ") == 0) {
    // printf("matches\n");
    strcpy(color, "#cc9966");
  }
  if(strcmp(iucrname, "ASSAULT ") == 0) {
    // printf("matches\n");
    strcpy(color, "#ff00cc");
  }
  if(strcmp(iucrname, "CRIMINAL TRESPASS ") == 0) {
    // printf("matches\n");
    strcpy(color, "#996633");
  }

  return color;
}




char * startbox(double x, double y, double width, double height) {
	char * frame = calloc(200, sizeof(char));
	char * x_str = calloc(20, sizeof(char));
	char * y_str = calloc(20, sizeof(char));
	char * h_str = calloc(20, sizeof(char));
	char * w_str = calloc(20, sizeof(char));

	strcpy(frame, "\n\n");
	strcat(frame, "<rect x=\"");

	sprintf(x_str, "%f", x);
	strcat(frame, x_str);

	strcat(frame, "\" y=\"");

	sprintf(y_str, "%f", y);
	strcat(frame, y_str);
	free(y_str);
	
	strcat(frame, "\" fill=\"none\" width=\"");
	
	sprintf(w_str, "%f", width);
	strcat(frame, w_str);
	free(w_str);

	strcat(frame, "\" height=\"");

	sprintf(h_str, "%f", height);
	strcat(frame, h_str);

	strcat(frame, "\"/>\n<text transform=\"matrix(1 0 0 1 "); 
	strcat(frame, x_str);
	free(x_str);
	
	sprintf(h_str, " %f", height*2);
	strcat(frame, h_str);
	free(h_str);

	strcat(frame, ")\">");
	return frame;
}

char * makeword(double x, double y, char * color, char * fontsize, char * word) {
	char * frame = calloc(200, sizeof(char));
	char * x_str = calloc(20, sizeof(char));
	char * y_str = calloc(20, sizeof(char));	

	strcpy(frame, "\n");
	strcat(frame, "<tspan x=\"");

	sprintf(x_str, "%f", x);
	strcat(frame, x_str);
	free(x_str);

	strcat(frame, "\" y=\"");

	sprintf(y_str, "%f", y);
	strcat(frame, y_str);
	free(y_str);

	strcat(frame, "\" fill=\"");
	strcat(frame, color);
	strcat(frame, "\" font-family=\"'ArialMT'\" font-size=\"");
	strcat(frame, fontsize);

	strcat(frame, "\">");
	strcat(frame, word);
	strcat(frame, "</tspan>");
	return frame;
}

char * parseflag(char * flag) {
	int i = 2; 
	char c, * text;
	text = calloc(40, sizeof(char));

	while(c = flag[i]) {
		if(c == '-') {
			text[i-2] = ' ';
		}
		else {
			text[i-2] = c;
		}
		++i;
	}
	return text;
}

char * getcolor(char * flag) {
	if(strcmp(flag, "--homicide") == 0) {
		return "#ff0000";
	}
	if(strcmp(flag, "--criminal-sexual-assault") == 0) {
		return "#cc3366";
	}
	if(strcmp(flag, "--criminal-damage") == 0) {
		return "#ff0033";
	}
	if(strcmp(flag, "--battery") == 0) {
		return "#cc0033";
	}


	if(strcmp(flag, "--burglary") == 0) {
		return "#ff3300";
	}
	if(strcmp(flag, "--theft") == 0) {
		return "#ff6600";
	}
	if(strcmp(flag, "--motor-vehicle-theft") == 0) {
		return "#ff6633";
	}
	if(strcmp(flag, "--robbery") == 0) {
		return "#cc3300";
	}


	if(strcmp(flag, "--public-indecency") == 0) {
		return "#ffcc00";
	}
	if(strcmp(flag, "--obscenity") == 0) {
		return "#ffcc33";
	}
	if(strcmp(flag, "--public-peace-violation") == 0) {
		return "#ffff00";
	}


	if(strcmp(flag, "--narcotics") == 0) {
		return "#33cc33";
	}
	if(strcmp(flag, "--liqour-law-violation") == 0) {
		return "#006600";
	}


	if(strcmp(flag, "--kidnapping") == 0) {
		return "#3399ff";
	}
	if(strcmp(flag, "--offense-involving-children") == 0) {
		return "#0066cc";
	}


	if(strcmp(flag, "--sex-offense") == 0) {
		return "#9900ff";
	}
	if(strcmp(flag, "--prostitution") == 0) {
		return "#660099";
	}


	if(strcmp(flag, "--weapons-violation") == 0) {
		return "#993300";
	}
	if(strcmp(flag, "--stalking") == 0) {
		return "#cc6633";
	}
	if(strcmp(flag, "--intimidation") == 0) {
		return "#663300";
	}
	if(strcmp(flag, "--interference-with-public-officer") == 0) {
		return "#cccccc";
	}
	if(strcmp(flag, "--ritualism") == 0) {
    		return "#999999";
	}
	if(strcmp(flag, "--arson") == 0) {
		return "#666666";
	}
	if(strcmp(flag, "--deceptive-practice") == 0) {
		return "#333333";
	}
	if(strcmp(flag, "--gambling") == 0) {
		return "#cc9966";	
	}
	if(strcmp(flag, "--assault") == 0) {
		return "#ff00cc";	
	}
	if(strcmp(flag, "--criminal-trespass") == 0) {
		return "#996633";	
	}
	else {
		printf("%s is not a valid flag.  Run ./crimes ops for valid options\n", flag);
	}
}


double labelsingle(char * flag, double x, double y, double width, double height, FILE * fp) {
	char * xmlflag, * word, * flagcolor, * text;
	double increase, xcurrent, ycurrent;
	double vertical = 6.2;

	xmlflag = calloc(3000, sizeof(char));

	flagcolor = getcolor(flag);
	//printf("%s\n", flagcolor);
	text = parseflag(flag);
	//printf("%s\n", text);

	increase = 0;
	ycurrent = height;

	word = startbox(x, y, width, height);
	strcat(xmlflag, word);
	increase += vertical;
	free(word);
	
	word = makeword(0, increase, flagcolor, "5", text);
	strcat(xmlflag, word);
	increase += vertical;
	free(word);

	strcat(xmlflag, "</text>");
	fwrite(xmlflag, strlen(xmlflag), 1, fp);

	free(text);
	free(xmlflag);
	return ycurrent + (increase/2);

}


double labelglob(char * flag, double x, double y, double width, double height, FILE * fp) {
	// make space for xml flag (remember, this will probably be big )	
	char * xmlflag, * word;
	double increase, xcurrent, ycurrent;
	double vertical = 6.2;

	xmlflag = calloc(3000, sizeof(char));
	strcpy(xmlflag, "");

	if(strcmp(flag, "-all") == 0) {
    		strcpy(flag, "-vtpdcs");
	}
	ycurrent = height;

	if(exhaust(flag, 'v')) {
		increase = 0;

		word = startbox(x, y, width, height);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);
		
		word = makeword(0, increase, "#ff0000", "5", "violent crime");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff0000", "5", "    homicide");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);	

		word = makeword(0, increase, "#cc3366", "5", "    criminal sexual assault");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff0033", "5", "    criminal damage");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#cc0033", "5", "    battery");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);
		
		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);	
  	}
	if(exhaust(flag, 't')) {
		increase = 0;

		word = startbox(x, y, width, ycurrent);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff3300", "5", "theft crime");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff3300", "5", "    burglary");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff6600", "5", "    theft");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ff6633", "5", "    motor vehicle theft");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#cc3300", "5", "    robbery");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);
		
		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);				
	}
	if(exhaust(flag, 'p')) {
		increase = 0;

		word = startbox(x, y, width, ycurrent);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ffcc00", "5", "public offense");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ffcc00", "5", "    public indecency");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ffcc33", "5", "    obscenity");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#ffff00", "5", "    public peace violation");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);
	}
	if(exhaust(flag, 'd')) {
		increase = 0;

		word = startbox(x, y, width, ycurrent);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#33cc33", "5", "drug related crime");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#33cc33", "5", "    narcotics");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#006600", "5", "    liqour law violation");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);
	}
	if(exhaust(flag, 'c')) {
		increase = 0;

		word = startbox(x, y, width, ycurrent);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#3399ff", "5", "child related crime");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#3399ff", "5", "    kidnapping");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#0066cc", "5", "    offense involving children");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);	    
	}
	if(exhaust(flag, 's')) {
		increase = 0;

		word = startbox(x, y, width, ycurrent);
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#9900ff", "5", "sexual crime");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#9900ff", "5", "    sexual offense");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#cc3366", "5", "    criminal sexual assault");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);

		word = makeword(0, increase, "#660099", "5", "    prostitution");
		strcat(xmlflag, word);
		increase += vertical;
		free(word);
		
		strcat(xmlflag, "</text>");
		fwrite(xmlflag, strlen(xmlflag), 1, fp);
		strcpy(xmlflag, "");

		ycurrent += (increase/2);
	}

	free(xmlflag);
	return ycurrent;
}

void to_legend(char ** flags, double x, double y, double width, double height, FILE * fp) {
	char * f;
	double newheight = height;
	int i = 0;

	newheight = height;
	while(f = flags[i]) {
		if(f[1] == '-') {
			newheight = labelsingle(f, x, y, width, newheight-1.5, fp);
		}
		else {
			newheight = labelglob(f, x, y, width, newheight, fp);
		}	
		++i;
	}
	free(f);
	return;
}


char * add_to_file(struct crime * c) {

  char * path, *hold;
  path = malloc(600*sizeof(char));
  char x[50];
  char y[50];
  char z[50];
  sprintf(x, "%f", c->lon);
  sprintf(y, "%f", c->lat);
  sprintf(z, "%f", (c->lon)+1.7797518);

  strcpy(path, "\n\n");
  strcat(path, "<path sodipodi:type=\"arc\"\n style=\"fill:");
  hold = color_crime(c->IUCRname);
  strcat(path, hold);
  free(hold);
  strcat(path, ";fill-rule:evenodd;stroke:#000000;stroke-width:0px;stroke-linecap:butt;stroke-linejoin:miter;stroke-opacity:1\"\n id=\"path13008\"\n"); 
  strcat(path, "sodipodi:cx=\"");
  strcat(path, x); 
  strcat(path, "\"\n"); 
  strcat(path, "sodipodi:cy=\""); 
  strcat(path, y);
  strcat(path, "\"\n");
  strcat(path, "sodipodi:rx=\"1.7797518\"\n sodipodi:ry=\"1.7797518\"\n d=\"m ");
  strcat(path, z);
  strcat(path, ",");
  strcat(path, y);
  strcat(path, " a 1.7797518,1.7797518 0 1 1 -3.5595,0 1.7797518,1.7797518 0 1 1 3.5595,0 z\" />");
  return path;
}

void build_svg(struct crimelist * cs, FILE * fp, char ** flag) {
	char svgpath[] = "</svg>", *new, *legend;
	struct crime c;
	int i = 0;

	while(i < cs->numcrimes) {
		c = (cs->crimes)[i];
		if(flag != NULL) {
			if(crimefilter(&c, flag)) {
				new = add_to_file(&c);
				//	printf("num crime %i\n", i); 
				//      fprintf(stderr, "%d\n", strlen(new));
				fwrite(new, strlen(new), 1, fp);
				free(new);
			}
		}
		else {
			new = add_to_file(&c);
			//	printf("num crime %i\n", i); 
			//      fprintf(stderr, "%d\n", strlen(new));
			fwrite(new, strlen(new), 1, fp);
			free(new);
		}
		++i;
	}

	// add legend : choose a reasonable starting height
	if(flag == NULL) {
		flag = calloc(12, sizeof(char *));
		flag[0] = "-vtpdcs";
		flag[1] = "--weapons-violation";
		flag[2] = "--stalking"; 
		flag[3] = "--assault";
		flag[4] = "--intimidation"; 
		flag[5] = "--interference-with-public-officer";
		flag[6] = "--ritualism";
		flag[7] = "--arson";
		flag[8] = "--deceptive-practice";
		flag[9] = "--gambling";
		flag[10] = "--criminal-trespass";
	}
	to_legend(flag, 53.655, 50, 181.379, 115.104, fp);
 
	fwrite(svgpath, strlen(svgpath), 1, fp); 
	return;
}




