#ifndef TMESSAGE_H
#define TMESSAGE_H

#include <string>

const int MESSAGE_SIZE = 10;  // 1 Kb

class TMessage
{
public: // constants
    static const int messageSize = MESSAGE_SIZE;

private:
    struct 
    {
        long type;
        char data[messageSize];
    } legacyMessage;
public:
    TMessage();
    ~TMessage();
    char* getFirstByte();

    long getType();
    void setType(long type); 

    std::string getMessageStr();
    char* getMessage();
    void setMessage(char *message);
};
#endif  //TMESSAGE_H


