#include <iostream>

using namespace std;

struct Ability
{
    //coldomw
    int CurrentCooldown;
    int LimitCooldown;
    //daño
    int damage;
    string name;
};

class Charsters
{
private:
    int life;
    // string name;
    bool live = true;
    string category;
    int cantSkills;
    //datos Entrada
    int locationRow=-1;
    int locationCol=-1;
    //mazmorra
public:
    Ability* skills;
    // cada atributo tiene sus metodos
    Charsters() {};
    //methods create

    void createAbility(int n) {
        this->skills = new Ability[n];
    }

    void deleteSkills() {
        delete[] this->skills;
    }

    //methods set
    void setCantSkill(int n) {
        this->cantSkills = n;
    }
    void setLife(int n) {
        this->life = n;
    }

    void setLive(bool n) {
        this->live = n;
    }

    void setCategory(string n) {
        this->category = n;
    }

    void setCurrentCooldownSkill(int n, int num) {
        this->skills[n].CurrentCooldown = num;
    }

    void setSkill(string skill, int damage, int limitcooldown, int currentcooldown, int n) {
        this->skills[n].name = skill;
        this->skills[n].LimitCooldown = limitcooldown;
        this->skills[n].CurrentCooldown = currentcooldown;
        this->skills[n].damage = damage;
    }

    void setLocationCol(int n) {
        this->locationCol = n;
    }

    void setLocationRow(int n) {
        this->locationRow = n;
    }
    //methods Get

    int getLocationCol() {
        return this->locationCol;
    }

    int getLocationRow() {
        return this->locationRow;
    }

    bool getlive() {
        return this->live;
    }
    int getCantSkill() {
        return this->cantSkills;
    }

    int getLife() {
        return this->life;
    }

    string getCategory() {
        return this->category;
    }

    int getDamageSkill(int n) {
        return this->skills[n].damage;
    }

    int getLimitCooldownSkill(int n) {
        return this->skills[n].LimitCooldown;
    }

    int getCurrentCooldownSkill(int n) {
        return this->skills[n].CurrentCooldown;
    }
};

class Aventurer : public Charsters
{
private:
    //habildad para obstaculos
    bool ar;
    bool pa;
public:
    Aventurer() {};

    void initPlayer(int life, string category) {
        this->setLife(life);
        this->setCategory(category);
        this->createAbility(4);
        this->setCantSkill(4);
        this->typeAventurer(category);
    }

    void typeAventurer(string category) {
        if (category == "AR" || category == "ar" ||  category == "Ar" ||  category == "aR") {
            this->setSkill("Disparo certero", 2, 3, -1, 0);
            this->setSkill("Disparo doble", 2, 2, -1, 1);
            this->setSkill("Tiro simple", 2, 1, -1, 2);
            this->setSkill("Patada simple", 1, 1, -1, 3);
            this->setAR(true);
            this->setPA(false);
        }
        else {
            this->setSkill("Corte vertical", 12, 4, -1, 0);
            this->setSkill("Corte horizontal", 7, 3, -1, 1);
            this->setSkill("Golpe simple", 4, 2, -1, 2);
            this->setSkill("Patada Simple", 2, 1, -1, 3);
            this->setAR(false);
            this->setPA(true);
        }

    };

    //methods get and set
    void setPA(bool a) {
        this->pa = a;
    }
    void setAR(bool a) {
        this->ar = a;
    }

    bool getPA() {
        return this->pa;
    }
    bool getAR() {
        return this->ar;
    }

    //methods logic for obstacles
    bool passObstacle(char ch) {
        if ((ch != 'A' && ch != 'a' )  && (ch != 'R' && ch != 'r') ) return true;
        if (this->getCategory() == "AR" || this->getCategory() == "ar" ||  this->getCategory() == "Ar" ||  this->getCategory() == "aR")
        {
            if (ch == 'R'   || ch == 'r') return this->getAR();
            return this->getPA();

        }
        else {
            if (ch == 'A' || ch == 'a') return this->getPA();
            return this->getAR();
        }
    }


};

