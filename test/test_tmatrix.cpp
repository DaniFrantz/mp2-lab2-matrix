#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
	m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
	m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

	TDynamicMatrix<int> m1(m);

	EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(3);
	m[0][0] = 1;

	TDynamicMatrix<int> m1(m);
	m1[0][0] = 100;

	EXPECT_NE(m[0][0], m1[0][0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(3);
	EXPECT_EQ(3, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(3);
	m[1][2] = 42;

	EXPECT_EQ(42, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(-1)[0] = 1);
	ASSERT_ANY_THROW(m.at(0)[-1] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(3);

	ASSERT_ANY_THROW(m.at(3)[0] = 1);
	ASSERT_ANY_THROW(m.at(0)[3] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(3);
	m[1][1] = 5;

	ASSERT_NO_THROW(m = m);
	EXPECT_EQ(5, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(3);

	m1[0][0] = 7;
	ASSERT_NO_THROW(m2 = m1);
	EXPECT_EQ(7, m2[0][0]);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(4);

	m2 = m1;
	EXPECT_EQ(3, m2.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	m1[0][0] = 5;

	ASSERT_NO_THROW(m2 = m1);
	EXPECT_EQ(5, m2[0][0]);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m1[0][0] = 1; m1[0][1] = 1;
	m1[1][0] = 3; m1[1][1] = 2;

	m2[0][0] = 1; m2[0][1] = 1;
	m2[1][0] = 3; m2[1][1] = 2;

	EXPECT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(3);
	EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(3);
	TDynamicMatrix<int> m2(5);

	EXPECT_NE(m1, m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m1[0][0] = 1; m1[0][1] = 2;
	m1[1][0] = 3; m1[1][1] = 4;

	m2[0][0] = 5; m2[0][1] = 6;
	m2[1][0] = 7; m2[1][1] = 8;

	TDynamicMatrix<int> res = m1 + m2;

	EXPECT_EQ(6, res[0][0]);
	EXPECT_EQ(8, res[0][1]);
	EXPECT_EQ(10, res[1][0]);
	EXPECT_EQ(12, res[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(2);

	m1[0][0] = 5; m1[0][1] = 7;
	m1[1][0] = 9; m1[1][1] = 11;

	m2[0][0] = 1; m2[0][1] = 2;
	m2[1][0] = 3; m2[1][1] = 4;

	TDynamicMatrix<int> res = m1 - m2;

	EXPECT_EQ(4, res[0][0]);
	EXPECT_EQ(5, res[0][1]);
	EXPECT_EQ(6, res[1][0]);
	EXPECT_EQ(7, res[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(2);
	TDynamicMatrix<int> m2(3);

	ASSERT_ANY_THROW(m1 - m2);
}
TEST(TDynamicMatrix, can_get_X_and_Y_of_Line)
{
	int l = 0;
	TDynamicMatrix<int> v(6);
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {

				if (i + k < 6 && j + k < 6 && v[i + k][j + k] == 0) {
					l += 1;
					v[i + k][j + k] = l;
				}
			}
		}
	}
	EXPECT_EQ(2, v.getting_lineX());
	EXPECT_EQ(3, v.getting_lineY());
}
TEST(TBendedMatrix, can_construct_bended_from_dynamic)
{
	int l = 0;
	TDynamicMatrix<int> v(6);
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {
				
				if (i + k < 6 && j + k < 6 &&  v[i + k][j + k] == 0){
					l += 1;
					v[i + k][j + k] = l; 
				}
			}
		}
	}
	ASSERT_NO_THROW(TBendedMatrix<int> w(v));
}
TEST(TBendedMatrix, can_recreate_matrix_from_bended)
{
	int l = 0;
	TDynamicMatrix<int> v(6);
	for (int k = 0; k < 5; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 3; j++) {

				if (i + k < 6 && j + k < 6 && v[i + k][j + k] == 0) {
					l += 1;
					v[i + k][j + k] = l;
				}
			}
		}
	}
	TBendedMatrix<int> w(v);
	EXPECT_EQ(v, w.ReturnMatrix());
}
//TEST(TBendedMatrix, can_use_output_operator)
//{
//	int l = 0;
//	TDynamicMatrix<int> v(7);
//	for (int k = 0; k < 6; k++) {
//		for (int i = 0; i < 2; i++) {
//			for (int j = 0; j < 5; j++) {
//
//				if (i + k < 7 && j + k < 7 && v[i + k][j + k] == 0) {
//					l += 1;
//					v[i + k][j + k] = l;
//				}
//			}
//		}
//	}
//	TBendedMatrix<int> w(v);
//	EXPECT_EQ(v, w.ReturnMatrix());
//	ASSERT_NO_THROW(cout << w);
//}
TEST(TBendedMatrix, can_use_index_operand)
{
	int l = 0;
	TDynamicMatrix<int> v(7);
	for (int k = 0; k < 6; k++) {
		for (int i = 0; i < 2; i++) {
			for (int j = 0; j < 5; j++) {

				if (i + k < 7 && j + k < 7 && v[i + k][j + k] == 0) {
					l += 1;
					v[i + k][j + k] = l;
				}
			}
		}
	}
	TBendedMatrix<int> w(v);
	ASSERT_NO_THROW(w[30]);
}
TEST(TSparseMatrix, can_construct_from_TDynamicMatrix)
{
	TDynamicMatrix<int> v(6);
	v[1][1] = 1; // 0 0 0 0 0 0
	v[4][1] = 2; // 0 1 0 0 2 0
	v[2][4] = 3; // 0 0 0 0 0 0
	v[3][5] = 4; // 0 0 0 0 0 0
				 // 0 0 3 0 0 0
				 // 0 0 0 4 0 0
	TSparseMatrix<int> w(v);
	for (int i = 0; i < w.num_of_col(); i++) {
		cout << w.getRow(i) << ' ';
	}
	cout << '\n';
	for (int i = 0; i < w.getSize(); i++) {
		cout << w.getIndCol(i) << ' ';
	}
	cout << '\n';
	for (int i = 0; i < w.getSize(); i++) {
		cout << w.getValue(i) << ' ';
	}
	cout << '\n';

}
TEST(TSparseMatrix, can_use_output_operator)
{
	TDynamicMatrix<int> v(6);
	v[1][1] = 1; // 0 0 0 0 0 0
	v[4][1] = 2; // 0 1 0 0 2 0
	v[2][4] = 3; // 0 0 0 0 0 0
	v[3][5] = 4; // 0 0 0 0 0 0
				 // 0 0 3 0 0 0
				 // 0 0 0 4 0 0
	TSparseMatrix<int> w(v);
	cout << w;
}