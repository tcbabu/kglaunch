#include "kulina.h"
#include "configlauncherCallbacks.h"
int Bred=190,Bgreen=200,Bblue=190;
int Btred=190,Btgreen=200,Btblue=190;
float Transparency=1.0;
int Align=5,IconShape=0;
int Color,Font=8,Red=230,Green=240,Blue=230,Nx=5,Ny=3,Xgap=40,Ygap=50,Bsize=72;
int Bcolor;
int Btcolor;
char ConfigFile[100];
void ModifyconfiglauncherGc(Gclr *gc) {
/*
//  You may change default settings here 
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   gc->FontSize =8;
   gc->Font=23;
*/
}
int ReadConfig(void) {
  FILE *fp;
  char buff[500];
  strcpy(ConfigFile,getenv("HOME"));
  strcat(ConfigFile,"/.kulina");
  mkdir(ConfigFile,0700);
  strcat(ConfigFile,"/launcher.conf");
  if((fp=fopen(ConfigFile,"r"))==NULL) return 0;
  if( fgets(buff,499,fp)!= NULL) {
   if(sscanf(buff,"%d%d%d",&Red,&Green,&Blue)== 0) return 0;
  }
  if( fgets(buff,499,fp)!= NULL) {
    if(sscanf(buff,"%d",&Font)== 0) return 0;
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
int WriteConfig(void) {
  FILE *fp;
  if((fp=fopen(ConfigFile,"w"))==NULL) return 0;
  if(fprintf(fp,"%d %d %d\n",Red,Green,Blue)== 0) return 0;
  if(fprintf(fp,"%d\n",Font)== 0) return 0;
  if(fprintf(fp,"%d %d %d %d %d\n",Nx,Ny,Xgap,Ygap,Bsize)== 0) return 0;
  if(fprintf(fp,"%d %d %d\n",Bred,Bgreen,Bblue)== 0) return 0;
  if(fprintf(fp,"%f %d %d\n",Transparency,Align,IconShape)== 0) return 0;
  if(fprintf(fp,"%d %d %d\n",Btred,Btgreen,Btblue)== 0) return 0;
  fclose(fp);
  return 1;
}
int configlauncherGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIM m0 = { 
    'm',
    160,79,  
    235,99,  
    1,0  
  };
  strncpy(m0.msg,(char *)"Text Color",499);
  strcpy(m0.Wid,(char *)"configlauncherWidget1");
  BUT_STR  *butn1=NULL; 
  butn1= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn1[0].sw=1;
  strcpy(butn1[0].title,(char *)"");
  butn1[0].xpmn=NULL;
  butn1[0].xpmp=NULL;
  butn1[0].xpmh=NULL;
  butn1[0].bkgr=-Color;
  butn1[0].butncode='';
  DIN b1 = { 
    'n',
    161,99,  
    235,173,
    2,2,  
    64, 
    64, 
    1,1, 
    2,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn1, 
    configlauncherbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b1.Wid,(char *)"configlauncherWidget2");
  char **menu2 ; 
  menu2= kgFontNames();
  char *prompt2 ; 
  prompt2=(char *)malloc(12);
  strcpy(prompt2,(char *)"Select Font");
  DIW w2 = { 
    'w',
    9,18,  
    266,47,   
    4,  
    (int *)v[0],
    prompt2 ,
    menu2 ,
    NULL,configlauncherbrowser1callback, /* *args, callback */
    0 
  };
  strcpy(w2.Wid,(char *)"configlauncherWidget3");
  T_ELMT *e3  ; 
  e3 =(T_ELMT *)malloc(sizeof(T_ELMT)*5);
  e3[0].fmt = (char *)malloc(11);
  strcpy(e3[0].fmt,(char *)"Columns%3d");
  e3[0].v=(void *)v[1];
  e3[0].sw=1;
  e3[1].fmt = (char *)malloc(8);
  strcpy(e3[1].fmt,(char *)"Rows%3d");
  e3[1].v=(void *)v[2];
  e3[1].sw=1;
  e3[2].fmt = (char *)malloc(14);
  strcpy(e3[2].fmt,(char *)"Column Gap%3d");
  e3[2].v=(void *)v[3];
  e3[2].sw=1;
  e3[3].fmt = (char *)malloc(11);
  strcpy(e3[3].fmt,(char *)"Row Gap%3d");
  e3[3].v=(void *)v[4];
  e3[3].sw=1;
  e3[4].fmt = (char *)malloc(13);
  strcpy(e3[4].fmt,(char *)"Icon Size%3d");
  e3[4].v=(void *)v[5];
  e3[4].sw=1;
  DIT t3 = { 
    't',
    276,17,  
    446,171,
    20, 
    1,5, 
    e3,
    1,1,
    NULL,configlaunchertextbox1callback,1,0,18,9 /* args,Call back */
  };
  strcpy(t3.Wid,(char *)"configlauncherWidget5");
  t3.pt=NULL;
  BUT_STR  *butn4=NULL; 
  butn4= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn4[0].sw=1;
  strcpy(butn4[0].title,(char *)"Cancel");
  butn4[0].xpmn=NULL;
  butn4[0].xpmp=NULL;
  butn4[0].xpmh=NULL;
  butn4[0].bkgr=-1;
  butn4[0].butncode='';
  butn4[1].sw=1;
  strcpy(butn4[1].title,(char *)"Okay");
  butn4[1].xpmn=NULL;
  butn4[1].xpmp=NULL;
  butn4[1].xpmh=NULL;
  butn4[1].bkgr=-1;
  butn4[1].butncode='';
  DIL h4 = { 
    'h',
    184,334,  
    340,367,
    2,0,  
    72, 
    25, 
    2,1, 
    5,0.500000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn4, 
    configlaunchersplbutton1callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(h4.Wid,(char *)"configlauncherWidget6");
  BUT_STR  *butn5=NULL; 
  butn5= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn5[0].sw=1;
  strcpy(butn5[0].title,(char *)"");
  butn5[0].xpmn=NULL;
  butn5[0].xpmp=NULL;
  butn5[0].xpmh=NULL;
  butn5[0].bkgr=-Bcolor;
  butn5[0].butncode='';
  DIN b5 = { 
    'n',
    86,99,
    160,173,
    2,2,  
    64, 
    64, 
    1,1, 
    2,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn5, 
    configlauncherbutton2callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b5.Wid,(char *)"configlauncherWidget6");
  DIM m6 = { 
    'm',
    89,79,  
    154,99,  
    1,0  
  };
  strncpy(m6.msg,(char *)"Base Color",499);
  strcpy(m6.Wid,(char *)"configlauncherWidget7");
  char *menu7[]  = { 
    (char *)"Bottom Left",
    (char *)"Bottom Centre",
    (char *)"Bottom Right",
    (char *)"Middle Left",
    (char *)"Middle Centre",
    (char *)"Middle Right",
    (char *)"Top Left",
    (char *)"Top Centre",
    (char *)"Top Right",
    NULL 
  };
  ThumbNail **th0 ;
  DIRA r7 = { 
    'r',
    41,206,  
    189,326,   
    8,0,  
    90, 
    25, 
    1,4, 
    1,4, 
    (int *)v[6], 
    NULL, 
    NULL ,
    NULL,configlauncherbrowser2callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th0 = (ThumbNail **)kgStringToThumbNails((char **)menu7);
  r7.list=(void **)th0;
  strcpy(r7.Wid,(char *)"configlauncherWidget8");
  DIM m8 = { 
    'm',
    22,185,  
    101,209,  
    1,0  
  };
  strncpy(m8.msg,(char *)"Alignment:",499);
  strcpy(m8.Wid,(char *)"configlauncherWidget10");
  DIF f9 = { 
    'f',
    335,189,  
    445,235,   
    0.000000,1.000000,  
    60,  
    (double *)v[7],
    NULL,
    NULL,configlauncherfslide1callback /* *args, callback */
  };
  strcpy(f9.Wid,(char *)"configlauncherWidget11");
  DIM m10 = { 
    'm',
    259,209,  
    335,232,  
    1,0  
  };
  strncpy(m10.msg,(char *)"Transparency",499);
  strcpy(m10.Wid,(char *)"configlauncherWidget13");
  char *menu11[]  = { 
    (char *)"None",
    (char *)"Rounded Square",
    (char *)"Round",
    (char *)"Square",
    NULL 
  };
  ThumbNail **th1 ;
  DIRA r11 = { 
    'r',
    214,260,  
    445,324,   
    8,0,  
    90, 
    25, 
    1,4, 
    1,2, 
    (int *)v[8], 
    NULL, 
    NULL ,
    NULL,configlauncherbrowser3callback, /* *args, callback */
    6,  /* Border Offset  */
     22,  /* Scroll width  */
     0,  /* Type  */
     0, /* item highlight */
    1, /* bordr */
    0, /* bkgr */
    0  /* =1 hide  */
   };
  th1 = (ThumbNail **)kgStringToThumbNails((char **)menu11);
  r11.list=(void **)th1;
  strcpy(r11.Wid,(char *)"configlauncherWidget14");
  DIM m12 = { 
    'm',
    195,243,  
    295,267,  
    1,0  
  };
  strncpy(m12.msg,(char *)"Icon Shaping:",499);
  strcpy(m12.Wid,(char *)"configlauncherWidget15");
  BUT_STR  *butn13=NULL; 
  butn13= (BUT_STR *)malloc(sizeof(BUT_STR)*1);
  butn13[0].sw=1;
  strcpy(butn13[0].title,(char *)"");
  butn13[0].xpmn=NULL;
  butn13[0].xpmp=NULL;
  butn13[0].xpmh=NULL;
  butn13[0].bkgr=-Btcolor;
  butn13[0].butncode='';
  DIN b13 = { 
    'n',
    11,99,  
    85,173,
    2,2,  
    64, 
    64, 
    1,1, 
    2,0.150000,0,0,0,1, /* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/
 
    butn13, 
    configlauncherbutton3callback, /*  Callbak */
      NULL  /* any args */
  };
  strcpy(b13.Wid,(char *)"configlauncherWidget14");
  DIM m14 = { 
    'm',
    12,79,  
    86,99,  
    1,0  
  };
  strncpy(m14.msg,(char *)"Icon Color",499);
  strcpy(m14.Wid,(char *)"configlauncherWidget15");
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+16));
  d =dtmp+i; 
  d[15].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIM));
  *d[0].m = m0;
  d[0].m->item = -1;
  d[1].t = (DIT *)malloc(sizeof(DIN));
  configlauncherbutton1init(&b1,pt) ;
  *d[1].N = b1;
  d[1].N->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIW));
  *d[2].w = w2;
  d[2].w->item = -1;
  d[3].t = (DIT *)malloc(sizeof(DIT));
  *d[3].t = t3;
  d[3].t->item = -1;
  d[4].t = (DIT *)malloc(sizeof(DIL));
  configlaunchersplbutton1init(&h4,pt) ;
  *d[4].h = h4;
  d[4].h->item = -1;
  d[5].t = (DIT *)malloc(sizeof(DIN));
  configlauncherbutton2init(&b5,pt) ;
  *d[5].N = b5;
  d[5].N->item = -1;
  d[6].t = (DIT *)malloc(sizeof(DIM));
  *d[6].m = m6;
  d[6].m->item = -1;
  d[7].t = (DIT *)malloc(sizeof(DIRA));
  configlauncherbrowser2init(&r7,pt) ;
  *d[7].r = r7;
  d[7].r->item = -1;
  d[8].t = (DIT *)malloc(sizeof(DIM));
  *d[8].m = m8;
  d[8].m->item = -1;
  d[9].t = (DIT *)malloc(sizeof(DIF));
  *d[9].f = f9;
  d[9].f->item = -1;
  d[10].t = (DIT *)malloc(sizeof(DIM));
  *d[10].m = m10;
  d[10].m->item = -1;
  d[11].t = (DIT *)malloc(sizeof(DIRA));
  configlauncherbrowser3init(&r11,pt) ;
  *d[11].r = r11;
  d[11].r->item = -1;
  d[12].t = (DIT *)malloc(sizeof(DIM));
  *d[12].m = m12;
  d[12].m->item = -1;
  d[13].t = (DIT *)malloc(sizeof(DIN));
  configlauncherbutton3init(&b13,pt) ;
  *d[13].N = b13;
  d[13].N->item = -1;
  d[14].t = (DIT *)malloc(sizeof(DIM));
  *d[14].m = m14;
  d[14].m->item = -1;
  d[15].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeconfiglauncherGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************

    Browser1  1 data value
    Text_Box1  5 data values
    RadioButtons2  1 data value
    Floatslidebar1  1 data value
    RadioButtons3  1 data value

