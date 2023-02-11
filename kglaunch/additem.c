#include <kulina.h>
#include "additemCallbacks.h"
DIALOG *Parent;

int Exit=0;
int xo,yo,xl,yl;
void ModifyadditemGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
*/
   gc->GuiFontSize =8;
//   gc->MenuFont=20;
}
int additemGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIX x0 = { 
    'x',
    1,2,  
    145,210,   
//    145,186,   
    2,2,  
    95, 
    23, 
    1,1, 
    1,7, 
    (int *)v[0], 
    NULL, 
    NULL, 
    NULL,additembrowser1callback, /* *args, callback */
    4,  /* Border Offset  */
     2,  /* Scroll width  */
     2,  /* Type  */
     1, /* item highlight */
    0, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  strcpy(x0.Wid,(char *)"additemWidget1");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+2));
  d =dtmp+i; 
  d[1].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIX));
  additembrowser1init(&x0,pt) ;
  *d[0].x = x0;
  d[0].x->item = -1;
  d[1].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeadditemGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Selectmenu1  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   void** v=(void **)malloc(sizeof(void*)*2);
   v[1]=NULL;
   v[0]=(void *)(v0);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = additemGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int additem( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = additemGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 0;
  D.df = 0;
  D.tw = 1;
  D.bw = 1;
  D.lw = 1;
  D.rw = 1;
  D.xo = xo;
  D.yo = yo;
  D.xl = 154;    /*  Length of Dialog */
  D.yl = 188;    /*  Width  of Dialog */
  D.yl = 212;    /*  Width  of Dialog */
  D.Initfun = additeminit;    /*   init fuction for Dialog */
  D.Cleanupfun = additemcleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 0;    /*  1 for Window Decorration */
  D.transparency = 0.400000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 0;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = additemCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = additemResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = additemWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 1;    /*  1 for not showing in task bar*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres,l,h,bw,xo,yo; 
     kgDisplaySize(&xres,&yres); 
     if(parent == NULL){
      free(kgGetGeometry(Parent,&xo,&yo,&l,&h,&bw));
      D.xl +=5;
      D.DrawBkgr = 1;    /*  1 for drawing background */
      D.Sticky = 1;    /*  1 for stickyness */
      D.xo += xo;
      D.yo += yo;
      if(D.xo+D.xl >xres) D.xo=xres-D.xl;
      if(D.yo+D.yl >yres) D.yo=yres-D.yl;
     }
     else {
      if(D.xo+D.xl >xl) D.xo=xl-D.xl;
      if(D.yo+D.yl >yl) D.yo=yl-D.yl;
     }
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
//  kgColorTheme(&D,210,210,210);    /*  set colors for gui*/
  ModifyadditemGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
int Runadditem(void *arg,int x1,int y1,int l,int h) {
/*************************************************

    Selectmenu1  1 data value

*************************************************/
   int ret;	
   int   v0 = 1;
   void* v[1];
   int Pxl,Pyl;
   Parent = (DIALOG *)arg;
   xo = x1;
   yo=y1;
   xl = l;
   yl = h;
   v[0]=(void *)(&v0);
   void *pt=NULL; /* pointer to send any extra information */
   Pxl = Parent->xl;
   Pyl = Parent->yl;
   if( (Pxl < 150)||(Pyl<220)) ret = additem(NULL,v,pt);
   else ret = additem(arg,v,pt );
   return Exit;
}
