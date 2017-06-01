extern "C"
{
  #include"api_scilab.h"
  #include "Scierror.h"

  int add_two(char *fname, unsigned fname_len)
  {
    SciErr sciErr;

    /*
    * Check number of input arguments=2
    * Check number of output arguments=1
    */
    CheckInputArgument(pvApiCtx,2,2);
    CheckOutputArgument(pvApiCtx,1,1);

    int *a_address; //address for first i/p arg
    int *b_address; //address for second i/p arg
    double *mat1=NULL; //first matrix
    int mat1_rows=0;
    int mat1_col=0;
    double *mat2=NULL; //second matrix
    int mat2_rows=0;
    int mat2_col=0;

    sciErr=getVarAddressFromPosition(pvApiCtx,1,&a_address); //get address of first argument
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }
    sciErr=getMatrixOfDouble(pvApiCtx,a_address,&mat1_rows,&mat1_col,&mat1); // matrix of first argument
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    sciErr=getVarAddressFromPosition(pvApiCtx,2,&b_address);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }
    sciErr=getMatrixOfDouble(pvApiCtx,b_address,&mat2_rows,&mat2_col,&mat2);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    //program

    double *resMat=NULL;
    resMat=(double*)malloc(sizeof(double));
    *resMat=*mat1+*mat2+3;

    sciErr=createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,1,1,resMat);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }
    AssignOutputVariable(pvApiCtx,1)=nbInputArgument(pvApiCtx)+1;
    ReturnArguments(pvApiCtx);
    return 0;
  }
}