class Mounster : public Charsters
{
private:
    //Para saber si bloquea el camino
    bool block;
    //para saber si desaparece
    bool disappear;
    
    //Atributo para saber si el mountro es encontrado
    bool visualized;
public:
    Mounster() {};

    void initMonster(int life, string category) {
        this->setLife(life);
        this->setCategory(category);
        this->typeMounster(category);
        this->setVisualized(0);
    }

    void typeMounster(string category) {
        if (category[0] == 'S' || category[0] == 's') {
            this->createAbility(1);
            this->setCantSkill(1);
            this->setSkill("Embestida", 1, 1, -1, 0);
            this->setBlock(false);
            this->setDisappear(true);
        }
        else if (category[0] == 'O' || category[0] == 'o') {
            this->createAbility(2);
            this->setCantSkill(2);
            this->setSkill("Patada giratoria", 4, 3, -1, 0);
            this->setSkill("Golpe simple", 2, 2, -1, 1);
            this->setBlock(false);
            this->setDisappear(false);
        }
        else {
            this->createAbility(1);
            this->setCantSkill(1);
            this->setSkill("Pisoteada", 5, 2, -1, 0);
            this->setBlock(true);
            this->setDisappear(false);
        }

    }

    //methods set
    void setVisualized(bool op) {
        this->visualized = op;
    }

    void setBlock(bool op) {
        this->block = op;
    }

    void setDisappear(bool op) {
        this->disappear = op;
    }

    //methods get
    bool getVisualized() {
        return this->visualized;
    }

    bool getBlock() {
        return this->block;
    }

    bool getDisappear() {
        return this->disappear;
    }

};

class Mazmorra
{
private:
    Aventurer player;
    //mounstros cantidad y arreglo
    Mounster* mobs;
    int cantMobs;
    int findCant;
    //datos mazmorra
    int amountDungeon; //cantidad de mazmorras
    int Row;//filas
    int Col;//columnas
    char** dungeons;
    //Valores para ganar;
    bool escape;
    bool deadMonster;
    //boleano para saber si el tablero tiene una salida
    bool exit;
    int rowExit;
    int colExit;
public:
    //cada atributo tiene su metodo get y set,a excepcion de lo punteros
    Mazmorra(/* args */) {
        this->amountDungeon = 0;
        this->Row = 0;
        this->Col = 0;
        this->cantMobs = 0;
        this->escape = false;
        this->deadMonster = false;
        this->findCant=0;
        this->exit=false;
        this->rowExit=0;
        this->colExit=0;
    }

    ~Mazmorra(/* args */) {
        player.deleteSkills();
    }

    
   

    void arrMobsInit() {
        this->mobs = new Mounster[10000];
    }

    void deleteMobs() {
        for (int i = 0; i < this->getCantMobs(); i++)
        {
            mobs[i].deleteSkills();
        }
        this->setCantMobs(0);
        delete[] this->mobs;
    }

    //Methods Set
     void setRowExit(int n){
        this->rowExit=n;
    }
    void setColExit(int n){
        this->colExit=n;
    }

    void setExit(bool op){
        this->exit=op;
    }
    void setFindCant(int n){
        this->findCant=n;
    }
    void setEscape(bool op) {
        this->escape = op;
    }

    void setDeadMonster(bool op) {
        this->deadMonster = op;
    }

    void setCantMobs(int n) {
        this->cantMobs = n;
    }

    void setAmountDungeon(int n) {
        this->amountDungeon = n;
    }


    void setRow(int n) {
        this->Row = n;
    }

    void setCol(int n) {
        this->Col = n;
    }

    void setDungeons(char date, int row, int col) {
        this->dungeons[row][col] = date;
    }

    //Methods Get
    int getRowExit(){
        return this->rowExit;
    }
    int getColExit(){
        return this->colExit;
    }

    bool getExit(){
        return this->exit;
    }
    int getFindCant(){
        return this->findCant;
    }
    bool getEscape() {
        return this->escape;
    }

