#include <GL/glut.h>
#include <unistd.h>
#include <math.h>
#include "reuzenrad.h"
#include "InitJPG.h"

//VARIABELEN
//visualisatie:
  GLint winWidth = 500, winHeight = 500;
  GLdouble aspectratio; //= winWidth/winHeight
  GLdouble xlens=20, ylens=8, zlens=20;
  float cameraHoek = 40;
  float xmin = -25, xmax = 25;
  float ymin = -30, ymax = 20;
  float near = 1, far = 200;
  char projectie;
  int toonmesh = 0;
  int meerdere = 0;
  int mist = 0;
  int doorzichtig = 0;
  int assenkruis = 0;
  int controlepunten = 0;
  int textuur = 0;

//debugvariabelen:
  int smooth = 1;
  int tooninfo = 0;
  int toonlamp = 0;

//afmetingen:
  //as:
    float centraleAsStraal = 0.5;
    float centraleAsLengte = 10.0;
  //schijven:
    float schijfafstand = 8.0;
    float schijfStraal = 10.0;
    float schijfDikte = 1.0;
  //spaken:
    int aantalSpaken = 10;
    float spaakDikte = 0.25;  //lengte i.f.v. schijfStraal
  //steunbalken:
    float steunBalkDikte = 0.75;
    float steunBalkLengte = 18.0;
  //zitje
    int aantalZitjes = 6;
    float ophanghoogte = 6;
    float ophangdikte = 0.25;
    GLfloat bakpunten[6][4][3] = {
      {{0.0, 2.0, -2.0},{0.5, 2.0, -2.0},{1.0, 3.0, -2.0},{1.5, 3.0, -1.5}},
      {{0.0, 0.5, -1.5},{1.0, 0.5, -1.5},{1.5, 1.0, -1.5},{2.0, 3.0, -1.0}},
      {{0.0, 0.0, -0.5},{1.0, 0.0, -0.5},{1.5, 0.5, -0.5},{2.0, 3.0, -0.5}},
      {{0.0, 0.0,  0.5},{1.0, 0.0,  0.5},{1.5, 0.5,  0.5},{2.0, 3.0,  0.5}},
      {{0.0, 0.5,  1.5},{1.0, 0.5,  1.5},{1.5, 1.0,  1.5},{2.0, 3.0,  1.0}},
      {{0.0, 2.0,  2.0},{0.5, 2.0,  2.0},{1.0, 3.0,  2.0},{1.5, 3.0,  1.5}} };
    GLfloat dakpunten[4][4][3] = {
      {{0.0, 0.0, 2.0},{0.5, 0.0, 1.0},{1.0, 0.0, 0.0},{2.0, 0.0, 0.0}},
      {{0.0, 0.5, 1.0},{0.5, 0.5, 1.0},{1.0, 0.5, 0.0},{2.0, 0.5, 0.0}},
      {{0.0, 1.0, 0.0},{0.5, 1.0, 0.0},{0.8, 0.8, 0.0},{1.6, 0.8, 0.0}},
      {{0.0, 2.0, 0.0},{0.5, 2.0, 0.0},{0.8, 1.6, 0.0},{1.3, 1.3, 0.0}} };
    GLfloat dakknopen[8] = {0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0};

//animatie
  int draai = 0;
  int wiebel = 0;
  int tijd = 10; //ms
  float animhoek = 0;
  float wiebelhoek = 0;
  float wiebeldelta = 0.4;  //ifv draai delta

//verlichting:
  float spothoek = 60;
  float spotexponent = 20;

//transparantie:
  GLenum srcf = GL_SRC_COLOR;
  GLenum dstf = GL_DST_COLOR;

//mist:
  GLfloat mistkleur[] = {0.8, 0.0, 0.8, 0.3};

//lichtplaatsen:
  GLfloat aplaats[3] = {0, 0, 20};  //ambient
  GLfloat dplaats[3] = {20, 0, 0};  //diffuus
  GLfloat splaats[3] = {20, 20, -20};  //specular
  GLfloat spplaats[3] = {15, 15, 0}; //spot

