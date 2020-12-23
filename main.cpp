#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

std::ostream& operator<<(std::ostream& os, const vector<vector<int>>& matrix) {
  for (auto row : matrix) {
    for (auto cell : row) {
      os << setw(4) << cell;
    }
    os << "\n";
  }

  return os;
}

struct Cell {
  int row;
  int column;

  Cell& operator+=(const Cell& other) {
    row += other.row;
    column += other.column;

    return *this;
  }
};

Cell operator+(const Cell& lhs, const Cell& rhs) {
   return Cell(lhs) += rhs;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
  return os << "{" << cell.row << "," << cell.column << "}";
}


class Solution {
public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix;
    matrix.resize(n);
    for (auto & row : matrix) {
      row.resize(n);
    }

    int value = 1;
    for (int i = 0; i < (n/2 + n%2); ++i) {
      fillSquareBorder(matrix, {i,i}, n-i*2, value);
    }

    return matrix;
  }

  void fillSquareBorder(vector<vector<int>>& matrix, const Cell& top_left,
                        int side_length, int & value) {
    fillSide(matrix, top_left, value, {0,1}, side_length);

    // if not last center element
    if (1 < side_length) {
      Cell top_right{top_left.row, top_left.column + side_length - 1};
      fillSide(matrix, top_right + Cell{1,0}, value, {1,0}, side_length - 1);

      Cell bottom_right{top_right.row + side_length - 1, top_right.column};
      fillSide(matrix, bottom_right + Cell{0,-1}, value, {0,-1}, side_length - 1);

      Cell bottom_left{top_left.row + side_length - 1, top_left.column};
      fillSide(matrix, bottom_left + Cell{-1,0}, value, {-1,0}, side_length - 2);
    }

    //    std::cout << top_left << "," << top_right << "," << bottom_right << "," << bottom_left << std::endl;
  }

  void fillSide(vector<vector<int>>& matrix, const Cell& start_cell, int & value,
                  const Cell& step, size_t length) {
    Cell cursor = start_cell;
    for (size_t i = 0; i < length; ++i, cursor += step, ++value) {
//      std::cout << matrix << std::endl;
      auto [row, column] = cursor;
      matrix[row][column] = value;
    }
  }
};

int main()
{
  Solution s;
  cout << s.generateMatrix(3) << endl;
  return 0;
}
