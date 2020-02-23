#define _CRT_SECURE_NO_WARNINGS
#include "interface_document.h"
#define ONE "------------------\n"
#define TWO "---------\n"
#define THREE "----\n"
#define FOUR ":\n"
#define FIVE "\n"
#define SIX ";\n"

//构建接口体
InterfaceBody* build_interface_body(char* interface_body_str);

//构建接口头
InterfaceHead* build_interface_head(char* interface_head_str);

//构建请求object
Object* build_object(char* object_str);

//构建objet_param
ObjectParam* build_object_param(char* object_param_str);

//释放接口头空间
void free_interface_head_memory(InterfaceHead** interface_heads, int size);

//释放接口体空间
void free_interface_body_memory(InterfaceBody** interface_bodys, int size);

//释放标准对象空间
void free_general_object_memory(Object** _objects, int size);

InterfaceDocument* build_interface_document(int num, String* interface_bodys_str, String* interface_heads_str
	, InterfaceBody** interface_bodys, InterfaceHead** interface_heads)
{
	InterfaceDocument* interface_document = (InterfaceDocument*)malloc(sizeof(InterfaceDocument));
	check_memory(interface_document);
	interface_document->interface_size = num;
	interface_document->interface_bodys_str = interface_bodys_str;
	interface_document->interface_heads_str = interface_heads_str;
	interface_document->interface_bodys = interface_bodys;
	interface_document->interface_heads = interface_heads;
	return interface_document;
}

InterfaceBody** parse_interface_body(String* interface_bodys_str, int interface_size)
{
	//分配空间
	InterfaceBody** interface_bodys = (InterfaceBody**)malloc(sizeof(InterfaceBody) * interface_size);
	check_memory(interface_bodys);
	//分割出接口体字符串
	char* next_interface_body_str = NULL;
	char* interface_body_str0 = my_split_plus(interface_bodys_str->buffer, ONE, NULL);
	int index = 0;
	//循环构建
	while (interface_body_str0)
	{
		next_interface_body_str = get_split_last_pointer();
		interface_bodys[index++] = build_interface_body(interface_body_str0);
		interface_body_str0 = my_split_plus(NULL, ONE, next_interface_body_str);
	}
	return interface_bodys;
}

InterfaceHead** parse_interface_head(String* interface_heads_str, int interface_size)
{
	//分配空间
	InterfaceHead** interface_heads = (InterfaceHead**)malloc(sizeof(InterfaceHead) * interface_size);
	check_memory(interface_heads);
	//分割出接口头字符串
	char* next_interface_head_str = NULL;
	char* interface_head_str0 = my_split_plus(interface_heads_str->buffer, SIX, NULL);
	int index = 0;
	//循环构建
	while (interface_head_str0)
	{
		next_interface_head_str = get_split_last_pointer();
		interface_heads[index++] = build_interface_head(interface_head_str0);
		interface_head_str0 = my_split_plus(NULL, SIX, next_interface_head_str);
	}
	return interface_heads;
}

void delete_interface_document(InterfaceDocument* interface_document)
{
	printf("free memory...\n");
	delete_string(interface_document->interface_heads_str);
	delete_string(interface_document->interface_bodys_str);
	free_interface_head_memory(interface_document->interface_heads, interface_document->interface_size);
	free_interface_body_memory(interface_document->interface_bodys, interface_document->interface_size);
	free(interface_document);
	printf("All memory free!\n");
}

