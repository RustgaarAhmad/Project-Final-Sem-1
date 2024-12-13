#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;


char getCharAtxy(short int x, short int y);
void gotoxy(int x, int y);
void printEnemy1();
void printEnemy2();
void printEnemy3();
void eraseEnemy1();
void eraseEnemy2();
void eraseEnemy3();
void erasePlayer();
void movePlayerLeft();
void movePlayerRight();
void moveEnemy1();
void moveEnemy2();
void moveEnemy3();
void printMaze();
void printheader();
void printPlayer();
void movePlayer();
void movePlayerUp();
void movePlayerDown();
void score();
void shoot();
void printscore();
void moveEnemyBullets();
void generateVerticalEnemyBullet(int eX, int eY);
void generateSecondEnemyBullet(int eX, int eY);
void checkForNextLevel();
void drawbullet();
void erasebullet();
void generateEnemyBullet(int eX, int eY) ;
 
void printBullet(int x, int y);
void eraseBullet(int x, int y);
void makeBulletInactive(int index);
void generateBullet();
void playerShooting();
void Health();
void setColor(int);
void displayEnemyHealth() ;

void playerWin();
void playerLose() ;

void spawnBoss() ;
void printBoss();
void eraseBoss();
void moveBoss();

int enemy1Health = 3; 
int enemy2Health = 3; 
int enemy3Health = 3; 

int enemyBulletX[100], enemyBulletY[100];
bool isEnemyBulletActive[100];
int enemyBulletCount = 0;
int eX1 = 2, eY1 = 2;
int eX2 = 5, eY2 = 31;
int eX3 = 50, eY3 = 10;

int bulletX[100];
int bulletY[100];
bool isBulletActive[100];
int bulletCount=0;
int health=100;
int pX = 4, pY = 13;
int bX=pX+1,bY=pY-1;
int gamescore;

int bossX = 40, bossY = 5;     // Initial position of the boss
int bossHealth = 20;           // Boss health
bool isBossActive = false;  // Whether the boss is active


const int BLUE = 1;
const int WHITE = 7;
void bossLevel();
void level1();
// main()
// {
	
// 	system("cls");
// 	printheader();
// 	system("cls");
// 	printMaze();
// 	printEnemy1();
//     printEnemy2();
//     printEnemy3();
// 	printPlayer();
	
	
// 	while (true)
// 	 {
//     moveEnemy1();
//     moveEnemy2();
//     moveEnemy3();
//     playerShooting();
//     moveEnemyBullets();
//     displayEnemyHealth();
//     printscore();
//     Health();
//     movePlayer();
//     moveBoss();


//     checkForNextLevel(); // Check if it's time to spawn the boss

//     if (health <= 0) {
//         playerLose();
//     }

//     if (!isBossActive && bossHealth <= 0) {
//         playerWin();
//     }

//     Sleep(25);


//     //lose condition
//     if (health <= 0) 
// 	{
//         playerLose();
//     }

//     //win condition 
//     if ((eX1 == -1 && eY1 == -1) && (eX2 == -1 && eY2 == -1) && (eX3 == -1 && eY3 == -1))
// 	 {
//         playerWin();
//     }

//     Sleep(25); 
// 	if (health == 0)
// 	{
// 		Sleep(1000);
// 		system("cls");
// 		playerLose();
// 		break;
// 	}
// }
int main() {
    system("cls");
    printheader();
    system("cls");

    // Start Level 1
    level1();

    // Transition to Boss Level
    bossLevel();

    return 0;
}



void bossLevel() {
    // Initialize Boss Level
    system("cls");
    printMaze();
    printPlayer();
    isBossActive = true;

    while (true) {
        // Boss logic
        if (isBossActive) {
            eraseBoss();
            bossY += (rand() % 2 ? 1 : -1); // Random vertical movement
            bossX += (rand() % 2 ? 1 : -1); // Random horizontal movement

            // Keep the boss within bounds
            if (bossY < 2) bossY = 2;
            if (bossY + 3 > 30) bossY = 27;
            if (bossX < 2) bossX = 2;
            if (bossX + 5 > 100) bossX = 95;

            printBoss();
        }

        playerShooting();
        moveEnemyBullets();
        Health();
        printscore();
        movePlayer();

        // Lose condition
        if (health <= 0) {
            playerLose();
        }

        // Win condition for Boss Level
        if (bossHealth <= 0) {
            eraseBoss();
            playerWin();
        }

        Sleep(25); // Control game speed
    }
}

