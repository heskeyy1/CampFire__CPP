#include <iostream>
#include <GL/glext.h>
#include <GL/glut.h>
#include <GL/glew.h>
#include <vector>
#define STB_IMAGE_IMPLEMENTATION

#include "Loader_img.h"
#include "Loader_obj.h"

using namespace std;

class Obiekt
{
public:
    GLuint Vao_Object;
    GLuint Object_texture;
    glm::mat4 Matrix_mod;
    vector<unsigned int> indeksy;

public:
    void Object_Init(string obj_path,string texture_path = "")
    {
        int szerokosc, wysokosc, Channel_num;
		vector<float> Pozycje;
        vector<float> Cord_texture;
        vector<float> Normal;
        objl::Loader wierzcholki;

        //wierzcholki
        wierzcholki.LoadFile(obj_path);

        for (int i = 0; i < wierzcholki.LoadedMeshes.size(); i++)
        {
            objl::Mesh mesh = wierzcholki.LoadedMeshes[i];

            for (int j = 0; j < mesh.Vertices.size(); j++)
            {

				Normal.push_back(mesh.Vertices[j].Normal.X);
                Normal.push_back(mesh.Vertices[j].Normal.Y);
                Normal.push_back(mesh.Vertices[j].Normal.Z);

                Pozycje.push_back(mesh.Vertices[j].Position.X);
                Pozycje.push_back(mesh.Vertices[j].Position.Y);
                Pozycje.push_back(mesh.Vertices[j].Position.Z);



                Cord_texture.push_back(mesh.Vertices[j].TextureCoordinate.X);
                Cord_texture.push_back(mesh.Vertices[j].TextureCoordinate.Y);
            }

            for (int k = 0; k < mesh.Indices.size(); k++)
            {
                indeksy.push_back(mesh.Indices[k]);
            }
        }

        // Wygenerowanie Vao_Object dla szescianu:
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Pozycje.size(), Pozycje.data(), GL_STATIC_DRAW);
        // Analogiczny bufor z normalnymi:
        GLuint nbo = 0;
        glGenBuffers(1, &nbo);
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Normal.size(), Normal.data(), GL_STATIC_DRAW);
        // Analogiczny bufor ze wspólrzednymi tekstur:
        GLuint tbo = 0;
        glGenBuffers(1, &tbo);
        glBindBuffer(GL_ARRAY_BUFFER, tbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Cord_texture.size(), Cord_texture.data(), GL_STATIC_DRAW);

        // Zaladowanie tekstury:
        if(texture_path != "")
        {
            glGenTextures(1, &this->Object_texture);
            glBindTexture(GL_TEXTURE_2D,this->Object_texture);

            unsigned char *data = stbi_load(texture_path.c_str(), &szerokosc, &wysokosc, &Channel_num, 0);

            if (data)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, szerokosc, wysokosc, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
                glGenerateMipmap(GL_TEXTURE_2D);

                glPixelStorei(GL_UNPACK_ALIGNMENT, 4);



                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            else
            {
                cout << "Blad w ladowaniu tekstury" << endl;
            }

            stbi_image_free(data);
        }

        // Przygotowanie Vao_Object:
        glGenVertexArrays(1, &this->Vao_Object);
        glBindVertexArray(this->Vao_Object);
        // Index 0 -> wierzcholki:
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        // Index 1 -> normalne:
        glBindBuffer(GL_ARRAY_BUFFER, nbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        // Index 2 -> Wspólrzedne tekstury:
        if(texture_path != "")
        {
            glBindBuffer(GL_ARRAY_BUFFER, tbo);
            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
            glEnableVertexAttribArray(2);
        }

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        this->Matrix_mod = glm::mat4(1.0f);
    }

    void Wyswietlanie_Obiektu()
    {
        if(this->Object_texture != 0)
        {
            glBindTexture(GL_TEXTURE_2D, this->Object_texture);
        }

        glBindVertexArray(this->Vao_Object);
        glDrawElements(GL_TRIANGLES, this->indeksy.size(), GL_UNSIGNED_INT, this->indeksy.data());
    }
};
