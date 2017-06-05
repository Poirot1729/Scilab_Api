extern "C"
{
  #include "api_scilab.h"
  #include "Scierror.h"

  int matrix(char *fname,unsigned fname_len)
  {
    SciErr sciErr;

    CheckInputArgument(pvApiCtx,2,2);
    CheckOutputArgument(pvApiCtx,1,1);

    double *mat1 = NULL;
    int m1,n1;
    int *add_mat1 = NULL;

    double *mat2 = NULL;
    int m2,n2;
    int *add_mat2 = NULL;

    sciErr = getVarAddressFromPosition(pvApiCtx,1,&add_mat1);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    if(!isDoubleType(pvApiCtx,add_mat1) || isVarComplex(pvApiCtx,add_mat1))
    {
      Scierror(999, ("%s: Wrong type for input argument #%d: A real matrix expected.\n"), fname, 1);
      return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx,add_mat1,&m1,&n1,&mat1);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    sciErr = getVarAddressFromPosition(pvApiCtx,2,&add_mat2);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    if(!isDoubleType(pvApiCtx,add_mat2) || isVarComplex(pvApiCtx,add_mat2))
    {
      Scierror(999, ("%s: Wrong type for input argument #%d: A real matrix expected.\n"), fname, 1);
      return 0;
    }

    sciErr = getMatrixOfDouble(pvApiCtx,add_mat2,&m2,&n2,&mat2);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    //main program

    if(n1 != m2)
    {
      Scierror(999, ("%s: Wrong type for input argument. Number of columns of first matrix should be equal to number of rows of second matrix\n"), fname, 1);
      return 0;
    }

    double *resMat = (double*)malloc(sizeof(double)*m1*n2);

    for(int i=0;i<m1;i++)
    {
      for(int j=0;j<n2;j++)
      {
        resMat[i*n2 + j]=0;
        for(int k=0;k<n1;k++)
        {
          resMat[i*n2 + j]+=mat1[i*n1 + k]*mat2[k*n2 + j];
        }
      }
    }

    sciErr = createMatrixOfDouble(pvApiCtx,nbInputArgument(pvApiCtx)+1,m1,n2,resMat);
    if(sciErr.iErr)
    {
      printError(&sciErr,0);
      return 0;
    }

    AssignOutputVariable(pvApiCtx,1) = nbInputArgument(pvApiCtx) + 1;
    ReturnArguments(pvApiCtx);

    return 0;
  }
}
