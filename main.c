#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


struct Role{
    //  ��ɫ��Ϣ��
    char name[128];  // ��ɫ��
    char sex[16];  // �Ա�
    char mp[16]; // ����
    int Lv;  // �ȼ�
    int HP;  // ����ֵ
    int ATK;  // ������
    int Speed;  // �ٶ�
    int EXP;  // ����ֵ
    char Skill[1024]; // �������

} User;

struct Pack{
    // ��Ʒ����
    int gold;  // ����

} Bag;

struct Equipment{
    int ATK; // ����������
    int HP;  // Ѫ������
    int Speed;  // �ٶ�����

}Equip;

struct Monster {                         // ���������������
    char name[64]; // ��������
    int HP;  // С��Ѫ��
    int ATK;  // С�ֹ�����
    int Speed;  //С���ٶ�
    struct Monster *next;   // ָ����һ��

};


void Start(); // ��Ϸ��ʼ��
void startPrint(); // һЩ��ʽ����������������װ

void Stop();  // ��Ϸ����

void mesSave(); // �浵
void mesRead(); // ��ȡ�浵

void rCreate(); // ��ɫ����
void action(); // ��ɫ��Ϊ
void myPrint(struct Role *role); // ��ӡ��ɫ��Ϣ,����ṹ��ָ��ķ�ʽ�����Ч��
void reBack(); // ������Ϣ

void adv(); // ����
void shop(); // װ���̵�,��������
void lvUp(); // ��������


void advStart(); // ����������
void Fight(struct Monster *Head); // ս��ϵͳ
int randData(int Min,int Max);  // ���������ֵ�������

void addMonster(struct Monster *monster);  // ��ӹ���
void releaseMonster(struct Monster *monster);  // �ͷ��ڴ�ռ�



int main() {
    int ac; // ��ɫ��Ϊ��ѡ��
    Start();

    while (1)
    {
        AC:
        action();
        scanf("%d",&ac);

        if (ac == 4){        // ������Ϸ
            Stop();
            break;
        }
        else if (ac == 1){      // �鿴��ɫ��Ϣ
            myPrint(&User);
        }
        else if (ac == 2){       // �������ɳ���
            reBack();
        }
        else if (ac == 3){      // ð�մ��
            adv();
        }
        else
        {
            printf("��������ȷ�Ĳ���ָ�\n");
            system("pause");
            goto AC;

        }

    }

    return 0;
}

// ��ɫ��Ϊ���
void Start(){
    int temp;

    startPrint();
    system("pause");

    STAR:

    printf("��ѡ����Ҫ���еĲ�����\n");
    printf("�µĿ�ʼ --> 0\n");
    printf("���ֽ��� --> 1\n");
    scanf("%d",&temp);

    if (temp == 0)
    {
        rCreate();
    }
    else if (temp == 1)
    {
        if ((access("GameData.txt",F_OK)) != -1)         // �浵�ļ��Ƿ���ڵļ��
        {
            printf("��⵽���ش浵����ʼ��������....\n");
            mesRead();
            sleep(2);
            printf("���ݼ������\n");
        }
        else{
            printf("û�м�⵽��Ϸ�浵����ѡ���µĿ�ʼ��\n");
            system("pause");
            goto STAR;
        }

    }
    else   // ���д�������Ĺ�ܣ�����GOTO ��ʡ������
    {
        printf("��������ȷ�Ĳ���ָ�\n");
        system("pause");
        goto STAR;
    }

    // ��ʼ��װ���ӳɵ���ֵ
    Equip.ATK = 0;
    Equip.Speed = 0;
    Equip.HP = 0;

    system("pause");

}

void Stop(){
    mesSave(); // �ļ������������浵
    printf("%s�����ڽ���߳����%d�����£�����ѡ����������.....\n",User.name,User.Lv);
    sleep(3);
    printf("���⽣Ӱ,Ѫ���ȷ磬Ҳ�𽥵���������Ұ.....\n");
    sleep(2);
    printf("��������Ȼ���ٻ����������Ӱ�����й����Ĵ�˵��������������.....\n");
    sleep(3);
    printf("The End?\tOr,to be continue.....");
    sleep(2);

}

