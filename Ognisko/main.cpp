#include <iostream>
#include <fstream>
#include <string>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/glm.hpp>
#include <GL/glext.h>
#include <GL/glut.h>
#include <time.h>
#include "Model_obj.h"
#include "Particle.h"
#include "shader.h"



Obiekt tree_model;
Obiekt grass_model;
Obiekt map;



Obiekt Ogien;

Obiekt Smoke;

const int Ilosc_Czasteczek_Ogien = 4000;

const int Ilosc_Czasteczek_Smoke = 100;

Particles_sys PsOgien;

Particles_sys SmokePs;

Shader shader;
int Ogien_czas = 1;

int Smoke_czas = 1;


glm::vec3 cam = glm::vec3(35, 15, 0);
glm::vec3 c_cam = glm::vec3(0, 0, 0);
glm::vec3 r_cam = glm::vec3(0, 2, 0);

void Verticies(objl::Loader loader)
{
    for (int i = 0; i < loader.LoadedMeshes.size(); i++)
    {
        objl::Mesh mesh = loader.LoadedMeshes[i];

        for (int j = 0; j < mesh.Vertices.size(); j++)
        {
            glVertex3f( mesh.Vertices[j].Position.X, mesh.Vertices[j].Position.Y, mesh.Vertices[j].Position.Z );
        }
    }
}

glm::vec3 Ogien_Pozycja()
{
    glm::mat4 mat_4_tmp = glm::mat4(1.0f);

    mat_4_tmp = glm::translate(mat_4_tmp,glm::vec3(1.0f,0.0f,1.0f));

    return glm::vec3(mat_4_tmp[2]);//?????
}


glm::vec3 SmokePosition()
{
    glm::mat4 mat_4_tmp = glm::mat4(1.0f);

    mat_4_tmp = glm::translate(mat_4_tmp,glm::vec3(0.0f,2.4f,1.0f));

    return glm::vec3(mat_4_tmp[3]);
}
void Map()
{
    map.Matrix_mod = glm::mat4(1.1f);
    map.Matrix_mod = glm::scale(map.Matrix_mod,glm::vec3(2.0f,1.0f,2.0f));
    map.Matrix_mod = glm::translate(map.Matrix_mod,glm::vec3(0.1f,-0.1f,0.1f));
    shader.Calculate(map.Matrix_mod);
    map.Wyswietlanie_Obiektu();
}

void grass()
{


    grass_model.Matrix_mod = glm::scale(glm::vec3(0.45f, 0.4f, 0.35f));
    grass_model.Matrix_mod = glm::translate(grass_model.Matrix_mod,glm::vec3(1.0f,1.0f,43.0f));
    shader.Calculate(grass_model.Matrix_mod);
    grass_model.Wyswietlanie_Obiektu();
}
void grass1()
{


    grass_model.Matrix_mod = glm::scale(glm::vec3(0.45f, 0.4f, 0.35f));
    grass_model.Matrix_mod = glm::translate(grass_model.Matrix_mod,glm::vec3(1.0f,1.f,-43.0f));
    shader.Calculate(grass_model.Matrix_mod);
    grass_model.Wyswietlanie_Obiektu();
}
void grass2()
{


	grass_model.Matrix_mod = glm::scale(glm::vec3(0.2f, 0.4f, 0.8f));
    grass_model.Matrix_mod = glm::translate(grass_model.Matrix_mod,glm::vec3(68.0f,1.f,1.0f));
    shader.Calculate(grass_model.Matrix_mod);
    grass_model.Wyswietlanie_Obiektu();

}
void grass3()
{


    grass_model.Matrix_mod = glm::scale(glm::vec3(0.2f, 0.4f, 0.8f));
    grass_model.Matrix_mod = glm::translate(grass_model.Matrix_mod,glm::vec3(-68.0f,1.f,1.0f));
    shader.Calculate(grass_model.Matrix_mod);
    grass_model.Wyswietlanie_Obiektu();

}
void tree()


{
    tree_model.Matrix_mod = glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
    tree_model.Matrix_mod = glm::translate(tree_model.Matrix_mod,glm::vec3(-35.0f,1.f,35.0f));
    shader.Calculate(tree_model.Matrix_mod);

    tree_model.Wyswietlanie_Obiektu();



}
void tree1()
{


    tree_model.Matrix_mod = glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
    tree_model.Matrix_mod = glm::translate(tree_model.Matrix_mod,glm::vec3(35.0f,1.f,35.0f));
    shader.Calculate(tree_model.Matrix_mod);

    tree_model.Wyswietlanie_Obiektu();

}
void tree2()
{


    tree_model.Matrix_mod = glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
    tree_model.Matrix_mod = glm::translate(tree_model.Matrix_mod,glm::vec3(-35.0f,1.f,-35.0f));
    shader.Calculate(tree_model.Matrix_mod);

    tree_model.Wyswietlanie_Obiektu();

}
void tree3()
{


    tree_model.Matrix_mod = glm::scale(glm::vec3(0.4f, 0.4f, 0.4f));
    tree_model.Matrix_mod = glm::translate(tree_model.Matrix_mod,glm::vec3(35.0f,1.f,-35.0f));
    shader.Calculate(tree_model.Matrix_mod);
    tree_model.Wyswietlanie_Obiektu();


}


