#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<conio.h>
#include<memory.h>
#include<windows.h>
void ini();         // �����ʼ�����������������
void first();       // ��ʼ�������������� һ����Ϊ2����һ��2��4������Ϊ4:1
void page();        // ��Ϸҳ��
void color(int m);  // �޸������д����ɫ

//�����ƶ�����
void move_left();
void move_up();
void move_right();
void move_down();

void random();	    // ����2��4��������ұ���Ϊ4:1

void check();       // ����Ƿ������Ϸ�����ý�����Ϸ��־
int game_blank();   // ��ȡ��ֵ����

int map[4][4];          // ����4��4�еĶ�ά����
int score = 0;          // ��Ϸ�÷�
int blank;              // �Ƿ��п�λ��־��0�����ޣ�1������
int need_add_num;       // �Ƿ���Ҫ�����������־��1��ʾ��Ҫ��0��ʾ����Ҫ
int if_game_over;       // �Ƿ���Ϸ������־��1��ʾ��Ϸ������0��ʾ����

int main()
{
    char cmd;
    ini();                // �����ʼ�����������������
    first();              // ��ʼ�������������� һ����Ϊ2����һ��2��4������Ϊ4:1
    while(1)
    {
        need_add_num = 0;      // ���趨��Ĭ����Ҫ�������������Ҫʱ���趨Ϊ1
        page();                // ��Ϸҳ��
        cmd = getch();         // ���ռ�����������                         
        switch (cmd)
        {
            case 'w':
            case 'W': move_up(); break;
            case 's':
            case 'S': move_down(); break;
            case 'a':
            case 'A': move_left(); break;
            case 'd':
            case 'D': move_right(); break;
        }
        if (need_add_num)                // ���������
        {
            random();
        }
        if (game_blank() == 0)           // ��ֵ����Ϊ0�ͼ���Ƿ�������Ԫ�����
        {
            check();
        }
        if (if_game_over)                // ��Ϸ�����������Ϸҳ��ͷ���
        {
            page();
            color(4);
            printf("\n\n            ��Ϸ����,������շ���Ϊ:%d\n", score);
            system("pause");
            return 0;
        }
    }
}

// �����Ϸ�Ƿ���� 
void check()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            // ���������Ƚϰ��ŵ�����Ԫ���Ƿ���ȣ������������Ϸ������
            if (map[i][j] == map[i][j+1] || map[j][i] == map[j+1][i])
            {
                if_game_over = 0;
                return;
            }
        }
    }
    if_game_over = 1;
}

// ��������� 
void random()							
{
	int i, j;
	do
	{
		i = rand() % 4;
		j = rand() % 4;
	} while (map[i][j] != 0);               //����ҵ�ֵΪ0��i��j��

	map[i][j] = rand() % 5 ? 2 : 4;         //����ֵΪ2��4������Ϊ4:1

}

// ��ȡ��ֵ���� 
int game_blank()
{
    int n = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            n += (map[i][j] == 0 ? 1 : 0);
        }
    }
    return n;
}

// ������ 
void move_left()
{
    // ����i��������������±�
	for (int i = 0; i < 4; i++)
	{
		// ����jΪ���±꣬����kΪ(���Ƚ�)/(�ϲ�)����±� 
		for (int j = 1, k = 0; j < 4; j++)
		{
			if (map[i][j] > 0) // �ҳ�k�����һ����Ϊ�յ���±�Ϊj��֮����������
			{
				if (map[i][k] == map[i][j]) // ���1��k���j����ȣ���ʱ�ϲ����鲢�Ʒ�
				{
                    map[i][k] *= 2;
                    score += map[i][k]; 
                    k++;
					map[i][j] = 0;
					need_add_num = 1; // ��Ҫ���������
				}
				else if (map[i][k] == 0) // ���2��k��Ϊ�գ����j�ֵ��k��൱��j�����ƶ���k����
				{
					map[i][k] = map[i][j];
					map[i][j] = 0;
					need_add_num = 1;
				}
				else // ���3��k�Ϊ�գ��Һ�j���ȣ���ʱ��j�ֵ��k+1��൱���ƶ���k+1��λ�� 
				{
					map[i][++k] = map[i][j];
					if (j != k) // �ж�j���k���Ƿ�ԭ�ȾͰ���һ�����������j�ֵΪ�գ�ֵΪ0��
					{
						map[i][j] = 0;
						need_add_num = 1;
					}
				}
			}
        }
    }
}