//lichtkleuren:
  GLfloat ambient[] = {1, 1, 1, 0}; //wit
  GLfloat diffuus[] = {.10, .90, .90, 0}; //groen-blauw
  GLfloat specular[] = {.90, .10, .10, 0};  //rood
  GLfloat spot[] = {.95, .95, .05, 0};  //geel
  GLfloat zwart[] = {.0, .0, .0, 1};  //zwart

//materiaal:
  float shini = 10;

  GLfloat grijsA[] = {.22, .22, .22, 1};
  GLfloat grijsD[] = {.33, .33, .33, 1};
  GLfloat grijsS[] = {.11, .11, .11, 1};

  GLfloat witachtigA[] = {.66, .66, .66, 1};
  GLfloat witachtigD[] = {.77, .77, .77, 1};
  GLfloat witachtigS[] = {.55, .55, .55, 1};

  GLfloat chroomA[] = {.46, .58, .35, 1};
  GLfloat chroomD[] = {.23, .29, .17, 1};
  GLfloat chroomS[] = {.69, .87, .52, 1};

  GLfloat bronsA[] = {.21, .13, .10, 1};
  GLfloat bronsD[] = {.39, .27, .17, 1};
  GLfloat bronsS[] = {.71, .43, .18, 1};

  GLfloat geelA[] = {.65, .55, .15, 1};
  GLfloat geelD[] = {.75, .45, .15, 1};
  GLfloat geelS[] = {.85, .35, .15, 1};

  GLfloat lilaA[] = {.45, .15, .75, 1};
  GLfloat lilaD[] = {.55, .15, .65, 1};
  GLfloat lilaS[] = {.35, .15, .85, 1};

  GLfloat zitjeA[] = {0, 0, 0, 1};
  GLfloat zitjeD[] = {0, 0, 0, 1};
  GLfloat zitjeS[] = {0, 0, 0, 1};

  GLfloat stangenA[] = {0, 0, 0, 1};
  GLfloat stangenD[] = {0, 0, 0, 1};
  GLfloat stangenS[] = {0, 0, 0, 1};

  GLfloat dakA[] = {0, 0, 0, 1};
  GLfloat dakD[] = {0, 0, 0, 1};
  GLfloat dakS[] = {0, 0, 0, 1};

  GLfloat steunbalkA[] = {0.2, 0.1, 0.1, 1};
  GLfloat steunbalkD[] = {0.1, 0.2, 0.1, 1};
  GLfloat steunbalkS[] = {0.1, 0.1, 0.2, 1};

  GLfloat asA[] = {0.1, 0.4, 0.1, 1};
  GLfloat asD[] = {0.1, 0.4, 0.1, 1};
  GLfloat asS[] = {0.1, 0.4, 0.1, 1};

  GLfloat spaakA[] = {0.4, 0.1, 0.1, 1};
  GLfloat spaakD[] = {0.4, 0.1, 0.1, 1};
  GLfloat spaakS[] = {0.4, 0.1, 0.1, 1};

  GLfloat schijfA[] = {0.1, 0.1, 0.4, 1};
  GLfloat schijfD[] = {0.1, 0.1, 0.4, .4};
  GLfloat schijfS[] = {0.1, 0.1, 0.4, .4};

//textuur
  GLuint textuurobject[AANTALAFBEELDINGEN];
  char jpgnaam[AANTALAFBEELDINGEN][20] = {"kassei.jpg", "roof.jpg", "seat.jpg"};


void kopierKleur(GLfloat dest[], GLfloat src[])
{
  dest[0] = src[0];
  dest[1] = src[1];
  dest[2] = src[2];
  dest[3] = src[3];
}

void steunBalk()
{
  float ratio = steunBalkLengte/steunBalkDikte;
  glPushMatrix();
  glRotated(-20, 1, 0, 1);	//20° naar binnen draaien
  glScalef(1.0, ratio, 1.0); //uitrekken
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, steunbalkA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, steunbalkD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, steunbalkS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);
  glutSolidCube(steunBalkDikte);
  glPopMatrix();
}