InterfaceBody* build_interface_body(char* interface_body_str)
{
	//获取请求对象字符串
	char* request_object_str = my_split(interface_body_str, TWO);
	//获取响应对象字符串
	char* response_object_str = my_split(NULL, TWO);
	//构建interface_body
	InterfaceBody* interface_body = (InterfaceBody*)malloc(sizeof(InterfaceBody));
	check_memory(interface_body);
	//获取请求对象大小
	interface_body->request_object_size = get_object_num(request_object_str, THREE);
	//获取响应对象大小
	interface_body->response_object_size = get_object_num(response_object_str, THREE);
	//初始化请求与响应对象指针
	interface_body->request_objects = (Object**)malloc(sizeof(Object*) * interface_body->request_object_size);
	interface_body->response_objects = (Object**)malloc(sizeof(Object*) * interface_body->response_object_size);
	check_memory(interface_body->request_objects);
	check_memory(interface_body->response_objects);
	//构建请求对象
	char* next_request_object_str = NULL;
	request_object_str = my_split_plus(request_object_str, THREE, NULL);
	int index = 0;
	while (request_object_str)
	{
		next_request_object_str = get_split_last_pointer();
		interface_body->request_objects[index++] = build_object(request_object_str);
		request_object_str = my_split_plus(NULL, THREE, next_request_object_str);
	}
	//构建响应对象
	char* next_response_object_str = NULL;
	response_object_str = my_split_plus(response_object_str, THREE, NULL);
	index = 0;
	while (response_object_str)
	{
		next_response_object_str = get_split_last_pointer();
		interface_body->response_objects[index++] = build_object(response_object_str);
		response_object_str = my_split_plus(NULL, THREE, next_response_object_str);
	}
	return interface_body;
}

InterfaceHead* build_interface_head(char* interface_head_str)
{
	InterfaceHead* interface_head = (InterfaceHead*)malloc(sizeof(InterfaceHead));
	check_memory(interface_head);
	interface_head->request_name = my_split(interface_head_str, ",");
	interface_head->request_way = my_split(NULL, ",");
	interface_head->request_url = my_split(NULL, ",");
	interface_head->request_type = my_split(NULL, ",");
	return interface_head;
}

Object* build_object(char* object_str)
{
	Object* object = (Object*)malloc(sizeof(Object));
	check_memory(object);
	char* temp = my_split(object_str, FOUR);
	//获取对象名字
	object->object_name = temp;
	temp = my_split(NULL, FOUR);
	//获取参数数量
	object->object_param_size = get_object_num(temp, FIVE);
	//申请空间
	object->object_params = (ObjectParam**)malloc(sizeof(ObjectParam*) * object->object_param_size);
	check_memory(object->object_params);
	int index = 0;
	char* next_temp = NULL;
	temp = my_split_plus(temp, FIVE, NULL);
	while (temp)
	{
		next_temp = get_split_last_pointer();
		object->object_params[index++] = build_object_param(temp);
		temp = my_split_plus(NULL, FIVE, next_temp);
	}
	return object;
}

ObjectParam* build_object_param(char* object_param_str)
{
	ObjectParam* object = (ObjectParam*)malloc(sizeof(ObjectParam));
	object->param_type = my_split(object_param_str, " ");
	char* temp = my_split(NULL, " ");
	object->param_name = my_split(temp, ";");
	temp = my_split(NULL, ";");
	temp = my_split(temp, "//");
	temp = my_split(NULL, "//");
	object->param_annotation = temp == NULL ? "" : temp;
	return object;
}

void free_interface_head_memory(InterfaceHead** interface_heads, int size)
{
	for (int i = 0; i < size; i++)
	{
		InterfaceHead* interface_head = interface_heads[i];
		free(interface_head);
	}
	free(interface_heads);
}

void free_interface_body_memory(InterfaceBody** interface_bodys, int size)
{
	for (int i = 0; i < size; i++)
	{
		InterfaceBody* interface_body = interface_bodys[i];
		free_general_object_memory(interface_body->request_objects, interface_body->request_object_size);
		free_general_object_memory(interface_body->response_objects, interface_body->response_object_size);
	}
	free(interface_bodys);
}

void free_general_object_memory(Object** _objects, int size)
{
	for (int i = 0; i < size; i++)
	{
		Object* object = _objects[i];
		for (int j = 0, _size = object->object_param_size; j < _size; j++)
		{
			ObjectParam* object_param = object->object_params[j];
			free(object_param);
		}
		free(object);
	}
	free(_objects);
}
