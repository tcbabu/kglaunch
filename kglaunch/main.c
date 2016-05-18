#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void *Runkglaunch(void *);
int KillOtherJobs(char *name) {
   char buff[300];
   int Id=0,Okay=0,Pid,ln,i;
   char tty[50],dummy[50],program[100];
   FILE *pp;
   char *pt;
   ln =strlen(name);
   while(name[ln]<=' ')name[ln--]='\0';
   while((ln>=0)&&(name[ln]!='/')) ln--;
   pt=name+ln+1;
   Pid = getpid();
   while(!Okay) {
     pp = popen("ps -e","r");
     if(pp==NULL) return 0;
     fgets(buff,299,pp);
     Okay =1;
     fgets(buff,299,pp);
     while( fgets(buff,299,pp) != NULL) {
        sscanf(buff,"%d%s%s%s",&Id,tty,dummy,program);
        if(strcmp(pt,program)==0) {
             if(Id==Pid) continue;
#if 1
             kill(Id,9);
             Okay =0;
#else
             exit(0);
#endif
        }
     }
     pclose(pp);
   }
   return Id;
}
int main(int argc,char **argv) {  
  if( getenv("HOME") != NULL) chdir(getenv("HOME"));
  KillOtherJobs(argv[0]);
  Runkglaunch(NULL);
  return 1;
}
