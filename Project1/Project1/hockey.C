#include<stdio.h>
#include<Windows.h>
#include<conio.h>
#include<stdlib.h> // rand 함수 사용
#include<time.h>

#define UP 72		// 키보드 위 방향키
#define DOWN 80		// 키보드 아래 방향키
#define speed_num 10 // 시작할때의 공의 속도 (숫자가 커질수록 느려짐 (3일 경우 3번에 한번 공이 이동한다는 뜻))
#define rally_num 1	 // 몇번의 랠리마다 속도를 증가시킬지 설정
#define width 49	// 가로 크기 - 1 (0부터 시작하기 때문) 
#define length 19	// 세로 크기 - 1 (0부터 시작하기 때문) 

int pos_x= width / 2; // 공의 시작 위치
int pos_y=length / 2;
int vel_x=1; // 공의 진행방향
int vel_y=1;
int speed1 = speed_num; 
int speed2 = 1;
int speed_flag = 1; 
int rally = rally_num; 
int rally_flag = 1;
int ball_flag1 = 0;
int ball_flag2 = 0;
int ball_flag3 = 0;
int diff = 0;
int com_speed = 0;
int com_flag = 0;

void SetConsoleView()	// 콘솔 창의 크기와 제목을 지정하는 함수
{
	system("mode con:cols=50 lines=20");
	system("title hockey game");

}

void GotoXY(int x, int y) // 커서의 위치를 x, y로 이동하는 함수
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

void Drawbar(int y) // player의 bar를 그려주는 함수
{
	GotoXY(0, y-2);
	printf("|\n");
	GotoXY(0, y-1);
	printf("|\n");
	GotoXY(0, y);
	printf("|\n");
	GotoXY(0, y+1);
	printf("|\n");
	GotoXY(0, y+2);
	printf("|\n");
}

void Drawcom(int y)	// 컴퓨터의 bar를 그려주는 함수
{
	GotoXY(width, y-2);
	printf("|");
	GotoXY(width, y-1);
	printf("|");
	GotoXY(width, y);
	printf("|");
	GotoXY(width, y+1);
	printf("|");
	GotoXY(width, y+2);
	printf("|");
}

void Drawlayout()	// 레이아웃을 그려주는 함수
{
	GotoXY(0, 0);
	printf("-------------------------------------------------");
	GotoXY(0, length);
	printf("-------------------------------------------------");

}

void Drawball(int x, int y) // 공을 그려주는 함수
{
	GotoXY(x, y);
	printf("o");
}


void update() // 공의 위치를 지정해 주는 함수
{
	if (speed1 > 1)
	{
		if (speed_flag == speed1)
		{
			pos_x = pos_x + vel_x;
			pos_y = pos_y + vel_y;
			speed_flag = 0;
		}

		speed_flag = speed_flag + 1;
	}
	else
	{
		pos_x = pos_x + (vel_x * speed2);
		pos_y = pos_y + (vel_y * speed2);
	}
	

	Drawball(pos_x, pos_y);
}

void Drawgameover(int score) // 게임종료창
{
	system("cls"); // 창을 초기화
	GotoXY(20, length / 2);
	printf("GAMEOVER\n");
	GotoXY(20, (length / 2)+1);
	printf("SCORE: %d\n\n\n", score);
	system("pause");
}

void Drawwin(int score)
{
	system("cls");
	GotoXY(20, length / 2);
	printf("YOU WIN\n");
	GotoXY(20, (length / 2) + 1);
	printf("SCORE: %d\n\n\n", score);
	system("pause");
}

void Drawdiff()
{
	system("cls");
	GotoXY(15, 6);
	printf("1. 난이도 쉬움");
	GotoXY(15, 8);
	printf("2. 난이도 어려움");
	GotoXY(15, 10);
	printf("해당되는 번호를 눌러주세요");
}

