#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxn 30//迷宫大小限制
typedef struct maze {//迷宫定义
	char a[maxn][maxn];
	int column;
	int row;
}Maze;
typedef struct {
	int column;
	int row;
}Direction;//移动方向的定义
typedef struct {
	Direction area;
	int direction;
}Mazenode;//迷宫节某一个结点的定义，内部包含了棋子下一步要走的方向以及该结点是否可以走

typedef struct linknode {
	Mazenode data;
	struct linknode* next;
}linknode, * Linknode;//栈的一个结点
typedef struct stack {
	Linknode top;
}linkstack, * Linkstack;
//链栈的定义
Linkstack create_linkstack()
{
	Linkstack s;
	s = (Linkstack)malloc(sizeof(linkstack));
	if (s)	s->top = NULL;
	return s;
}
int ifempty(Linkstack s)//栈空
{
	return (s->top == NULL);
}
int push_stack(Linkstack s, Mazenode x)//入栈函数
{
	Linknode p;
	p = (Linknode)malloc(sizeof(linknode));
	if (!p) {
		printf("内存溢出");
		return 0;
	}
	p->data = x;
	p->next = s->top;
	s->top = p;
	return 1;
}
int pop_stack(Linkstack s, Mazenode* x)//出栈函数
{
	Linknode p;
	if (ifempty(s)) {
		printf("栈空，不能出栈");
		return 0;
	}
	*x = s->top->data;
	p = s->top;
	s->top = s->top->next;
	free(p);
	return 1;
}
void destory_linkstack(Linkstack* s)//删除栈结点
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
//迷宫的相关操作
int create_maze(Maze* maze)//迷宫的构建
{
	int i, j, m, p, q;
	printf("请输入迷宫的行和列:\n");
	scanf_s("%d%d", &maze->row, &maze->column);
	for (i = 0; i <= maze->column + 1; i++)//外围障碍物
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
	printf("请输入障碍的个数:\n");
	scanf_s("%d", &m);
	printf("请输入障碍的坐标:\n");
	for (i = 0; i < m; i++) {
		scanf_s("%d%d", &p, &q);
		if (p <= 0 || q <= 0 || p > maze->row || q > maze->column) {
			printf("数组越界,重新输入");
			i = i - 1;
			continue;
		}
		maze->a[p][q] = '#';
	}
	return 1;
}
Direction nextcord(Direction pos, int i)//方向判断函数
{
	switch (i) {
	case 1://右
		pos.column += 1;
		break;
	case 2://下
		pos.row += 1;
		break;
	case 3://左
		pos.column -= 1;
		break;
	case 4://上
		pos.row -= 1;
		break;
	}
	return pos;
}
int ifpass(Maze* maze, Direction pos) 
{
	if (maze->a[pos.row][pos.column] == '*')//表示可以走
		return 1;
	else return 0;
}
int markerpass(Maze* maze, Direction pos)
{
	maze->a[pos.row][pos.column] = '2';//表示已经走过 
	return 1;
}
int markernopass(Maze* maze, Direction pos)
{
	maze->a[pos.row][pos.column] = '3';//表示不能走 
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
		if (road->top == NULL)//判断是否无路
			p.direction = 0;
		printf("(%d,%d,%d)", p.area.row, p.area.column, p.direction);
	}
	printf("\n");
}
int maze_path(Maze* maze, Direction start, Direction end)//迷宫通路寻找函数
{
	Linkstack s;
	Direction pos;
	int nextstep = 1;
	Mazenode p;
	s = create_linkstack();
	pos = start;
	do {
		if (ifpass(maze, pos)) {			//迷宫可以走 
			markerpass(maze, pos);		//标记迷宫已经走过 
			p.direction = nextstep;		//记录下一次要走的方向 
			p.area = pos;					//移动到当前点 
			push_stack(s, p);
			if (pos.row == end.row && pos.column == end.column) {//如果走到出口就结束 
				print_road(&s);
				destory_linkstack(&s);
				return 1;
			}
			else { 
				pos = nextcord(pos, nextstep);//移动pos到下一个点 
			//	nextstep++;//改变移动方向 
			}
		}
		else { //该位置不能走 
			if (!ifempty(s)) 
			{
				pop_stack(s, &p);//退栈到上一位置
				while (p.direction > 4 && !ifempty(s)) 
				{
					markernopass(maze, p.area);//非出口的死路已被标记为3
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
void print(Maze* maze)//迷宫形状输出函数
{
	int i, j;
	for (i = 1; i <= maze->row; i++) {
		for (j = 1; j <= maze->column; j++)
		{
			if (maze->a[i][j] == '#') printf("# ");
			else if (maze->a[i][j] == '2') printf("* ");//走过的可行的路变为*号
			else printf("  ");//走不通的空路
		}
		printf("\n");
	}
}

int main()
{
	Maze maze;
	Direction start, end;
	printf("创建迷宫\n");
	create_maze(&maze);
	printf("输入迷宫的入口\n");
	scanf_s("%d%d", &start.row, &start.column);
	printf("输入迷宫的出口\n");
	scanf_s("%d%d", &end.row, &end.column);
	if (!maze_path(&maze, start, end)) 
	{
		printf("没有通路\n");
		return 0;
	}
	printf("迷宫以及走出的路径:\n");
	print(&maze);
}