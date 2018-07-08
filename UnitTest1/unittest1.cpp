#include "stdafx.h"
#include "CppUnitTest.h"


#include"readInData.h"
#include"DataCloud.h"
#include"LinearInterpolation.h"
#include"MatFileReader.h"
#include"MatFileReader.cpp"
#include"ODESolver.cpp"
#include<Eigen/Dense>
#include"Transformation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
	
		TEST_METHOD(readInParameter_test)
		{	
			//Arrange
			readInData test;
			test.setPath("../../Input/");
			Float64 test_value;
			Float64 reference_value = 9.1;

			//Act
			test_value = test.readInParameter("wing_span", "Aircraft.txt");

			//Assert
			Assert::AreEqual(test_value,reference_value );
			
		}

		TEST_METHOD(readInTable_test)
		{
			//Arrange
			readInData test;
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d reference_matrix;
			reference_matrix << -0.723,-0.727,-0.733,-0.449,-0.452,-0.456,-0.185,-0.186,-0.188;

			int counter = 0;
			int reference_counter = 9;
			test.setPath("../../Input/");

			//Act
			test_matrix = test.readInTable("testMatrix.txt");
			

			//Assert
			Assert::AreEqual(test_matrix(0, 0), test_matrix(0, 0));
			Assert::AreEqual(test_matrix(0, 1), test_matrix(0, 1));
			Assert::AreEqual(test_matrix(0, 2), test_matrix(0, 2));

			Assert::AreEqual(test_matrix(1, 0), test_matrix(1, 0));
			Assert::AreEqual(test_matrix(1, 1), test_matrix(1, 1));
			Assert::AreEqual(test_matrix(1, 2), test_matrix(1, 2));

			Assert::AreEqual(test_matrix(2, 0), test_matrix(2, 0));
			Assert::AreEqual(test_matrix(2, 1), test_matrix(2, 1));
			Assert::AreEqual(test_matrix(2, 2), test_matrix(2, 2));

		}

		TEST_METHOD(Matrix_Transposition_test)
		{
			//Arrange
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d ref_matrix;
			Eigen::Matrix3d matrix;
			test_matrix << 1, 2, 3, 4, 5, 6, 7, 8, 9;
			ref_matrix << 1, 4, 7, 2, 5, 8, 3, 6, 9;

			//Act
			matrix = test_matrix.transpose();


			//Assert
			Assert::AreEqual(matrix(0, 0), ref_matrix(0, 0));
			Assert::AreEqual(matrix(0, 1), ref_matrix(0, 1));
			Assert::AreEqual(matrix(0, 2), ref_matrix(0, 2));

			Assert::AreEqual(matrix(1, 0), ref_matrix(1, 0));
			Assert::AreEqual(matrix(1, 1), ref_matrix(1, 1));
			Assert::AreEqual(matrix(1, 2), ref_matrix(1, 2));

			Assert::AreEqual(matrix(2, 0), ref_matrix(2, 0));
			Assert::AreEqual(matrix(2, 1), ref_matrix(2, 1));
			Assert::AreEqual(matrix(2, 2), ref_matrix(2, 2));
		}


		TEST_METHOD(Matrix_Vector_Multiplication_test)
		{
			//Arrange
			Eigen::Matrix3d test_matrix;
			Eigen::Vector3d test_vector;
			Eigen::Vector3d Vector;
			Eigen::Vector3d ref_vector;
			test_matrix << 1, 2, 3, 4, 5, 6, 7, 8, 9;
			test_vector << 2, 3, 4;
			ref_vector << 20, 47, 74;

			//Act
			Vector = test_matrix * test_vector;


			//Assert
			Assert::AreEqual(Vector(0), ref_vector(0));
			Assert::AreEqual(Vector(1), ref_vector(1));
			Assert::AreEqual(Vector(2), ref_vector(2));
		}
