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

// stage3,4 �ùε� �迭
int citizens[LEN_MAX/2] = { 0 };					// �ùε� ��ġ
int preCitizens[LEN_MAX/2] = { 0 };					// �ùε� ������ġ 
int citizensAggro[LEN_MAX / 2] = { 0 };		        // �ùε� ��׷� 
int preCitizensAggro[LEN_MAX / 2] = { 0 };		    // �ùε� ���� ��׷� 
int zombies[LEN_MAX / 2] = { 0 };			 		// ����� ��ġ
int preZombies[LEN_MAX / 2] = { 0 };			 	// ����� ������ġ

// �Լ�����

// ��Ʈ�� �ƿ�Ʈ��
void intro(void);
void citizenWin(void);
void zombieWin(void);

//�Է�
int inputTrainL();
int inputPercent();
int inputMdsStam();
int inputMdsMove(int, int);
int inputMdsAction(int, int);

// ���
void printTrain(int, int, int, int);
void printCitizenMove(int, int, int, int);
void printZombieMove(int, int, int, int);
void printMdsMove(int, int, int, int, int);
void printMovePhase1(int turn, int trainL, int mdsPullNum, int cPosition, int preCPosition, int cAggro, int preCAggro, int zPosition, int perZPosition, int mPosition);
void printMovePhase2(int trainL, int cPosition, int zPosition, int mPosition, int preMPosition, int mAggro, int preMAggro, int mStm);

// <�ൿ> ���
void printRestAction(int, int, int, int, int);
void printProvoAction(int, int, int, int);
void printPullAction(int, int, int, int, int, int);
void printzombieAction(int infectionNum, int mdsStamina, int preMdsStamina, int citizenAggro, int mdsAggro);
void printActionPhase1(int zombieActionNum, int cAggro, int mAggro, int mStm, int preMStm);
void printActionPhase2(int mPosition, int mActionNum, int mAggro, int preMAggro, int mStm, int preMStm, int mdsPullNum);

// �̵�, ��׷�
int citizenMove(int, int);
int zombieMove(int, int, int, int, int, int, int, int);
int mdsMove(int, int);
int citizenAggroChange(int, int, int);
int mdsAggroChange(int, int, int);

// ������ �ൿ
int mdsInfection(int, int);
int mdsRestAggro(int);
int mdsRsetStamina(int);
int mdsPull(int);
int mdsPullAggro(int);
int mdsActionStm(int mActionNum, int mStm);
int mdsActionAggro(int mActionNum, int mAggro);
// �ൿ
int citizenAction(int citizen);
int zombieAction(int, int, int, int, int);

// stage2 �Լ�
void printStage2(void);
void printTrain2(int trainL, int citizen, int zombie, int madongseok, int villain);
int villainMove(int villain, int citizen, int precitizen);
int villainAction(int citizen, int villain);
int villainAction2(int cPosition, int vPosition, int preVPosition);
void printVillainMove(int villain, int preVillain, int villainAggro, int preVillainAggro);
void printVillainAction(int villain, int preVillain, int citizen, int precitizen);
void printSt2MovePhase1(int turn, int trainL, int mdsPullNum, int cPosition, int preCPosition, int cAggro, int preCAggro, int zPosition, int preZPosition, int mPosition, int vPosition, int preVPosition);
void printSt2ActionPhase1( int zombieActionNum, int cAggro, int mAggro, int mStm, int preMStm, int vPosition, int preVPosition, int cPosition, int preCPosition);

// stage3, 4 �����Լ� 
int citizensMoveSt34(int arrLength, int percent);


// stage3 �Լ�
void printStage3();

void citizensSetting(int citizensNum, int trainL, int arrLength, int cPosition);
void printTrainSt3(int trainL, int zPosition, int mPosition);

void printcitizensMove34(int escapeNum, int arrLength);

// stage 4 �Լ�
void printStage4(void);
void citizensTurn0();

void printTrainSt4(int trainL, int mPosition, int zArrLength);
int zombieMoveSt4(int citizen, int zombie, int percent, int madonseok, int citizenAggro, int mdsAggro, int turn, int mdsPullNum, int i, int backZombie, int frontZombie);
int zombiesMoveSt4(int zArrLength, int arrLength, int percent, int mPosition, int mAggro, int turn, int mdsPullNum);
int zombieActionSt4(int zombie, int citizen, int madongseok, int citizenAggro, int mdsAggro, int endZombie);

void printzombiesMoveSt4(int zArrLength, int turn, int mdsPullNum);

