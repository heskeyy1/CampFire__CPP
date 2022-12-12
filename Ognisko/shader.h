#include <GL/glew.h>
#include <GL/glext.h>
#include <GL/glut.h>


using namespace std;

class Shader
{
public:
    glm::mat4 matrix_vision;
    glm::mat4 matrix_show;
private:
	GLuint Position_light;
	GLuint Matrix_mvp_loc;
	GLuint model_matrix_loc;
    GLuint matrix_vision_loc;
    GLuint Program_shader;


public:
    void Init_shader(string vert_shader_path,string frag_shader_path)
    {
        // Wczytanie kodu shaderów z plików:
        string VertSource = LoadTextFile(vert_shader_path);
        string FragSource = LoadTextFile(frag_shader_path);
        const char* src[1];

        // Inicjalizacja shaderów:
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        src[0] = VertSource.c_str();
        glShaderSource(vs, 1, src, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        src[0] = FragSource.c_str();
        glShaderSource(fs, 1, src, NULL);
        glCompileShader(fs);

        if (!CheckCompileErrors(vs) || !CheckCompileErrors(fs))
        {
            cout << "Shader compile error!" << endl;
            system("pause");
            exit(0);
        }
        // Utworzenie programu i po³¹czenie:
        Program_shader = glCreateProgram();
        glAttachShader(Program_shader, fs);
        glAttachShader(Program_shader, vs);
        glLinkProgram(Program_shader);

        if (!CheckLinkErrors(Program_shader))
        {
            cout << "Shader linking error!" << endl;
            system("pause");
            exit(0);
        }

        glUseProgram(Program_shader);
        // Zapamiêtanie lokalizacji macierzy na póŸniej:
        Matrix_mvp_loc = glGetUniformLocation(Program_shader, "mvp_matrix");
        model_matrix_loc = glGetUniformLocation(Program_shader, "model_matrix");
        matrix_vision_loc = glGetUniformLocation(Program_shader, "matrix_vision");
        // Analogicznie po³o¿enie œwiat³a:
        Position_light = glGetUniformLocation(Program_shader, "LightPos");

        // Ustawienie numeru jednostki teksturujacej dla shadera
        GLuint TLoc = glGetUniformLocation(Program_shader, "Tex0");
        glUniform1f(TLoc, 0);
    }
    void Calculate(glm::mat4 model_matrix,glm::vec4 Kolor_Czasteczki = glm::vec4(0))
    {
        GLint tmp = glGetUniformLocation(Program_shader, "Kolor_Czasteczki");

        // Wyliczenie i przekazanie macierzy:
        glUniformMatrix4fv(this->model_matrix_loc, 1, GL_FALSE, &model_matrix[0][0]);
        glUniformMatrix4fv(this->matrix_vision_loc, 1, GL_FALSE, &this->matrix_vision[0][0]);
        glm::mat4 mvp_matrix = this->matrix_show * this->matrix_vision * model_matrix;
        glUniformMatrix4fv(this->Matrix_mvp_loc, 1, GL_FALSE, &mvp_matrix[0][0]);
        glUniform4f(tmp,Kolor_Czasteczki[0],Kolor_Czasteczki[1],Kolor_Czasteczki[2],Kolor_Czasteczki[3]);
    }

    void Light()
    {
        glm::vec3 light_position = { 0.0f, 0.0f, 100.0f };
        glUniform3fv(this->Position_light, 1, &light_position[0]);
    }
private:
    // Sprawdzenie b³êdów linkowania:
    bool CheckLinkErrors(GLuint prog)
    {
        int res, logLen;
        char buff[1024];

        glGetProgramiv(prog, GL_LINK_STATUS, &res);
        if (res == GL_FALSE)
        {
            cout << "GL_LINK_STATUS ERROR!" << endl;
            glGetProgramInfoLog(prog, 1024, &logLen, buff);
            cout << buff << endl;
            return(false);
        }
        return(true);
    }
    // Sprawdzenie b³êdów kompilacji:
    bool CheckCompileErrors(GLuint shad)
    {
        int res, logLen;
        char buff[1024];

        glGetShaderiv(shad, GL_COMPILE_STATUS, &res);
        if (res == GL_FALSE)
        {
            cout << "GL_COMPILE_STATUS ERROR!" << endl;
            glGetShaderInfoLog(shad, 1024, &logLen, buff);
            cout << buff << endl;
            return(false);
        }
        return(true);
    }

    // Uniwersalna funkcja wczytujaca dane z pliku:
    string LoadTextFile(string fileName)
    {
        ifstream plix;
        plix.open(fileName, ios::in);
        if (!plix.is_open())
        {
            cout << "Open file error: " << fileName << endl;
            system("pause");
            exit(0);
        }
        // Odczyt calosci pliku:
        string line, buff;
        while (!plix.eof())
        {
            getline(plix, line);
            buff += line + "\n";
        }
        return(buff);
    }
};


