#include <cmath>
#include <iostream>

using namespace std;

//структура для координат
struct Coords
{
    int row;
    int column;
    Coords() : row(-1), column(-1) {}
};


//цвет
enum Color
{
    white,
    black
};

//тип фигуры
enum FigureType
{
	Pawn = 1, //пешка
	Bishop,	  //слон 2
	Queen,	  //ферзь 3
	King,	  //король 4
	Horse,	  //конь 5
	Rook,	  //ладья 6
	Empty	  //нет фигуры 7
};


//структура для фигуры
struct Figure
{
	Color color;            // цвет фигуры
	FigureType type;
        Figure() : color(white), type(Empty) {}        //тип фигуры
};

//структура для клетки
struct Cell
{
	Color color;      // цвет клетки
	Figure figure;    // фигура, стоящая на клетке
        Coords coords;  // координаты клетки
        Cell() : color(white), figure(Empty), coords(-1, -1) {}
};

//структура для доски
struct Board
{
	Cell cells[8][8];
};

//структура для отображения занятых клеток доски
struct OccupiedCells
{
    int num;
    Cell occupiedCells[8];
};


//печать типа фигуры
void PrintCell(Cell cell)
{
    switch (cell.figure.type)
    {
    case Pawn:
        cout << "P\t";
        break;
    case Bishop:
        cout << "B\t";
        break;
    case Queen:
        cout << "Q";
        break;
    case King:
        cout << "K\t";
        break;
    case Horse:
        cout << "H\t";
        break;
    case Rook:
        cout << "R\t";
        break;
    case Empty:
        //тернарный оператор для печати цвета пустой клетки
        cell.color == white ? cout << "-" : cout << "*";
        break;
    default:
        cout << "Фигура не найдена\n";
    }
}

//печать координат ферзей
void PrintQueens(OccupiedCells &occupied)
{
    for (int i = 0; i < occupied.num; i++)
    {
       //
       cout << (char)(occupied.occupiedCells[i].coords.column + 65);
       cout << occupied.occupiedCells[i].coords.row + 1 << " ";
    }
}

//функция печати доски
void PrintBoard(Board board)
{
    cout << "\n";
    for (int i = 7; i >= 0; i--)
    {
        //вывод цифр
        cout << i + 1;
        for (int j = 0; j <= 7; j++)
        {
            PrintCell(board.cells[i][j]);
        }
        cout << "\n";
    }
    cout << " ";
    //вывод букв
    for (char letter = 65; letter <= 72; letter++)
    {
        cout << letter;
    }
    cout << "\n";
}

//проверка клетки на пустоту
bool IsEmpty(Cell cell)
{
    return cell.figure.type == Empty;
}

//проверка, бьется ли клетка
bool IsBeaten(OccupiedCells &occupied, Cell cell)
{  
    //иначе просматриваем все фигуры, стоящие на доске
     if (occupied.num != 0)
    {
        for (int i = occupied.num - 1; i >= 0; i--)
        {
            //если наткнулись на бьющуюся клетку - сразу выходим
            if ((cell.coords.row == occupied.occupiedCells[i].coords.row) ||
                (cell.coords.column == occupied.occupiedCells[i].coords.column) ||
                ((abs(cell.coords.row - occupied.occupiedCells[i].coords.row)) ==
                    (abs(cell.coords.column - occupied.occupiedCells[i].coords.column))))
            {
                return true;
            }
        }
    }
    //если доска не пуста, и мы не наткнулись на бьющуюся клетку, то возвращаем false (нет, не бьется)
    return false;
}

//заполнить массив занятых фигур "пустыми" фигурами
OccupiedCells FillOccupied()
{
    OccupiedCells occupied;
    for (int i = 0; i <= 7; i++)
    {
        occupied.occupiedCells[i].figure.type = Empty;
        occupied.occupiedCells[i].coords.row = -1;
        occupied.occupiedCells[i].coords.column = -100;
    }
    occupied.num = 0;
    return occupied;
}

//добавить фигуру в массив имеющихся на доске фигур
void AddFigureInOccupiedArray(OccupiedCells &occupied, int row, int column)
{
    occupied.occupiedCells[occupied.num].figure.type = Queen;
    occupied.occupiedCells[occupied.num].coords.row = row;
    occupied.occupiedCells[occupied.num].coords.column = column;
    occupied.num += 1;
}

//удалить фигуру
void DeleteFigure(Board &board, Cell  &cell, OccupiedCells &occupied)
{
    board.cells[cell.coords.row][cell.coords.column].figure.type = Empty;

    occupied.occupiedCells[(occupied.num) - 1].figure.type = Empty;
    occupied.occupiedCells[(occupied.num) - 1].coords.row = -1;
    occupied.occupiedCells[(occupied.num) - 1].coords.column = -100;
    occupied.num--;
}

//заполнить доску пустыми фигурами
Board FillWithEmptyFigures()
{
    Board board;
    for (int i = 0; i <= 7; i++)
    {
        for (int j = 0; j <= 7; j++)
        {
            if ((i + j) % 2 == 0)
            {
                board.cells[i][j].color = black;
            }
            else
            {
                board.cells[i][j].color = white;
            }
            //конструктор клетки
            board.cells[i][j].coords.row = i;
            board.cells[i][j].coords.column = j;
            board.cells[i][j].figure.type = Empty;
        }
    }
    return board;
}

//поставить фигуру на доску
void SetFigure(Board& board, int row, int column, OccupiedCells &occupied)
{
    board.cells[row][column].figure.type = Queen;
    AddFigureInOccupiedArray(occupied, row, column);
}

//поставить определенное число ферзей, рекурсия
void SetQueens(Board &board, OccupiedCells &occupied, int count, int start_row, int start_column)
{
    //если дошли до конца доски - выходим
    if (start_row == 8)
    {
        return;
    }
    //если поставили все фигуры - печатаем их и выходим
    else if (count == 0)
    {
        PrintQueens(occupied);
        cout << "\n\n";
        return;
    }
    else {
        //если клетка не бьется
        if (!IsBeaten(occupied, board.cells[start_row][start_column]))
        {
            //ставим фигуру
            SetFigure(board, start_row, start_column, occupied);
            //уменьшаем количество оставшихся фигур
            count--;
            //переходим на следующую строку
            start_row += 1;
            start_column = 0;
            //ставим фигуры начиная с новой строки
            SetQueens(board, occupied, count, start_row, start_column);
        }
        else
        {
            //если дошли до конца строки - перейти на следующую
            if (start_column == 8) {
                start_column = 0;
                start_row += 1;
            }
            //если в строке еще есть место - переходим на следующую клетку
            else {
                start_column += 1;
            }
            SetQueens(board, occupied, count, start_row, start_column);
        }
    }
}


int main()
{
    Board board = FillWithEmptyFigures();
    OccupiedCells occupied = FillOccupied();
    SetQueens(board, occupied, 5, 0, 0);
    
    cout << "\n\n";
    PrintBoard(board);
    return 0;
}
