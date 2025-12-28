

// File: AppDelegate.h
// Brief: Declares the application delegate.
#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"


// AppDelegate encapsulates related behavior and state.


class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    // Initializes the object.

    virtual void initGLContextAttrs();

    
    // TODO: Add a brief description.

    
    virtual bool applicationDidFinishLaunching();

    
    // TODO: Add a brief description.

    
    virtual void applicationDidEnterBackground();

    
    // TODO: Add a brief description.

    
    virtual void applicationWillEnterForeground();
};

#endif 

