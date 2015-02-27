#include "../Classes/AppDelegate.h"
#include "cocos2d.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>

#include <sys/sysmips.h>

USING_NS_CC;

int main(int argc, char **argv)
{
    printf("main()\n");
    sysmips(MIPS_FIXADE, 1);
    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}
