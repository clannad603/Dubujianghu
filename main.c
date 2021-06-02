#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


struct Role {
    //  ��ɫ��Ϣ��
    char name[128];  // ��ɫ��
    char sex[16];  // �Ա�
    char mp[16]; // ����
    int Lv;  // �ȼ�
    int HP;  // ����ֵ
    int ATK;  // ������
    int Speed;  // �ٶ�
    int EXP;  // ����ֵ
    char Skill[20]; // �������

} user;

struct Pack {
    // ��Ʒ����
    int gold;  // ����

} bag;

struct Equipment {
    int ATK; // ����������
    int HP;  // Ѫ������
    int Speed;  // �ٶ�����
} equip;

struct Monster {                         // ���������������
    char name[64]; // ��������
    int HP;  // С��Ѫ��
    int ATK;  // С�ֹ�����
    int Speed;  //С���ٶ�
    struct Monster *next;   // ָ����һ��

};


void start(); // ��Ϸ��ʼ��
void startPrint(); // һЩ��ʽ����������������װ

void stop();  // ��Ϸ����

void mesSave(); // �浵
void mesRead(); // ��ȡ�浵

void rCreate(); // ��ɫ����
void action(); // ��ɫ��Ϊ
void myPrint(struct Role *role); // ��ӡ��ɫ��Ϣ,����ṹ��ָ��ķ�ʽ�����Ч��
void reBack(); // ������Ϣ
void addSkill();//��Ӽ���
void adv(); // ����
void shop(); // װ���̵�,��������
void lvUp(); // ��������

void advStart(); // ����������
void fight(struct Monster *Head); // ս��ϵͳ
int randData(int Min, int Max);  // ���������ֵ�������

void addMonster(struct Monster *monster);  // ��ӹ���
void releaseMonster(struct Monster *monster);  // �ͷ��ڴ�ռ�
void wearEquip();

int rank = 1;//��¼��ֲ��������Ų������ӣ���Ҳ��Խ��Խǿ
int main() {
    int ac; // ��ɫ��Ϊ��ѡ��
    start();

    while (1) {
        action();
        scanf("%d", &ac);
        wearEquip();
        if (ac == 4) {        // ������Ϸ
            stop();
            break;
        } else if (ac == 1) {      // �鿴��ɫ��Ϣ
            myPrint(&user);
        } else if (ac == 2) {       // �������ɳ���
            reBack();

        } else if (ac == 3) {      // ð�մ��
            adv();

        } else {
            printf("��������ȷ�Ĳ���ָ�\n");
            system("pause");

        }

    }

    return 0;
}

//����װ��
void wearEquip() {
    user.Speed += equip.Speed;
    user.HP += equip.HP;
    user.ATK += equip.ATK;
}

// ��ɫ��Ϊ���
void start() {
    int temp;

    startPrint();
    system("pause");
    while (1) {
        printf("��ѡ����Ҫ���еĲ�����\n");
        printf("�µĿ�ʼ --> 0\n");
        printf("���ֽ��� --> 1\n");
        scanf("%d", &temp);

        if (temp == 0) {
            rCreate();
            break;
        } else if (temp == 1) {
            if ((access("GameData.txt", F_OK)) != -1)         // �浵�ļ��Ƿ���ڵļ��
            {
                printf("��⵽���ش浵����ʼ��������....\n");
                mesRead();
                sleep(2);
                printf("���ݼ������\n");
                break;
            } else {
                printf("û�м�⵽��Ϸ�浵����ѡ���µĿ�ʼ��\n");
                system("pause");
            }
        } else {
            printf("��������ȷ�Ĳ���ָ�\n");
            system("pause");
        }
    }
    // ��ʼ��װ���ӳɵ���ֵ
    equip.ATK = 0;
    equip.Speed = 0;
    equip.HP = 0;
    system("pause");
}

