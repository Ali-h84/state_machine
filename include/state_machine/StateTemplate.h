/*
    Author: Alireza Hekmati (alireza@ai-systems.ca)
*/

#ifndef ASM_STATE_TEMPLATE_H_
#define ASM_STATE_TEMPLATE_H_

#include "ros/ros.h"
#include "ais_state_machine/AbstractClasses/AbstractROSState.h"
namespace ais_state_machine 
{

class StateTemplate final: public AbstractROSState
{
public: 
    /*
     *   Constructor that takes in shared_ptr of AbstractStateMachineManager.     
     */
    StateTemplate(shared_ptr<AbstractStateMachineManager> state_manager, ros::NodeHandle& nh);
    /*
     *   Destructor     
     */
    ~StateTemplate();
    /*
     *  Execution loop for state. Must not include long blocking calls as the StateMachineManager
     *  will run this function in a loop.
     */
    void runState();
    /*
     *  Function that signals if state has completed its action from evaluateStateStatus() and needs to
     *  transition to another state.
     */   
    bool isStateFinished();
    /*
     *  Function that returns the next StateTypes enum. (Which state to transition to)
     */ 
    StateTypes getNextStateName();
    /*
     *  Is called when the need to reinitialize State member variables back to clean state for when 
     *  state is transitioned to.
     */ 
    void reset();
    /*
     *  This function is called when the state machine manager transitions OUT of this state.
     */ 
    void finish();
    /*
     *  This function is called when the state machine manager transitions IN to this state.
     */ 
    void init();
    /*
     *  This function is called when an interrupt is triggered in the StateMachineManager. Function 
     *  should cleanly resolve any currently running process in the state. Example: move_base action  
     */ 
    void interruptState();
private: 
    /*
     *  Function that contains code that determines which state should be run next. If the state is not
     *  finished, then the state should point to itself, if the state is finished, state should point
     *  to the next state
     */ 
    void evaluateStateStatus();
};

} // end of namespace ais_state_machine
#endif // END ASM_STATE_TEMPLATE_H_
