struct ROBOT{
    char nickname[16];
    int health;
    int damage;
    int defence;
    int range;
    int rate;
    int speed;
    int accurracy;
    int rank;
};

enum WEAPONS {laserSMG, plasmaGun, railCannon, nanoDistructor};
enum ARMORS {powerT45, powerT51, powerT60, powerX01};
enum VEHICLES {wheels, tracks, airscrews, walkers};

int menu(char * command[], int size, int numMenu);
void printMenu(char * command[], int selected, int size);
void nullRobot(int size, struct ROBOT pRobots[size]);
void print(struct ROBOT * pRobots, int x, int y);
void chooseWeapon(struct ROBOT * pRobots, int selected);
void chooseArmor(struct ROBOT * pRobots, int selected);
void chooseVehicle(struct ROBOT * pRobots, int selected);
void createRobot(struct ROBOT * pRobots);
void loadGame(struct ROBOT * Robots);
void saveGame(struct ROBOT * Robots);
void duel(struct ROBOT * Robot1, struct ROBOT * Robot2);
void printcommand(int x, int y, int length, int high);
void bender(int x, int y);
void printRating(int size, struct ROBOT Robots[size]);
void robot(int x, int y, int state);
void printShot(int x, int y, int state);
void printHealth(char * nick, int health, int x, int y);
void advantages(int selected, int numMenu);
