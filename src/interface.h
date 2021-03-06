/***** interface.h **********************************************************
 * Description: Cut region from sequence
 * Author: Bernhard Haubold
 * Email: haubold@evolbio.mpg.de
 * License: GNU General Public License, https://www.gnu.org/licenses/gpl.html
 * Date: Tue Jun 11 09:43:14 2019
 ****************************************************************************/
#ifndef INTERFACE
#define INTERFACE

/* define argument container */
typedef struct args{
  char    h; /* help message?         */
  char    v; /* version message?      */
  char  err; /* error                 */
  int     l; /* line length           */
  char   *r; /* regions               */
  char   *f; /* file with regions     */
  char    s; /* spliced?              */
  char **fi; /* input files           */
  int    nf; /* number of input files */
} Args;

Args *getArgs(int argc, char *argv[]);
Args *newArgs();
void freeArgs(Args *args);
void printUsage();
void printSplash(Args *args);

#endif
