#ifndef LS_H
#define LS_H

#include "command.h"

class Ls : public Command
{
public:
    Ls();
    Ls(QList<QByteArray>);
    void command_effect();
};

#endif // LS_H