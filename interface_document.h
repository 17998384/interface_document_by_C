#pragma once
#include "my_string.h"
#include "utils.h"
#include "exception.h"

typedef struct object_body
{
	char* param_type;			//参数类型
	char* param_name;			//参数名字
	char* param_annotation;		//参数注释
}ObjectParam;

typedef struct object
{
	char* object_name;			//对象名
	int object_param_size;		//形参大小
	ObjectParam** object_param;	//对象参数数组
}Object;

typedef struct interface_body
{
	int request_object_size;		//请求对象大小
	int response_object_size;		//响应对象大小
	Object** request_objects;		//请求对象数组
	Object** response_objects;		//响应对象数组
}InterfaceBody;

typedef struct interface_head
{
	char* request_name;		//该请求名字
	char* request_way;		//请求方式
	char* request_url;		//请求路径
	char* request_type;		//请求类型(form-data,json)
}InterfaceHead;

typedef struct interface_document
{
	int interface_size;					//接口总数
	InterfaceHead** interface_heads;	//接口头数组
	InterfaceBody** interface_bodys;	//接口体数组
}InterfaceDocument;

//解析文件体成字符串
InterfaceBody** parse_interface_body(char* source, int interface_size);

InterfaceHead** parse_interface_head(char* source, int interface_size);