void rCreate() {
    char temp;
    int sec;
    printf("========��ɫ��ʼ��========\n");

    printf("�������������(���߽���������): ");
    scanf("%s", User.name);

    printf("��ѡ������Ա�: ��(M)/Ů(F) \n");
    getchar();
    scanf("%c",&temp);

    if (temp == 'M'){
        strcpy(User.sex,"��");
    }else{
        strcpy(User.sex,"Ů");
    }

    SEC:
    printf("��ѡ���������: \n");
    printf("����(ֻ�����е���) --> 1\n");
    printf("�䵱 --> 2\n");
    printf("��ü(ֻ����Ů����) --> 3\n");
    printf("ؤ�� --> 4\n");
    scanf("%d",&sec);


    if ( sec == 1){
        if (temp == 'M'){
            printf("ѡ����ɣ���ɫ��ʼ��...\n");
            strcpy(User.mp,"����");
            User.HP = 300;
            User.ATK = 60;
            User.Lv = 1;
            User.Speed = 10;
            User.EXP = 0;



        }else{
            printf("������ֻ�����е��ӣ�������ѡ��\n");
            goto SEC;
        }
    }
    else if ( sec == 2){
        printf("ѡ����ɣ���ɫ��ʼ��...\n");
        strcpy(User.mp,"�䵱");
        User.HP = 200;
        User.ATK = 70;
        User.Lv = 1;
        User.Speed = 20;
        User.EXP = 0;
    }
    else if (sec == 3){
        if (temp == 'F'){
            printf("ѡ����ɣ���ɫ��ʼ��...\n");
            strcpy(User.mp,"��ü");
            User.HP = 250;
            User.ATK = 70;
            User.Lv = 2;
            User.Speed = 20;
            User.EXP = 0;
        }else{
            printf("��ü��ֻ����Ů���ӣ�������ѡ��\n");
            goto SEC;
        }
    }
    else if (sec == 4){
        printf("ѡ����ɣ���ɫ��ʼ��...\n");
        strcpy(User.mp,"ؤ��");
        User.HP = 270;
        User.ATK = 65;
        User.Lv = 1;
        User.Speed = 15;
        User.EXP = 0;
    }

    sleep(1);
    printf("��ʼ�����\n");
    sleep(2);

}

void action(){
    printf("��ѡ����Ҫ���еĶ�����\n");
    printf("��ɫ��Ϣ --> 1\n");
    printf("�������� --> 2\n");
    printf("�������� --> 3\n");
    printf("�������� --> 4\n");
}

void myPrint(struct Role *User){
    printf("==========���������Ϣ����==========\n");
    printf("����: %s\n",User->name);
    printf("�Ա�: %s\n",User->sex);
    printf("����: %s\n",User->mp);
    printf("����: %d\n",User->Lv);
    printf("����: %d\n",User->HP);
    printf("����: %d\n",User->ATK);
    printf("��: %d\n",User->Speed);
    printf("����ֵ: %d\n",User->EXP);
    printf("==============================\n");

    sleep(1);
    system("pause");

}


