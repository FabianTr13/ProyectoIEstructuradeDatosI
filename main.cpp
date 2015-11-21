/*Conecta 4 by Fabian
Proyecto #1 Clase Estructura de Datos I
develop on codeblock linux
pt:esta ingles todo pura gana practicar
*/
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>// para usar el clear es el equivalente a cls en linux
using namespace std;

//clase nodo con 4 apuntadores y un tipo dato char
class Node{
private:

public:
    char letter;
    Node *nUp;
    Node *nDown;
    Node *nLeft;
    Node *nRight;
    Node(char letter, Node *nUp=NULL, Node *nDown=NULL, Node *nLeft=NULL, Node *nRight=NULL){
        this->letter=letter;
        this->nUp=nUp;
        this->nDown=nDown;
        this->nLeft=nLeft;
        this->nRight=nRight;

    }
    friend class Board;
};

class nodo {

    public:
        string elemt;
    nodo *nnext;

    nodo(string v, nodo *next = NULL) {
       elemt = v;
       nnext = next;
    }
};



class cola {

   private:
    nodo *last;
    nodo *first;

   public:
    int cLenght;
    cola(){
        this->cLenght=0;
        this->last=NULL;
        this->first=NULL;
    }

    void addCola(string v) {
        nodo *newNode;
        newNode = new nodo(v);
        if(last) last->nnext = newNode;
        last = newNode;
        if(!first) first = newNode;
        cLenght++;
    }

    string readCola() {
        nodo *nodo;
        string v;
        nodo = first;
        if(!nodo) {
            return 0;
        }
        first = nodo->nnext;
        v = nodo->elemt;
        delete nodo;
        if(!first){
        last = NULL;
        }
   return v;

    }

};

//tablero donde las funciones crean enlazan e ingresan y revisan el tablero
class Board{
private:

        //tamano en dimencion del tablero ejemplo tLenght = n
public:
    Node *first;        //identificador del primer nodo
    Node *last;         //identificador del segundo nodo
    int sizeBoard;      //tamano de mi tablero en nodos ejemplo sizeBoard=n*n
    int tLenght;
    Board(){                //constructor tablero
        this->first=NULL;
        this->last=NULL;
        this->sizeBoard=0;
        this->tLenght=0;
    }

    //funcion para verificar si esta vacio
    bool isEmpty(){
        return (this->first==NULL);
    }

    //agregar nodo al final solamente enladados de derecha a izquierda
    void addAtEnd(char val){
        Node *newNode=new Node(val);
                if(isEmpty()){
                    this->first=this->last=newNode;
                    this->sizeBoard++;
                }else{
                    this->last->nRight=newNode;
                    newNode->nLeft=this->last;
                    newNode->nRight=first;
                    this->first->nLeft=newNode;
                    this->last=newNode;
                    this->sizeBoard++;
                }
    }

    // crea los nodos del tablero ejemplo si tamano ingresado es 4 entonces crea 16 nodos y inicializa en vacios
    //de una vez guardo tLenght que es el que me servira en la mayoria de las funciiones
    void createLine(int num){
        this->tLenght=num;
        for(int i=0;i<num*num;i++){
            addAtEnd(' ');
        }
    }

    //aqui donde se enlazan los nodos hacia habajo
    void linkNode ()
    {
        Node *tmp1 = first;
        Node *tmp2 = first;

        for (int i = 0; i<tLenght; i++){ //me muevo al nodo n+1 y sera ese el que baje abajo de n y luego me muevo a tmp2 a la derecha y asi
            tmp1 = tmp1->nRight;         //se van enlazando hacia abajo
        }

        for (int j = 1; j<= tLenght*tLenght; j++)
        {
            tmp2->nDown = tmp1;
            tmp1->nUp = tmp2;
            tmp2 = tmp2->nRight;
            tmp1 = tmp1->nRight;
        }
    }

