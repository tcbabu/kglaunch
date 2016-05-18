#include "kulina.h"
#include "headers.h"
#include "timages.c"
ThumbNail **th=NULL;
extern DIALOG *Parent;
extern int Restart;
extern Dlink *Blist;
extern int Item;
void WriteRecords(void);
void *Runedititem(void *);
void *Runimport(void *arg);
extern int Exit;
int  additembrowser1callback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIX *X;void *pt; 
  int ret=1; 
  BUTACTION *bt=NULL;
  D = (DIALOG *)Tmp;
  pt = D->pt;
  X = (DIX *)kgGetWidget(Tmp,i);
  switch(item) {
    case 1:
      system("configlauncher");
      Restart=1;
      kgSetExit(Parent);
      break;
    case 2: 
      Runimport(Tmp);
      break;
    case 3: 
      bt = (BUTACTION *) malloc(sizeof(BUTACTION));
      bt->Name[0]='\0';
      bt->Icon[0]='\0';
      bt->Command[0]='\0';
      if( Runedititem(bt)!= NULL){
        if(Item > 0) {
          Dposition(Blist,Item);
          Dinsert(Blist,bt);
        }
        else   Dappend(Blist,bt);
        WriteRecords();
        Restart=1;
        kgSetExit(Parent);
      }
      else free(bt);
      break;
    case 4:
      if(Item > 0) {
        Dposition(Blist,Item);
        Ddelete(Blist);
        WriteRecords();
        Restart=1;
        kgSetExit(Parent);
      }
      break;
    case 5:
      if(Item > 0) {
        Dposition(Blist,Item);
        bt = (BUTACTION *)Getrecord(Blist);
        if( Runedititem(bt)!= NULL){
          WriteRecords();
          Restart=1;
          kgSetExit(Parent);
        }
      }
      break;
    case 6:
      if(Item > 0) {
        Dposition(Blist,Item);
        bt = (BUTACTION *)Dpick(Blist);
        Resetlink(Blist);
        Dinsert(Blist,bt);
        WriteRecords();
        Restart=1;
        kgSetExit(Parent);
      }
      break;
    case 7:
      if(Item > 0) {
        Dposition(Blist,Item);
        bt = (BUTACTION *)Dpick(Blist);
        Dappend(Blist,bt);
        WriteRecords();
        Restart=1;
        kgSetExit(Parent);
      }
      break;
    default:
      Exit=1;
      break;
  }
  return ret;
}
void  additembrowser1init(DIX *X,void *pt) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
 char *menu[]={"Config Launcher","Import item","Add new item",
               "Delete item", "Edit item","Move to first",
               "Move to end","Close Launcher",NULL};
 X->list = (void *)kgStringToThumbNails(menu);
 th = (ThumbNail **)X->list;
 th[0]->img=(void *)&config_str;
 th[1]->img=(void *)&add_str;
 th[2]->img=(void *)&add_str;
 th[3]->img=(void *)&remove_str;
 th[4]->img=(void *)&edit_str;
 th[5]->img=(void *)&top_str;
 th[6]->img=(void *)&bottom_str;
 th[7]->img=(void *)&exit_str;
}
int additeminit(void *Tmp) {
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
int additemcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;void *pt;
  D = (DIALOG *)Tmp;
  DIX *X;
  pt = D->pt;
  X = (DIX *)kgGetWidget(D,0);
  kgFreeThumbNails((ThumbNail **)X->list);
  X->list=NULL;
  return ret;
}
int additemCallBack(void *Tmp,void *tmp) {
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
      ret=1;
  }
  return ret;
}
int additemResizeCallBack(void *Tmp) {
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
int additemWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0,vl;
  KBEVENT kbe;
  if((vl=kgCheckRootEvent(Tmp,&kbe))!= 3) return 0;
//  printf("Got root event %d\n",vl);
  if(kbe.event ==1) {
//      printf("Got root event\n");
      ret=1;
  }
  return ret;
}
