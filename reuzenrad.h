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

int tooninfo = 0;
int toonlamp = 0;
int smooth = 1; //controlekarakter

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
float wiebeldelta = 0.4;

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
  GLfloat spplaats[3] = {0, 30, 0}; //spot

  //lichtkleuren:
  GLfloat ambient[] = {1, 1, 1, 0}; //wit
  GLfloat diffuus[] = {.10, .90, .90, 0}; //groen-blauw
  GLfloat specular[] = {.90, .10, .10, 0};  //rood
  GLfloat spot[] = {.95, .95, .05, 0};  //geel
  GLfloat zwart[] = {.0, .0, .0, 1};  //zwart

  //materiaalkleuren:
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