    //agrega los datos al nodo y su posicion recibe char del jugador de turno y posicion
    void addElement(char player,int position){
        Node *nposition=first->nLeft; //me posiciono atras del primero para que no seme pase en la iteracion en primer iteracion cae al primero
        for (int i = 0; i<position; i++)    //asi consigo sea columna 1 2 3 4... y asi
        {
            nposition = nposition->nRight;
        }
        if(nposition->letter!=' '){ //si la primera pocision esta llena osea la cabecera entonces manda que esta lleno
            cout<<"Columna llena"<<endl;
            cout<<"Jugador "<<player<<" Ingrese columna distinta"<<endl;
            int col;
            cin>>col;
            addElement(player,col);
        }else{                             // de contrario pues comineza a bajar ylo deposita arriba del que este lleno so es el ultimo pues lo manda
            for(int i=0;i<tLenght;i++){     //arriba

                if(nposition->letter==' '){
                    nposition=nposition->nDown;
                }else{
                    nposition->nUp->letter=player;
                    return;
                }
                if(i+1==tLenght){
                nposition->nUp->letter=player;
                }
            }
        }
    }

//devuelve el valor de tLenght ya es privada
    int getTLenght(){
        return tLenght;
    }
//revisa tablero si todos sus espacios son diferentes de " "
    bool full(){
        Node *tmp=first->nLeft;
        int iter=0;
        for(int i=0; i<sizeBoard;i++){
            tmp=tmp->nRight;
            if(tmp->letter!=' '){
                iter++;
            }
        }

        return (iter==sizeBoard);
    }

//aqui biene lo entrenido la verificaciones
//primeral verificacion es horizontal
    bool checkLineal(){

        Node *tmp=first;

        for(int r=0;r<tLenght;r++){ //pues tomo los elementos de cada linea y los deposito en un arreglo de char para verificarlos luego aver si hay
            int secondVal=tLenght-1;//4 juntos
            char elem[tLenght];

            for(int i=0; i<tLenght;i++){

                elem[i]=tmp->letter;
                tmp=tmp->nRight;
            }

        //verifica ganador izq a derecha horizontales
            for(int v1=0;v1<tLenght-3;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
        //verifica ganador de derecha a izq horizintales
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
            }
        }
        return false;
    }
//misma historia de horizontal solo apunta hacia abajo
      bool checkVertical(){

        Node *tmp=first;
        Node *tmp2=first;
        for(int r=0;r<tLenght;r++){
            int secondVal=tLenght-1;
            char elem[tLenght];

            for(int i=0; i<tLenght;i++){

                elem[i]=tmp->letter;
                tmp=tmp->nDown;
            }
            tmp2=tmp2->nRight;
            tmp=tmp2;

        //verifica ganador izq a derecha horizontales
            for(int v1=0;v1<tLenght-3;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
        //verifica ganador de derecha a izq horizintales
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
            }
        }
        return false;
    }

/*Las verificaciones diagonales las dividi en 4  asimilando los triangulos
el primero representa las diagolanles del triandulo superios iqz
*/
    bool checkDiagonalTa(){

        Node *tmp=first;
        Node *tmp2=first;
        int v=tLenght;

        for(int i=0;i<tLenght-3;i++){ //ese menos 3 quiere decir que buscara esa cantidad de matrices la formula calcular las matrices es n-3

                int secondVal=tLenght-1-i; //el iterador lo resto porque solo la primera diagonal tendra el mismo nuemro de elementos que el
                char elem[v-i];            //tamano que es t lenght  ya las otras iran restando un elemento

            for(int k=0;k<tLenght;k++){
                elem[k]=tmp->letter;
                for(int j=0;j<tLenght+1;j++){
                tmp=tmp->nRight;
                }
            }
            tmp2=tmp2->nRight;
            tmp=tmp2;

        /*for(int p=0;p<tLenght-i;p++){  //esto use para ir viendo como quedaban los arreglos de las diagonales tomadas que se generan n, n-i ...n-iterador
            cout<<elem[p]<<"-->";
        }
        cout<<endl;*/

        // esto es lo mismo ya solo se busca en el arreglo que 4 sean iguales
         for(int v1=0;v1<tLenght-3-i;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
         }
        }
        return false;
    }

//el mismo procediminetp solo que ahora se buscan las diagonales de el triangulo infreior derecho
      bool checkDiagonalTb(){

        Node *tmp=last;
        Node *tmp2=last;
        int v=tLenght;

        for(int i=0;i<tLenght-3;i++){

                int secondVal=tLenght-1-i;
                char elem[v-i];

            for(int k=0;k<tLenght;k++){
                elem[k]=tmp->letter;
                for(int j=0;j<tLenght+1;j++){
                tmp=tmp->nLeft;
                }
            }
            tmp2=tmp2->nLeft;
            tmp=tmp2;

        /*for(int p=0;p<tLenght-i;p++){
            cout<<elem[p]<<"-->";
        }
        cout<<endl;*/
         for(int v1=0;v1<tLenght-3-i;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
         }
        }
        return false;
    }

//ahora se busca las diagonales del trianfulo superior derecho
     bool checkDiagonalTc(){

        Node *tmp=first->nLeft;
        Node *tmp2;
        int v=tLenght;

        for(int o=0;o<tLenght;o++){
            tmp=tmp->nRight;
        }
            tmp2=tmp;

        for(int i=0;i<tLenght-3;i++){

                int secondVal=tLenght-1-i;
                char elem[v-i];

            for(int k=0;k<tLenght;k++){
                elem[k]=tmp->letter;
                for(int j=0;j<tLenght-1;j++){
                tmp=tmp->nRight;
                }
            }
            tmp2=tmp2->nLeft;
            tmp=tmp2;

        /*for(int p=0;p<tLenght-i;p++){
            cout<<elem[p]<<"-->";
        }
        cout<<endl;*/
         for(int v1=0;v1<tLenght-3-i;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
         }
        }
        return false;
    }

//por ultimo las diagonales del triangulo inferior izq
       bool checkDiagonalTd(){

        Node *tmp=last->nRight;
        Node *tmp2;
        int v=tLenght;

        for(int o=0;o<tLenght;o++){
            tmp=tmp->nLeft;
        }
            tmp2=tmp;

        for(int i=0;i<tLenght-3;i++){

                int secondVal=tLenght-1-i;
                char elem[v-i];

            for(int k=0;k<tLenght;k++){
                elem[k]=tmp->letter;
                for(int j=0;j<tLenght-1;j++){
                tmp=tmp->nLeft;
                }
            }
            tmp2=tmp2->nRight;
            tmp=tmp2;

       /* for(int p=0;p<tLenght-i;p++){
            cout<<elem[p]<<"-->";
        }
        cout<<endl;*/
         for(int v1=0;v1<tLenght-3-i;v1++){

                if(elem[v1]==elem[v1+3] && elem[v1]==elem[v1+1] && elem[v1]==elem[v1+2]){
                    if(elem[v1]!=' '){
                        return true;
                    }
                }
                if(elem[secondVal]==elem[secondVal-3] && elem[secondVal]==elem[secondVal-1] && elem[secondVal]==elem[secondVal-2]){
                    if(elem[secondVal]!=' '){
                        return true;
                    }
                }
         }
        }
        return false;
    }

};


