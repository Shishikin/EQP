#include <iostream>
#include <cmath>

using namespace std;

//структура для координат
struct Coords 
{
	int row;
	int column;
};

//цвет
enum Color
{
	white = 1,
	black,
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
	FigureType type;        //тип фигуры
};

//структура для клетки
struct Cell
{
	Color color;      // цвет клетки
	Figure figure;    // фигура, стоящая на клетке
  Coords coords;    // координаты клетки
};

//структура для доски
struct Board
{
	Cell cells[8][8];
};

//num - число занятых клеток на доске,
//массив - параметры занятых клеток
struct Current 
{
	int num;               //количество занятых клетки
	Cell current[8];      //массив клеток, в которых будут стоять ферзи, с запасом на 8 клеток
};

//печать цвета пустой клетки
void PrintEmptyCell(Cell cell)
{
	if (cell.color == white)
	{
		cout << "-";
	}
	else
	{
		cout << "*";
	}
}

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
		PrintEmptyCell(cell);
		break;
	default:
		cout << "Неизвестный тип фигуры\n";
	}
}

//печать координатов ферзей
void PrintQueens(Current &current)
{
  std::cout << "\n";
  for (int i= 0; i < current.num; i++) 
  {
    switch(current.current[i].coords.column) 
    {
      case 0:
        cout << "A";
        break;
      case 1:
        cout << "B";
        break;
      case 2:
        cout << "C";
        break;
      case 3:
        cout << "D";
        break;
      case 4:
         cout << "E";
        break;
      case 5:
        cout << "F";
        break;
      case 6:
        cout << "G";
        break;
      case 7:
        cout << "H";
        break;
      default:
       cout << "Ошибка!\n";
    }
    cout << current.current[i].coords.row + 1 << " ";
    cout << "\n";
//    cout << "num = " << current.num;
  }
}

//Представление доски в памяти компьютера
void PrintBoardTest(Board board) 
{	
  cout << "\n";
  cout << " ";
  for (int i = 0; i <= 7; i++)
	{
		//вывод цифр
		cout << i;
	}
  cout << "\n";
  for (int i = 0; i <= 7; i++)
  {
    cout << i;
    for (int j = 0; j <=7; j++) 
    {
      PrintCell(board.cells[i][j]);
    }
    cout << "\n";
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

//функция проверки клетки "на пустоту"
bool CheckIfCellIsEmpty(Cell cell)
{
	return cell.figure.type == Empty;
}

//проверка бьется ли клетка
bool isBeaten(Current& current, Cell cell) 
  {
	bool flag = false;//переменная по умолчанию не бьётся
	for (int i = 0; i <= 7; i++) 
    {
		if ((cell.coords.row == current.current[i].coords.row) ||
			(cell.coords.column == current.current[i].coords.column) ||
			(abs(cell.coords.row - current.current[i].coords.row) == abs(cell.coords.column - current.current[i].coords.column))) 
        {
			flag = true;
			break;
		}
		else 
        {
			continue;
		}
	}
	return flag;
}

//заполнить массив текущих фигур пустыми значениями
Current CreateCurrent() {
  Current current;
	for (int i = 0; i <= 7; i++) 
    {
		current.current[i].figure.type = Empty;
		current.current[i].coords.row = -1;
		current.current[i].coords.column = -100;
	}
	current.num = 0;             
	return current;
}

//добавить фугуру в массив текущх фигур
Current AddFigureInCurrentArray(Current &current, int row, int column) 
{
	for (int i = 0; i <= 7; i++) {
		if (current.current[i].figure.type == Empty) 
        {
			current.current[i].figure.type = Queen;
			current.current[i].coords.row = row;
			current.current[i].coords.column = column;
			current.num++;
			break;
		}
		}
	return current;
}

//функция удаления ферзя
void DeleteFigure(Board &board, Current &current) 
{
    board.cells[current.current[(current.num)-1].coords.row][current.current[(current.num)-1].coords.column].figure.type = Empty;
  	current.current[(current.num)-1].figure.type = Empty;
	current.current[(current.num)-1].coords.row = -1;
	current.current[(current.num)-1].coords.column = -100;
    current.num--;

}

//функция создания пустой доски
Board CreateBoard()
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
			board.cells[i][j].coords.row = i;
			board.cells[i][j].coords.column = j;
			board.cells[i][j].figure.type = Empty;
		}
	}
	return board;
}

//поставить фигуру на клетку
//на вход принимает доску и координаты клетки
void SetFigure(Board &board, int row, int column)
{
	board.cells[row][column].figure.type = Queen;
}



//функция выводит координаты 8 ферзей
Board SetQueens(Board &board, Current &current) // мне кажется слишком длиинная функция не умещается на экране монитора
{
  int row = 0;
  int column = 0;
  int count = 0;
  while (true)//(current.current[0].coords.column < 8)  
  {  
     //условия нужные для поиска с возвратом
     if ((current.num != 0) && ((column > 7) or(current.num == 8)))
     { 
       if (current.num == 8)
       {
            count = count + 1;
            std::cout << "\n" << count;
            PrintQueens(current);
            //переходим на координату ПРЕДПОСЛЕДНЕЙ  ферзи + 1 у координаты столбца                             
            row = current.current[current.num-1].coords.row - 1;   
            column = current.current[current.num-2].coords.column +1;
            // удаляем 2 последних ферзя
            DeleteFigure(board, current);
            DeleteFigure(board, current);
       }
       else{
       //если последняя поставленная ферзь стоит НЕ на последнем столбце строки      
            if (current.current[current.num-1].coords.column < 7) 
            {
                //переходим на координату ПОСЛЕДНЕЙ ферзи + 1 у координаты столбца 
            row = current.current[current.num-1].coords.row;   
            column = current.current[current.num-1].coords.column + 1;
            //удаляем последнего ферзя
            DeleteFigure(board, current);
            }
            //если последняя поставленная ферзь стоит на последнем столбце строки
           else                     
           {  
                //переходим на координату ПРЕДПОСЛЕДНЕЙ  ферзи + 1 у координаты столбца                                           
                //условие выхода из цикла первый ферзь стоит на последнем столбце первой строки и его следующем шагом удалят (плохо много лишних операций сравнения из-за одного случая)
                row = current.current[current.num-1].coords.row - 1;   
                column = current.current[current.num-2].coords.column +1;
                // удаляем 2 последних ферзя
                DeleteFigure(board, current);
                // мне кажется слишком много операций сравнения ради одного случая(все комбинации найдены и надо удалить последнего ферзя на 1 строке)
				if (current.num == 0) {
					break;
				}
                DeleteFigure(board, current);
           }
       }
    }   
     //алгоритм постановки ферзи
        if (isBeaten(current, board.cells[row][column]) == 0)  //если клетка НЕ бьётся
        {
            //ставим ферзя
            SetFigure(board, row, column);                   
            //добавляем ферзя в массив
            AddFigureInCurrentArray(current, row, column);   
//            PrintBoard(board);
         
            row++;                         //увеличиваем строку на 1
            column = -1;                   // -1 так как потом столбец вырастет на один обнуляем столбец
        }
    
    column++;                         // увеличиваем столбец на один
  }
  return board;
}

int main()
{
	//создаем доску
	Board board = CreateBoard();
	cout << "Исходная доска: \n\n";
	//печатаем доскуе
	
	Current current = CreateCurrent();
//  cout << "\n\n\n\nДоска после добавления 5 ферзей подряд:\n\n";
  SetQueens(board, current);

//  PrintBoard(board); 
  cout << "\n\n";
    PrintBoard(board);
//  PrintQueens(current);
  printf("The End");
	return 0;
}