// �Լ� ����
// skipStage
int intputskipStage() {
	int skipStageNum;
	while (1) {
		printf("skip stage? (1: yes, 2: no) >> ");
		scanf_s("%d", &skipStageNum);
		if (skipStageNum == 1 || skipStageNum == 2) break;
	}
	return skipStageNum;
}

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
int inputMdsStam() {
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
		else {
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
// <�̵�> ���
void printCitizenMove(int citizen, int preCitizen, int preCitizenAggro, int CitizenAggro) {
	printf("\n");
	if (citizen != preCitizen && preCitizenAggro != CitizenAggro)
		printf("citizen: %d -> %d (aggro: %d -> %d)\n", preCitizen, citizen, preCitizenAggro, CitizenAggro); 
	else if (citizen != preCitizen && preCitizenAggro == CitizenAggro)
		printf("citizen: %d -> %d (aggro: %d(not change))\n", preCitizen, citizen, CitizenAggro);
	else if (citizen == preCitizen && preCitizenAggro == CitizenAggro) 
		printf("citizen: stay %d (aggro: %d(not change))\n", citizen, CitizenAggro);
	else
		printf("citizen: stay %d (aggro: %d -> %d)\n", preCitizen, preCitizenAggro, CitizenAggro);
}
void printZombieMove(int zombie, int preZombie, int mdsPullNum, int turn) {
	if (mdsPullNum == 1)
		printf("Zombie can't move by madongseok\n");
	else {
		if (turn % 2 == 1) {
			if (zombie != preZombie)
				printf("Zombie: %d -> %d\n\n", preZombie, zombie);
			else
				printf("Zombie: stay %d\n\n", preZombie);
		}
		else
			printf("Zombie: stay %d(cannot move)\n\n", preZombie);
	}
}
void printMdsMove(int madongseok, int preMadongseok, int preMdsAggro, int mdsAggro, int mdsStamina) {
	if (madongseok != preMadongseok && mdsAggro != preMdsAggro) 
		printf("madongseok: %d -> %d(aggro: %d -> %d, stamina: %d)\n\n",preMadongseok, madongseok, preMdsAggro, mdsAggro, mdsStamina); 
	else if (madongseok == preMadongseok && mdsAggro == preMdsAggro)
		printf("madongseok: stay %d(aggro: %d(not change), stamina: %d)\n\n", madongseok, preMdsAggro, mdsStamina); 
	else if (madongseok == preMadongseok && mdsAggro != preMdsAggro) 
		printf("madongseok: stay %d(aggro: %d -> %d, stamina: %d)\n\n", madongseok, preMdsAggro, mdsAggro, mdsStamina);  
	else
		printf("madongseok: %d -> %d(aggro: %d(not change), stamina: %d)\n\n", preMadongseok, madongseok, mdsAggro, mdsStamina); 
}
void printMovePhase1(int turn, int trainL, int mdsPullNum, int cPosition, int preCPosition, int cAggro, int preCAggro, int zPosition, int perZPosition, int mPosition) {
	printf("turn: %d\n", turn);
	printTrain(trainL, cPosition, zPosition, mPosition);
	printCitizenMove(cPosition, preCPosition, preCAggro, cAggro);
	printZombieMove(zPosition, perZPosition, mdsPullNum, turn);
}
void printMovePhase2(int trainL, int cPosition, int zPosition, int mPosition, int preMPosition, int mAggro, int preMAggro, int mStm) {
	printTrain(trainL, cPosition, zPosition, mPosition);
	printf("\n");
	printMdsMove(mPosition, preMPosition, preMAggro, mAggro, mStm);
}

// <�ൿ> ���
void printRestAction(int mPosition, int mdsAggro, int preMdsAggro, int mdsStamina, int preMdsStamina) {
	printf("\nmadongseok rests...\n");
	if (mdsAggro != preMdsAggro && mdsStamina != preMdsStamina)
	printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", mPosition, preMdsAggro, mdsAggro, preMdsStamina, mdsStamina);
	else if (mdsAggro != preMdsAggro && mdsStamina == preMdsStamina) 
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d(not change))\n\n", mPosition, preMdsAggro, mdsAggro, mdsStamina); 
	else if (mdsAggro == preMdsAggro && mdsStamina != preMdsStamina) 
		printf("madongseok: %d (aggro: %d(not change), stamina: %d -> %d)\n\n", mPosition, mdsAggro, preMdsStamina, mdsStamina); 
	else
		printf("madongseok: %d (aggro: %d(not change), stamina: %d(not change))\n\n", mPosition, mdsAggro, mdsStamina); 
}
void printProvoAction(int mPosition, int mdsAggro, int preMdsAggro, int mdsStamina) {
	printf("\nmadongseok provoked zombie...\n");
	if (mdsAggro == preMdsAggro)
		printf("madongseok: %d (aggro: %d(not change), stamina: %d)\n\n", mPosition, mdsAggro, mdsStamina);
	else
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d)\n\n", mPosition, preMdsAggro, mdsAggro, mdsStamina);
}
void printPullAction(int mPosition, int mdsPullNum, int mdsAggro, int preMdsAggro, int mdsStamina, int preMdsStamina) {
	if (mdsPullNum == 0)
		printf("\nmadongseok failed to pull zombie\n");
	else
		printf("\nmadongseok pulled zombie... Next turn, it can't move\n");

	if (mdsAggro != preMdsAggro) 
		printf("madongseok: %d (aggro: %d -> %d, stamina: %d -> %d)\n\n", mPosition, preMdsAggro, mdsAggro, preMdsStamina, mdsStamina); 
	else 
		printf("madongseok: %d (aggro: %d(not change), stamina: %d -> %d)\n\n", mPosition, mdsAggro, preMdsStamina, mdsStamina); 

} 
void printzombieAction(int infectionNum, int mdsStamina, int preMdsStamina, int citizenAggro, int mdsAggro) {

	switch (infectionNum) {
	case 0 :
		printf("Zomibe attacked citizen.(aggro: %d vs. %d)\n", citizenAggro, mdsAggro);  
		zombieWin(); 
		break;
	case 3:
		printf("Zomibe attacked citizen.\n"); 
		zombieWin();
		break;
	case 1:
	case 2: // �Ѵ� �����ϰ� ��׷ΰ� �������� ������ ����(ppt 14�� ����)
		printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina:  %d -> %d)\n", citizenAggro, mdsAggro, preMdsStamina, mdsStamina);
		break;
	case 4:
		printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", preMdsStamina, mdsStamina); 
		break;
	default:
		printf("zombie attacked nobody.\n");
	}
}
void printActionPhase1(int zombieActionNum, int cAggro, int mAggro, int mStm, int preMStm) {
	// �ù� �ൿ ���
	printf("citizen does nothing.\n");
	// ���� �ൿ ���
	printzombieAction(zombieActionNum, mStm, preMStm, cAggro, mAggro);
}
void printActionPhase2(int mPosition, int mActionNum, int mAggro, int preMAggro, int mStm, int preMStm, int mdsPullNum) {
	switch (mActionNum) {
	case ACTION_REST:
		printRestAction(mPosition, mAggro, preMAggro, mStm, preMStm);
		break;
	case ACTION_PROVOKE:
		printProvoAction(mPosition, mAggro, preMAggro, mStm);
		break;
	case ACTION_PULL:
		printPullAction(mPosition, mdsPullNum, mAggro, preMAggro, mStm, preMStm);
	}
}

