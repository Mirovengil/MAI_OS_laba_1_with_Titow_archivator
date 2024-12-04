#ifndef TQUEUE_H
#define TQUEUE_H

#include <string>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "TMessage.h"

class TQueue
{
private:
    int qId;
    key_t key;
    int indexOfLastElem;

    bool keyIsCorrect();
    bool qIdIsCorrect();
    bool tryToCloseIsSuccess();

    TMessage messageToPop;
public:
    TQueue (int id=777, std::string way="/home/ivan/MAI/OS/laba_3_cpp_ver/TQueue.h");
    ~TQueue();

    void close();
    void addElem(TMessage elem);
    TMessage popElem();
    void waitForReceiving();
};

#endif //TQUEUE_H