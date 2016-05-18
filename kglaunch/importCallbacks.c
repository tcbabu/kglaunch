#include "kulina.h"
#include "headers.h"
extern Dlink *Blist;
static Dlink *Dlist=NULL;
extern int Restart;
extern DIALOG *Parent;
void *MakeButList(Dlink *Blist);
int  importbrowser1callback(int item,int i,void *Tmp) {
  DIALOG *D;DIY *Y;void *pt; 
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret=1; 
  int pos,k,x,y;
  D = (DIALOG *)Tmp;
  ThumbNail **th=NULL;
  BUTACTION *bt,*btmp;
  DIY *YB;
  pt = D->pt;
  Y = (DIY *)kgGetWidget(Tmp,i);
  YB = (DIY *)kgGetWidget(Tmp,1);
  th = (ThumbNail **)kgGetList(YB);
  if(kgDragThumbNail(Y,item-1,&x,&y)) {
     pos = kgGetThumbNailItem(YB,x,y);
     if(pos>=0 ) {
       Dposition(Dlist,item);
       bt = (BUTACTION *) Getrecord(Dlist);
       btmp = (BUTACTION *) malloc(sizeof(BUTACTION));
       strcpy(btmp->Command,bt->Command);
       strcpy(btmp->Name,bt->Name);
       strcpy(btmp->Icon,bt->Icon);
       Dposition(Blist,pos+1);
       Dinsert(Blist,btmp);
       kgFreeThumbNails(th);
       th = (ThumbNail **)MakeButList(Blist);
       kgSetList(YB,(void **)th);
       YB->pt=(void *)th;
       kgUpdateWidget(YB);
       kgUpdateOn(Tmp);
       WriteRecords();
       Restart=1;
       kgSetExit(Parent);
     }
     
  }
  return ret;
}
void *MakeButList(Dlink *Blist) {
  int i,k;
  int count;
  char Icon[500];
  void *img;
  ThumbNail **th=NULL;
  
  BUTACTION *bt;
  count = Dcount(Blist);
  th=(ThumbNail **)malloc(sizeof(ThumbNail *)*(count+1));
  for(i=0;i<=count;i++) th[i]=NULL;
  Resetlink(Blist);
  k=0;
  while((bt=(BUTACTION *)Getrecord(Blist))!= NULL) {
    i = strlen(bt->Name);
    while((i>=0)&&(bt->Name[i]<=' ')) bt->Name[i--]='\0';
    if(i< 0) bt->Name[i]='\0';
    i = strlen(bt->Icon);
    while((i>=0)&&(bt->Icon[i]<=' ')) bt->Icon[i--]='\0';
    if(i< 0) bt->Icon[i]='\0';
    strcpy(Icon,"##");
    strcat(Icon,bt->Icon);
    i = strlen(bt->Command);
    while((i>=0)&&(bt->Command[i]<=' ')) bt->Command[i--]='\0';
    if(i< 0) bt->Command[i]='\0';
    i=k;
    k++;
    th[i]=(ThumbNail *)malloc(sizeof(ThumbNail));
    th[i]->name = (char *)malloc(strlen(bt->Name)+1);
    strcpy(th[i]->name,bt->Name);
    img = kgGetImageCopy(NULL,Icon);
    th[i]->img= kgChangeSizeImage(img,48,48);
    kgFreeImage(img);
//    th[i]->img= NULL;
    th[i]->sw=0;
  }
  return (void *)th;
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

static int comppath(void *pt1,void *pt2) {
  return strcmp((char *)pt1,(char *)pt2);
}
static int compdup(void *pt1,void *pt2) {
  int ret;
  ret=strcmp((char *)pt1,(char *)pt2);
  if(ret==0) {return 1;}
  else return 0;
}
static char *TryString(char *buff1,char *m1,char *str,char *pgr){
  char *res=NULL;
  char buff2[500];
  char buff3[500];
  char **m2;
  char **m3;
  int k,l; 
  strcpy(buff2,buff1);
  strcat(buff2,"/");
  strcat(buff2,m1);
  m2 = kgFolderMenu(buff2);
  if(m2==NULL) {return NULL;}
  if(m2[0]==NULL) { kgFreeDouble((void **)m2);return NULL;}
  k=0;
  while(m2[k]!= NULL){
           strcpy(buff3,buff2);
           strcat(buff3,"/");
           strcat(buff3,m2[k]);
           if((str!=NULL)&&(SearchString(buff3,str)<0)) {k++;continue;}
           m3 = kgFileMenu(buff3,"*.png");
           if(m3==NULL) return res;
           if(m3[0]==NULL) { kgFreeDouble((void **)m3);return res;}
           l=0;
           while(m3[l]!= NULL){
              if(SearchString(m3[l],pgr)>=0) {
                strcat(buff3,"/");
                strcat(buff3,m3[l]);
                res =(char *)malloc( strlen(buff3)+1);
                strcpy(res,buff3);
                break;
              }
              l++;
           }
           if(m3!= NULL) kgFreeDouble((void **)m3);
           if(res != NULL) break;
           k++;
  }
  kgFreeDouble((void **)m2);
  return res;
}
static int compname(void *pt1,void *pt2) {
  char *s1,*s2;
  s2 = (char *)pt2;
  if(SearchString(s2,"scala")>=0 ) return 1;
  s1 = (char *)pt1;
  if( isdigit(s1[0])&&isdigit(s2[0])){
    int n1,n2,i;
    n1=0;
    i=0;
    while( isdigit(s1[i])) {n1 = n1*10+(s1[i]-'0');i++;}
    n2=0;
    i=0;
    while( isdigit(s2[i])) {n2 = n2*10+(s2[i]-'0');i++;}
    if(n2>n1) return 1;
  }
  return 0;
}
char *uiSearchFolder(char *Folder,char *Icon) {
  char **Dirs,**Files;
  char *res=NULL,*cpt;
  char buff[500];
  int i,l;
  Dlink *L;
  Files = kgFileMenu(Folder,"*.png");
  if(Files != NULL) {
    if(Files[0]!= NULL) {
      i=0;
      while(Files[i]!= NULL){
       l=i;
       i++;
       if(SearchString(Files[l],Icon)>=0) {
           strcpy(buff,Folder);
           strcat(buff,"/");
           strcat(buff,Files[l]);
           res =(char *)malloc( strlen(buff)+1);
           strcpy(res,buff);
           break;
       }
      }
    } // Files[0]
    kgFreeDouble((void **)Files);
    if(res != NULL) return res;
  }
/*  Going down throuch Folders */

  Dirs = kgFolderMenu(Folder);
  if(Dirs==NULL) return res;
  if(Dirs[0]==NULL) { kgFreeDouble((void **)Dirs); return res;}
  L = Dopen();
  i=0;
  while(Dirs[i]!= NULL) {Dadd(L,Dirs[i]);i++;}
  free(Dirs);
  Dsort(L,compname);
  Resetlink(L);
  while ( (cpt=(char *)Getrecord(L))!=NULL) {
    strcpy(buff,Folder);
    strcat(buff,"/");
    strcat(buff,cpt);
    res = uiSearchFolder(buff,Icon);
    if(res != NULL) break;
  }
  Dempty(L);
  return res;
}
char *kgWhichIcon(char *pgr,char *theme) {
/* Caller must free result if it is not NULL */
  int i=0,j,k=0,End=0;
  char *pt,**m,*res=NULL,*cpt,**m1,**m2;
  char buff[500];
  char buff1[500];
  char buff2[500];
  char path[5000];
  Dlink *L;
  if(pgr[0]=='/') {
    int l;
    char **m,*pt1;
    strcpy(path,pgr);
    pt=path;
    l = strlen(pt);
    while(pt[l]!='/') l--;
    if(l==0) {
     m = kgFileMenu("/",pt+1);
    }
    else {
     pt1=pt+l+1;
     pt[l]='\0';
     m = kgFileMenu(pt,pt1);
    }
    if( (m==NULL)) {return NULL;}
    if( (m[0]==NULL)) {kgFreeDouble((void **)m);return NULL;}
    kgFreeDouble((void **)m);
    res = (char *)malloc(strlen(pgr)+1);
    strcpy(res,pgr);
    return res;
  } 
  pt = getenv("XDG_DATA_DIRS");
  if(pt==NULL) strcpy(path,"/usr/share");
  else strcpy(path , getenv("XDG_DATA_DIRS"));
  L = Dopen();
  while(!End) {
    j=i;
    if(pt[j]< ' ') break;
    while(path[j]!=':') {
      if(path[j]<' ') {End=1;break;}
      j++;
    }
    path[j]='\0';
    cpt = (char *)malloc(strlen(path+i)+1);
    strcpy(cpt,path+i);
    Dadd(L,cpt);
    i=j+1;
  }
  Dsort(L,comppath);
  Drmvdup_cond(L,compdup);
  Resetlink(L);
  while( (pt = (char *)Getrecord(L))!=NULL) {
    strcpy(buff,pt);
    strcat(buff,"/");
    strcat(buff,"icons");
    m = kgFolderMenu(buff);
    if(m==NULL) continue;
    if(m[0]==NULL) { kgFreeDouble((void **)m);continue;}
    i=0;
    while(m[i]!= NULL){
//      printf("THEME: %s : %s\n",m[i],theme);
      if(SearchString(m[i],theme)< 0) {i++;continue;}
      strcpy(buff1,buff);
      strcat(buff1,"/");
      strcat(buff1,m[i]);
      res  = uiSearchFolder(buff1,pgr);
      if(res != NULL) break;
      i++;
    }
  }
  Dempty(L);
  return res;
}
char *kgWhichIcon_o(char *pgr,char *theme) {
/* Caller must free result if it is not NULL */
  int i=0,j,k=0,End=0;
  char *pt,**m,*res=NULL,*cpt,**m1,**m2;
  char buff[500];
  char buff1[500];
  char buff2[500];
  char path[5000];
  Dlink *L;
  if(pgr[0]=='/') {
    int l;
    char **m,*pt1;
    l = strlen(pt);
    while(pt[l]!='/') l--;
    if(l==0) {
     m = kgFileMenu("/",pt+1);
    }
    else {
     pt1=pt+l+1;
     pt[l]='\0';
     m = kgFileMenu(pt,pt1);
    }
    if( (m==NULL)) {return NULL;}
    if( (m[0]==NULL)) {kgFreeDouble((void **)m);return NULL;}
    kgFreeDouble((void **)m);
    res = (char *)malloc(strlen(pgr)+1);
    strcpy(res,pgr);
    return res;
  } 
  pt = getenv("XDG_DATA_DIRS");
  if(pt==NULL) strcpy(path,"/usr/share");
  else strcpy(path , getenv("XDG_DATA_DIRS"));
  L = Dopen();
  while(!End) {
    j=i;
    if(pt[j]< ' ') break;
    while(path[j]!=':') {
      if(path[j]<' ') {End=1;break;}
      j++;
    }
    path[j]='\0';
    cpt = (char *)malloc(strlen(path+i)+1);
    strcpy(cpt,path+i);
    Dadd(L,cpt);
    i=j+1;
  }
  Dsort(L,comppath);
  Drmvdup_cond(L,compdup);
  Resetlink(L);
  while( (pt = (char *)Getrecord(L))!=NULL) {
    strcpy(buff,pt);
    strcat(buff,"/");
    strcat(buff,"icons");
    m = kgFolderMenu(buff);
    if(m==NULL) continue;
    if(m[0]==NULL) { kgFreeDouble((void **)m);continue;}
    i=0;
    while(m[i]!= NULL){
//      printf("THEME: %s : %s\n",m[i],theme);
      if(SearchString(m[i],theme)< 0) {i++;continue;}
      strcpy(buff1,buff);
      strcat(buff1,"/");
      strcat(buff1,m[i]);
      m1 = kgFolderMenu(buff1);
      if(m1==NULL) {i++;continue;}
      if(m1[0]==NULL) { i++;kgFreeDouble((void **)m1);continue;}
      j=0;
      while(m1[j]!= NULL){
//         printf("ICON : %s:%s\n",buff1,m1[j]);
        strcpy(buff2,buff1);
        strcat(buff2,"/");
        strcat(buff2,m1[j]);
        m2 = kgFolderMenu(buff2);
        if(m2==NULL) {j++;continue;}
        if(m2[0]==NULL) { j++;kgFreeDouble((void **)m2);continue;}
        k=0;
        while(m2[k]!= NULL){
          res= TryString(buff2,m2[k],"scalable",pgr);
          if(res==NULL) {
            res= TryString(buff2,m2[k],"256",pgr);
          }
          if(res==NULL) {
            res= TryString(buff2,m2[k],"192",pgr);
          }
          if(res==NULL) {
            res= TryString(buff2,m2[k],"128",pgr);
          }
          if(res==NULL) {
            res= TryString(buff2,m2[k],"64",pgr);
          }
          if(res==NULL) {
            res= TryString(buff2,m2[k],NULL,pgr);
          }
          if(res != NULL) {  break;}
          k++;
        } // while m2[k]
        if(m2!= NULL) kgFreeDouble((void **)m2);
        if(res != NULL) {  break;}
        j++;
      } // while(m1[j]
      if(m1!= NULL) kgFreeDouble((void **)m1);
      i++;
      if(res != NULL) {  break;}
    } // while(m[i]
    if(m!= NULL) kgFreeDouble((void **)m);
  }
  Dempty(L);
  return res;
}
void *SearchIcon(void *Btmp) {
  BUTACTION *bt;
  char *pt,*res=NULL;
  bt = (BUTACTION *)Btmp;
  pt = bt->Icon;
  res = kgWhichIcon(pt,"oxygen");
  if(res==NULL) res = kgWhichIcon(pt,"Oxygen");
  if(res==NULL) res = kgWhichIcon(pt,"KDE");
  if(res==NULL) res = kgWhichIcon(pt,"gnome");
  if(res==NULL) res = kgWhichIcon(pt,"CratOS");
  if(res==NULL) res = kgWhichIcon(pt,"hicolor");
  if(res!= NULL) {
//                  printf("res: %s : %s\n",pt,res);
                   strcpy(bt->Icon,res);
                   free(res);
                 }
                 else {
                   bt->Icon[0]='\0';
                 }
  return Btmp;
}
void *MakeDesktopList(void) {
  int i,pos,SKIP,l;
  char **m,*pt,*res;
  char buff[500];
  FILE *fp;
  BUTACTION *bt,Btmp;
  void *Thid;
  Thid = OpenThreads(0);
  if(Dlist != NULL) {
   Dempty(Dlist);
   Dlist = NULL;
  }
  if(Dlist == NULL) {
    Dlist = Dopen();
    m = kgFileMenu("/usr/share/applications","*.desktop");
    if(m != NULL) {
      i=0;
      while(m[i]!= NULL) {
        strcpy(buff,"/usr/share/applications/");
        strcat(buff,m[i]);
        fp = fopen(buff,"r");
        if(fp == NULL) {
          printf("Failed: |%s|\n",m[i]);
        }
        i++;
        if(fp != NULL) {
          SKIP=1;
          Btmp.Icon[0]='\0';
          while (fgets(buff,499,fp) != NULL) {
            if(SearchString(buff,"Name[") >= 0) continue;
            if(SearchString(buff,"Generic") >= 0) continue;
            if(SearchString(buff,"TryExec") >= 0) continue;
            if(SearchString(buff,"Exec") >= 0) {
              SKIP=0;
              if((pos=SearchString(buff,"=")) >=0) {
                 pt = buff+pos+1;
                 while( *pt == ' ') pt++;
                 l = strlen(pt);
                 while((l>0)&&(pt[l]<' ')) {pt[l]='\0';l--;}
                 if((pt[0]!='/')) {
                    if((res=kgWhich(pt))==NULL) {SKIP=1;break;}
                    free(res);
                 }
                 else {
                   char **m,*pt1;
                   l = strlen(pt);
                   while(pt[l]!='/') l--;
                   if(l==0) {
                    m = kgFileMenu("/",pt+1);
                   }
                   else {
                    pt1=pt+l+1;
                    pt[l]='\0';
                    m = kgFileMenu(pt,pt1);
                    pt[l]='/';
                   }
                   if( (m==NULL)) {SKIP=1;break;}
                   if( (m[0]==NULL)) {kgFreeDouble((void **)m);SKIP=1;break;}
                   kgFreeDouble((void **)m);
                 }
//                 strcpy(Btmp.Command,pt);
                 sscanf(pt,"%s",Btmp.Command);
              }
            }
            if(SearchString(buff,"Name") >= 0) {
              if((pos=SearchString(buff,"=")) >=0) {
                 pt = buff+pos+1;
                 while( *pt == ' ') pt++;
                 l = strlen(pt);
                 while((l>0)&&(pt[l]<' ')) {pt[l]='\0';l--;}
                 strcpy(Btmp.Name,pt);
              }
            }
            if(SearchString(buff,"Icon") >= 0) {
              if((pos=SearchString(buff,"=")) >=0) {
                 char *res=NULL;
                 pt = buff+pos+1;
                 while( *pt == ' ') pt++;
                 l = strlen(pt);
                 while((l>0)&&(pt[l]<=' ')) {pt[l]='\0';l--;}
                 strcpy(Btmp.Icon,pt);
              }
            }
          } // fgets
          fclose(fp);
          if(Btmp.Icon[0]=='\0') SKIP=1;
          if(!SKIP) { // add item
            bt = (BUTACTION *) malloc(sizeof(BUTACTION));
            strcpy(bt->Command,Btmp.Command);
            strcpy(bt->Icon,Btmp.Icon);
            strcpy(bt->Name,Btmp.Name);
            Dadd(Dlist,bt);
//            printf("Searching : %s\n",bt->Icon);
            DoInAnyThread(Thid,SearchIcon,bt);
//            SearchIcon(bt);
          }
        }
      } //while
    }
  }  
  WaitThreads(Thid);
  CloseThreads(Thid);
  Resetlink(Dlist);
  while ( (bt=(BUTACTION *)Getrecord(Dlist))!= NULL) {
    if(bt->Icon[0] != '\0') continue;
    else {Dmove_back(Dlist,1); Ddelete(Dlist);}
  }
  return MakeButList(Dlist);
}
void  importbrowser2init(DIY *Y,void *pt) {
 // One may setup browser list here by setting Y->list
 // if it need to be freed set it as Y->pt also
  void *th=NULL;
  th = MakeButList(Blist);
  Y->list=(void *)th;
  Y->pt=(void *)th;
}
int  importbrowser2callback(int item,int i,void *Tmp) {
  DIALOG *D;DIY *Y;void *pt; 
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret=0; 
  int pos,x,y,k;
  ThumbNail **th,*tpt;
  BUTACTION *bt,*btmp;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  Y = (DIY *)kgGetWidget(Tmp,i);
  th = (ThumbNail **)kgGetList(Y);
  if(kgDragThumbNail(Y,item-1,&x,&y)) {
     pos = kgGetThumbNailItem(Y,x,y);
     if((pos >=0)&&(pos!=(item-1)) ) {
       tpt = th[item-1];
       if(pos < (item-1) ) {
          for(k=(item-1);k>pos;k--){ th[k]=th[k-1]; }
          th[pos]= tpt;
       }
      else {
          for(k=item;k<pos;k++) {th[k-1]=th[k];}
          th[pos-1]= tpt;
      }
      *(Y->df) = pos+1;
      Dposition(Blist,item);
      bt = Dpick(Blist);
      if(pos > (item-1)) {
        Dposition(Blist,pos);
      }
      else {
        Dposition(Blist,pos+1);
      }
      Dinsert(Blist,bt);
      WriteRecords();
      Restart=1;
      kgSetExit(Parent);
      kgSetList(Y,(void **)th);
      kgUpdateWidget(Y);
      kgUpdateOn(Tmp);
    }
     
  }
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
void  importbrowser1init(DIY *Y,void *pt) {
 // One may setup browser list here by setting Y->list
 // if it need to be freed set it as Y->pt also
 void *th,*id;
 id=kgOpenBusy(pt,30,30);
 th = MakeDesktopList();
 kgCloseBusy(id);
 Y->list = (void *)th;
 Y->pt = (void *)th;
}
int  importsplbutton1callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int pos=0;
  DIALOG *D;DIL *B; 
  BUTACTION *bt,*btmp;
  DIY *Y,*YB;
  ThumbNail **th;
  int n,ret=1; 
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  void * thumb;
  n = B->nx;
  Y = (DIY *)kgGetWidget(Tmp,0);
  YB = (DIY *)kgGetWidget(Tmp,1);
  th = (ThumbNail **)kgGetList(Y);
  switch(butno) {
    case 1: 
      pos =0; 
      while ( (thumb = th[pos])!= NULL) {
        kgSetSwitch(Y,pos,0);
//        th[pos]->sw =0;
        pos++;
      }
      ret = 0;
      kgUpdateWidget(Y);
      kgUpdateOn(Tmp);
      break;
    case 2: 
      pos =0; 
      while ( (thumb = th[pos])!= NULL) {
        if(kgGetSwitch(Y,pos)) {
         Dposition(Dlist,pos+1);
         bt = (BUTACTION *) Getrecord(Dlist);
         btmp = (BUTACTION *) malloc(sizeof(BUTACTION));
         strcpy(btmp->Command,bt->Command);
         strcpy(btmp->Name,bt->Name);
         strcpy(btmp->Icon,bt->Icon);
         Dappend(Blist,btmp);
        }
//        th[pos]->sw =0;
        pos++;
      }
      th = (ThumbNail **)kgGetList(YB);
      kgFreeThumbNails(th);
      th = MakeButList(Blist);
      kgSetList(YB,(void **)th);
      YB->pt=(void *)th;
      pos=0;
      while(th[pos]!=NULL) pos++;
      kgSetSelection(YB,pos);
      kgUpdateWidget(YB);
      kgUpdateOn(Tmp);
      WriteRecords();
      Restart=1;
      kgSetExit(Parent);
      ret = 0;
      break;
    case 3: 
      break;
  }
  return ret;
}
void  importsplbutton1init(DIL *B,void *pt) {
}
int  importsplbutton2callback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1,pos,off=1; 
  DIY *Y;
  ThumbNail **th;
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  Y = (DIY *)kgGetWidget(Tmp,1);
  th = (ThumbNail **)kgGetList(Y);
  switch(butno) {
    case 1: 
      pos =0; 
      while ( (th[pos])!= NULL) {
        if(kgGetSwitch(Y,pos)) {
            Dposition(Blist,pos+off);
            Ddelete(Blist);
            off--;
        }
        pos++;
      }
      kgFreeThumbNails(th);
      th = MakeButList(Blist);
      kgSetList(Y,(void **)th);
      Y->pt=(void *)th;
      kgUpdateWidget(Y);
      kgUpdateOn(Tmp);
      WriteRecords();
      Restart=1;
      kgSetExit(Parent);
      ret=0;
      break;
  }
  return ret;
}
void  importsplbutton2init(DIL *B,void *pt) {
}
int importinit(void *Tmp) {
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
int importcleanup(void *Tmp) {
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
int importCallBack(void *Tmp,void *tmp) {
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
int importResizeCallBack(void *Tmp) {
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
int importWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  return ret;
}
