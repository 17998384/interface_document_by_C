#define _CRT_SECURE_NO_WARNINGS
#include "interface_document.h"
#define ONE "----\n"
#define TWO "---\n"
#define THREE "--\n"
#define FOUR ":\n"
#define FIVE "\n"

//�����ӿ���
InterfaceBody* build_interface_body(char* interface_body_str);

//��������object
Object* build_object(char* object_str);

//����objet_param
ObjectParam* build_object_param(char* object_param_str);

InterfaceBody** parse_interface_body(char* source, int interface_size)
{
	//��ȡ�ļ�
	String* str = read_file(source);
	//����ռ�
	InterfaceBody** inter_face_bodys = (InterfaceBody**)malloc(sizeof(InterfaceBody) * interface_size);
	check_memory(inter_face_bodys);
	//�ָ���ӿ����ַ���
	char* interface_body_str = strtok(str->buffer, "----\n");
	char* next_interface_body_str;
	int index = 0;
	//ѭ������
	while (interface_body_str)
	{
		next_interface_body_str = strtok(NULL, "----\n");
		inter_face_bodys[index++] = build_interface_body(interface_body_str);
		if (next_interface_body_str == NULL)
		{
			break;
		}
		interface_body_str = strtok(next_interface_body_str, ONE);
	}
	return inter_face_bodys;
}

InterfaceHead** parse_interface_head(char* source, int interface_size)
{
	//��ȡ�ļ�
	String* str = read_file(source);
	return NULL;
}

InterfaceBody* build_interface_body(char* interface_body_str)
{
	//��ȡ��������ַ���
	char* request_object_str = strtok(interface_body_str, TWO);
	//��ȡ��Ӧ�����ַ���
	char* response_object_str = strtok(NULL, TWO);
	//����interface_body
	InterfaceBody* interface_body = (InterfaceBody*)malloc(sizeof(InterfaceBody));
	check_memory(interface_body);
	//��ȡ��������С
	interface_body->request_object_size = get_object_num(request_object_str, THREE);
	//��ȡ��Ӧ�����С
	interface_body->response_object_size = get_object_num(response_object_str, THREE);
	Object** request_objects = interface_body->request_objects;
	Object** response_objects = interface_body->response_objects;
	//��ʼ����������Ӧ����ָ��
	request_objects = (Object**)malloc(sizeof(Object*) * interface_body->request_object_size);
	response_objects = (Object**)malloc(sizeof(Object*) * interface_body->response_object_size);
	//�����������
	request_object_str = strtok(request_object_str, THREE);
	char* next_request_object_str;
	int index = 0;
	while (request_object_str)
	{
		next_request_object_str = strtok(NULL, THREE);
		request_objects[index++] = build_object(request_object_str);
		if (next_request_object_str == NULL)
		{
			break;
		}
		request_object_str = strtok(next_request_object_str, THREE);
	}
	//������Ӧ����
	response_object_str = strtok(response_object_str, THREE);
	char* next_response_object_str;
	index = 0;
	while (response_object_str)
	{
		next_response_object_str = strtok(NULL, THREE);
		response_objects[index++] = build_object(response_object_str);
		if (next_response_object_str == NULL)
		{
			break;
		}
		response_object_str = strtok(next_response_object_str, THREE);
	}
	return interface_body;
}


Object* build_object(char* object_str)
{
	Object* object = (Object*)malloc(sizeof(Object));
	check_memory(object);
	char* temp = strtok(object_str, FOUR);
	temp = strtok(NULL, FOUR);
	//��ȡ��������
	object->object_param_size = get_object_num(temp, FOUR);
	//��ȡ��������
	object->object_name = strtok(object_str, FOUR);
	//����ռ�
	ObjectParam** object_params = object->object_param;
	object_params = (ObjectParam**)malloc(sizeof(ObjectParam*) * object->object_param_size);
	check_memory(object_params);
	int index = 0;
	temp = strtok(temp, FIVE);
	char* next_temp;
	while (temp)
	{
		next_temp = strtok(NULL, FIVE);
		object_params[index++] = build_object_param(temp);
		if (next_temp == NULL)
		{
			break;
		}
		temp = strtok(next_temp, FIVE);
	}
	return object;
}

ObjectParam* build_object_param(char* object_param_str)
{
	ObjectParam* object = (ObjectParam*)malloc(sizeof(ObjectParam));
	object->param_type = strtok(object_param_str, " ");
	object->param_name = strtok(NULL, ";");
	object->param_annotation = strtok(NULL, "//");
	return object;
}