void steunBalken()
{
  glPushMatrix();
  float afstandx = cos(20*2*M_PI/360)*cos(45*2*M_PI/360)*steunBalkLengte/2-steunBalkDikte;
  float afstandz = afstandx + centraleAsLengte;
  glTranslatef(afstandx/2, steunBalkLengte/2, 0);	//centreer het geheel
  //glDouble clipvlak[4] = {};
  for (int i=0; i<2; i++)
  {
    glPushMatrix();
    glTranslatef(0, 0, afstandz/2);
    for (int j=0; j<2; j++)
    {
      glRotated(90, 0, 1, 0);
      steunBalk();
      glTranslatef(afstandz, 0, 0);
    }
    glPopMatrix();
    glRotated(180, 0, 1, 0);
    glTranslatef(afstandx, 0, 0);
  }
  glPopMatrix();
}

void centraleAs()
{
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, asA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, asD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, asS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);

  GLUquadricObj *cilinder;
  cilinder = gluNewQuadric();
    gluQuadricDrawStyle(cilinder, GLU_FILL);
    gluCylinder(cilinder, centraleAsStraal, centraleAsStraal, centraleAsLengte, 20, 20);
  gluDeleteQuadric(cilinder);

  cilinder = gluNewQuadric();
    gluQuadricDrawStyle(cilinder, GLU_FILL);
    gluCylinder(cilinder, 0, centraleAsStraal, 0, 20, 20);
  gluDeleteQuadric(cilinder);

  glTranslatef(0, 0, centraleAsLengte);	//naar ander einde van de as

  cilinder = gluNewQuadric();
    gluQuadricDrawStyle(cilinder, GLU_FILL);
    gluCylinder(cilinder, 0, centraleAsStraal, 0, 20, 20);
  gluDeleteQuadric(cilinder);

  glPopMatrix();
}

void spaken()
{
  glPushMatrix();
  glTranslatef(0, 0, (centraleAsLengte-schijfafstand+schijfDikte)/2);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, spaakA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, spaakD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spaakS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);
  for (int j=0; j<2; j++)
  {
    for (int i=0; i<aantalSpaken; i++)
    {
      glRotatef(360/aantalSpaken, 0, 0, 1);
      glPushMatrix();
      glRotated(90, 0, 1, 0);

      GLUquadricObj *cilinder;
      cilinder = gluNewQuadric();
        gluQuadricDrawStyle(cilinder, GLU_FILL);
        gluCylinder(cilinder, spaakDikte, spaakDikte, schijfStraal, 20, 20);
      gluDeleteQuadric(cilinder);
      glPopMatrix();
    }
    glTranslatef(0, 0, schijfafstand-schijfDikte);
  }
  glPopMatrix();
}

void schijven()
{
  glPushMatrix();
  if (doorzichtig)
    glEnable(GL_BLEND);
  glTranslatef(0, 0, (centraleAsLengte-schijfafstand)/2);
  float binnenstraal = schijfStraal-schijfDikte/2;
  float buitenstraal = schijfStraal+schijfDikte/2;
  for (int i=0; i<2; i++)
  {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, schijfA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, schijfD);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, schijfS);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);

    GLUquadricObj *cilinder;

    cilinder = gluNewQuadric();	//buitenschijf
      gluQuadricDrawStyle(cilinder, GLU_FILL);
      gluCylinder(cilinder, buitenstraal, buitenstraal, schijfDikte, 20, 20);
    gluDeleteQuadric(cilinder);

    cilinder = gluNewQuadric();	//binnenschijf
      gluQuadricDrawStyle(cilinder, GLU_FILL);
      gluCylinder(cilinder, binnenstraal, binnenstraal, schijfDikte, 20, 20);
    gluDeleteQuadric(cilinder);

    cilinder = gluNewQuadric();	//rechterschijf
      gluQuadricDrawStyle(cilinder, GLU_FILL);
      gluCylinder(cilinder, buitenstraal, binnenstraal, 0, 20, 20);
    gluDeleteQuadric(cilinder);

    glTranslatef(0, 0, schijfDikte);	//ga even naar linkerschijf positie
    cilinder = gluNewQuadric();	//linkerschijf
      gluQuadricDrawStyle(cilinder, GLU_FILL);
      gluCylinder(cilinder, buitenstraal, binnenstraal, 0, 20, 20);
    gluDeleteQuadric(cilinder);

    glTranslatef(0, 0, -schijfDikte);	//keer terug om volgende schijf vanuit rechts te beginnen
    glTranslatef(0, 0, schijfafstand-schijfDikte);	//ga naar andere kant rad
  }
  glDisable(GL_BLEND);
  glPopMatrix();
}

