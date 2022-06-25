""" Maximum size square sub-matrix with all 1s

Source: Geeks for geeks
https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/

Given a binary matrix, find the maximum size square sub-matrix with all 1s.
"""
import unittest
import numpy


class Result:
    def __init__(self, *, size: int, row: int, column: int):
        self.size = size
        # bottom right corner of the sub-matrix:
        self.row = row
        self.column = column


def solve(matrix: numpy.ndarray, *, debug: bool = False) -> Result:
    result = Result(size=0, row=0, column=0)

    rows, columns = matrix.shape
    m = numpy.array([[0 for _ in range(columns)] for _ in range(rows)])
    # Top and left boundaries match the original matrix:
    for column in range(columns):
        m[0, column] = matrix[0, column]
        if result.size < 1 and m[0, column] == 1:
            result = Result(size=1, row=0, column=column)
    for row in range(rows):
        m[row, 0] = matrix[row, 0]
        if result.size < 1 and m[row, 0] == 1:
            result = Result(size=1, row=row, column=0)

    # And some dynamic programming
    for row in range(1, rows):
        for column in range(1, columns):
            if matrix[row, column] == 1:  # else m[row, column] remains 0.
                m[row, column] = 1 + min(m[row-1, column-1], m[row-1, column], m[row, column-1])
                if m[row, column] > result.size:
                    result = Result(size=m[row, column], row=row, column=column)
    if debug:
        print(m)
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
        self.__expect_result(result, 3, 4, 3)

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
