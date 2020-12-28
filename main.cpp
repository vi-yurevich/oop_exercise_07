/*
Юревич В.Ю. М80-207Б
Спроектировать простейший «графический» векторный редактор.
Требование к функционалу редактора:
	создание нового документа.
	импорт документа из файла.
	экспорт документа в файл.
	создание графического примитива (согласно варианту задания).
	удаление графического примитива.
	отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout).
	реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур.
Требования к реализации:
	Создание графических примитивов необходимо вынести в отдельный класс – Factory. 
	Сделать упор на использовании полиморфизма при работе с фигурами.
	Взаимодействие с пользователем (ввод команд) реализовать в функции main.
Вариант 13: ромб, пятиугольник, шестиугольник.
*/

#include <iostream>
#include <memory>
#include <stack>
#include <limits>
#include "Figure.h"

class TFactory {
public:
    static TFactory& Object() {
        static TFactory ob;
        return ob;
    }

    std::shared_ptr<TFigure> Rhomb(double x0, double y0, double h, double v) {
    	return std::make_shared<TRhombus>(x0, y0, h, v);
    }

    std::shared_ptr<TFigure> Pent(double x0, double y0, double s) {
    	return std::make_shared<TPentagone>(x0, y0, s);
    }

    std::shared_ptr<TFigure> Hex(double x0, double y0 , double s) {
    	return std::make_shared<THexagone>(x0, y0, s);
    }

private:
    TFactory() {}
    TFactory(const TFactory& ob) = delete;
    TFactory& operator=(const TFactory&) = delete;
};


struct memento {
    std::vector<std::shared_ptr<TFigure> > state;
    memento() {}
    memento(const std::vector<std::shared_ptr<TFigure>> &other) : state({other}) {}
    ~memento() {}
};


struct TOrg {
    std::stack<memento> tmp;
    void SaveState(std::vector<std::shared_ptr<TFigure>>  nextmove) {
        tmp.emplace(nextmove);
    }

    std::vector<std::shared_ptr<TFigure>> Undo() {
        if (!tmp.empty()) {
            std::vector<std::shared_ptr<TFigure>> result = tmp.top().state;
            tmp.pop();
            return result;
        } else {
            throw std::logic_error("Ошибка. Отсутсвуют предыдущие состояния\n");
        }
    }
};

std::ostream& operator<<(std::ostream &os, std::vector<std::shared_ptr<TFigure>>& vec) {
    if (vec.empty() == false ) {
        for (int j = 0; j < vec.size(); ++j) {
                    std::cout << "[" << j << "] ";
                    std::cout << "Тип: " << vec[j]->Name() << std::endl;
                    std::cout << "Координаты точек: " << vec[j]->Coordinate() << std::endl;
                    std::cout << "Координаты центра: " << vec[j]->Center() << std::endl;
                    std::cout << "Площадь: " << vec[j]->Area() << std::endl;
        }
    }
    else {
        std::cout << "Сначала нужно ввести хотя бы одну фигуру\n";
    }
    return os;
}