void bakmesh()
{
  glDisable(GL_LIGHTING);
  glPointSize(8.0);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
    for (int i=0; i<6; i++)
    {
      for (int j=0; j<4; j++)
        glVertex3f(bakpunten[i][j][0], bakpunten[i][j][1], bakpunten[i][j][2]);
    }
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  for (int i=0; i<6; i++)
  {
    glBegin(GL_LINE_STRIP);
      for (int j=0; j<4; j++)
        glVertex3f(bakpunten[i][j][0], bakpunten[i][j][1], bakpunten[i][j][2]);
    glEnd();
  }
  for (int i=0; i<4; i++)
  {
    glBegin(GL_LINE_STRIP);
      for (int j=0; j<6; j++)
        glVertex3f(bakpunten[j][i][0], bakpunten[j][i][1], bakpunten[j][i][2]);
    glEnd();
  }
  glEnable(GL_LIGHTING);
}

void dakmesh()
{
  glDisable(GL_LIGHTING);
  glPointSize(8.0);
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_POINTS);
    for (int i=0; i<4; i++)
    {
      for (int j=0; j<4; j++)
        glVertex3f(dakpunten[i][j][0], dakpunten[i][j][1], dakpunten[i][j][2]);
    }
  glEnd();
  glColor3f(0.0, 0.0, 1.0);
  for (int i=0; i<4; i++)
  {
    glBegin(GL_LINE_STRIP);
      for (int j=0; j<4; j++)
      glVertex3f(dakpunten[i][j][0], dakpunten[i][j][1], dakpunten[i][j][2]);
    glEnd();
  }
  for (int i=0; i<4; i++)
  {
    glBegin(GL_LINE_STRIP);
      for (int j=0; j<4; j++)
        glVertex3f(dakpunten[j][i][0], dakpunten[j][i][1], dakpunten[j][i][2]);
    glEnd();
  }
  glEnable(GL_LIGHTING);
}

void bakje()
{
  glPushMatrix();
  for (int i=0; i<2; i++)
  {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, zitjeA);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, zitjeD);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, zitjeS);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);

    if (textuur)
      glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, textuurobject[KUIPI]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 6, &bakpunten[0][0][0]);
    glEnable(GL_MAP2_VERTEX_3);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 3, 4, 0, 1, 12, 6, &bakpunten[0][0][0]);
      glEnable(GL_MAP2_TEXTURE_COORD_2);
        glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
      glDisable(GL_MAP2_TEXTURE_COORD_2);
    glDisable(GL_MAP2_VERTEX_3);

    glDisable(GL_TEXTURE_2D);
    if (toonmesh)
      bakmesh();
    glScalef(-1, 1, 1);
  }
  glPopMatrix();
}

void ophangstaaf()
{
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, stangenA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, stangenD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, stangenS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);

  //vertikale staaf tussen bodem bakje en horizontale staaf
  glPushMatrix();
  glTranslatef(0, 0.3, 0);
  glRotated(-90, 1, 0, 0);

  GLUquadricObj *cilinder;
  cilinder = gluNewQuadric();
    gluQuadricDrawStyle(cilinder, GLU_FILL);
    gluCylinder(cilinder, ophangdikte, ophangdikte, ophanghoogte-0.3, 20, 20);
  gluDeleteQuadric(cilinder);
  glPopMatrix();

  //horizontale staaf tussen schijven
  glPushMatrix();
  glTranslatef(0, ophanghoogte-ophangdikte/2, -schijfafstand/2);

  cilinder = gluNewQuadric();
    gluQuadricDrawStyle(cilinder, GLU_FILL);
    gluCylinder(cilinder, ophangdikte, ophangdikte, schijfafstand, 20, 20);
  gluDeleteQuadric(cilinder);

  glPopMatrix();
}