void printBoss() {
    gotoxy(bossX, bossY);
    cout << "#####"; // Boss top row
    gotoxy(bossX, bossY + 1);
    cout << "#BOSS#"; // Boss middle row
    gotoxy(bossX, bossY + 2);
    cout << "#####"; // Boss bottom row
}

void eraseBoss() {
    gotoxy(bossX, bossY);
    cout << "     "; // Clear boss top row
    gotoxy(bossX, bossY + 1);
    cout << "     "; // Clear boss middle row
    gotoxy(bossX, bossY + 2);
    cout << "     "; // Clear boss bottom row
}

void level1() {
    // Initialize Level 1
    system("cls");
    printMaze();
    printEnemy1();
    printEnemy2();
    printEnemy3();
    printPlayer();

    while (true) {
        moveEnemy1();
        moveEnemy2();
        moveEnemy3();
        playerShooting();
        moveEnemyBullets();
        displayEnemyHealth();
        printscore();
        Health();
        movePlayer();

        // Lose condition
        if (health <= 0) {
            playerLose();
        }

        // Win condition for Level 1
        if ((eX1 == -1 && eY1 == -1) && (eX2 == -1 && eY2 == -1) && (eX3 == -1 && eY3 == -1)) {
            break; // Transition to the Boss Level
        }

        Sleep(25); // Control game speed
    }
}


