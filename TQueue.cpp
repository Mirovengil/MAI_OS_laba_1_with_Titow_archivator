#include "TQueue.h"
#include <stdexcept>

bool TQueue::keyIsCorrect()
{
    return (key >= 0);
}

bool TQueue::qIdIsCorrect()
{
    return (qId >= 0);
}

TQueue::TQueue (int id, std::string way)
{
    key = ftok(way.c_str(), id);
    if (!keyIsCorrect())
        throw std::logic_error("TQueue: Problem with key's creating!");

    qId = msgget(key, 0666 | IPC_CREAT);
    if (!qIdIsCorrect())
        throw std::logic_error("TQueue: Problems with queue's creating/opening!");
    
    indexOfLastElem = 1;
}

TQueue::~TQueue()
{
    // no destructor here
}

bool TQueue::tryToCloseIsSuccess()
{
    return (msgctl(qId, IPC_RMID, NULL) >= 0);
}

void TQueue::close()
{
    if (!tryToCloseIsSuccess())
        throw std::logic_error("TQueue: Queue can't be closed!");
}

void TQueue::addElem(TMessage elem)
{
    elem.setType(indexOfLastElem);
    indexOfLastElem++;

    msgsnd(qId, elem.getFirstByte(), TMessage::messageSize, IPC_NOWAIT);
};

TMessage TQueue::popElem()
{
    return messageToPop;
};

void TQueue::waitForReceiving()
{
    while (true)
    {
        bool wasReceived = 
        (msgrcv(qId, messageToPop.getFirstByte(), TMessage::messageSize, 
            indexOfLastElem, MSG_NOERROR | IPC_NOWAIT) >= 0);
        
        if (wasReceived)
            break;
    };

    indexOfLastElem++;
};