    bool getDeadMonster() {
        return this->deadMonster;
    }

    int getCantMobs() {
        return this->cantMobs;
    }

    int getAmountDungeon() {
        return this->amountDungeon;
    }

    int getRow() {
        return this->Row;
    }

    int getCol() {
        return this->Col;
    }

    char getDungeons(int row, int col) {
        return this->dungeons[row][col];
    }

    //Funcion derestauracion devalores
    void restore() {
        this->setFindCant(0);
        this->dungeonEscape();
        this->deleteDungeon();
        this->deleteMobs();
        this->setEscape(0);
        this->setExit(0);
    }

    void dungeonEscape() {
        //cout<<getEscape()<<" "<<getDeadMonster()<<endl;
        canYouKillThemAll(player);
        //cout<<getEscape()<<" "<<getDeadMonster()<<endl;
        if (getEscape() && getDeadMonster())
        {
            cout << "YOU GET THE GLORY" << endl;
        }
        else if (getEscape()) {
            cout << "YOU SURVIVE" << endl;
        }
        else {
            cout << "YOU DIE" << endl;
        }

    }

    void canYouKillThemAll(Aventurer charster) {
        bool op;
        for (int i = 0, j; i < getCantMobs(); i++)
        {
            if (!mobs[i].getVisualized()) {
                setDeadMonster(0);
                return;
            }
            op = startCombat(charster, mobs[i].getLocationRow(), mobs[i].getLocationCol(), j);
            if ((mobs[i].getlive())) {
                setDeadMonster(0);
                return;
            }
           // cout<<"Heridas "<<mobs[i].getCategory()<<" "<< j <<endl;
        }
        //cout << "Life final: " << charster.getLife() << endl;
        setDeadMonster(1);

    }
    //methods logic
    //Funcion que contiene la logica
    void readerDungeon() {
        string structure;
        int number;
        cin >> number;
        cin >> structure;
        this->player.initPlayer(number, structure);
        cin >> number;
        this->setAmountDungeon(number);

        for (int i = 0; i < this->getAmountDungeon(); i++)
        {
            cin >> number;
            setRow(number);
            cin >> number;
            setCol(number);
            this->arrMobsInit();
            this->createDungeon();
            //Lectura del tablero
            for (int j = 0; j < getRow(); j++)
            {   
                structure= entrace(getCol(),j);
                toRefilDungeon(structure, j);
            }
            //recorrer la matriz para asignar filas y columnas a cada mounstro
           if(getCantMobs() > 0) this->searchMosters();
            //inicio de backtraking
            //this->PrintDungeon();
            testOutput(getRowExit(),getColExit());
            if(player.getLocationCol() != -1 && player.getLocationRow()!= -1 && this->getExit()){
            //cout<<"entro"<<endl;
             this->walkDungeon(this->player, player.getLocationRow(),player.getLocationCol());
            }
            //Fin del backtraking,siguiente tablero
            this->restore();

        }

    }

    void testOutput(int row,int col){
        int zona=0;
        int block=4;
        if(this->getExit()){
            //Abajo
            if ((row+1 <= getRow() - 1)){
                if(getDungeons(row+1,col) == '*') zona++;
            }else block--;
            //Arriba
            if ((row-1 >= 0)){
                if(getDungeons(row-1,col) == '*') zona++;
            }else block--;
            //Derecha
            if ((col+1 <= getCol() - 1)){
                if(getDungeons(row,col+1) == '*') zona++;
            }else block--;
            //Izquierda
            if ((col-1 >= 0)){
                if(getDungeons(row,col-1) == '*') zona++;
            }else block--;
        }

        if(zona == block) setExit(0);
    }
    //Valida si el caracter obtenido es un mounstro
    bool isMonster(char m) {
        string str = "sSoOgG";
        for (char ch : str) {
            if (m == ch) return true;
        }
        return false;
    }
    // Metodos para leer mazmorra
    void searchMosters() {
        int cant = 0;
        for (int i = 0; i < this->getRow(); i++)
        {
            for (int j = 0; j < this->getCol(); j++)
            {
                //como la cantidad de mounstros siempre es menor o igual a las columnas,
                //nunca superara el tama o del arreglo de mobs
                if (isMonster(this->dungeons[i][j]))
                {
                    this->mobs[cant].setLocationRow(i);
                    this->mobs[cant].setLocationCol(j);
                    cant++;
                }
            }


        }
    }