void dak()
{
  glPushMatrix();
  glTranslatef(0, ophanghoogte-ophangdikte-1.5, 0);
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, dakA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, dakD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, dakS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);

  glBindTexture(GL_TEXTURE_2D, textuurobject[DAKI]);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  for (int i=0; i<4; i++)
  {
    if (textuur)
    glEnable(GL_TEXTURE_2D);
    glRotated(90, 0, 1, 0);
    glPushMatrix();
    glRotated(90, -1, 0, 0);
    GLUnurbsObj *dakelement;
    dakelement = gluNewNurbsRenderer();
      gluNurbsProperty(dakelement, GLU_DISPLAY_MODE, GLU_FILL);
      gluNurbsProperty(dakelement, GLU_SAMPLING_TOLERANCE, 25.0);
      gluBeginSurface(dakelement);
        gluNurbsSurface(dakelement, 8, dakknopen, 8, dakknopen, 4*3, 3, &dakpunten[0][0][0], 4, 4, GL_MAP2_TEXTURE_COORD_2);
        gluNurbsSurface(dakelement, 8, dakknopen, 8, dakknopen, 4*3, 3, &dakpunten[0][0][0], 4, 4, GL_MAP2_VERTEX_3);
      gluEndSurface(dakelement);
    gluDeleteNurbsRenderer(dakelement);
    glDisable(GL_TEXTURE_2D);
    if (toonmesh)
      dakmesh();
    glPopMatrix();
  }
  glPopMatrix();
}

void zitje()
{
  glPushMatrix();
  glRotatef(animhoek, 0, 0, -1);	//om draaien rad tegen te werken
  glRotatef(wiebelhoek, 0, 0, 1);	//schommel beweging
  glTranslatef(0, -ophanghoogte+.2, 0);	//zodat ophangstaaf in het relatieve midden zit
  bakje();
  ophangstaaf();
  dak();
  glPopMatrix();
}

void zitjes()
{
  glPushMatrix();
  glTranslatef(0, 0, centraleAsLengte/2);
  for (int i=0; i<aantalZitjes; i++)
  {
    glRotatef(360/aantalZitjes, 0, 0, 1);
    glPushMatrix();
    glTranslatef(schijfStraal, 0, 0);
    glRotatef(360/aantalZitjes*(i+1), 0, 0, -1);
    zitje();
    glPopMatrix();
  }
  glPopMatrix();
}

void rad()
{
  glPushMatrix();
  glTranslatef(0, steunBalkLengte, -centraleAsLengte/2);	//plaats het rad boven de steunbalken
  glRotatef(animhoek, 0, 0, 1);	//draai het rad
  centraleAs();
  zitjes();
  spaken();
  schijven();
  glPopMatrix();
}

void vloer()
{
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, steunbalkA);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, steunbalkD);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, steunbalkS);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);
  if (textuur)
    glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, textuurobject[VLOERI]);
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

  glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0); glVertex3f(-10, 0, -10);
    glTexCoord2f(1.0, 0.0); glVertex3f( 10, 0, -10);
    glTexCoord2f(1.0, 1.0); glVertex3f( 10, 0,  10);
    glTexCoord2f(0.0, 1.0); glVertex3f(-10, 0,  10);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  glPopMatrix();
}

