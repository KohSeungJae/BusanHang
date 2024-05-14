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
int inputMdsAction(int, int);

// ���
void printTrain(int, int, int, int); 
void printCitizenData(int, int, int, int);
void printZombieData(int, int, int, int);
void printMdsData(int, int, int, int, int);
//void printCitizenAction(int);
void printRest(int, int, int, int);
void printProvo(int, int, int);
void printPull(int, int, int, int, int);

// �̵�
int citizenMove(int,int);
int zombieMove(int, int, int, int, int, int);
int mdsMove(int, int);

// ��׷�
int citizenAggroChange(int, int, int);
int mdsAggroChange(int, int, int);

// �ൿ
int zombieAction(int, int, int, int, int);
int mdsInfection(int, int);
int mdsRestAggro(int);
int mdsRsetStamina(int);
int mdsPull(int); 
int mdsPullAggro(int);
 

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
		printf("citizen(s) escaped to the next train\n\n");
}
void zombieWin(void) {
		printf(" _____   ___  ___  ___ _____   _____  _   _  _____ ______ \n");
		printf("|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | ||  ___|| ___ \\\n");
		printf("| |  \\// /_\\ \\| .  . || |__   | | | || | | || |__  | |_/ /\n");
		printf("| | __ |  _  || |\\/| ||  __|  | | | || | | ||  __| |    / \n");
		printf("| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ /| |___ | |\\ \\ \n");
		printf(" \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/ \\____/ \\_| \\_|\n");
		exit(0);
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
		if (madongseok == zombie + 1) {
			printf("madongseok move(%d:stay)>> ", MOVE_STAY);
			scanf_s("%d", &mdsMove);
			if (mdsMove == MOVE_STAY) break;
		}
		else{
			printf("madongseok move(%d:stay, %d:left)>> ", MOVE_STAY, MOVE_LEFT); 
			scanf_s("%d", &mdsMove); 
			if (mdsMove == MOVE_STAY || mdsMove == MOVE_LEFT) break;
		}
	}
	printf("\n"); 
	return mdsMove; 
}
int inputMdsAction(int zombie, int madongseok) {
	int Action;
	while (1) {
		if (zombie != madongseok - 1) {
			printf("madongseok action(%d.rest, %d.provoke)>> ", ACTION_REST, ACTION_PROVOKE);
			scanf_s("%d", &Action);
			if (Action == ACTION_REST || Action == ACTION_PROVOKE) break;
		}
		else {
			printf("madongseok action(%d.rest, %d.provoke %d.pull)>> ", ACTION_REST, ACTION_PROVOKE, ACTION_PULL);
			scanf_s("%d", &Action);
			if (Action == ACTION_REST || Action == ACTION_PROVOKE || Action == ACTION_PULL) break;
		}
	}
	return Action;
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
void printCitizenData(int citizen, int preCitizen, int preCitizenAggro, int CitizenAggro) {
	printf("\n");
	if (citizen != preCitizen) 
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", preCitizen, citizen, preCitizenAggro, CitizenAggro);
	else 
		printf("citizen: stay %d (aggro: %d -> %d)\n", preCitizen, preCitizenAggro, CitizenAggro); 
}
void printZombieData(int turn, int zombie, int preZombie, int mdsPullNum) {
	if (mdsPullNum == 1) 
		printf("Zombie  can't move by madongseok\n");
	else {
		if (turn % 2 == 1)
		{
			if (zombie != preZombie)
				printf("Zombie: %d -> %d\n\n", preZombie, zombie);
			else
				printf("Zombie: stay %d\n\n", preZombie);
		}
		else
			printf("Zombie: stay %d(cannot move)\n\n", preZombie);
	}
}
void printMdsData(int madongseok, int preMadongseok, int preMdsAggro, int mdsAggro, int mdsStamina) {
	if (madongseok == preMadongseok)
		printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n\n", madongseok, preMdsAggro, mdsAggro, mdsStamina);
	else
		printf("madongseok: %d -> %d(aggro: %d -> %d, stamina: %d)\n\n", preMadongseok, madongseok, preMdsAggro, mdsAggro, mdsStamina);
}
/*void printCitizenAction(int citizen) {
	if (citizen == 1)
		printf("you win.\n");
	else
		printf("citizen does nothing.\n");
}
*/
void printRest(int mdsAggro, int preMdsAggro, int mdsStamina, int preMdsStamina) {
	printf("\nmadongseok rests...\n");
	printf("madongseok: 7 (aggro: %d -> %d, stamina: %d -> %d)\n\n", preMdsAggro, mdsAggro, preMdsStamina, mdsStamina);
}
void printProvo(int mdsAggro, int preMdsAggro, int mdsStamina) {
	printf("\nmadongseok provoked zombie...\n");
	printf("madongseok: 7 (aggro: %d -> %d, stamina: %d)\n\n", preMdsAggro, mdsAggro, mdsStamina);
}
void printPull(int mdsPullNum, int mdsAggro, int preMdsAggro, int mdsStamina, int preMdsStamina) {
	if (mdsPullNum == 0) 
		printf("\nmadongseok failed to pull zombie\n");
	else 
		printf("\nmadongseok pulled zombie... Next turn, it can't move\n");
printf("madongseok: 7 (aggro: %d -> %d, stamina: %d -> %d)\n\n", preMdsAggro, mdsAggro, preMdsStamina, mdsStamina);
}
void printzombieAction(int infectionNum,int mdsStamina, int preMdsStamina, int citizenAggro, int mdsAggro) { 
	  
	switch (infectionNum) {
	case 1:
	case 4:
		printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", preMdsStamina, mdsStamina);
		break;
	case 2:
		printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina:  %d -> %d)\n", citizenAggro, mdsAggro, preMdsStamina, mdsStamina); 
		break;
	default:
		printf("zombie attacked nobody.\n"); 
	}
}

