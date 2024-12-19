#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <unistd.h>
#include <vector>
#include <thread>

enum Sex
{
    MALE,
    FEMALE
};

int INDEX = 0;

class TCreature
{
private:
    Sex sex;
    int needTimeToWash;
    int personalIndex;

public:
    TCreature(Sex sex);
    int getIndex();
    int getTimeToWash();
    Sex getSex();
    std::string getSignature();
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
    std::string getSignature(int ind);
    int getSize();
};

void waitRandomTime();
void doWashing(std::queue<TCreature> *queue, TWashingRoom *washingRoom);
void addPeoples(std::queue<TCreature> *mans, std::queue<TCreature> *womans);
void logData(
    std::queue<TCreature> *mans,
    std::queue<TCreature> *womans,
    TWashingRoom *washingRoom
);

int main()
{
    srand(time(0));


    std::queue<TCreature> mens, womans;
    TWashingRoom washingRoom(2);
    std::thread t1(doWashing, &mens, &washingRoom);
    std::thread t2(doWashing, &womans, &washingRoom);
    std::thread t3(addPeoples, &mens, &womans);
    std::thread t4(logData, &mens, &womans, &washingRoom);

    t3.join();
    t1.join();
    t2.join();
    t4.join();

    
}

void logData(
    std::queue<TCreature> *mans,
    std::queue<TCreature> *womans,
    TWashingRoom *washingRoom
)
{
    while (true)
    {
        sleep(1);
        
        std::cout << "Мужская очередь: " << mans->size() << " чел.\n";
        if (mans->size() != 0)
            std::cout << "Первый: " << mans->front().getSignature() << "\n\n";

        std::cout << "Женская очередь: " << womans->size() << " чел.\n";
        if (womans->size() != 0)
            std::cout << "Первая: " << womans->front().getSignature() << "\n\n";
        
        std::cout << "Душевые кабинки: \n";
        std::cout << "|";
        for (int i = 0; i < washingRoom->getSize(); ++i)
            std::cout << washingRoom->getSignature(i) << "\t|";
        std::cout << "\n\n\n";
    }   
};

void addPeoples(std::queue<TCreature> *mans, std::queue<TCreature> *womans)
{
    int NUMBER_OF_PEOPLE = 100;

    for (int i = 0; i < NUMBER_OF_PEOPLE; ++i)
    {
        Sex sex;
        if (rand()%2)
            sex = MALE;
        else
            sex = FEMALE;

        TCreature newSmb(sex);
        if (sex == MALE)
            mans->push(newSmb);
        if (sex == FEMALE)
            womans->push(newSmb);
        
        waitRandomTime();
    }
}

std::string TCreature::getSignature()
{
    std::string signature = "";
    if (sex == MALE)
        signature = "m_";
    else
        signature = "w_";
    return signature + std::to_string(personalIndex);
}


void doWashing(std::queue<TCreature> *queue, TWashingRoom *washingRoom)
{
    while (true)
    {
        if (queue->size() == 0)
            continue;

        TCreature washer = queue->front();
        
        // может ли он помыться?
        if (washer.getSex() == MALE && washingRoom->hasWomans())
            continue;
        if (washer.getSex() == FEMALE && washingRoom->hasMens())
            continue;
        if (!washingRoom->hasPlace())
            continue;
        
        std::cout << " I AM " << washer.getSignature() << "\n";
        std::cout << washingRoom->hasMens() << " ; " << washingRoom->hasWomans() << "\n"; 

        washingRoom->add(&washer);
        queue->pop();
        sleep(washer.getTimeToWash() / 1000);
        washingRoom->remove(washer.getIndex());
    }
}

void waitRandomTime()
{
    // новый человек приходит в диапазоне 7-20 сек
    int MIN = 1000;
    int MAX = 3000;
    int timeToSleep = rand() % (MAX - MIN) + MIN;

    sleep(timeToSleep/1000);
};

TCreature::TCreature(Sex sex)
{
    this->sex = sex;
    personalIndex = ++INDEX;
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
        if (showers[i] == nullptr)
            continue;
        if (showers[i]->getIndex() != index)
            continue;
        showers[i] = nullptr;
    }
}

std::string TWashingRoom::getSignature(int ind)
{
    if (showers[ind] == nullptr)
        return "free";
    return showers[ind]->getSignature();
}

int TWashingRoom::getSize()
{
    return showers.size();
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