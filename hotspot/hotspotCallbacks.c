#include "kulina.h"
#include <fcntl.h>
extern int Xm,Ym;
#define WAIT(pid) {\
  pid_t w;\
  int status;\
  do { \
                   w = waitpid(pid, &status, WUNTRACED | WCONTINUED); \
                   if (w == -1) { \
                       perror("waitpid"); \
                       exit(EXIT_FAILURE); \
                   }\
               } while (!WIFEXITED(status) && !WIFSIGNALED(status));\
}
int GetLine(int pip0,char *buff){
     unsigned char ch;
     fd_set rfds;
     struct timeval tv;
     int retval,chnl,status,i;
     int ret,val;
     chnl = pip0;
     i=0;
     FD_ZERO(&rfds);
     FD_SET(pip0,&rfds);
     while(1) {
       tv.tv_sec = 10;
       tv.tv_usec =0;
       ret=0;
       retval = select(chnl+1,&rfds,NULL,NULL,&tv);
       val=1;
       if((retval> 0)&&(FD_ISSET(chnl,&rfds))){
         if(read(chnl,&ch,1) != 1){
           ret=0;
           break;
         }
         buff[i++]=ch;
         if( (ch=='\n')||(ch=='\r')) {ret=ch;break;}
       }
       else {ret=-1;break;}
     }
     buff[i]='\0';
     return ret;
}
int WaitForProcess(int pip0,int pip1,int Pid) {
     char buff[1000],device[20],connection[20],reso[30];
     int ch,i=0,j;
     write(pip1,"\n",1);
     while((ch=GetLine(pip0,buff)) ) {
         if(ch< 0) continue;
//          printf("%s\n",buff);
     }
//     printf("Okay Back\n");
     return 1;
}
int runjob(char *job,int (*ProcessOut)(int,int,int)){
   FILE *fp,*fp1;
   int pip[2],pid,status,pip2[2];
   char *args[100],buff[1000],pt[300];
   char *pgrpath=NULL;
   int i=0,pos=0;
   if(job==NULL) return 0;
   if( pipe(pip) < 0) return 0;
   if( pipe(pip2) < 0) return 0;
//   pipew =pip2[1];
   while(job[i]==' ') i++;
   strcpy(buff,job+i);
   i=0;
   while ( sscanf(buff+pos,"%s",pt) > 0 ) {
     if(pt[0]=='\"') {
      pos++;
      args[i]=buff+pos;
      while(buff[pos]!='\"')pos++;
      buff[pos]='\0';
      i++;
     }
     else {
       args[i]=buff+pos;
       pos +=strlen(pt);
       i++;
       if(buff[pos]< ' ') break;
       buff[pos]='\0';
     }
     pos++;
     while(buff[pos]==' ') pos++;
   }
   args[i]=NULL;
   if(i==0) return 0;
   pgrpath=kgWhich(args[0]);
   if (pgrpath==NULL) return 0;
   pid = fork();
   if(pid == 0) { /* child process */
//     if(fork()!=0) exit(0); /* to avoid zombie */
     close(0);
     dup(pip2[0]);
     close(pip2[0]);
     close(1);
     dup(pip[1]);
     close(2);
#if 1
     open("/dev/null",O_WRONLY|O_CREAT,0777);
#else
     dup(pip[1]);
#endif
     close(pip[1]);
     execv(pgrpath,args);
     fprintf(stderr,"Failed to execute \n");
     sleep(5);
     exit(1);
   }
   else {   /* parent process */
//     printf("Waiting pid: %d\n",pid);
     close(pip2[0]);
     close(pip[1]);
     if(ProcessOut != NULL)ProcessOut(pip[0],pip2[1],pid);
     WAIT(pid);
     free(pgrpath);
     return pid;
   }
}
int changejob(char *job){
   FILE *fp,*fp1;
   int pip[2],pid,status,pip2[2];
   char *args[100],buff[1000],pt[300];
   char *pgrpath=NULL;
   int i=0,pos=0;
   if(job==NULL) return 0;
   if(job[0]=='\0') return 0;
   if((pid=fork())==0) {
     if(fork()!= 0) exit(0);
   }
   else {
     WAIT(pid);
     return 0;
   }
   while(job[i]==' ') i++;
   strcpy(buff,job+i);
   
   i=0;
   while ( sscanf(buff+pos,"%s",pt) > 0 ) {
     if(pt[0]=='\"') {
      pos++;
      args[i]=buff+pos;
      while(buff[pos]!='\"')pos++;
      buff[pos]='\0';
      i++;
     }
     else {
       args[i]=buff+pos;
       pos +=strlen(pt);
       i++;
       if(buff[pos]< ' ') break;
       buff[pos]='\0';
     }
     pos++;
     while(buff[pos]==' ') pos++;
   }
   args[i]=NULL;
   if(i==0) return 0;
   if(args[0][0]=='/') pgrpath=args[0];
   else pgrpath=kgWhich(args[0]);
   if (pgrpath==NULL) return 0;
   execv(pgrpath,args);
   fprintf(stderr,"Failed to execute \n");
   sleep(5);
   exit(1);
}
int LaunchJob(char *Command) {
      char buff[500];
      changejob(Command);
      sprintf(buff,"Launching %-s Pl. wait...",Command);
      kgSplashMessage(NULL,Xm,Ym,200,30,buff,12,53,50);
      return 1;
}

int  hotspotbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  char HomeDir[200],command[500];
  int n,ret =0,Sel; 
  KBEVENT *kbe;
  D = (DIALOG*)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  Sel = *((int *)(D->pt));
  switch(Sel) {
     case 0:
      LaunchJob("firefox");
     break;
     case 2:
      LaunchJob("kgclock");
     break;
     case 3:
      LaunchJob("gimp");
     break;
     case 4:
      system("kglaunch");
     break;
     case 8:
      system("kglogout");
     break;
     case 6:
      if(kgWhich("xfce4-terminal") != NULL) {
        sprintf(command,"xfce4-terminal --default-working-directory=%-s",
          getenv("HOME"));
      }
      else {
        sprintf(command,"konsole --workdir %-s",
          getenv("HOME"));
      }
      system(command);
     break;
     default:
     break;
  }
  return ret;
}
void  hotspotbutton1init(DIN *B,void *pt) {
}
int hotspotinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int hotspotcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  return ret;
}
int hotspotCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int hotspotResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  kgGetWindowSize(D,&xres,&yres);
  dx = xres - D->xl;
  dy = yres - D->yl;
  /* extra code */
  D->xl= xres;
  D->yl= yres;
  kgRedrawDialog(D);
  return ret;
}
int hotspotWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
