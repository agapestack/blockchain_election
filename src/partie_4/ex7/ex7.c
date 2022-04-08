#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

#include "block.h"

int main(void) {
  printf("----------START TEST OPENSSL----------\n");
  const char *s =  "Rosetta code";
  unsigned char *d = SHA256(s, strlen(s), 0);
  
  for(int i=0; i < SHA256_DIGEST_LENGTH; i++) {
    printf("%02x", d[i]);
  }
  putchar('\n');
  printf("----------END TEST OPENSSL----------\n\n\n");

  printf("----------START CUSTOM SHA256----------\n");
  char *str_test = "Rosetta code";
  unsigned char *res = hash_sha256(str_test);
  printf("%s\n", res);
  printf("----------END CUSTOM SHA256----------\n\n\n");

  return 0;
}
