#ifndef _CHRONO_H
#define _CHRONO_H

#include <time.h>

#if ( defined(_WIN16) || defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
      defined(__TOS_WIN__) || defined(__WINDOWS__) )

#else

#define POSIX

#endif

#ifndef POSIX
#include <windows.h>
#else
#include <sys/time.h>
#include <sys/resource.h>
#endif

#ifndef  ON
#define  RESET  0
#define  ON     1
#define  OFF    2
#endif

#define  BIG      1e6
#define  BIG1     1e-6
#define  TIMEMAX  12

typedef struct mytime {
  double  gini,gend,gdif,uini,uend,udif,sini,send,sdif;
#ifdef POSIX
  struct  timeval rutim;
  struct  rusage  ru;
#else
  HANDLE        thisProcess;
  FILETIME      ftIni, ftEnd, ftSys, ftUser;
  SYSTEMTIME    stSys, stUser;
  LARGE_INTEGER frequency;
  LARGE_INTEGER rutim;
#endif
  int     call;
} mytime;


/* prototypes */
void   chrono(int cmode,mytime *ptt);
void   tminit(mytime *t,int maxtim);
void   printim(double ,char *);
char  *getim(double );

#endif
