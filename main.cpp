#include <iostream>
#include <iomanip>
#include <random>

class Snake{ // This class contain the map, snake and food attributes
    //Core attributes
    private:
    int height;
    int width;
    int snakeBodyLenght;
    char** mapMatrix;
    int snakeHead[2];

    int** snakeBody;
    int food[2] = {0,0};

    char mapChar = '0';
    char headChar = 'C';
    char bodyChar = 'B';
    char foodChar = 'f';

    public:
    //Constructor
    Snake(int heightCr, int widthCr) :
        height(heightCr),  
        width(widthCr),
        snakeBodyLenght(1)
        {
        int X = heightCr / 2;
        int Y = widthCr / 2;

        mapMatrix = createMap(height, width);
        snakeHead[0] = X;
        snakeHead[1] = Y;

        snakeBody = new int*[snakeBodyLenght];
        snakeBody[0] = new int[2];
        snakeBody[0][0] = X;
        snakeBody[0][1] = Y - 1;  

        food[0] = X;
        food[1] = width - 2;
    }

    //Methods
    private:
    char** createMap(int heightC, int widthC); //This method create the map matrix.
    
    public:
    void showMap();
    void snakeMove(char direction);
    void reset();
    void generateFood();

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
    //this block show the snake in the map
    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = bodyChar;
    }
    mapMatrix[snakeHead[0]][snakeHead[1]] = headChar;
    mapMatrix[food[0]][food[1]] = foodChar;

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            std::cout << std::setw(2) << mapMatrix[i][j];
        }
        std::cout << std::endl;
    }

    //this block will clean the snake of the map
    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = mapChar;
    }
    mapMatrix[snakeHead[0]][snakeHead[1]] = mapChar; 
}

void Snake::snakeMove(char direction){
    int auxHead[2] = {snakeHead[0], snakeHead[1]}; 
    
    if (direction == 'd'){
        auxHead[1]++; 
    }else if (direction == 's'){
        auxHead[0]++; 
    }else if (direction == 'a'){
        auxHead[1]--; 
    }else if (direction == 'w'){
        auxHead[0]--; 
    }

    bool grow;
    grow = (auxHead[0] == food[0] and auxHead[1] == food[1]);

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
        generateFood();
    }else {
        for(int i = snakeBodyLenght - 1; i > 0; i--){
            snakeBody[i][0] = snakeBody[i-1][0];
            snakeBody[i][1] = snakeBody[i-1][1];
        }

        snakeBody[0][0] = snakeHead[0];
        snakeBody[0][1] = snakeHead[1];
    }

    snakeHead[0] = auxHead[0];
    snakeHead[1] = auxHead[1];

    for(int i = snakeBodyLenght -1; i >= 0; i--){
        if ((snakeHead[0] == snakeBody[i][0] and snakeHead[1] == snakeBody[i][1]) or (snakeHead[0] < 0) or (snakeHead[0] >= height) or (snakeHead[1] < 0) or (snakeHead[1] >= width)){
            std::cout << "You Lose, Bastard!!" << std::endl;
            reset();
            return;
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

    mapMatrix[food[0]][food[1]] = mapChar;

    food[0] = X;
    food[1] = width - 2;
}

void Snake::generateFood(){
    std::random_device generator;
    std::uniform_int_distribution<int> distributionH(0,height - 1);
    std::uniform_int_distribution<int> distributionW(0,width - 1);

    food[0] = distributionH(generator);
    food[1] = distributionW(generator);

    for(int i = snakeBodyLenght -1; i >= 0; i--){
        if ((food[0] == snakeBody[i][0] and food[1] == snakeBody[i][1]) or (food[0] == snakeHead[0] and food[1] == snakeHead[1])){
            generateFood();
        }
    }
}

int main(){

    char movemento;
    Snake teste(8, 9);

    teste.showMap();

    while(true){
        std::cin >> movemento; 
        teste.snakeMove(movemento);    
        teste.showMap();    
    }
}