void stop() {
    mesSave(); // �ļ������������浵
    printf("%s�����ڽ���߳����%d�����£�����ѡ����������.....\n", user.name, user.Lv);
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
    scanf("%s", user.name);

    printf("��ѡ������Ա�: ��(M)/Ů(F) \n");
    getchar();
    scanf("%c", &temp);

    if (temp == 'M') {
        strcpy(user.sex, "��");
    } else {
        strcpy(user.sex, "Ů");
    }

    while (1) {
        printf("��ѡ���������: \n");
        printf("����(ֻ�����е���) --> 1\n");
        printf("�䵱 --> 2\n");
        printf("��ü(ֻ����Ů����) --> 3\n");
        printf("ؤ�� --> 4\n");
        scanf("%d", &sec);
        if (sec == 1) {
            if (temp == 'M') {
                printf("ѡ����ɣ���ɫ��ʼ��...\n");
                strcpy(user.mp, "����");
                user.HP = 300;
                user.ATK = 60;
                user.Lv = 1;
                user.Speed = 10;
                user.EXP = 0;

                break;
            } else {
                printf("������ֻ�����е��ӣ�������ѡ��\n");
            }
        } else if (sec == 2) {
            printf("ѡ����ɣ���ɫ��ʼ��...\n");
            strcpy(user.mp, "�䵱");
            user.HP = 200;
            user.ATK = 70;
            user.Lv = 1;
            user.Speed = 20;
            user.EXP = 0;
            break;
        } else if (sec == 3) {
            if (temp == 'F') {
                printf("ѡ����ɣ���ɫ��ʼ��...\n");
                strcpy(user.mp, "��ü");
                user.HP = 250;
                user.ATK = 70;
                user.Lv = 2;
                user.Speed = 20;
                user.EXP = 0;
                break;
            } else {
                printf("��ü��ֻ����Ů���ӣ�������ѡ��\n");

            }
        } else if (sec == 4) {
            printf("ѡ����ɣ���ɫ��ʼ��...\n");
            strcpy(user.mp, "ؤ��");
            user.HP = 270;
            user.ATK = 65;
            user.Lv = 1;
            user.Speed = 15;
            user.EXP = 0;
            break;
        }
    }
    sleep(1);
    printf("��ʼ�����\n");
    sleep(2);

}

void action() {
    printf("��ѡ����Ҫ���еĶ�����\n");
    printf("��ɫ��Ϣ --> 1\n");
    printf("�������� --> 2\n");
    printf("�������� --> 3\n");
    printf("�������� --> 4\n");
}

void myPrint(struct Role *User) {
    printf("==========���������Ϣ����==========\n");
    printf("����: %s\n", User->name);
    printf("�Ա�: %s\n", User->sex);
    printf("����: %s\n", User->mp);
    printf("����: %d\n", User->Lv);
    printf("����: %d\n", User->HP);
    printf("����: %d\n", User->ATK);
    printf("��: %d\n", User->Speed);
    printf("����ֵ: %d\n", User->EXP);
    printf("����: %s\n", User->Skill);

    printf("==============================\n");

    sleep(1);
    system("pause");

}

void addSkill() {
    printf("��ӭ���뼼��ѧϰ����\n");
    printf("�����ڿ���ѧϰ���¼���\n");
    printf("1.�񱩼���->ûɶ�õļ�20����\n");
    printf("2.�̻�����->�ܵ��˺�����30%\n");
    printf("3.���һ����Ѫ->Ѫ����ʱ��100\n");
    int c;
    scanf("%d", &c);
    switch (c) {
        case 1:
            printf("�����˿񱩼���\n");
            strcpy(user.Skill, "��");
            break;
        case 2:
            printf("�����˹̻�����\n");
            strcpy(user.Skill, "�̻�");
            break;
        case 3:
            printf("������Ѫ����\n");
            strcpy(user.Skill, "Ѫ��");
            break;
    }


}

// ���ɰ�麯��
void reBack() {
    int temp;

    printf("���ɳ���������.....\n");
    sleep(2);
    printf("======��������: %s======\n", user.mp);

    while (1) {

        printf("��ѡ����Ҫ����Ľ���: \n");
        printf("���(����ѧϰ) --> 1\n");
        printf("������(װ������) --> 2\n");
        printf("���ĵ�(�ȼ�����) --> 3\n");
        printf("�뿪���� --> 4\n");
        scanf("%d", &temp);

        if (temp == 1) {
            if (user.Lv <=3) {
                printf("����������㣬���Ͻ�ֹ������\n");
                printf("��ǰ����: %d\n", user.Lv);
                sleep(2);
            } else {
                addSkill();
            }

        } else if (temp == 2) {
            shop();
        } else if (temp == 3) {
            if (user.EXP >= user.Lv * 100) {
                printf("��ľ���ֵ��������������\n");
                printf("��ʼ�ȼ�����....\n");
                lvUp();
                sleep(2);
                printf("�����ɹ���������������ˣ�\n");


            } else {
                printf("��Ǹ���������ֵ���㣬���������������\n");
                sleep(2);


            }
        } else if (temp == 4) {
            return;
        } else {
            printf("��������ȷ�Ĳ���ָ�\n");
            system("pause");

        }
    }
}

