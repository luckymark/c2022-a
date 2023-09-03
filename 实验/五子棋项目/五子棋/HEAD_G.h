//graphic.cpp头文件
#ifndef _HEAD_G
#define _HEAD_G

#include"HEAD.h"
int running(int running_mode);//五子棋运行程序，running_mode为游戏模式，1为双人，2为人机
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);//光标位置回调函数，参数：窗口,光标x坐标，光标y坐标
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);//鼠标回调函数，参数：窗口，当前操作键，操作行为，操作状态
void board_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods);//键盘回调函数，参数：窗口，当前操作键，操作行为，操作状态
void delete_shader(void);//删除着色器
void compile_shader(void);//编译着色器程序
GLuint linkprogram1();//棋盘渲染管线链接函数
GLuint linkprogram2();//棋子渲染管线链接函数
void startup();//渲染循环前处理函数
void render(GLFWwindow* window,int running_mode);//渲染循环中处理函数
void shutdown(GLFWwindow* window);//渲染循环后处理函数
#endif