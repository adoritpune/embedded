#include <incap.h>

#ifdef _IC1IF

/********************************************************************
*    Function Name:  ReadCapture3                                   *
*    Description:    This routine reads all pending InputCapture    *
*                    Buffers and stores in the locations specified  *
*    Parameters:     address of locations where buffer data to be   *
*                    stored                                         *
*    Return Value:   None                                           *
********************************************************************/

void ReadCapture1(unsigned int * buffer)
{
	while (IC1CONbits.ICBNE)
	{
		*buffer++ = IC1BUF; /* reads the input capture buffer */
	}
}

#else
#warning "Does not build on this target"
#endif
