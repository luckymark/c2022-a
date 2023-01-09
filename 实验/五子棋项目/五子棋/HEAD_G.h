#ifndef _HEAD_G
#define _HEAD_G

#include"HEAD.h"
extern GLuint rendering_program;

extern GLuint vs[2];
extern GLuint tcs;
extern GLuint tes;
extern GLuint gs;
extern GLuint fs[2];
extern GLuint rendering_program1;//管线1，渲染棋盘
extern GLuint rendering_program2;//管线2，渲染棋子
extern GLuint vertex_array_object;
void compile_shader(void);
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);
int running(int running_mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void startup();
void render(double currentTime,GLFWwindow* window,int running_mode);
void shutdown();
#endif