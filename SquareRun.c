#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define SQUARE_BOTTOM_Y 12
#define TREE_BOTTOM_Y 13
#define TREE_BOTTOM_X 50

/*Made by Hyun-Seok Lee.
Idea was made by HSL but the source code was from goole
How to find the code: Search in Google "C로 공룡 게임 만들기"*/

void SetConsoleView()
{
	system("mode con:cols=100 lines=25");
	system("title square run. By Ben");
}

void GotoXY(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

int getKeyDown()
{
	if(_kbhit() != 0)
	{
		return _getch();
	}
	return 0;
}

void drawSquare(int squareY)
{
	GotoXY(0, squareY);
	printf("$$$$$$$\n");
	printf("$$$$$$$\n");
	printf("$$$$$$$\n");
	printf("$$$$$$$\n");
}

void drawTree(int treeX)
{
	GotoXY(treeX, TREE_BOTTOM_Y);
	printf("###");
	GotoXY(treeX, TREE_BOTTOM_Y + 1);
	printf("###");
	GotoXY(treeX, TREE_BOTTOM_Y + 2);
	printf("###");
}

void drawGameOver(const int score)
{
    system("cls");
    int x = 18;
    int y = 8;
    GotoXY(x, y);
    printf("===========================");
    GotoXY(x, y + 1);
    printf("======G A M E O V E R======");
    GotoXY(x, y + 2);    
    printf("===========================");
    GotoXY(x, y + 5);
	printf("SCORE : %d", score);
 
    printf("\n\n\n\n\n\n\n\n\n");
    system("pause");
}

boolean isCollision(const int treeX, const int squareY)
{
    GotoXY(0, 0);
    printf("treeX : %d, squareY : %d", treeX, squareY);
    if (treeX <= 7 && treeX >= 4 &&
        squareY > 7)
    {
        return TRUE;
    }
    return FALSE;
}

int main(void)
{
	SetConsoleView();

	boolean isJumping = FALSE;
	boolean isBottom = TRUE;
	const int gravity  = 3;
	
	int squareY = SQUARE_BOTTOM_Y;
	int treeX = TREE_BOTTOM_X;

	int score = 0;
	clock_t start, curr;
	start = clock();

	while (1)
	{
		if(isCollision(treeX, squareY))
                break;
		
		if(getKeyDown() == 'z' && isBottom)
		{
			isJumping = TRUE;
			isBottom = FALSE;
		}

		if(isJumping)
		{
			squareY -= gravity;
		}
		else
		{
			squareY += gravity;
		}

		if(squareY >= SQUARE_BOTTOM_Y)
		{
			squareY = SQUARE_BOTTOM_Y;
			isBottom = TRUE;
		}

		if(squareY <= 3)
		{
			isJumping = FALSE;
		}

		treeX -= 4;
		if(treeX <= 0)
		{
			treeX = TREE_BOTTOM_X;
		}
		
		drawSquare(squareY);
		drawTree(treeX);

		curr = clock();
		if(((curr - start) / CLOCKS_PER_SEC) >= 1)
		{
			score++;
			start = clock();
		}
		
		Sleep(60);
		system("cls");

		GotoXY(22, 0);
		printf("Score: %d", score);
	}
	drawGameOver(score);
	
	return 0;
}