//la clase player me define los jugadores el tanamo que quieren del tablero y cada jugador puede seleccionar su caracter u inicial deseada
 class player{
 public:
    int players, column;
    char nplayer[5];
    string colorPlayer[5];
    player(){
        players=0;
        column=0;
        nplayer[0]='.';         //los declaor asi para que al momento de colorear no me haga rollo
        nplayer[1]='.';
        nplayer[2]='.';
        nplayer[3]='.';
        nplayer[4]='.';                 //estas son la secuencias de escape en colores
        colorPlayer[0]="\033[22;37m";  //blanco
        colorPlayer[1]="\033[22;34m";  //azul
        colorPlayer[2]="\033[22;32m";  //verde
        colorPlayer[3]="\033[22;31m";  //rojo
        colorPlayer[4]="\033[22;33m";  //amarillo
        accion();
    }

    void accion(){                                          //recolecta numero columnas jugadores y sus caracteres
    cout<<"\n\t\t\t**Welcome to connect 4**"<<endl;
    cout<<"Enter a number of columns greater than 4"<<endl;

    do{
        cin>>column;
        if(column<4){
            cout<<"Enter correct number greater than 4"<<endl;
            column=0;
        }
    }
    while(column==0);

    cout<<"\nEnter players 2-4"<<endl;
    do{
        cin>>players;
        if(players>4||players==1){
            cout<<"Enter a correct number from 1 to 4"<<endl;
            players=0;
        }
    }
    while(players==0);
    for(int i=1; i<=players;i++){
    cout<<"\n Player #"<<i<< " Select your character:"<<endl;
    cin>>nplayer[i]; nplayer[i]=toupper(nplayer[i]);
    }
        system("clear");

    }
 };



 void printTable(player p, Board l){     //mi funsion que imprime el tablero y me lo divide en los cuadritos y todas las decoraciones para quede ordenado

        Node *tmp1 = l.first;
        Node *tmp2 =  l.first;

        for(int i=1;i<=l.tLenght;i++){
            cout<<" "<<i<< "   ";
        }
        cout<<endl;
        for (int i = 1; i<=l.tLenght; i++)
        {
            for (int j = 1; j<=l.tLenght; j++)
            {

                if(p.nplayer[1]==tmp1->letter){
                cout<<"|"<<p.colorPlayer[1]<<tmp1->letter<<p.colorPlayer[0]<<"|  ";
                }
                if(p.nplayer[2]==tmp1->letter){
                cout<<"|"<<p.colorPlayer[2]<<tmp1->letter<<p.colorPlayer[0]<<"|  ";
                }
                if(p.nplayer[3]==tmp1->letter){
                cout<<"|"<<p.colorPlayer[3]<<tmp1->letter<<p.colorPlayer[0]<<"|  ";
                }
                if(p.nplayer[4]==tmp1->letter){
                cout<<"|"<<p.colorPlayer[4]<<tmp1->letter<<p.colorPlayer[0]<<"|  ";
                }
                if(tmp1->letter==' '){
                    cout<<"| |  ";
                }
                tmp1 = tmp1->nRight;
            }
            cout << "\n";
            tmp2 = tmp2->nDown;
            tmp1 = tmp2;
        }
    }

   void fSave(int medal,player p, Board l,char win){
        medal--;
        cola c;
        int playerPoint[4];//identificador de jugadores
        int locador=0;     //locadizador de lineas que ocupo editar
        stringstream ss;   //convertir int a string
        string addPila="";  //variable que se agrega a pila
        ifstream fe;        //lector de achivos

        fe.open("Score.txt");
        while(!fe.eof()){

            locador++;
            getline(fe,addPila);
            playerPoint[medal]= atoi(addPila.c_str());
           if(locador==3&&medal==0){
                    playerPoint[0]++;
                    ss<<playerPoint[0];
                    addPila=ss.str();
           }else if(locador==5&&medal==1){
                    playerPoint[1]++;
                    ss<<playerPoint[1];
                    addPila=ss.str();
           }else if(locador==7&&medal==2){
                    playerPoint[2]++;
                    ss<<playerPoint[2];
                    addPila=ss.str();
           }else if(locador==9&&medal==3){
                    playerPoint[3]++;
                    ss<<playerPoint[3];
                    addPila=ss.str();
           }
        c.addCola(addPila);
        }
        fe.close();

        ofstream fs("Score.txt");
        for(int o=0;o<c.cLenght;o++){
            fs<<c.readCola()<<endl;
        }

//-------------------------------------------------------------------------------------------------

Node *tmp1 = l.first;
        Node *tmp2 =  l.first;

        for(int i=1;i<=l.tLenght;i++){
            fs<<" "<<i<< "   ";
        }
        fs<<endl;
        for (int i = 1; i<=l.tLenght; i++)
        {
            for (int j = 1; j<=l.tLenght; j++)
            {

               fs<<"|"<< tmp1->letter << "|  ";
                tmp1 = tmp1->nRight;
            }
            fs << "\n";
            tmp2 = tmp2->nDown;
            tmp1 = tmp2;
        }
    fs<<"Ganador es jugador "<<medal+1<< " con letra"<<win<<endl;



//---------------------------------------------------------------------------------------------------
            fs.close();

    }


