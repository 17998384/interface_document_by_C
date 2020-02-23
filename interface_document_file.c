#define _CRT_SECURE_NO_WARNINGS
#include "interface_document_file.h"
//��������ı���
#define FIRST_TITLE "# "
#define SECOND_TITLE "## "
#define TIRED_TITLE "### "
#define FOURTH_TITLE "#### "
#define FIFTH_TITLE "##### "
#define SIXTH_TITLE "###### "
//��׼������
#define GENERAL_TITLE "|������|��������|��������|\n|-------|--------|----------|\n"
//ͨ����
#define GENERAL_BODY "|code|int|״̬��|\n|message|string|����|\n|data|object|���ص�����|\n"
#define SEPARATOR "|"

#define B "**"
//������
#define WITH_BR 4
//խ������
#define NARROW_BR 3

static FILE* out_put_file = NULL;
String* cache = NULL;

//�����ӿ��ĵ��ı���
void create_interface_document_title(char* interface_document_title);

//�����ӿ��ĵ���ͷ
void create_interface_document_head(InterfaceHead* interface_head, int num);

//�����ӿ��ĵ�����
void create_interface_document_body(InterfaceBody* interface_body);

//��������ӿ���
void create_interface_document_general_body(Object* request_object);

//�����������
void create_interface_document_general_param(ObjectParam* object_param);

//��������ַ���(��ˣ����ϵͳ�����������data��)
void create_interface_doucment_after_end_str();

//�ӿڽ���,���»���,��ջ���
void create_interface_doucment_line_feed();

void output_to_file(InterfaceDocument* interface_document, char* output_file_path, char* interface_document_title)
{
	check_null(interface_document);
	//���ļ�
	out_put_file = fopen(output_file_path, "a");
	//����������
	cache = new_string();
	create_interface_document_title(interface_document_title);
	//ѭ�������������
	for (int i = 0, size = interface_document->interface_size; i < size; i++)
	{
		InterfaceHead* interface_head = interface_document->interface_heads[i];
		InterfaceBody* interface_body = interface_document->interface_bodys[i];
		//�����ӿ��ĵ�ͷ
		create_interface_document_head(interface_head, i);
		//�����ӿ��ĵ���
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
	strcat(*buffer, "ϵͳ������");
	strcat(*buffer, B);
	put_multi_row(*buffer, WITH_BR);
	strcat(*buffer, GENERAL_TITLE);
	strcat(*buffer, GENERAL_BODY);
	put_multi_row(*buffer, WITH_BR);

	//������ļ�
	fputs(*buffer, out_put_file);
	fflush(out_put_file);
}

void create_interface_document_head(InterfaceHead* interface_head, int num)
{
	string_clear(cache);
	char** buffer = &cache->buffer;
	sprintf(*buffer, "%s%d%s", TIRED_TITLE, ++num, "��");
	strcat(*buffer, interface_head->request_name);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, B);
	strcat(*buffer, "ǰ��");
	strcat(*buffer, B);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "����ʽ��");
	strcat(*buffer, interface_head->request_way);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "����·����");
	strcat(*buffer, interface_head->request_url);
	put_multi_row(*buffer, NARROW_BR);
	strcat(*buffer, "�������ͣ�");
	strcat(*buffer, interface_head->request_type);
	put_multi_row(*buffer, NARROW_BR);

	//������ļ�
	fputs(*buffer, out_put_file);
	fflush(out_put_file);
}

void create_interface_document_body(InterfaceBody* interface_body)
{
	//��������ӿ���
	for (int i = 0, size = interface_body->request_object_size; i < size; i++)
	{
		Object* request_object = interface_body->request_objects[i];
		create_interface_document_general_body(request_object);
		fputs(cache->buffer, out_put_file);
	}
	//���������ʾ�� eg:  ��ˣ����ϵͳ�����������data��
	create_interface_doucment_after_end_str();
	//������Ӧ�ӿ���
	for (int i = 0, size = interface_body->response_object_size; i < size; i++)
	{
		Object* response_object = interface_body->response_objects[i];
		create_interface_document_general_body(response_object);
		fputs(cache->buffer, out_put_file);
	}
	//�ӿڽ���,���»���,��ջ���
	create_interface_doucment_line_feed();
}

void create_interface_document_general_body(Object* object)
{
	string_clear(cache);
	char** buffer = &cache->buffer;
	strcat(*buffer, object->object_name);
	strcat(*buffer, "��");
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
	strcat(*buffer, "���");
	strcat(*buffer, B);
	strcat(*buffer, "�����ϵͳ�����������data��");
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