void assen()
{
  if (assenkruis)
  {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glColor3f(0.0, 0.5, 0.5);
    glBegin(GL_LINES);
      glVertex3f(-10.0, 0.0, 0.0);
      glVertex3f(10.0, 0.0, 0.0);
    glEnd();
    glColor3f(0.5, 0.0, 0.5);
    glBegin(GL_LINES);
      glVertex3f(0.0, -10.0, 0.0);
      glVertex3f(0.0, 10.0, 0.0);
    glEnd();
    glColor3f(0.5, 0.5, 0.0);
    glBegin(GL_LINES);
      glVertex3f(0.0, 0.0, -10.0);
      glVertex3f(0.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();
    glEnable(GL_LIGHTING);
  }
}

void belichting()
{
  glLightfv(GL_LIGHT0, GL_POSITION, aplaats);
  glLightfv(GL_LIGHT1, GL_POSITION, dplaats);
  glLightfv(GL_LIGHT2, GL_POSITION, splaats);
  glLightfv(GL_LIGHT3, GL_POSITION, spplaats);

  //spot instellingen
  GLfloat richting[] = {-1, -1, 0};
  glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, richting);
  glLightf(GL_LIGHT3, GL_SPOT_CUTOFF, spothoek);
  glLightf(GL_LIGHT3, GL_SPOT_EXPONENT, spotexponent);
  glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 0.0);
  glLightf(GL_LIGHT3, GL_LINEAR_ATTENUATION, 0.0);
  glLightf(GL_LIGHT3, GL_QUADRATIC_ATTENUATION, 1.0);

  if (toonlamp)
  {
    glDisable(GL_LIGHTING);
    glPointSize(8.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex3f(aplaats[0], aplaats[1], aplaats[2]);
    glVertex3f(dplaats[0], dplaats[1], dplaats[2]);
    glVertex3f(splaats[0], splaats[1], splaats[2]);
    glVertex3f(spplaats[0], spplaats[1], spplaats[2]);
    glEnd();
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3fv(spplaats);
    glVertex3f(spplaats[0]+5*richting[0], spplaats[1]+5*richting[1], spplaats[2]+5*richting[2]);
    glEnd();
    glEnable(GL_LIGHTING);
  }
}

void mistf()
{
  glEnable(GL_FOG);
  if (mist > 2)
    glFogi(GL_FOG_MODE, GL_EXP2);
  if (mist == 2)
    glFogi(GL_FOG_MODE, GL_EXP);
  if (mist == 1)
    glFogi(GL_FOG_MODE, GL_LINEAR);
  glFogfv(GL_FOG_COLOR, mistkleur);
  glFogf(GL_FOG_DENSITY, 0.25);
  glFogf(GL_FOG_START, 0.0);
  glFogf(GL_FOG_END, 70.0);
}

void kermis()	//display functie
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (xlens == 0 && zlens == 0)
    gluLookAt(xlens,ylens,zlens, 0,0,0, -1,0,0);	//indien recht boven rad, herorienteer camera
  else
    gluLookAt(xlens,ylens,zlens, 0,0,0, 0,1,0);

  glEnable(GL_LIGHTING);
  belichting();	//eerst lookat, dan pas belichting zodat belichting

  if (mist)
    mistf();

  assen();

  glTranslatef(0, -steunBalkLengte, 0);		//plaats de as ongeveer in het midden
  vloer();
  steunBalken();
  rad();
  if (meerdere)
  {
    glTranslatef(0.75*schijfStraal, 0, -2.5*centraleAsLengte);
    steunBalken();
    rad();
  }
  if (mist)
    glDisable(GL_FOG);
  glDisable(GL_LIGHTING);

  glFlush();
}

void raam(GLint newWidth, GLint newHeight)	//herschaling
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  switch(projectie)
  {
    case 'p':
      gluPerspective(cameraHoek, 1.0, near, far);
      printf("Perspectief projectie\n");
      xlens = 40;
      ylens = 15;
      zlens = 35;
      break;
    case 'f':
      glFrustum(xmin/10, xmax/10, ymin/10, ymax/10, 3*near,9*far);
      printf("Frustum projectie\n");
      /*xlens = 15;
      ylens = 15;
      zlens = 20;*/
      break;
    case 'o':
    default:
      glOrtho(xmin, xmax, ymin, ymax, near, far);
      printf("Orthogonale projectie\n");
      break;
  }
  if (newWidth > aspectratio*newHeight)
    glViewport(0, 0, newHeight*aspectratio, newHeight);
  else
    glViewport(0, 0, newWidth, newWidth/aspectratio);
  //printf("ar:%f, w%d, h%d, nw%d, nh%d \n", aspectratio, winWidth, winHeight, newWidth, newHeight);
  winWidth = newWidth;
  winHeight = newHeight;
}

