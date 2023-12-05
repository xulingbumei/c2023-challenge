#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define LEN1 sizeof(struct product)
#define LEN2 sizeof(struct sales)
#define LEN3 sizeof(struct purchase)
//
static int shu = 0;

struct product//记录库存商品
{
    int id;
    char name[20];
    double price;
    int stock;
    struct product* next;
};

struct sales//记录销售记录（出库）
{
    int id;
    double pri;
    int quantity;
    struct sales* next;
};

struct purchase//记录购买记录（入库）
{
    int id;
    double pr;
    int num;
    struct purchase* next;
};

struct product* creat1(int n, struct product* h);//创建一个库存变量
struct purchase*creat3(int n,struct purchase*p);

struct sales *creat2(int n,struct product *p);//创建商品销售链表

struct product* conect1(struct product* p1_c1, struct product* p2_c1);//在文件中读取出来的库存链表后面连接上新生成的链表
struct sales *conect2(struct sales*p1_c2,struct sales*p2_c2);
struct purchase*connect3(struct purchase*p1_c3,struct purchase*p2_c3);


void print1(struct product* head);//输出库存链表

struct product* load1(struct product* head);//
struct sales *load_sl(struct sales *head);
struct purchase *load_pu(struct purchase *head);//商品进货信息文件加载函数


struct product* write(struct product* head_wr);

struct product *save1(struct product *p1,int q,int s);
struct product *save1(struct product *p1,int q,int s)//销售商品时改变商品信息中的商品数
{
    struct product *pm=NULL,*p2_sa=NULL;
    pm=p1;
    int i=0;
    while (pm!=NULL)//查找对应商品
    {
        if(pm->id==q){
            pm->stock-=s;
            i=1;
            break;
        }
        pm=pm->next;
    }
    if(!i){
        printf("未找到对应商品,请先录入商品信息或检查商品ID是否错误!\n");
    }
    return p2_sa;//返回空指针
}
struct product *save2(struct product*p1,int q,int s);//进货时修改商品信息中的商品数
struct product *save2(struct product*p1,int q,int s)
{
    struct product *pm=NULL,*p2=NULL;
    pm=p1;
    int i=0;
    while (pm!=NULL)//找到对应商品
    {
        if(pm->id==q){
            pm->stock+=s;
            i=1;
            break;
        }
        pm=pm->next;
    }
    if(!i){
        printf("未找到对应商品,请先录入商品信息或检查商品ID是否错误!\n");
    }
    return p2;
}



struct sales *dailys(struct sales*head);
struct purchase*dailyp(struct purchase*head){
    FILE *fp_ph;
    struct purchase *p1_ph=NULL;
    if((fp_ph=fopen("purchase form.txt","w+"))==NULL){
        printf("加载文档出错。\n");
        exit(1);
    }
    p1_ph=head;
    while(p1_ph!=NULL){
        fprintf(fp_ph,"\n%d\n",p1_ph->id);
        fprintf(fp_ph,"%lf\n",p1_ph->pr);
        fprintf(fp_ph,"%d",p1_ph->num);
        p1_ph=p1_ph->next;
    }
    fclose(fp_ph);
    printf("数据写入成功!\n");
    p1_ph=NULL;
    return p1_ph;
}




void print1(struct product* head);

int main() {

    struct product* head1 = NULL, * head2 = NULL, * flag = NULL;
    struct sales* list1 = NULL, * list2 = NULL, * flag1 = NULL;
    struct purchase* form1 = NULL, * form2 = NULL, * flag2 = NULL;
    int n, i, j = 0;
    head1 = load1(head1);
    list1= load_sl(list1);
    form1= load_pu(form1);
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
            list2=creat2(1,head1);
            if(list1){//判断是否生成链表
                list1=conect2(list1,list2);
            }else{
                list1=list2;
            }
            printf("\n按任意键继续\n");
            system("pause");
        }else if(j=3){
            form2=creat3(1,form1);
            if(form1){
                form1=connect3(form1,form2);
            }else{
                form1=form2;
            }
            printf("\n按任意键继续\n");
            system("pause");
        }
        else if(j==4){
            print1(head1);
            printf("按任意键继续\n");
            system("pause");
        }
        else if(j==5){
            break;
        }
    }
    flag=write(head1);
    flag1=dailys(list1);
    flag2=dailyp(form1);
    printf("----------感谢使用----------\n");
    return 0;
}
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
}
struct sales *creat2(int n,struct product *p)//创建商品销售链表
{
    struct sales *p1_sl=NULL,*p2=NULL,*head=NULL;
    struct product *m;
    int i,q,s;
    for(i=1;i<=n;i++)
    {
        p1_sl=(struct sales *)malloc(LEN2);
        printf("请输入商品id:\n");
        scanf("%d",&q);
        p1_sl->id=q;
        printf("请输入销售价格:\n");
        scanf("%lf",&p1_sl->pri);
        printf("请输入销售数量:\n");
        scanf("%d",&s);
        p1_sl->quantity=s;
        m=save1(p,q,s);//调用函数改变商品数量
        p1_sl->next=NULL;
        if(i==1) head=p1_sl;
        else p2->next=p1_sl;
        p2=p1_sl;
    }
    return(head);
}
struct purchase*creat3(int n,struct purchase*p){
    struct purchase *p1_pu=NULL,*p2=NULL,*p3=NULL;
    struct product*m=NULL;
    int i,q,s;
    for(i=1;i<=n;i++){
        p1_pu=(struct purchase*)malloc(LEN3);
        printf("请输入商品id\n");
        scanf("%d",&q);
        p1_pu->id=q;
        printf("请输入进货价格\n");
        scanf("%lf",&p1_pu->pr);
        printf("请输入进货数量\n");
        scanf("%d",s);
        p1_pu->num=s;
        m=save2(p,q,s);
        p1_pu->next=NULL;
        if(i==1)p3=p1_pu;
        else p2->next=p1_pu;
        p2=p1_pu;
    }
    return p3;
}

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

