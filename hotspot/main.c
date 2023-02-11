#include <unistd.h>
#include <stdio.h>
void *Runhotspot(int);
int main(void) { 
  if(fork()==0) {
    if(fork()==0) {
      Runhotspot(4);
      return 1;
    }
    else {
      if(fork()==0) {
        Runhotspot(0);
        return 1;
      }
      if(fork()==0) {
        Runhotspot(8);
        return 1;
      }
#if 0
      if(fork()==0) {
        Runhotspot(2);
        return 1;
      }
      if(fork()==0) {
        Runhotspot(3);
        return 1;
      }
      if(fork()==0) {
        Runhotspot(8);
        return 1;
      }
      if(fork()==0) {
        Runhotspot(0);
        return 1;
      }
      if(fork()==0) {
        Runhotspot(6);
        return 1;
      }
#endif
      return 1;
    }
  }
  else return 1;
}
