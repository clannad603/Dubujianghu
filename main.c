#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


struct Role{
    //  角色信息栏
    char name[128];  // 角色名
    char sex[16];  // 性别
    char mp[16]; // 门派
    int Lv;  // 等级
    int HP;  // 生命值
    int ATK;  // 攻击力
    int Speed;  // 速度
    int EXP;  // 经验值
    char Skill[1024]; // 技能面板

} User;

struct Pack{
    // 物品背包
    int gold;  // 银两

} Bag;

struct Equipment{
    int ATK; // 攻击力增加
    int HP;  // 血量增加
    int Speed;  // 速度增加

}Equip;

struct Monster {                         // 单链表储存怪物数据
    char name[64]; // 怪物名称
    int HP;  // 小怪血量
    int ATK;  // 小怪攻击力
    int Speed;  //小怪速度
    struct Monster *next;   // 指向下一个

};


void Start(); // 游戏初始化
void startPrint(); // 一些形式主义的输出，单独封装

void Stop();  // 游戏结束

void mesSave(); // 存档
void mesRead(); // 读取存档

void rCreate(); // 角色创建
void action(); // 角色行为
void myPrint(struct Role *role); // 打印角色信息,船体结构体指针的方式，提高效率
void reBack(); // 门派信息

void adv(); // 历练
void shop(); // 装备商店,暂无内容
void lvUp(); // 人物升级


void advStart(); // 开场白描述
void Fight(struct Monster *Head); // 战斗系统
int randData(int Min,int Max);  // 怪物的属性值随机生成

void addMonster(struct Monster *monster);  // 添加怪物
void releaseMonster(struct Monster *monster);  // 释放内存空间



int main() {
    int ac; // 角色行为的选择
    Start();

    while (1)
    {
        AC:
        action();
        scanf("%d",&ac);

        if (ac == 4){        // 结束游戏
            Stop();
            break;
        }
        else if (ac == 1){      // 查看角色信息
            myPrint(&User);
        }
        else if (ac == 2){       // 返回门派场景
            reBack();
        }
        else if (ac == 3){      // 冒险打怪
            adv();
        }
        else
        {
            printf("请输入正确的操作指令！\n");
            system("pause");
            goto AC;

        }

    }

    return 0;
}

// 角色行为板块
void Start(){
    int temp;

    startPrint();
    system("pause");

    STAR:

    printf("请选择你要进行的操作：\n");
    printf("新的开始 --> 0\n");
    printf("重现江湖 --> 1\n");
    scanf("%d",&temp);

    if (temp == 0)
    {
        rCreate();
    }
    else if (temp == 1)
    {
        if ((access("GameData.txt",F_OK)) != -1)         // 存档文件是否存在的检测
        {
            printf("检测到本地存档，开始导入数据....\n");
            mesRead();
            sleep(2);
            printf("数据加载完毕\n");
        }
        else{
            printf("没有检测到游戏存档，请选择新的开始！\n");
            system("pause");
            goto STAR;
        }

    }
    else   // 进行错误输入的规避，才用GOTO 节省代码行
    {
        printf("请输入正确的操作指令！\n");
        system("pause");
        goto STAR;
    }

    // 初始化装备加成的数值
    Equip.ATK = 0;
    Equip.Speed = 0;
    Equip.HP = 0;

    system("pause");

}

void Stop(){
    mesSave(); // 文件操作，保留存档
    printf("%s大侠在江湖叱咤了%d载岁月，最终选择暂隐江湖.....\n",User.name,User.Lv);
    sleep(3);
    printf("刀光剑影,血雨腥风，也逐渐淡出他的视野.....\n");
    sleep(2);
    printf("江湖上虽然不再会出现他的身影，但有关他的传说，或许将永世流传.....\n");
    sleep(3);
    printf("The End?\tOr,to be continue.....");
    sleep(2);

}