void gotoxy(int x, int y)
{
	COORD coordinates;
	coordinates.X = x;
	coordinates.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

char getCharAtxy(short int x, short int y)
{
	CHAR_INFO ci;
	COORD xy = {0, 0};
	SMALL_RECT rect = {x, y, x, y};
	COORD coordBufSize;
	coordBufSize.X = 1;
	coordBufSize.Y = 1;
	return ReadConsoleOutput(GetStdHandle(STD_OUTPUT_HANDLE), &ci, coordBufSize, xy, &rect) ? ci.Char.AsciiChar: ' ';
}

void printMaze()
{
	system("color 03");
cout <<"######################################################################################################"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                 $                                                ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##########################                                                                          ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##         $                                            ########################################### ##"<<endl;
cout <<"##                                                      #                                           ##"<<endl;
cout <<"##                                                      #                                           ##"<<endl;
cout <<"##                                                      #                                           ##"<<endl;
cout <<"##                        ##                            #                                           ##"<<endl;
cout <<"##                        ##                            #                                           ##"<<endl;
cout <<"##                        ##                            #                                           ##"<<endl;
cout <<"#######################################                 #                                           ##"<<endl;
cout <<"##                                                      #                                           ##"<<endl;
cout <<"##                                                      #                                           ##"<<endl;
cout <<"##       $                                                                                          ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"## #####                                                                                            ##"<<endl;
cout <<"## #############################                                                                    ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                     $                                                                            ##"<<endl;
cout <<"##                                                                           ###################### ##"<<endl;
cout <<"##                                                                           ##                     ##"<<endl;
cout <<"##                                                                                    $             ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"##                                                                                                  ##"<<endl;
cout <<"######################################################################################################"<<endl;
}

void printBullet(int x, int y)
{
    gotoxy(x,y);
    cout<<"*";
}
void eraseBullet(int x, int y)
{
    gotoxy(x,y);
    cout<<" ";
}
void makeBulletInactive(int index)
{
    isBulletActive[index]= false;
}
void generateBullet()
{
    bulletX[bulletCount]=pX+4;
    bulletY[bulletCount]=pY;
    isBulletActive[bulletCount]= true;
    gotoxy(pX+4,pY);
    cout<<"*";
    bulletCount++;
}

void playerShooting() {
    for (int x = 0; x < bulletCount; x++) 
	{
        if (isBulletActive[x] == true)
		 {
            char next = getCharAtxy(bulletX[x] + 1, bulletY[x]);

        

            // collision Enemy1
            if (bulletX[x] >= eX1 && bulletX[x] <= eX1 + 2 && bulletY[x] >= eY1 && bulletY[x] <= eY1 + 1) 
			{
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
                enemy1Health--; 
                if (enemy1Health <= 0)
				 {
                    eraseEnemy1();
                    eX1 = -1; eY1 = -1;
					enemy1Health--; 
                    gamescore += 100; 
                }
                continue; 
            }

            // Check collision Enemy2
            if (bulletX[x] >= eX2 && bulletX[x] <= eX2 + 2 && bulletY[x] >= eY2 && bulletY[x] <= eY2 + 1)
			 {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
                enemy2Health--; 
                if (enemy2Health <= 0) 
				{
                    eraseEnemy2();
                    eX2 = -1; eY2 = -1; 
					enemy2Health--;
                    gamescore += 150; 
                }
                continue;
            }

            // Check collision Enemy3
            if (bulletX[x] >= eX3 && bulletX[x] <= eX3 + 2 && bulletY[x] >= eY3 && bulletY[x] <= eY3 + 1) 
			{
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
                enemy3Health--; // Decrease health
                if (enemy3Health <= 0) {
                    eraseEnemy3();
                    eX3 = -1; eY3 = -1;
					enemy3Health--;
                    gamescore += 200; 
                }
                continue;
            }

             if (isBossActive && bulletX[x] >= bossX && bulletX[x] <= bossX + 4 &&
                bulletY[x] >= bossY && bulletY[x] <= bossY + 2) {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
                bossHealth--; // Reduce boss health

                if (bossHealth <= 0) {
                    eraseBoss();
                    isBossActive = false; // Deactivate the boss
                    gamescore += 5000;   // Bonus score for defeating the boss
                }
                continue; // Skip further bullet processing
            }


            // Check obstacleswalls
            if (next != ' ')
			 {
                eraseBullet(bulletX[x], bulletY[x]);
                makeBulletInactive(x);
            } else
			 {
                // Move bullet forward
                eraseBullet(bulletX[x], bulletY[x]);
                bulletX[x] += 1;
                printBullet(bulletX[x], bulletY[x]);
            }
        }
    }
}

void Health()
{
    if(((getCharAtxy(pX,pY-1)!=' ') || (getCharAtxy(pX+1,pY-1)!=' ') || (getCharAtxy(pX+2,pY-1)!=' '))
	&&((getCharAtxy(pX,pY-1)!='$') && (getCharAtxy(pX+1,pY-1)!='$') && (getCharAtxy(pX+2,pY-1)!='$')))
    {
        health--;
    }
	if(((getCharAtxy(pX,pY+2)!=' ') || (getCharAtxy(pX+1,pY+2)!=' ') || (getCharAtxy(pX+2,pY+2)!=' '))
	&& ((getCharAtxy(pX,pY+2)!='$') && (getCharAtxy(pX+1,pY+2)!='$') && (getCharAtxy(pX+2,pY+2)!='$')))
    {
        health--;
    }
	if(((getCharAtxy(pX-1,pY)!=' ') || (getCharAtxy(pX-1,pY+1)!=' '))
	&&((getCharAtxy(pX-1,pY)!='$') && (getCharAtxy(pX-1,pY+1)!='$')))
    {
        health--;
    }
	if(((getCharAtxy(pX+3,pY)!=' ') || (getCharAtxy(pX+3,pY+1)!=' '))
	&&((getCharAtxy(pX+3,pY)!='$') && (getCharAtxy(pX+3,pY+1)!='$')))
    {
        health--;
    }
    gotoxy(0, 39);
    cout << "HEALTH:    ";
    gotoxy(0, 39);
    cout << "HEALTH:" << health;
}


void printEnemy1()
{
	gotoxy(eX1, eY1);
	cout << "000" << endl;
	gotoxy(eX1, eY1 + 1);
	cout << "(&)" << endl;
}

void eraseEnemy1()
{
	gotoxy(eX1, eY1);
	cout << "   " << endl;
	gotoxy(eX1, eY1 + 1);
	cout << "   " << endl;
    gotoxy(eX1 + 1, eY1); 
    cout << "$";
}

void moveEnemy1() 
{
	if (eX1 == -1 && eY1 == -1) return;
    eraseEnemy1();
    eX1 = eX1 + 1;
    if (eX1 + 4 == 100)
	 { 
        eX1 = 2;
    }
    printEnemy1();


    if (rand() % 10 == 0)
	 { 
        generateEnemyBullet(eX1, eY1);
    }
	moveEnemyBullets();
    Sleep(50);
}

void printEnemy2()
{
	gotoxy(eX2, eY2);
	cout << "000" << endl;
	gotoxy(eX2, eY2 + 1);
	cout << "(#)" << endl;
}
void eraseEnemy2()
{
	gotoxy(eX2, eY2);
	cout << "   " << endl;
	gotoxy(eX2, eY2 + 1);
	cout << "   " << endl;
    gotoxy(eX2 + 1, eY2); 
    cout << "$";
}
void moveEnemy2() 
{
	  if (eX2 == -1 && eY2 == -1) return;
    eraseEnemy2();
    eX2 = eX2 + 1; 
    if (eX2 + 4 == 100)
     { 
        eX2 = 5;
    }
    printEnemy2();

    //shoot vertically
    if (rand() % 15 == 0)
	 { 
        generateSecondEnemyBullet(eX2, eY2);
    }
	moveEnemyBullets();
    Sleep(50);
}
void printEnemy3()
{
	gotoxy(eX3, eY3);   
	cout << "000" << endl;
	gotoxy(eX3, eY3 + 1);
	cout << "(@)" << endl;
}
void eraseEnemy3() {
    gotoxy(eX3, eY3);
    cout << "   "; 
    gotoxy(eX3, eY3 + 1);
    cout << "   "; 
  
}

void moveEnemy3() 
{
	if (eX3 == -1 && eY3 == -1) return;
    eraseEnemy3();
    // Vertical movement
    eY3 = eY3 + 1; 
    if (eY3 + 2 == 30) 
    { 
        eY3 = 10;
    }
    printEnemy3();


    if (rand() % 10 == 0) 
	{ 
        generateVerticalEnemyBullet(eX3, eY3);
    }
	moveEnemyBullets();
    Sleep(50);
}
void printPlayer()
{
	setColor(BLUE);
    gotoxy(pX,pY);
	cout << "(-)" << endl;
    gotoxy(pX,pY+1);
	cout << "000" << endl;
	setColor(WHITE);

}
void erasePlayer()
{
    gotoxy(pX,pY);
	cout << "   " << endl;
    gotoxy(pX,pY+1);
	cout << "   " << endl;
}
void movePlayer()
{
    if(GetAsyncKeyState(VK_RIGHT))
	{
		movePlayerRight();
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		movePlayerLeft();
	}
	else if(GetAsyncKeyState(VK_UP))
	{
		movePlayerUp();
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		movePlayerDown();
	}
	else if(GetAsyncKeyState(VK_SPACE))
	{
		generateBullet();
	}
}

void movePlayerRight()
{
	if((getCharAtxy(pX+3,pY)!='#') && getCharAtxy(pX+3,pY+1)!='#') 
	{
	score();
    erasePlayer();
    pX=pX+2;
    printPlayer();
	Sleep(5);
	}
    
}

void movePlayerLeft()
{
	if((getCharAtxy(pX-1,pY)!='#') && getCharAtxy(pX-1,pY+1)!='#') 
	{
	score();
	erasePlayer();
    pX=pX-2;
    printPlayer();
	Sleep(5);
	}

}


void movePlayerUp()
{
	
	if((getCharAtxy(pX,pY-1)!='#') && (getCharAtxy(pX+3,pY-1)!='#')) 
	{
		score();
		erasePlayer();
		pY = pY - 1;
		printPlayer();
		Sleep(10);
	}
	
}
void movePlayerDown()
{
	if((getCharAtxy(pX,pY+2)!='#') && getCharAtxy(pX+3,pY+2)!='#')
	{
		score();
		erasePlayer();
		pY = pY + 1;;
		printPlayer();
		Sleep(10);
	}
}



void score() 
{
    bool collected = false;

    // above player
    if (getCharAtxy(pX, pY - 1) == '$' || getCharAtxy(pX + 1, pY - 1) == '$' || getCharAtxy(pX + 2, pY - 1) == '$')
     {
        collected = true;
    }
    // below player
    else if (getCharAtxy(pX, pY + 2) == '$' || getCharAtxy(pX + 1, pY + 2) == '$' || getCharAtxy(pX + 2, pY + 2) == '$')
     {
        collected = true;
    }
    // right player
    else if (getCharAtxy(pX + 3, pY) == '$' || getCharAtxy(pX + 3, pY + 1) == '$') 
    {
        collected = true;
    }
    // left player
    else if (getCharAtxy(pX - 1, pY) == '$' || getCharAtxy(pX - 1, pY + 1) == '$')
     {
        collected = true;
    }

    if (collected)
     {
        gamescore += 500; 
        gotoxy(pX, pY); 
        cout << " ";
    }
}


void printscore()
{
	gotoxy(0, 38);
	cout << "Score:" << gamescore << endl;
}

void shoot()
{
		erasebullet();
		bY--;
		drawbullet();
		Sleep(100);
		erasebullet();
}
void drawbullet()
{
	gotoxy(bX,bY);
	cout<<'0';
}
void erasebullet()
{
	gotoxy(bX,bY);
	cout<<' ';
}

void generateEnemyBullet(int eX, int eY)
 {
    enemyBulletX[enemyBulletCount] = eX + 1;
    enemyBulletY[enemyBulletCount] = eY + 2;
    isEnemyBulletActive[enemyBulletCount] = true;
    gotoxy(eX + 1, eY + 2);
    cout << "^"; 
    enemyBulletCount++;
}


void moveEnemyBullets()
 {
    for (int i = 0; i < enemyBulletCount; i++) 
	{
        if (isEnemyBulletActive[i]) 
		{
            char nextChar = getCharAtxy(enemyBulletX[i], enemyBulletY[i] + 1);

            // Check if bullet hits the player
            if ((enemyBulletY[i] + 1 == pY || enemyBulletY[i] + 1 == pY + 1) &&
                (enemyBulletX[i] >= pX && enemyBulletX[i] <= pX + 2))
				 {
                gotoxy(enemyBulletX[i], enemyBulletY[i]);
                cout << " "; 
                isEnemyBulletActive[i] = false; 
                health--; 
                if (health <= 0) {
                    playerLose(); 
                }
                continue;
            }

            // bullet hitsobstacleboundary
            if (nextChar != ' ')
			 {
                gotoxy(enemyBulletX[i], enemyBulletY[i]);
                cout << " "; 
                isEnemyBulletActive[i] = false; 
            } else {
                // Move bullet downward
                gotoxy(enemyBulletX[i], enemyBulletY[i]);
                cout << " "; 
                enemyBulletY[i]++; 
                gotoxy(enemyBulletX[i], enemyBulletY[i]);
                cout << "^"; 
            }
        }
    }
}


void generateVerticalEnemyBullet(int eX, int eY)
 {
    enemyBulletX[enemyBulletCount] = eX;       
    enemyBulletY[enemyBulletCount] = eY + 1;  
    isEnemyBulletActive[enemyBulletCount] = true;
    gotoxy(eX, eY + 1);
    cout << "^"; 
    enemyBulletCount++;
}
void generateSecondEnemyBullet(int eX, int eY) 
{
    enemyBulletX[enemyBulletCount] = eX + 1; 
    enemyBulletY[enemyBulletCount] = eY + 2; 
    isEnemyBulletActive[enemyBulletCount] = true;
    gotoxy(eX + 1, eY + 2);
    cout << "^"; 
    enemyBulletCount++;
}
void setColor(int color)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(Console, color);
}
void displayEnemyHealth() 
{
    // Display Enemy1 Health
    if (eX1 != -1 && eY1 != -1) 
	{ 
        gotoxy(140, 16);
        cout << "E1H1: " << enemy1Health;
    }

    // Display Enemy2 Health
    if (eX2 != -1 && eY2 != -1) 
	{
        gotoxy(140, 18);
        cout << "E2H2: " << enemy2Health;
    }

    // Display Enemy3 Health
    if (eX3 != -1 && eY3 != -1)
	 {
        gotoxy(140, 20);
        cout <<"E3H3: " << enemy3Health;
    }
}


