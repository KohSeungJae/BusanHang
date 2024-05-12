#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

//�Ķ����
#define LEN_MIN 15     // ���� ����
#define LEN_MAX 50
#define STM_MIN 0	  // ������ ü��
#define STM_MAX 5
#define PROB_MIN 10    // Ȯ��
#define PROB_MAX 90
#define AGGRO_MIN 0    //��׷� ����
#define AGGRO_MAX 5

// ������ �̵�����
#define MOVE_LEFT 1
#define MOVE_STAY 0

// ������ ���ݴ��
#define ATK_NONE 0
#define ATK_CITIZEN 1 
#define ATK_DONGSEOK 2 

// ������ �ൿ
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// �Լ�����
void intro(void);
void citizenWin(void);
void zombieWin(viod);
int inputTrainL();
int inputPercent();
int inputMdsStamina();
void printTrain(int,int,int,int);
int citizenMove(int,int);
int zombieMove(int, int);
void printCitizenData(int, int);
void printZombieData(int, int, int);

// �Լ� ����
// ��Ʈ��
void intro(void) {
	printf(" ______                   _      _          _____                         \n");
	printf("|___  /                  | |    (_)        |  __ \\                        \n");
	printf("   / /   ___   _ __ ___  | |__   _   ___   | |  \\/  __ _  _ __ ___    ___ \n");
	printf("  / /   / _ \\ | '_ ` _ \\ | '_ \\ | | / _ \\  | | __  / _` || '_ ` _ \\  / _ \\\n");
	printf("./ /___| (_) || | | | | || |_) || ||  __/  | |_\\ \\| (_| || | | | | ||  __/\n");
	printf("\\_____/ \\___/ |_| |_| |_||_.__/ |_| \\___|   \\____/ \\__,_||_| |_| |_| \\___|\n");
	printf("\n\n\n");
}
void citizenWin(void) {
		printf(" _____  _   _  _____  _____  _____  _____  _____ \n");
		printf("/  ___|| | | |/  __ \\/  __ \\|  ___|/  ___|/  ___|\n");
		printf("\\ `--. | | | || /  \\/| /  \\/| |__  \\ `--. \\ `--. \n");
		printf(" `--. \\| | | || |    | |    |  __|  `--. \\ `--.\\ \n");
		printf("/\\__/ /| |_| || \\__/\\| \\__/\\| |___ /\\__/ //\\__/ /\n");
		printf("\\____/  \\___/  \\____/ \\____/\\____/ \\____/ \\____/ \n");
		printf("citizen(s) escaped to the next train\n");
}
void zombieWin(void) {
		printf(" _____   ___  ___  ___ _____   _____  _   _  _____ ______ \n");
		printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\\n");
		printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /\n");
		printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    / \n");
		printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ \n");
		printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|\n");
		printf("Citizen(s) has(have) been attacked by a zombie\n");
}

// �Է�
int inputTrainL() {
	int trainL;
	while (1) {
		printf("train length(%d ~ %d)>> ", LEN_MIN, LEN_MAX);
		scanf_s("%d", &trainL);
		if (trainL >= LEN_MIN && trainL <= LEN_MAX) break;
	}
	return trainL;
}
int inputPercent() {
	int percent;
	while (1) {
		printf("percentile probability 'p'(%d ~ %d)>> ", PROB_MIN, PROB_MAX);
		scanf_s("%d", &percent);
		if (percent >= PROB_MIN && percent <= PROB_MAX) break;
	}
	return percent;
}
int inputMdsStamina() {
	int MdsSt;
	while (1) {
		printf("madongseok stamina(%d~%d)>> ", STM_MIN, STM_MAX);
		scanf_s("%d", &MdsSt);
		if (MdsSt >= STM_MIN && MdsSt <= STM_MAX) break;
	}
	return MdsSt;
}

// ���
void printTrain(int trainL, int citizen, int zombie, int madongseok) {
	//���� ù��° �� ���
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n");

	//���� �ι�° �� ���
	for (int i = 0; i <= trainL - 1; i++) {
		if (i == 0 || i == trainL - 1)
			printf("#");
		else if (i == citizen)
			printf("C");
		else if (i == zombie)
			printf("Z");
		else if (i == madongseok)
			printf("M");
		else
			printf(" ");
	}

	//���� ����° �� ���
	printf("\n");
	for (int i = 0; i <= trainL - 1; i++)
		printf("#");
	printf("\n");
}
void printCitizenData(int citizen, int perCitizen) {
	if (citizen != perCitizen) 
		printf("citizen: %d -> %d \n", perCitizen, citizen);
	else 
		printf("citizen: stay %d\n", perCitizen); 
}
void printZombieData(int turn, int zombie, int perZombie) {
	if (turn % 2 == 1) 
	{
		if (zombie != perZombie)
			printf("Zomnie: %d -> %d\n", perZombie, zombie);
		else
			printf("Zombie: stay %d\n", perZombie);
	}
	else 
		printf("Zombie: stay %d(cannot move)\n", perZombie);
}

// �̵�����
int citizenMove(int citizen, int percent) {
	int citizenData = citizen;
	int citizenRandomNum = rand() % 100; 
	if (citizenRandomNum < (100 - percent)) { 
		citizenData--;
	}
	return citizenData;
}
int zombieMove(int zombie, int percent) {
	int zombieData = zombie;
	int zombieRandomNum = rand() % 100; 
	if (zombieRandomNum < percent) { 
		zombieData--;  
	}
	return zombieData;
}


int main(void) {
	srand((unsigned int)time(NULL));

	// ��������
	int trainL, percent, mdsStamina;           // ���� ����,  Ȯ��,  ������ ü��
	int citizen, zombie, madongseok; 		  // �ù�,  ����, ������
	int perCitizen, perZombie;				 // citizen, zombie �� ���� ��ġ 
	int turn = 1;							// ������ ��

	//��Ʈ��
	intro();

	//�������� �Է�
	trainL = inputTrainL();
	mdsStamina = inputMdsStamina();
	percent = inputPercent();
	

	citizen = trainL - 6;
	zombie = trainL - 3;
	madongseok = trainL - 2; 

	perCitizen = citizen;
	perZombie = zombie;

	// �ʱ⿭�� ���
	printf("\n\n\n");
	printTrain(trainL, citizen, zombie, madongseok);
	printf("\n\n\n");
	
			

	while (1) {
		// �̵�
		citizen = citizenMove(citizen, percent);
		if (turn % 2 == 1) {
			zombie = zombieMove(zombie, percent);
		}
		// ���
		 // ��
		printf("turn: %d\n", turn);

		 // ����
		printTrain(trainL, citizen, zombie, madongseok);

		 // �̵���Ȳ
		printCitizenData(citizen, perCitizen);
		printZombieData(turn, zombie, perZombie);
		printf("\n\n\n");

		//���� �Ѿ��, ��ġ ����, �� +1
		perCitizen = citizen;
		perZombie = zombie;
		turn += 1;

		// ��������
		if (citizen == 1) { 
			citizenWin();
			break;
		}
		else if (citizen == zombie - 1) {
			zombieWin();
			break;
		}
		Sleep(4000); 
	}

	return 0;
}