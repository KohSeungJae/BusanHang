#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int citizen[2] = { 0 }, zombie, mds[3] = { 0 }, villain[2] = { 0 };               // 0 : 위치, 1 : 어그로, 2 : 체력
int preCitizen[2] = { 0 }, preZombie, preMds[3] = { 0 }, preVillain[2] = { 0 };   // 이전 정보 
int citizens[25] = { 0 };

//파라미터
#define LEN_MIN 15     // 기차 길이
#define LEN_MAX 50
#define STM_MIN 0	  // 마동석 체력
#define STM_MAX 5
#define PROB_MIN 10    // 확률
#define PROB_MAX 90
#define AGGRO_MIN 0    //어그로 범위
#define AGGRO_MAX 5

// 마동석 이동방향
#define MOVE_LEFT 1
#define MOVE_STAY 0

// 좀비의 공격대상
#define ATK_NONE 0
#define ATK_CITIZEN 1 
#define ATK_DONGSEOK 2 

// 마동석 행동
#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// 함수선언

// 인트로 아웃트로
void intro(void);
void citizenWin(void);
void zombieWin(void);

//입력
int inputTrainL();
int inputPercent();
int inputMdsStamina();
int inputMdsMove(int, int);
int inputMdsAction(int, int);

// 출력
void printTrain(int, int, int, int); 
void printCitizenData(int, int, int, int);
void printZombieData(int, int, int, int);
void printMdsData(int, int, int, int, int);
//void printCitizenAction(int);
void printRest(int, int, int, int);
void printProvo(int, int, int);
void printPull(int, int, int, int, int);

// 이동
int citizenMove(int,int);
int zombieMove(int, int, int, int, int);
int mdsMove(int, int);

// 어그로
int citizenAggroChange(int, int, int);
int mdsAggroChange(int, int, int);

// 행동
int zombieAction(int, int, int, int, int);
int mdsInfection(int, int);
int mdsRestAggro(int);
int mdsRsetStamina(int);
int mdsPull(int); 
int mdsPullAggro(int);
 

// 함수 정의

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

// 인트로
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

// 입력
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

