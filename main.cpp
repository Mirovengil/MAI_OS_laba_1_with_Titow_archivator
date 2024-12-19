#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <unistd.h>
#include <vector>
enum Sex
{
    MALE,
    FEMALE
};

class TCreature
{
private:
    Sex sex;
    int needTimeToWash;
    int personalIndex;

    static int index;
public:
    TCreature(Sex sex);
    static void setIndex(int value);
    int getIndex();
    int getTimeToWash();
    Sex getSex();
};

class TWashingRoom
{
private:
    std::vector <TCreature*> showers;
public:
    TWashingRoom(int size);
    bool hasMens();
    bool hasWomans();
    bool hasPlace();
    void add(TCreature *creature);
    void remove(int index);
};

void waitRandomTime();
void doWashing(std::queue<TCreature> &queue, TWashingRoom *washingRoom);

int main()
{
    TCreature::setIndex(0);
    srand(time(0));

    int NUMBER_OF_PEOPLE = 100;

    std::queue<TCreature> mens, womans;
    TWashingRoom washingRoom(2);

    for (int i = 0; i < NUMBER_OF_PEOPLE; ++i)
    {
        Sex sex;
        if (rand()%2)
            sex = MALE;
        else
            sex = FEMALE;

        TCreature newSmb(sex);
        if (sex == MALE)
            mens.push(newSmb);
        if (sex == FEMALE)
            womans.push(newSmb);
    }
}

void doWashing(std::queue<TCreature> &queue, TWashingRoom *washingRoom)
{
    while (!queue.empty())
    {
        TCreature washer = queue.front();
        
        // может ли он помыться?
        if (washer.getSex() == MALE && washingRoom->hasWomans())
            continue;
        if (washer.getSex() == FEMALE && washingRoom->hasMens())
            continue;
        if (!washingRoom->hasPlace())
            continue;
        
        washingRoom->add(&washer);
        sleep(washer.getTimeToWash() / 1000);
        washingRoom->remove(washer.getIndex());
        queue.pop();
    }
}

void waitRandomTime()
{
    // новый человек приходит в диапазоне 7-20 сек
    int MIN = 7000;
    int MAX = 20000;
    int timeToSleep = rand() % (MAX - MIN) + MIN;

    sleep(timeToSleep/1000);
};

void TCreature::setIndex(int value)
{
    index = value;
}

TCreature::TCreature(Sex sex)
{
    this->sex = sex;
    personalIndex = ++index;
    // моются чудики от 3 секунд до 10
    
    int MIN = 3000;
    int MAX = 1000;
    needTimeToWash = rand() % (MAX - MIN) + MIN; 
}

TWashingRoom::TWashingRoom(int size)
{
    showers.resize(size);
    for (int i = 0; i < size; ++i)
        showers[i] = nullptr;
}

bool TWashingRoom::hasMens()
{
    for (int i = 0; i < showers.size(); ++i)
    {
        if (showers[i] == nullptr)
            continue;
        if (showers[i]->getSex() == MALE)
            return true;
    }
    return false;
}

bool TWashingRoom::hasWomans()
{
    for (int i = 0; i < showers.size(); ++i)
    {
        if (showers[i] == nullptr)
            continue;
        if (showers[i]->getSex() == FEMALE)
            return true;
    }
    return false;
}

bool TWashingRoom::hasPlace()
{
    for (int i = 0; i < showers.size(); ++i)
    {
        if (showers[i] == nullptr)
            return true;
    }
    return false;
}


void TWashingRoom::add(TCreature *creature)
{
    for (int i = 0; i < showers.size(); ++i)
    {
        if (showers[i] != nullptr)
            continue;
        
        showers[i] = creature;
        break;
    }
}

void TWashingRoom::remove(int index)
{
    for (int i = 0; i < showers.size(); ++i)
    {
        if (showers[i]->getIndex() != index)
            continue;
        showers[i] = nullptr;
    }
}


int TCreature::getIndex()
{
    return personalIndex;
}

int TCreature::getTimeToWash()
{
    return needTimeToWash;
}

Sex TCreature::getSex()
{
    return sex;
}