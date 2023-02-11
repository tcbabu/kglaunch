#include <kulina.h>
#include "importCallbacks.h"
void ModifyimportGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int importGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIY y0 = { 
    'y',
    212,43,  
    962,518,   
    60,30,  
    64, 
    64, 
    1,1, 
    0,3, 
    (int *)v[0], 
    NULL, 
    NULL, 
    NULL,importbrowser1callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(y0.Wid,(char *)"importWidget2");
  y0.item = -1;
  DIY y1 = { 
    'y',
    7,43,  
    211,518,   
    50,30,  
    64, 
    64, 
    1,1, 
    0,4, 
    (int *)v[1], 
    NULL, 
    NULL, 
    NULL,importbrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     1, /* item highlight */
    1, /* bordr */
    1, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(y1.Wid,(char *)"importWidget3");
  y1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*3);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"Clear");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-1;
  butn2[0].butncode='';
  butn2[1].sw=1;
  strcpy(butn2[1].title,(char *)"Import");
  butn2[1].xpmn=NULL;
  butn2[1].xpmp=NULL;
  butn2[1].xpmh=NULL;
  butn2[1].bkgr=-1;
  butn2[1].butncode='';
  butn2[2].sw=1;
  strcpy(butn2[2].title,(char *)"Finish");
  butn2[2].xpmn=NULL;
  butn2[2].xpmp=NULL;
  butn2[2].xpmh=NULL;
  butn2[2].bkgr=-1;
  butn2[2].butncode='';
  DIL h2 = { 
    'h',
    591,8,  
    821,41,
    2,0,  
    72, 
    25, 
    3,1, 
    4,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn2, 
    importsplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h2.Wid,(char *)"importWidget4");
  h2.item = -1;
  BUT_STR  *butn3=NULL; 
  butn3= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn3[0].sw=1;
  strcpy(butn3[0].title,(char *)"Delete");
  butn3[0].xpmn=NULL;
  butn3[0].xpmp=NULL;
  butn3[0].xpmh=NULL;
  butn3[0].bkgr=-1;
  butn3[0].butncode='';
  DIL h3 = { 
    'h',
    11,8,  
    93,41,
    2,0,  
    72, 
    25, 
    1,1, 
    2,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn3, 
    importsplbutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h3.Wid,(char *)"importWidget5");
  h3.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+5));
  d =dtmp+i; 
  d[4].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIY));
  importbrowser1init(&y0,pt) ;
  *d[0].y = y0;
  d[0].y->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIY));
  importbrowser2init(&y1,pt) ;
  *d[1].y = y1;
  d[1].y->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIL));
  importsplbutton1init(&h2,pt) ;
  *d[2].h = h2;
  d[2].h->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIL));
  importsplbutton2init(&h3,pt) ;
  *d[3].h = h3;
  d[3].h->item = -1;
  d[4].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeimportGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    ThumbnailBrowser1  1 data value
    ThumbnailBrowser2  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   void** v=(void **)malloc(sizeof(void*)*3);
   v[2]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = importGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int import( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = importGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 3;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 10;   /* Position of Dialog */ 
  D.yo = 10;
  D.xl = 967;    /*  Length of Dialog */
  D.yl = 521;    /*  Width  of Dialog */
  D.Initfun = importinit;    /*   init fuction for Dialog */
  D.Cleanupfun = importcleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = importCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = importResizeCallBack;  /*  Resize callback */
#if 1 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = importWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
  strcpy(D.name,"Kulina Launcher: Import");    /*  Dialog name you may change */
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
//  ModifyimportGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runimport(void *arg) {
/*************************************************

    ThumbnailBrowser1  1 data value
    ThumbnailBrowser2  1 data value

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   void* v[2];
   v[0]=(void *)(&v0);
   v[1]=(void *)(&v1);
   void *pt=arg; /* pointer to send any extra information */
   import(NULL,v,pt );
   return NULL;
}
