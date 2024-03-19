    #ifndef _TEST_DLL_H_  
    #define _TEST_DLL_H_  
    #endif  
      
    #if defined (EXPORTBUILD)  
    # define _DLLExport __declspec (dllexport)  
    # else  
    # define _DLLExport __declspec (dllimport)  
    #endif  

	extern "C" float _DLLExport GJK(float Object_A[][3], float Object_B[][3], int Length_A, int Length_B, float ClosestPoint1[3], float ClosestPoint2[3]);
      
    _DLLExport class GJK_DLL  
    {  
    public:  
        GJK_DLL(void);  
        ~GJK_DLL(void);        
    };  