    string entrace(int tam,int row){
        char ch;
        int num;
        string name;
        string str="";
        for (int i = 0; i < tam; i++)
        {
           cin>>ch;
           if (isMonster(ch))
           {
                setCantMobs(getCantMobs()+1);
                name=ch;
                cin>>num;
                this->mobs[getCantMobs() - 1].initMonster(num,name);
                str+=ch;
           }
           else if(ch == 'P' || ch=='p'){
                cin>>ch;
                if(ch == 'e' || ch =='E'){
                    this->player.setLocationRow(row);
                    this->player.setLocationCol(i);
                    
                }
                if(ch == 's' || ch == 'S'){
                    str+='V';
                    this->setExit(true);
                    this->setRowExit(row);
                    this->setColExit(i);
                }else str+=ch;
           }
           else if(ch == 'A'|| ch=='a'){
                cin>>ch;
                str+=ch;
           }else{
            str+=ch;
           }
           
        }
        
        return str;
        
    }

    void deleteDungeon() {
        for (int i = 0; i < getRow(); i++)
        {
            delete[]this->dungeons[i];
        }
        delete[]this->dungeons;
    }

    void toRefilDungeon(string str, int row) {
        for (int i = 0; i < getCol(); i++)
        {
            this->setDungeons(str[i], row, i);
        }

    }

    void createDungeon() {
        this->dungeons = new char* [getRow()];
        for (int i = 0; i < getRow(); i++)
        {
            this->dungeons[i] = new char[getCol()];
        }
    }

    void PrintDungeon() {
        for (int i = 0; i < this->getRow(); i++)
        {
            for (int j = 0; j < this->getCol(); j++)
            {
                cout << this->dungeons[i][j];
            }
            cout << endl;
        }
    }

    int whatMonster(int row, int col) {
        for (int i = 0; i < getCantMobs(); i++)
        {
            if (mobs[i].getLocationRow() == row && mobs[i].getLocationCol() == col)
            {
                return i;
            }

        }
        return -1;
    }

    ///--->Fin<---

    //-->BACKTRING<--
    bool moveToLeft(Aventurer& charter, int row, int col, int& hurt) {
        if (!(col >= 0)) return false;
        if (getDungeons(row, col) == '-') return false;
        if (getDungeons(row, col) == 'V') return true;
        if (this->getDungeons(row, col) != '*' && charter.passObstacle(getDungeons(row, col)))
        {
            if (!(isMonster(getDungeons(row, col)))) return true;
            //Combate,return solo por estar cambiara dependiendo si gana o no;
            return startCombat(charter, row, col, hurt);
        }
        return false;

    }

    bool moveToRight(Aventurer& charter, int row, int col, int& hurt) {
        if (!(col <= getCol() - 1)) return false;
        if (getDungeons(row, col) == '-') return false;
        if (getDungeons(row, col) == 'V') return true;
        if (this->getDungeons(row, col) != '*' && charter.passObstacle(getDungeons(row, col)))
        {
            if (!(isMonster(getDungeons(row, col)))) return true;
            //Combate,return solo por estar cambiara dependiendo si gana o no;
            return startCombat(charter, row, col, hurt);
        }
        return false;
    }

    bool moveToTop(Aventurer& charter, int row, int col, int& hurt) {
        if (!(row >= 0)) return false;
        if (getDungeons(row, col) == '-') return false;
        if (getDungeons(row, col) == 'V') return true;

        if (this->getDungeons(row, col) != '*' && charter.passObstacle(getDungeons(row, col)))
        {
            if (!(isMonster(getDungeons(row, col)))) return true;
            //Combate,return solo por estar cambiara dependiendo si gana o no;
            return startCombat(charter, row, col, hurt);
        }
        return false;
    }

