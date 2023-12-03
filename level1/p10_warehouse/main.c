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
    int id;
    char name[20];
    double price;
    int stock;
    struct product* next;
};

struct sales
{
    int id;
    double pri;
    int quantity;
    struct sales* next;
};

struct purchase
{
    int id;
    double pr;
    int num;
    struct purchase* next;
};

struct product* creat1(int n, struct product* h)
{
    struct product* head = NULL, * p1 = NULL, * p2 = NULL, * p3 = NULL;
    int i, j, f = 0;
    p3 = h;
    for (i = 1; i <= n; i++)
    {
        p1 = (struct product*)malloc(LEN1);
        printf("输入商品编号:");
        scanf("%d", &j);
        while (p3) {
            if (p3->id == j) {
                printf("已存在相同编号的商品!");
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
        printf("输入商品的名字:");
        scanf("%s", &p1->name);
        printf("输入商品的价格:");
        scanf("%lf", &p1->price);
        printf("输入商品的库存数量:");
        scanf("%d", &p1->stock);
        p1->next = NULL;
        if (i == 1) head = p1;
        else p2->next = p1;
        p2 = p1;
    }
    return(head);
};

struct product* conect1(struct product* p1_c1, struct product* p2_c1)
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

void print1(struct product* head)
{
    struct product* p1_h = NULL;
    int i;
    p1_h = head;
    while (p1_h != NULL) {
        printf("__________________________\n");
        printf("|商品ID:%d               \n", p1_h->id);
        printf("|商品名称:%s             \n", p1_h->name);
        printf("|商品价格%lf            \n", p1_h->price);
        printf("|商品库存:%d             \n", p1_h->stock);
        printf("__________________________\n\n");
        p1_h = p1_h->next;
    }
    p1_h = NULL;

}


struct product* load(struct product* head)
{
    FILE* fp_l;
    if ((fp_l = fopen("C:\\Users\\ying\\CLionProjects\\c2023-challenge\\level1\\p10_warehouse\\数据\\menu.txt", "r")) == NULL) {
        printf("加载商品信息文档失败\n");
        exit(1);
    }
    else {
        printf("加载商品信息文档成功\n\n\n");
    }
    int flag = 1;
    int id_t;
    char name_t[20];
    double price_t;
    int stock_t;
    struct product* p1_lo = NULL, * p2_lo = NULL, * p3_lo = NULL;
    p2_lo = (struct product*)malloc(LEN1);
    p2_lo->next = NULL;
    while (!feof(fp_l))//????????????
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



struct product* write(struct product* head_wr)
{
    FILE* fp_wr;
    struct product* p1_wr = NULL;
    if ((fp_wr = fopen("C:\\Users\\ying\\CLionProjects\\c2023-challenge\\level1\\p10_warehouse\\数据\\menu.txt", "w+")) == NULL) {
        printf("数据文档加载失败\n");
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
    printf("数据写入成功!\n\n\n");
    return p1_wr;
}

int main() {

    struct product* head1 = NULL, * head2 = NULL, * flag = NULL;
    struct sales* list1 = NULL, * list2 = NULL, * flag1 = NULL;
    struct purchase* form1 = NULL, * form2 = NULL, * flag2 = NULL;
    int n, i, j = 0;
    head1 = load(head1);
    while (j != 5) {
        system("cls");//?????????????????
        printf("______________________________________________________________________\n");
        printf("....................欢迎使用商品进销管理系统..........................\n");
        printf("______________________________________________________________________\n");
        printf(".                    您可以继续进行的操作如下:                       .\n");
        printf(".                        1.录入商品信息                       .\n");
        printf(".                        2.商品入库                          .\n");
        printf(".                        3.商品出库                          .\n");
        printf(".                        4.输出所有商品信息                    .\n");
        printf(".                        5.退出程序                          .\n");
        printf("______________________________________________________________________\n");
        printf("请输入数字进行操作:");
        scanf("%d", &j);
        printf("\n等待中......", j);
        printf("......................................................................\n\n\n\n\n\n\n");
        system("cls");
        if (j == 1) {
            head2 = creat1(1, head1);
            if (head1) {
                head1 = conect1(head1, head2);
            }
            else {
                head1 = head2;
            }
            printf("\n按任意键继续\n");
            system("pause");
        }else if(j==2){

        }else if(j==5){
            print1(head1);
        }
        else if(j==5){
            break;
        }
    }
    flag=write(head1);
    printf("----------感谢使用----------\n");
    return 0;
}