void rCreate() {
    char temp;
    int sec;
    printf("========角色初始化========\n");

    printf("请输入你的姓名(行走江湖的名号): ");
    scanf("%s", User.name);

    printf("请选择你的性别: 男(M)/女(F) \n");
    getchar();
    scanf("%c",&temp);

    if (temp == 'M'){
        strcpy(User.sex,"男");
    }else{
        strcpy(User.sex,"女");
    }

    SEC:
    printf("请选择你的门派: \n");
    printf("少林(只招收男弟子) --> 1\n");
    printf("武当 --> 2\n");
    printf("峨眉(只招收女弟子) --> 3\n");
    printf("丐帮 --> 4\n");
    scanf("%d",&sec);


    if ( sec == 1){
        if (temp == 'M'){
            printf("选择完成，角色初始化...\n");
            strcpy(User.mp,"少林");
            User.HP = 300;
            User.ATK = 60;
            User.Lv = 1;
            User.Speed = 10;
            User.EXP = 0;



        }else{
            printf("少林派只招收男弟子，请重新选择！\n");
            goto SEC;
        }
    }
    else if ( sec == 2){
        printf("选择完成，角色初始化...\n");
        strcpy(User.mp,"武当");
        User.HP = 200;
        User.ATK = 70;
        User.Lv = 1;
        User.Speed = 20;
        User.EXP = 0;
    }
    else if (sec == 3){
        if (temp == 'F'){
            printf("选择完成，角色初始化...\n");
            strcpy(User.mp,"峨眉");
            User.HP = 250;
            User.ATK = 70;
            User.Lv = 2;
            User.Speed = 20;
            User.EXP = 0;
        }else{
            printf("峨眉派只招收女弟子，请重新选择！\n");
            goto SEC;
        }
    }
    else if (sec == 4){
        printf("选择完成，角色初始化...\n");
        strcpy(User.mp,"丐帮");
        User.HP = 270;
        User.ATK = 65;
        User.Lv = 1;
        User.Speed = 15;
        User.EXP = 0;
    }

    sleep(1);
    printf("初始化完成\n");
    sleep(2);

}

void action(){
    printf("请选择你要进行的动作：\n");
    printf("角色信息 --> 1\n");
    printf("返回门派 --> 2\n");
    printf("江湖历练 --> 3\n");
    printf("归隐江湖 --> 4\n");
}

void myPrint(struct Role *User){
    printf("==========你的人物信息如下==========\n");
    printf("姓名: %s\n",User->name);
    printf("性别: %s\n",User->sex);
    printf("门派: %s\n",User->mp);
    printf("阅历: %d\n",User->Lv);
    printf("生命: %d\n",User->HP);
    printf("武力: %d\n",User->ATK);
    printf("身法: %d\n",User->Speed);
    printf("阅历值: %d\n",User->EXP);
    printf("==============================\n");

    sleep(1);
    system("pause");

}


// 门派板块函数
void reBack(){
    int temp;

    printf("门派场景载入中.....\n");
    sleep(2);
    printf("======返回门派: %s======\n",User.mp);

    MP:

    printf("请选择你要进入的建筑: \n");
    printf("大殿(技能学习) --> 1\n");
    printf("演武堂(装备购买) --> 2\n");
    printf("静心殿(等级提升) --> 3\n");
    printf("离开门派 --> 4\n");
    scanf("%d",&temp);

    if (temp == 1){
        if (User.Lv <= 10){
            printf("你的阅历不足，长老禁止你进入大殿！\n");
            printf("当前阅历: %d\n",User.Lv);
            sleep(2);
            goto MP;
        }

    }
    else if (temp == 2){
        shop();
    }
    else if (temp ==3){
        if (User.EXP >= User.Lv*100)
        {
            printf("你的经验值已满足升级需求！\n");
            printf("开始等级提升....\n");
            lvUp();
            sleep(2);
            printf("升级成功，你的属性增加了！\n");
            goto MP;

        }
        else{
            printf("抱歉，你的阅历值不足，请继续江湖闯荡！\n");
            sleep(2);
            goto MP;

        }
    }
    else if (temp == 4)
    {
        return;
    }
    else
    {
        printf("请输入正确的操作指令！\n");
        system("pause");
        goto MP;
    }

}

void shop(){
    printf("========装备系统载入完成========\n");
}

void lvUp(){
    /*  角色基础属性数值
     *  HP  200
     *  ATK  50
     *  Speed  10
     */

    User.EXP -= 100 * User.Lv; // 经验值减少
    User.Lv += 1;  // 升级

    User.HP += 50; // 每次升级血量增加 50
    User.ATK += 20; // 每次升级攻击增加 20
    User.Speed += 10; // 每次升级速度增加 10

}