    bool moveToBottom(Aventurer& charter, int row, int col, int& hurt) {
        if (!(row <= getRow() - 1)) return false;
        if (getDungeons(row, col) == '-') return false;
        if (getDungeons(row, col) == 'V') return true;
        if (this->getDungeons(row, col) != '*' && charter.passObstacle(getDungeons(row, col)))
        {
            if (!(isMonster(getDungeons(row, col)))) return true;
            //Combate,return solo por estar cambiara dependiendo si gana o no;
            return startCombat(charter, row, col, hurt);
        }
        return false;
    }
    
    void walkDungeon(Aventurer charster, int row = 0, int col = 0, int hurt = 0) {
        char ch = getDungeons(row,col);
        Objetive(row,col);
        if (getDungeons(row,col) == 'V') setEscape(true);
        if(!(getEscape() && (getFindCant() == getCantMobs()))) {
            for (int i = row; i < this->getRow(); i++)
            {
                for (int j = col; j < this->getCol(); j++)
                {
                    if (this->moveToTop(charster, i - 1, j, hurt)) {
                        setDungeons('-', row, col);
                        //this->PrintDungeon();

                        walkDungeon(charster, i - 1, j, hurt);
                        setDungeons(ch, row, col);
                        if (isMonster(getDungeons(i - 1, j))) {
                            charster.setLife(charster.getLife() + hurt);
                            mobs[this->whatMonster(i - 1, j)].setLive(1);
                        }
                    }
                    if (this->moveToRight(charster, i, j + 1, hurt))
                    {
                        setDungeons('-', row, col);
                        //this->PrintDungeon();
                        walkDungeon(charster, i, j + 1, hurt);
                        setDungeons(ch, row, col);
                        if (isMonster(getDungeons(i, j + 1))) {
                            charster.setLife(charster.getLife() + hurt);
                            mobs[this->whatMonster(i, j + 1)].setLive(1);
                        }

                    }

                    if (this->moveToBottom(charster, i + 1, j, hurt)) {
                        setDungeons('-', row, col);
                        //this->PrintDungeon();

                        walkDungeon(charster, i + 1, j, hurt);
                        setDungeons(ch, row, col);
                        if (isMonster(getDungeons(i + 1, j))) {
                            charster.setLife(charster.getLife() + hurt);
                            mobs[this->whatMonster(i + 1, j)].setLive(1);
                        }
                    }

                    if (this->moveToLeft(charster, i, j - 1, hurt)) {
                        setDungeons('-', row, col);
                        //this->PrintDungeon();

                        walkDungeon(charster, i, j - 1, hurt);
                        setDungeons(ch, row, col);
                        if (isMonster(getDungeons(i, j - 1))) {
                            charster.setLife(charster.getLife() + hurt);
                            mobs[this->whatMonster(i, j - 1)].setLive(1);
                        }
                    }
                    //cout<<"No se puede salir"<<endl;
                    return;

                }

            }

        }

    }

