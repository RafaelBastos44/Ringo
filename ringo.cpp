#include <gl/glut.h>
#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

const int DIMX = 900;
const int DIMY = 900;
const int radTab = 70;

int nivelMouse1 = 0;
int setorMouse1 = 0;
int nivelMouse2 = 0;
int setorMouse2 = 0;

int selecionado;
int turno = 1;

int tabuleiro[8][6] = { {0,0,0,0,0,0},
                       {1,2,1,2,1,2},
                       {2,1,2,1,2,1},
                       {1,2,1,2,1,2},
                       {2,1,2,1,2,1},
                       {1,2,1,2,1,2},
                       {2,1,2,1,2,1},
                       {1,2,1,2,1,2} };

int tabuleiroPecas[8][6] = { {0,0,0,0,0,0},
                           {0,2,0,0,0,1},
                           {0,0,0,0,0,1},
                           {0,2,0,0,0,1},
                           {0,0,0,0,0,1},
                           {0,2,0,0,0,1},
                           {0,0,0,0,0,1},
                           {0,2,0,0,0,1} };

void desenhaCirculo(float radius)
{
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glLineWidth(4);
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 361; i++) {
        float radian = i * 3.14159 / 180.0;
        glVertex2f(DIMX / 2 + radius * cos(radian), DIMY / 2 + radius * sin(radian));
    }
    glEnd();
}

void desenhaLinhas(float x0, float y0, float radius)
{
    glColor4f(0.0, 0.0, 0.0, 1.0);
    glLineWidth(4);
    glBegin(GL_LINES);
    for (int i = 0; i < 8; i++) {
        float radian = 45 * i * 3.14159 / 180.0;
        glVertex2f(x0 + radius * cos(radian), y0 + radius * sin(radian));
        glVertex2f(x0 + 70 * cos(radian), y0 + 70 * sin(radian));
    }
    glEnd();
}

void desenhaCirculoPreenchido(float x, float y, int color, int rad)
{
    if (color == 1)
        glColor4f(1.0, 0.0, 0.0, 1.0);
    else if (color == 2)
        glColor4f(0.0, 1.0, 0.0, 1.0);
    else
        glColor4f(0.0, 0.6, 1.0, 1.0);

    glBegin(GL_POLYGON);
    for (int i = 0; i < 361; i++) {
        float radian = i * 3.14159 / 180.0;
        glVertex2f(x + rad * cos(radian), y + rad * sin(radian));
    }
    glEnd();
}

void desenhaPecaPolar(int setor, int nivel, int color)
{
    if (color == 0) return;
    //Setor vai de 0(0->45) a 7(315->360)
    float ang = (22.5 + (45 * setor)) * PI / 180;
    //Nivel vai de 0 a 5
    float dist = 35 + nivel * (radTab);
    float x = DIMX / 2 + dist * cos(ang);
    float y = DIMY / 2 - dist * sin(ang);

    //int r = 20;

    desenhaCirculoPreenchido(x, y, color, 20);
}

void desenhaSetorParcial(int setor, int nivel, int state)
{
    //Setor vai de 0(0->45) a 7(315->360)
    int angSetor = 45 * (setor + 1);
    //Nivel vai de 0 a 5
    float dist1 = nivel * radTab;
    float dist2 = (nivel * radTab) + radTab;

    float x = DIMX / 2;
    float y = DIMY / 2;

    if (state == 0)
        glColor4f(0.5, 0.5, 0.5, 0.0);
    else if (state == 1)
        glColor4f(0.0, 0.0, 0.0, 0.0);
    else
        glColor4f(94 / 255.0, 29 / 255.0, 0.0, 1.0);

    glBegin(GL_POLYGON);
    for (int i = angSetor - 45; i <= angSetor; i++) {
        float radian = i * PI / 180.0;
        glVertex2f(x + dist2 * cos(radian), y - dist2 * sin(radian));
    }
    glVertex2f(x + dist1 * cos((angSetor)*PI / 180), y - dist1 * sin((angSetor)*PI / 180));
    glVertex2f(x + dist1 * cos((angSetor - 45) * PI / 180), y - dist1 * sin((angSetor - 45) * PI / 180));
    glEnd();
}

void convCartPolar(int x, int y, int& setor, int& nivel)
{
    float dist = sqrt(pow(x - DIMX / 2, 2) + pow(y - DIMY / 2, 2));
    float ang = atan2(DIMY / 2 - y, x - DIMX / 2) * 180 / PI;
    if (ang < 0)
        ang = ang + 360;

    setorMouse2 = setor;
    nivelMouse2 = nivel;
    setor = ang / 45;
    nivel = dist / radTab;
}