void playerLose() 
{
system("cls"); 
cout<<" ____     _      __  __ _____    _____       _______ ____  "<<endl; 
cout<<"/ ___|   / \\  |  \\/  | ____|  / _ \\ \\   / / ____|  _ \\ "<<endl;
cout<<"| |  _  / _ \\ | |\\/| |  _|   | | | \\ \\ / /|  _| | |_) |"<<endl;
cout<<"| |_| |/ ___ \\| |  | | |___  | |_| |\\ V / | |___|  _ < "<<endl;
cout<<"\\____/_/   \\_\\_|  |_|_____|  \\___/  \\_/  |_____|_| \\_\\"<<endl;
cout<<" \n\n\n\n\n\n\n\n\n"<<endl;
cout << "Final Score: " << gamescore << endl;
exit(0);
}

void playerWin()
 {
system("cls");
cout<<" ____ ___  _   _  ____ ____      _  _____ _   _  _        _  _____ ___ ___              "<<endl;
cout<<"/ ___/ _ \\| \\ | |/ ___|  _ \\   / \\|_   _| | || |      / \\|_   _|_ _/ _ \\       "<<endl;
cout<<"| |  | | | |  \\| | |  _| |_) |  / _ \\ | | | | | | |     / _ \\ | |  | | | | |        "<<endl;
cout<<"| |__| |_| | |\\  | |_| |  _ <  / ___ \\| | | |_| | |___ / ___ \\| |  | | |_| |        "<<endl;
cout<<"\\____\\___/|_| \\_|\\____|_|_\\_\\/_/   \\_\\_|__\\___/|_____/_/   \\_\\_| |___\\___/ "<<endl;

cout<<"| \\ | | | \\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | |                   "<<endl;               
cout<<"|  \\| | |  \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| |                    "<<endl;                   
cout<<"| |\\  |_|   | || |_| | |_| |   \\ V  V /  | || |\\  |                       "<<endl;                 
cout<<"|_| \\_(_)   |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_|                    "<<endl;
cout<<" \n\n\n\n\n\n\n\n\n"<<endl;
cout << "Final Score: " << gamescore << endl;
exit(0);
}

