#version 400

// Dane wejściowe - współrzędne, normalne i współrzędne tekstury:
layout(location = 0) in vec3 vp;
layout(location = 1) in vec3 vn;
layout(location = 2) in vec2 vt;
// Macierze transformacji i ich iloczyn:
uniform mat4 model_matrix, matrix_vision, mvp_matrix;

out mat4 matrix_vision_translate;
// Wektor normalny do interpolacji:
out vec3 normal;
// Współrzędna tekstury do interpolacji:
out vec2 tex_coord;


void main()
{
	// Przekazanie współrzędnej tekstury:
	tex_coord = vt;
	// Transformacja wektora normalnego:
	normal = (matrix_vision * model_matrix * vec4(vn, 0)).xyz;
	// Transformacja i rzutowanie wierzchołka:
	gl_Position = mvp_matrix * vec4(vp, 1.0);

	matrix_vision_translate = model_matrix;
}
