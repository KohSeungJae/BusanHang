#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

#define LEN_MIN 15 // ���� ����
#define LEN_MAX 50
#define PROB_MIN 10  // Ȯ��
#define PROB_MAX 90

int main(void) {
	srand((unsigned int)time(NULL));


	//��Ʈ��
	printf(" ______                   _      _          _____                         \n");
	printf("|___  /                  | |    (_)        |  __ \\                        \n");
	printf("   / /   ___   _ __ ___  | |__   _   ___   | |  \\/  __ _  _ __ ___    ___ \n");
	printf("  / /   / _ \\ | '_ ` _ \\ | '_ \\ | | / _ \\  | | __  / _` || '_ ` _ \\  / _ \\\n");
	printf("./ /___| (_) || | | | | || |_) || ||  __/  | |_\\ \\| (_| || | | | | ||  __/\n");
	printf("\\_____/ \\___/ |_| |_| |_||_.__/ |_| \\___|   \\____/ \\__,_||_| |_| |_| \\___|\n");
	printf("\n\n\n");





	// ��������

	int TrainL, Percent;         // ���� ����,  Ȯ��
	int Citizen, Zombie, M;		 // �ù�,  ����, ������
	int PerCitizen, PerZombie;   // citizen, zombie �� ���� ��ġ 
	int turn = 1;                // ������ ��

	//�������� �Է�

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


			// ���� �ʱ���� ���
			printf("\n\n\n");

			//���� ù��° �� ���

			for (int i = 0; i <= TrainL - 1; i++) {
				printf("#");
			}
			printf("\n");

			//���� �ι�° �� ���

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

			//���� ����° �� ���

			printf("\n");
			for (int i = 0; i <= TrainL - 1; i++)
				printf("#");
			printf("\n");
			printf("\n\n\n");

			//�ݺ���

			while (1) {




				// �ù� �̵� ���� ����

				int SP1 = rand() % 100;
				if (SP1 < (100 - Percent)) {
					Citizen--;
				}
				else
				{
				} // pass



	 // ���� �̵� ����  ����

				int ZP1 = rand() % 100;
				if (turn % 2 == 1) { // Ȧ����° ���϶�
					if (ZP1 < Percent) {
						Zombie--;
					}
					else
					{
					}
				}
				else  // ¦����° ���ϋ�
				{
				}




				// turn ���
				printf("turn: %d\n\n", turn);


				//�������� ���
					//���� ��� �κ�
				for (int i = 0; i <= TrainL - 1; i++) {
					printf("#");
				}
				printf("\n");

				//���� �ߴ� �κ�
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
				//���� �ϴ� �κ�
				printf("\n");
				for (int i = 0; i <= TrainL - 1; i++)
					printf("#");
				printf("\n\n\n");

				// �̵���Ȳ ���

					//�ù�
				if (Citizen != PerCitizen)
					printf("citizen: %d -> %d \n", PerCitizen, Citizen);

				else
					printf("citizen: stay %d\n", PerCitizen);

				//����
				if (turn % 2 == 1) // Ȧ�� ���϶� 
				{
					if (Zombie != PerZombie)
						printf("Zomnie: %d -> %d\n", PerZombie, Zombie);
					else
						printf("Zombie: stay %d\n", PerZombie);
				}
				else // ¦�� ���ϋ�
					printf("Zombie: stay %d(cannot move)\n", PerZombie);


				printf("\n\n\n");

				//���� �Ѿ��, ��ġ ����, �� +1
				PerCitizen = Citizen;
				PerZombie = Zombie;
				turn += 1;

				// ��������
				if (Citizen == 1) {
					printf(" _____  _   _  _____  _____  _____  _____  _____ \n");
					printf("/  ___|| | | |/  __ \\/  __ \\|  ___|/  ___|/  ___|\n");
					printf("\\ `--. | | | || /  \\/| /  \\/| |__  \\ `--. \\ `--. \n");
					printf(" `--. \\| | | || |    | |    |  __|  `--. \\ `--.\\ \n");
					printf("/\\__/ /| |_| || \\__/\\| \\__/\\| |___ /\\__/ //\\__/ /\n");
					printf("\\____/  \\___/  \\____/ \\____/\\____/ \\____/ \\____/ \n");
					printf("citizen(s) escaped to the next train\n");
					break; // while Ż��
				}
				else if (Citizen == Zombie - 1) {
					printf(" _____   ___  ___  ___ _____   _____  _   _  _____ ______ \n");
					printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\\n");
					printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /\n");
					printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    / \n");
					printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ \n");
					printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|\n");
					printf("Citizen(s) has(have) been attacked by a zombie\n");
					break; // while Ż��
				}

				Sleep(4000); // 4�� ���
			}

		}
		else
			printf("percentile probability error"); // Ȯ�� ����
	}
	else
		printf("train length error"); // ���� ����

	return 0;
}