void printheader()
{
cout<<"   _      _    _____    __ __     _____       _____     __   __    _____                   "<<endl;
cout<<"  /_/\\  /\\_\\  /\\___/\\  /_/\\__/\\  /\\____\\     ) ___ (   /_/\\ /\\_\\ /\\_____\\    "<<endl;
cout<<"  ) ) )( ( ( / / _ \\ \\ ) ) ) ) ) \\/_ ( (    / /\\_/\\ \\  ) ) \\ ( (( (_____/           "<<endl;
cout<<"  /_/ //\\\\ \\_\\\\ \\(_)/ //_/ /_/_/     \\ \\_\\  / /_/ (_\\\\/_/   \\ \\_\\\\ \\__\\   "<<endl;
cout<<"  \\ \\ /  \\ / // / _ \\ \\\\ \\ \\ \\ \\     / / /__\\ \\ )_/ / /\\ \\ \\   / // /__/_   "<<endl;
cout<<"  )_) /\\ (_(( (_( )_) ))_) ) \\ \\   ( (____( \\ \\/_\\/ /  )_) \\ (_(( (_____\\          "<<endl;
cout<<"  \\_\\/  \\/_/ \\/_/ \\_\\/ \\_\\/ \\_\\/    \\/____/  )_____(   \\_\\/ \\/_/ \\/_____/   "<<endl;
cout<<" \n\n\n\n\n\n\n\n\n"<<endl;
cout << "Press any key to start the game...";
getch();
}

