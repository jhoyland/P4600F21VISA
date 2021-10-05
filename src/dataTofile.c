#include <stdio.h>
#include <stdlib.h>

void dataTofile(double *data, char *filename, int ndata)
{
	char filenamedotdat[64];
	sprintf(filenamedotdat, "%s.dat", filename);

	FILE* outputfile =   fopen(filenamedotdat,"w");
  if(outputfile != NULL)
  {
    for(int i = 0; i < ndata; i++)
      {
        fprintf(outputfile,"\n%0.5f",data[i]);

      }
      fclose(outputfile);
  }
}