void init()
{
  glClearColor(0.8, 0.8, 0.8, 0.0);
  glEnable(GL_DEPTH_TEST);
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, zwart);	//Geen belichting zonder lampen

  //Default belichting uit de lampen halen
  glLightfv(GL_LIGHT0,GL_AMBIENT,ambient);
  glLightfv(GL_LIGHT1,GL_AMBIENT,zwart);
  glLightfv(GL_LIGHT2,GL_AMBIENT,zwart);
  glLightfv(GL_LIGHT3,GL_AMBIENT,spot);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,zwart);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,diffuus);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,zwart);
  glLightfv(GL_LIGHT3,GL_DIFFUSE,spot);
  glLightfv(GL_LIGHT0,GL_SPECULAR,zwart);
  glLightfv(GL_LIGHT1,GL_SPECULAR,zwart);
  glLightfv(GL_LIGHT2,GL_SPECULAR,specular);
  glLightfv(GL_LIGHT3,GL_SPECULAR,spot);

  glMaterialf(GL_FRONT, GL_SHININESS, 127.0);

  glBlendFunc(srcf, dstf);

  kopierKleur(zitjeA, grijsA);
  kopierKleur(zitjeD, grijsD);
  kopierKleur(zitjeS, grijsS);

  kopierKleur(stangenA, chroomA);
  kopierKleur(stangenD, chroomD);
  kopierKleur(stangenS, chroomS);

  kopierKleur(dakA, geelA);
  kopierKleur(dakD, geelD);
  kopierKleur(dakS, geelS);

  tImageJPG *loadImage;
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(AANTALAFBEELDINGEN, textuurobject);
  for (int i=0; i<AANTALAFBEELDINGEN; i++)
  {
    loadImage = LoadJPG(jpgnaam[i]);
    fprintf(stderr, "Afbeelding %s: %d x %d\n", jpgnaam[i], loadImage->sizeX, loadImage->sizeY);
    glBindTexture(GL_TEXTURE_2D, textuurobject[i]);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, loadImage->sizeX, loadImage->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, loadImage->data);
  }

  aspectratio = 1.0*winWidth/winHeight;
}

void toets(unsigned char key, int x, int y)	//toetsen
{
  switch(key)
  {
    case 'a': glEnable(GL_LIGHT0); break;
    case 'A': glDisable(GL_LIGHT0); break;
    case 'b': glEnable(GL_LIGHT1); break;
    case 'B': glDisable(GL_LIGHT1); break;
    case 'c': glEnable(GL_LIGHT2); break;
    case 'C': glDisable(GL_LIGHT2); break;
    case 'd': glEnable(GL_LIGHT3); break;
    case 'D': glDisable(GL_LIGHT3); break;
    case 'e': shini+=5; break;
    case 'E': shini-=5; break;
    case 'f': doorzichtig = !doorzichtig; break;
    case 'g': draai = !draai; break;
    case 'G': wiebel = !wiebel; break;
    case 'h': spplaats[1]++; break;
    case 'H': spplaats[1]--; break;

    case 'j': assenkruis = !assenkruis; break;
    case 'k': controlepunten = !controlepunten; break;
    case 'l': toonmesh = !toonmesh; break;
    case 'L': toonlamp = !toonlamp; break;
    case 'm': mist = !mist; break;
    case 'M': mist++; break;
    case 'n': meerdere = !meerdere; break;

    case 'q': exit(0); break;
    case 'r': animhoek = 0; wiebelhoek = 0; break;
    case 's': glShadeModel(GL_FLAT); smooth=0; break;
    case 'S': glShadeModel(GL_SMOOTH); smooth=1; break;
    case 't': textuur = !textuur; break;

    case 'v': spothoek++; break;
    case 'V': spothoek--; break;
    case 'w': spotexponent+=5; break;
    case 'W': spotexponent-=5; break;
    case 'x': xlens++; break;
    case 'X': xlens--; break;
    case 'y': ylens++; break;
    case 'Y': ylens--; break;
    case 'z': zlens++; break;
    case 'Z': zlens--; break;
  }
  if (tooninfo)
  {
    printf("\n--------------------------------------------------------------\n");
    printf("Draaien: %d, Wiebelen: %d, Mist: %d, Textuur: %d doorzichtig: %d\n", draai, wiebel, mist, textuur, doorzichtig);
    printf("Meerder: %d, Shading: %d, Mesh: %d, Assen: %d, Controlepunten: %d\n", meerdere, smooth, toonmesh, assenkruis, controlepunten);
    printf("Lamp 0: %d, 1: %d, 2: %d, 3: %d, Lamppunten: %d\n", glIsEnabled(GL_LIGHT0), glIsEnabled(GL_LIGHT1), glIsEnabled(GL_LIGHT2), glIsEnabled(GL_LIGHT3), toonlamp);
    printf("Spot hoogte: %f, hoek: %f, exponent: %f\n", spplaats[1], spothoek, spotexponent);
    printf("Shininess: %f\n", shini);
    printf("Lens x: %f, y: %f, z: %f\n", xlens, ylens, zlens);
  }
  glutPostRedisplay();
}

