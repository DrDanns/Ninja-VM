#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "support.h"

void fatalError(char *msg) {
  /*TODO: alles in fputs ausgeben*/
  fputs("Fatal error: ", stderr);
  printf("%s\n", msg);
  exit(EXIT_FAILURE);
}

ObjRef newPrimObject(int dataSize) {
  ObjRef objRef;

  if(objRef == NULL) {
    fatalError("cannot allocate memory for objRef.\n")
  }
  
  objRef = allocate(sizeof(unsigned int) +
                  dataSize * sizeof(unsigned char));
  objRef->size = dataSize;

  return objRef;
}
