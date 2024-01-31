""" Maximum size square sub-matrix with all 1s

Source: Geeks for geeks
https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/

Given a binary matrix, find the maximum size square sub-matrix with all 1s.

The solution is based on dynamic programming.
The key idea is that for the size of the sub-matrix "ending" at (i, j) to be k,
one needs the following conditions to be true:
- the element at (i, j) is 1
- the size of the sub-matrix ending at (i-1, j) is at least k-1
- the size of the sub-matrix ending at (i, j-1) is at least k-1
- the size of the sub-matrix ending at (i-1, j-1) is at least k-1

A terse way of expressing this is (assuming m[i,j] == 1):
size(i, j) = 1 + min(size(i-1, j), size(i, j-1), size(i-1, j-1))
"""
import unittest
import numpy


class Result:
    def __init__(self, *, size: int, row: int, column: int):
        self.size = size
        # bottom right corner of the sub-matrix:
        self.row = row
        self.column = column


def solve(matrix: numpy.ndarray) -> Result:
    rows, columns = matrix.shape
    result = Result(size=0, row=0, column=0)

    # We don't need to store the whole matrix, just the previous row.
    previous_row = numpy.array([matrix[0, column] for column in range(columns)])
    column = next((column for column in range(columns) if previous_row[column] == 1), None)
    if column is not None:
        result = Result(size=1, row=0, column=column)

    for row in range(1, rows):
        current_row = numpy.array([0 for _ in range(columns)])
        current_row[0] = matrix[row, 0]
        if result.size < 1 and current_row[0] == 1:
            result = Result(size=1, row=row, column=0)
        for column in range(1, columns):
            if matrix[row, column] == 1:
                current_row[column] = 1 + min(previous_row[column-1], previous_row[column], current_row[column-1])
                if current_row[column] > result.size:
                    result = Result(size=current_row[column], row=row, column=column)
        previous_row = current_row
    return result


class UnitTests(unittest.TestCase):
    def __expect_result(self, result: Result, size: int, row: int, column: int) -> None:
        self.assertEqual(result.size, size)
        self.assertEqual(result.row, row)
        self.assertEqual(result.column, column)

    def test_example(self):
        result = solve(
            matrix=numpy.array([
                [0, 1, 1, 0, 1],
                [1, 1, 0, 1, 0],
                [0, 1, 1, 1, 0],
                [1, 1, 1, 1, 0],
                [1, 1, 1, 1, 1],
                [0, 0, 0, 0, 0]]))
        self.__expect_result(result, 3, 4, 3)  # 3x3 sub-matrix with all 1s ending at (4, 3)

    def test_corner(self):
        self.__expect_result(solve(numpy.array([[0]])), 0, 0, 0)
        self.__expect_result(solve(numpy.array([[1]])), 1, 0, 0)

    def test_single_row(self):
        self.__expect_result(solve(numpy.array([[0, 0, 0, 0]])), 0, 0, 0)
        self.__expect_result(solve(numpy.array([[1, 0, 0, 0]])), 1, 0, 0)
        self.__expect_result(solve(numpy.array([[0, 0, 1, 0]])), 1, 0, 2)

    def test_single_column(self):
        self.__expect_result(solve(numpy.array([[0], [0], [0]])), 0, 0, 0)
        self.__expect_result(solve(numpy.array([[1], [0], [0]])), 1, 0, 0)
        self.__expect_result(solve(numpy.array([[0], [0], [1]])), 1, 2, 0)


if __name__ == '__main__':
    unittest.main()
