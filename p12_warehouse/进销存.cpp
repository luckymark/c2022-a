#include<stdio.h>  
#include<string.h> 
#include<stdlib.h> 
#define M 100      
#define N 100      
struct goods       
{
    int  number;   
    int  price1;
    int  price2;
    int  amount;
    char name[20]; 
 
};
struct orderlist           
{
    struct goods L[M];
};
struct customer            
{
    char name[20];        
    char password[6];      
    int count;             
};
struct customer khl[N];   
struct goods base[M];      
struct orderlist odl[10 * N];
struct goods lackl[M];    
struct goods suml[M + 1];    
int PP = 0;                  
int QQ = 0;                  
int goodssum = 0;              


int main()                    
{
    int SysUseWay();        
    int chushihua();     
    int welcome();       
    int kh();           
    int buyer();     
    int manager();    
    int goodbye();   
    int n, m = 9;   


    chushihua();  
    while (m == 9) 
    {
        welcome(); 
        scanf_s("%d", &n);
        switch (n) 
        {
        case 0:;break;
        case 1: kh(); break;     
        case 2: buyer(); break;    
        case 3: manager(); break;  
        default: printf("输入错误!请退出重从新输入");
        }
        if (n == 0)
            break;
        printf("              继续进入主界面请按 9  退出请按0\n");
        scanf_s("%d", &m);
    }
    goodbye();                
    return 0;
}                             

int welcome()
{

    printf("................................................................................\n");
    printf("\n");
    printf("                      ~~~~~~~~欢迎使用商品销售系统~~~~~~~~\n");
    printf("                              公司客户请按       1\n");
    printf("                              采购人员请按       2\n");
    printf("                              公司经理请按       3\n");
    printf("                              退出主界面请按     0\n");
    return 0;
}

int chushihua()
{
    int i = 0, j = 0;
    for (i = 0;i < M;i++)
    {
        suml[i].number = lackl[i].number = base[i].number = -1;
        base[i].amount = 0;
        base[i].price1 = base[i].price2 = 0;
        lackl[i].amount = 0;
        suml[i].price1 = 0;
        suml[i].amount = 0;
    }
    suml[M].price1 = 0;
    for (i = 0;i < N;i++)
        khl[i].count = -1;
    for (i = 0;i < 10 * N;i++)
    {
        for (j = 0;j < M;j++)
        {
            odl[i].L[j].number = j;
            odl[i].L[j].amount = 0;
            odl[i].L[j].price1 = base[j].price1;
            odl[i].L[j].price2 = base[j].price2;
        }
    }

    return 0;
}

int goodbye()
{
    printf("                 ~~~~感谢您使用商品销售系统~~~~\n");
    return 0;
}

int buyer()
{
    int welcomebuyer();     
    int buildbaser();       
    int solvelack();    
    int chackbase();      
    int n;
    int m = 9;
    while (m == 9)            
    {
        welcomebuyer();             
        scanf_s("%d", &n);            
        switch (n)
        {
        case 0:;break;          
        case 1: solvelack();break; 
        case 2: buildbaser();break; 
        case 3: chackbase();break;  
        default:printf("输入错误!\n");
        }
        if (n == 0)
            break;
        printf("              继续采购请按 9  否则请按0\n");
        scanf_s("%d", &m);
    }
    return 0;
}

int welcomebuyer()
{
    printf("................................................................................\n");
    printf("\n");
    printf("                      ~~~~~~~~欢迎来到采购之家~~~~~~~~\n");
    printf("                              处理缺货                请按   1\n");
    printf("                              进货                    请按   2\n");
    printf("                              查询当前存货情况        请按   3\n");
    printf("                              退出采购                请按   0\n");
    return 0;
}

int buildbaser()
{
    int i = 0;
    printf("            若想停止进货,请在货物数量上输入 0\n\n");
    for (i = 0;i < M;i++)
    {
        printf("\n货物名称:");
        scanf_s("%s", base[i].name);
        base[i].number = i;
        printf("\n货物数量:");
        scanf_s("%d", &base[i].amount);
        if (base[i].amount <= 0) {
            base[i].amount = 0;
            break;
        }
        goodssum += base[i].amount;
        printf("\n货物进价:");
        scanf_s("%d", &base[i].price1);
        printf("\n货物售价:");
        scanf_s("%d", &base[i].price2);
    }
    return 0;
}

