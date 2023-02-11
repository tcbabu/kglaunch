#include <kulina.h>
#include "headers.h"
#include <sys/stat.h>
#include "kglaunchCallbacks.h"
#include "images.c"
int Restart=1;
Dlink *Blist=NULL;
char Home[500];
int Xm,Ym;
int Nx=8,Ny=2,Bsize=72,Xgap=40,Ygap=50,Nb,Xl,Yl;
int Bred=190,Bgreen=200,Bblue=190;
int Btred=190,Btgreen=200,Btblue=190;
int Red=240,Green=250,Blue=240;
int Bfont=8,Bcolor;
float Transparency=0.4;
int Align=2,IconShape=3;
int Xres,Yres,Nxmax,Nymax,Nbmax;
char ConfigFile[1000];
 
int ReadConfig(void) {
  FILE *fp;
  char buff[500];
  strcpy(ConfigFile,getenv("HOME"));
  strcat(ConfigFile,"/.kulina");
  mkdir(ConfigFile,0700);
  strcat(ConfigFile,"/launcher.conf");
  if((fp=fopen(ConfigFile,"r"))==NULL){
    sprintf(buff,"cp /usr/share/kglaunch/Launcher %-s/.kulina",getenv("HOME"));
    system(buff);
    sprintf(buff,"cp /usr/share/kglaunch/launcher.conf %-s/.kulina",getenv("HOME"));
    system(buff);
    if((fp=fopen(ConfigFile,"r"))==NULL) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
   if(sscanf(buff,"%d%d%d",&Red,&Green,&Blue)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%d",&Bfont)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%d%d%d%d%d",&Nx,&Ny,&Xgap,&Ygap,&Bsize)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%d%d%d",&Bred,&Bgreen,&Bblue)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%f%d%d",&Transparency,&Align,&IconShape)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%d%d%d",&Btred,&Btgreen,&Btblue)== 0) return 0;
  }
  fclose(fp);
  return 1;
}
void ModifykglaunchGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
   kgDefineColor(67,Red,Green,Blue);
   kgDefineColor(68,Bred,Bgreen,Bblue);
   gc->but_char = 67;
   gc->ButtonFont = Bfont;
}
void WriteRecords(void){
  BUTACTION *bt;
  FILE *fp;
  int i,j;
  fp = fopen(Home,"w");
  Resetlink(Blist);
  while((bt=(BUTACTION *)Getrecord(Blist))!= NULL) {
    i = strlen(bt->Name);
    while((i>=0)&&(bt->Name[i]<=' ')) bt->Name[i--]='\0';
    if(i< 0) bt->Name[i]='\0';
    i = strlen(bt->Icon);
    while((i>=0)&&(bt->Icon[i]<=' ')) bt->Icon[i--]='\0';
    if(i< 0) bt->Icon[i]='\0';
    i = strlen(bt->Command);
    while((i>=0)&&(bt->Command[i]<=' ')) bt->Command[i--]='\0';
    if(i< 0) bt->Command[i]='\0';
    fprintf(fp,"%s\n",bt->Name);
    fprintf(fp,"%s\n",bt->Icon);
    fprintf(fp,"%s\n",bt->Command);
  }
  fclose(fp);
}
BUTACTION *ReadRecord(FILE *fp) {
  BUTACTION *bt;
  int i;
  bt = (BUTACTION *)malloc(sizeof(BUTACTION));
  if(fgets(bt->Name,99,fp)!= NULL) {
    i = strlen(bt->Name);
    while((i>=0)&&(bt->Name[i]<=' ')) bt->Name[i--]='\0';
    if(i< 0) bt->Name[i]='\0';
    if(fgets(bt->Icon,499,fp) != NULL) {
      i = strlen(bt->Icon);
      while((i>=0)&&(bt->Icon[i]<=' ')) bt->Icon[i--]='\0';
      if(i< 0) bt->Icon[i]='\0';
      if(fgets(bt->Command,499,fp)!= NULL) {
         i = strlen(bt->Command);
         while((i>=0)&&(bt->Command[i]<=' ')) bt->Command[i--]='\0';
         if(i< 0) bt->Command[i]='\0';
         return bt;
      }
      else { free(bt); return NULL; }
    }
    else { free(bt); return NULL; }
  }
  else { free(bt); return NULL; }
}
void * MakeMask(int w,int h,float fac) {
   void *fid,*img;

   fid = kgInitImage(w,h,1);
   kgUserFrame(fid,0.,0.,(float)(w+2),(float)(h+2));
   kgRoundedRectangleFill(fid,w*0.5,h*0.5,w+3.0,h+3.,0,0,0.0);
   kgRoundedRectangleFill(fid,w*0.5,h*0.5,w+1.0,h+1.,0,15,fac);
   img = kgGetResizedImage(fid);
   kgCloseImage(fid);
   return img;
}
void *GetProcessedImage(void *timg) {
  GMIMG *img;
  void *rzimg,*fid,*tmp,*mask;
  int Color = 68,rsize;
  int nsize;
  float rf,gf,bf,h,s,v,Vb,l,w,rfac=0.2;
  switch(IconShape) {
    default:
     case 1:
       rfac = 0.2;
     break;
     case 2:
       rfac = 0.5;
     break;
     case 3:
       rfac = 0.0;
     break;
  }
  img = (GMIMG *)kgGetImageCopy(NULL,timg);
  l = (Bsize)*0.5;
  w = l;
  rsize = (Bsize/2)*2+1;
  if(IconShape==3){
     fid = kgInitImage(rsize+2,rsize+2,2);
     kgUserFrame(fid,-l,-w,l,w);
  }
  else {
    fid =kgInitImage(rsize-2,rsize-2,4);
    kgUserFrame(fid,-l-2,-w-2,l+2,w+2);
  }
  RGBtoHSV(Btred,Btgreen,Btblue,&h,&s,&v);
  Vb = 2.0*v;
  if(Vb >1.) Vb=1.;
  HSVtoRGB(&rf,&gf,&bf,h,s,Vb);
  kgChangeColor(fid,152,(int)rf,(int)gf,(int)bf);
  HSVtoRGB(&rf,&gf,&bf,h,s,0.8*v);
  kgChangeColor(fid,153,(int)rf,(int)gf,(int)bf);
  kgChangeColor(fid,151,(int)Btred,(int)Btgreen,(int)Btblue);
//  kgRoundedRectangleFill(fid,0.,0.,2*l-1.,2*l-1.,0,153,rfac);
  if(IconShape!=3) {
   kgRoundedRectangleFill(fid,0.,0.,2*l+1.,2*l+1.,0,152,rfac);
   kgRoundedRectangleFill(fid,0.,0.,2*l-4.,2*l-4.,0,151,rfac);
  }
  else {
   kgRoundedRectangleFill(fid,0.,0.,2*l+2.,2*l+2.,0,152,rfac);
   kgRoundedRectangleFill(fid,0.,0.,2*l-4.,2*l-4.,0,151,rfac);
  }
  
  rzimg = kgGetResizedImage(fid);
  kgCloseImage(fid);
#if 0
  if(rsize > 24) {
   rsize = rsize-8;
  }
#endif
  switch(IconShape) {
    default:
      nsize = rsize;
      break;
    case 2:
      nsize = rsize*0.65;
      break;
    case 1:
      nsize = rsize*0.8;
      break;
    case 3:
      nsize = rsize*0.85;
      break;
  }
  if(nsize > (rsize-8) ) nsize = rsize-8;
  if((img->image_width > (nsize))||(img->image_height >(nsize))) {
      tmp= kgChangeSizeImage(img,nsize,nsize);
      kgFreeImage(img);
      img = tmp;
  }
#if 0
  mask = MakeMask(nsize,nsize,rfac);
  tmp = kgMaskImage(img,mask);
  kgFreeImage(img);
  kgFreeImage(mask);
  img = tmp;
#endif
  rzimg = kgMergeImages(rzimg,img,0,2);
  kgFreeImage(img);
  return rzimg;
}
void *GetButtons(void) {
  void *img;
  char buff[500];
  BUTACTION *bt;
  FILE *fp;
  int i,j,Color,Bcount,dir=1;
  float rfac=-1.0;
  BUT_STR  *butn0=NULL; 
  Nxmax =(Xres-20)/(Bsize+Xgap);
  Nymax =(Yres-20)/(Bsize+Ygap);
  Nbmax = (Nxmax*Nymax);
  butn0= (BUT_STR *)malloc(sizeof(BUT_STR)*Nb);
  Color=-1;
  for(i=0;i<(Nb);i++) {
    butn0[i].sw=0;
    strcpy(butn0[i].title,(char *)"");
    butn0[i].xpmn=NULL;
    butn0[i].xpmp=NULL;
    butn0[i].xpmh=NULL;
    butn0[i].bkgr=Color;
    butn0[i].butncode='';
  }
  if(Blist == NULL) Dempty(Blist);
  Blist = Dopen();
  strcpy(Home,getenv("HOME"));
  strcat(Home,"/.kulina");
  mkdir(Home,0700);
  strcat(Home,"/Launcher");
  fp = fopen(Home,"r");
  if(fp==NULL) {
    sprintf(buff,"cp /usr/share/kglaunch/Launcher %-s/.kulina",getenv("HOME"));
    system(buff);
    sprintf(buff,"cp /usr/share/kglaunch/launcher.conf %-s/.kulina",getenv("HOME"));
    system(buff);
    fp = fopen(Home,"r");
  }
  if(fp==NULL) return butn0;
  while( (bt=ReadRecord(fp))!= NULL) Dadd(Blist,bt);
  Bcount=Dcount(Blist);
  if(Ny>Nx) dir=2;
  while(Bcount>Nb) {
    switch(dir) {
      case 1:
       if(Nx<Nxmax) Nx++;
       else {Nx = Nx/2+1;Ny++;}
      break;
      default:
       if(Ny<Nymax) Ny++;
       else {Ny=Ny/2+1;Nx++;}
      break;
    }
    Nb = Nx*Ny;
    free(butn0);
    butn0= (BUT_STR *)malloc(sizeof(BUT_STR)*Nb);
    for(i=0;i<(Nb);i++) {
      butn0[i].sw=0;
      strcpy(butn0[i].title,(char *)"");
      butn0[i].xpmn=NULL;
      butn0[i].xpmp=NULL;
      butn0[i].xpmh=NULL;
      butn0[i].bkgr=Color;
      butn0[i].butncode='';
    }
    if(Nb>= Nbmax) break;
  }
  i=0;
  Resetlink(Blist);
  while((bt=Getrecord(Blist))!= NULL) {
    if(i==Nb) break;
    butn0[i].sw=1;
    if(Ygap>10) strcpy(butn0[i].title,bt->Name);
#if 0
    butn0[i].xpmn= (char *)malloc(502); 
    if(bt->Icon[0]!='\0') {
      strcpy(butn0[i].xpmn,"##");
      strcat(butn0[i].xpmn,bt->Icon);
    }
    else butn0[i].xpmn =&default_str;
    if(IconShape != 0) {
       img=GetProcessedImage(butn0[i].xpmn);
       butn0[i].xpmn = (char *)img;
    }
#else
  switch(IconShape) {
     case 1:
       rfac = 0.2;
     break;
     case 2:
       rfac = 0.5;
     break;
     case 3:
       rfac = 0.0;
     break;
  }
  if(bt->Icon[0]!='\0') {
      strcpy(buff,"##");
      strcat(buff,bt->Icon);
      img=kgGetProcessedImage(buff,Bsize,rfac,Btred,Btgreen,Btblue);
  }
  else {
      img=kgGetProcessedImage(&default_str,Bsize,rfac,Btred,Btgreen,Btblue);
  }
  butn0[i].xpmn = (char *)img;
#endif
    i++;
  }
  fclose(fp);
  return butn0;
}
int kglaunchGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  BUT_STR  *butn0=NULL; 
  Nb = Nx*Ny;
  butn0= (BUT_STR *)GetButtons();
  DIN b0 = { 
    'n',
    1,1,  
    627,445,
    50,70,  
    72, 
    72, 
    5,3, 
    0,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
    butn0, 
    kglaunchbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  b0.lngth = Bsize;
  b0.width = Bsize;
  b0.nx = Nx;
  b0.ny = Ny;
  b0.xgap = Xgap;
  b0.ygap = Ygap;
  b0.x2=(Nx*(Bsize+b0.xgap))+b0.x1+8;
  b0.y2=(Ny*(Bsize+b0.ygap))+b0.y1+8;
  Xl = (b0.x2 -b0.x1)+2*b0.x1;
  Yl = (b0.y2 -b0.y1)+2*b0.y1;
  strcpy(b0.Wid,(char *)"kglaunchWidget1");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+2));
  d =dtmp+i; 
  d[1].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIN));
  kglaunchbutton1init(&b0,pt) ;
  *d[0].N = b0;
  d[0].N->item = -1;
  d[1].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakekglaunchGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = kglaunchGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int kglaunch( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = kglaunchGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 0;
  D.df = 0;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 390;   /* Position of Dialog */ 
  D.yo = 148;
  D.xl = Xl;    /*  Length of Dialog */
  D.yl = Yl;    /*  Width  of Dialog */
  D.Initfun = kglaunchinit;    /*   init fuction for Dialog */
  D.Cleanupfun = kglaunchcleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 0;    /*  1 for Window Decorration */
  D.transparency = Transparency;
//  D.transparency = 0.950000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 1;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = kglaunchCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = kglaunchResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = kglaunchWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 1;    /*  1 for not showing in task bar*/
  D.StackPos = -1;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 1.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     Xm= xres/2-100;
     Ym= yres/2-20;
     D.xo = (xres-D.xl)/2;
     D.yo = (yres-D.yl)/2;
     switch(Align) {
      case 5:
      default:
      break;
      case 4:
       D.xo=2;
      break;
      case 6:
       D.xo= xres-2-D.xl;
      break;
      case 1:
       D.xo=2;
       D.yo= yres -D.yl;
      break;
      case  3:
       D.xo= xres-2-D.xl;
       D.yo= yres -D.yl;
      break;
      case 7:
       D.xo=2;
       D.yo= 2;
      break;
      case  9:
       D.xo= xres-2-D.xl;
       D.yo= 2;
      break;
      case 2:
       D.yo= yres -D.yl;
      break;
      case 8:
       D.yo= 1;
      break;
     }

      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
     Xm= xres/2-100;
     Ym= yres/2-20;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
  kgColorTheme(&D,Bred,Bgreen,Bblue);
  ModifykglaunchGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runkglaunch(void *arg) {
/*************************************************


*************************************************/
   int pid;
   int ret;
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
   kgDisplaySize(&Xres,&Yres); 
    while(Restart) {
        ret = ReadConfig();
        ret = kglaunch(NULL,v,pt );
    }
   return NULL;
}