*************************************************/
   int  *v0 ;
   v0 = (int *)malloc(sizeof(int));
   *v0 = 1;
   int  *v1 ;
   v1 = (int *)malloc(sizeof(int));
   *v1 = 1;
   int  *v2 ;
   v2 = (int *)malloc(sizeof(int));
   *v2 = 1;
   int  *v3 ;
   v3 = (int *)malloc(sizeof(int));
   *v3 = 1;
   int  *v4 ;
   v4 = (int *)malloc(sizeof(int));
   *v4 = 1;
   int  *v5 ;
   v5 = (int *)malloc(sizeof(int));
   *v5 = 1;
   int  *v6 ;
   v6 = (int *)malloc(sizeof(int));
   *v6 = 1;
   double *v7 ;
   v7 = (double *)malloc(sizeof(double));
   *v7 = 0.0;
   int  *v8 ;
   v8 = (int *)malloc(sizeof(int));
   *v8 = 1;
   void** v=(void **)malloc(sizeof(void*)*10);
   v[9]=NULL;
   v[0]=(void *)(v0);
   v[1]=(void *)(v1);
   v[2]=(void *)(v2);
   v[3]=(void *)(v3);
   v[4]=(void *)(v4);
   v[5]=(void *)(v5);
   v[6]=(void *)(v6);
   v[7]=(void *)(v7);
   v[8]=(void *)(v8);
   void *pt=NULL; /* pointer to send any extra information */
   GrpId = configlauncherGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v;
   return GrpId;
}