// �̵�, ��׷�
int citizenMove(int citizen, int percent) {
	if (citizen != 1) {
		int citizenRandomNum = rand() % 100;
		if (citizenRandomNum < (100 - percent)) {
			citizen--;
		}
	}
	return citizen;  
}
int zombieMove(int citizen, int zombie, int percent, int madonseok, int citizenAggro, int mdsAggro, int turn, int mdsPullNum) {
	if (turn % 2 == 1 && mdsPullNum != 1) {
		int zombieRandomNum = rand() % 100;
		if (zombieRandomNum < percent) { 
			if (citizenAggro < mdsAggro) { 
				if (zombie != madonseok - 1) 
					zombie++; 
			}
			else { 
				if(zombie != citizen + 1) 
					zombie--;  
			}
		}
	}
	return zombie;
}
int mdsMove(int mdsMoveNum, int madongseok) {
	int mdsData = madongseok;
	if (mdsMoveNum == MOVE_LEFT)
		mdsData--;
	return mdsData;
}

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


// ������ �ൿ
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
int mdsActionStm(int mActionNum, int mStm) {

	switch (mActionNum) {
	case ACTION_REST:
		mStm = mdsRsetStamina(mStm);
		break;
	case ACTION_PROVOKE:
		break;
	case ACTION_PULL:
		mStm--;
	}
	return mStm;
}
int mdsActionAggro(int mActionNum, int mAggro) {
	switch (mActionNum) {
	case ACTION_REST:
		mAggro = mdsRestAggro(mAggro);
		break;
	case ACTION_PROVOKE:
		mAggro = AGGRO_MAX;
		break;
	case ACTION_PULL:
		mAggro = mdsPullAggro(mAggro);
	}
	return mAggro;
}
// �ൿ
int citizenAction(int citizen) {
	int citizenActionNum;
	if (citizen == 1)
		citizenActionNum = 1;
	else
		citizenActionNum = 0;
	return citizenActionNum;
}
int zombieAction(int zombie, int citizen, int madongseok, int citizenAggro, int mdsAggro) {
	int infectionNum;
	if (citizen == zombie - 1 && madongseok == zombie + 1) {
		if (citizenAggro > mdsAggro)
			infectionNum = 0;
		else if (citizenAggro < mdsAggro)
			infectionNum = 1;
		else	// �Ѵ� �����ϰ� ��׷ΰ� �������� ������ ����(ppt 14�� ����)
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


// stage2 �Լ�
void printStage2(void) {
	printf(" _____  _____   ___   _____  _____  _____ \n");
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___|/ __  \\\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__  `' / /'\n");
	printf(" `--. \\  | |  |  _  || | __ |  __|   / /  \n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ ./ /___\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/ \\_____/\n");
	printf("\n");
}
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

int villainMove(int villain, int citizen, int precitizen) {
	if (villain != -1) {
		if (citizen != precitizen)
			villain--;
	}
	return villain;
}
int villainAction(int citizen, int villain) {

		if (citizen == villain - 1 || citizen == villain + 1) {
			int ran = rand() % 100;
			if (ran < 30)
				villain = citizen;
		}
	return villain;
} 
int villainAction2(int cPosition, int vPosition, int preVPosition) {
	if (vPosition == cPosition) {
		if (vPosition < preVPosition) cPosition++; 
		else cPosition--;
	}

	return cPosition;
}

void printVillainMove(int villain, int preVillain, int villainAggro, int preVillainAggro) {
	if (villain != -1) {
		if (villain != preVillain && villainAggro != preVillainAggro) 
			printf("villain: %d -> %d (aggro: %d -> %d)\n", preVillain, villain, preVillainAggro, villainAggro);
		else if (villain != preVillain && villainAggro == preVillainAggro)
			printf("villain: %d -> %d (aggro: %d(not change))\n", preVillain, villain, villainAggro); 
		else if (villain == preVillain && villainAggro != preVillainAggro) 
			printf("villain: stay %d (aggro: %d -> %d)\n", villain, preVillainAggro, villainAggro); 
		else
			printf("villain: stay %d (aggro: %d(not change))\n", villain, villainAggro);
	}
}
void printVillainAction(int villain, int preVillain, int citizen, int precitizen) {
	if (villain != preVillain) {
		printf("villain is trolling! The location changes.\n");
		printf("villain: %d -> %d, citizen: %d -> %d\n", preVillain, villain, precitizen, citizen);
	}
	else
		printf("villain does nothing.\n");
}
void printSt2MovePhase1(int turn, int trainL, int mdsPullNum, int cPosition, int preCPosition, int cAggro, int preCAggro, int zPosition, int preZPosition, int mPosition, int vPosition, int preVPosition) {  
	printf("turn: %d\n", turn);
	printTrain2(trainL, cPosition, zPosition, mPosition, vPosition);  
	printCitizenMove(cPosition, preCPosition, preCAggro, cAggro);
	printVillainMove(vPosition, preVPosition, cAggro, preCAggro);     
	printZombieMove(zPosition, preZPosition, mdsPullNum, turn); 
} 
void printSt2MovePhase2(int turn, int trainL, int cPosition, int zPosition, int mPosition, int vPosition, int preMPosition, int preMAggro, int mAggro, int mStm) {
	printTrain2(trainL, cPosition, zPosition, mPosition, vPosition);  
	printMdsMove(mPosition, preMPosition, preMAggro, mAggro, mStm); 
}
void printSt2ActionPhase1(int zombieActionNum, int cAggro, int mAggro, int mStm, int preMStm, int vPosition, int preVPosition, int cPosition, int preCPosition) { 
	// �ù� �ൿ
	printf("citizen does nothing.\n"); 
	// �����ൿ
	if (vPosition != -1)
		printVillainAction(vPosition, preVPosition, cPosition, preCPosition);  
}  

int zombieActionSt2(int zombie, int citizen, int madongseok, int citizenAggro, int mdsAggro, int villain) {
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
	else if (villain == zombie - 1)
		infectionNum = 6;
	else
		infectionNum = 5;
	return infectionNum;
}
 
// stage3, 4 �����Լ� 
int citizensMoveSt34(int arrLength, int percent){  
	// �ù��̵�,��׷� 
	int frontCitizen;
	for (int i = 0; i <= arrLength; i++) {
		if (i == 0)
			frontCitizen = 0;
		else
			frontCitizen = citizens[i - 1];

		if (citizens[i] != 1 && citizens[i] != frontCitizen + 1) { 
			int citizenRandomNum = rand() % 100;
			if (citizenRandomNum < (100 - percent)) {
				citizens[i]--;   
			}
		}

		citizensAggro[i] = citizenAggroChange(citizensAggro[i], citizens[i], preCitizens[i]); 
	}
	return 0;
}

// stage3 �Լ�
void printStage3() { 
	printf(" _____  _____   ___   _____  _____  _____ \n"); 
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___||____ |\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__      / /\n"); 
	printf(" `--. \\  | |  |  _  || | __ |  __|     \\ \\\n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ .___/ /\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/ \\____/ \n");
	printf("\n");

} 

void citizensSetting(int citizensNum, int trainL, int arrLength, int cPosition) {   
	// �ù� ��ġ �Ҵ�
	for (int i = 0; i < citizensNum; i++) {  
		int tmp = i;
		citizens[i] = rand() % (trainL - 8) + 2;  
		for (int j = 0; j < i; j++) {
			if (citizens[i] == citizens[j]) { 
				tmp = i - 1;
				break;
			}
		}
		i = tmp;
	}
	citizens[arrLength] = cPosition;  // stage3 ������ cPostion ���x, citizens[arrLength] �� ��ü.

	// �������� ����
	for (int i = 0; i < citizensNum - 1; i++) {
		for (int j = 0; j < citizensNum - 1 - i; j++) {
			if (citizens[j] > citizens[j + 1]) {
				int tmp = citizens[j];
				citizens[j] = citizens[j + 1];
				citizens[j + 1] = tmp;
			}
		}
	}
	// preCitizens
	for (int i = 0; i <= arrLength; i++) {
		preCitizens[i] = citizens[i];
	}
}
void printTrainSt3(int trainL, int zPosition, int mPosition) {  
	for (int i = 0; i <= trainL - 1; i++) { 
		printf("#");
	}
	printf("\n");
	int cIndex = 0; 
	for (int i = 0; i <= trainL - 1; i++) { 
		if (i == 0 || i == trainL - 1) 
			printf("#");
		else if (i == zPosition) 
			printf("Z"); 
		else if (i == mPosition) 
			printf("M"); 
		else if (i == citizens[cIndex]) { 
			printf("C"); 
			cIndex++; 
		} 
		else
			printf(" "); 
	}
	printf("\n");
	for (int i = 0; i <= trainL - 1; i++) { 
		printf("#"); 
	}
	printf("\n\n\n");
} 

void printcitizensMove34(int escapeNum, int arrLength) { 
	int tmp = escapeNum;
	for (int i = 0; i <= arrLength; i++) { 
		if (preCitizens[i] == citizens[i] && citizensAggro[i] == preCitizensAggro[i]) 
			printf("citizen%d: Stay %d (aggro: %d(not change))\n", tmp, citizens[i], citizensAggro[i]); 
		else if (preCitizens[i] == citizens[i] && citizensAggro[i] != preCitizensAggro[i])
			printf("citizen%d: Stay %d (aggro: %d -> %d)\n", tmp, citizens[i], preCitizensAggro[i], citizensAggro[i]); 
		else if (preCitizens[i] != citizens[i] && citizensAggro[i] == preCitizensAggro[i])  
			printf("citizen%d: %d -> %d (aggro: %d(not change))\n", tmp, preCitizens[i], citizens[i], citizensAggro[i]);  
		else
			printf("citizen%d: %d -> %d (aggro: %d -> %d)\n", tmp, preCitizens[i], citizens[i], preCitizensAggro[i], citizensAggro[i]); 
		// ���� ����
		preCitizens[i] = citizens[i];
		preCitizensAggro[i] = citizensAggro[i]; 
		tmp++;
	}
} 

// stage 4 �Լ�
void printStage4(void) {
	printf(" _____  _____   ___   _____  _____    ___ \n");
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___|  /   |\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__   / /| |\n");
	printf(" `--. \\  | |  |  _  || | __ |  __| / /_| |\n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ \\___  |\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/     |_/\n");
	printf("\n");
}
void citizensTurn0() {
	// citizens[] 0 ���� �ʱ�ȭ 
	for (int i = 0; i < LEN_MAX/2; i++) {
		citizens[i] = 0; 
		citizensAggro[i] = 0; 
		preCitizensAggro[i] = 0; 
		preCitizens[i] = 0; 
	}
}

void printTrainSt4(int trainL,int mPosition, int zArrLength) { 
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n");
	int cIndex = 0;
	int zIndex = zArrLength;  
	for (int i = 0; i <= trainL - 1; i++) {
		if (i == 0 || i == trainL - 1)
			printf("#");
		else if (i == zombies[zIndex]) { 
			printf("Z");
			zIndex++;  
		}
		else if (i == mPosition) 
			printf("M");
		else if (i == citizens[cIndex]) { 
			printf("C");
			cIndex++;
		}
		else
			printf(" ");
	}
	printf("\n");
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n\n\n");
} 
int zombieMoveSt4(int citizen, int zombie, int percent, int madonseok, int citizenAggro, int mdsAggro, int turn, int mdsPullNum, int i, int backZombie, int frontZombie) { 
	if (i == 24) { 
		if (turn % 2 == 1 && mdsPullNum != 1) {
			int zombieRandomNum = rand() % 100;
			if (zombieRandomNum < percent) {
				if (citizenAggro < mdsAggro) {
					if (zombie != madonseok - 1 && zombie != backZombie - 1)
						zombie++;
				}
				else {
					if (zombie != citizen + 1 && zombie != frontZombie + 1)
					zombie--;
				}
			}
		}
	}
	else {
		int zombieRandomNum = rand() % 100;  
		if (zombieRandomNum < percent) { 
			if (citizenAggro < mdsAggro) { 
				if (zombie != madonseok - 1 && zombie != backZombie - 1)
					zombie++; 
			}
			else {
				if (zombie != citizen + 1 && zombie != frontZombie + 1)
					zombie--;
			}
		}
	}

	return zombie;
} 
int zombiesMoveSt4(int zArrLength, int arrLength, int percent, int mPosition, int mAggro, int turn, int mdsPullNum) {
	// ���� �̵�
	int backZombie, frontZombie;
	for (int i = zArrLength; i <= LEN_MAX / 2 - 1; i++) {
		if (i == LEN_MAX/2 -1)
			backZombie = 0;
		else
			backZombie = zombies[i + 1];
		if (i == 0)
			frontZombie = 0;
		else
			frontZombie = zombies[i - 1];

		zombies[i] = zombieMoveSt4(citizens[arrLength], zombies[i], percent, mPosition, citizensAggro[arrLength], mAggro, turn, mdsPullNum, i, backZombie, frontZombie);   
	}
} 
int zombieActionSt4(int zombie, int citizen, int madongseok, int citizenAggro, int mdsAggro, int endZombie) {
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
	else if (madongseok == endZombie + 1) 
		infectionNum = 4;
	else
		infectionNum = 5;
	return infectionNum;
}
void printzombiesMoveSt4(int zArrLength, int turn, int mdsPullNum) { 
	int tmp = 0;
	// ���� �̵� ��� 
	for (int i = zArrLength; i <= 24; i++) {
		if (i == 24) {
			if (turn % 2 == 0)
				printf("zombie%d: Stay %d (cannot move)\n", tmp, zombies[i]);
			else if (mdsPullNum == 1)
				printf("zombie cannot move byt madongseok.\n");
			else if (preZombies[i] == zombies[i])
				printf("zombie%d: Stay %d\n", tmp, zombies[i]);
			else
				printf("zombie%d: %d -> %d\n", tmp, preZombies[i], zombies[i]);
		}
		else {
			if (preZombies[i] == zombies[i])
				printf("zombie%d: Stay %d\n",  tmp, zombies[i]);
			else
				printf("zombie%d: %d -> %d\n", tmp, preZombies[i], zombies[i]);
		}
		// ���� ����
		preZombies[i] = zombies[i];
		tmp++;
	}
	printf("\n");
}

void printYouWin() {
	printf("__   __ _____  _   _   _    _  _____  _   _  _ \n");
	printf("\\ \\ / /|  _  || | | | | |  | ||_   _|| \\ | || |\n");
	printf(" \\ V / | | | || | | | | |  | |  | |  |  \\| || |\n");
	printf("  \\ /  | | | || | | | | |/\\| |  | |  | . ` || |\n");
	printf("  | |  \\ \\_/ /| |_| | \\  /\\  / _| |_ | |\\  ||_|\n");
	printf("  \\_/   \\___/  \\___/   \\/  \\/  \\___/ \\_| \\_/(_)\n");
	printf("\n");
}

void printzombieAction34(int infectionNum, int mdsStamina, int preMdsStamina, int citizenAggro, int mdsAggro) {

	switch (infectionNum) {
	case 1:
	case 2: // �Ѵ� �����ϰ� ��׷ΰ� �������� ������ ����(ppt 14�� ����)
		printf("Zomibe attacked madongseok(aggro: %d vs. %d, madongseok stamina:  %d -> %d)\n", citizenAggro, mdsAggro, preMdsStamina, mdsStamina);
		break;
	case 4:
		printf("Zomibe attacked madongseok(madongseok stamina: %d -> %d)\n", preMdsStamina, mdsStamina);
		break;
	default:
		printf("zombie attacked nobody.\n");
	}
}


int main(void) {
	// ���� �õ�
	srand((unsigned int)time(NULL));
	// ��������
	int trainL, percent;										          // �⺻����
	int cPosition, cAggro, preCPosition, preCAggro;                       // �ù����� (����, ����)
	int zPosition, preZPosition;										  // �������� (����, ����)
	int mPosition, mAggro, mStm, preMPosition, preMAggro, preMStm;		  // ���������� (����, ����)
	int mdsMoveNum = 0, mdsPullNum = 0;									  // ������(�̵�, �ൿ)
	int citizenActionNum, zombieActionNum, mActionNum;					  // �ൿ����
	int turn = 1;					 									  // ��

	//��Ʈ��
	intro();

	//�������� �Է�
	trainL = inputTrainL();
	mStm = inputMdsStam();
	percent = inputPercent();

	cPosition = trainL - 6;
	zPosition = trainL - 3;
	mPosition = trainL - 2;

	preCPosition = cPosition;
	preZPosition = zPosition;
	preMPosition = mPosition;

	cAggro = AGGRO_MIN, preCAggro = AGGRO_MIN;
	mAggro = AGGRO_MIN, preMAggro = AGGRO_MIN;
	mStm = STM_MAX, preMStm = STM_MAX;

	// �ʱ⿭�� ���
	printf("\n\n\n");
	printTrain(trainL, cPosition, zPosition, mPosition);
	printf("\n\n\n");

	int skipStageNum = 2;
	// skipStageNum = intputskipStage();
	while (1) {
		// skipStage
		if (skipStageNum == 1) break; 

		// <�̵�> phase

		// �ù��̵�,��׷�
		cPosition = citizenMove(cPosition, percent);
		cAggro = citizenAggroChange(cAggro, cPosition, preCPosition);
		// ���� �̵�
		zPosition = zombieMove(cPosition, zPosition, percent, mPosition, cAggro, mAggro, turn, mdsPullNum);

		// <�̵�>1(����, �ù�, ���� �̵���Ȳ) ���
		printMovePhase1(turn, trainL, mdsPullNum, cPosition, preCPosition, cAggro, preCAggro, zPosition, preZPosition, mPosition);

		// �������� 
		preCPosition = cPosition;
		preCAggro = cAggro;
		preZPosition = zPosition;
		mdsPullNum = 0;

		// ������ �̵�, ��׷�
		mdsMoveNum = inputMdsMove(mPosition, zPosition);
		mPosition = mdsMove(mdsMoveNum, mPosition);
		mAggro = mdsAggroChange(mAggro, mPosition, preMPosition);

		// <�̵�>2(����, ������ �̵���Ȳ) ���
	    printMovePhase2(trainL, cPosition, zPosition, mPosition, preMPosition, mAggro, preMAggro, mStm);

		// ��������
		preMPosition = mPosition;
		preMAggro = mAggro;

		// <�ൿ> Phase

		// �ù� �ൿ
		if (cPosition == 1) {
			citizenWin();
			break;
		}
		// ���� �ൿ
		zombieActionNum = zombieAction(zPosition, cPosition, mPosition, cAggro, mAggro);
		// ���� �ൿ�� ���� ������ ü�°���
		mStm = mdsInfection(zombieActionNum, mStm);

		// <�ൿ>1(�ù�, ����) ���
		printActionPhase1(zombieActionNum, cAggro, mAggro, mStm, preMStm);
		// ���� �¸�
		if (zombieActionNum == 0 || zombieActionNum == 3) return 0;  

		// ��������
		preMStm = mStm;
		// ������ ���񿡰� ���	
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// ������ �ൿ �Է�
		mActionNum = inputMdsAction(zPosition, mPosition);

		// ������ �ൿ
		mAggro = mdsActionAggro(mActionNum, mAggro);
		mStm = mdsActionStm(mActionNum, mStm);
		if (mActionNum == 2)
			mdsPullNum = mdsPull(percent);

		// <�ൿ>2(������) ���
		printActionPhase2(mPosition, mActionNum, mAggro, preMAggro, mStm, preMStm, mdsPullNum);
		// ������ PULL�ൿ���� ���� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}
		// ��������
		preMAggro = mAggro;
		preMStm = mStm;

		turn++;
	}
	

	// Stage2 
	printStage2();

	// ����
	int vPosition = trainL - 5;
	int preVPosition = vPosition;
	// ������׷� == �ùξ�׷�

	// ���� �ʱ�ȭ
	cPosition = trainL - 6;
	zPosition = trainL - 3;
	mPosition = trainL - 2;

	preCPosition = cPosition;
	preZPosition = zPosition;
	preMPosition = mPosition;

	cAggro = AGGRO_MIN, preCAggro = AGGRO_MIN;
	mAggro = AGGRO_MIN, preMAggro = AGGRO_MIN;
	mStm = STM_MAX, preMStm = STM_MAX;

	zombieActionNum = 0;

	turn = 1;

	// �ʱ⿭�� ���
	printf("\n\n\n");
	printTrain2(trainL, cPosition, zPosition, mPosition, vPosition); 
	printf("\n\n\n");

	
	// skipStageNum = intputskipStage();
	while (1) {
		// skipStage
		if (skipStageNum == 1) break;

		// <�̵�> Phase
		
		// �ù��̵�,��׷�
		cPosition = citizenMove(cPosition, percent);
		cAggro = citizenAggroChange(cAggro, cPosition, preCPosition);
		// �����̵�
		vPosition = villainMove(vPosition, cPosition, preCPosition);
		// ���� �̵�
		zPosition = zombieMove(cPosition, zPosition, percent, mPosition, cAggro, mAggro, turn, mdsPullNum);

		// <�̵�>1(����, �ù�,����,���� �̵���Ȳ) ���
		printSt2MovePhase1(turn, trainL, mdsPullNum, cPosition, preCPosition, cAggro, preCAggro, zPosition, preZPosition, mPosition, vPosition, preVPosition);
		// �������� 
		preCPosition = cPosition;
		preVPosition = vPosition;
		preZPosition = zPosition;
		preCAggro = cAggro;
		mdsPullNum = 0;

		// ������ �̵�, ��׷�
		mdsMoveNum = inputMdsMove(mPosition, zPosition);
		mPosition = mdsMove(mdsMoveNum, mPosition);
		mAggro = mdsAggroChange(mAggro, mPosition, preMPosition);

		// <�̵�>2(����, ������ �̵���Ȳ) ���
		printSt2MovePhase2(turn, trainL, cPosition, zPosition, mPosition, vPosition, preMPosition, preMAggro, mAggro, mStm);
		// ��������
		preMPosition = mPosition;
		preMAggro = mAggro;

		// <�ൿ> Phase
		
		// �ù� �ൿ
		citizenActionNum = citizenAction(cPosition);
		if (cPosition == 1) {
			citizenWin();
			break;
		}
		// �����ൿ  
		if (vPosition == 1) // ���� Ż��� ��ġ�� -1 �� ����
			vPosition = -1;
		vPosition = villainAction(cPosition, vPosition);
		cPosition = villainAction2(cPosition, vPosition, preVPosition);

		// <�ൿ>1(�ù�, ����) ���
		printSt2ActionPhase1(zombieActionNum, cAggro, mAggro, mStm, preMStm, vPosition, preVPosition, cPosition, preCPosition);

		// ������ �ൿ �Է�
		mActionNum = inputMdsAction(zPosition, mPosition);

		// ������ �ൿ
		mAggro = mdsActionAggro(mActionNum, mAggro);
		mStm = mdsActionStm(mActionNum, mStm);
		if (mActionNum == 2) 
			mdsPullNum = mdsPull(percent);  

		// <�ൿ>2(������) ���
		printActionPhase2(mPosition, mActionNum, mAggro, preMAggro, mStm, preMStm, mdsPullNum);
		// ������ PULL�ൿ���� ���� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// ��������
		preMAggro = mAggro;
		preMStm = mStm;

		// ���� �ൿ 
		zombieActionNum = zombieActionSt2(zPosition, cPosition, mPosition, cAggro, mAggro, vPosition); 
		// ���� �ൿ�� ���� ������ ü�°���
		mStm = mdsInfection(zombieActionNum, mStm);
		// ���� <�ൿ> ���
		if (zombieActionNum == 6) {
			vPosition = -1;
			printf("Zomibe attacked villain.\n");
		}
		else
			printzombieAction(zombieActionNum, mStm, preMStm, cAggro, mAggro);
		// ���� �¸�
		if (zombieActionNum == 0 || zombieActionNum == 3) return 0;
		
		// ������ ���񿡰� ���	 
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// ���� ���� 
		preCPosition = cPosition;
		preVPosition = vPosition;
		preMStm = mStm;
		// �� + 1
		turn++;
	}

	// stage3
	printStage3();

	// ���� �ʱ�ȭ
	cPosition = trainL - 6;
	zPosition = trainL - 3;
	mPosition = trainL - 2;

	preCPosition = cPosition;
	preZPosition = zPosition;
	preMPosition = mPosition;

	cAggro = AGGRO_MIN, preCAggro = AGGRO_MIN;
	mAggro = AGGRO_MIN, preMAggro = AGGRO_MIN;
	mStm = STM_MAX, preMStm = STM_MAX;

	turn = 1;

	// stage 3,4 ����
	// �̵�
	// stage 3,4��  �ùε�, ������� ���� �ù� & ���� �̵����� �ʰ� ���θ��� ������ �̵��� �� ���� �����Ͽ����ϴ�.
	// ��������
	// stage 3,4 �� ���� ���� ������ ������ �����ϴ� ����, ������ �����ϱ� ���ؼ��� �� ������ ��ϵ� �ù��� 1���� ���� ������ ������ �����ϰ� �˴ϴ�. �׶� ���� �Ѹ��� �ù��� Ż���ϸ�, �ù��� �¸�, ���񿡰� ������ ������ �¸��� �Ǵ� ������ �����ϰ� �׷��� �����Ͽ����ϴ�. 
	// ���� �ù� ���
	// �ù��� Ż�� ������, ���񿡰� �������� ��� (" %dcitizen(s) alive(s).", ���� ĭ �ȿ� �����ִ� �ùμ�) �� ����Ͽ����ϴ�.


	// stage3 ����
	int citizensNum = rand() % ((trainL / 2) - (trainL / 4) + 1) + ((trainL / 4) - 1);
	int arrLength = citizensNum;		        // arrLength == �����ִ� �ù� �� - 1,  citizens[arrLenth] == ���� ������ �ù��� ��ġ
	
	int escapeNum = 0;			                // Ż���� �ù��� ��ȣ (Ż�� ��¿�)
	int attackedCitizenNum = arrLength;         // ���ݴ��� �ù��� ��ȣ (���� ��¿�)

	// citizens ����
	citizensSetting(citizensNum, trainL, arrLength, cPosition); 

	// ���� ���
	printTrainSt3(trainL, zPosition, mPosition); 

	// skipStage
	// skipStageNum = intputskipStage();
	while (1) {
		// skipStage
		if (skipStageNum == 1) break;

		// �ù��̵�,��׷� 
		citizensMoveSt34(arrLength, percent); 
		// ���� �̵�
		zPosition = zombieMove(citizens[arrLength], zPosition, percent, mPosition, cAggro, mAggro, turn, mdsPullNum);

		// �����
		printf("turn: %d\n", turn); 
		// ���� ���
		printTrainSt3(trainL, zPosition, mPosition); 
		// �ù� �̵� ���
		printcitizensMove34(escapeNum, arrLength); 
		// ���� <�̵�> ���
		printZombieMove(zPosition, preZPosition, mdsPullNum, turn);
		// ��������
		preZPosition = zPosition;
		mdsPullNum = 0;


		// ������ �̵�, ��׷�
		mdsMoveNum = inputMdsMove(mPosition, zPosition);
		mPosition = mdsMove(mdsMoveNum, mPosition);
		mAggro = mdsAggroChange(mAggro, mPosition, preMPosition);
		// ���� ���
		printTrainSt3(trainL, zPosition, mPosition);  
		// <�̵�>2 (������) ���
		printMdsMove(mPosition, preMPosition, preMAggro, mAggro, mStm);
		// ��������
		preMPosition = mPosition;
		preMAggro = mAggro;

		// <�ൿ>
		
		// �ù� Ż��� Ż���ൿ ���, �迭 �б�
		if (citizens[0] == 1) { 
			printf("citizen%d escaped to the next train.\n", escapeNum); 
			printf("%dcitizen(s) alive(s).\n", arrLength); 
			escapeNum++; 
			for (int i = 0; i <= arrLength; i++) {  // ���� ������ �ù��� ��ġ�� citizens[0]�� ���� �� �� �ֵ��� �迭��������.
				citizens[i] = citizens[i + 1]; 
				preCitizens[i] = preCitizens[i + 1]; 
			}
			arrLength--;
			if (arrLength < 0) arrLength = 0; 
			// ������������
			if (citizens[arrLength] == 0) {
				citizenWin();
				break;
			}
		}
		else
			printf("citizen does nothing.\n"); 

		// ���� �ൿ
		zombieActionNum = zombieAction(zPosition, citizens[arrLength], mPosition, cAggro, mAggro);
		// ���� �ൿ�� ���� ������ ü�°���
		mStm = mdsInfection(zombieActionNum, mStm);
		// ���� �ൿ ���
		if (zombieActionNum == 0 || zombieActionNum == 3) {
			if (zombieActionNum == 0)
				printf("citizen%d has been attacked by zombie.(aggro: %d vs. %d)\n", attackedCitizenNum, cAggro, mAggro); 
			else
				printf("citizen%d has been attacked by zombie.\n", attackedCitizenNum); 
			
			printf("%dcitizen(s) alive(s).\n", arrLength);
			citizens[arrLength] = 0;
			arrLength--;
			attackedCitizenNum--;
			if (arrLength < 0) {
				arrLength = 0;
				zombieWin(); 
				return 0;
			}
		}
		else
			printzombieAction34(zombieActionNum, mStm, preMStm, cAggro, mAggro);
		// ���� �¸�
		if (zombieActionNum == 0 || zombieActionNum == 3) return 0; 

		// ��������
		preMStm = mStm;
		// ������ ���񿡰� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// ������ �ൿ �Է�
		mActionNum = inputMdsAction(zPosition, mPosition);
		// ������ �ൿ
		mAggro = mdsActionAggro(mActionNum, mAggro);
		mStm = mdsActionStm(mActionNum, mStm);
		if (mActionNum == 2) 
			mdsPullNum = mdsPull(percent); 
		// <�ൿ>2(������) ���
		printActionPhase2(mPosition, mActionNum, mAggro, preMAggro, mStm, preMStm, mdsPullNum);
		// ������ PULL�ൿ���� ���� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// ��������
		preMAggro = mAggro;
		preMStm = mStm;
		turn++;
	}
	printStage4();

	// ���� �ʱ�ȭ
	cPosition = trainL - 6;
	zPosition = trainL - 3;
	mPosition = trainL - 2;

	preCPosition = cPosition;
	preZPosition = zPosition;
	preMPosition = mPosition;

	cAggro = AGGRO_MIN, preCAggro = AGGRO_MIN;
	mAggro = AGGRO_MIN, preMAggro = AGGRO_MIN;
	mStm = STM_MAX, preMStm = STM_MAX;

	turn = 1;

	citizensNum = rand() % ((trainL / 2) - (trainL / 4) + 1) + ((trainL / 4) - 1); 
	arrLength = citizensNum;		     	// citizens �迭 �ε��� == �ù� �� - 1,  citizens[arrLenth] == ���� ������ �ù��� ��ġ

	escapeNum = 0;							// Ż���� �ù��� ��ȣ (Ż�� ��¿�) 
	attackedCitizenNum = arrLength;         // ���ݴ��� �ù��� ��ȣ (���� ��¿�)
	

	// stage 4 ����
	int zArrLength = LEN_MAX / 2 - 1;			// zArrLenght == (LEN_MAX/2) - (���� ��), zombies[zArrLengh] == ���� ���� ������ ��ġ 
	zombies[zArrLength] = zPosition;			// stage4 ������ zPostion ���x, zombie[zArrLength] �� ��ü.  zombie[] �� �ڿ��� ���� ����.
	preZombies[zArrLength] = zPosition;
	

	// citizens[] 0 ���� �ʱ�ȭ
	citizensTurn0();
	/// citizens ����
	citizensSetting(citizensNum, trainL, arrLength, cPosition); 
	// ���� ���
	printTrainSt4(trainL, mPosition, zArrLength);  

	while (1) {
		// �ù��̵�,��׷� 
		citizensMoveSt34(arrLength, percent); 
		// ���� �̵�
		zombiesMoveSt4(zArrLength, arrLength, percent, mPosition, mAggro, turn, mdsPullNum);  

		printf("turn: %d\n", turn);
		// ���� ���
		printTrainSt4(trainL, mPosition, zArrLength); 
		// �ù� �̵� ���
		printcitizensMove34(escapeNum, arrLength);  
		// ���� �̵� ��� 
		printzombiesMoveSt4(zArrLength, turn, mdsPullNum); 

		// ������ �̵�, ��׷� 
		mdsMoveNum = inputMdsMove(mPosition, zombies[24]);
		mPosition = mdsMove(mdsMoveNum, mPosition); 
		mAggro = mdsAggroChange(mAggro, mPosition, preMPosition); 
		// ���� ���
		printTrainSt4(trainL, mPosition, zArrLength);
		// <�̵�>2 (������) ���
		printMdsMove(mPosition, preMPosition, preMAggro, mAggro, mStm); 
		// �������� 
		preMPosition = mPosition; 
		preMAggro = mAggro; 

		// �ù� Ż��� Ż���ൿ ���, �迭 �б�
		if (citizens[0] == 1) { 
			printf("citizen%d escaped to the next train.\n", escapeNum); 
			printf("%dcitizen(s) alive(s).\n", arrLength); 
			escapeNum++;  
			for (int i = 0; i <= arrLength; i++) { 
				citizens[i] = citizens[i + 1]; 
				preCitizens[i] = preCitizens[i + 1];
				citizensAggro[i] = citizensAggro[i + 1];
				preCitizensAggro[i] = preCitizensAggro[i + 1];
			}
			arrLength--; 
			if (arrLength < 0) arrLength = 0; 
			// �������� 
			if (citizens[arrLength] == 0) { 
				citizenWin();
				printYouWin();
				break; 
			}
		}
		else
			printf("citizen does nothing.\n"); 

		// ���� �ൿ����
		zombieActionNum = zombieActionSt4(zombies[zArrLength], citizens[arrLength], mPosition, citizensAggro[arrLength], mAggro, zombies[24]);
		// ���� �ൿ�� ���� ������ ü�°��� 
		mStm = mdsInfection(zombieActionNum, mStm); 
		// ���� �ൿ ��� 
		if (zombieActionNum == 0 || zombieActionNum == 3) { 
			if (zombieActionNum == 0) 
				printf("citizen%d has been attacked by zombie.(aggro: %d vs. %d)\n", attackedCitizenNum,  cAggro, mAggro); 
			else
				printf("citizen%d has been attacked by zombie.\n", attackedCitizenNum); 
		
			printf("citizen%d turned into a zombie!\n", attackedCitizenNum);
			printf("%dcitizen(s) alive(s).\n", arrLength);  
			zArrLength--;
			zombies[zArrLength] = citizens[arrLength];  // �ù� -> ���� ����
			preZombies[zArrLength] = citizens[arrLength];	
			citizens[arrLength] = 0; 
			arrLength--; 
			attackedCitizenNum--;
			if (arrLength < 0) {  
				arrLength = 0; 
				zombieWin(); 
				return 0;
			} 
		}
		else
			printzombieAction34(zombieActionNum, mStm, preMStm, citizensAggro[arrLength], mAggro); 
		// ���� �¸�
		if (zombieActionNum == 0 || zombieActionNum == 3) return 0; 
		// ��������
		preMStm = mStm; 
		// ������ ���񿡰� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}
			

		// ������ �ൿ �Է� 
		mActionNum = inputMdsAction(zombies[LEN_MAX / 2 - 1], mPosition);   
		// ������ �ൿ
		mAggro = mdsActionAggro(mActionNum, mAggro); 
		mStm = mdsActionStm(mActionNum, mStm); 
		if (mActionNum == 2) 
			mdsPullNum = mdsPull(percent);  
		// <�ൿ>2(������) ���
		printActionPhase2(mPosition, mActionNum, mAggro, preMAggro, mStm, preMStm, mdsPullNum); 
		// ������ PULL�ൿ���� ���� ���
		if (mStm <= STM_MIN) {
			zombieWin();
			return 0;
		}

		// �������� 0
		preMAggro = mAggro; 
		preMStm = mStm; 
		turn++; 
	}

	return 0;
}
