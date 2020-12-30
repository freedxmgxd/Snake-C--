#include <iostream>
#include <iomanip>

class Snake{ // This class contain the map, snake and food attributes
    //Core attributes
    private:
    int height, width;
    char** mapMatrix;

    public:
    //Constructor
    Snake(int heightCr, int widthCr){
        height = heightCr;
        width = widthCr;
        mapMatrix = createMap(height, width);
    }

    //Methods
    private:
    char** createMap(int heightC, int widthC); //This method create the map matrix.
    public:
    void showMap();
};

char** Snake::createMap(int heightC, int widthC){
    char** map = new char*[heightC];
    for (int i = 0; i < heightC; i++){
        map[i] = new char[widthC];
        for (int j = 0; j < widthC; j++){
            map[i][j] = '0'; // this will be what's printed in terminal.
        }
    }
    return map;
}

void Snake::showMap(){
    for(int i=0; i < height; i++){
        for(int j=0; j < width; j++){
            std::cout << std::setw(2) << mapMatrix[i][j];
        }
        std::cout << std::endl;
    }
}

int main(){

    Snake teste(8, 9);

    teste.showMap();
}