struct sales *conect2(struct sales*p1_c2,struct sales*p2_c2){
    struct sales*p3_c2=NULL;
    p3_c2=p1_c2;
    while(p3_c2->next!=NULL){
        p3_c2=p3_c2->next;
    }
    p3_c2->next=p2_c2;
    return (p1_c2);
}
struct purchase*connect3(struct purchase*p1_c3,struct purchase*p2_c3){
    struct purchase*p3_c3=NULL;
    p3_c3=p1_c3;
    while(p3_c3->next!=NULL){
        p3_c3=p3_c3->next;
    }
    p3_c3->next=p2_c3;
    return(p1_c3);
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

struct product* load1(struct product* head)
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
struct sales *load_sl(struct sales *head)//商品销售信息文件加载函数
{
    FILE *fp_l;
    if((fp_l=fopen("sales form.txt","r"))==NULL){
        printf("加载销售文档出错。\n");
        exit(1);
    }else{
        printf("加载销售文档成功。\n");
    }
    int flag=1;
    int id_sl;                     //商品ID
    double pri_sl;                 //销售价格
    int quantity_sl;               //销售量
    struct sales *p1_lo=NULL,*p2_lo=NULL,*p3_lo=NULL;
    p2_lo=(struct sales *)malloc(LEN2);
    p2_lo->next=NULL;
    while(!feof(fp_l)){
        fscanf(fp_l,"%d",&id_sl);
        fscanf(fp_l,"%lf",&pri_sl);
        fscanf(fp_l,"%d",&quantity_sl);
        if(flag){//只有第一个链表分配了存储空间
            p2_lo->id=id_sl;
            p2_lo->pri=pri_sl;
            p2_lo->quantity=quantity_sl;
            flag=0;
            p1_lo=p2_lo;
            p3_lo=p2_lo;
        }else{//后面的链表还没有分配过存储空间
            p2_lo=(struct sales *)malloc(LEN2);
            p2_lo->next=NULL;
            p2_lo->id=id_sl;
            p2_lo->pri=pri_sl;
            p2_lo->quantity=quantity_sl;
            p3_lo->next=p2_lo;
            p3_lo=p3_lo->next;
        }
    }
    fclose(fp_l);
    return p1_lo;
};
struct purchase *load_pu(struct purchase *head)//商品进货信息文件加载函数
{
    FILE *fp_l;
    if((fp_l=fopen("purchase form.txt","r"))==NULL){
        printf("加载进货文档出错。\n");
        exit(1);
    }else{
        printf("加载进货文档成功。\n");
    }
    int flag=1;
    int id_pu;                     //商品ID
    double pr_pu;                  //进货价格
    int num_pu;                    //进货量
    struct purchase *p1_lo=NULL,*p2_lo=NULL,*p3_lo=NULL;
    p2_lo=(struct purchase *)malloc(LEN3);
    p2_lo->next=NULL;
    while(!feof(fp_l)){
        fscanf(fp_l,"%d",&id_pu);
        fscanf(fp_l,"%lf",&pr_pu);
        fscanf(fp_l,"%d",&num_pu);
        if(flag){
            p2_lo->id=id_pu;
            p2_lo->pr=pr_pu;
            p2_lo->num=num_pu;
            flag=0;
            p1_lo=p2_lo;
            p3_lo=p2_lo;
        }else{
            p2_lo=(struct purchase *)malloc(LEN3);
            p2_lo->next=NULL;
            p2_lo->id=id_pu;
            p2_lo->pr=pr_pu;
            p2_lo->num=num_pu;
            p3_lo->next=p2_lo;
            p3_lo=p3_lo->next;
        }
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
struct sales *dailys(struct sales*head)//销售日志写入
{
    FILE  *fp_sl;
    struct sales*p1=NULL;
    p1=head;
    if(fp_sl=fopen("\"C:\\Users\\ying\\CLionProjects\\c2023-challenge\\level1\\p10_warehouse\\数据\\sales form.txt\"","w+"))
    {
        printf("\n写入文档错误\n");
        exit(1);
    }
    while(p1!=NULL){
        fprintf(fp_sl,"\n%d\n",p1->id);
        fprintf(fp_sl,"%lf\n",p1->pri);
        fprintf(fp_sl,"%d",p1->quantity);
        p1=p1->next;
    }
    fclose(fp_sl);
    printf("\n数据写入成功\n");
    p1=NULL;
    return(p1);
}