// �̵�
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

// ��׷�
int citizenAggroChange(int citizenAggro, int citizen, int preCitizen) {
	int aggroData = citizenAggro;
	if (citizen != preCitizen) 
		aggroData++;
	else
		aggroData--;

	if (aggroData > AGGRO_MAX || aggroData < AGGRO_MIN) 
		aggroData = citizenAggro;
	return aggroData; 
}
int mdsAggroChange(int mdsAggro, int madongseok, int preMadongseok) {
	int aggroData = mdsAggro;
	if (madongseok != preMadongseok)
		aggroData++;
	else
		aggroData--;

	if (aggroData > AGGRO_MAX || aggroData < AGGRO_MIN)
		aggroData = mdsAggro;
	return aggroData;
}

// �ൿ
int zombieAction(int zombie, int citizen, int madongseok, int citizenAggro, int mdsAggro) {
	int infectionNum;
	if (citizen == zombie - 1 && madongseok == zombie + 1) {
		if (citizenAggro > mdsAggro) 
			infectionNum = 0; 
		else if (citizenAggro < mdsAggro)
			infectionNum = 1;
		else
			infectionNum = 2;
	}
	else if (citizen == zombie - 1)
		infectionNum = 3;
	else if (madongseok == zombie + 1)
		infectionNum = 4;
	else
		infectionNum = 5;
	return infectionNum;
}
int mdsInfection(int infectionNum, int mdsStamina) {
	int stamina = mdsStamina;
	if (infectionNum == 1 || infectionNum == 2 || infectionNum == 4) {
		stamina--;
	}
	return stamina;
}
int mdsRestAggro(int mdsAggro) {
	int Aggro = mdsAggro;
	Aggro--;
	if (Aggro < AGGRO_MIN)
		Aggro = mdsAggro;
	return Aggro;
}
int mdsRsetStamina(int mdsStamina) {
	int stamina = mdsStamina;
	stamina++;
	if (stamina > STM_MAX)
		stamina = mdsStamina;
	return stamina;
}
int mdsPull(int percent) {
	int PullNum = 0;
	int ran = rand() % 100;
	if (ran < (100 - percent)) {
		PullNum = 1;
	}
	return PullNum;
}
int mdsPullAggro(int mdsAggro) {
	int aggro = mdsAggro;
	aggro += 2;
	if (aggro > AGGRO_MAX)
		aggro = AGGRO_MAX;
	return aggro;
}