    void Objetive(int row,int col){
        int i=0;
        //Abajo
        if ((row+1 <= getRow() - 1)){
            if (getDungeons(row+1,col) == 'V'){
                setEscape(true);
                
            }
            else if (isMonster(getDungeons(row+1,col)))
            {   
                i=whatMonster(row+1,col);
                if (i != -1){
                    if (!mobs[i].getVisualized()){
                         this->setFindCant(this->getFindCant()+1);
                         mobs[i].setVisualized(true);
                    };
                }
            }
            
        }
        //Arriba
        if ((row-1 >= 0)){
            if (getDungeons(row-1,col) == 'V'){
                setEscape(true);
            
            }
            else if (isMonster(getDungeons(row-1,col)))
            {   
                i=whatMonster(row-1,col);
                if (i != -1){
                    if (!mobs[i].getVisualized()){
                         this->setFindCant(this->getFindCant()+1);
                         mobs[i].setVisualized(true);
                    };
                }
            }
        }
        //Derecha
        if ((col+1 <= getCol() - 1)){
            if (getDungeons(row,col+1) == 'V'){
                setEscape(true); 
            }
            else if (isMonster(getDungeons(row,col+1)))
            {   
                i=whatMonster(row,col+1);
                if (i != -1){
                    if (!mobs[i].getVisualized()){
                         this->setFindCant(this->getFindCant()+1);
                         mobs[i].setVisualized(true);
                    };
                }
            }
        }
        //Izquierda
        if ((col-1 >= 0)){
            if (getDungeons(row,col-1) == 'V'){
                setEscape(true);
            }
            else if (isMonster(getDungeons(row,col-1)))
            {   
                i=whatMonster(row,col-1);
                if (i != -1){
                    if (!mobs[i].getVisualized()){
                         this->setFindCant(this->getFindCant()+1);
                         mobs[i].setVisualized(true);
                    };
                }
            }
        }
        
    }

    /************** COMBATE ****************/

    int HabilidadDisponible(Ability* Arr, int N) {

        for (int i = 0; i < N; i++) {
            if (Arr[i].CurrentCooldown <= -1) {
                /*  cout << Arr[i].name << endl;*/ //QUITAR COMENTARIO PARA TESTEAR
                return i;
            }
        }
        return -1;
    }

    void turnoAventurero(Aventurer& Av, Mounster& Mons) {
        int A = HabilidadDisponible(Av.skills, Av.getCantSkill());
        if (A != -1) {
            Mons.setLife(Mons.getLife() - Av.getDamageSkill(A)); // Hacer dano
            Av.skills[A].CurrentCooldown = Av.skills[A].LimitCooldown; // Establecer cooldown al maximo
            return;
        }

    }

    void turnoMonstruo(Aventurer& Av, Mounster& Mons) {
        int A = HabilidadDisponible(Mons.skills, Mons.getCantSkill());
        if (A != -1) {
            Av.setLife(Av.getLife() - Mons.getDamageSkill(A));  // Hacer danio
            Mons.skills[A].CurrentCooldown = Mons.skills[A].LimitCooldown; // Establecer cooldown al maximo
            return;
        }
    }

    void ReduceCooldownMonstruo(Mounster& Monster) {

        for (int i = 0; i < Monster.getCantSkill(); i++) {

            if (Monster.getCurrentCooldownSkill(i) > -1) Monster.setCurrentCooldownSkill(i, Monster.getCurrentCooldownSkill(i) - 1);

        }
    }
    void ReduceCooldownAventurero(Aventurer& Av) {

        for (int i = 0; i < Av.getCantSkill(); i++) {

            if (Av.getCurrentCooldownSkill(i) > -1) Av.setCurrentCooldownSkill(i, Av.getCurrentCooldownSkill(i) - 1);

        }
    }

