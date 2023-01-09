#include"HEAD.h"
#include"HEAD_G.h"
GLuint rendering_program;

GLuint vs[2] = { 0 };
GLuint tcs = 0;
GLuint tes = 0;
GLuint gs = 0;
GLuint fs[2] = { 0 };
GLuint rendering_program1;//管线1，渲染棋盘
GLuint rendering_program2;//管线2，渲染棋子
GLuint vertex_array_object;
int running(int running_mode)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "Learning2", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int win_width = windowWidth;
	int win_hight = windowHeight;
	glfwGetFramebufferSize(window, &win_width, &win_hight);
	glViewport(0, 0, win_width, win_hight);
	glfwSetCursorPosCallback(window, mouse_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	startup();

	while (!glfwWindowShouldClose(window)) {
		double timeValue = glfwGetTime();
		render(timeValue,window,running_mode);
		winchack(chess_draw_list[count - 1]);
		if (isWin) {
			return 0;
		}
	}

	shutdown();
	glfwTerminate();
	return 0;
}
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	int current_xpos = xpos / (windowWidth / 16);
	double ex_current_xpos = xpos / (windowWidth / 16.0f);
	if (ex_current_xpos - current_xpos > 0.5)
		current_xpos++;
	int current_ypos = ypos / (windowHeight / 16);
	double ex_current_ypos = ypos / (windowHeight / 16.0f);
	if (ex_current_ypos - current_ypos > 0.5)
		current_ypos++;
	if (current_xpos > 0 && current_xpos < 16)
		chess_pos_cursor.xpos = current_xpos;
	else
		chess_pos_cursor.xpos = -1;
	if (current_ypos > 0 && current_ypos < 16)
		chess_pos_cursor.ypos = current_ypos;
	else
		chess_pos_cursor.ypos = -1;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		if (chess_pos_cursor.xpos != -1 && chess_pos_cursor.ypos != -1) {
			if (chessmap[chess_pos_cursor.xpos - 1][chess_pos_cursor.ypos - 1].chesskind == EMPTY) {
				if (count % 2) {
					chessmap[chess_pos_cursor.xpos - 1][chess_pos_cursor.ypos - 1].chesskind = WHITE;
					chess_draw_list[count][0] = WHITE;
					chess_draw_list[count][1] = chess_pos_cursor.xpos;
					chess_draw_list[count][2] = chess_pos_cursor.ypos;
				}
				else {
					chessmap[chess_pos_cursor.xpos - 1][chess_pos_cursor.ypos - 1].chesskind = BLACK;
					chess_draw_list[count][0] = BLACK;
					chess_draw_list[count][1] = chess_pos_cursor.xpos;
					chess_draw_list[count][2] = chess_pos_cursor.ypos;
				}
				if (chess_pos_cursor.xpos - 1 < AI_ThinkWidth[2]) {
					AI_ThinkWidth[2] = chess_pos_cursor.xpos - 3;
					if (AI_ThinkWidth[2]<0)
					{
						AI_ThinkWidth[2] = 0;
					}
				}
				if (chess_pos_cursor.xpos - 1 > AI_ThinkWidth[3]) {
					AI_ThinkWidth[3] = chess_pos_cursor.xpos + 1;
					if (AI_ThinkWidth[3]>14)
					{
						AI_ThinkWidth[3] = 14;
					}
				}
				if (chess_pos_cursor.ypos - 1 < AI_ThinkWidth[0]) {
					AI_ThinkWidth[0] = chess_pos_cursor.ypos - 3;
					if (AI_ThinkWidth[0]<0)
					{
						AI_ThinkWidth[0] = 0;
					}
				}
				if (chess_pos_cursor.ypos - 1 > AI_ThinkWidth[1]) {
					AI_ThinkWidth[1] = chess_pos_cursor.ypos + 1;
					if (AI_ThinkWidth[1]>14)
					{
						AI_ThinkWidth[1] = 14;
					}
				}
				count++;
			}
		}
	}
}
void delete_shader(void) {
	int i = 0;
	for (i = 0; i < 3; i++)
	{
		if (vs[i] != 0)
			glDeleteShader(vs[i]);

		glDeleteShader(tcs);
		glDeleteShader(tes);
		glDeleteShader(gs);
		if (fs[i] != 0)
			glDeleteShader(fs[i]);
	}
	return;
}
void compile_shader(void) {

	static const GLchar* vertex_shader_source1[] = {
		"#version 450 core			\n"
		"void main(void){			\n"
		"const vec4 vertices[4]=vec4[4](vec4(1.0,1.0,0.5,1.0),\n"
		"								vec4(1.0,-1.0,0.5,1.0),\n"
		"								vec4(-1.0,-1.0,0.5,1.0),\n"
		"								vec4(-1.0,1.0,0.5,1.0));\n"
		"gl_Position=vertices[gl_VertexID];\n"
		"}\n"
	};
	static const GLchar* vertex_shader_source2[] = {
		"#version 450 core\n"
		"layout(location = 0)in vec4 onechess;\n"
		"out vec4 vs_color;\n"
		"void main(void) {\n"
		"	vec4 vs_pos = vec4((onechess.y-8)/8, (onechess.z-8)/-8, 0.0, 1.0);\n"
		"	vec4 color;"
		"	if (onechess.x == 1) {\n"
		"		color = vec4(1.0, 1.0, 1.0, 1.0);\n"
		"	}\n"
		"else{\n"
		"		color = vec4(0.0, 0.0, 0.0, 1.0);\n"
		"}\n"
		"	gl_Position=vs_pos;\n"
		"	vs_color = color;\n"
		"}\n"
	};

	static const GLchar* tess_control_shader_source1[] = {
		"#version 450 core\n"
		"layout(vertices=4) out;\n"
		"void main(void){\n"
		"if(gl_InvocationID==0){\n"
		"	gl_TessLevelInner[0]=16.0;\n"
		"	gl_TessLevelInner[1]=16.0;\n"
		"	gl_TessLevelOuter[0]=16.0;\n"
		"	gl_TessLevelOuter[1]=16.0;\n"
		"	gl_TessLevelOuter[2]=16.0;\n"
		"	gl_TessLevelOuter[3]=16.0;\n"
		"}\n"
		"gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;\n"
		"}\n"
	};

	static const GLchar* tess_evaluate_shader_source1[] = {
		"#version 450 core\n"
		"layout(quads,equal_spacing,ccw)in;"
		"void main(void){\n"
		"float u=gl_TessCoord.x;\n"
		"float v=gl_TessCoord.y;\n"
		"float omu=1-u;\n"
		"float omv=1-v;\n"
		"gl_Position=\n"
		"omu*omv*gl_in[0].gl_Position+\n"
		"u*omv*gl_in[1].gl_Position+\n"
		"u*v*gl_in[2].gl_Position+\n"
		"omu*v*gl_in[3].gl_Position;\n"
		"}\n"
	};

	static const GLchar* geometry_shader_source1[]{
		"#version 450 core\n"
		"layout(triangles)in;\n"
		"layout(line_strip,max_vertices=8)out;\n"
		"void main(void){\n"
		"if(gl_in[0].gl_Position.x<0.5){\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position+vec4(0.2,0.0,0.0,0.0);EmitVertex();\n"
		"}else{\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"}\n"
		"if(gl_in[0].gl_Position.x>-0.5){\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position+vec4(-0.2,0.0,0.0,0.0);EmitVertex();\n"
		"}else{\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"}\n"
		"if(gl_in[0].gl_Position.y<0.5){\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position+vec4(0.0,0.2,0.0,0.0);EmitVertex();\n"
		"}else{\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"}\n"
		"if(gl_in[0].gl_Position.y>-0.5){\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position+vec4(0.0,-0.2,0.0,0.0);EmitVertex();\n"
		"}else{\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"gl_Position=gl_in[0].gl_Position;EmitVertex();\n"
		"}\n"
		"}\n"
	};

	static const GLchar* fragment_shader_source1[]{
		"#version 450 core\n"
		"out vec4 color;\n"
		"void main(void){\n"
		"color=vec4(0.9,0.9,0.8,1.0);\n"
		"}\n"
	};
	static const GLchar* fragment_shader_source2[] = {
		"#version 450 core\n"
		"in vec4 vs_color;\n"
		"out vec4 color;\n"
		"void main(void) {\n"
		"	color = vs_color;\n"
		"}\n"
	};
	vs[0] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs[0], 1, vertex_shader_source1, NULL);
	glCompileShader(vs[0]);

	vs[1] = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs[1], 1, vertex_shader_source2, NULL);
	glCompileShader(vs[1]);

	tcs = glCreateShader(GL_TESS_CONTROL_SHADER);
	glShaderSource(tcs, 1, tess_control_shader_source1, NULL);
	glCompileShader(tcs);

	tes = glCreateShader(GL_TESS_EVALUATION_SHADER);
	glShaderSource(tes, 1, tess_evaluate_shader_source1, NULL);
	glCompileShader(tes);

	gs = glCreateShader(GL_GEOMETRY_SHADER);
	glShaderSource(gs, 1, geometry_shader_source1, NULL);
	glCompileShader(gs);

	fs[0] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs[0], 1, fragment_shader_source1, NULL);
	glCompileShader(fs[0]);
	fs[1] = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs[1], 1, fragment_shader_source2, NULL);
	glCompileShader(fs[1]);
	return;
}
GLuint linkprogram1() {
	GLuint program = glCreateProgram();
	glAttachShader(program, vs[0]);
	glAttachShader(program, tcs);
	glAttachShader(program, tes);
	glAttachShader(program, gs);
	glAttachShader(program, fs[0]);
	glLinkProgram(program);
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar* m_infor = new GLchar[1024];
		glGetProgramInfoLog(program, 1023, NULL, m_infor);
		std::cout << "ERROR_IN: program " << std::endl << "\tError in link program " << program << std::endl;
		std::cout << "ERROR_IN: program " << std::endl << "\terror message : " << std::endl << m_infor << std::endl;
		delete[]m_infor;
		return 0;
	}
	return program;
}
GLuint linkprogram2() {
	GLuint program = glCreateProgram();
	glAttachShader(program, vs[1]);
	glAttachShader(program, fs[1]);
	glLinkProgram(program);
	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar* m_infor = new GLchar[1024];
		glGetProgramInfoLog(program, 1023, NULL, m_infor);
		std::cout << "ERROR_IN: program " << std::endl << "\tError in link program " << program << std::endl;
		std::cout << "ERROR_IN: program " << std::endl << "\terror message : " << std::endl << m_infor << std::endl;
		delete[]m_infor;
		return 0;
	}
	return program;
}
void startup() {
	compile_shader();
	rendering_program1 = linkprogram1();
	rendering_program2 = linkprogram2();
	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	glLineWidth(3.0);
	glPointSize(40.0);
}
void render(double currentTime,GLFWwindow* window,int running_mode) {
	static const GLfloat black[]{ 0.2f,0.3f,0.4f,1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(rendering_program1);
	glDrawArrays(GL_PATCHES, 0, 4);
	if (count) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glUseProgram(rendering_program2);
		for (int i = 0; i < count; i++)
		{
			GLfloat onechess[4] = { chess_draw_list[i][0],chess_draw_list[i][1],chess_draw_list[i][2],1.0f };
			glVertexAttrib4fv(0, onechess);
			glDrawArrays(GL_POINTS, 0, 1);
		}
	}
	glfwSwapBuffers(window);
	if (running_mode==1||!(count % 2)) {
		glfwPollEvents();
	}
	else {
		AI_Running();
	}
}
void shutdown() {
	delete_shader();
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program1);
	glDeleteVertexArrays(1, &vertex_array_object);
}