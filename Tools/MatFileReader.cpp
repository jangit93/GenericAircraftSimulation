#include "MatFileReader.h"


MatFileReader::MatFileReader(const char * filename)
{
	ing_index = 0;
	err = EXIT_SUCCESS;


	mat = Mat_Open(filename, MAT_ACC_RDONLY);

	if (NULL == mat) {
		fprintf(stderr, "Error opening a.mat\n");
		//return EXIT_FAILURE;
	}
}

MatFileReader::~MatFileReader()
{
}



std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Float64,Eigen::RowVectorXd> MatFileReader::readMatFileStructure(const char * FieldName, 
																											 int & start, 
																											 int & stride, 
																											 int & edge, 
																											 int & copy_fields)
{
	stru = Mat_VarGetStructsLinear(matvar, start, stride, edge, copy_fields); 

	if (NULL == stru) {
		fprintf(stderr, "Error getting 'ing{%lu}'\n", ing_index);
		err = EXIT_FAILURE;
	}
	else if (MAT_C_STRUCT != stru->class_type) {
		fprintf(stderr, "Variable 'ing{%lu}' is not a struct-arrayn\n", ing_index);
		err = EXIT_FAILURE;
	}
	else {
		field = Mat_VarGetStructFieldByName(stru, FieldName, 0); 
		if (NULL == stru) {
			fprintf(stderr, "Error getting 'ing{%lu}.%s'\n", ing_index, FieldName);
			err = EXIT_FAILURE;
		}
		else {
			read_err = Mat_VarReadDataAll(mat, field); 
			if (read_err) {
				fprintf(stderr, "Error reading data for 'ing{%lu}.%s'\n", ing_index, FieldName);
				err = EXIT_FAILURE;
			}
			else 
			{
				if (MAT_T_DOUBLE == field->data_type) {
					field->dims;
					unsigned xSize = field->nbytes / field->data_size;
					const double *xData = static_cast<const double*>(field->data);
					size_t * dim = static_cast<size_t*>(field->dims);
			
					if (dim[0] > 1 && dim[1] > 1)
					{
						matrix.resize(dim[0], dim[1]);
						for (int i = 0; i < dim[0]; ++i) {
							for (int ii = 0; ii < dim[1]; ii++) {
								matrix(i, ii) = xData[ii*dim[0] + i];
							}

						}
						//std::cout << matrix << std::endl;
					}
					else if (dim[0] == 1 && dim[1] == 1) {
						value = xData[0];
					}
					else if (dim[0] == 1 && dim[0] < dim[1]) {
						row_vector.resize(dim[1]);
						for (int i = 0; i < dim[1] ; ++i) {
							row_vector(i) = xData[i];
						}
					}	
					else {
						vector.resize(std::max(dim[0], dim[1]));
						for (int i = 0; i < std::max(dim[0], dim[1]); ++i) {
							vector(i) = xData[i];
						}
					}
					return std::make_tuple(matrix, vector, value,row_vector);
				}
			}
		}
	}
}




std::tuple<Eigen::MatrixXd, Eigen::VectorXd, Float64, Eigen::RowVectorXd> MatFileReader::readMatFileData(const char * FieldName)
{
	matvar = Mat_VarRead(mat, FieldName);

	
	if (MAT_T_DOUBLE == matvar->data_type) {

		unsigned xSize = matvar->nbytes / matvar->data_size;
		const double *xData = static_cast<const double*>(matvar->data);
		size_t * dim = static_cast<size_t*>(matvar->dims);
		
		if (dim[0] > 1 && dim[1] > 1)
		{
			matrix.resize(dim[0], dim[1]);
			for (int i = 0; i < dim[0]; ++i) {
				for (int ii = 0; ii < dim[1]; ii++) {
					matrix(i, ii) = xData[ii*dim[0] + i];
				}
			}

		}
		else if (dim[0] == 1 && dim[1] == 1) {
			value = xData[0];
		}
		else {
			vector.resize(std::max(dim[0], dim[1]));
			for (int i = 0; i < std::max(dim[0], dim[1]); ++i) {
				vector(i) = xData[i];
			}
		}
		return std::make_tuple(matrix, vector, value,row_vector);
	}
}

matvar_t MatFileReader::getMatFileInfo(const char * MatFileName)
{

	matvar = Mat_VarReadInfo(mat, MatFileName);
	if (NULL == matvar) {
		fprintf(stderr, "Error reading 'AutpilotData' variable information\n");
		err = EXIT_FAILURE;
	}

	return *matvar;
}