    bool Combat(Aventurer& Av, Mounster& Monster, int& hurt) {

        /* El aventurero debe ya estar inicializado */

        // Inicializar monstruo

        //Monster.initMonster(MonsterLife, MonsterC);
        //Monster.typeMounster(MonsterC);

        // int i = 1;                                                        QUITAR COMENTARIO PARA TESTEAR
         //cout << "VIDA MONSTRUO: " << Monster.getLife() << endl;           QUITAR COMENTARIO PARA TESTEAR
        // cout << "VIDA AVENTURERO: " << Av.getLife() << endl;              QUITAR COMENTARIO PARA TESTEAR

        const int AvBaseLife = Av.getLife();
        const int MonsterBaseLife = Monster.getLife();

        hurt = AvBaseLife - Av.getLife();

        if (Monster.getlive() == false && Monster.getBlock() == false) return true;
        if (Monster.getlive() == false && Monster.getBlock() == true) return false;
        while (Monster.getLife() > 0 && Av.getLife() > 0) {

            //     cout << endl << "Ronda " << i << endl;        QUITAR COMENTARIO PARA TESTEAR

            turnoAventurero(Av, Monster);
            //     cout << "VIDA MONSTRUO: " << Monster.getLife() << endl;                               QUITAR COMENTARIO PARA TESTEAR

             //    cout << Av.skills[0].name << ": " << Av.skills[0].CurrentCooldown << endl;            QUITAR COMENTARIO PARA TESTEAR
              //   cout << Av.skills[1].name << ": " << Av.skills[1].CurrentCooldown << endl;            QUITAR COMENTARIO PARA TESTEAR
             //    cout << Av.skills[2].name << ": " << Av.skills[2].CurrentCooldown << endl;            QUITAR COMENTARIO PARA TESTEAR
             //    cout << Av.skills[3].name << ": " << Av.skills[3].CurrentCooldown << endl << endl;    QUITAR COMENTARIO PARA TESTEAR
            if (Monster.getLife() <= 0) {
                Monster.setLife(MonsterBaseLife);
                Monster.setLive(0);
                Av.setCurrentCooldownSkill(0, -1);
                Av.setCurrentCooldownSkill(1, -1);
                Av.setCurrentCooldownSkill(2, -1);
                Av.setCurrentCooldownSkill(3, -1);
                Monster.setCurrentCooldownSkill(0, -1);
                if (Monster.getCategory() == "O" || Monster.getCategory() == "o") {
                    Monster.setCurrentCooldownSkill(1, -1);
                }
                if (Monster.getBlock() == true) { return false; }
                //    cout << Monster.getLife() << endl;     QUITAR COMENTARIO PARA TESTEAR
                //  cout << Av.getLife() << endl;          QUITAR COMENTARIO PARA TESTEAR
                return true;
            }

            turnoMonstruo(Av, Monster);
            hurt = AvBaseLife - Av.getLife();

            //  cout << "VIDA AVENTURERO: " << Av.getLife() << endl;      QUITAR COMENTARIO PARA TESTEAR

             //cout << Monster.skills[0].name << ": " << Monster.skills[0].CurrentCooldown << endl;          QUITAR COMENTARIO PARA TESTEAR
            // cout << Monster.skills[1].name << ": " << Monster.skills[1].CurrentCooldown << endl << endl;  QUITAR COMENTARIO PARA TESTEAR
             //cout << Monster.skills[2].name << ": " << Monster.skills[1].CurrentCooldown << endl << endl;  QUITAR COMENTARIO PARA TESTEAR
            if (Av.getLife() <= 0) {
                Av.setLife(AvBaseLife);
                Av.setCurrentCooldownSkill(0, -1);
                Av.setCurrentCooldownSkill(1, -1);
                Av.setCurrentCooldownSkill(2, -1);
                Av.setCurrentCooldownSkill(3, -1);
                Monster.setCurrentCooldownSkill(0, -1);
                if (Monster.getCategory() == "O" || Monster.getCategory() == "o") {
                    Monster.setCurrentCooldownSkill(1, -1);
                }
                Monster.setLife(MonsterBaseLife);
                return false;
            }


            ReduceCooldownAventurero(Av);
            ReduceCooldownMonstruo(Monster);
            //  cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXX" << endl;        QUITAR COMENTARIO PARA TESTEAR
             // i++;
        }
        return false;
    }

    bool startCombat(Aventurer& charter, int row, int col, int& hurt) {
        int indice = whatMonster(row, col);
        if (indice == -1) return true;
        //cout << charter.getCategory() << " " << charter.getLife() << endl;
        //cout << mobs[indice].getCategory() << " " << mobs[indice].getLife() << endl;
        if (!mobs[indice].getVisualized()) this->setFindCant(this->getFindCant()+1);
        mobs[indice].setVisualized(1);
        return Combat(charter, mobs[indice], hurt);
    }

};


int main() {
    Mazmorra P;

    P.readerDungeon();
    return 0;
}