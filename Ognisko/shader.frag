#version 400
// Natężenie składowej diffuse i ambient:
const vec3 Rozproszenie_Swiatla = vec3(0.8, 0.8, 0.8);
const vec3 Swiatlo_Otoczenia = vec3(0.2, 0.2, 0.2);
// Współczynnik rozbłysków materiału:
const vec3 MatSpecular = vec3(0.4, 0.4, 0.4);
const int MatShininess = 24;

// Stały wektor "patrzenia" obserwatora wzdłuż osi Z:
const vec3 lookvec = vec3(0, 0, 1);
// Położenie źródła światła - dane przekazane z aplikacji:
uniform vec3 LightPos;

// Interpolowany wektor normalny:
in vec3 normal;
// Interpolowana współrzędna tekstury:
in vec2 tex_coord;



// Wynikowy kolor piksela (fragmentu):
out vec4 frag_colour;
// Sampler dla tekstury:
uniform sampler2D Tex0;

// kolor
uniform vec4 Kolor_Czasteczki;


float rand(float n)
{
    return fract(sin(n) * 43758.5453123);
}

void main()
{
    // Wektor padania światła (źródło kierunkowe):
    vec3 lightDir = normalize(LightPos);
    // Normalizacja interpolowanej normalnej:
    vec3 n = normalize(normal);

    // Jasność (diffuse):
    float jasnosc = max( dot(lightDir, n), 0.0 );

    // Model oświetlenia Blinna-Phonga:
    vec3 HV = vec3( normalize(lightDir + lookvec) );
    float NdotHV = max(dot(n, HV), 0.0);
    float spec = pow(NdotHV, MatShininess);

    // Teksel tekstury:
    vec4 texel = texture2D(Tex0, tex_coord);

    vec4 p_color;

    //kolorowanie
    if(Kolor_Czasteczki != vec4(0)) //
    {
        p_color = Kolor_Czasteczki;
    }
    else
    {
        // Kolor wynikowy z teksturą (bez rozbłysków):
        p_color = texel * vec4(jasnosc * Rozproszenie_Swiatla + Swiatlo_Otoczenia, 1.2);
    }

    // Rozbłyski lub nie:
    if(jasnosc > 0.0 && spec > 0.0)
        frag_colour = clamp(p_color + spec * vec4(MatSpecular, 1.1), 0.0, 1.1);
    else	frag_colour = clamp(p_color, 0.0, 1.1);
}