// 冒险板块
void adv(){
    struct Monster *Head = NULL;   // 头指针
    Head = (struct Monster* )malloc(sizeof (struct Monster ));
    Head->next=NULL;
    printf("你选择踏上江湖历练之路....\n");
    sleep(1);
    printf("你当前阅历为：%d\n",User.Lv);
    system("pause");
    if (User.Lv <= 10)
    {
        advStart();
        addMonster(Head);
    }
    else if (User.Lv > 10 && User.Lv <= 30)
    {
        advStart();
        addMonster(Head);
    }

    Fight(Head);  // 传入单链表的头指针

    /*
     *  releaseMonster(&Head); // 释放内存空间
     *  释放内存有问题，会提示数据溢出
     *  待解决
     *  
     * */

    releaseMonster(Head);


}


void addMonster(struct Monster *Head)   // 尾插法添加怪物数据
{
    struct Monster *mons,*p;
    int tempATK,tempHP,tempSpeed;
    /*
     * 随机数出了问题，每只怪物的数据都一样
     * 待解决
     *
     * */
    p= Head;

    for(int i=0; i<3; i++)
    {
        mons = (struct Monster *)malloc(sizeof(struct Monster));  // 新建结构体单元，并分配内存
        if (mons == NULL)
        {
            printf("内存分配失败");
            exit(1);
        }
        if (User.Lv <= 10)
        {
            tempHP = randData(120,170);
            tempATK = randData(30,50);
            tempSpeed = randData(7,12);
            strcpy(mons->name,"发狂野兽");
        }
        else if (User.Lv >10 && User.Lv <= 30)
        {
            tempHP = randData(2000,2700);
            tempATK = randData(250,350);
            tempSpeed = randData(150,260);
            strcpy(mons->name,"日月教弟子");
        }

        mons->HP = tempHP;
        mons->ATK = tempATK;
        mons->Speed = tempSpeed;
        p->next = mons;
        p = mons;
    }
    p->next=NULL;
}

void releaseMonster(struct Monster *Head)
{
    struct Monster *temp,*p1;
    p1 = Head;
    temp = p1->next ;
    while (temp!= NULL)
    {
        p1->next= temp->next;
        free(temp);
        temp = p1->next;
    }
    free(Head);
}

int randData(int Min,int Max)
{
    static unsigned int seed = 0;
    seed++;
    int data;
    srand((unsigned)time(NULL)+seed*seed);
    data = rand()%(Max-Min+1)+Min;
    return data;

}

void Fight(struct Monster *Head)
{
    struct Monster *mons;
    mons = Head->next;

    int userHP,monHP;
    int count =1;

    while(mons != NULL)
    {

        printf("遭遇：%s%d\n",mons->name,count);
        sleep(2);

        userHP = User.HP;
        monHP = mons->HP;

        if (mons->Speed > User.Speed)
        {
            // 怪物先手攻击
            while (monHP > 0 || userHP >0)
            {
                userHP -= mons->ATK;
                if (userHP<=0)
                {
                    userHP = 0;
                }

                printf("%s%d 对你造成了 %d 点伤害，你当前剩余生命值： %d\n",mons->name,count,mons->ATK,userHP);
                if (userHP<=0)
                {
                    userHP = 0;
                    break;
                }
                sleep(2);

                monHP -= User.ATK;
                if (monHP <= 0)
                {
                    monHP = 0;
                }

                printf("你对 %s%d 造成了 %d 伤害，%s%d 当前剩余生命值： %d\n",mons->name,count,User.ATK,mons->name,count,monHP);
                if (monHP <= 0)
                {
                    monHP = 0;
                    break;
                }
                sleep(2);
            }

            if (userHP <= 0)
            {
                printf("你被 %s%d 打成重伤，慌忙逃离了现场....\n",mons->name,count);
                system("pause");
                return;
            }
            else{
                printf("你战胜了 %s%d ,获得 30 阅历值！\n",mons->name,count);
                User.EXP += 30;
                system("pause");

            }

        }
        else{
            // 角色先手攻击
            while (monHP > 0 || userHP >0)
            {
                monHP -= User.ATK;
                if (monHP <= 0)
                {
                    monHP = 0;
                }

                printf("你对 %s%d 造成了 %d 伤害，%s%d 当前剩余生命值： %d\n",mons->name,count,User.ATK,mons->name,count,monHP);
                if (monHP <= 0)
                {
                    monHP = 0;
                    break;
                }
                sleep(2);

                userHP -= mons->ATK;
                if (userHP<=0)
                {
                    userHP = 0;
                    break;
                }

                printf("%s%d 对你造成了 %d 点伤害，你当前剩余生命值： %d\n",mons->name,count,mons->ATK,userHP);
                if (userHP<=0)
                {
                    userHP = 0;
                    break;
                }

                sleep(2);

            }

            if (userHP <= 0)
            {
                printf("你被 %s%d 打成重伤，慌忙逃离了现场....\n",mons->name,count);
                system("pause");
                return;
            }
            else{
                printf("你战胜了 %s%d ,获得 30 阅历值！\n",mons->name,count);
                User.EXP += 30;
                system("pause");

            }

        }

        mons = mons->next;
        count ++;

        if (count >= 4)  // 链表无限插入？暂时没找到原因，故强制退出
        {
            break;
        }
    }

    printf("你战胜了全部的 %s,恭喜你，%s ！\n",mons->name,User.name);
    system("pause");

}


