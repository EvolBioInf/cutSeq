/***** interface.c **********************************************************
 * Description: Cut region from sequence
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Tue Jun 11 09:43:14 2019
 ****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <bsd/stdlib.h>
#include "interface.h"
#include "error.h"
#include "seq.h"

Args *newArgs() {
  Args *args = (Args *)emalloc(sizeof(Args));
  args->h   = 0;
  args->v   = 0;
  args->err = 0;
  args->l   = DEFAULT_LINE_LEN;
  args->r   = NULL;
  args->f   = NULL;
  args->s   = 0;
  return args;
}

void freeArgs(Args *args) {
  if (args->r)
    free(args->r);
  if (args->f)
    free(args->f);
  free(args);
}

Args *getArgs(int argc, char *argv[]) {
  int c;
  char *optString = "hvsr:f:l:";
  Args *args = newArgs();

  while ((c = getopt(argc, argv, optString)) != -1) {
    switch(c) {
    case 'l': /* line length */
      args->l = atoi(optarg);
      break;
    case 'r': /* regions */
      args->r = estrdup(optarg);
      break;
    case 'f': /* file with regions */
      args->f = estrdup(optarg);
      break;
    case 's': /* spliced? */
      args->s = 1;
      break;
    case 'h': /* help       */
      args->h = 1;
      break;
    case 'v': /* version    */
      args->v = 1;
      break;
    case '?':
      args->err = 1;
      if(optopt == 'i')
	fprintf(stderr, "Error: Option `%c` requires an argument.\n", optopt);
      else if(isprint(optopt))
	fprintf(stderr, "Error: Unknown option `%c`.\n", optopt);
      else
	fprintf(stderr, "Error: Unknown option character `\\x%x`.\n", optopt);
    default:
      args->err = 1;
      return args;
    }
  }
  args->fi = argv + optind;
  args->nf = argc - optind;

  return args;
}

void printUsage() {
  printf("Usage: %s [options] [inputFiles]\n", getprogname());
  printf("Cut regions from molecular sequences\n");
  printf("Example: %s -r 256-665,5-100 foo.fasta\n", getprogname());
  printf("Options:\n");
  printf("\t[-r <REGIIONS>, e.g. 256-665,5-100  ( (use -f for large number of regions)]\n");
  printf("\t[-f <FILE> containing regions (one pair of blank-separated start & end positions per line)\n");
  printf("\t    default: positions read from -r]\n");
  printf("\t[-l <NUM> length; default: %d\n", DEFAULT_LINE_LEN);
  printf("\t[-s splice regions]\n");
  printf("\t[-h print this help message and exit]\n");
  printf("\t[-v print version & program information and exit]\n");
  exit(0);
}

void printSplash(Args *args) {
  printf("%s ", getprogname());
  int l = strlen(VERSION);
  for(int i = 0; i < l - 1; i++)
    printf("%c", VERSION[i]);
  printf(", %s\n", DATE);
  printf("Author: Bernhard Haubold\n");
  printf("License: GNU General Public License, https://www.gnu.org/licenses/gpl.html\n");
  printf("Bugs: haubold@evolbio.mpg.de\n");
  exit(0);
}