// 출력
void printTrain(int trainL, int citizen, int zombie, int madongseok) {
	//열차 첫번째 줄 출력
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n");

	//열차 두번째 줄 출력
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

	//열차 세번째 줄 출력
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
void printZombieData(int zombie, int preZombie, int mdsPullNum, int turn) {
	if (mdsPullNum == 1) 
		printf("Zombie can't move by madongseok\n");
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

// 이동
int citizenMove(int citizen, int percent) {
	int citizenData = citizen;
	int citizenRandomNum = rand() % 100; 
	if (citizenRandomNum < (100 - percent)) { 
		citizenData--;
	}
	return citizenData;
}
int zombieMove(int zombie, int percent,  int madonseok, int citizenAggro, int mdsAggro) {
	int zombieData = zombie;
	int zombieRandomNum = rand() % 100; 
	if (zombieRandomNum < percent) {
		if (citizenAggro < mdsAggro) {
			if (zombieData != madonseok - 1) 
				zombieData++;
		}
		else 
				zombieData--;
		
	}
	return zombieData;
}
int mdsMove(int mdsMoveNum, int madongseok) {
	int mdsData = madongseok;
	if (mdsMoveNum == MOVE_LEFT)	
		mdsData--; 
	return mdsData;
}

// 어그로
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

// 행동
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

// stage2 함수
void printTrain2(int trainL, int citizen, int zombie, int madongseok, int villain) {
	//열차 첫번째 줄 출력
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n");

	//열차 두번째 줄 출력
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

	//열차 세번째 줄 출력
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

// stage3 함수
void printStage3() {
	printf(" _____  _____   ___   _____  _____  _____ \n");
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___||____ |\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__      / /\n");
	printf(" `--. \\  | |  |  _  || | __ |  __|     \\ \\\n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ .___/ /\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/ \\____/ \n");
	printf("\n");

}
void printTrain13(int trainL) {
	for (int i = 0; i <= trainL - 1; i++) {
		printf("#");
	}
	printf("\n");

}
int citizensMove(int citizen, int preCitizen) {
	int res = 0;
	if (citizen != preCitizen)
		res = -1;
	return res;
}
void printCitizensData(int citizen, int preCitizen, int preCitizenAggro, int CitizenAggro) {
	printf("\n");
	if (citizen != preCitizen)
		printf("citizens: move (aggro: %d -> %d)\n", preCitizenAggro, CitizenAggro);
	else
		printf("citizens: stay  (aggro: %d -> %d)\n", preCitizenAggro, CitizenAggro);
}

// stage 4 함수
void printStage4(void) {
	printf(" _____  _____   ___   _____  _____    ___ \n");
	printf("/  ___||_   _| / _ \\ |  __ \\|  ___|  /   |\n");
	printf("\\ `--.   | |  / /_\\ \\| |  \\/| |__   / /| |\n");
	printf(" `--. \\  | |  |  _  || | __ |  __| / /_| |\n");
	printf("/\\__/ /  | |  | | | || |_\\ \\| |___ \\___  |\n");
	printf("\\____/   \\_/  \\_| |_/ \\____/\\____/     |_/\n");
	printf("\n");
}


int main(void) {
	srand((unsigned int)time(NULL));

	// 변수선언
	int trainL, percent;										  // 기본정보
	int infectionNum = 0, mdsMoveNum = 0, mdsPullNum = 0;         // 여부 판단 변수 
	int turn = 1;					 							  // 턴

	//인트로
	intro(); 

	//열차정보 입력
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

	// 초기열차 출력
	printf("\n\n\n");
	printTrain(trainL, citizen[0], zombie, mds[0]);
	printf("\n\n\n");
	
	int skipStageNum = intputskipStage(); 

	//stage 1
	while (1) {
		// skipStage
		if (skipStageNum == 1) break;

		// 턴 출력
		printf("turn: %d\n", turn);



		// 이동
		// 시민이동,어그로
		citizen[0] = citizenMove(citizen[0], percent);
		citizen[1] = citizenAggroChange(citizen[1], citizen[0], preCitizen[0]);
		
		// 좀비 이동
		if (turn % 2 == 1 && mdsPullNum == 0) {
			zombie = zombieMove(zombie, percent, mds[0], citizen[1], mds[1]);
		}

		// 열차 출력
		printTrain(trainL, citizen[0], zombie, mds[0]);

		// 시민, 좀비 이동현황출력
		printCitizenData(citizen[0], preCitizen[0], preCitizen[1], citizen[1]);
		printZombieData(turn, zombie, preZombie, mdsPullNum);
		preCitizen[0] = citizen[0];
		preCitizen[1] = citizen[1];  
		preZombie = zombie;
		// pullNum 초기화
		mdsPullNum = 0;
		
		// 마동석 이동(입력),어그로
		mdsMoveNum = inputMdsMove(mds[0], zombie); 
		mds[0] = mdsMove(mdsMoveNum, mds[0]);
		mds[1] = mdsAggroChange(mds[1], mds[0], preMds[0]); 

		// 열차 출력
		printTrain(trainL, citizen[0], zombie, mds[0]);
		printf("\n"); 

		// 마동석 정보 출력(위치, 어그로 변화가능)
		printMdsData(mds[0], preMds[0], preMds[1], mds[1], mds[2]);  
		preMds[0] = mds[0]; 
		preMds[1] = mds[1];



		// 행동	
		// 시민행동출력
		if (citizen[0] == 1) {
			citizenWin();
			break;
		}
		else
			printf("citizen does nothing.\n"); 

		// 좀비행동
		infectionNum = zombieAction(zombie, citizen[0], mds[0], citizen[1], mds[1]);  
		// 좀비 행동에 따른 마동석 체력감소
		mds[2] = mdsInfection(infectionNum, mds[2]); 
		// 좀비 행동 출력
		if (infectionNum == 0 || infectionNum == 3 )
			zombieWin();
		else
			printzombieAction(infectionNum, mds[2], preMds[2], citizen[1], mds[1]);

		preMds[2] = mds[2]; 

		// 마동석 좀비에게 사망
		if (mds[2] <= STM_MIN) { 
			zombieWin(); 
		}
		
		// 마동석 행동
		// 마동석 행동 입력
		int mdsActionNum = inputMdsAction(zombie, mds[0]); 

		// 마동석 행동, 행동출력
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
		if (mds[2] <= STM_MIN) 
			zombieWin();

		preMds[1] = mds[1];
		preMds[2] = mds[2]; 

		// 턴 +1
		turn += 1;
	}

	// Stage2
	printStage2(); 

	// 변수 초기화
	citizen[0] = trainL - 6;
	villain[0] = trainL - 5;
	zombie = trainL - 3;
	mds[0] = trainL - 2;

	preCitizen[0] = citizen[0];
	preVillain[0] = villain[0];
	preZombie = zombie;
	preMds[0] = mds[0];
	
	citizen[1] = 0, preCitizen[1] = 0;
	mds[1] = 0, preMds[1] = 0;
	mds[2] = STM_MAX, preMds[2] = STM_MAX; 

	turn = 1;
	skipStageNum = 2;
	
	// 초기열차 출력
	printf("\n\n\n");
	printTrain2(trainL, citizen[0], zombie, mds[0], villain[0]);
	printf("\n\n\n");

	// skipStage
	skipStageNum = intputskipStage(); 
	
	while (1) {
		// skipStage
		if (skipStageNum == 1) break;

		// 이동
		// 시민이동,어그로
		citizen[0] = citizenMove(citizen[0], percent);
		citizen[1] = citizenAggroChange(citizen[1], citizen[0], preCitizen[0]);

		// 빌런이동, 어그로
		villain[0] = villainMove(villain[0], citizen[0], preCitizen[0]);
		villain[1] = villainAggroChange(villain[0], preVillain[0], villain[1]);

		// 좀비 이동
		if (turn % 2 == 1 && mdsPullNum == 0) {
			zombie = zombieMove(zombie, percent, citizen[0], mds[0], citizen[1], mds[1]);
		}

		// 턴 출력
		printf("turn: %d\n", turn);

		// 열차 출력
		printTrain2(trainL, citizen[0], zombie, mds[0], villain[0]);

		// 시민, 빌런, 좀비 이동현황출력
		printCitizenData(citizen[0], preCitizen[0], preCitizen[1], citizen[1]);
		printVillainData(villain[0], preVillain[0], villain[1], preVillain[1]);
		printZombieData(zombie, preZombie, mdsPullNum, turn);
		preCitizen[0] = citizen[0];
		preCitizen[1] = citizen[1];
		preVillain[0] = villain[0];
		preVillain[1] = villain[1];
		preZombie = zombie;

		// pullNum 초기화
		mdsPullNum = 0;

		// 마동석 이동 입력
		mdsMoveNum = inputMdsMove(mds[0], zombie);
		mds[0] = mdsMove(mdsMoveNum, mds[0]);
		mds[1] = mdsAggroChange(mds[1], mds[0], preMds[0]);

		// 빌런행동 -> <행동> 열차 출력에 반영
		villain[0] = villainAction(citizen[0], villain[0]);
		if (villain[0] == citizen[0]) { 
			if (villain[0] < preVillain[0]) citizen[0]++;
			else citizen[0]--; 
		}

		// 열차 출력
		printTrain2(trainL, citizen[0], zombie, mds[0], villain[0]);
		printf("\n");

		// 마동석 정보 출력(위치, 어그로 변화가능)
		printMdsData(mds[0], preMds[0], preMds[1], mds[1], mds[2]);
		preMds[0] = mds[0];
		preMds[1] = mds[1];

		// 행동	
		// 시민행동출력
		if (citizen[0] != 1) 
			printf("citizen does nothing.\n");


			// 빌런행동 출력
			printVillainAction(villain[0], preVillain[0], citizen[0], preCitizen[0]);
			preCitizen[0] = citizen[0];
			preVillain[0] = villain[0];

			// 시민탈출(빌런의 행동으로 탈출이 가능하기 때문에 빌런행동 출력 다음에 실행)
			if (citizen[0] == 1) {
				citizenWin();
				break;
			}

			// 마동석 행동
			// 마동석 행동 입력
			int mdsActionNum = inputMdsAction(zombie, mds[0]);

			// 마동석 행동, 행동출력
			switch (mdsActionNum) {
			case ACTION_REST:
				mds[1] = mdsRestAggro(mds[1]);
				mds[2] = mdsRsetStamina(mds[2]);
				printRest(mds[1], preMds[1], mds[2], preMds[2]);
				break;
			case ACTION_PROVOKE:
				mds[1] = AGGRO_MAX;
				printProvo(mds[1], preMds[1], mds[2]);
				break;
			case ACTION_PULL:
				mdsPullNum = mdsPull(percent);
				mds[1] = mdsPullAggro(mds[1]);
				mds[2]--;
				printPull(mdsPullNum, mds[1], preMds[1], mds[2], preMds[2]);
			}
			if (mds[2] <= STM_MIN)
				zombieWin();

			preMds[1] = mds[1];
			preMds[2] = mds[2];

			// 좀비행동
			infectionNum = zombieAction(zombie, citizen[0], mds[0], citizen[1], mds[1]); 
			// 좀비 행동에 따른 마동석 체력감소 
			mds[2] = mdsInfection(infectionNum, mds[2]); 
			// 좀비 행동 출력 
			if (infectionNum == 0 || infectionNum == 3) 
				zombieWin(); 
			else
				printzombieAction(infectionNum, mds[2], preMds[2], citizen[1], mds[1]); 
			printf("\n");

			preMds[2] = mds[2]; 

			// 마동석 좀비에게 사망
			if (mds[2] <= STM_MIN) 
				zombieWin(); 
			
			// 턴 +1
			turn += 1;
	}

	// stage3
	// 시민수 생성
	int trainLD4 = trainL / 4;
	int citizensNum = rand() % trainLD4 + (trainLD4 - 1);
	int arrLength = citizensNum;
	int escapeNum = arrLength;
	int esNum = 0;
	int attackedCitizenNum = -1;
	int citizenIndex[25] = { 0 };
	int indicater; 

	// 변수초기화
	citizen[0] = trainL - 6;
	villain[0] = trainL - 5;
	zombie = trainL - 3;
	mds[0] = trainL - 2;
	turn = 1;

	// 시민 위치 할당
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
	citizens[arrLength] = citizen[0];

	// 오름차순 정렬
	for (int i = 0; i < citizensNum - 1; i++) {
		for (int j = 0; j < citizensNum - 1 - i; j++) {
			if (citizens[j] > citizens[j + 1]) {
				int tmp = citizens[j];
				citizens[j] = citizens[j + 1];
				citizens[j + 1] = tmp;
			}
		}
	}

	printStage3();

	printf("\n\n\n");
	printTrain13(trainL);

	//열차 두번째 줄 출력
	indicater = 0;
	for (int i = 0; i <= trainL - 1; i++) {
		if (i == 0 || i == trainL - 1)
			printf("#");
		else if (i == zombie)
			printf("Z");
		else if (i == mds[0])
			printf("M");
		else if (i == citizens[indicater]) {
			printf("C");
			indicater++;
		}
		else
			printf(" ");
	}
	printf("\n");
	printTrain13(trainL);
	printf("\n\n");

	while (1) {
		// 턴 출력
		printf("turn: %d\n", turn);

		// 이동
		// 시민이동,어그로 
		citizens[arrLength] = citizenMove(citizens[arrLength], percent);
		citizen[1] = citizenAggroChange(citizen[1], citizens[arrLength], preCitizen[0]);
		for (int i = 0; i < arrLength; i++) {
			citizens[i] += citizensMove(citizens[arrLength], preCitizen[0]);
		}
		// 좀비 이동
		if (turn % 2 == 1 && mdsPullNum == 0) {
			zombie = zombieMove(zombie, percent, mds[0], citizen[1], mds[1]);
		}

		// 열차 출력
		printTrain13(trainL);
		//열차 두번째 줄 출력
		indicater = 0;
		for (int i = 0; i <= trainL - 1; i++) {
			if (i == 0 || i == trainL - 1)
				printf("#");
			else if (i == zombie)
				printf("Z");
			else if (i == mds[0])
				printf("M");
			else if (i == citizens[indicater]) {
				printf("C");
				indicater++;
			}
			else
				printf(" ");
		}
		printf("\n");
		printTrain13(trainL);
		printf("\n\n");

		printf("\n");
		if (citizens[arrLength] != preCitizen[0]) {
			int tmp = esNum;
			for (int i = 0; i <= arrLength; i++) {
				printf("citizen%d: %d -> %d (aggro: %d -> %d)\n", tmp, citizens[i] + 1, citizens[i], preCitizen[1], citizen[1]);
				tmp++;
			}
		}
		else
			printf("citizens: stay  (aggro: %d -> %d)\n", preCitizen[1], citizen[1]);
		printZombieData(zombie, preZombie, mdsPullNum, turn);

		preCitizen[0] = citizens[arrLength];
		preCitizen[1] = citizen[1];
		preZombie = zombie;
		// pullNum 초기화
		mdsPullNum = 0;


		// 마동석 이동(입력),어그로
		mdsMoveNum = inputMdsMove(mds[0], zombie);
		mds[0] = mdsMove(mdsMoveNum, mds[0]);
		mds[1] = mdsAggroChange(mds[1], mds[0], preMds[0]);


		// 열차 출력
		printTrain13(trainL);
		//열차 두번째 줄 출력
		indicater = 0;
		for (int i = 0; i <= trainL - 1; i++) {
			if (i == 0 || i == trainL - 1)
				printf("#");
			else if (i == zombie)
				printf("Z");
			else if (i == mds[0])
				printf("M");
			else if (i == citizens[indicater]) {
				printf("C");
				indicater++;
			}
			else
				printf(" ");
		}
		printf("\n");
		printTrain13(trainL);
		printf("\n\n");


		// 마동석 정보 출력(위치, 어그로 변화가능)
		printMdsData(mds[0], preMds[0], preMds[1], mds[1], mds[2]);
		preMds[0] = mds[0];
		preMds[1] = mds[1];


		// 시민 탈출시 탈출행동 출력, 배열 밀기
		if (citizens[0] == 1) {
			printf("citizen%d escaped to the next train.\n", escapeNum);
			printf("%dcitizen(s) alive(s).\n", arrLength);
			escapeNum--;
			esNum++;
			for (int i = 0; i <= arrLength; i++) {
				citizens[i] = citizens[i + 1];
			}
			arrLength--;
			if (arrLength < 0) arrLength = 0;
			// 게임종료
			if (citizens[arrLength] == 0) break;
		}
		else
			printf("citizen does nothing.\n");


		// 좀비 행동
		infectionNum = zombieAction(zombie, citizens[arrLength], mds[0], citizen[1], mds[1]);
		// 좀비 행동에 따른 마동석 체력감소
		mds[2] = mdsInfection(infectionNum, mds[2]);
		// 좀비 행동 출력
		if (infectionNum == 0 || infectionNum == 3) {
			attackedCitizenNum++;
			printf("citizen%d has been attacked by zombie.\n", attackedCitizenNum);
			printf("%dcitizen(s) alive(s).\n", arrLength);
			citizens[arrLength] = 0;
			arrLength--;
			if (arrLength < 0) {
				arrLength = 0;
				zombieWin();
			}
		}
		else
			printzombieAction(infectionNum, mds[2], preMds[2], citizen[1], mds[1]);

		preMds[2] = mds[2];

		// 마동석 좀비에게 사망
		if (mds[2] <= STM_MIN) {
			zombieWin();
		}

		// 마동석 행동
		// 마동석 행동 입력
		int mdsActionNum = inputMdsAction(zombie, mds[0]);

		// 마동석 행동, 행동출력
		switch (mdsActionNum) {
		case ACTION_REST:
			mds[1] = mdsRestAggro(mds[1]);
			mds[2] = mdsRsetStamina(mds[2]);
			printRest(mds[1], preMds[1], mds[2], preMds[2]);
			break;
		case ACTION_PROVOKE:
			mds[1] = AGGRO_MAX;
			printProvo(mds[1], preMds[1], mds[2]);
			break;
		case ACTION_PULL:
			mdsPullNum = mdsPull(percent);
			mds[1] = mdsPullAggro(mds[1]);
			mds[2]--;
			printPull(mdsPullNum, mds[1], preMds[1], mds[2], preMds[2]);
		}
		if (mds[2] <= STM_MIN)
			zombieWin();

		preMds[1] = mds[1];
		preMds[2] = mds[2];

		turn++;
	}

	
	printStage4();

	return 0;
}