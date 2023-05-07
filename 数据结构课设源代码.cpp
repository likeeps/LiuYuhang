#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 30//�Թ���С����
typedef struct maze {//�Թ�����
	char a[maxn][maxn];
	int column;
	int row;
}Maze;
typedef struct {
	int column;
	int row;
}Direction;//�ƶ�����Ķ���
typedef struct {
	Direction area;
	int direction;
}Mazenode;//�Թ���ĳһ�����Ķ��壬�ڲ�������������һ��Ҫ�ߵķ����Լ��ý���Ƿ������

typedef struct linknode {
	Mazenode data;
	struct linknode* next;
}linknode, * Linknode;//ջ��һ�����
typedef struct stack {
	Linknode top;
}linkstack, * Linkstack;
//��ջ�Ķ���
Linkstack create_linkstack()
{
	Linkstack s;
	s = (Linkstack)malloc(sizeof(linkstack));
	if (s)	s->top = NULL;
	return s;
}
int ifempty(Linkstack s)//ջ��
{
	return (s->top == NULL);
}
int push_stack(Linkstack s, Mazenode x)//��ջ����
{
	Linknode p;
	p = (Linknode)malloc(sizeof(linknode));
	if (!p) {
		printf("�ڴ����");
		return 0;
	}
	p->data = x;
	p->next = s->top;
	s->top = p;
	return 1;
}
int pop_stack(Linkstack s, Mazenode* x)//��ջ����
{
	Linknode p;
	if (ifempty(s)) {
		printf("ջ�գ����ܳ�ջ");
		return 0;
	}
	*x = s->top->data;
	p = s->top;
	s->top = s->top->next;
	free(p);
	return 1;
}
void destory_linkstack(Linkstack* s)//ɾ��ջ���
{
	Linknode p, q;
	if (*s) {
		p = (*s)->top;
		while (p)
		{
			q = p;
			p = p->next;
			free(q);
		}
		free(*s);
	}
	*s = NULL;
	return;
}
//�Թ�����ز���
int create_maze(Maze* maze)//�Թ��Ĺ���
{
	int i, j, m, p, q;
	printf("�������Թ����к���:\n");
	scanf_s("%d%d", &maze->row, &maze->column);
	for (i = 0; i <= maze->column + 1; i++)//��Χ�ϰ���
	{
		maze->a[0][i] = '#';
		maze->a[maze->row + 1][i] = '#';
	}
	for (i = 0; i < maze->row + 1; i++) {
		maze->a[i][0] = '#';
		maze->a[i][maze->column + 1] = '#';
	}
	for (i = 1; i <= maze->row; i++) {
		for (j = 0; j <= maze->column; j++)
			maze->a[i][j] = '*';
	}
	printf("�������ϰ��ĸ���:\n");
	scanf_s("%d", &m);
	printf("�������ϰ�������:\n");
	for (i = 0; i < m; i++) {
		scanf_s("%d%d", &p, &q);
		if (p <= 0 || q <= 0 || p > maze->row || q > maze->column) {
			printf("����Խ��,��������");
			i = i - 1;
			continue;
		}
		maze->a[p][q] = '#';
	}
	return 1;
}
Direction nextcord(Direction pos, int i)//�����жϺ���
{
	switch (i) {
	case 1://��
		pos.column += 1;
		break;
	case 2://��
		pos.row += 1;
		break;
	case 3://��
		pos.column -= 1;
		break;
	case 4://��
		pos.row -= 1;
		break;
	}
	return pos;
}
int ifpass(Maze* maze, Direction pos) 
{
	if (maze->a[pos.row][pos.column] == '*')//��ʾ������
		return 1;
	else return 0;
}
int markerpass(Maze* maze, Direction pos)
{
	maze->a[pos.row][pos.column] = '2';//��ʾ�Ѿ��߹� 
	return 1;
}
int markernopass(Maze* maze, Direction pos)
{
	maze->a[pos.row][pos.column] = '3';//��ʾ������ 
	return 1;
}
void print_road(Linkstack* s)
{
	Mazenode p;
	Linkstack road;
	road = create_linkstack();
	while (!ifempty(*s))
	{
		pop_stack(*s, &p);
		push_stack(road, p);
	}
	while (!ifempty(road)) 
	{
		pop_stack(road, &p);
		if (road->top == NULL)//�ж��Ƿ���·
			p.direction = 0;
		printf("(%d,%d,%d)", p.area.row, p.area.column, p.direction);
	}
	printf("\n");
}
int maze_path(Maze* maze, Direction start, Direction end)//�Թ�ͨ·Ѱ�Һ���
{
	Linkstack s;
	Direction pos;
	int nextstep = 1;
	Mazenode p;
	s = create_linkstack();
	pos = start;
	do {
		if (ifpass(maze, pos)) {			//�Թ������� 
			markerpass(maze, pos);		//����Թ��Ѿ��߹� 
			p.direction = nextstep;		//��¼��һ��Ҫ�ߵķ��� 
			p.area = pos;					//�ƶ�����ǰ�� 
			push_stack(s, p);
			if (pos.row == end.row && pos.column == end.column) {//����ߵ����ھͽ��� 
				print_road(&s);
				destory_linkstack(&s);
				return 1;
			}
			else { 
				pos = nextcord(pos, nextstep);//�ƶ�pos����һ���� 
			//	nextstep++;//�ı��ƶ����� 
			}
		}
		else { //��λ�ò����� 
			if (!ifempty(s)) 
			{
				pop_stack(s, &p);//��ջ����һλ��
				while (p.direction > 4 && !ifempty(s)) 
				{
					markernopass(maze, p.area);//�ǳ��ڵ���·�ѱ����Ϊ3
					pop_stack(s, &p);
				}
				if (p.direction <= 4) 
				{
					p.direction++;
					push_stack(s, p);
					pos = nextcord(p.area, p.direction);
				}
			}
		}

	} while (!ifempty(s));
	destory_linkstack(&s);
	return 0;

}
void print(Maze* maze)//�Թ���״�������
{
	int i, j;
	for (i = 1; i <= maze->row; i++) {
		for (j = 1; j <= maze->column; j++)
		{
			if (maze->a[i][j] == '#') printf("# ");
			else if (maze->a[i][j] == '2') printf("* ");//�߹��Ŀ��е�·��Ϊ*��
			else printf("  ");//�߲�ͨ�Ŀ�·
		}
		printf("\n");
	}
}

int main()
{
	Maze maze;
	Direction start, end;
	printf("�����Թ�\n");
	create_maze(&maze);
	printf("�����Թ������\n");
	scanf_s("%d%d", &start.row, &start.column);
	printf("�����Թ��ĳ���\n");
	scanf_s("%d%d", &end.row, &end.column);
	if (!maze_path(&maze, start, end)) 
	{
		printf("û��ͨ·\n");
		return 0;
	}
	printf("�Թ��Լ��߳���·��:\n");
	print(&maze);
}