/*
		TEST_METHOD(Matrix_inversion_test)
		{
			//Arrange
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d ref_matrix;
			Eigen::Matrix3d matrix;
			test_matrix << 12,0,-1,0,7,0,-1,0,8;
			ref_matrix << 0.0842105, 0, 0.0105,
				0, 0.1429, 0,
				0.0105, 0, 0.1263;

			//Act
			matrix = test_matrix.inverse();


			//Assert
			//Assert
			Assert::AreEqual(matrix(0, 0), ref_matrix(0, 0));
			Assert::AreEqual(matrix(0, 1), ref_matrix(0, 1));
			Assert::AreEqual(matrix(0, 2), ref_matrix(0, 2));

			Assert::AreEqual(matrix(1, 0), ref_matrix(1, 0));
			Assert::AreEqual(matrix(1, 1), ref_matrix(1, 1));
			Assert::AreEqual(matrix(1, 2), ref_matrix(1, 2));

			Assert::AreEqual(matrix(2, 0), ref_matrix(2, 0));
			Assert::AreEqual(matrix(2, 1), ref_matrix(2, 1));
			Assert::AreEqual(matrix(2, 2), ref_matrix(2, 2));
	

		}*/


		TEST_METHOD(scalar_product_test)
		{
			//Arrange
			Eigen::Vector3d test_vec1;
			Eigen::Vector3d test_vec2;
			int value;
			int ref_value = 20;
			test_vec1 << 1, 2, 3;
			test_vec2 << 2, 3, 4;

			//Act
			value = test_vec1.dot(test_vec2);


			//Assert
			Assert::AreEqual(value, ref_value);
		}


		TEST_METHOD(linearInterpolation_2D_test)
		{
			//Arrange
			readInData test;
			LinearInterpolation testInterp;
			test.setPath("../../Input/");

			MatrixXd CL = test.readInTable("CL.txt");

			VectorXd AOA_table = test.readInVector("AoA.txt");
			VectorXd Mach_table = test.readInVector("Ma.txt");

			Float64 AoA = 2;
			Float64 Mach = 0.31;
			Float64 test_value;
			Float64 reference_value = 0.1912;

			//Act
			test_value = testInterp.linearInterpolation2D(AOA_table, Mach_table, CL, AoA, Mach);

			//Assert
			Assert::AreEqual(test_value, reference_value);
			

		}

		TEST_METHOD(linearInterpolation_1D_test)
		{
			//Arrange
			LinearInterpolation test;
			readInData test1;
			
			test1.setPath("../../Input/Aerodynamics/");
			Eigen:VectorXd Cmq = test1.readInVector("CMQ.txt");
			Eigen::VectorXd Mach_table = test1.readInVector("Ma.txt");

			Float64 test_value;
			Float64 reference_value = -7.3071;
			Float64 Mach = 0.21;
			
			//Act
			test_value = test.linearInterpolation1D(Mach_table, Cmq, Mach);
			
			//Assert
			Assert::AreEqual(test_value,reference_value );

		}

		TEST_METHOD(ODE_solver_test)
		{
			//Arrange
			Float32 a = 0.5;
			Float32 V_0 = 100;
			Float32 V = 100;
			Float32 V_ref;
			Float32 t = 10;
			int dt = 1;
			V_ref = V_0 + a * t;

			//Act
			for (int i = 1; i < 11; i += dt) {
				V = EulerIntegration(V, a, dt);
			}
			
			//Assert
			Assert::AreEqual(V, V_ref);

		}

		TEST_METHOD(MatNEDToBody_Transformation_test)
		{
			//Arrange
			Transformation test;
			Float64 phi = 0;
			Float64 theta  = 0;
			Float64 psi = 0;
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d reference_matrix;
			reference_matrix << 1, 0, 0, 0, 1, 0, 0, 0, 1;
			//Act
			test_matrix = test.MatNedToBody(phi, theta, psi);
			

			//Assert
			Assert::AreEqual(test_matrix(0, 0), test_matrix(0, 0));
			Assert::AreEqual(test_matrix(0, 1), test_matrix(0, 1));
			Assert::AreEqual(test_matrix(0, 2), test_matrix(0, 2));

			Assert::AreEqual(test_matrix(1, 0), test_matrix(1, 0));
			Assert::AreEqual(test_matrix(1, 1), test_matrix(1, 1));
			Assert::AreEqual(test_matrix(1, 2), test_matrix(1, 2));

			Assert::AreEqual(test_matrix(2, 0), test_matrix(2, 0));
			Assert::AreEqual(test_matrix(2, 1), test_matrix(2, 1));
			Assert::AreEqual(test_matrix(2, 2), test_matrix(2, 2));
		}

		TEST_METHOD(MatNEDToTrajectory_Transformation_test)
		{
			//Arrange
			Transformation test;
			Float64 chi = 0;
			Float64 gamma = 0;
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d reference_matrix;
			reference_matrix << 1, 0, 0, 0, 1, 0, 0, 0, 1;
			//Act
			test_matrix = test.MatNEDToTrajectory(gamma, chi);


			//Assert
			Assert::AreEqual(test_matrix(0, 0), test_matrix(0, 0));
			Assert::AreEqual(test_matrix(0, 1), test_matrix(0, 1));
			Assert::AreEqual(test_matrix(0, 2), test_matrix(0, 2));

			Assert::AreEqual(test_matrix(1, 0), test_matrix(1, 0));
			Assert::AreEqual(test_matrix(1, 1), test_matrix(1, 1));
			Assert::AreEqual(test_matrix(1, 2), test_matrix(1, 2));

			Assert::AreEqual(test_matrix(2, 0), test_matrix(2, 0));
			Assert::AreEqual(test_matrix(2, 1), test_matrix(2, 1));
			Assert::AreEqual(test_matrix(2, 2), test_matrix(2, 2));
		}


		TEST_METHOD(MatAeroToBody_Transformation_test)
		{
			//Arrange
			Transformation test;
			Float64 alpha = 0;
			Float64 beta = 0;
			Eigen::Matrix3d test_matrix;
			Eigen::Matrix3d reference_matrix;
			reference_matrix << 1, 0, 0, 0, 1, 0, 0, 0, 1;
			//Act
			test_matrix = test.MatAeroToBody(alpha,beta);


			//Assert
			Assert::AreEqual(test_matrix(0, 0), test_matrix(0, 0));
			Assert::AreEqual(test_matrix(0, 1), test_matrix(0, 1));
			Assert::AreEqual(test_matrix(0, 2), test_matrix(0, 2));

			Assert::AreEqual(test_matrix(1, 0), test_matrix(1, 0));
			Assert::AreEqual(test_matrix(1, 1), test_matrix(1, 1));
			Assert::AreEqual(test_matrix(1, 2), test_matrix(1, 2));

			Assert::AreEqual(test_matrix(2, 0), test_matrix(2, 0));
			Assert::AreEqual(test_matrix(2, 1), test_matrix(2, 1));
			Assert::AreEqual(test_matrix(2, 2), test_matrix(2, 2));
		}





		
		TEST_METHOD(Matfilereader_test)
		{
			//Arrange
			MatFileReader readData("../../Input/test_mat.mat");

			Eigen::Matrix2d A;
			Float64 B;
			Eigen::Vector2d C;

			Eigen::Matrix2d A_ref;
			A_ref << 1, 2, 3, 4;
			Float64 B_ref = 7;
			Eigen::Vector2d C_ref;
			C_ref << 8, 9;
			

			//Act
			A = std::get<0>(readData.readMatFileData("A"));
			B = std::get<2>(readData.readMatFileData("B"));
			C = std::get<1>(readData.readMatFileData("c"));
			//Assert
			Assert::AreEqual(A(0, 0), A_ref(0, 0));
			Assert::AreEqual(A(0, 1), A_ref(0, 1));
			Assert::AreEqual(A(1, 0), A_ref(1, 0));
			Assert::AreEqual(A(1, 1), A_ref(1, 1));

			Assert::AreEqual(B, B_ref);
			Assert::AreEqual(C(0), C_ref(0));
			Assert::AreEqual(C(1), C_ref(1));

		}

	};
}