// ���ɰ�麯��
void reBack(){
    int temp;

    printf("���ɳ���������.....\n");
    sleep(2);
    printf("======��������: %s======\n",User.mp);

    MP:

    printf("��ѡ����Ҫ����Ľ���: \n");
    printf("���(����ѧϰ) --> 1\n");
    printf("������(װ������) --> 2\n");
    printf("���ĵ�(�ȼ�����) --> 3\n");
    printf("�뿪���� --> 4\n");
    scanf("%d",&temp);

    if (temp == 1){
        if (User.Lv <= 10){
            printf("����������㣬���Ͻ�ֹ������\n");
            printf("��ǰ����: %d\n",User.Lv);
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
            printf("��ľ���ֵ��������������\n");
            printf("��ʼ�ȼ�����....\n");
            lvUp();
            sleep(2);
            printf("�����ɹ���������������ˣ�\n");
            goto MP;

        }
        else{
            printf("��Ǹ���������ֵ���㣬���������������\n");
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
        printf("��������ȷ�Ĳ���ָ�\n");
        system("pause");
        goto MP;
    }

}

void shop(){
    printf("========װ��ϵͳ�������========\n");
}

void lvUp(){
    /*  ��ɫ����������ֵ
     *  HP  200
     *  ATK  50
     *  Speed  10
     */

    User.EXP -= 100 * User.Lv; // ����ֵ����
    User.Lv += 1;  // ����

    User.HP += 50; // ÿ������Ѫ������ 50
    User.ATK += 20; // ÿ�������������� 20
    User.Speed += 10; // ÿ�������ٶ����� 10

}



// ð�հ��
void adv(){
    struct Monster *Head = NULL;   // ͷָ��
    Head = (struct Monster* )malloc(sizeof (struct Monster ));
    Head->next=NULL;
    printf("��ѡ��̤�Ͻ�������֮·....\n");
    sleep(1);
    printf("�㵱ǰ����Ϊ��%d\n",User.Lv);
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

    Fight(Head);  // ���뵥�����ͷָ��

    /*
     *  releaseMonster(&Head); // �ͷ��ڴ�ռ�
     *  �ͷ��ڴ������⣬����ʾ�������
     *  �����
     *  
     * */

    releaseMonster(Head);


}


void addMonster(struct Monster *Head)   // β�巨��ӹ�������
{
    struct Monster *mons,*p;
    int tempATK,tempHP,tempSpeed;
    /*
     * ������������⣬ÿֻ��������ݶ�һ��
     * �����
     *
     * */
    p= Head;

    for(int i=0; i<3; i++)
    {
        mons = (struct Monster *)malloc(sizeof(struct Monster));  // �½��ṹ�嵥Ԫ���������ڴ�
        if (mons == NULL)
        {
            printf("�ڴ����ʧ��");
            exit(1);
        }
        if (User.Lv <= 10)
        {
            tempHP = randData(120,170);
            tempATK = randData(30,50);
            tempSpeed = randData(7,12);
            strcpy(mons->name,"����Ұ��");
        }
        else if (User.Lv >10 && User.Lv <= 30)
        {
            tempHP = randData(2000,2700);
            tempATK = randData(250,350);
            tempSpeed = randData(150,260);
            strcpy(mons->name,"���½̵���");
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

        printf("������%s%d\n",mons->name,count);
        sleep(2);

        userHP = User.HP;
        monHP = mons->HP;

        if (mons->Speed > User.Speed)
        {
            // �������ֹ���
            while (monHP > 0 || userHP >0)
            {
                userHP -= mons->ATK;
                if (userHP<=0)
                {
                    userHP = 0;
                }

                printf("%s%d ��������� %d ���˺����㵱ǰʣ������ֵ�� %d\n",mons->name,count,mons->ATK,userHP);
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

                printf("��� %s%d ����� %d �˺���%s%d ��ǰʣ������ֵ�� %d\n",mons->name,count,User.ATK,mons->name,count,monHP);
                if (monHP <= 0)
                {
                    monHP = 0;
                    break;
                }
                sleep(2);
            }

            if (userHP <= 0)
            {
                printf("�㱻 %s%d ������ˣ���æ�������ֳ�....\n",mons->name,count);
                system("pause");
                return;
            }
            else{
                printf("��սʤ�� %s%d ,��� 30 ����ֵ��\n",mons->name,count);
                User.EXP += 30;
                system("pause");

            }

        }
        else{
            // ��ɫ���ֹ���
            while (monHP > 0 || userHP >0)
            {
                monHP -= User.ATK;
                if (monHP <= 0)
                {
                    monHP = 0;
                }

                printf("��� %s%d ����� %d �˺���%s%d ��ǰʣ������ֵ�� %d\n",mons->name,count,User.ATK,mons->name,count,monHP);
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

                printf("%s%d ��������� %d ���˺����㵱ǰʣ������ֵ�� %d\n",mons->name,count,mons->ATK,userHP);
                if (userHP<=0)
                {
                    userHP = 0;
                    break;
                }

                sleep(2);

            }

            if (userHP <= 0)
            {
                printf("�㱻 %s%d ������ˣ���æ�������ֳ�....\n",mons->name,count);
                system("pause");
                return;
            }
            else{
                printf("��սʤ�� %s%d ,��� 30 ����ֵ��\n",mons->name,count);
                User.EXP += 30;
                system("pause");

            }

        }

        mons = mons->next;
        count ++;

        if (count >= 4)  // �������޲��룿��ʱû�ҵ�ԭ�򣬹�ǿ���˳�
        {
            break;
        }
    }

    printf("��սʤ��ȫ���� %s,��ϲ�㣬%s ��\n",mons->name,User.name);
    system("pause");

}


// �浵��ȡ��غ���

/*
     *��ȡ�ļ�����һ�п�ʼ����Ϣ�ֱ��ǣ�
     * ��ɫ��    1        �ļ���ȡʱ��ȷ������Ϊ ANSI�������ֶ�������
     * �Ա�      2
     * ����      3
     * �ȼ�      4
     * ����ֵ    5
     * ������    6
     * �ٶ�      7
     * ����ֵ    8
     * ��ʼ���������Ƿ�Ϊ�գ����￪ʼ�Ǳ��������Ʒ
     *
     * */

void mesSave()
{
    FILE *fp;
    char temp[64];

    if ((fp = fopen("GameData.txt","w")) == NULL )
    {
        // �ļ����쳣
        exit(EXIT_FAILURE);
    }

    fputs(User.name,fp);    // ��ɫ��
    fputs("\n",fp);    // �س�����

    fputs(User.sex,fp);     // ��ɫ�Ա�
    fputs("\n",fp);    // �س�����

    fputs(User.mp,fp);      // ��ɫ����
    fputs("\n",fp);    // �س�����

    fputs(itoa(User.Lv,temp,10),fp);   // ��ɫ�ȼ�
    fputs("\n",fp);    // �س�����

    fputs(itoa(User.HP,temp,10),fp);   // ��ɫ����ֵ
    fputs("\n",fp);    // �س�����

    fputs(itoa(User.ATK,temp,10),fp);  // ��ɫ����
    fputs("\n",fp);    // �س�����

    fputs(itoa(User.Speed,temp,10),fp);  // ��ɫ�ٶ�
    fputs("\n",fp);    // �س�����

    fputs(itoa(User.EXP,temp,10),fp);  // ��ɫ����ֵ
    fputs("\n",fp);    // �س�����

    fputs("EOF\n",fp);  // ���ݽ���


}

void mesRead()
{
    char buf[64];
    FILE *fp;
    int len;

    if((fp = fopen("GameData.txt","r")) == NULL)
    {
        perror("�ļ���ʧ�ܣ�\n");
        exit (1) ;
    }

    if (fgets(buf,64,fp) != NULL)        // ��ȡ��ɫ��
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*ȥ�����з�*/
        strcpy(User.name,buf);
    }

    if (fgets(buf,64,fp) != NULL)        // ��ȡ�Ա�
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*ȥ�����з�*/
        strcpy(User.sex,buf);
    }

    if (fgets(buf,64,fp) != NULL)        // ��ȡ����
    {
        len = strlen(buf);
        buf[len-1] = '\0';  /*ȥ�����з�*/
        strcpy(User.mp,buf);
    }

    if (fgets(buf,64,fp) != NULL)       // ��ȡ�ȼ�
    {
        User.Lv = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // ��ȡ����ֵ
    {
        User.HP = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // ��ȡ������
    {
        User.ATK = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // ��ȡ�ٶ�
    {
        User.Speed = atoi(buf);
    }

    if (fgets(buf,64,fp) != NULL)       // ��ȡ����ֵ
    {
        User.EXP = atoi(buf);
    }

}


/*
 * ����ĺ��������Ƕ�һЩ��������Ϣ�Ĵ�ӡ���
 * ���������Ĵ��룬���ӿɶ���
 * */
void startPrint()
{
    printf("��ӭ��������������\n");
    sleep(1);
    printf("���ֽ�����������....\n");
    sleep(1);
    printf("ð��Ԫ���������....\n");
    sleep(1);
    printf("��ʼ��������ð�տ�ʼ��\n");

}

void advStart(){
    if (User.Lv <= 10)
    {
        printf("���ɵ�����������ȱ��һ����ҩ\n");
        sleep(1);
        printf("�ص�λ�����ɭ�ֱ�Ե����������̫�����͵�Ұ��\n");
        sleep(1);
        printf("�����ǰ���˴�......\n");
        sleep(2);
        system("Pause");

        printf("���⻹�ǳ����ˣ��������˰����������޳�....\n");

        sleep(2);
        system("pause");
    }
    else if(User.Lv > 10 && User.Lv <= 30)
    {
        printf("���½̽������������Ѿ������ڴ���ܱ߻....\n");
        sleep(1);
        printf("����Ҫȥץ����̽�ӣ�֪������Ǳ�ص�Ŀ��...\n");
        sleep(2);
        system("Pause");

        printf("������ǵش�������һֻ���½�С�ӣ����Ǹ�����....\n");

        sleep(2);
        system("pause");

    }

}