void movePeca()
{
    if (selecionado == 1 && tabuleiroPecas[setorMouse2][nivelMouse2] != 2) //Atacante
    {
        //Movimento
        if ((nivelMouse2 == nivelMouse1 + 1) && (nivelMouse1 == 0))
        {
            tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
            tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }
        else if ((setorMouse2 == setorMouse1) && (nivelMouse2 == nivelMouse1 + 1))
        {
            tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
            tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }
        if (((setorMouse2 == (setorMouse1 + 1) % 8) || (setorMouse2 == (setorMouse1 + 7) % 8)) && (nivelMouse2 == nivelMouse1))
        {
            tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
            tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }

        //Captura
        //Captura no mesmo n�vel
        if (((setorMouse2 == (setorMouse1 + 2) % 8) || (setorMouse2 == (setorMouse1 + 6) % 8)) && (nivelMouse2 == nivelMouse1))
        {
            if ((tabuleiroPecas[(setorMouse1 + 7) % 8][nivelMouse1] == 2) && (tabuleiroPecas[(setorMouse2 + 1) % 8][nivelMouse2] == 2) && (((setorMouse1 + 7) % 8) == ((setorMouse2 + 1) % 8)) && (setorMouse1 + 7) % 8 != 0)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[(setorMouse1 + 7) % 8][nivelMouse1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
                std::cout << "\nUm atacante capturou um defensor.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
            else if ((tabuleiroPecas[(setorMouse1 + 1) % 8][nivelMouse1] == 2) && (tabuleiroPecas[(setorMouse2 + 7) % 8][nivelMouse2] == 2) && (((setorMouse1 + 1) % 8) == ((setorMouse2 + 7) % 8)) && (setorMouse1 + 1) % 8 != 0)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[(setorMouse1 + 1) % 8][nivelMouse1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
                std::cout << "\nUm atacante capturou um defensor.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
        }
        //Captura no mesmo setor
        else if ((setorMouse2 == setorMouse1) && (nivelMouse2 == nivelMouse1 + 2) && (setorMouse1 != 0))
        {
            if (tabuleiroPecas[setorMouse1][nivelMouse1 + 1] == 2)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1 + 1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 1;
                std::cout << "\nUm atacante capturou um defensor.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
        }
    }
    else if (selecionado == 2 && tabuleiroPecas[setorMouse2][nivelMouse2] != 1) //Defensor
    {
        //Movimento
        if (((setorMouse2 == (setorMouse1 + 1) % 8) || (setorMouse2 == (setorMouse1 + 7) % 8)) && (nivelMouse2 == nivelMouse1))
        {
            tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
            tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }
        else if ((setorMouse2 == setorMouse1) && ((nivelMouse2 == nivelMouse1 + 1) || (nivelMouse2 == nivelMouse1 - 1)) && (nivelMouse1 != 0))
        {
            tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
            tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }

        //Captura
        //Captura no mesmo n�vel
        if (((setorMouse2 == (setorMouse1 + 2) % 8) || (setorMouse2 == (setorMouse1 + 6) % 8)) && (nivelMouse2 == nivelMouse1))
        {
            if ((tabuleiroPecas[(setorMouse1 + 7) % 8][nivelMouse1] == 1) && (tabuleiroPecas[(setorMouse2 + 1) % 8][nivelMouse2] == 1) && (((setorMouse1 + 7) % 8) == ((setorMouse2 + 1) % 8)) && (setorMouse1 + 7) % 8 != 0)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[(setorMouse1 + 7) % 8][nivelMouse1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
                std::cout << "\nUm defensor capturou um atacante.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
            else if ((tabuleiroPecas[(setorMouse1 + 1) % 8][nivelMouse1] == 1) && (tabuleiroPecas[(setorMouse2 + 7) % 8][nivelMouse2] == 1) && (((setorMouse1 + 1) % 8) == ((setorMouse2 + 7) % 8)) && (setorMouse1 + 1) % 8 != 0)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[(setorMouse1 + 1) % 8][nivelMouse1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
                std::cout << "\nUm defensor capturou um atacante.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
        }
        //Captura no castelo
        else if ((nivelMouse2 == 1 && nivelMouse1 == 1) && (fabs((setorMouse1 - setorMouse2)) == 4))
        {
            int atacantesCastelo = 0;
            for (int setorCastelo = 0; setorCastelo < 8; setorCastelo++)
            {
                if (tabuleiroPecas[setorCastelo][0] == 1)
                    atacantesCastelo++;
            }

            if (atacantesCastelo > 0)
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 2;

                for (int i = 0; i < 8; i++)
                    tabuleiroPecas[i][0] = 0;

                std::cout << "\nUm defensor capturou um atacante.\n" << std::endl;
            }
            turno++;
            std::cout << "Turno: " << turno << std::endl;
        }
        //Captura no mesmo setor
        else if ((setorMouse2 == setorMouse1) && ((nivelMouse2 == nivelMouse1 + 2) || (nivelMouse2 == nivelMouse1 - 2)) && (setorMouse1 != 0))
        {
            if (tabuleiroPecas[setorMouse1][nivelMouse1 + 1] == 1 && (nivelMouse1 + 1 == nivelMouse2 - 1))
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1 + 1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
                std::cout << "\nUm defensor capturou um atacante.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
            else if (tabuleiroPecas[setorMouse1][nivelMouse1 - 1] == 1 && (nivelMouse1 - 1 == nivelMouse2 + 1))
            {
                tabuleiroPecas[setorMouse2][nivelMouse2] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1 - 1] = 0;
                tabuleiroPecas[setorMouse1][nivelMouse1] = 2;
                std::cout << "\nUm defensor capturou um atacante.\n" << std::endl;
                turno++;
                std::cout << "Turno: " << turno << std::endl;
            }
        }
    }
}

void verificaClique()
{
    std::cout << setorMouse1 << ' ' << nivelMouse1 << std::endl;
    std::cout << setorMouse2 << ' ' << nivelMouse2 << std::endl;
    if (tabuleiroPecas[setorMouse1][nivelMouse1] == 0)
    {
        std::cout << "Casa vazia Selecionada" << std::endl;
        movePeca();
        selecionado = 0;
    }

    else if (tabuleiroPecas[setorMouse1][nivelMouse1] == 1) //Atacantes
    {
        if (turno % 2 != 0)
        {
            std::cout << "Atacante Selecionado" << std::endl;
            selecionado = 1;
        }
        else
            std::cout << "Turno dos defensores." << std::endl;
    }

    else //Defensores
    {
        if (turno % 2 == 0)
        {
            std::cout << "Defensor Selecionado" << std::endl;
            selecionado = 2;
        }
        else
            std::cout << "Turno dos atacantes." << std::endl;
    }
}

int verificaVitoria(void)
{
    int countCastelo = 0;
    int countAtacantes = 0;
    int countDefensores = 0;

    for (int s = 0; s < 8; s++)
    {
        if (tabuleiroPecas[s][0] == 1)
            countCastelo++;
    }
    if (countCastelo > 1)
        return 1;

    for (int setor = 0; setor < 8; setor++)
    {
        for (int nivel = 0; nivel < 6; nivel++)
        {
            if (tabuleiroPecas[setor][nivel] == 1)
                countAtacantes++;
        }
    }
    if (countAtacantes == 1)
        return 2;

    for (int setor = 0; setor < 8; setor++)
    {
        for (int nivel = 0; nivel < 6; nivel++)
        {
            if (tabuleiroPecas[setor][nivel] == 2)
                countDefensores++;
        }
    }
    if (countDefensores == 0)
        return 1;

    return 0;
}

void desenhaTabuleiroPecas()
{
    int state;
    for (int setor = 0; setor < 8; setor++)
    {
        for (int nivel = 0; nivel < 6; nivel++)
        {
            state = tabuleiroPecas[setor][nivel];
            desenhaPecaPolar(setor, nivel, state);
        }
    }
    if (verificaVitoria() == 1)
    {
        std::cout << "\nVitoria dos atacantes!!" << std::endl;
        exit(0);
    }
    else if (verificaVitoria() == 2)
    {
        std::cout << "\nVitoria dos defensores!!" << std::endl;
        exit(0);
    }
    glutPostRedisplay();
}

void mouse(int b, int state, int x, int y)
{
    if (b == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        convCartPolar(x, y, setorMouse1, nivelMouse1);
        verificaClique();
        desenhaTabuleiroPecas();
    }
}

void display(void)
{
    glClearColor(0.0, 0.2, 0.2, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    int state;
    for (int setor = 7; setor >= 0; setor--)
    {
        for (int nivel = 5; nivel >= 1; nivel--)
        {
            state = tabuleiro[setor][nivel];
            desenhaSetorParcial(setor, nivel, state);
        }
    }
    desenhaCirculoPreenchido(DIMX / 2, DIMY / 2, 3, radTab);
    for (int i = 0; i < 6; i++)
    {
        desenhaCirculo((radTab) * (i + 1));
    }
    desenhaLinhas(DIMX / 2, DIMY / 2, radTab * 6);

    desenhaTabuleiroPecas();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(DIMX, DIMY);
    glutInitWindowPosition(700, 50);
    glutCreateWindow("Ringo");
    gluOrtho2D(0, DIMX - 1, DIMY - 1, 0);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutMainLoop();
}