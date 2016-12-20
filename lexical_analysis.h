#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
�ⲿ���Ǵʷ���������Ϊͷ�ļ���dfa.c�ļ�����
���ߣ�������
*/

typedef struct List* list_pointer;
struct List {
	int num;
	char* s;
	char* value;
	char* type;
	char* error;
	list_pointer next;
};//����ʷ��������н������

typedef struct Result* pointer;
struct Result {
	int index;//����
	list_pointer list;
	pointer next;
};//����ʷ������������
typedef pointer result_p;

/*
��ʼ������ʷ������������
*/
result_p create() {
	pointer head = (pointer)malloc(sizeof(struct Result));
	head->index = 0;
	head->list = NULL;
	head->next = NULL;
	return head;
}

/*
������Ԫ��
*/
list_pointer setData(int num, char* s, char* value, char* type, list_pointer p, char* error) {
	list_pointer list_head = (list_pointer)malloc(sizeof(struct List));
	list_head->num = num;
	list_head->s = s;
	list_head->value = value;
	list_head->type = type;
	list_head->error = error;
	list_head->next = NULL;

	p->next = list_head;
	p = list_head;
	return p;
}

/*
���дʷ�����
*/
pointer single_analysis(char* str, pointer h) {
	char* a = "int";
	char* b = "double";
	char* c = "������ڷǷ��ַ�";
	char* d = "��ͷ���ڷǷ��ַ�";
	char* e = "��ֵ�Ƿ�";
	int i = 0;
	char *s,*value,*type,*error;
	list_pointer p = (list_pointer)malloc(sizeof(struct List));
	pointer r = (pointer)malloc(sizeof(struct Result));
	p->next = NULL;
	r->index = h->index+1;
	r->list = p;
	r->next = NULL;
	h->next = r;
	h = r;

	while(*(str+i) != '\0') {
		switch(*(str+i)) {
			case ' ':
				break;
			case '\n'://ĩβ���з�
				break;
			case '\t':
				break;
			case '+':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(1,s,value,type,p,error);
				break;
			case '-':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(2,s,value,type,p,error);
				break;
			case '*':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(3,s,value,type,p,error);
				break;
			case '/':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(4,s,value,type,p,error);
				break;
			case '(':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(6,s,value,type,p,error);
				break;
			case ')':
				s = (char*)malloc(sizeof(char)*2);
				strncpy(s,str+i,1);
				s[1] = '\0';
				value = NULL;
				type = NULL;
				error = NULL;
				p = setData(7,s,value,type,p,error);
				break;
			case '.':
				error = (char*)malloc(sizeof(char)*10);
				strncpy(error,str+i,1);
				error[1] = '\0';
				strcat(error,e);

				s = NULL;
				value = NULL;
				type = NULL;
				p = setData(0,s,value,type,p,error);
				break;
			default:
				if(*(str+i) >= '0' && *(str+i) <= '9') {
					int num = 5,j,k;
					int flag = 0;//��ʶС����
					value = NULL;
					type = NULL;
					s = (char*)malloc(sizeof(char)*51);
					strncpy(s,str+i,1);
					s[1] = '\0';
				/*	if(*(str+i) == '0' && *(str+i+1) != '.') {
						i++;
					} else {*/
					while(*(str+(++i)) == '.' || (*(str+i) >= '0' && *(str+i) <= '9')) {
						if(*(str+i) == '.') {
							if(flag == 0) {
								flag = 1;
								num = 8;
								type = (char*)malloc(sizeof(char)*7);
								strcpy(type,b);
							} else {
								break;
							}
							
						}
						if(strlen(s) < 50)
							strncat(s,str+i,1);
					}
					if(*(str+i-1) == '.')
						flag = 2;
				//	}
					if(type == NULL) {
						type = (char*)malloc(sizeof(char)*4);
						strcpy(type,a);
					}

					//���ָ�ʽ���󱨴�
					if(flag == 2){
						error = (char*)malloc(sizeof(char)*(strlen(s)+8+1));
						error[0] = '\0';
						strcpy(error,s);
						strcat(error,e);

						free(s);
						free(type);
						s = NULL;
						value = NULL;
						type = NULL;
						p = setData(0,s,value,type,p,error);
					} else {
						//ȥ����ֵ������0
						for(j=0,k=strlen(s)-1; (s[j] == '0' || (s[k]=='0' && type[0]=='d')) && j<k; ) {
							if(s[j] == '0') {
								j++;
							}
							if(s[k]=='0' && type[0]=='d') {
								k--;
							}
						}
						if(s[j] == '.') {
							j--;
						}
						if(s[k] == '.') {
							k++;
						}
						value = (char*)malloc(sizeof(char)*(k-j+2));
						strncpy(value,s+j,k-j+1);
						value[k-j+1] = '\0';

						error = NULL;
						p = setData(num,s,value,type,p,error);
					}
					i--;
				} else {
					error = (char*)malloc(sizeof(char)*20);
					if(i-1 < 0) {
						error[0] = '\0';
						strcat(error,d);
					} else {
						strncpy(error,str+i-1,1);
						error[1] = '\0';
						strcat(error,c);
					}

					//�ж������ַ���Ӣ���ַ�
					if(*(str+i) > -1 && *(str+i) < 128) {
						strncat(error,str+i,1);
						error[strlen(c)+2] = '\0';
					} else {
						strncat(error,str+i,2);
						error[strlen(c)+3] = '\0';
						i++;
					}
					
					s = NULL;
					value = NULL;
					type = NULL;
					p = setData(0,s,value,type,p,error);
				}
				break;
		}
		i++;
	}
	return h;
}

/*
����ʷ�����
*/
void lexical_analysis(result_p head) {
	FILE *fp;
	pointer h = head;
	char* f = (char*)malloc(sizeof(char)*20);
	char* str = (char*)malloc(sizeof(char)*500);

	while(1) {
		printf("�������ļ���(����·����20�ַ���)��");
		gets(f);
		//�ļ��򿪲��ж��Ƿ�ɹ�
		if((fp=fopen(f,"r")) == NULL) {
			printf("\n�����ļ���ʧ�ܣ�\n\n");
		} else {
			break;
		}
	}
	//��ȡÿһ�в�����
	while(fgets(str,500,fp) != NULL) {
		h = single_analysis(str,h);
	}
	fclose(fp);
}

/*
�ʷ�����������
*/
void output_lexical(result_p head) {
	pointer p = head->next;
	int sum = 0;
	printf("\n�ʷ����������\n");
	while(p != NULL) {
		list_pointer q = p->list->next;
		printf("-----------------\n");
		if(q == NULL) {//����
			printf("****����****\n");
		}
		while(q != NULL) {
			if(q->error == NULL)
				printf("    (%d, %s, %s, %s)\n",q->num,q->s,q->value==NULL?"NULL":q->value,q->type==NULL?"NULL":q->type);
			q = q->next;
		}
		p = p->next;
	}
	printf("����������������������������������������\n");

	//��ʾ������Ϣ
	p = head->next;
	while(p != NULL) {
		list_pointer q = p->list->next;
		while(q != NULL) {
			if(q->error != NULL)
				printf(" Error%d����%d�У�%s\n",++sum,p->index,q->error);
			q = q->next;
		}
		p = p->next;
	}
	printf("\n");
}