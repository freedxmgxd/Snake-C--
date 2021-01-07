#include <iostream>
#include <iomanip>

class Snake{ // This class contain the map, snake and food attributes
    //Core attributes
    private:
    int height, width;
    char** mapMatrix;
    int snakeHead[2];
    int snakeBodyLenght;
    int** snakeBody;

    char mapChar = '0';
    char headChar = 'C';
    char bodyChar = 'B';

    public:
    //Constructor
    Snake(int heightCr, int widthCr){
        int X = heightCr / 2;
        int Y = widthCr / 2;

        height = heightCr;
        width = widthCr;
        mapMatrix = createMap(height, width);
        snakeHead[0] = X;
        snakeHead[1] = Y;
        snakeBodyLenght = 1;

        snakeBody = new int*[snakeBodyLenght];
        snakeBody[0] = new int[2];
        snakeBody[0][0] = X;
        snakeBody[0][1] = Y - 1;    
    }

    //Methods
    private:
    char** createMap(int heightC, int widthC); //This method create the map matrix.
    
    public:
    void showMap();
    void snakeMove(char direction, bool grow);
    void reset();

};

char** Snake::createMap(int heightC, int widthC){
    char** map = new char*[heightC];
    for (int i = 0; i < heightC; i++){
        map[i] = new char[widthC];
        for (int j = 0; j < widthC; j++){
            map[i][j] = mapChar; // this will be what's printed in terminal.
        }
    }
    return map;
}

void Snake::showMap(){
    mapMatrix[snakeHead[0]][snakeHead[1]] = headChar; //this block show the snake in the map
    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = bodyChar;
    }

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            std::cout << std::setw(2) << mapMatrix[i][j];
        }
        std::cout << std::endl;
    }

    mapMatrix[snakeHead[0]][snakeHead[1]] = mapChar; //this block will clean the snake of the map
    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = mapChar;
    }
}

void Snake::snakeMove(char direction, bool grow){
    if(grow){
        int** auxBody = new int*[snakeBodyLenght];
        for(int i=0; i < snakeBodyLenght; i++){
            auxBody[i] = new int[2];
            auxBody[i][0] = snakeBody[i][0];
            auxBody[i][1] = snakeBody[i][1];
        }
        delete[] snakeBody;

        snakeBodyLenght = snakeBodyLenght + 1;

        snakeBody = new int*[snakeBodyLenght];

        snakeBody[0] = new int[2];
        snakeBody[0][0] = snakeHead[0];
        snakeBody[0][1] = snakeHead[1];

        for(int i=1; i < snakeBodyLenght; i++){
            snakeBody[i] = new int[2];
            snakeBody[i][0] = auxBody[i - 1][0];
            snakeBody[i][1] = auxBody[i - 1][1];
        }
    }else {
        for(int i = snakeBodyLenght - 1; i > 0; i--){
            snakeBody[i][0] = snakeBody[i-1][0];
            snakeBody[i][1] = snakeBody[i-1][1];
        }

        snakeBody[0][0] = snakeHead[0];
        snakeBody[0][1] = snakeHead[1];
    }

    if (direction == 'd'){
        snakeHead[1]++; 
    }else if (direction == 's'){
        snakeHead[0]++; 
    }else if (direction == 'a'){
        snakeHead[1]--; 
    }else if (direction == 'w'){
        snakeHead[0]--; 
    }

    for(int i = snakeBodyLenght -1; i >= 0; i--){
        if ((snakeHead == snakeBody[i]) or (snakeHead[0] < 0) or (snakeHead[0] >= height) or (snakeHead[1] < 0) or (snakeHead[1] >= width)){
            std::cout << "You Lose, Bastard!!" << std::endl;
            reset();
        }
    }
}

void Snake::reset(){
    int X = height / 2;
    int Y = width / 2;
    
    snakeHead[0] = X;
    snakeHead[1] = Y;
    snakeBodyLenght = 1;

    snakeBody = new int*[snakeBodyLenght];
    snakeBody[0] = new int[2];
    snakeBody[0][0] = X;
    snakeBody[0][1] = Y - 1;
}

int main(){

    char movemento;
    Snake teste(8, 9);

    teste.showMap();

        std::cin >> movemento; 
        teste.snakeMove(movemento, true);    
        teste.showMap(); 

                std::cin >> movemento; 
        teste.snakeMove(movemento, true);    
        teste.showMap(); 
                std::cin >> movemento; 
        teste.snakeMove(movemento, true);    
        teste.showMap(); 

    while(true){
        std::cin >> movemento; 
        teste.snakeMove(movemento, false);    
        teste.showMap();    
    }
}