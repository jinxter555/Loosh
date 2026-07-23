#pragma once
// 
// CURRENT_ is use by frame stack

#define UNIVERSE "universe"
#define PID "pid"
#define PPID "ppid"
//#define CFS "control_flow_state"
#define FRAMES "frames"
#define DQ_WORKER "dq_worker"
#define STATE "state"

#define VAR "var"
#define IMMUTE "immute"
#define _NAME "name"
#define VECTOR "vector"
#define NAMESPACE "namespace"
#define CURRENT_NAMESPACE_IMMUTE "__NAMESPACE__"

#define _MODULE "module"
#define MODULE_PTR "module_ptr"

#define CURRENT_MODULE "current_module"
#define CURRENT_MODULE_PTR "current_module_ptr"
#define CURRENT_MODULE_IMMUTE "__MODULE__"
#define CURRENT_PID  "__PID__"
#define CURRENT_PPID  "__PPID__"

#define FUNCTION "function"
#define MACRO "macro"
#define ALIAS "alias"

#define CURRENT_FUNCTION "current_function"
#define CURRENT_FUNCTION_IMMUTE "__FUN__"
#define CURRENT_FUNCTION_PTR "current_function_ptr"

#define _CLASS "class"
#define CLASS_PTR "class_ptr"

#define CURRENT_CLASS "current_class"
#define CURRENT_CLASS_IMMUTE "__CLASS__"

#define CURRENT_CLASS_PTR "current_class_ptr"

#define CURRENT_PROCESS_PID "current_process_pid"
#define CURRENT_PROCESS_PTR "current_process_ptr"

#define PARENT "parent"
#define CODE "code"
#define _PARAMS "params"
#define ARGS "args"
#define SCOPES "scopes"
#define DESC "description"
#define OBJ_INFO "__object_info__"
#define CC_OBJ_ID "__cc_obj_id__"

#define _TYPE "type"
#define BASE_FRAME "base_frame"

#define RET_VALUE "return_value"
#define INITIALIZE "initialize"
#define FINALIZE "finalize"

#define CLOSURABLE_FILE "closurable.txt"

#define LOOSH_T_LONG long