void AddFigureToVec(char type, std::vector<std::shared_ptr<TFigure>>& vec, TOrg& act) {
    bool key = false;
    double x0, y0, side, vert, hor;
    do {
        std::cout << "Укажите координату Х центра фигуры: ";
        std::cin >> x0;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else { 
            key = true;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (key != true);
    do {
        std::cout << "Укажите координату Y центра фигуры: ";
        std::cin >> y0;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
        }
        else { 
            key = false;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (key != false);
    switch(type) {
        case 'r': {
            do {
                std::cout << "Укажите длину вертикальной диагонали: ";
                std::cin >> vert;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
                }
                else if (vert < 0) {
                            std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                        }
                else {
                    key = true;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(key != true);
            do {
                std::cout << "Укажите длину горизонтальной диагонали: ";
                std::cin >> hor;
                if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
                }
                else if (hor < 0) {
                            std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                        }
                else {
                    key = false;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(key != false);
            act.SaveState(vec);
            vec.push_back(TFactory::Object().Rhomb(x0, y0, vert, hor));
            break;
        }
        case 'p': {
            do {
                std::cout << "Укажите длину стороны: ";
                std::cin >> side;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
                }
                else if (side < 0) {
                            std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                        }
                else {
                    key = true;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(key != true);
            act.SaveState(vec);
            vec.push_back(TFactory::Object().Pent(x0, y0, side));
            break;
        }
        case 'h': {
            do {
                std::cout << "Укажите длину стороны: ";
                std::cin >> side;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
                }
                else if (side < 0) {
                            std::cout << "Ошибка ввода. Длина не может быть отрицательной. Повторите ввод.\n";
                        }
                else {
                    key = true;
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            } while(key != true);
            act.SaveState(vec);
            vec.push_back(TFactory::Object().Hex(x0, y0, side));
            break;
        }
    }
}

int main () {

int menu;
bool key;
double x, y, side, horDiag, vertDiag;

TOrg act;
std::vector<std::shared_ptr<TFigure>> vec;

menu = 1;
key = false;
while(menu != 0) {
    switch(menu) {
    case 1:
        std::cout << "1 - Вывод меню\n2 - Импорт данных\n3 - Экспорт текущего состояния в файл\n";
        std::cout << "4 - Добавить ромб\n5 - Добавить пятиугольник\n6 - Добавить шестиугольник\n";
        std::cout << "7 - Удалить элемент по индексу\n8 - Печать элементов на экран\n";
        std::cout << "9 - Отмена последнего действия\n10 - Очистка\n0 - Выход из программы\n";
        break;
    case 2: {
        char typeFig;
        act.SaveState(vec);
        vec.clear();
        std::string fileName;
        FILE* file = nullptr;
        std::cout << "Введите имя файла: ";
        std::cin >> fileName;
        file = fopen(fileName.c_str(), "r");
        if (file == nullptr) {
            std::cout << "Ошибка. Невозможно открыть файл" << std::endl;
            vec = act.Undo();
            break;
        }
        while (!feof(file)) {
            fread(&typeFig, sizeof(char), 1, file);
            if (typeFig == 'r') {
            fread(&vertDiag, sizeof(double), 1, file);
            fread(&horDiag, sizeof(double), 1, file);
            }
            else {
                fread(&side, sizeof(double), 1, file);
            }
            fread(&x, sizeof(double), 1, file);
            fread(&y, sizeof(double), 1, file); 
            switch (typeFig) {
            case 'r':
                vec.push_back(TFactory::Object().Rhomb(x, y, vertDiag, horDiag));
                break;
            case 'p':
                vec.push_back(TFactory::Object().Pent(x, y, side));
                break;
            case 'h':
                vec.push_back(TFactory::Object().Hex(x, y, side));
                break;
            }
        }
        vec.pop_back();
        fclose(file);
        break;
    }
    case 3: {
        if (vec.empty() == true) {
            std::cout << "Сначала нужно ввести хотя бы одну фигуру\n";
            break;
        }
        std::string fileName;
        FILE* file = nullptr;
        char typeFig;
        std::cout << "Введите имя файла: ";
        std::cin >> fileName;
        file = fopen(fileName.c_str(), "w");
        if (file == NULL) {
            std::cout << "Ошибка. Невозможно открыть файл" << std::endl;
            break;   
        }
        int g = 0;
        for (int j = 0; j < vec.size(); ++j) {
            if (vec[j]->Name() == "Ромб") typeFig = 'r';
            else if (vec[j]->Name() == "Пятиугольник") typeFig = 'p';
            else if (vec[j]->Name() == "Шестиугольник") typeFig = 'h';
            fwrite(&typeFig, sizeof(char), 1, file);
            switch(typeFig) {
                case 'r': {
                    vertDiag = vec[j]->Side().x;
                    horDiag = vec[j]->Side().y;
                    fwrite(&vertDiag, sizeof(double), 1, file);
                    fwrite(&horDiag, sizeof(double), 1, file);
                    break;
                }
                default: {
                    side = vec[j]->Side().x;
                    fwrite(&side, sizeof(double), 1, file);
                    break;
                }
            }
            x = vec[j]->Center().x;
            y = vec[j]->Center().y;
            fwrite(&x, sizeof(double), 1, file);
            fwrite(&y, sizeof(double), 1, file);
        }
        fclose(file);
        break;
    }
    case 4:
        AddFigureToVec('r', vec, act);
        break;
    case 5:
        AddFigureToVec('p', vec, act);
        break;
    case 6:
        AddFigureToVec('h', vec, act);
        break;
    case 7: {
        int j;
        bool key;
        key = false;
        do {
            std::cout << "Укажите индекс: ";
            std::cin >> j;
            if (std::cin.fail()) {
            std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
            }
            else if ((j < 0) || (j > (vec.size() - 1))) {
                std::cout << "Ошибка. Элемент с указанным индексом отсутсвует в массиве. Повторите ввод.\n";
            }
            else {
                key = true;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }
        } while(key != true);
        act.SaveState(vec);
        j = (j == 0) ? j : --j; 
        vec.erase(vec.begin() + j);
        break;
    }
    case 8: {
        std::cout << vec;
        break;
    }
    case 9: {
        try {
            vec = act.Undo();
            break;
        }
        catch(std::logic_error& error){
            std::cout << error.what();
        }
    }
    case 10:
    act.SaveState(vec);
    vec.clear();
    break;
}
do {
    std::cout << "Выберете пункт меню: ";
    std::cin >> menu;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Ошибка ввода. Повторите ввод." << std::endl;
    }
    else if ((menu < 0) || (menu > 11)) {
        std::cout << "Указанный пункт отсутсвует в меню. Попробуйте ещё раз." << std::endl;
    }
    else {
        key = true;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
} while(key != true);
key = false;
}
return(0);
}