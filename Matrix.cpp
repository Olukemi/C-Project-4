
#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
#include <string>
using namespace std;

Matrix::Matrix(){
 rowsNum=3;
 colsNum=3;
 matrixData=NULL;
 matrixData = (int**)malloc(rowsNum*sizeof(int*));

    // Allocate rows for fake "2D array":
    for (int i = 0 ; i < rowsNum ; ++i )
    {
       matrixData[i] = (int*) malloc(colsNum*sizeof(int));
    }

    for (int i = 0 ; i < rowsNum ; ++i )
    	for (int j = 0 ; j < colsNum ; ++j )
    		matrixData[i][j]=0;
}

Matrix::Matrix( int row, int col ){

	/*
	* constructs a row-by-col matrix with
	* all elements equal to 0; if row ≤ 0, the number of rows of the matrix is set to
	* 3; likewise, if col ≤ 0 the number of columns of the matrix is set to 3.
	*/

	// initialize rows, columns and the matrix
	rowsNum = row;
	colsNum = col;
	matrixData = NULL;

	if (row <= 0){ // if number of rows is less than or equal to 0, set number of rows to be 3
		rowsNum = 3;
	} else { // else number of rows remains as initialized
		rowsNum = row;
	}

	if (col <= 0){ // if number of columns is less than or equal to 0, set number of columns to be 3
		colsNum = 3;
	} else { // else number of columns remains as initialized
		colsNum = col;
	}

	matrixData = (int**) malloc(colsNum*sizeof(int)); // generate memory for the matrix

	for (int i = 0 ; i < rowsNum ; ++i ){
	     matrixData[i] = (int*) malloc(colsNum*sizeof(int)); // generate memory for rows in the matrix
	}

	for(int r = 0; r < rowsNum; r++){
		for(int c = 0; c < colsNum; c++){
			matrixData[r][c] = 0; // set each element in the matrix equal to 0
		}
	}


	         

}


Matrix::Matrix(int row, int col, int** table){

	/*
	* constructs a matrix out of the two dimensional array table, with the same number of rows, columns, and the same
	* element in each position as array table.
	*/

	//initialize rows, columns and the matrix
	rowsNum = row;
	colsNum = col;
	matrixData = NULL;

	matrixData = (int**)malloc(rowsNum*sizeof(int*)); // generate memory for the matrix

	for (int i = 0 ; i < rowsNum ; ++i ){
		 matrixData[i] = (int*) malloc(colsNum*sizeof(int)); // generate memory for rows in the matrix
	}

	for(int r = 0; r < rowsNum; r++){
		for(int c = 0; c < colsNum; c++){
			matrixData[r][c] = *(*(table+r)+c); // set each element in the matrix equal to the element from the table at the same position
		}
	}

	

}

int Matrix::getElement(int i, int j){

	if (i < 0 || i > rowsNum || j < 0 || j > colsNum){ // check if indices are valid
		throw std::out_of_range("Invalid indexes."); // if not, throw this exception
	} else {
		return matrixData[i][j]; // if indices are valid return the element at i,j in the matrix
	}

}

bool Matrix::setElement(int x, int i, int j){

	if (i < 0 || i > rowsNum || j < 0 || j > colsNum){ // check if indices are valid
		return false; // return false if not valid
	} else {
		matrixData[i][j] = x; // if valid set element at i,j in matrix to equal x
		return true; // return true
	}

}


Matrix Matrix::copy(){

	/* fix the code and write your implementation below */
	Matrix copy = Matrix (0,0); // dynamically allocates memory for new matrix

    copy =  Matrix(rowsNum,colsNum);

    for(int r = 0; r < rowsNum; r++){
    	for(int c = 0; c < colsNum; c++){
    		copy.setElement(getElement(r, c), r, c); // get element at r,c and set the element in new matrix copy to be that element from the old copy
    	}
    }

    //return copy
    return  copy;


}


void Matrix::addTo( Matrix m ){
	
	if (m.getsizeofrows() != rowsNum || m.getsizeofcols() != colsNum){ // check if a both matrices are of the same size in rows and columns
		throw std::invalid_argument("Invalid operation"); // throw exception if not
	} else {
		for(int r = 0; r < rowsNum; r++){
			for(int c = 0; c < colsNum; c++){
				int x = (getElement(r, c) + m.getElement(r, c)); // add the 2 elements from both matrices together
				setElement(x, r, c); //set "this" matrix to be equal to the sum
			}
		}
	}

}


Matrix Matrix::subMatrix(int i, int j){

	/* The exception detail message should read: "Submatrix not defined"*/

	/* fix the code and write your implementation below */
	Matrix subM = Matrix (i+1,j+1); // generate an empty matrix for submatrix

	if (i >= rowsNum || i < 0 || j >= colsNum || i < 0){ // check if a submatrix is possible
			throw::out_of_range("Submatrix not defined"); // throw exception if not
	} else {
		for(int r = 0; r < i+1; r++){
			for(int c = 0; c < j+1; c++){
				subM.setElement(getElement(r, c), r, c); //set the elements to be the value for the submatrix from "this" matrix
			}
		}
	}

	// return submatirx
    return  subM;
}


int Matrix::getsizeofrows(){

	
	/* update below return */
	return rowsNum;
}


int Matrix::getsizeofcols(){



	/* update below return */
    return colsNum;
}


bool Matrix::isUpperTr(){

	/* write your implementation here and update return accordingly */
	
	// loop through the numbers below the diagonal
	for(int r = 1; r < getsizeofrows(); r++){
		for(int c = 0; c < r; c++){
			if(getElement(r,c) != 0){ // if the element at r,c below the diagonal doesn't equal 0 then return false indicating the matrix is not an upper triangle matrix
				return false;
			}
		}
	}

	// return true if matrix is an upper triangle matrix
	return true;
}


string Matrix::toString(){

	string output="";

	for(int r = 0; r < getsizeofrows(); r++){
		for(int c = 0; c < getsizeofcols(); c++){
			output += to_string(getElement(r, c)) + " "; // convert the integers to string and add them to output for that row
		}
		output += "\n"; // make a new line before adding string to output
	}

	//return output
	 return output;
}