// stage2 �Լ�
void printTrain2(int trainL, int citizen, int zombie, int madongseok, int villain) {
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
		else if (i == villain)
			printf("V");
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
void printStage2(void) {
	printf(" _____  _____   ___   _____  _____  _____ \n");
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___|/ __  \\\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__  `' / /'\n");
	printf(" `--. \\  | |  |  _  || | __ |  __|   / /  \n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ ./ /___\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/ \\_____/\n");
	printf("\n");
}
void printVillainData(int villain, int preVillain, int villainAggro, int preVillainAggro) { 
	if (villain != preVillain)
		printf("villain: %d -> %d (aggro: %d -> %d)\n", preVillain, villain, preVillainAggro, villainAggro);
	else
		printf("villain: stay %d (aggro: %d -> %d)\n", villain, preVillainAggro, villainAggro);
}
void printVillainAction(int villain, int preVillain, int citizen, int precitizen) {
	if (villain != preVillain) {
		printf("villain is trolling! The location changes.\n");
		printf("villain: %d -> %d, citizen: %d -> %d\n", preVillain, villain, precitizen, citizen);
	}
	else
		printf("villain does nothing.\n");
}
int villainMove(int villain, int citizen, int precitizen) {
	if (citizen != precitizen)
		villain--;
	return villain;
}
int villainAggroChange(int villain, int previllain, int villainAggro) {
	if (villain != previllain) {
		villainAggro++;
		if (villainAggro > AGGRO_MAX) villainAggro = AGGRO_MAX;
	}
	else {
		villainAggro--;
		if (villainAggro < 0) villainAggro = 0;
	}
	return villainAggro;
}
int villainAction(int citizen, int villain) {
	if (citizen == villain - 1 || citizen == villain + 1) {
		int ran = rand() % 100;
		if (ran < 30)
			villain = citizen;
	}
	return villain;
} 



int main(void) {
	srand((unsigned int)time(NULL));

	// ��������
	int trainL, percent;										  // �⺻����
	int citizen[2] = { 0 }, zombie, mds[3] = { 0 };               // 0 : ��ġ, 1 : ��׷�, 2 : ü��
	int preCitizen[2] = { 0 }, preZombie, preMds[3] = { 0 };      // ���� ����
	int infectionNum = 0, mdsMoveNum = 0, mdsPullNum = 0;         // ���� �Ǵ� ���� 
	int turn = 1;					 							  // ��

	//��Ʈ��
	intro(); 

	//�������� �Է�
	trainL = inputTrainL();
	mds[2] = inputMdsStamina();
	percent = inputPercent();
	
	citizen[0] = trainL - 6;
	zombie = trainL - 3;
	mds[0] = trainL - 2;

	preCitizen[0] = citizen[0]; 
	preZombie = zombie;
	preMds[0] = mds[0];  
	preMds[2] = mds[2]; 

	// �ʱ⿭�� ���
	printf("\n\n\n");
	printTrain(trainL, citizen[0], zombie, mds[0]);
	printf("\n\n\n");
	
	//stage 1
	while (1) {
		// �� ���
		printf("turn: %d\n", turn);



		// �̵�
		// �ù��̵�,��׷�
		citizen[0] = citizenMove(citizen[0], percent);
		citizen[1] = citizenAggroChange(citizen[1], citizen[0], preCitizen[0]);
		
		// ���� �̵�
		if (turn % 2 == 1 && mdsPullNum == 0) {
			zombie = zombieMove(zombie, percent, citizen[0], mds[0], citizen[1], mds[1]);
		}

		// ���� ���
		printTrain(trainL, citizen[0], zombie, mds[0]);

		// �ù�, ���� �̵���Ȳ���
		printCitizenData(citizen[0], preCitizen[0], preCitizen[1], citizen[1]);
		printZombieData(turn, zombie, preZombie, mdsPullNum);
		preCitizen[0] = citizen[0];
		preCitizen[1] = citizen[1];  
		preZombie = zombie;
		// pullNum �ʱ�ȭ
		mdsPullNum = 0;
		
		// ������ �̵�(�Է�),��׷�
		mdsMoveNum = inputMdsMove(mds[0], zombie); 
		mds[0] = mdsMove(mdsMoveNum, mds[0]);
		mds[1] = mdsAggroChange(mds[1], mds[0], preMds[0]); 

		// ���� ���
		printTrain(trainL, citizen[0], zombie, mds[0]);
		printf("\n"); 

		// ������ ���� ���(��ġ, ��׷� ��ȭ����)
		printMdsData(mds[0], preMds[0], preMds[1], mds[1], mds[2]);  
		preMds[0] = mds[0]; 
		preMds[1] = mds[1];



		// �ൿ	
		// �ù��ൿ���
		if (citizen[0] == 1) {
			citizenWin();
			break;
		}
		else
			printf("citizen does nothing.\n"); 

		// �����ൿ
		infectionNum = zombieAction(zombie, citizen[0], mds[0], citizen[1], mds[1]);  
		// ���� �ൿ�� ���� ������ ü�°���
		mds[2] = mdsInfection(infectionNum, mds[2]); 
		// ���� �ൿ ���
		if (infectionNum == 0 || infectionNum == 3 )
			zombieWin();
		else
			printzombieAction(infectionNum, mds[2], preMds[2], citizen[1], mds[1]);

		preMds[2] = mds[2]; 

		// ������ ���񿡰� ���
		if (mds[2] <= STM_MIN) { 
			zombieWin(); 
		}
		
		// ������ �ൿ
		// ������ �ൿ �Է�
		int mdsActionNum = inputMdsAction(zombie, mds[0]); 

		// ������ �ൿ, �ൿ���
		switch (mdsActionNum) {
		case ACTION_REST : 
			mds[1] = mdsRestAggro(mds[1]);
			mds[2] = mdsRsetStamina(mds[2]);
			printRest(mds[1], preMds[1], mds[2], preMds[2]); 
			break;
		case ACTION_PROVOKE :
			mds[1] = AGGRO_MAX;
			printProvo(mds[1], preMds[1], mds[2]);
			break;
		case ACTION_PULL: 
			mdsPullNum = mdsPull(percent);
			mds[1] = mdsPullAggro(mds[1]);
			mds[2]--;
			printPull(mdsPullNum, mds[1], preMds[1], mds[2], preMds[2]);
		}
		if (mds[2] <= STM_MIN) { 
			zombieWin();
			break;
		}
		preMds[1] = mds[1];
		preMds[2] = mds[2]; 

		// �� +1
		turn += 1;
	}

	return 0;
}