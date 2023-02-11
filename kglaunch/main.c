#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include<string.h>
#include<signal.h>
void *Runkglaunch(void *);

int CheckProcessDisplay(char *curdsp,int pid) {
  int pp;
  char name[3000];
  char *pt;
  int ret=0,count,i;
  sprintf(name,"/proc/%-d/environ",pid);
  pp = open(name ,O_RDONLY);  
  if(pp < 0) return ret;
  while(( count=read(pp,name,2900)) >0) {
     i=0; while(i< count) {
       if((name[i]< ' ') ) name[i]=' ';
       i++;
     }
     name[count]='\n';
     name[count+1]='\0';

     pt =strstr(name,"DISPLAY=");
     if(pt == NULL ) continue;
//     printf("GOT: %s\n",pt);
     pt +=8;
     count= strlen(curdsp);
     strncpy(name,pt,count);
     name[count]='\0';
     if (strcmp(curdsp,name)==0) ret = 1;
     break;
  }
  close(pp);
  
  return ret;
 
}
int KillOtherJobs(char *name) {
   char buff[300];
   int Id=0,Okay=0,Pid,ln,i;
   char tty[50],dummy[50],program[100];
   FILE *pp;
   char *pt;
   char *env;
   ln =strlen(name);
   while(name[ln]<=' ')name[ln--]='\0';
   while((ln>=0)&&(name[ln]!='/')) ln--;
   pt=name+ln+1;
   Pid = getpid();
   env = getenv("DISPLAY");
//   printf("DISPLAY=%s\n",env);
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
             if( CheckProcessDisplay(env,Id)) {
//               printf("Killing : %d\n",Id);
               kill(Id,9);
               Okay =0;
             }
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
  void *Ret;
  if( getenv("HOME") != NULL) chdir(getenv("HOME"));
  KillOtherJobs(basename(argv[0]));
  if(argc > 1){
   if (strcmp(argv[1],"-d") ==0 ) daemon(0,0);
  }
  Ret = Runkglaunch(NULL);
  return 1;
}