// 存档读取相关函数

/*
     *读取文件，从一行开始，信息分别是：
     * 角色名    1        文件读取时，确保编码为 ANSI，否则汉字读出乱码
     * 性别      2
     * 门派      3
     * 等级      4
     * 生命值    5
     * 攻击力    6
     * 速度      7
     * 经验值    8
     * 开始检索内容是否为空，这里开始是背包里的物品
     *
     * */

void mesSave()
{
    FILE *fp;
    char temp[64];

    if ((fp = fopen("GameData.txt","w")) == NULL )
    {
        // 文件打开异常
        exit(EXIT_FAILURE);
    }

    fputs(User.name,fp);    // 角色名
    fputs("\n",fp);    // 回车换行

    fputs(User.sex,fp);     // 角色性别
    fputs("\n",fp);    // 回车换行

    fputs(User.mp,fp);      // 角色门派
    fputs("\n",fp);    // 回车换行

    fputs(itoa(User.Lv,temp,10),fp);   // 角色等级
    fputs("\n",fp);    // 回车换行

    fputs(itoa(User.HP,temp,10),fp);   // 角色生命值
    fputs("\n",fp);    // 回车换行

    fputs(itoa(User.ATK,temp,10),fp);  // 角色攻击
    fputs("\n",fp);    // 回车换行

    fputs(itoa(User.Speed,temp,10),fp);  // 角色速度
    fputs("\n",fp);    // 回车换行

    fputs(itoa(User.EXP,temp,10),fp);  // 角色经验值
    fputs("\n",fp);    // 回车换行

    fputs("EOF\n",fp);  // 内容结束


}

void mesRead()
{
    char buf[64];
    FILE *fp;
    int len;

    if((fp = fopen("GameData.txt","r")) == NULL)
    {
        perror("文件打开失败！\n");
        exit (1) ;
    }

    if (fgets(buf,64,fp) != NULL)        // 读取角色名
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        strcpy(User.name,buf);
    }

    if (fgets(buf,64,fp) != NULL)        // 读取性别
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        strcpy(User.sex,buf);
    }

    if (fgets(buf,64,fp) != NULL)        // 读取门派
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*去掉换行符*/
        strcpy(User.mp,buf);
    }

    if (fgets(buf,64,fp) != NULL)       // 读取等级
    {
        User.Lv = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // 读取生命值
    {
        User.HP = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // 读取攻击力
    {
        User.ATK = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // 读取速度
    {
        User.Speed = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // 读取经验值
    {
        User.EXP = atoi(buf);
    }

}


/*
 * 下面的函数，都是对一些描述性信息的打印输出
 * 简化主函数的代码，增加可读性
 * */
void startPrint()
{
    printf("欢迎来到独步江湖！\n");
    sleep(1);
    printf("武林江湖正在载入....\n");
    sleep(1);
    printf("冒险元素正在添加....\n");
    sleep(1);
    printf("初始化结束，冒险开始！\n");

}

void advStart(){
    if (User.Lv <= 10)
    {
        printf("门派的炼丹房近日缺少一批灵药\n");
        sleep(1);
        printf("地点位于万界森林边缘，不会遇到太过凶猛的野兽\n");
        sleep(1);
        printf("你决定前往此处......\n");
        sleep(2);
        system("Pause");

        printf("意外还是出现了，你遭遇了百年难遇的兽潮....\n");

        sleep(2);
        system("pause");
    }
    else if(User.Lv > 10 && User.Lv <= 30)
    {
        printf("日月教今日愈发猖狂，已经隐隐在大奉周边活动....\n");
        sleep(1);
        printf("你需要去抓几个探子，知道他们潜藏的目的...\n");
        sleep(2);
        system("Pause");

        printf("你在外城地带遭遇了一只日月教小队，这是个机会....\n");

        sleep(2);
        system("pause");

    }

}