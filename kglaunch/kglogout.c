#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<string.h>
#include <sys/types.h>
#include <signal.h>
#include <kulina.h>
int killxvnc(char *env) {
  FILE *pf;
  char buff[200],dummy[50],sock[100];
  int ret=0,pid;
  int display,mydsp;
  char *pt;
  pt = strstr(env,":");
  pt++;
  strcpy(buff,pt);
  pt=strstr(buff,".");
  pt[0]=' ';
  sscanf(buff,"%d",&mydsp);
  pf = popen("ps -ef","r");
  while( fgets(buff,199,pf) != NULL) {
     if(strstr(buff,"Xvnc") == NULL ) continue;
     pt = strstr(buff,"unixpath=");
     if(pt == NULL ) continue;
     pt += 9;
//     printf("%s\n",pt);
//     printf("%s\n",sock);
     if(pt == NULL ) continue;
     sscanf(pt,"%s",sock);
     sscanf(buff,"%s%d",dummy,&pid);
     
     pt = strchr(sock,'.');
     strncpy(dummy,pt+1,40);
     pt = strchr(dummy,'.');
     pt[0]= ' ';
     sscanf(dummy,"%d",&display);
     if(mydsp==display) {
      if(kill(pid,9)) { 
        sprintf(dummy,"/tmp/X%-d-lock",display);
        remove(dummy);
        sprintf(dummy,"/tmp/X11d-unix/X%-d",display);
        remove(dummy);
        strcpy(dummy,sock);
        dummy[5]='.';dummy[6]='L';dummy[7]='K';
        remove(dummy);
      }
     }
     ret=1;
  }
  return ret;
}

int CheckString(char *s1,char *s2) {
   int ch,ln,ret=0;
   ln = strlen(s2);
   if(strlen(s1)<ln) ret=0;
   else {
     ch = s1[ln];
     s1[ln]='\0';
     if( strcmp(s1,s2)==0 ) ret=1;
     s1[ln]=ch;
   }
   return ret;
}
int SearchString(char *s1,char *s2) {
   int ch,ln,ret=-1,ln1,i=0;
   ln = strlen(s2);
   ln1 = strlen(s1);
   if(ln1<ln) ret=-1;
   else {
    i=0;
    for(i=0;i<=(ln1-ln);i++) {
      if(CheckString(s1+i,s2)){
        ret=i;
        break;
      }
    }
   }
   return ret;
}
int changejob(char *job){
   FILE *fp,*fp1;
   int pip[2],pid,status,pip2[2];
   char *args[100],buff[1000],pt[300];
   char *pgrpath=NULL;
   int i=0,pos=0;
   printf("JOB= %s\n",job);
   if(job==NULL) return 0;
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
   execv(pgrpath,args);
   fprintf(stderr,"Failed to execute \n");
   sleep(5);
   return 0;
}
int HangupXserver(char *name) {
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
#if 1
             kill(Id,SIGHUP);
             Okay =1;
#else
             exit(0);
#endif
        }
     }
     pclose(pp);
   }
   return Id;
}
int CheckProcess(char *procname) {
   char buff[300];
   int Id=0,Okay=0,count=0,ln;
   char tty[50],dummy[50],program[100];
   FILE *pp;
     ln = strlen(procname);
     pp = popen("ps -e","r");
     fgets(buff,299,pp);
     while( fgets(buff,299,pp) != NULL) {
        sscanf(buff,"%d%s%s%s",&Id,tty,dummy,program);
        program[ln]='\0';
        if((strcmp(procname,program)==0)) {
//             printf(" %s : %s\n",procname,program);
             Okay=Id;
             break;
        }
     }
     pclose(pp);
   return Okay;
}
int main(int argc,char **argv) {  
  char buf[200],*env=NULL;
  env = getenv("DISPLAY"); 
  if( strcmp(env,":0.0") !=0 ) {
    killxvnc(env);
  }
  if(SearchString(argv[0],"kglogout")>=0) {
    if(CheckProcess("startkde")) {
       changejob("kdeinit4_shutdown");
    }
//    if(CheckProcess("kdeinit")) {
//       changejob("kdeinit4_shutdown");
//    }
    if(CheckProcess("gnome-session")) {
       changejob("gnome-session-quit");
    }
    if(CheckProcess("xfce4-session")) {
       changejob("xfce4-session-logout");
    }
    changejob("kgLogout");
  }
  if( strcmp(getenv("DISPLAY"),":0.0") ==0 ) {
      strcpy(buf,"Xorg");
      if(HangupXserver(buf)== 0) {
        strcpy(buf,"X");
        HangupXserver(buf);
      }
  }
  
  return 1;

}