int configlauncher( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=1401010200;
  kgInitUi(&D);
  D.d=NULL;
  GrpId = configlauncherGroup(&D,v,pt);
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 11;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 417;   /* Position of Dialog */ 
  D.yo = 67;
  D.xl = 458;    /*  Length of Dialog */
  D.yl = 373;    /*  Width  of Dialog */
  D.Initfun = configlauncherinit;    /*   init fuction for Dialog */
  D.Cleanupfun = configlaunchercleanup;    /*   init fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.200000;    /*  float 1.0 for full transparency */
  D.Newwin = 0;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = configlauncherCallBack;    /*  default callback */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = configlauncherResizeCallBack;  /*  Resize callback */
#if 1 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = configlauncherWaitCallBack;  /*  Wait callback */
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
  kgColorTheme(&D,Bred,Bgreen,Bblue);    /*  set colors for gui*/
//  ModifyconfiglauncherGc(&(D.gc));    /*  set colors for gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *Runconfiglauncher(void *arg) {
/*************************************************

    Browser1  1 data value
    Text_Box1  5 data values
    RadioButtons2  1 data value
    Floatslidebar1  1 data value
    RadioButtons3  1 data value

*************************************************/
   int   v0 = 1;
   int   v1 = 1;
   int   v2 = 1;
   int   v3 = 1;
   int   v4 = 1;
   int   v5 = 1;
   int   v6 = 5;
   double v7 = 0.0;
   int   v8 = 1;
   void* v[9];
   int ret;
   ReadConfig();
   Font =Font+1;
   v7 = Transparency;
   v[0]=(void *)(&Font);
   v[1]=(void *)(&Nx);
   v[2]=(void *)(&Ny);
   v[3]=(void *)(&Xgap);
   v[4]=(void *)(&Ygap);
   v[5]=(void *)(&Bsize);
   v[6]=(void *)(&v6);
   v[7]=(void *)(&v7);
   v[8]=(void *)(&v8);
   v6 = Align;
   v8 = IconShape+1;
   Color = Red*1000000+Green*1000+Blue;
   Bcolor = Bred*1000000+Bgreen*1000+Bblue;
   Btcolor = Btred*1000000+Btgreen*1000+Btblue;
   
   void *pt=NULL; /* pointer to send any extra information */
   ret = configlauncher(NULL,v,pt );
   Font -=1;
//   printf("ret= %d %s\n",ret,ConfigFile);
   if(ret > 1) {
     Transparency = v7;
     Align = v6;
     IconShape = v8-1;
     WriteConfig();
   }
   return NULL;
}
void *Runconfiglauncher(void *);
int main(void) { Runconfiglauncher(NULL);return 1;}
