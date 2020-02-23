
//Created by ���� on 2020/02/23
//Copyright	 2020 ����. All rights reserved.

#pragma once
#include "my_string.h"
#include "utils.h"
#include "exception.h"

//�������
typedef struct object_param
{
	char* param_type;			//��������
	char* param_name;			//��������
	char* param_annotation;		//����ע��
}ObjectParam;

//����
typedef struct object
{
	char* object_name;				//������
	int object_param_size;			//�βδ�С
	ObjectParam** object_params;	//�����������
}Object;

//�ӿ���entity
typedef struct interface_body
{
	int request_object_size;		//��������С
	int response_object_size;		//��Ӧ�����С
	Object** request_objects;		//�����������
	Object** response_objects;		//��Ӧ��������
}InterfaceBody;

//�ӿ�ͷentity
typedef struct interface_head
{
	char* request_name;		//����������
	char* request_way;		//����ʽ
	char* request_url;		//����·��
	char* request_type;		//��������(form-data,json)
}InterfaceHead;

//�ӿ��ĵ�entity
typedef struct interface_document
{
	int interface_size;					//�ӿ�����
	InterfaceHead** interface_heads;	//�ӿ�ͷ����
	InterfaceBody** interface_bodys;	//�ӿ�������
	String* interface_heads_str;		//�����Ľ����ַ���
	String* interface_bodys_str;		//�����Ľ����ַ���
}InterfaceDocument;

//�����ӿ��ĵ�
InterfaceDocument* build_interface_document(int num, String* interface_bodys_str, String* interface_heads_str
	, InterfaceBody** interface_bodys, InterfaceHead** interface_heads);

//�����ɽӿ������
InterfaceBody** parse_interface_body(String* interface_bodys_str, int interface_size);

//�����ɽӿ�ͷ����
InterfaceHead** parse_interface_head(String* interface_heads_str, int interface_size);

//�ͷ��ĵ��ռ�
void delete_interface_document(InterfaceDocument* interface_document);
