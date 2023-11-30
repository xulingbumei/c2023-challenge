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
    int id;                     //商品编号
    char name[20];              //商品名称
    double price;               //商品单价
    int stock;                  //商品库存
    struct product* next;       //指向下一个商品信息的指针
};

struct sales
{
    int id;                     //商品ID
    double pri;                 //销售价格
    int quantity;               //销售量
    struct sales* next;         //指向下一个销售信息的指针
};

struct purchase
{
    int id;                     //商品ID
    double pr;                  //进货价格
    int num;                    //进货量
    struct purchase* next;      //指向下一个进货信息的指针
};

struct product* creat1(int n, struct product* h)//创建商品信息链表
{
    struct product* head = NULL, * p1 = NULL, * p2 = NULL, * p3 = NULL;
    int i, j, f = 0;
    p3 = h;
    for (i = 1; i <= n; i++)
    {
        p1 = (struct product*)malloc(LEN1);
        printf("请输入商品编号:");
        scanf("%d", &j);
        while (p3) {
            if (p3->id == j) {
                printf("以存在相同ID商品,请更换ID重新输入!");
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
        printf("请输入商品名字:");
        scanf("%s", &p1->name);
        printf("请输入商品价格:");
        scanf("%lf", &p1->price);
        printf("请输入商品库存:");
        scanf("%d", &p1->stock);
        p1->next = NULL;
        if (i == 1) head = p1;
        else p2->next = p1;
        p2 = p1;
    }
    return(head);
};

struct product* conect1(struct product* p1_c1, struct product* p2_c1)//商品信息链表链接函数
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

void print1(struct product* head)//打印商品信息的函数
{
    struct product* p1_h = NULL;
    int i;
    p1_h = head;
    while (p1_h != NULL) {
        printf("__________________________\n");
        printf("|商品ID:%d               \n", p1_h->id);
        printf("|商品名字:%s             \n", p1_h->name);
        printf("|商品价格:%lf            \n", p1_h->price);
        printf("|商品库存:%d             \n", p1_h->stock);
        printf("__________________________\n\n");
        p1_h = p1_h->next;
    }
    p1_h = NULL;

}


struct product* load(struct product* head)//商品信息文件加载函数
{
    FILE* fp_l;
    if ((fp_l = fopen("menu.txt", "r")) == NULL) {
        printf("加载商品信息文档出错。\n");
        exit(1);
    }
    else {
        printf("加载商品信息文档成功。\n\n\n");
    }
    int flag = 1;
    int id_t;                     //商品编号
    char name_t[20];              //商品名称
    double price_t;               //商品单价
    int stock_t;                  //商品库存
    struct product* p1_lo = NULL, * p2_lo = NULL, * p3_lo = NULL;
    p2_lo = (struct product*)malloc(LEN1);
    p2_lo->next = NULL;
    while (!feof(fp_l))//检测文件是否结束
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



struct product* write(struct product* head_wr)//商品信息写入函数
{
    FILE* fp_wr;
    struct product* p1_wr = NULL;
    if ((fp_wr = fopen("menu.txt", "w+")) == NULL) {
        printf("加载文档出错。\n");
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
    while (j != 11) {
        system("cls");//清屏操作，以下同理
        printf("______________________________________________________________________\n");
        printf("....................欢迎使用商品进销管理系统..........................\n");
        printf("______________________________________________________________________\n");
        printf(".                    您可以继续进行的操作是:                       .\n");
        printf(".                        1.录入商品信息。                        .\n");
        printf(".                      2.录入商品进货信息。                        .\n");
        printf(".                      3.录入商品销售信息。                          .\n");
        printf(".                        4.查找商品信息。                          .\n");
        printf(".                        5.删除商品信息。                          .\n");
        printf(".                        6.修改商品信息。                          .\n");
        printf(".                         7.统计销售额。                           .\n");
        printf(".                         8.统计进货额。                           .\n");
        printf(".                      9.按价格升序排列商品。                      .\n");
        printf(".                      10.打印所有商品信息。                       .\n");
        printf(".                          11.结束程序。                           .\n");
        printf("______________________________________________________________________\n");
        printf("请输入1、2、3、4、5、6、7、8、9、10、11来进行对应操作。\n请问您要进行的操作是:");
        scanf("%d", &j);
        printf("\n即将执行操作%c......", j);
        printf("......................................................................\n\n\n\n\n\n\n");
        system("cls");
        if (j == 1) {
            head2 = creat1(1, head1);
            if (head1) {//判断是否已经生成链表
                head1 = conect1(head1, head2);//将新链表与旧链表链接
            }
            else {
                head1 = head2;
            }
            printf("\n按任意键继续......\n");
            system("pause");

        }
    }
    return 0;
}