void move_up()
{
    // д�����������ƣ�ֻ�Ƿ���ͬ��˼·��һ����
    for (int j = 0; j < 4; j++)
    {
        for (int i = 1, k = 0; i < 4; i++)
        {
            if (map[i][j] > 0)
            {
                if (map[k][j] == map[i][j])
                {
                    map[k][j] *= 2;
                    score += map[k][j];
                    k++;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[k][j] == 0)
                {
                    map[k][j] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[++k][j] = map[i][j];
                    if (k != i)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

void move_right()
{
    // д�����������ƣ�ֻ�Ƿ���ͬ��˼·��һ����
    for (int i = 0; i < 4; i++)
    {
        for (int j = 2, k = 3; j > -1; j--)
        {
            if (map[i][j] > 0)
            {
                if (map[i][j] == map[i][k])
                {
                    map[i][k] *= 2;
                    score += map[i][k];
                    k--;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[i][k] == 0)
                {
                    map[i][k] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[i][--k] = map[i][j];
                    if(k != j)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

void move_down()
{
    // д�����������ƣ�ֻ�Ƿ���ͬ��˼·��һ����
    for (int j = 0; j < 4; j++)
    {
        for (int i = 2, k = 3; i > -1; i--)
        {
            if (map[i][j] > 0)
            {
                if (map[i][j] == map[k][j])
                {
                    map[k][j] *= 2;
                    score += map[k][j];
                    k--;
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else if (map[k][j] == 0)
                {
                    map[k][j] = map[i][j];
                    map[i][j] = 0;
                    need_add_num = 1;
                }
                else
                {
                    map[--k][j] = map[i][j];
                    if(i != k)
                    {
                        map[i][j] = 0;
                        need_add_num = 1;
                    }
                }
            }
        }
    }
}

// ��Ϸ����
void page()
{
    int i, j;
    COORD pos = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
    system("cls");
    color(3);
    printf("��Ϸ��: 2048                                 ����: %06d\n", score);
	printf("------------------------------------------------------------\n\n");
	printf("               �����������ש��������ש��������ש���������");       //���߿� 
	printf("\n");
	for (i = 0; i < 4; i++)
    {
        printf("               ��");
		for (j = 0; j < 4; j++)
        {
			if (map[i][j] == 0)
            {
                printf("    ��");                        //ֵΪ0ʱ��ֻ��ӡ(|)
            }                                    
			else
            {  
                printf("%4d��", map[i][j]);              //ֵ��Ϊ0ʱ����ӡ(����|)
            }
		}
		if (i != 3)
        {
            printf("\n               �ǩ��������贈�������贈�������贈��������\n");//��߿� 
        }
		else 
        {    
            printf("\n               �����������ߩ��������ߩ��������ߩ���������\n");//�ױ߿�
        } 
	}
	printf("------------------------------------------------------------\n");
	color(6);
	printf("           W��  A��  ��D  ��S\n");
	printf("��ǰ����Ϊ:%d\n", score);
}

// ��ʼ��������������
void first()                            
{
    int i, j;

    i = rand() % 4;
    j = rand() % 4;
    map[i][j] = 2;                      //��������2

    do
    {
        i = rand() % 4;
        j = rand() % 4;
    } while (map[i][j] != 0);           //����ҵ�ֵΪ0��i��j��

    map[i][j] = rand() % 5 ? 2 : 4;     //����ֵΪ2��4������Ϊ4:1
}

// ��ʼ�����������������
void ini()	  
{
	srand(time(NULL));      
    memset(map, 0, sizeof(map));      //��map�������ȫ��ֵ����Ϊ0
}

// �޸������д����ɫ
void color(int m)
{
	HANDLE consolehend;
	consolehend = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(consolehend, m);
}