//metodo turno que es que se encarga de ir alternando los turnos y dentro de el se va verificando quien gana u si se llena el tablero
    bool turn(int players, Board b, player p){
        bool hi = true;
        while(hi){
                for(int i =1; i<=players;i++){
                    int column=0;
                    do{
                        cout<<"Player #"<<i<<" with letter "<<p.nplayer[i]<<" is your turn\n Enter a column"<<endl;
                        cin>>column;
                    }while(column>b.getTLenght());

                        b.addElement(p.nplayer[i],column);
                        system("clear");
                        printTable(p,b);
                        if(b.checkVertical()||b.checkLineal()||b.checkDiagonalTa()||b.checkDiagonalTb()||b.checkDiagonalTc()||b.checkDiagonalTd()){
                        cout<<"There a winner is the player "<<p.nplayer[i]<<endl;
                        fSave(i,p,b,p.nplayer[i]);
                        return false;
                        }
                        if(b.full()){
                        cout<<"Board is full, There not a winner"<<endl;
                        return false;
                        }
                    }
            }
        return true;
    }


int main()
{

    Board b;                    //instancia tablero
    player p;                   //instancia de jugador
    b.createLine(p.column);     //creo las lineas de nodos
    b.linkNode();               //los enlazo
    printTable(p,b);            //pues imprimo un tbalero en blanco
    turn(p.players,b,p);        //turno se encarga del trabajo
    return 0;
}
