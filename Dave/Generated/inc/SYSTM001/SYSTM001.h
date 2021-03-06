/*******************************************************************************
**  DAVE App Name : SYSTM001       App Version: 1.0.18               
**  This file is generated by DAVE, User modification to this file will be    **
**  overwritten at the next code generation.                                  **
*******************************************************************************/

/*CODE_BLOCK_BEGIN[SYSTM001.h]*/
/**************************************************************************//**
 *
 * Copyright (C) 2014 Infineon Technologies AG. All rights reserved.
 *
 * Infineon Technologies AG (Infineon) is supplying this software for use with
 * Infineon's microcontrollers.
 * This file can be freely distributed within development tools that are
 * supporting such microcontrollers.
 *
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 * OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
********************************************************************************
**                                                                            **
**                                                                            **
** PLATFORM : Infineon XMC4000/XMC1xxx Series		                          **
**                                                                            **
** COMPILER : Compiler Independent                                            **
**                                                                            **
** AUTHOR   : App Developer                                                   **
**                                                                            **
** MAY BE CHANGED BY USER [yes/Yes]: Yes                                      **
**                                                                            **
** MODIFICATION DATE : Jan 29, 2014                                           **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                       Author(s) Identity                                   **
********************************************************************************
**                                                                            **
** Initials     Name                                                          **
** ---------------------------------------------------------------------------**
** Yogesh     App Developer                                                   **
*******************************************************************************/
/* Revision History
 *****************************************************************************
 *Date           Version     Remarks
 *13/1/2013       1.0.10      XMC1xxx device support added
 *03/10/2013      1.0.14      XMC1201,XMC1202,XMC1301 device support added.
 *29/01/2014      1.0.16      DBG002 App changes are taken care
 *
*/
/**
 * @file SYSTM001.h
 *
 * @App Version SYSTM001 <1.0.18>
 * 
 * @brief  Simple System Timer App implementation header file.
 *
 */

 #ifndef SYSTM001_H_
 #define SYSTM001_H_

 /* Support for C++ codebase */
 #ifdef __cplusplus
 extern "C" {
 #endif
 /*******************************************************************************
**                      Include Files                                         **
*******************************************************************************/
/* Inclusion of Platform specific file */
#include <DAVE3.h>

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/**
 * @ingroup SYSTM001_publicparam
 * @{
 */

  /* System Core clock frequency in MHz */

  
#define SYSTM001_SYS_CORE_CLOCK  32.0 


  /* Time between between two systick interrupt in Msec */
 #define SYSTM001_SYSTICK_INTERVAL 1U
  /* Maximum No of timer */
#define SYSTM001_CFG_MAX_TMR  32U 

/* Macro function to convert systick count to millisecond */
#define CONVERT_SYSTICK_COUNT_TO_MSEC(val) (val * SYSTM001_SYSTICK_INTERVAL)
/* Macro function to convert millisecond to systick count */
#define CONVERT_MSEC_TO_SYSICK_COUNT(val)   (SYSTM001_SYS_CORE_CLOCK * val * 1000U)

/**
 * @}
 */

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/
/**
 * @ingroup SYSTM001_publicparam
 * @{
 */

/*
 * This enumeration define possible timer state.
 */
typedef enum SYSTM001_TimerStateType{
/**
 * The timer is in running state
 */
  SYSTM001_STATE_RUNNING,
/**
  * The timer is stopped
 */
  SYSTM001_STATE_STOPPED
}SYSTM001_TimerStateType;

/**
 * Enum values which describes timer types
 */
typedef enum SYSTM001_TimerType
{
  /**
    * Timer Type is one shot.
    */
  SYSTM001_ONE_SHOT,
  /**
   * Timer Type is periodic.
   */
  SYSTM001_PERIODIC
}SYSTM001_TimerType;



/**
 * Enum values which describes return status of functions
 */
typedef enum SYSTM001_ErrorCodesType
{
  /**
   * Invalid Handle.
   */
  /**
   * @cond INTERNAL_DOCS
   * @param MODULENAME SYSTM001
   * @endcond
  */
  /**
   * @cond INTERNAL_DOCS
   * @param	ERRCODESTRING1 SYSTM001_INVALID_HANDLE_ERROR
   * @param	STRCODESTRING1 Input handle is not valid
   * @endcond
  */
  SYSTM001_INVALID_HANDLE_ERROR = 1,
  /**
   * Timer error occured.
   */
  /**
   * @cond INTERNAL_DOCS
   * @param	ERRCODESTRING2 SYSTM001_ERROR
   * @param	STRCODESTRING2 Timer Error
   * @endcond
  */
  SYSTM001_ERROR,
  /**
   * Debuglog function entry.
   */
  /**
   * @cond INTERNAL_DOCS
   * @param	ERRCODESTRING3 SYSTM001_FUNCTION_ENTRY
   * @param	STRCODESTRING3 Entered function \%s
   * @endcond
   *
   */
  SYSTM001_FUNCTION_ENTRY,
  /**
   * Debuglog function exit.
   */
  /**
   * @cond INTERNAL_DOCS
   * @param ERRCODESTRING4 SYSTM001_FUNCTION_EXIT
   * @param STRCODESTRING4 Exited function \%s
   * @endcond
  */
  SYSTM001_FUNCTION_EXIT
}SYSTM001_ErrorCodesType;


/**
 * Timer callback function pointer.
 */
typedef void (*SYSTM001_TimerCallBackPtr)(void* ParamToCallBack);



/**
 * Global structure which acts as the timer control block .
 *  
 */
typedef struct SYSTM001_TimerObject
{
  /* <<<DD_SYSTM001_STRUCT_1>>> */
  /** Timer ID  */
  uint32_t TimerID;
  /** Timer Type (Single Shot or Periodic)*/
  SYSTM001_TimerType TimerType;
  /** Timer State  */
  SYSTM001_TimerStateType TimerState;
  /** Timer Counter  */
  uint32_t TimerCount;
  /** Timer Reload Counter value */
  uint32_t TimerReload;
  /** Callback function pointer */
  SYSTM001_TimerCallBackPtr TimerCallBack;
  /** Parameter to callback function */
  void* ParamToCallBack;
  /** pointer to next timer control block*/
  struct SYSTM001_TimerObject*  TimerNext;
  /** Pointer to previous timer control block */
  struct SYSTM001_TimerObject*  TimerPrev;
}SYSTM001_TimerObject;


/**
 * @}
 */

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/


/*******************************************************************************
**                      Extern Variables                                      **
*******************************************************************************/


/*******************************************************************************
**                     FUNCTION PROTOTYPES                                    **
*******************************************************************************/
/**
 * @ingroup SYSTM001_apidoc
 * @{
 */


/**
 * Initializes the systick counter as per the systick interval specified by the 
 * user and start the systick counter. It also initializes global variables.
 *
 * @return     void
 *
 *
 * <b>Reentrant: NO </b><BR>
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  int main(void)
 *  {
 *    // Initialize and Systick counter
 *    DAVE_Init(); // SYSTM001_Init() will be called within DAVE_Init()
 *    // ... infinite loop ...
 *    while(1)
 *    {
 *    
 *    }
 *     
 *  }
 * @endcode<BR> </p>
 */
void  SYSTM001_Init( void);


/**
 *  Creates a new software Timer.
 *  
 *  Note : This App uses SysTick Exception for controlling the timer list. Call back function
 *  registered through this function will be called in SysTick exception when the timer is expired.
 *  One shot timers are removed from the timer list, if it expires. To use
 *  this SW timer again it has to be first deleted and then created again. 
 *  Periodic timer will be added again to the timer list with the same periodic
 *  value after it expires.
 *
 *
 * @param[in]  Period Timer period value in milliseconds
 * @param[in]  TimerType Type of Timer(ONE_SHOT/PERIODIC)
 * @param[in]  TimerCallBack Call back function of the timer(No Macros are allowed)
 * @param[in]  pCallBackArgPtr Call back function parameter
 *
 * @return     handle_t<BR> 
 *             Timer ID : If timer created successfully.<BR>
 *             0  : If timer creation failed.<BR>
 *
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 * static volatile bool TimerExpired;
 * void my_func_a(void* Temp)
 *  {
 *    static uint32_t Count = 1;
 *    if(Count == 10)
 *    {
 *      TimerExpired = TRUE;
 *    }
 *    Count++;
 *  }
 *  int main(void)
 *  {
 *    handle_t TimerId;
 *    // ... Initializes Apps configurations ...
 *    DAVE_Init();
 *    TimerId = SYSTM001_CreateTimer(100,SYSTM001_PERIODIC,my_func_a,NULL);
 *    if(TimerId != 0)
 *    {
 *    //Timer is created successfully
 *    }
 *    // ... infinite loop ...
 *    while(1)
 *    {
 *    
 *    }
 *     
 *  }
 * @endcode<BR> </p>
 */
handle_t SYSTM001_CreateTimer
(
  uint32_t Period,
  SYSTM001_TimerType TimerType,
  SYSTM001_TimerCallBackPtr TimerCallBack,
  void  * pCallBackArgPtr
);

/**
 * Starts the software timer .
 *
 *
 * @param[in]  Handle Timer ID obtained from SYSTM001_CreateTimer
 *
 * @return     status_t<BR>
 *             DAVEApp_SUCCESS 			: If timer is started successufully<BR>
 *             SYSTM001_INVALID_HANDLE  : If Timer ID  passed is invalid<BR>
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  static volatile bool TimerExpired; 
 *  void my_func_a(void* Temp)
 *  {
 *    static uint32_t Count = 1;
 *    if(Count == 10)
 *    {
 *      TimerExpired = TRUE;
 *    }
 *    Count++;
 *  }
 *  int main(void)
 *  {
 *    handle_t TimerId;
 *    uint32_t Status = SYSTM001_ERROR;
 *    // ... Initializes Apps configurations ...
 *    DAVE_Init();
 *    TimerId = SYSTM001_CreateTimer(100,SYSTM001_PERIODIC,my_func_a,NULL);
 *    if(TimerId != 0)
 *    {
 *      //Timer is created successfully
 *   	Status = SYSTM001_StartTimer(TimerId);
 *   	if(Status == DAVEApp_SUCCESS)
 *   	{
 *   	         //Timer started
 *   	}
 *	  }
 *    // ... infinite loop ...
 *    while(1)
 *    {
 *    
 *    }
 *  }
 * @endcode<BR> </p>
 */
status_t SYSTM001_StartTimer(handle_t  Handle) ;


/**
 * Stops the software timer
 *
 * @param[in]  Handle Timer ID obtained from SYSTM001_CreateTimer
 *
 * @return     status_t<BR>
 *             DAVEApp_SUCCESS 			: if timer is stopped successfully.<BR>
 *             SYSTM001_INVALID_HANDLE  : If Timer ID  passed is invalid.<BR>
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  static volatile bool TimerExpired;
 *  void my_func_a(void* Temp)
 *  {
 *   static uint32_t Count = 1;
 *   if(Count == 10)
 *   {
 *     TimerExpired = TRUE;
 *   }
 *    Count++;
 *  }
 *  int main(void)
 *  {
 *    handle_t TimerId;
 *   uint32_t Status = SYSTM001_ERROR;
 *   // ... Initializes Apps configurations ...
 *    DAVE_Init();
 *    TimerId = SYSTM001_CreateTimer(100,SYSTM001_PERIODIC,my_func_a,NULL);
 *    if(TimerId != 0)
 *    {
 *      //Timer is created successfully
 *    	Status = SYSTM001_StartTimer(TimerId);
 *      if(Status == DAVEApp_SUCCESS)
 *    	{
 *    	   // Wait till timer is expired
 *    	   while(TimerExpired == FALSE)
 *         {}
 *    		//stop the timer
 *    		Status = SYSTM001_StopTimer(TimerId);
 *    	    if(Status == DAVEApp_SUCCESS)
 *    		{
 *    	      //Timer stopped
 *    		}
 *       }
 *       // start the timer
 *        SYSTM001_StartTimer(TimerId);
 *    }
 *    // ... infinite loop ...
 *    while(1)
 *    {
 *     
 *    }
 *      
 * }
 * @endcode<BR> </p>
 */
status_t SYSTM001_StopTimer(handle_t Handle) ;

/**
 * Deletes the software timer from the timer list.
 *  
 *  Note : One shot timers are removed from the timer list, if it expires. To use 
 *  this SW timer again it have to be first deleted and then created again. 
 *  Periodic timer will be added again to the timer list with the same periodic
 *  value after it expires.
 *
 *
 * @param[in]  Handle Timer ID
 *
 * @return     status_t<BR>
 *             DAVEApp_SUCCESS 			: if timer is deleted successufully.<BR>
 *             SYSTM001_INVALID_HANDLE  : If Timer ID  passed is invalid.<BR>
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  static volatile bool TimerExpired;
 *  void my_func_a(void* Temp)
 *  {
 *   static uint32_t Count = 1;
 *   if(Count == 10)
 *   {
 *     TimerExpired = TRUE;
 *   }
 *   Count++;
 *  }
 *  int main(void)
 *  {
 *    handle_t TimerId;
 *    uint32_t Status = SYSTM001_ERROR;
 *    // ... Initializes Apps configurations ...
 *    DAVE_Init();
 *    TimerId = SYSTM001_CreateTimer(100,SYSTM001_PERIODIC,my_func_a,NULL);
 *    if(TimerId != 0)
 *    {
 *      //Timer is created successfully
 *      Status = SYSTM001_StartTimer(TimerId);
 *      if(Status == DAVEApp_SUCCESS)
 *    	{
 *        // Wait till timer is expired
 *        while(TimerExpired == FALSE)
 *        {}
 *    	  //stop the timer
 *    	  Status = SYSTM001_StopTimer(TimerId);
 *        if(Status == DAVEApp_SUCCESS)
 *    	  {
 *    	    SYSTM001_DeleteTimer(TimerId);
 *    	  }
 *      }
 *    }    
 *    // ... infinite loop ...
 *    while(1)
 *    {
 *     
 *    } 
 * }
 * @endcode<BR> </p>
 */
status_t SYSTM001_DeleteTimer(handle_t Handle) ;


/**
 * Gives the current system time in millisec since start of counter.
 *
 *
 * @return     uint32_t returns current system time in millisec.
 *
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  static volatile bool TimerExpired; 
 *  void my_func_a(void* Temp)
 *  {
 *    static uint32_t Count = 1;
 * 	  if(Count == 10)
 *    {
 *      TimerExpired = TRUE;
 *    }
 *    Count++;
 *  }
 *  int main(void)
 *  {
 * 	  handle_t TimerId;
 *    uint32_t SystemTime = 0;
 *    uint32_t Status = SYSTM001_ERROR;
 *    // ... Initializes Apps configurations ...
 *    DAVE_Init();
 *    TimerId = SYSTM001_CreateTimer(100,SYSTM001_PERIODIC,my_func_a,NULL);
 *    if(TimerId != 0)
 *    {
 *      //Timer is created successfully
 *      Status = SYSTM001_StartTimer(TimerId);
 *      if(Status == DAVEApp_SUCCESS)
 *      {
 *        SystemTime = SYSTM001_GetTime();
 *      }
 *    }
 *     // ... infinite loop ...
 *    while(1)
 *    {
 *    
 *    }
 * }
 * @endcode<BR> </p>
 */
uint32_t  SYSTM001_GetTime(void);


/**
 * Utility function to get the no of system ticks for the
 * specified period given in millisec.
 *
 *
 * @return     uint32_t returns no of system ticks
 *
 *
 * <b>Reentrant: NO </b><BR>
 *
 * <BR><P ALIGN="LEFT"><B>Example:</B>
 * @code
 *  #include <DAVE3.h>
 *  int main(void)
 *  {
 *    uint32_t SysTickCount = 0;
 *    DAVE_Init();
 *    // Get systick timer count value for 100millisec
 *    SysTickCount = SYSTM001_GetSysTickCount(100);
 *    return 0;
 *  }
 * @endcode<BR> </p>
 */
uint32_t  SYSTM001_GetSysTickCount(uint32_t Period );

/**
 *@}
 */

/* Support for C++ codebase */
#ifdef __cplusplus
}
#endif  

#endif /* SYSTM001_H_ */   

/*CODE_BLOCK_END*/
