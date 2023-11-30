#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define LEN1 sizeof(struct product)
#define LEN2 sizeof(struct sales)
#define LEN3 sizeof(struct purchase)

static int shu = 0;

struct product
{
    int id;                     //��Ʒ���
    char name[20];              //��Ʒ����
    double price;               //��Ʒ����
    int stock;                  //��Ʒ���
    struct product* next;       //ָ����һ����Ʒ��Ϣ��ָ��
};

struct sales
{
    int id;                     //��ƷID
    double pri;                 //���ۼ۸�
    int quantity;               //������
    struct sales* next;         //ָ����һ��������Ϣ��ָ��
};

struct purchase
{
    int id;                     //��ƷID
    double pr;                  //�����۸�
    int num;                    //������
    struct purchase* next;      //ָ����һ��������Ϣ��ָ��
};

struct product* creat1(int n, struct product* h)//������Ʒ��Ϣ����
{
    struct product* head = NULL, * p1 = NULL, * p2 = NULL, * p3 = NULL;
    int i, j, f = 0;
    p3 = h;
    for (i = 1; i <= n; i++)
    {
        p1 = (struct product*)malloc(LEN1);
        printf("��������Ʒ���:");
        scanf("%d", &j);
        while (p3) {
            if (p3->id == j) {
                printf("�Դ�����ͬID��Ʒ,�����ID��������!");
                p3 = NULL;
                f = 1;
                break;
            }
            else {
                p3 = p3->next;
            }
        }
        if (f == 1) {
            i--;
            f = 0;
            continue;
        }
        p1->id = j;
        printf("��������Ʒ����:");
        scanf("%s", &p1->name);
        printf("��������Ʒ�۸�:");
        scanf("%lf", &p1->price);
        printf("��������Ʒ���:");
        scanf("%d", &p1->stock);
        p1->next = NULL;
        if (i == 1) head = p1;
        else p2->next = p1;
        p2 = p1;
    }
    return(head);
};

struct product* conect1(struct product* p1_c1, struct product* p2_c1)//��Ʒ��Ϣ�������Ӻ���
{
    struct product* p3_c1 = NULL;
    p3_c1 = p1_c1;
    while (1)
    {
        if (p1_c1->next == NULL) {
            break;
        }
        p1_c1 = p1_c1->next;
    }
    p1_c1->next = p2_c1;
    return (p3_c1);
}

void print1(struct product* head)//��ӡ��Ʒ��Ϣ�ĺ���
{
    struct product* p1_h = NULL;
    int i;
    p1_h = head;
    while (p1_h != NULL) {
        printf("__________________________\n");
        printf("|��ƷID:%d               \n", p1_h->id);
        printf("|��Ʒ����:%s             \n", p1_h->name);
        printf("|��Ʒ�۸�:%lf            \n", p1_h->price);
        printf("|��Ʒ���:%d             \n", p1_h->stock);
        printf("__________________________\n\n");
        p1_h = p1_h->next;
    }
    p1_h = NULL;

}


struct product* load(struct product* head)//��Ʒ��Ϣ�ļ����غ���
{
    FILE* fp_l;
    if ((fp_l = fopen("menu.txt", "r")) == NULL) {
        printf("������Ʒ��Ϣ�ĵ�����\n");
        exit(1);
    }
    else {
        printf("������Ʒ��Ϣ�ĵ��ɹ���\n\n\n");
    }
    int flag = 1;
    int id_t;                     //��Ʒ���
    char name_t[20];              //��Ʒ����
    double price_t;               //��Ʒ����
    int stock_t;                  //��Ʒ���
    struct product* p1_lo = NULL, * p2_lo = NULL, * p3_lo = NULL;
    p2_lo = (struct product*)malloc(LEN1);
    p2_lo->next = NULL;
    while (!feof(fp_l))//����ļ��Ƿ����
    {
        fscanf(fp_l, "%d", &id_t);
        fscanf(fp_l, "%s", name_t);
        fscanf(fp_l, "%lf", &price_t);
        fscanf(fp_l, "%d", &stock_t);
        if (flag) {
            p2_lo->id = id_t;
            strcpy(p2_lo->name, name_t);
            p2_lo->price = price_t;
            p2_lo->stock = stock_t;
            flag = 0;
            p1_lo = p2_lo;
            p3_lo = p2_lo;
        }
        else {
            p2_lo = (struct product*)malloc(LEN1);
            p2_lo->next = NULL;
            p2_lo->id = id_t;
            strcpy(p2_lo->name, name_t);
            p2_lo->price = price_t;
            p2_lo->stock = stock_t;
            p3_lo->next = p2_lo;
            p3_lo = p3_lo->next;
        }
        shu++;
    }
    fclose(fp_l);
    return p1_lo;
};



struct product* write(struct product* head_wr)//��Ʒ��Ϣд�뺯��
{
    FILE* fp_wr;
    struct product* p1_wr = NULL;
    if ((fp_wr = fopen("menu.txt", "w+")) == NULL) {
        printf("�����ĵ�����\n");
        exit(1);
    }
    while (head_wr != NULL) {
        fprintf(fp_wr, "\n%d\n", head_wr->id);
        fprintf(fp_wr, "%s\n", head_wr->name);
        fprintf(fp_wr, "%lf\n", head_wr->price);
        fprintf(fp_wr, "%d", head_wr->stock);
        head_wr = head_wr->next;
    }
    fclose(fp_wr);
    printf("����д��ɹ�!\n\n\n");
    return p1_wr;
}

int main() {

    struct product* head1 = NULL, * head2 = NULL, * flag = NULL;
    struct sales* list1 = NULL, * list2 = NULL, * flag1 = NULL;
    struct purchase* form1 = NULL, * form2 = NULL, * flag2 = NULL;
    int n, i, j = 0;
    head1 = load(head1);
    while (j != 11) {
        system("cls");//��������������ͬ��
        printf("______________________________________________________________________\n");
        printf("....................��ӭʹ����Ʒ��������ϵͳ..........................\n");
        printf("______________________________________________________________________\n");
        printf(".                    �����Լ������еĲ�����:                       .\n");
        printf(".                        1.¼����Ʒ��Ϣ��                        .\n");
        printf(".                      2.¼����Ʒ������Ϣ��                        .\n");
        printf(".                      3.¼����Ʒ������Ϣ��                          .\n");
        printf(".                        4.������Ʒ��Ϣ��                          .\n");
        printf(".                        5.ɾ����Ʒ��Ϣ��                          .\n");
        printf(".                        6.�޸���Ʒ��Ϣ��                          .\n");
        printf(".                         7.ͳ�����۶                           .\n");
        printf(".                         8.ͳ�ƽ����                           .\n");
        printf(".                      9.���۸�����������Ʒ��                      .\n");
        printf(".                      10.��ӡ������Ʒ��Ϣ��                       .\n");
        printf(".                          11.��������                           .\n");
        printf("______________________________________________________________________\n");
        printf("������1��2��3��4��5��6��7��8��9��10��11�����ж�Ӧ������\n������Ҫ���еĲ�����:");
        scanf("%d", &j);
        printf("\n����ִ�в���%c......", j);
        printf("......................................................................\n\n\n\n\n\n\n");
        system("cls");
        if (j == 1) {
            head2 = creat1(1, head1);
            if (head1) {//�ж��Ƿ��Ѿ���������
                head1 = conect1(head1, head2);//�������������������
            }
            else {
                head1 = head2;
            }
            printf("\n�����������......\n");
            system("pause");

        }
    }
    return 0;
}