void anim(int delta)
{
  if (draai)
    animhoek += delta;
  if (wiebel)
    wiebelhoek += delta * wiebeldelta;
  if (animhoek > 360)
    animhoek -= 360;
  if (abs(wiebelhoek) > 25)	//max 25 graden afwijken van stilstand
    wiebeldelta = wiebeldelta * -1;
  glutTimerFunc(tijd, anim, delta);
  glutSwapBuffers();
  glutPostRedisplay();
}

void menu(int keuze)
{
  switch (keuze)
  {
    case 0:
      kopierKleur(zitjeA, grijsA);
      kopierKleur(zitjeD, grijsD);
      kopierKleur(zitjeS, grijsS);
      break;
    case 1:
      kopierKleur(zitjeA, witachtigA);
      kopierKleur(zitjeD, witachtigD);
      kopierKleur(zitjeS, witachtigS);
      break;
    case 2:
      kopierKleur(stangenA, chroomA);
      kopierKleur(stangenD, chroomD);
      kopierKleur(stangenS, chroomS);
      break;
    case 3:
      kopierKleur(stangenA, bronsA);
      kopierKleur(stangenD, bronsD);
      kopierKleur(stangenS, bronsS);
      break;
    case 4:
      kopierKleur(dakA, geelA);
      kopierKleur(dakD, geelD);
      kopierKleur(dakS, geelS);
      break;
    case 5:
      kopierKleur(dakA, lilaA);
      kopierKleur(dakD, lilaD);
      kopierKleur(dakS, lilaS);
      break;
  }
}

void maakMenu()
{
  GLint zitjemenu = glutCreateMenu(menu);
    glutAddMenuEntry("Grijs", 0);
    glutAddMenuEntry("Witachtig", 1);
  GLint stangenmenu = glutCreateMenu(menu);
    glutAddMenuEntry("Chroom", 2);
    glutAddMenuEntry("Brons", 3);
  GLint dakmenu = glutCreateMenu(menu);
    glutAddMenuEntry("Geel", 4);
    glutAddMenuEntry("Lila", 5);
  glutCreateMenu(menu);
    glutAddSubMenu("Zitje", zitjemenu);
    glutAddSubMenu("Stangen", stangenmenu);
    glutAddSubMenu("Dak", dakmenu);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main (int argc, char* argv[])
{
  char c;
  while ((c=getopt(argc, argv, "-i-z:-p:")) != EOF)
  {
    switch (c)
    {
      case 'z': aantalZitjes = atoi(optarg); break;
      case 'p': projectie = *optarg; break;
      case 'i': tooninfo = 1; break;
    }
  }
  if (aantalZitjes > 10)
    aantalZitjes = 10;
  printf("%d zitjes.\n", aantalZitjes);
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowPosition(1,1);
  glutInitWindowSize(winWidth, winHeight);
  glutCreateWindow("Reuzenrad Kwinten Vanlathem");
  init();
  glutReshapeFunc(raam);
  glutDisplayFunc(kermis);
  glutKeyboardFunc(toets);
  maakMenu();
  glutTimerFunc(tijd, anim, 1); //bepaald updatesnelheid en draaistappen
  glutMainLoop();
}