void shop() {
    printf("========װ��ϵͳ�������========\n");
    printf("������������װ��\n");
    printf("�͹٣������˶���Ǯ��\n");
    printf("�Ҵ���%d������\n", bag.gold);
    int choice;
    while (1) {
        int flag = 0;
        printf("1.������С��,50��\n");
        printf("2.��ħ�˵�С��,100��\n");
        printf("3.�ܺ��Ѫ��ʯ,50��\n");
        printf("4.�ȽϿ��Ь��,100��\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if (bag.gold > 50) {
                    equip.ATK += 10;
                    flag = 1;
                    bag.gold -= 50;
                } else {
                    printf("Ǯ���������᣿\n");
                }
                break;
            case 2:
                if (bag.gold > 100) {
                    equip.ATK += 50;
                    flag = 1;
                    bag.gold -= 100;
                } else {
                    printf("Ǯ���������᣿\n");
                }
                break;
            case 3:
                if (bag.gold > 50) {
                    equip.HP += 10;
                    flag = 1;
                    bag.gold -= 50;
                } else {
                    printf("Ǯ���������᣿\n");
                }
                break;
            case 4:
                if (bag.gold > 100) {
                    equip.Speed += 10;
                    flag = 1;
                    bag.gold -= 100;
                } else {
                    printf("Ǯ���������᣿\n");
                }
                break;
        }
        if (flag) {
            printf("����ʣ%d������\n", bag.gold);
            printf("����,�´�����\n");
            break;
        }
    }

}

void lvUp() {
    /*  ��ɫ����������ֵ
     *  HP  200
     *  ATK  50
     *  Speed  10
     */

    user.EXP -= 100 * user.Lv; // ����ֵ����
    user.Lv += 1;  // ����

    user.HP += 50; // ÿ������Ѫ������ 50
    user.ATK += 20; // ÿ�������������� 20
    user.Speed += 10; // ÿ�������ٶ����� 10

}


// ð�հ��
void adv() {
    struct Monster *Head = NULL;   // ͷָ��
    Head = (struct Monster *) malloc(sizeof(struct Monster));
    Head->next = NULL;
    printf("��ѡ��̤�Ͻ�������֮·....\n");
    sleep(1);
    printf("�㵱ǰ����Ϊ��%d\n", user.Lv);
    system("pause");
    if (user.Lv <= 10) {
        advStart();
        addMonster(Head);
    } else if (user.Lv > 10 && user.Lv <= 30) {
        advStart();
        addMonster(Head);
    }

    fight(Head);  // ���뵥�����ͷָ��

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
    struct Monster *mons, *p;
    int tempATK, tempHP, tempSpeed;
    /*
     * ������������⣬ÿֻ��������ݶ�һ��
     * �����
     *
     * */
    p = Head;
    int random = 0;
    random = randData(1, 5);
    for (int i = 0; i < random; i++) {
        mons = (struct Monster *) malloc(sizeof(struct Monster));  // �½��ṹ�嵥Ԫ���������ڴ�
        if (mons == NULL) {
            printf("�ڴ����ʧ��");
            exit(1);
        }
        if (user.Lv <= 5 && random != 2) {
            tempHP = randData(120 + rank, 170 + rank);
            tempATK = randData(30 + rank % 10, 50 + rank % 10);
            tempSpeed = randData(7 + rank % 5, 12 + rank % 5);
            strcpy(mons->name, "����Ұ��");
        } else if ((user.Lv > 5 && user.Lv <= 10) || random == 2) {
            tempHP = randData(2000 + rank, 2700 + rank);
            tempATK = randData(250 + rank % 10, 350 + rank % 10);
            tempSpeed = randData(150 + rank % 5, 260 + rank % 5);
            strcpy(mons->name, "���½̵���");
        }

        mons->HP = tempHP;
        mons->ATK = tempATK;
        mons->Speed = tempSpeed;
        p->next = mons;
        p = mons;
    }
    p->next = NULL;
}

void releaseMonster(struct Monster *Head) {
    struct Monster *temp, *p1;
    p1 = Head;
    temp = p1->next;
    while (temp != NULL) {
        p1->next = temp->next;
        free(temp);
        temp = p1->next;
    }
    free(Head);
}