int chackbase()
{
    int i = 0;
    printf("................................................................................\n");
    if (goodssum == 0)
    {
        printf("           仓库没货!!!         请采购部门及时进货!!!\n");
        return 0;
    }
    for (i = 0;i < M;i++)
    {
        if (base[i].amount > 0) {
            printf("................................................................................\n");
            printf("货物编号  货物名称             货物数量          进价       售价\n");
            printf(" %3d      %-20s %6d          %6d     %6d \n", base[i].number, base[i].name, base[i].amount, base[i].price1, base[i].price2);
            printf("................................................................................\n");
        }
        else
            continue;
    }
    printf("................................................................................\n");
    return 0;
}

int solvelack()
{
    int i = 0, k = 0;
    int printlack();           
    int supplement();         
    printlack();              
    printf("           如果需要进货，请按1  ； 否则，请按0   \n");
    scanf_s("%d", &k);
    switch (k)
    {
    case 1:supplement();break;
    case 0:;break;
    default:printf("输入错误!\n");
    }
    return 0;
}
int printlack()                
{
    int i = 0, count = 0;
    if (goodssum == 0) {
        printf("                  !!!仓库没货!!!请采购人员及时进货!!!\n");
        return 0;
    }
    printf("................................................................................\n");
    for (i = 0;i < M;i++)
    {
        if (lackl[i].amount == 0) {
            count++;
            continue;
        }
        else {
            printf("................................................................................\n");
            printf("货物编号  货物名称             缺货数量\n");
            printf(" %3d      %-20s %6d          \n", lackl[i].number, base[i].name, lackl[i].amount);
        }
    }
    printf("................................................................................\n");
    if (count == M)
        printf("              货物充足\n");
    else
        printf("                    !!缺!!\n");
    return 0;
}

int supplement()
{
    int i = 0, j = 1;
    int printlack();
    printlack();
    printf("     若想停止进货，请在货物数量上输入0\n");
    while (j > 0)
    {
        printf("产品编号\n");
        scanf_s("%d", &i);
        while (i >= M) {
            printf("此货物不存在，请重新输入\n");
            scanf_s("%d", &i);
        }
        base[i].number = i;
        printf("产品名称:\n");
        scanf_s("%s", base[i].name);
        printf("进货数量:\n");
        scanf_s("%d", &j);
        if (j > 0) {
            base[i].amount += j;
            goodssum += j;
        }
        else
            break;
        printf("\n货物进价:");
        scanf_s("%d", &base[i].price1);
        printf("\n货物售价:");
        scanf_s("%d", &base[i].price2);
    }
    return 0;
}


int kh()
{
    int login();                     
    int registe();                   
    int welcomekh();                  
    int searchkh(int falg);           
    int order(int falg);              
    int i, k = 0, flag = 0;
    int n = 9, m = 9;
    welcomekh();                   
    while (m == 9)                   
    {
        printf("        登陆请按1，          注册请按2,          否则请按 0\n");
        scanf_s("%d", &i);
        switch (i)
        {
        case 0:;break;
        case 1: flag = login(); break;
        case 2: registe(); break;
        default:printf("输入错误!\n");
        }
        if (i == 0)
            break;
        printf("           登陆或注册请按 9  否则请按0\n");
        scanf_s("%d", &m);
    }

    while (n == 9)                    
    {
        printf("         查询请按 1,   订购请按 2,      否则请按 0\n");
        scanf_s("%d", &i);
        switch (i)
        {
        case 0:;break;
        case 1: searchkh(flag); break;
        case 2: order(flag); break;
        default:printf("输入错误!\n");
        }
        if (i == 0)
            break;
        printf("           继续查询或订购请按 9  否则请按0\n");
        scanf_s("%d", &n);
    }
    return 0;
}


int welcomekh()                   
{

    printf("..............................................................................\n");
    printf("  ~~~~~~~~欢迎来到客户之家~~~~~~~~\n");
    printf("..............................................................................\n");
    return 0;
}


int login()
{
    int n, count = 0;
    char password[6];
    printf("-------------------请输入服务编号-----------------------\n");
    scanf_s("%d", &n);
    printf("-------------------请输入六位密码-----------------------\n");
    scanf_s("%s", password);
    while (strcmp(password, khl[n].password))
    {
        printf("~~~~~~~~~~~~~~~请重新输入六位密码~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n");
        printf("               退出登陆,请输入123456\n");
        scanf_s("%s", password);
        if (!strcmp(password, "123456"))
            break;
    }
    if (!strcmp(password, "123456"))
        return 0;
    else
        return n;
}


