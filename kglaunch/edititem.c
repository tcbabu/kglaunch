#include <kulina.h>
#include "headers.h"
#include "edititemCallbacks.h"
extern char Icon[500],Command[500],Name[500];
void ModifyedititemGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int edititemGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  T_ELMT *e0  ; 
  e0 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e0[0].fmt = (char *)malloc(17);
  strcpy(e0[0].fmt,(char *)"Display Name%40s");
  e0[0].v=(void *)v[0];
  e0[0].sw=1;
  DIT t0 = { 
    't',
    19,19,  
    540,53,
    20, 
    1,1, 
    e0,
    1,1,
    NULL,edititemtextbox1callback,0,0,18,9 /* args,Call back */
  };
  t0.type=1;
  strcpy(t0.Wid,(char *)"edititemWidget2");
  t0.pt=NULL;
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"Browse");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-1;
  butn1[0].butncode='';
  DIN b1 = { 
    'n',
    541,64,  
    615,98,
    2,2,  
    64, 
    24, 
    1,1, 
    4,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    edititembutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b1.Wid,(char *)"edititemWidget3");
  T_ELMT *e2  ; 
  e2 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e2[0].fmt = (char *)malloc(9);
  strcpy(e2[0].fmt,(char *)"Icon%40s");
  e2[0].v=(void *)v[1];
  e2[0].sw=1;
  DIT t2 = { 
    't',
    91,64,  
    540,98,
    20, 
    1,1, 
    e2,
    1,1,
    NULL,edititemtextbox2callback,0,0,18,9 /* args,Call back */
  };
  t2.type=1;
  strcpy(t2.Wid,(char *)"edititemWidget5");
  t2.pt=NULL;
  T_ELMT *e3  ; 
  e3 =(T_ELMT *)malloc(sizeof(T_ELMT)*1);
  e3[0].fmt = (char *)malloc(12);
  strcpy(e3[0].fmt,(char *)"Command%40s");
  e3[0].v=(void *)v[2];
  e3[0].sw=1;
  DIT t3 = { 
    't',
    64,114,  
    540,148,
    20, 
    1,1, 
    e3,
    1,1,
    NULL,edititemtextbox3callback,0,0,18,9 /* args,Call back */
  };
  t3.type=1;
  strcpy(t3.Wid,(char *)"edititemWidget8");
  t3.pt=NULL;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Browse");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-1;
  butn4[0].butncode='';
  DIN b4 = { 
    'n',
    541,114,  
    615,148,
    2,2,  
    64, 
    24, 
    1,1, 
    4,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    edititembutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b4.Wid,(char *)"edititemWidget9");
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"Cancel");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-147000000;
  butn5[0].butncode='';
  butn5[1].sw=1;
  strcpy(butn5[1].title,(char *)"Okay");
  butn5[1].xpmn=NULL;
  butn5[1].xpmp=NULL;
  butn5[1].xpmh=NULL;
  butn5[1].bkgr=-177000;
  butn5[1].butncode='';
  DIL h5 = { 
    'h',
    249,159,  
    405,192,
    2,0,  
    72, 
    25, 
    2,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn5, 
    edititemsplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h5.Wid,(char *)"edititemWidget10");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+7));
  d =dtmp+i; 
  d[6].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIT));
  *d[0].t = t0;
  d[0].t->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIN));
  edititembutton1init(&b1,pt) ;
  *d[1].N = b1;
  d[1].N->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIT));
  *d[2].t = t2;
  d[2].t->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIT));
  *d[3].t = t3;
  d[3].t->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIN));
  edititembutton2init(&b4,pt) ;
  *d[4].N = b4;
  d[4].N->item = -1;
  d[5].t = (DIT *)malloc(sizeof(DIL));
  edititemsplbutton1init(&h5,pt) ;
  *d[5].h = h5;
  d[5].h->item = -1;
  d[6].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeedititemGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values
    Text_Box2  1 data values
    Text_Box3  1 data values

*************************************************/
   char  *v0 ;
   v0 = (char *)malloc(sizeof(100));
   v0[0] = '\0';
   char  *v1 ;
   v1 = (char *)malloc(sizeof(100));
   v1[0] = '\0';
   char  *v2 ;
   v2 = (char *)malloc(sizeof(100));
   v2[0] = '\0';
   void** v=(void **)malloc(sizeof(void*)*4);
   v[3]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = edititemGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int edititem( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = edititemGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 5;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 399;   /* Position of Dialog */ 
  D.yo = 121;
  D.xl = 629;    /*  Length of Dialog */
  D.yl = 205;    /*  Width  of Dialog */
  D.Initfun = edititeminit;    /*   init fuction for Dialog */
  D.Cleanupfun = edititemcleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.100000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = edititemCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = edititemResizeCallBack;  /*  Resize callback */
#if 1 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = edititemWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
//  ModifyedititemGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runedititem(void *arg) {
/*************************************************

    Text_Box1  1 data values
    Text_Box2  1 data values
    Text_Box3  1 data values

*************************************************/
   BUTACTION *bt;
   int ret;
   char  v0[500]=" " ;
   char  v1[500]=" " ;
   char  v2[500]=" " ;
   void* v[3];
   bt = (BUTACTION *)arg;
   strncpy(v0,bt->Name,490);
   strncpy(v1,bt->Icon,490);
   strncpy(v2,bt->Command,490);
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   void *pt=NULL; /* pointer to send any extra information */
   ret = edititem(NULL,v,pt );
   if(ret==2) {
     strncpy(bt->Name,Name,490);
     strncpy(bt->Icon,Icon,490);
     strncpy(bt->Command,Command,490);
     return bt;
   }
   else return NULL;
}
