#include <cmath>
#include <iostream>
#include <vector>
#include <map>



//цвет
enum Color
{
    white = 'w',
    black = 'b'
};

//тип фигуры
enum FigureType
{
    Pawn = 'P', //пешка
    Bishop = 'B', //слон
    Queen = 'Q', //ферзь
    King = 'K', //король
    Horse = 'H', //конь
    Rook = 'R', //ладья
    Empty = 'E' //нет фигуры
};

//вынести

//класс фигуры
class Figure
{
private:
    Color color; // цвет фигуры
    FigureType type; //тип фигуры

public:
    //конструктор по умолчанию
    Figure(FigureType figuretype) : color(white), type(figuretype) {}

    //дружественная функция (перегрузка <<) для вывода типа фигуры
    friend std::ostream& operator << (std::ostream& out, const Figure& figure)
    {
        char a = figure.type; //
        return out << a;
    }

    //проверка типа фигуры
    bool IsA(FigureType t) const
    {
        return t == type;
    }

    char CharGetTypeFigure() const
    {
        return (char)(type);
    }
};



//класс клетки
class Cell
{
private:
    Color color; // цвет клетки
    Figure figure; // фигура, стоящая на клетке
public:
    //конструктор по умолчанию
    Cell() : color(white), figure(Figure(Empty)) {}

    Cell(Color _colorCell, FigureType fig) : color(_colorCell), figure(Figure(fig)) {}

    //перегрузка оператора <<
    friend std::ostream& operator << (std::ostream& out, const Cell& cell)
    {
        //если клетка пуста вывести цвет
        char a = cell.color;
        cell.figure.IsA(Empty) ? out << a : out << cell.figure;
        return out;
    }

    char CellFigure() const
    {
        return figure.CharGetTypeFigure();
    }

};




//структура для доски
class Board
{
private:
    // доска представленная в виде вектора
    std::vector<Cell> cells;
    int size; // число столбцов

    //псевдокласс нужен для возможности обращения по [][]
    class Proxy
    {
        const std::vector<Cell>& cells;
        int d;
    public:
        Proxy(int h, const std::vector<Cell>& cells_) : d(h), cells(cells_) {}


        const Cell& operator[](int j) const
        {
            return cells[d * sqrt(cells.size()) + j];
        }
    };

public:
    std::map<int, char > Position()
    {
        std::map<int, char > position;
        for (int i = 0; i < cells.size(); i++)
        {
            if (cells[i].CellFigure() != 'E')
            {
                position.insert({ i, cells[i].CellFigure() });
            }
        }
        return position;
    }


    std::vector<Cell>::iterator begin() {
        return cells.begin();
    }

    std::vector<Cell>::iterator end() {
        return cells.end();
    }
    Board(int bsize); //конструктор по умолчанию
    // Position

//псевдокласс нужен для возможности обращения по [][]
// const Proxy operator[] (int i) const;

    const Proxy operator[] (int i) const

    {
        Proxy proxy = Proxy(i, cells);
        return proxy;
    }

    friend std::ostream& operator << (std::ostream& out, const Board& board); // печать только доски, пока занятых клеток не печатает
    // Position
};


void IntToLetter(int letter)
{
    switch (letter)
    {
    case 0:
        std::cout << 'A';
        break;
    case 1:
        std::cout << 'B';
        break;
    case 2:
        std::cout << 'C';
        break;
    case 3:
        std::cout << 'D';
        break;
    case 4:
        std::cout << 'E';
        break;
    case 5:
        std::cout << 'F';
        break;
    case 6:
        std::cout << 'G';
        break;
    case 7:
        std::cout << 'H';
        break;
    }
}

void PrintPosition(std::map<int, char> PositionList) {
    std::map <int, char> ::iterator it = PositionList.begin();
    for (; it != PositionList.end(); it++) {
        int num = ((it->first) % 8) + 1;
        int letter = (it->first) / 8;
        IntToLetter(letter);
        std::cout << num << "\n";
    }
}

/*
const Board::Proxy Board::operator[] (int i) const
{
    Proxy proxy = Proxy(*this);
    return proxy;
}
*/
//конструктор по умолчанию для доски
Board::Board(int bsize) : size(bsize)
{
    // заполнение самой доски
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            // переделать в тенарный оператор, когда убедимся, что тут нет ошибок
            if ((i + j) % 2 == 0)
            {
                cells.push_back(Cell(black, Empty));
            }
            else
            {
                cells.push_back(Cell(white, Empty));
            }
        }
    }
    for (int i = 0; i < size * 1.5; i++)
    {
        cells[i] = Cell(black, Queen);
    }

}