int registe()
{
    printf("~~~~~~~~~~您的服务编号是: %d ,请你一定要记牢您! ~~~~~~~~~~~~~~\n", QQ);
    printf("~~~~~~~~~~~~~~~请输入您的用户名:~~~~~~~~~~~~~~~~~~\n");
    scanf_s("%s", khl[QQ].name);
    printf("~~~~~~~~~~~~~~~~请输入六位密码:~~~~~~~~~~~~~~~~~~~\n");
    printf("\n");
    scanf_s("%s", khl[QQ].password);
    QQ++;
    return 0;
}


int searchkh(int flag)
{
    int n, i = 0;
    n = flag;
    printf("................................................................................\n");
    printf("               Hello   %s   您的服务编号是: %d\n", khl[n].name, n);
    printf("................................................................................\n");
    if (khl[n].count != -1) {
        for (i = 0;i < M;i++) {
            if (odl[khl[n].count].L[i].amount == 0)
                i++;
            else {
                printf("................................................................................\n");
                printf("货物编号  货物名称             订货数量          单价\n");
                printf(" %3d  %-20s %6d  %6d\n", base[i].number, base[i].name, odl[khl[n].count].L[i].amount, base[i].price2);
                printf("................................................................................\n");
            }

        }
    }
    else {
        printf("\n");
        printf("................................................................................\n");
        printf("             您当前没有订货。          \n");
        printf("................................................................................\n");
    }
    printf("................................................................................\n");
    return 0;
}


int order(int flag)
{
    int i = 0, k = 0, m = 0, n = 0, count = 0;
    printf("\n");
    n = flag;
    printf("货物编号  货物名称               售价\n");
    printf("\n");
    for (i = 0;i < M;i++) {
        if (base[i].number == -1) {
            count++;
            continue;
        }
        else
            printf(" %3d      %-20s %6d\n", base[i].number, base[i].name, base[i].price2);
    }
    if (count == M)
    {
        printf("仓库现在没货，请稍后再来。麻烦您通知采购部门及时补货。。。谢谢。。。\n");
        return 0;
    }
    printf("请输入产品编号和数量,若想结束,在订购数量上输入 0 \n");
    printf("产品编号\n");
    scanf_s("%d", &k);
    while ((k >= M) || (base[k].number == -1)) {
        printf("此货物不存在，请重新输入\n");
        scanf_s("%d", &k);
    }
    printf("数量\n");
    scanf_s("%d", &m);
    while (m > 0)
    {
        if (base[k].amount < m)
        {
            odl[PP].L[k].amount = base[k].amount;
            base[k].amount = 0;
            printf("存货不足,缺 %d 个,先卖给您%d个,剩下的请您稍后重新注册服务编号再预定!同时麻烦您通知采购部门及时补货。。。谢谢。。。\n", odl[PP].L[k].amount - base[k].amount, base[k].amount);
            lackl[k].amount += (m - base[k].amount);
        }
        else {
            odl[PP].L[k].amount = m;
            base[k].amount -= m;
        }
        goodssum -= odl[PP].L[k].amount;
        suml[k].price1 += (odl[PP].L[k].amount * (base[k].price2 - base[k].price1));
        suml[M].price1 += suml[k].price1;
        suml[k].amount += odl[PP].L[k].amount;
        printf("产品编号\n");
        scanf_s("%d", &k);
        while ((k >= M) || (base[k].number == -1)) {
            printf("此货物不存在，请重新输入\n");
            scanf_s("%d", &k);
        }
        printf("订购数量\n");
        scanf_s("%d", &m);
    }
    khl[n].count = PP;
    PP++;
    return 0;
}

int manager()
{

    int i = 0;
    for (i = 0;i < M;i++)
    {
        if (suml[i].amount == 0)
            i++;
        else {
            printf("................................................................................\n");
            printf("货物编号  货物名称           该货物利润\n");
            printf(" %3d      %-20s %6d          \n", suml[i].number, base[i].name, suml[i].price1);
            printf("................................................................................\n");
        }
    }
    printf("\n--------------------总货量为  %d  个-----------------------------\n", goodssum);
    printf("\n--------------------总利润为  %d  美元-----------------------------\n", suml[M].price1);
    return 0;
}


