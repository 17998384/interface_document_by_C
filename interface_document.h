#pragma once
#include "my_string.h"
#include "utils.h"
#include "exception.h"

typedef struct object_body
{
	char* param_type;			//��������
	char* param_name;			//��������
	char* param_annotation;		//����ע��
}ObjectParam;

typedef struct object
{
	char* object_name;			//������
	int object_param_size;		//�βδ�С
	ObjectParam** object_param;	//�����������
}Object;

typedef struct interface_body
{
	int request_object_size;		//��������С
	int response_object_size;		//��Ӧ�����С
	Object** request_objects;		//�����������
	Object** response_objects;		//��Ӧ��������
}InterfaceBody;

typedef struct interface_head
{
	char* request_name;		//����������
	char* request_way;		//����ʽ
	char* request_url;		//����·��
	char* request_type;		//��������(form-data,json)
}InterfaceHead;

typedef struct interface_document
{
	int interface_size;					//�ӿ�����
	InterfaceHead** interface_heads;	//�ӿ�ͷ����
	InterfaceBody** interface_bodys;	//�ӿ�������
}InterfaceDocument;

//�����ļ�����ַ���
InterfaceBody** parse_interface_body(char* source, int interface_size);

InterfaceHead** parse_interface_head(char* source, int interface_size);