// печать только доски, пока занятых клеток не печатает
std::ostream& operator << (std::ostream& out, const Board& board)
{
    out << "\n";
    for (int i = board.size - 1; i >= 0; i--)
    {
        //вывод цифр
        out << i + 1 << ' ';
        for (int j = 0; j < board.size; j++)
        {
            out << ' ' << board.cells[i + board.size * j];
        }
        out << "\n";
    }
    out << " ";
    //вывод букв
    for (char letter = 65; letter <= 72; letter++)
    {
        out << letter << ' ';
    }
    out << "\n";
    return out;
}

class GameRules
{
public:
    virtual bool Move(Figure figure, int coord1, int coord2) = 0;
    virtual bool Set(Figure figure, int coord) = 0;
    virtual bool Remove(Figure figure, int coord) = 0;
    virtual bool Test() = 0;
};

class Queens : GameRules
{
private:
    Board board;

public:

    Queens(Board board_) : GameRules(), board(board_) {}
    bool Test() override
    {
        return true;
    }

    bool Move(Figure figure, int coord1, int coord2) override
    {
        return true;
    }

    bool Set(Figure figure, int coord) override
    {
        return true;
    }
    bool Remove(Figure figure, int coord) override
    {
        return true;
    }
    /*
      override
      { bool Move(Figure figure, int coord1, int coord2)
         {
           return true;
         }
      }
     */

};
/*
class Match
{
private:
  GameRules *gr = new Queens;

public:
 // GameRules *gr = new Queens;
   Board Play();
};
*/
int main()
{

    Board board = Board(8);
    std::cout << board;
    Cell a = board[1][0];
    std::cout << a;
    char checksymvol = board[1][0].CellFigure();
    std::cout << checksymvol << '\n';
    std::map<int, char> Dictionary = board.Position();
    PrintPosition(Dictionary);
    Queens queens(board);
    bool q = queens.Test();
    // bool q = GameRules->M();
    // GameRules->Move#include <cmath>
#include <iostream>
#include <vector>
#include <map>



//цвет
    enum Color
    {
        white = 'w',
        black = 'b'
    };

    //тип фигуры
    enum FigureType
    {
        Pawn = 'P', //пешка
        Bishop = 'B', //слон
        Queen = 'Q', //ферзь
        King = 'K', //король
        Horse = 'H', //конь
        Rook = 'R', //ладья
        Empty = 'E' //нет фигуры
    };

    //вынести

    //класс фигуры
    class Figure
    {
    private:
        Color color; // цвет фигуры
        FigureType type; //тип фигуры

    public:
        //конструктор по умолчанию
        Figure(FigureType figuretype) : color(white), type(figuretype) {}

        //дружественная функция (перегрузка <<) для вывода типа фигуры
        friend std::ostream& operator << (std::ostream& out, const Figure& figure)
        {
            char a = figure.type; //
            return out << a;
        }

        //проверка типа фигуры
        bool IsA(FigureType t) const
        {
            return t == type;
        }

        char CharGetTypeFigure() const
        {
            return (char)(type);
        }
    };



    //класс клетки
    class Cell
    {
    private:
        Color color; // цвет клетки
        Figure figure; // фигура, стоящая на клетке
    public:
        //конструктор по умолчанию
        Cell() : color(white), figure(Figure(Empty)) {}

        Cell(Color _colorCell, FigureType fig) : color(_colorCell), figure(Figure(fig)) {}

        //перегрузка оператора <<
        friend std::ostream& operator << (std::ostream& out, const Cell& cell)
        {
            //если клетка пуста вывести цвет
            char a = cell.color;
            cell.figure.IsA(Empty) ? out << a : out << cell.figure;
            return out;
        }

        char CellFigure() const
        {
            return figure.CharGetTypeFigure();
        }

    };




    //структура для доски
    class Board
    {
    private:
        // доска представленная в виде вектора
        std::vector<Cell> cells;
        int size; // число столбцов

        //псевдокласс нужен для возможности обращения по [][]
        class Proxy
        {
            const std::vector<Cell>& cells;
            int d;
        public:
            Proxy(int h, const std::vector<Cell>& cells_) : d(h), cells(cells_) {}


            const Cell& operator[](int j) const
            {
                return cells[d * sqrt(cells.size()) + j];
            }
        };

    public:
        std::map<int, char > Position()
        {
            std::map<int, char > position;
            for (int i = 0; i < cells.size(); i++)
            {
                if (cells[i].CellFigure() != 'E')
                {
                    position.insert({ i, cells[i].CellFigure() });
                }
            }
            return position;
        }


        std::vector<Cell>::iterator begin() {
            return cells.begin();
        }

        std::vector<Cell>::iterator end() {
            return cells.end();
        }
        Board(int bsize); //конструктор по умолчанию
        // Position

    //псевдокласс нужен для возможности обращения по [][]
    // const Proxy operator[] (int i) const;

        const Proxy operator[] (int i) const

        {
            Proxy proxy = Proxy(i, cells);
            return proxy;
        }

        friend std::ostream& operator << (std::ostream& out, const Board& board); // печать только доски, пока занятых клеток не печатает
        // Position
    };


    void IntToLetter(int letter)
    {
        switch (letter)
        {
        case 0:
            std::cout << 'A';
            break;
        case 1:
            std::cout << 'B';
            break;
        case 2:
            std::cout << 'C';
            break;
        case 3:
            std::cout << 'D';
            break;
        case 4:
            std::cout << 'E';
            break;
        case 5:
            std::cout << 'F';
            break;
        case 6:
            std::cout << 'G';
            break;
        case 7:
            std::cout << 'H';
            break;
        }
    }

    void PrintPosition(std::map<int, char> PositionList) {
        std::map <int, char> ::iterator it = PositionList.begin();
        for (; it != PositionList.end(); it++) {
            int num = ((it->first) % 8) + 1;
            int letter = (it->first) / 8;
            IntToLetter(letter);
            std::cout << num << "\n";
        }
    }

    /*
    const Board::Proxy Board::operator[] (int i) const
    {
        Proxy proxy = Proxy(*this);
        return proxy;
    }
    */
    //конструктор по умолчанию для доски
    Board::Board(int bsize) : size(bsize)
    {
        // заполнение самой доски
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // переделать в тенарный оператор, когда убедимся, что тут нет ошибок
                if ((i + j) % 2 == 0)
                {
                    cells.push_back(Cell(black, Empty));
                }
                else
                {
                    cells.push_back(Cell(white, Empty));
                }
            }
        }
        for (int i = 0; i < size * 1.5; i++)
        {
            cells[i] = Cell(black, Queen);
        }

    }

    // печать только доски, пока занятых клеток не печатает
    std::ostream& operator << (std::ostream & out, const Board & board)
    {
        out << "\n";
        for (int i = board.size - 1; i >= 0; i--)
        {
            //вывод цифр
            out << i + 1 << ' ';
            for (int j = 0; j < board.size; j++)
            {
                out << ' ' << board.cells[i + board.size * j];
            }
            out << "\n";
        }
        out << " ";
        //вывод букв
        for (char letter = 65; letter <= 72; letter++)
        {
            out << letter << ' ';
        }
        out << "\n";
        return out;
    }

    class GameRules
    {
    public:
        virtual bool Move(Figure figure, int coord1, int coord2) = 0;
        virtual bool Set(Figure figure, int coord) = 0;
        virtual bool Remove(Figure figure, int coord) = 0;
        virtual bool Test() = 0;
    };

    class Queens : GameRules
    {
    private:
        Board board;

    public:

        Queens(Board board_) : GameRules(), board(board_) {}
        bool Test() override
        {
            return true;
        }

        bool Move(Figure figure, int coord1, int coord2) override
        {
            return true;
        }

        bool Set(Figure figure, int coord) override
        {
            return true;
        }
        bool Remove(Figure figure, int coord) override
        {
            return true;
        }
        /*
          override
          { bool Move(Figure figure, int coord1, int coord2)
             {
               return true;
             }
          }
         */

    };
    /*
    class Match
    {
    private:
      GameRules *gr = new Queens;

    public:
     // GameRules *gr = new Queens;
       Board Play();
    };
    */
    int main()
    {

        Board board = Board(8);
        std::cout << board;
        Cell a = board[1][0];
        std::cout << a;
        char checksymvol = board[1][0].CellFigure();
        std::cout << checksymvol << '\n';
        std::map<int, char> Dictionary = board.Position();
        PrintPosition(Dictionary);
        Queens queens(board);
        bool q = queens.Test();
        // bool q = GameRules->M();
        // GameRules->Move('E', 0, 0);



        return 0;
    }('E', 0, 0);



    return 0;
}