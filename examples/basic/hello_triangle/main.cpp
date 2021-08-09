
#include <ct/ct.hpp>
#include <ct/platform/platform.hpp>
#include <ct/platform/render_window.hpp>
#include <glad/glad.h>


ct::Logger logger;

typedef struct {
	GLuint vao;
	GLuint ibo;
	GLuint vertices_vbo;
	GLuint color_vbo;
} TriangleMesh;

bool check_shader_compilation(GLuint shader) {
	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(shader, 1024, NULL, infoLog);
		logger.log("SHADER::COMPILATION_FAILED:\n", infoLog);
		return false;
	}
	return true;
}

GLuint init_shaders() {
	/* these are the strings of code for the shaders
	the vertex shader positions each vertex point */
	const char * vertex_shader = "#version 330\n"
	                             ""
	                             "layout (location = 0) in vec3 in_pos;"
	                             "layout (location = 1) in vec3 in_col;"
	                             ""
	                             "out vec3 out_color;"
	                             ""
	                             "void main () {"
	                             "  out_color = in_col;"
	                             "  gl_Position = vec4(in_pos, 1.0);"
	                             "}\0";

	/* the fragment shader colours each fragment (pixel-sized area of the
	triangle) */
	const char * fragment_shader = "#version 330\n"
	                               ""
	                               "in vec3 out_color;"
	                               ""
	                               "out vec4 frag_color;"
	                               "void main () {"
	                               "  frag_color = vec4(out_color, 1.0);"
	                               "}\0";

	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, NULL);
	glCompileShader(vs);
	if (!check_shader_compilation(vs)) {
		return -1;
	}

	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, NULL);
	glCompileShader(fs);
	if (!check_shader_compilation(vs)) {
		return -1;
	}

	GLuint shader_program = glCreateProgram();
	glAttachShader(shader_program, fs);
	glAttachShader(shader_program, vs);
	glLinkProgram(shader_program);

	// Delete shader objects if we no longer need them anymore
	// glDeleteShader(vs);
	// glDeleteShader(fs);

	return shader_program;
}

TriangleMesh create_triangle(GLuint shader_program) {
	GLuint vao = 0;
	GLuint ibo;
	GLuint color_vbo;
	GLuint vertices_vbo;
	GLuint indices[] = {0, 1, 2};

	// position vertex buffer - geometry to use
	// 3 xyz points (9 GLfloat total) and this will make our triangle
	GLfloat vertices[] = {
	    -0.5f,
	    -0.5f,
	    0.0f, // left
	    0.5f,
	    -0.5f,
	    0.0f, // right
	    0.0f,
	    0.5f,
	    0.0f // top
	};
	// color vertex buffer
	GLfloat colors[] = {1.0f,
	                    0.0f,
	                    0.0f, // red
	                    0.0f,
	                    1.0f,
	                    0.0f, // green
	                    0.0f,
	                    0.0f,
	                    1.0f}; // blue

	// vertex array object (VAO)
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/////////////////////////////////
	// vertex buffer object (VBO)
	// store array of data in GPU memory
	// binds VBO to VAO
	glGenBuffers(1, &vertices_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &color_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(GLfloat), colors, GL_STATIC_DRAW);

	/////////////////////////////////
	// index buffer data (IBO/EBO)
	glGenBuffers(1, &ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(indices), indices, GL_STATIC_DRAW);

	/////////////////////////////////
	// bind VBOs to VAO
	glBindBuffer(GL_ARRAY_BUFFER, vertices_vbo);
	GLint position_attr = glGetAttribLocation(shader_program, "in_pos");
	glVertexAttribPointer(position_attr, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(position_attr);

	glBindBuffer(GL_ARRAY_BUFFER, color_vbo);
	GLint col_attr = glGetAttribLocation(shader_program, "in_col");
	glVertexAttribPointer(col_attr, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void *)0);
	glEnableVertexAttribArray(col_attr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return TriangleMesh {vao, ibo, vertices_vbo, color_vbo};
}

int main(int argc, char const * argv[]) {
	if (!ct::Platform::init()) {
		logger.log("Could not initialize Platform module");
		return 1;
	}

	logger.log("Opening window...");

	const int width = 480;
	const int height = 360;
	ct::RenderWindow win;
	
	win.create(width, height, "hello triangle");

	// apply current opengl context
	// IMPORTANT: this must be called before gladLoadGLLoader
	win.make_current();

	// init glad
	if (!gladLoadGLLoader((GLADloadproc)ct::Platform::get_proc_address)) {
		logger.log("Failed to initialize glad");
		return 1;
	};

	logger.log("OpenGL version:", glGetString(GL_VERSION));

	// enable depth testing
	glEnable(GL_DEPTH_TEST);

	// init our shaders and triangle
	GLuint shader_program = init_shaders();
	TriangleMesh triangle = create_triangle(shader_program);

	glViewport(0, 0, width, height);

	win.set_visible(true);

	while (win.is_visible()) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

		glUseProgram(shader_program);
		glBindVertexArray(triangle.vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		ct::Platform::poll_events();

		win.swap_buffers();
	}


	if (!ct::Platform::terminate()) {
		logger.log("Terminating with error.");
		return 1;
	}

	return 0;
}
