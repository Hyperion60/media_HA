#include <err.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); // Efface le buffer
    glColor3f(0.0, 0.0, 1.0); // Defini la couleur RGB
    glBegin(GL_LINES); // Trace des lignes entre des couples de points
    glVertex3f(10, 10, 0.0); // Point 1
    glVertex3f(100, 100, 0.0); // Point 2
    glEnd();
    glutSwapBuffers(); // Affiche a l'ecran le buffer dans lequel nous avons dessine
}


void affiche(void)
{
    glutPostRedisplay();
    usleep(1000);
}


void *thread_affichage(void *arguments)
{
    int nbarg = 1;
    glutInit(&nbarg, (char **)arguments); // Fonction d'initialisation
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB); // Utilise le codage RGB en double buffer
    glutInitWindowSize(500, 500); // Taille de la fenetre que l'on va creer
    glutInitWindowPosition(50, 10); // Position de la fenetre sur l'ecran
    glutCreateWindow("Bonjour"); // Nom de la fenetre

    glClearColor(1.0, 1.0, 1.0, 0.0); // Defini la couleur d'effacement par defaut, ici blanc
    glOrtho(0, 500, 0, 500, -1.0, 1.0); // Defini la position du repere dans la scene visible

    glutDisplayFunc(display); // Defini la fonction appelee pour afficher la scene
    glutIdleFunc(affiche); // Defini la fonction lancee lorsque le systeme n'a plus rien a faire
    glutMainLoop(); // Fonction bloquante permettant la gestion de l'affichage
}

int main(int argc, char **argv)
{
    pthread_t thr_print;
    int e = pthread_create(&thr_print, NULL, thread_affichage, argv);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");

    pthread_join(thr_print, NULL);
    return 0;
}
