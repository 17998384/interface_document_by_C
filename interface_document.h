
//Created by 葛振东 on 2020/02/23
//Copyright	 2020 葛振东. All rights reserved.

#pragma once
#include "my_string.h"
#include "utils.h"
#include "exception.h"

//对象参数
typedef struct object_param
{
	char* param_type;			//参数类型
	char* param_name;			//参数名字
	char* param_annotation;		//参数注释
}ObjectParam;

//对象
typedef struct object
{
	char* object_name;				//对象名
	int object_param_size;			//形参大小
	ObjectParam** object_params;	//对象参数数组
}Object;

//接口体entity
typedef struct interface_body
{
	int request_object_size;		//请求对象大小
	int response_object_size;		//响应对象大小
	Object** request_objects;		//请求对象数组
	Object** response_objects;		//响应对象数组
}InterfaceBody;

//接口头entity
typedef struct interface_head
{
	char* request_name;		//该请求名字
	char* request_way;		//请求方式
	char* request_url;		//请求路径
	char* request_type;		//请求类型(form-data,json)
}InterfaceHead;

//接口文档entity
typedef struct interface_document
{
	int interface_size;					//接口总数
	InterfaceHead** interface_heads;	//接口头数组
	InterfaceBody** interface_bodys;	//接口体数组
	String* interface_heads_str;		//依赖的解析字符串
	String* interface_bodys_str;		//依赖的解析字符串
}InterfaceDocument;

//构建接口文档
InterfaceDocument* build_interface_document(int num, String* interface_bodys_str, String* interface_heads_str
	, InterfaceBody** interface_bodys, InterfaceHead** interface_heads);

//解析成接口体对象
InterfaceBody** parse_interface_body(String* interface_bodys_str, int interface_size);

//解析成接口头对象
InterfaceHead** parse_interface_head(String* interface_heads_str, int interface_size);

//释放文档空间
void delete_interface_document(InterfaceDocument* interface_document);
