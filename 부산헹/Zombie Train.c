#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define LEN_MIN 15 // 기차 길이
#define LEN_MAX 50
#define PROB_MIN 10  // 확률
#define PROB_MAX 90

int main(void) {
	srand((unsigned int)time(NULL));


	//인트로
	printf(" ______                   _      _          _____                         \n");
	printf("|___  /                  | |    (_)        |  __ \\                        \n");
	printf("   / /   ___   _ __ ___  | |__   _   ___   | |  \\/  __ _  _ __ ___    ___ \n");
	printf("  / /   / _ \\ | '_ ` _ \\ | '_ \\ | | / _ \\  | | __  / _` || '_ ` _ \\  / _ \\\n");
	printf("./ /___| (_) || | | | | || |_) || ||  __/  | |_\\ \\| (_| || | | | | ||  __/\n");
	printf("\\_____/ \\___/ |_| |_| |_||_.__/ |_| \\___|   \\____/ \\__,_||_| |_| |_| \\___|\n");
	printf("\n\n\n");





	// 변수선언

	int TrainL, Percent;         // 기차 길이,  확률
	int Citizen, Zombie, M;		 // 시민,  좀비, 마동석
	int PerCitizen, PerZombie;   // citizen, zombie 의 이전 위치 
	int turn = 1;                // 게임의 턴

	//열차정보 입력

	printf("train length(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
	scanf_s("%d", &TrainL);
	printf("percentile probability 'p'(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
	scanf_s("%d", &Percent);

	Citizen = TrainL - 6;
	PerCitizen = Citizen;
	Zombie = TrainL - 3;
	PerZombie = Zombie;
	M = TrainL - 2;


	if (TrainL >= LEN_MIN && TrainL <= LEN_MAX) {
		if (Percent >= PROB_MIN && Percent <= PROB_MAX) {
			// GAME START
			printf(" _____   ___  ___  ___ _____   _____  _____   ___  ______  _____ \n");
			printf("|  __ \\ / _ \\ |  \\/  ||  ___| /  ___||_   _| / _ \\ | ___ \\|_   _|\n");
			printf("| |  \\// /_\\ \\| .  . || |__   \\ `--.   | |  / /_\\ \\| |_/ /  | |  \n");
			printf("| | __ |  _  || |\\/| ||  __|   `--. \\  | |  |  _  ||    /   | |  \n");
			printf("| |_\\ \\| | | || |  | || |___  /\\__/ /  | |  | | | || |\\ \\   | |  \n");
			printf(" \\____/\\_| |_/\\_|  |_/\\____/  \\____/   \\_/  \\_| |_/\\_| \\_|  \\_/  \n");


			// 열차 초기상태 출력
			printf("\n\n\n");

			//열차 첫번째 줄 출력

			for (int i = 0; i <= TrainL - 1; i++) {
				printf("#");
			}
			printf("\n");

			//열차 두번째 줄 출력

			for (int i = 0; i <= TrainL - 1; i++) {
				if (i == 0 || i == TrainL - 1)
					printf("#");
				else if (i == Citizen)
					printf("C");
				else if (i == Zombie)
					printf("Z");
				else if (i == M)
					printf("M");
				else
					printf(" ");
			}

			//열차 세번째 줄 출력

			printf("\n");
			for (int i = 0; i <= TrainL - 1; i++)
				printf("#");
			printf("\n");
			printf("\n\n\n");

			//반복문

			while (1) {




				// 시민 이동 정보 저장

				int SP1 = rand() % 100;
				if (SP1 < (100 - Percent)) {
					Citizen--;
				}
				else
				{
				} // pass



	 // 좀비 이동 정보  저장

				int ZP1 = rand() % 100;
				if (turn % 2 == 1) { // 홀수번째 턴일때
					if (ZP1 < Percent) {
						Zombie--;
					}
					else
					{
					}
				}
				else  // 짝수번째 턴일떄
				{
				}




				// turn 출력
				printf("turn: %d\n\n", turn);


				//열차상태 출력
					//열차 상단 부분
				for (int i = 0; i <= TrainL - 1; i++) {
					printf("#");
				}
				printf("\n");

				//열차 중단 부분
				for (int i = 0; i <= TrainL - 1; i++) {
					if (i == 0 || i == TrainL - 1)
						printf("#");
					else if (i == Citizen)
						printf("C");
					else if (i == Zombie)
						printf("Z");
					else if (i == M)
						printf("M");
					else
						printf(" ");
				}
				//열차 하단 부분
				printf("\n");
				for (int i = 0; i <= TrainL - 1; i++)
					printf("#");
				printf("\n\n\n");

				// 이동현황 출력

					//시민
				if (Citizen != PerCitizen)
					printf("citizen: %d -> %d \n", PerCitizen, Citizen);

				else
					printf("citizen: stay %d\n", PerCitizen);

				//좀비
				if (turn % 2 == 1) // 홀수 턴일때 
				{
					if (Zombie != PerZombie)
						printf("Zomnie: %d -> %d\n", PerZombie, Zombie);
					else
						printf("Zombie: stay %d\n", PerZombie);
				}
				else // 짝수 턴일떄
					printf("Zombie: stay %d(cannot move)\n", PerZombie);


				printf("\n\n\n");

				//턴이 넘어갈때, 위치 저장, 턴 +1
				PerCitizen = Citizen;
				PerZombie = Zombie;
				turn += 1;

				// 게임종료
				if (Citizen == 1) {
					printf(" _____  _   _  _____  _____  _____  _____  _____ \n");
					printf("/  ___|| | | |/  __ \\/  __ \\|  ___|/  ___|/  ___|\n");
					printf("\\ `--. | | | || /  \\/| /  \\/| |__  \\ `--. \\ `--. \n");
					printf(" `--. \\| | | || |    | |    |  __|  `--. \\ `--.\\ \n");
					printf("/\\__/ /| |_| || \\__/\\| \\__/\\| |___ /\\__/ //\\__/ /\n");
					printf("\\____/  \\___/  \\____/ \\____/\\____/ \\____/ \\____/ \n");
					printf("citizen(s) escaped to the next train\n");
					break; // while 탈출
				}
				else if (Citizen == Zombie - 1) {
					printf(" _____   ___  ___  ___ _____   _____  _   _  _____ ______ \n");
					printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\\n");
					printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /\n");
					printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    / \n");
					printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ \n");
					printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|\n");
					printf("Citizen(s) has(have) been attacked by a zombie\n");
					break; // while 탈출
				}

				Sleep(4000); // 4초 대기
			}

		}
		else
			printf("percentile probability error"); // 확률 에러
	}
	else
		printf("train length error"); // 길이 에러

	return 0;
}