void Czasteczki_Ogien()
{
    for(int i=0; i<PsOgien.get_Particle_Num(); i++)
    {
        if(PsOgien.Particle_left_time(i) > 0)
        {
            Ogien.Matrix_mod = glm::translate(PsOgien.getParticlelocation(i));



            glm::vec4 color;

            float tmp = (190 + rand()%48)/250.0f;

            if(rand()%2 == 0)
            {
                color = glm::vec4(tmp,0,0,2);
            }
            else
            {
                color = glm::vec4(tmp,tmp,0,2);
            }

            shader.Calculate(Ogien.Matrix_mod,color);
            Ogien.Wyswietlanie_Obiektu();

            PsOgien.P_left_time_decrease(i);
        }
        else
        {
            PsOgien.set_Left_Time(i,100+rand()%100);
            PsOgien.setlocation(i,Ogien_Pozycja());
        }

        PsOgien.setspeed(i,glm::vec3(( -10 + rand()%21)/100.0f, ( rand()%5)/100.0f, (-10 + rand()%21)/100.0f));
        PsOgien.changelocation(i);
    }
}

void SmokeP()
{
    for(int i=0; i<SmokePs.get_Particle_Num(); i++)
    {
        if(SmokePs.Particle_left_time(i) > 0)
        {
            Smoke.Matrix_mod = glm::translate(SmokePs.getParticlelocation(i));



            glm::vec4 color;

            float tmp = (190 + rand()%48)/250.0f;


            color = glm::vec4(tmp,tmp,tmp,1);
            shader.Calculate(Smoke.Matrix_mod,color);
            Smoke.Wyswietlanie_Obiektu();

            SmokePs.P_left_time_decrease(i);
        }
        else
        {
            SmokePs.set_Left_Time(i,100+rand()%100);
            SmokePs.setlocation(i,SmokePosition());
        }

        SmokePs.setspeed(i,glm::vec3(( -10 + rand()%21)/100.0f, (  5+ rand()%8)/100.0f, (-10 + rand()%21)/100.0f));
        SmokePs.changelocation(i);
    }
}
void F_IDLE()
{
    static int l_time;
    int n_time = glutGet(GLUT_ELAPSED_TIME);

    if(l_time > 0)
    {
        float time_delta = (n_time - l_time) / 100.0f;




    }

    l_time = n_time;

    glutPostRedisplay();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.1f,0.4f,1.4f,0.3f);

    Map();
    tree();
    tree1();
    tree2();
    tree3();
    grass();
    grass1();
    grass2();
    grass3();
    glFlush();


    Czasteczki_Ogien();
    SmokeP();

    shader.Light();

    glutSwapBuffers();



}
void Reshape( int szerokosc, int wysokosc )

{
    glViewport(0, 0, szerokosc, wysokosc);

    shader.matrix_vision = glm::lookAt(cam, c_cam, r_cam);
    shader.matrix_show = glm::perspective<float>(glm::radians(60.0f), (float)szerokosc / (float)wysokosc, 0.2f, 1001.0f);
}




void Sterowanie( unsigned char key, int x, int y )
{

    if( key == 'w' )
        cam = glm::rotate(cam,-0.05f,glm::vec3(0.0f,0.0f,1.0f));

    if( key == 's' )
        cam = glm::rotate(cam,0.05f,glm::vec3(0.0f,0.0f,1.0f));

    if( key == 'a' )
        cam = glm::rotate(cam,-0.05f,glm::vec3(0.0f,1.0f,0.0f));

    if( key == 'd' )
        cam = glm::rotate(cam,0.05f,glm::vec3(0.0f,1.0f,0.0f));

    if(key == 'q')
    {
        exit(0);
    }



    Reshape( glutGet( GLUT_WINDOW_WIDTH ), glutGet( GLUT_WINDOW_HEIGHT ) );
}
int main(int argc, char *argv[])
{





    PsOgien.InitParticles_sys(Ilosc_Czasteczek_Ogien,Ogien_Pozycja());

    SmokePs.InitParticles_sys(Ilosc_Czasteczek_Ogien,SmokePosition());

    srand(time(NULL));

    glutInit( & argc, argv );
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
    glutInitWindowSize( 800, 600 );
    glutCreateWindow( "OGNISKO");
    glewInit();
    glEnable(GL_DEPTH_TEST);


    shader.Init_shader("shader.vert","shader.frag");

    stbi_set_flip_vertically_on_load(true);



    map.Object_Init("obiekty/mapa.obj","obiekty/mapa.tga");
    tree_model.Object_Init("obiekty/tree.obj","obiekty/tree.tga");
    grass_model.Object_Init("obiekty/grass.obj","obiekty/grass.tga");
    Smoke.Object_Init("obiekty/czasteczka.obj");

    Ogien.Object_Init("obiekty/czasteczka.obj");
    glutDisplayFunc(Display);
    glutReshapeFunc(Reshape);
    glutIdleFunc(F_IDLE);
    glutKeyboardFunc(Sterowanie);

    glutMainLoop();

    return(0);
}