void spawnBoss() {
    isBossActive = true;
    bossX = 40; // Center of the screen horizontally
    bossY = 5;  // Start near the top of the screen
    bossHealth = 20; // Reset health
    printBoss();
}


// void moveBoss()
//  {
//     if (!isBossActive) return; // Skip if the boss is not active

//     eraseBoss();

//     // Random horizontal movement
//     if (rand() % 2 == 0) bossX += (rand() % 2 ? 1 : -1);
//     // Random vertical movement
//     if (rand() % 2 == 0) bossY += (rand() % 2 ? 1 : -1);

//     // Keep boss within bounds
//     if (bossX < 2) bossX = 2;
//     if (bossX + 5 > 100) bossX = 95;
//     if (bossY < 2) bossY = 2;
//     if (bossY + 3 > 30) bossY = 27;

//     printBoss();
// }
void moveBoss() {
    if (!isBossActive) return; // Skip if the boss is not active

    eraseBoss(); // Remove boss from its current position

    // Randomly decide direction for horizontal movement
    if (rand() % 2 == 0) bossX += (rand() % 2 ? 1 : -1);

    // Randomly decide direction for vertical movement
    if (rand() % 2 == 0) bossY += (rand() % 2 ? 1 : -1);

    // Ensure the boss stays within boundaries
    if (bossX < 2) bossX = 2;
    if (bossX + 5 > 100) bossX = 95; // Width of the boss is 5
    if (bossY < 2) bossY = 2;
    if (bossY + 3 > 30) bossY = 27; // Height of the boss is 3

    // Randomly shoot bullets downward
    if (rand() % 8 == 0) {
        generateVerticalEnemyBullet(bossX + 2, bossY + 2); // Centered under the boss
    }

    printBoss(); // Draw boss at the new position

    // Display Boss Health
    gotoxy(bossX + 1, bossY - 1); // Position above the boss
    cout << "HP:" << bossHealth;
}

void checkForNextLevel() {
    if (!isBossActive && eX1 == -1 && eX2 == -1 && eX3 == -1) {
        spawnBoss();
    }
}



