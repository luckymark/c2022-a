//graphic.cppͷ�ļ�
#ifndef _HEAD_G
#define _HEAD_G

#include"HEAD.h"
int running(int running_mode);//���������г���running_modeΪ��Ϸģʽ��1Ϊ˫�ˣ�2Ϊ�˻�
void mouse_pos_callback(GLFWwindow* window, double xpos, double ypos);//���λ�ûص�����������������,���x���꣬���y����
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);//���ص����������������ڣ���ǰ��������������Ϊ������״̬
void board_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods);//���̻ص����������������ڣ���ǰ��������������Ϊ������״̬
void delete_shader(void);//ɾ����ɫ��
void compile_shader(void);//������ɫ������
GLuint linkprogram1();//������Ⱦ�������Ӻ���
GLuint linkprogram2();//������Ⱦ�������Ӻ���
void startup();//��Ⱦѭ��ǰ������
void render(GLFWwindow* window,int running_mode);//��Ⱦѭ���д�����
void shutdown(GLFWwindow* window);//��Ⱦѭ��������
#endif