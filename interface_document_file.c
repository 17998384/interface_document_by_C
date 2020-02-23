#define _CRT_SECURE_NO_WARNINGS
#include "interface_document_file.h"
//各个级别的标题
#define FIRST_TITLE "# "
#define SECOND_TITLE "## "
#define TIRED_TITLE "### "
#define FOURTH_TITLE "#### "
#define FIFTH_TITLE "##### "
#define SIXTH_TITLE "###### "
//标准表格标题
#define GENERAL_TITLE "|参数名|参数类型|参数描述|\n|-------|--------|----------|\n"
//通用体
#define GENERAL_BODY "|code|int|状态码|\n|message|string|描述|\n|data|object|返回的数据|\n"
#define SEPARATOR "|"

#define B "**"
//宽换行数
#define WITH_BR 4
//窄换行数
#define NARROW_BR 3

static FILE* out_put_file = NULL;
String* cache = NULL;

//创建接口文档的标题
void create_interface_document_title(char* interface_document_title);

//创建接口文档的头
void create_interface_document_head(InterfaceHead* interface_head, int num);

//创建接口文档的体
void create_interface_document_body(InterfaceBody* interface_body);

//创建请求接口体
void create_interface_document_general_body(Object* request_object);

//创建对象参数
void create_interface_document_general_param(ObjectParam* object_param);

//创建后端字符串(后端（针对系统级参数里面的data）)
void create_interface_doucment_after_end_str();

//接口结束,留下换行,清空缓存
void create_interface_doucment_line_feed();

void output_to_file(InterfaceDocument* interface_document, char* output_file_path, char* interface_document_title)
{
	check_null(interface_document);
	//打开文件
	out_put_file = fopen(output_file_path, "a");
	//创建缓冲区
	cache = new_string();
	create_interface_document_title(interface_document_title);
	//循环放入解析内容
	for (int i = 0, size = interface_document->interface_size; i < size; i++)
	{
		InterfaceHead* interface_head = interface_document->interface_heads[i];
		InterfaceBody* interface_body = interface_document->interface_bodys[i];
		//创建接口文档头
		create_interface_document_head(interface_head, i);
		//创建接口文档体
		create_interface_document_body(interface_body);
	}
	delete_string(cache);
	fclose(out_put_file);
	cache = NULL;
	out_put_file = NULL;
}

void create_interface_document_title(char* interface_document_title)
{
	char** buffer = &cache->buffer;
	strcat(*buffer, FIRST_TITLE);
	strcat(*buffer, interface_document_title);
	put_multi_row(*buffer, WITH_BR);
	strcat(*buffer, B);
	strcat(*buffer, "系统级参数");
	strcat(*buffer, B);
	put_multi_row(*buffer, WITH_BR);
	strcat(*buffer, GENERAL_TITLE);
	strcat(*buffer, GENERAL_BODY);
	put_multi_row(*buffer, WITH_BR);

	//输出到文件
	fputs(*buffer, out_put_file);
	fflush(out_put_file);
}

void create_interface_document_head(InterfaceHead* interface_head, int num)
{
	string_clear(cache);
	char** buffer = &cache->buffer;
	sprintf(*buffer, "%s%d%s", TIRED_TITLE, ++num, "、");
	strcat(*buffer, interface_head->request_name);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, B);
	strcat(*buffer, "前端");
	strcat(*buffer, B);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "请求方式：");
	strcat(*buffer, interface_head->request_way);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "请求路径：");
	strcat(*buffer, interface_head->request_url);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "请求类型：");
	strcat(*buffer, interface_head->request_type);
	put_multi_row(*buffer, NARROW_BR);

	//输出到文件
	fputs(*buffer, out_put_file);
	fflush(out_put_file);
}

void create_interface_document_body(InterfaceBody* interface_body)
{
	//创建请求接口体
	for (int i = 0, size = interface_body->request_object_size; i < size; i++)
	{
		Object* request_object = interface_body->request_objects[i];
		create_interface_document_general_body(request_object);
		fputs(cache->buffer, out_put_file);
	}
	//创建后端提示语 eg:  后端（针对系统级参数里面的data）
	create_interface_doucment_after_end_str();
	//创建响应接口体
	for (int i = 0, size = interface_body->response_object_size; i < size; i++)
	{
		Object* response_object = interface_body->response_objects[i];
		create_interface_document_general_body(response_object);
		fputs(cache->buffer, out_put_file);
	}
	//接口结束,留下换行,清空缓存
	create_interface_doucment_line_feed();
}

void create_interface_document_general_body(Object* object)
{
	string_clear(cache);
	char** buffer = &cache->buffer;
	strcat(*buffer, object->object_name);
	strcat(*buffer, "：");
	put_multi_row(*buffer, 3);
	strcat(*buffer, GENERAL_TITLE);
	for (int i = 0, size = object->object_param_size; i < size; i++)
	{
		ObjectParam* object_param = object->object_params[i];
		create_interface_document_general_param(object_param);
	}
}

void create_interface_document_general_param(ObjectParam* object_param)
{
	char** buffer = &cache->buffer;
	strcat(*buffer, SEPARATOR);
	strcat(*buffer, object_param->param_name);
	strcat(*buffer, SEPARATOR);
	strcat(*buffer, object_param->param_type);
	strcat(*buffer, SEPARATOR);
	strcat(*buffer, object_param->param_annotation);
	strcat(*buffer, SEPARATOR);
	strcat(*buffer, "\n");
}

void create_interface_doucment_after_end_str()
{
	string_clear(cache);
	char** buffer = &cache->buffer;
	put_multi_row(*buffer, 4);
	strcat(*buffer, B);
	strcat(*buffer, "后端");
	strcat(*buffer, B);
	strcat(*buffer, "（针对系统级参数里面的data）");
	put_multi_row(*buffer, 4);
	fputs(*buffer,out_put_file);
	fflush(out_put_file);
}

void create_interface_doucment_line_feed()
{
	string_clear(cache);
	put_multi_row(cache->buffer, 4);
	fputs(cache->buffer, out_put_file);
	fflush(out_put_file);
}