int randData(int Min, int Max) {
    static unsigned int seed = 0;
    seed++;
    int data;
    srand((unsigned) time(NULL) + seed * seed);
    data = rand() % (Max - Min + 1) + Min;
    //���������Сֵ
    return data;
    /***
     * ������ʹ��һ����̬�������������ӽ��в������������������ڳ��������󣬻�ȡ��������̶�
     */
}

void fight(struct Monster *Head) {
    struct Monster *mons;
    mons = Head->next;
    int userHP, monHP;
    int count = 1;
    int userAtk = user.ATK;
    int hash;
    userHP = user.HP;
    hash = randData(1, 5);
    if (hash == 1) {
        printf("�����Ӻ�����������䣬����˺�������\n");
        user.ATK -=30;
        sleep(1);
    }
    if (hash == 2) {
        printf("�˴�������֮��������˺������30%�����\n");
        user.ATK = userAtk * (1.3);
        sleep(1);
    }
    if (hash == 3) {
        printf("�˴������ر��䣬��������%d\n", randData(rank * 10, rank * 12));
        sleep(2);
    }
    while (mons != NULL) {
        monHP = mons->HP;
        int has;
        has = randData(4,6);
         if ((strcasecmp(user.Skill, "��") == 0)&&has==4) {
             printf("�������ܿ�\n");
             user.ATK=user.ATK*1.3;
         }
         if ((strcasecmp(user.Skill, "�̻�") == 0)&&has==5) {
             printf("�������ܹ̻�\n");
             mons->ATK=mons->ATK*0.7;
         }
        if ((strcasecmp(user.Skill, "Ѫ��") == 0)&&has==5) {
            printf("��������Ѫ��\n");
            userHP += 100;
        }
        printf("������%s%d\n", mons->name, count);
        sleep(2);

        if (user.Speed - mons->Speed >= 50) {
            printf("�����ٶ�̫��,�ָ����򲻶��㣬��ֱ�ӱ�Եop����\n");
            break;
        }
        if (mons->Speed > user.Speed) {
            // �������ֹ���
            while (monHP > 0 || userHP > 0) {
                int rand;
                rand = randData(1, 3);
                userHP -= mons->ATK;
                if (userHP <= 0) {
                    userHP = 0;
                }
                if (rand == 1) {
                    printf("�������ô�����Ĺ��Ӻ�������\n");
                    mons->ATK += 100;
                }
                printf("%s%d ��������� %d ���˺����㵱ǰʣ������ֵ�� %d\n", mons->name, count, mons->ATK, userHP);
                if (userHP <= 0) {
                    userHP = 0;
                    break;
                }
                sleep(2);

                monHP -= user.ATK;
                if (monHP <= 0) {
                    monHP = 0;
                }

                printf("��� %s%d ����� %d �˺���%s%d ��ǰʣ������ֵ�� %d\n", mons->name, count, user.ATK, mons->name, count, monHP);
                if (monHP <= 0) {
                    monHP = 0;
                    break;
                }
                sleep(2);
            }

            if (userHP <= 0) {
                printf("�㱻 %s%d ������ˣ���æ�������ֳ�....\n", mons->name, count);
                system("pause");
                return;
            } else {
                printf("��սʤ�� %s%d ,��� 30 ����ֵ��\n", mons->name, count);
                user.EXP += 30;
                system("pause");

            }

        } else {
            // ��ɫ���ֹ���
            while (monHP > 0 || userHP > 0) {
                int rand;
                rand = randData(1, 3);
                monHP -= user.ATK;
                if (monHP <= 0) {
                    monHP = 0;
                }
                if (rand == 1) {
                    printf("�������ô�����Ĺ��Ӻ�������\n");
                    mons->ATK += 30;
                }
                printf("��� %s%d ����� %d �˺���%s%d ��ǰʣ������ֵ�� %d\n", mons->name, count, user.ATK, mons->name, count, monHP);
                if (monHP <= 0) {
                    monHP = 0;
                    break;
                }
                sleep(2);

                userHP -= mons->ATK;
                if (userHP <= 0) {
                    userHP = 0;
                    break;
                }

                printf("%s%d ��������� %d ���˺����㵱ǰʣ������ֵ�� %d\n", mons->name, count, mons->ATK, userHP);
                if (userHP <= 0) {
                    userHP = 0;
                    break;
                }

                sleep(2);

            }

            if (userHP <= 0) {
                printf("�㱻 %s%d ������ˣ���æ�������ֳ�....\n", mons->name, count);
                system("pause");
                return;
            } else {
                printf("��սʤ��%s%d ,��� 30 ����ֵ��\n", mons->name, count);
                user.EXP += 30;
                system("pause");
            }

        }

        mons = mons->next;
        count++;

    }
    user.ATK = userAtk;
    printf("��սʤ��ȫ���Ĺ�,��ϲ�㣬%s ��\n", user.name);
    bag.gold += randData(100, 200);
    printf("������%d��ûʲô�õ�����\n", bag.gold);
    rank += 10;
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

void mesSave() {
    FILE *fp;
    char temp[64];

    if ((fp = fopen("GameData.txt", "w")) == NULL) {
        // �ļ����쳣
        exit(EXIT_FAILURE);
    }

    fputs(user.name, fp);    // ��ɫ��
    fputs("\n", fp);    // �س�����

    fputs(user.sex, fp);     // ��ɫ�Ա�
    fputs("\n", fp);    // �س�����

    fputs(user.mp, fp);      // ��ɫ����
    fputs("\n", fp);    // �س�����

    fputs(itoa(user.Lv, temp, 10), fp);   // ��ɫ�ȼ�
    fputs("\n", fp);    // �س�����

    fputs(itoa(user.HP - equip.HP, temp, 10), fp);   // ��ɫ����ֵ
    fputs("\n", fp);    // �س�����

    fputs(itoa(user.ATK - equip.ATK, temp, 10), fp);  // ��ɫ����
    fputs("\n", fp);    // �س�����

    fputs(itoa(user.Speed - equip.Speed, temp, 10), fp);  // ��ɫ�ٶ�
    fputs("\n", fp);    // �س�����

    fputs(itoa(user.EXP, temp, 10), fp);  // ��ɫ����ֵ
    fputs("\n", fp);    // �س�����

    fputs(itoa(bag.gold, temp, 10), fp);  // ��ɫǮ
    fputs("\n", fp);    // �س�����

    fputs(user.Skill, fp);  // ��ɫ����
    fputs("\n", fp);    // �س�����

    fputs("EOF\n", fp);  // ���ݽ���


}

void mesRead() {
    char buf[64];
    FILE *fp;
    int len;

    if ((fp = fopen("GameData.txt", "r")) == NULL) {
        perror("�ļ���ʧ�ܣ�\n");
        exit(1);
    }

    if (fgets(buf, 64, fp) != NULL)        // ��ȡ��ɫ��
    {
        len = strlen(buf);
        buf[len - 1] = '\0';  /*ȥ�����з�*/
        strcpy(user.name, buf);
    }

    if (fgets(buf, 64, fp) != NULL)        // ��ȡ�Ա�
    {
        len = strlen(buf);
        buf[len - 1] = '\0';  /*ȥ�����з�*/
        strcpy(user.sex, buf);
    }

    if (fgets(buf, 64, fp) != NULL)        // ��ȡ����
    {
        len = strlen(buf);
        buf[len - 1] = '\0';  /*ȥ�����з�*/
        strcpy(user.mp, buf);
    }

    if (fgets(buf, 64, fp) != NULL)       // ��ȡ�ȼ�
    {
        user.Lv = atoi(buf);
    }

    if (fgets(buf, 64, fp) != NULL)       // ��ȡ����ֵ
    {
        user.HP = atoi(buf);
    }

    if (fgets(buf, 64, fp) != NULL)       // ��ȡ������
    {
        user.ATK = atoi(buf);
    }

    if (fgets(buf, 64, fp) != NULL)       // ��ȡ�ٶ�
    {
        user.Speed = atoi(buf);
    }

    if (fgets(buf, 64, fp) != NULL)       // ��ȡ����ֵ
    {
        user.EXP = atoi(buf);
    }
    if (fgets(buf, 64, fp) != NULL)       // ��ȡǮ
    {
        bag.gold = atoi(buf);
    }
    if (fgets(buf, 64, fp) != NULL)       // ��ȡǮ
    {
        strcpy(user.Skill,buf);
    }
}


/*
 * ����ĺ��������Ƕ�һЩ��������Ϣ�Ĵ�ӡ���
 * ���������Ĵ��룬���ӿɶ���
 * */
void startPrint() {
    printf("��ӭ��������������\n");
    sleep(1);
    printf("���ֽ�����������....\n");
    sleep(1);
    printf("ð��Ԫ���������....\n");
    sleep(1);
    printf("��ʼ��������ð�տ�ʼ��\n");

}

void advStart() {
    if (user.Lv <= 5) {
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
    } else if (user.Lv > 5 && user.Lv <= 10) {
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
