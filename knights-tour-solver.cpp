#include <iostream>
#include <vector>
#include <sstream>
#include <string>

void checkParameters(int &boardSize, int &xStart, int &yStart, int &xEnd, int &yEnd)
{
    bool valid = true;
    if (!((boardSize >= 1) && (boardSize <= 26)))
    {
        valid = false;
    }
    if (!((xStart >= 0) && (xStart <= boardSize - 1)))
    {
        valid = false;
    }
    if (!((yStart >= 0) && (yStart <= boardSize - 1)))
    {
        valid = false;
    }
    if (!((xEnd >= 0) && (xEnd <= boardSize - 1)))
    {
        valid = false;
    }
    if (!((yEnd >= 0) && (yEnd <= boardSize - 1)))
    {
        valid = false;
    }
    if (!valid)
    {
        throw std::runtime_error("invalid parameter list");
    }
}

void initialiseBoard(std::vector<std::vector<int>> &board, int boardSize)
{
    std::vector<int> squares(boardSize);
    for (int i = 0; i < boardSize; ++i)
    {
        board.push_back(squares);
    }
}



bool alreadyVisited(std::vector<std::vector<int>> &board, int xPos, int yPos)
{
    if ((board.at(xPos)).at(yPos) == false)
    {
        return false;
    }

    return true;
}

bool onTheBoard(int xPos, int yPos, int boardSize)
{
    if ((xPos > boardSize - 1) || (yPos > boardSize - 1))
    {
        return false;
    }
    if ((xPos < 0) || (yPos < 0))
    {
        return false;
    }

    return true;
}

bool validMove(std::vector<std::vector<int>> &board, int xPos, int yPos, int boardSize)
{
    if (onTheBoard(xPos, yPos, boardSize))
    {
        if (!alreadyVisited(board, xPos, yPos))
        {
            return true;
        }
    }

    return false;
}

bool findKnightsTour(std::vector<std::vector<int>> &board, int &xStart, int &yStart, int &xEnd, int &yEnd, int moveNumber, int &numberOfMoves)
{
    std::vector<int> xMoves = {2, 2, -2, -2, 1, -1, 1, -1};
    std::vector<int> yMoves = {1, -1, 1, -1, 2, 2, -2, -2};
    int xNew;
    int yNew;
    bool success;

    if ((xStart == xEnd) && (yStart == yEnd))
    {
        return true;
    }

    // Loop for all possibe moves from start
    for (int i = 0; i < 8; ++i)
    {
        xNew = xStart + xMoves.at(i);
        yNew = yStart + yMoves.at(i);

        if (validMove(board, xNew, yNew, board.size()))
        {
            // Mark board with square visited
            (board.at(xNew)).at(yNew) = moveNumber;
            numberOfMoves += 1;

            success = findKnightsTour(board, xNew, yNew, xEnd, yEnd, moveNumber + 1, numberOfMoves);
            if (success)
            {
                return true;
            }

            // Remove mark of square visited
            (board.at(xNew)).at(yNew) = 0;
            numberOfMoves -= 1;
        }
    }

    return false;
}

int main(int argc, char *argv[])
{
    try
    {
        if (argc == 4)
        {
            // Valid number of CL parameters
            int boardSize, xStart, xEnd, yStart, yEnd;
            int numberOfMoves = 1;
            char xStartChar, xEndChar;
            std::istringstream boardSizeSS(argv[1]), startSquareSS(argv[2]), endSquareSS(argv[3]);

            boardSizeSS >> boardSize;
            startSquareSS >> xStartChar >> yStart;
            endSquareSS >> xEndChar >> yEnd;

            xStart = xStartChar - 97;
            xEnd = xEndChar - 97;
            yStart -= 1;
            yEnd -= 1;

            checkParameters(boardSize, xStart, yStart, xEnd, yEnd);

            std::vector<std::vector<int>> board;
            initialiseBoard(board, boardSize);

            (board.at(xStart)).at(yStart) = 1;

            if (findKnightsTour(board, xStart, yStart, xEnd, yEnd, 2, numberOfMoves))
            {
                for (int lookingFor = 1; lookingFor <= numberOfMoves; ++lookingFor)
                {
                    for (int i = 0; i < board.size(); ++i)
                    {
                        for (int j = 0; j < board.size(); ++j)
                        {
                            if ((board.at(i)).at(j) == lookingFor)
                            {
                                std::cout << static_cast<char>(i + 97) << j + 1 << " ";
                            }
                        }
                    }
                }
            }
            else
            {
                std::cout << "could not find a knight's tour";
            }
        }
        else
        {
            // Error with CL parameters
            throw std::runtime_error("invalid parameter list");
        }

        return 0;
    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what();
        return 1;
    }
}