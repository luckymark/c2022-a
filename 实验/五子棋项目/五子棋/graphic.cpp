//程序图形部分代码
#include"HEAD.h"
#include"HEAD_G.h"
GLuint vs[2] = { 0 };
GLuint tcs = 0;
GLuint tes = 0;
GLuint gs = 0;
GLuint fs[2] = { 0 };
GLuint rendering_program1;//管线1，渲染棋盘
GLuint rendering_program2;//管线2，渲染棋子
GLuint vertex_array_object;
chess_pos chess_pos_cursor = { 0,0 };//最新落子坐标
double fallbacktime=0;
int running(int running_mode)
{
	//glfw库调用
	//glfw初始化
	glfwInit();
	//主副版本号确认
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//使用OpenGL核心扩展
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//限制窗口缩放
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//窗口对象，前三参数分别为窗口宽、高、窗口名
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "wuziqi", nullptr, nullptr);
	if (window == nullptr) {
		std::cout << "Failed to create GLFW window" << std::endl;
		return -1;
	}
	//绑定当前运行窗口
	glfwMakeContextCurrent(window);
	//glewExperimental为glew和glfw库核心扩展对应的参数
	glewExperimental = GL_TRUE;
	//glew初始化
	if (glewInit() != GLEW_OK) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	int win_width = windowWidth;
	int win_hight = windowHeight;
	//以下为对窗口、视口的设置，暂时还没有搞懂
	glfwGetFramebufferSize(window, &win_width, &win_hight);
	glViewport(0, 0, win_width, win_hight);
	//设置光标回调函数和鼠标回调函数
	glfwSetCursorPosCallback(window, mouse_pos_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetKeyCallback(window, board_button_callback);
	//进行渲染循环前处理
	startup();
	//渲染循环
	while (!glfwWindowShouldClose(window)) {
		render(window,running_mode);
		wincheck(chess_draw_list[count - 1]);
		if (isWin) {
			break;
		}
	}
	//进行渲染循环后处理
	shutdown(window);
	//结束glfw库调用
	glfwTerminate();
	return 0;
}
void board_button_callback(GLFWwindow* window,int key,int scancode,int action,int mods) {
		if (key == GLFW_KEY_R && action == GLFW_PRESS) {
			if (glfwGetTime() -fallbacktime > 0.25)
			{
				if (gamemode == 2)
				{
					fallbacktime = glfwGetTime();
				}

				switch (gamemode)
				{
				case 1:
					if (count - 1 >= 0)
					{
						chessmap[chess_draw_list[count - 1][1] - 1][chess_draw_list[count - 1][2] - 1].chesskind = EMPTY;
						count -= 1;
					}
					break;
				case 2:
					if (count - 2 >= 0)
					{
						chessmap[chess_draw_list[count - 1][1] - 1][chess_draw_list[count - 1][2] - 1].chesskind = EMPTY;
						chessmap[chess_draw_list[count - 2][1] - 1][chess_draw_list[count - 2][2] - 1].chesskind = EMPTY;
						count -= 2;
					}
					break;
				default:
					break;
				}
			}
		}
}
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos) {
	//实时将点击鼠标时距离光标坐标最近的落子点坐标传给全局变量chess_pos_cursor
	int current_xpos = xpos / (windowWidth / 16);//current_xpos为0~16的数字，代表光标在棋盘的x坐标
	double ex_current_xpos = xpos / (windowWidth / 16.0f);//ex_current_xpos为0~16度量轴下光标x坐标的精确值
	if (ex_current_xpos - current_xpos > 0.5)
		current_xpos++;
	int current_ypos = ypos / (windowHeight / 16);
	double ex_current_ypos = ypos / (windowHeight / 16.0f);
	if (ex_current_ypos - current_ypos > 0.5)
		current_ypos++;
	if (current_xpos > 0 && current_xpos < 16)//只取1~15为有效输入
		chess_pos_cursor.xpos = current_xpos;
	else
		chess_pos_cursor.xpos = -1;
	if (current_ypos > 0 && current_ypos < 16)
		chess_pos_cursor.ypos = current_ypos;
	else
		chess_pos_cursor.ypos = -1;
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		//鼠标点击时，将全局变量chess_pos_cursor传入棋子渲染序列，视为完成落子
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
					//更新落子手数，完成落子
					count++;
					//更新AI演算区域
					if (chess_pos_cursor.xpos - 1 < AI_ThinkWidth[2] + 2) {
						AI_ThinkWidth[2] = chess_pos_cursor.xpos - 3;
						if (AI_ThinkWidth[2] < 0)
						{
							AI_ThinkWidth[2] = 0;
						}
					}
					if (chess_pos_cursor.xpos - 1 > AI_ThinkWidth[3] - 2) {
						AI_ThinkWidth[3] = chess_pos_cursor.xpos + 1;
						if (AI_ThinkWidth[3] > 14)
						{
							AI_ThinkWidth[3] = 14;
						}
					}
					if (chess_pos_cursor.ypos - 1 < AI_ThinkWidth[0] + 2) {
						AI_ThinkWidth[0] = chess_pos_cursor.ypos - 3;
						if (AI_ThinkWidth[0] < 0)
						{
							AI_ThinkWidth[0] = 0;
						}
					}
					if (chess_pos_cursor.ypos - 1 > AI_ThinkWidth[1] - 2) {
						AI_ThinkWidth[1] = chess_pos_cursor.ypos + 1;
						if (AI_ThinkWidth[1] > 14)
						{
							AI_ThinkWidth[1] = 14;
						}
					}
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

	static const GLchar* vertex_shader_source1[] = {//棋盘顶点着色器
		"#version 450 core			\n"
		"void main(void){			\n"
		//向管线中传递四个三维坐标
		"const vec4 vertices[4]=vec4[4](vec4(1.0,1.0,0.5,1.0),\n"//GLSL中窗口坐标区间为-1~1，前三个参数为xyz，第四个参数与空间中透视相关，渲染平面时不用管
		"								vec4(1.0,-1.0,0.5,1.0),\n"
		"								vec4(-1.0,-1.0,0.5,1.0),\n"
		"								vec4(-1.0,1.0,0.5,1.0));\n"
		"gl_Position=vertices[gl_VertexID];\n"
		"}\n"
	};
	static const GLchar* vertex_shader_source2[] = {//棋子顶点着色器
		"#version 450 core\n"
		"layout(location = 0)in vec4 onechess;\n"//onechess为当前渲染棋子，成员变量x,y,z依次为棋子颜色，x坐标，y坐标（1~15的坐标通过坐标变换，变为渲染坐标系下-1~1的坐标）
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

	static const GLchar* tess_control_shader_source1[] = {//棋盘曲面细分着色器控制部分
		"#version 450 core\n"
		"layout(vertices=4) out;\n"//细分为4边形
		"void main(void){\n"
		"if(gl_InvocationID==0){\n"
		"	gl_TessLevelInner[0]=16.0;\n"//根据顶点着色器传来的4点，从任何方向均细分为16分，最终得到16*16的方格阵，后续将除去外1圈，剩余部分作为棋盘
		"	gl_TessLevelInner[1]=16.0;\n"
		"	gl_TessLevelOuter[0]=16.0;\n"
		"	gl_TessLevelOuter[1]=16.0;\n"
		"	gl_TessLevelOuter[2]=16.0;\n"
		"	gl_TessLevelOuter[3]=16.0;\n"
		"}\n"
		"gl_out[gl_InvocationID].gl_Position=gl_in[gl_InvocationID].gl_Position;\n"
		"}\n"
	};

	static const GLchar* tess_evaluate_shader_source1[] = {//棋盘曲面细分着色器评估部分，暂时没弄明白
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

	static const GLchar* geometry_shader_source1[]{//棋盘几何着色器，根据细分着色器传来的点画线，形成棋盘
		"#version 450 core\n"
		"layout(triangles)in;\n"//细分着色器后存在于管线中的是三角形数据，不通过画线，直接正常渲染的话不能得到方格
		"layout(line_strip,max_vertices=8)out;\n"
		"void main(void){\n"
		//以下四个if监测是否到达棋盘边缘，进而避免将线画出棋盘
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

	static const GLchar* fragment_shader_source1[]{//棋盘片元着色器
		"#version 450 core\n"
		"out vec4 color;\n"
		"void main(void){\n"
		"color=vec4(0.9,0.9,0.8,1.0);\n"
		"}\n"
	};
	static const GLchar* fragment_shader_source2[] = {//棋子片元着色器
		"#version 450 core\n"
		"in vec4 vs_color;\n"
		"out vec4 color;\n"
		"void main(void) {\n"
		"	color = vs_color;\n"
		"}\n"
	};
	//创建着色器
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
	//完成着色器准备工作
	compile_shader();
	rendering_program1 = linkprogram1();
	rendering_program2 = linkprogram2();
	//生成绑定顶点数组
	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);
	//glPatchParameteri中将参数设置为4，进而能在细分着色器中进行四边形细分
	glPatchParameteri(GL_PATCH_VERTICES, 4);
	//设置绘制线宽、像素点大小，以像素点作为棋子
	glLineWidth(6.0);
	glPointSize(80.0);
}
void render(GLFWwindow* window,int running_mode) {
	//设置渲染背景色
	static const GLfloat black[]{ 0.2f,0.3f,0.4f,1.0f };
	glClearBufferfv(GL_COLOR, 0, black);
	//绘制棋盘
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glUseProgram(rendering_program1);
	glDrawArrays(GL_PATCHES, 0, 4);
	//根据棋子渲染序列依次绘制棋子
	if (count) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		glUseProgram(rendering_program2);
		for (int i = 0; i < count; i++)
		{
			GLfloat onechess[4] = { chess_draw_list[i][0],chess_draw_list[i][1],chess_draw_list[i][2],1.0f };
			glVertexAttrib4fv(0, onechess);
			glDrawArrays(GL_POINTS, 0, 1);
		}
		//绘制上一落子标识
		glPointSize(38.0);
		GLfloat chessflag[4] = { abs(chess_draw_list[count - 1][0] / 2 - 2),chess_draw_list[count-1][1]+0.25,chess_draw_list[count-1][2] - 0.25,1.0f };
		glVertexAttrib4fv(0, chessflag);
		glDrawArrays(GL_POINTS, 0, 1);
		glPointSize(80.0);
	}
	glfwSwapBuffers(window);
	//在双人模式中，以及人机模式人落子阶段识别落子，在人机模式AI落子阶段完成评估并落子
	if (running_mode==1||(count % 2)==(gamer_color-1)) {
		glfwPollEvents();
	}
	else {
		AI_Running();
	}
}
void shutdown(GLFWwindow* window) {
	if (isWin)
	{
		static const GLfloat blackwin[]{ 0.1f,0.2f,0.3f,1.0f };
		static const GLfloat whitewin[]{ 0.3f,0.4f,0.5f,1.0f };
		if (count % 2)
		{
			glClearBufferfv(GL_COLOR, 0, blackwin);
		}
		else {
			glClearBufferfv(GL_COLOR, 0, whitewin);
		}

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
			glPointSize(38.0);
			GLfloat chessflag[4] = { abs(chess_draw_list[count - 1][0] / 2 - 2),chess_draw_list[count - 1][1] + 0.25,chess_draw_list[count - 1][2] - 0.25,1.0f };
			glVertexAttrib4fv(0, chessflag);
			glDrawArrays(GL_POINTS, 0, 1);
			glPointSize(80.0);
		}
		glfwSwapBuffers(window);
		if (count % 2)
		{
			MessageBox(0, TEXT("黑棋胜利"), TEXT("result"), 0);
		}
		else {
			MessageBox(0, TEXT("白棋胜利"), TEXT("result"), 0);
		}
	}
	//删除着色器、管线、顶点数组
	delete_shader();
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program1);
	glDeleteVertexArrays(1, &vertex_array_object);
}