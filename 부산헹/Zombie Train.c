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
// ��Ʈ�� �ƿ�Ʈ��
void intro(void);
void citizenWin(void);
void zombieWin(void);

//�Է�
int inputTrainL();
int inputPercent();
int inputMdsStamina();
int inputMdsMove(int, int);

// �̵�, ��׷�
int citizenMove(int,int);
int zombieMove(int, int, int, int, int, int);
int mdsMove(int, int);
int citizenAggroChange(int, int, int);
int mdsAggroChange(int, int, int);

// ���
void printTrain(int, int, int, int); 
void printCitizenData(int, int, int, int);
void printZombieData(int, int, int);
void printMdsData(int, int, int, int, int);
void printCitizenAction(int);
void printZombieAction(int, int, int, int, int);

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
int inputMdsMove(int madongseok, int zombie) {
	int mdsMove;
	while (1) {
		printf("madongseok move(%d:stay, %d:left)>> ", MOVE_STAY, MOVE_LEFT); 
		scanf_s("%d", &mdsMove);
		if (mdsMove == MOVE_LEFT || mdsMove == MOVE_STAY) {
			if (madongseok == zombie + 1 && mdsMove == MOVE_LEFT)
				continue;
			else 
				break;
		}
	}
	return mdsMove; 
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
void printCitizenData(int citizen, int perCitizen, int perCitizenAggro, int CitizenAggro) {
	if (citizen != perCitizen) 
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", perCitizen, citizen, perCitizenAggro, CitizenAggro);
	else 
		printf("citizen: stay %d (aggro: %d -> %d)\n", perCitizen, perCitizenAggro, CitizenAggro); 
}
void printZombieData(int turn, int zombie, int perZombie) {
	if (turn % 2 == 1) 
	{
		if (zombie != perZombie)
			printf("Zomnie: %d -> %d\n\n", perZombie, zombie);
		else
			printf("Zombie: stay %d\n\n", perZombie);
	}
	else 
		printf("Zombie: stay %d(cannot move)\n\n", perZombie);
}
void printMdsData(int madongseok, int perMadongseok, int perMdsAggro, int mdsAggro, int mdsStamina) {
	if (madongseok == perMadongseok)
		printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n\n", madongseok, perMdsAggro, mdsAggro, mdsStamina);
	else
		printf("madongseok: %d -> %d(aggro: %d -> %d, stamina: %d)\n\n", perMadongseok, madongseok, perMdsAggro, mdsAggro, mdsStamina);
}
void printCitizenAction(int citizen) {
	if (citizen == 1)
		printf("you win.\n");
	else
		printf("citizen does nothing.\n");
}
void printZombieAction(int citizen, int zombie, int madonseok, int citizenAggro, int mdsAggro) {
	if (citizen == zombie - 1 && madonseok == zombie + 1) {
		if (citizenAggro > mdsAggro)
			printf("GAME OEVER! citizen dead...\n");
		else if (citizenAggro < mdsAggro)
			printf("Zomibe attacked madongseok(madongseok stamina:  -> )\n");
		else
			printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina:  -> )\n", citizenAggro, mdsAggro);
	}
	else if (citizen == zombie - 1)
		printf("GAME OEVER! citizen dead...\n");
	else if (madonseok == zombie + 1)
		printf("Zomibe attacked madongseok(madongseok stamina:  -> )\n");
	else
		printf("zombie attacked nobody.\n");
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
int zombieMove(int zombie, int percent, int citizen, int madonseok, int citizenAggro, int mdsAggro) {
	int zombieData = zombie;
	int zombieRandomNum = rand() % 100; 
	if (zombieRandomNum < percent) {
		if (citizenAggro < mdsAggro) {
			if (zombieData != madonseok - 1) 
				zombieData++;
		}
		else {
			if (zombieData != citizen + 1)
				zombieData--;
		}
	}
	return zombieData;
}
int mdsMove(int mdsMoveNum, int madongseok) {
	int mdsData = madongseok;
	if (mdsMoveNum == MOVE_LEFT)	
		mdsData--; 
	return mdsData;
}

// ��׷κ���
int citizenAggroChange(int citizenAggro, int citizen, int perCitizen) {
	int aggroData = citizenAggro;
	if (citizen != perCitizen) 
		aggroData++;
	else
		aggroData--;

	if (aggroData > AGGRO_MAX || aggroData < AGGRO_MIN) 
		aggroData = citizenAggro;
	return aggroData; 
}
int mdsAggroChange(int mdsAggro, int madongseok, int perMadongseok) {
	int aggroData = mdsAggro;
	if (madongseok != perMadongseok)
		aggroData++;
	else
		aggroData--;

	if (aggroData > AGGRO_MAX || aggroData < AGGRO_MIN)
		aggroData = mdsAggro;
	return aggroData;
}



int main(void) {
	srand((unsigned int)time(NULL));

	// ��������
	int trainL, percent, mdsStamina;           // ���� ����,  Ȯ��,  ������ ü��
	int citizen, zombie, madongseok; 	       // �ù�,  ����, ������
	int mdsMoveNum; 
	int citizenAggro = 0, mdsAggro = 0;	       // �ù�, ������ ��׷�	
	int perCitizenAggro = 0, perMdsAggro = 0;
	int perCitizen, perZombie, perMadongseok;   // citizen, zombie, ������ �� ���� ��ġ 
	int turn = 1;						       // ������ ��

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
	perMadongseok = madongseok; 

	// �ʱ⿭�� ���
	printf("\n\n\n");
	printTrain(trainL, citizen, zombie, madongseok);
	printf("\n\n\n");
	
			

	while (1) {
		// �̵�
		citizen = citizenMove(citizen, percent);

		// �ù� ��׷�
		citizenAggro = citizenAggroChange(citizenAggro, citizen, perCitizen);

		// ���� �̵�
		if (turn % 2 == 1) {
			zombie = zombieMove(zombie, percent, citizen, madongseok, citizenAggro, mdsAggro);
		}
		
	
		// �� ���
		printf("turn: %d\n", turn);

		// ���� ���
		printTrain(trainL, citizen, zombie, madongseok);

		// �̵����� ���
		printCitizenData(citizen, perCitizen, perCitizenAggro, citizenAggro);
		printZombieData(turn, zombie, perZombie);
		

		// ������ �̵� �Է�
		mdsMoveNum = inputMdsMove(madongseok, zombie);
		madongseok = mdsMove(mdsMoveNum, madongseok);

		// ������ ��׷�
		mdsAggro = mdsAggroChange(mdsAggro, madongseok, perMadongseok);


		// ���� ���
		printTrain(trainL, citizen, zombie, madongseok); 
		printf("\n"); 

		// ������ ���� ���
		printMdsData(madongseok, perMadongseok, perMdsAggro, mdsAggro, mdsStamina); 


		// �ൿ	
		// �ù��ൿ
		
		// �����ൿ
		
		// ������ �ൿ


		// �ൿ���
		//printCitizenAction(citizen);
		//printZombieAction(citizen, zombie, madongseok, citizenAggro, mdsAggro);


		// ��ġ ����, �� +1
		perCitizen = citizen;
		perCitizenAggro = citizenAggro; 
		perMadongseok = madongseok;
		perMdsAggro = mdsAggro; 
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
	}

	return 0;
}