int main(void)
{
	SetConsoleView();
	
	while (1)
	{
		// 초기화
		int bar_y = length/2;
		int com_y = length/2;
		int score = 0;
		pos_x = width/2;
		pos_y = length/2;
		vel_x = 1; // 공의 진행방향
		vel_y = 1;
		speed1 = speed_num; // 공의 속도 (숫자가 커질수록 느려짐 (3일 경우 3번에 한번 공이 이동한다는 뜻))
		speed_flag = 1;
		rally = rally_num; // 몇번의 랠리마다 속도를 증가시킬지 설정
		rally_flag = 1;
		ball_flag1 = 0;
		ball_flag2 = 0;
		ball_flag3 = 0;
		com_speed = 0;
		com_flag = 0;
		int rand1 = 0;
		int rand2 = 0;


		//////////////////////// 난수생성기 /////////////////////////////
		srand((unsigned int)time(NULL)); // rand의 seed를 현재 시간으로 입력해준다	
		rand1 = rand() % 2;	// rand값의 범위는 0~32767이다 2로 나눈 나머지를 구하게 되면 0과 1 두가지 값이 나오게 된다
		rand2 = rand() % 2;

		if (rand1 == 0)
		{
			vel_x = -1;
		}
		else
		{
			vel_x = 1;
		}

		if (rand2 == 0)
		{
			vel_y = -1;
		}
		else
		{
			vel_y = 1;
		}
		//////////////////////////////////////////////////////

		Drawdiff();
		while (1)
		{
			diff = 0;
			if (_kbhit()) {					// 1. 키보드 입력이 감지되면
				int pressedKey = _getch();	// 2. 아스키 코드 값을 가져오고
				switch (pressedKey) {		// 3. 입력받은 키에 해당하는 동작을 수행한다.
				case '1':	// 난이도 쉬움
					diff = 1;
					break;

				case '2':	// 난이도 어려움
					diff = 2;
					break;

				default:
					GotoXY(10, 12);
					printf("1, 2 중 원하는 난이도를 눌러주세요");
				}
			}
			if (diff == 1 || diff == 2)
			{
				break;
			}
		}
		

		while (1)
		{

			if (_kbhit()) {					// 1. 키보드 입력이 감지되면
				int pressedKey = _getch();	// 2. 아스키 코드 값을 가져오고
				switch (pressedKey) {		// 3. 입력받은 키에 해당하는 동작을 수행한다.
				case UP:
					bar_y -= 2;
					break;
					// 위로 이동
				case DOWN:
					bar_y += 2;
					break;
					// 아래로 이동
				}
			}


			if (bar_y <= 3)		// player bar의 위 아래 최소 최대 값을 정해준다
			{
				bar_y = 3;
			}
			else if (bar_y >= length - 3)
			{
				bar_y = length - 3;
			}


			update(); // 공의 위치를 변경해주는 함수


			////////////////////////////////////////////////////////////////////////////////////////

			if (diff == 1)	// 난이도 쉬움
			{
				com_speed = 2;
			}
			else if (diff == 2)	// 난이도 어려움
			{
				com_speed = 1;
			}

			if (com_flag == com_speed)
			{
				if (com_y > pos_y)	// 컴퓨터 bar의 위치를 설정해준다
				{
					com_y = com_y - 1;
				}
				else if (com_y < pos_y)
				{
					com_y = com_y + 1;
				}
				com_flag = 0;
			}
			com_flag = com_flag + 1;


			if (com_y <= 3)		// 컴퓨터 bar의 위 아래 최소 최대 값을 정해준다
			{
				com_y = 3;
			}
			else if (com_y >= length - 3)
			{
				com_y = length - 3;
			}
			///////////////////////////////////////////////////////////////////////////////

			 
			//////////////////////// 공의 방향전환 ///////////////////////////
			if (pos_y <= 1) // 공이 위 부분에 닿으면 방향을 전환해준다 
			{
				pos_y = 1;
				if (ball_flag1 == 0)	// ball_flag가 0이면 방향을 바꾸어 준다
				{
					vel_y = vel_y * -1;
					ball_flag1 = 1;
				}
				
			}
			else if (pos_y >= length - 1) // 공이 아래 부분에 닿으면 방향을 전환해준다 
			{
				pos_y = length - 1;
				if (ball_flag1 == 0)	// ball_flag가 0이면 방향을 바꾸어 준다
				{
					vel_y = vel_y * -1;
					ball_flag1 = 1;
				}
			}
			else
			{
				ball_flag1 = 0;
			}

			if (pos_x >= width - 1)			// 공이 컴퓨터 bar와 만나면 방향을 전환해준다
			{
				if ((pos_y >= com_y - 2) && (pos_y <= com_y + 2))
				{
					pos_x = width - 1;
					if (ball_flag2 == 0)
					{
						vel_x = vel_x * -1;
						ball_flag2 = 1;
					}
					
				}
			}
			else
			{
				ball_flag2 = 0;
			}

			if (pos_x <= 1)			// 공이 player bar와 만나면 방향을 전환해준다 player bar와 만날 때 마다 점수가 올라가고 속도가 빨라진다
			{
				if ((pos_y >= bar_y - 2) && (pos_y <= bar_y + 2))
				{
					pos_x = 1;
					if (ball_flag3 == 0)
					{
						vel_x = vel_x * -1;
						score = score + 1; // 점수를 추가
						if (rally_flag == rally) // 설정한 랠리만큼 진행이되면 속도를 높여줌
						{
							if (speed1 > 1)	
							{
								speed1 = speed1 - 1;
							}
							else
							{
								speed2 = speed2 + 1;
							}
							rally_flag = 0;
						}
						rally_flag = rally_flag + 1;
						ball_flag3 = 1;
					}

				}
			}
			else
			{
				ball_flag3 = 0;
			}
			//////////////////////////////////////////////////////////////////////

			if (pos_x <= 0)	// 공이 아웃될 때
			{
				Drawgameover(score);
				break;
			}
			else if (pos_x >= width)
			{
				Drawwin(score);
				break;
			}


			Drawbar(bar_y);	// player bar를 그려준다
			Drawcom(com_y); // 컴퓨터의 bar를 그려준다
			Drawlayout();	// 레이아웃을 그려준다
			Sleep(10);
			system("cls");	// 화면을 초기화 해준다
		}

		
	}
	return 0;
}