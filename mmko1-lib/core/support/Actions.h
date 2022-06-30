#ifndef MMKO1_LIB_ACTIONS_H
#define MMKO1_LIB_ACTIONS_H

#include <functional>

class CallFunc {
public:
    static CallFunc* create(const std::function<void()>& func);

    CallFunc(const CallFunc& ) = delete;
    CallFunc& operator=(const CallFunc& ) = delete;
    CallFunc(CallFunc&& ) = delete;
    CallFunc& operator=(CallFunc&& ) = delete;

   /** initialize the action with the std::function<void()>
    *
    */
    bool initWithFunction(const std::function<void()>& func);
private:
    CallFunc() = default ;
    ~CallFunc() = default;

    /** function that will be called */
    std::function<void()>& _function;
};


#endif //MMKO1_LIB_ACTIONS_H
