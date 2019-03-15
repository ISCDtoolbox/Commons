/* simulation of a chronograph
 * modified (08/2010) for // usage */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "chrono.h"


void  chrono(int cmode,mytime *ptt) {

  if ( cmode == RESET ) {
    ptt->call = 0;
    ptt->gini = ptt->gend = ptt->gdif = 0.0;
    ptt->sini = ptt->send = ptt->sdif = 0.0;
    ptt->uini = ptt->uend = ptt->udif = 0.0;
  }
  else {
#ifdef POSIX
    gettimeofday(&(ptt->rutim), NULL);
#else
	  QueryPerformanceCounter(&ptt->rutim);

    GetProcessTimes(ptt->thisProcess, &ptt->ftIni, &ptt->ftEnd, &ptt->ftSys, &ptt->ftUser);
    FileTimeToSystemTime(&ptt->ftSys , &ptt->stSys );
    FileTimeToSystemTime(&ptt->ftUser, &ptt->stUser);
#endif
    if ( cmode == ON ) {
#ifdef POSIX
      ptt->gini  = (double)((ptt->rutim.tv_sec ) + (ptt->rutim.tv_usec) * BIG1);

      getrusage(RUSAGE_SELF,&(ptt->ru));
      ptt->rutim = ptt->ru.ru_utime;
      ptt->uini  = (double)((ptt->rutim.tv_sec) * BIG + (ptt->rutim.tv_usec));
      ptt->rutim = ptt->ru.ru_stime;
      ptt->sini  = (double)((ptt->rutim.tv_sec )* BIG + (ptt->rutim.tv_usec));
#else
      ptt->gini = (double)(ptt->rutim.QuadPart / ptt->frequency.QuadPart);

      ptt->uini = ((double)ptt->stUser.wHour * 3600 + (double)ptt->stUser.wMinute * 60
        + (double)ptt->stUser.wSecond) * BIG + (double)ptt->stUser.wMilliseconds * 1000;
      ptt->sini = ((double)ptt->stSys.wHour * 3600 + (double)ptt->stSys.wMinute * 60
        + (double)ptt->stSys.wSecond) * BIG + (double)ptt->stSys.wMilliseconds * 1000;
#endif
    }
    else if ( cmode == OFF ) {
#ifdef POSIX
      ptt->gend  = (double)((ptt->rutim.tv_sec ) + (ptt->rutim.tv_usec) * BIG1);

      getrusage(RUSAGE_SELF,&(ptt->ru));
      ptt->rutim = ptt->ru.ru_utime;
      ptt->uend  = (double)((ptt->rutim.tv_sec ) * BIG + (ptt->rutim.tv_usec));
      ptt->rutim = ptt->ru.ru_stime;
      ptt->send  = (double)((ptt->rutim.tv_sec ) * BIG + (ptt->rutim.tv_usec));
#else
      ptt->gend = (double)(ptt->rutim.QuadPart / ptt->frequency.QuadPart);

      ptt->uend = ((double)ptt->stUser.wHour * 3600 + (double)ptt->stUser.wMinute * 60
        + (double)ptt->stUser.wSecond) * BIG + (double)ptt->stUser.wMilliseconds * 1000;
      ptt->send = ((double)ptt->stSys.wHour * 3600 + (double)ptt->stSys.wMinute * 60
        + (double)ptt->stSys.wSecond) * BIG + (double)ptt->stSys.wMilliseconds * 1000;
#endif

      ptt->gdif += ptt->gend - ptt->gini;

      ptt->udif += (ptt->uend - ptt->uini) * BIG1;
      ptt->sdif += (ptt->send - ptt->sini) * BIG1;

      ptt->call++;
    }
  }
}


/** initialize time table */
void  tminit(mytime *t,int maxtim) {
  mytime  *ptt;
  int      k;

#ifndef POSIX
  QueryPerformanceFrequency(&t[0].frequency);

  t[0].thisProcess = GetCurrentProcess();
  for (k = 1; k < maxtim; k++) {
    t[k].frequency   = t[0].frequency;
    t[k].thisProcess = t[0].thisProcess;
  }
#endif
  for (k=0; k<maxtim; k++) {
    ptt = &t[k];
    ptt->call = 0;
    ptt->gini = ptt->gend = ptt->gdif = 0.0;
    ptt->sini = ptt->send = ptt->sdif = 0.0;
    ptt->uini = ptt->uend = ptt->udif = 0.0;
  }
}


/** print real time */
void printim(double elps,char *stim) {
  int    hh,mm,ss;

  if ( elps < 60.0 )
    sprintf(stim,"%5.3lfs",elps);
  else if ( elps < 3600.0 ) {
    mm = elps / 60.0;
    ss = (int)elps - mm * 60;
    sprintf(stim,"%dm%ds (%7.3lfs)",mm,ss,elps);
  }
  else {
    hh = elps / 3600;
    mm = (elps - hh*3600) / 60;
    ss = elps - mm*60 - hh*3600;
    sprintf(stim,"%dh%dm%ds",hh,mm,ss);
  }
}

/* print and return real time */
char *getim(double elps) {
  int    hh,mm,ss;
  char  *data;
	
  data = malloc(32*sizeof(char));
  assert(data);
  if ( elps < 60.0 )
    sprintf(data,"%5.3lfs",elps);
  else if ( elps < 3600.0 ) {
    mm = elps / 60.0;
    ss = (int)elps - mm * 60;
    sprintf(data,"%dm%ds (%7.3lfs)",mm,ss,elps);
  }
  else {
    hh = elps / 3600;
    mm = (elps - hh*3600) / 60;
    ss = elps - mm*60 - hh*3600;
    sprintf(data,"%dh%dm%ds",hh,mm,ss);
  }

  return(data);
}
