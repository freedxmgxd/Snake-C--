#include <iostream>
#include <iomanip>
#include <random>

class Snake{
    
    private:
    int height;
    int width;
    int snakeBodyLenght;
    char** mapMatrix;
    int snakeHead[2];
    char direction;

    int** snakeBody;
    int food[2] = {0,0};

    char mapChar = '0';
    char headChar = 'H';
    char bodyChar = 'B';
    char foodChar = 'f';

    public:
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
        direction = 'd';

        snakeBody = new int*[snakeBodyLenght];
        snakeBody[0] = new int[2];
        snakeBody[0][0] = X;
        snakeBody[0][1] = Y - 1;  

        food[0] = X;
        food[1] = width - 2;
    }

    ~Snake(){
        std::cout << "Destroyed" << std::endl;
        cleanUp();
    }

    private:
    char** createMap(int heightC, int widthC);
    
    public:
    void showMap();
    void snakeMove(char direction);
    void reset();
    void generateFood();
    void cleanUp();

};

char** Snake::createMap(int heightC, int widthC){
    char** map = new char*[heightC];
    for (int i = 0; i < heightC; i++){
        map[i] = new char[widthC];
        for (int j = 0; j < widthC; j++){
            map[i][j] = mapChar;
        }
    }
    return map;
}

void Snake::showMap(){
    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = bodyChar;
    }
    mapMatrix[snakeHead[0]][snakeHead[1]] = headChar;
    mapMatrix[food[0]][food[1]] = foodChar;

    system("clear");

    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            std::cout << std::setw(2) << mapMatrix[i][j];
        }
        std::cout << std::endl;
    }

    for (int i = 0; i < snakeBodyLenght; i++){
        mapMatrix[snakeBody[i][0]][snakeBody[i][1]] = mapChar;
    }
    mapMatrix[snakeHead[0]][snakeHead[1]] = mapChar; 
}

void Snake::snakeMove(char directionAux){
    int auxHead[2] = {snakeHead[0], snakeHead[1]}; 
    int oldHead[2] = {snakeHead[0], snakeHead[1]};

    switch (directionAux)
    {
    case 'd':
        auxHead[1]++;
        direction = directionAux;
        break;
    case 's':
        auxHead[0]++;
        direction = directionAux; 
        break;
    case 'a':
        auxHead[1]--;
        direction = directionAux;
        break; 
    case 'w':
        auxHead[0]--; 
        direction = directionAux;
        break;
    default:
        snakeMove(direction);
        return;
    }

    snakeHead[0] = auxHead[0];
    snakeHead[1] = auxHead[1];
    
    bool grow;
    grow = (auxHead[0] == food[0] and auxHead[1] == food[1]);

    if(grow){
        int** auxBody = new int*[snakeBodyLenght];
        for(int i=0; i < snakeBodyLenght; i++){
            auxBody[i] = new int[2];
            auxBody[i][0] = snakeBody[i][0];
            auxBody[i][1] = snakeBody[i][1];
        }
        delete snakeBody;

        snakeBodyLenght = snakeBodyLenght + 1;

        snakeBody = new int*[snakeBodyLenght];

        snakeBody[0] = new int[2];
        snakeBody[0][0] = oldHead[0];
        snakeBody[0][1] = oldHead[1];

        for(int i=1; i < snakeBodyLenght; i++){
            snakeBody[i] = new int[2];
            snakeBody[i][0] = auxBody[i - 1][0];
            snakeBody[i][1] = auxBody[i - 1][1];
            delete auxBody[i - 1];
        }
        delete auxBody;
        generateFood();
    }else {
        for(int i = snakeBodyLenght - 1; i > 0; i--){
            snakeBody[i][0] = snakeBody[i-1][0];
            snakeBody[i][1] = snakeBody[i-1][1];
        }

        snakeBody[0][0] = oldHead[0];
        snakeBody[0][1] = oldHead[1];
    }



    for(int i = snakeBodyLenght -1; i >= 0; i--){
        if ((snakeHead[0] == snakeBody[i][0] and snakeHead[1] == snakeBody[i][1]) or (snakeHead[0] < 0) or (snakeHead[0] >= height) or (snakeHead[1] < 0) or (snakeHead[1] >= width)){
            std::cout << "You Lose, Bastard!!" << std::endl;
            char hold;
            std::cin >> hold;
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

    if (snakeBodyLenght > (height * width) - 2){
            std::cout << "You are free now!"<< std::endl;
            char hold;
            std::cin >> hold;
            reset();
            return;
        }

    for(int i = snakeBodyLenght -1; i >= 0; i--){
        if ((food[0] == snakeBody[i][0] and food[1] == snakeBody[i][1]) or (food[0] == snakeHead[0] and food[1] == snakeHead[1])){
            generateFood();
        }
    }
}
void Snake::cleanUp(){
    for (int i = 0; i < height; i++){
        delete mapMatrix[i];
    }
    delete mapMatrix;

    for (int i = 0; i < snakeBodyLenght; i++){
        delete snakeBody[i];
    }
    delete snakeBody;
}

int main(){
    char movemento;
    Snake teste(4, 4);

    teste.showMap();

    while(true){
        std::cin >> movemento; 
        teste.snakeMove(movemento);    
        teste.showMap();    
    }
    teste.cleanUp();
}