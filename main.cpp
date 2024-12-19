#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <queue>
#include <unistd.h>
#include <vector>
#include <thread>
#include <semaphore>

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
std::binary_semaphore mensSemaphore(1);
std::binary_semaphore womansSemaphore(1);
std::vector <std::binary_semaphore*> showersSemaphores;

class TWashingRoom
{
private:
    std::vector <TCreature*> showers;
public:
    TWashingRoom(int size);
    bool asbolutelyFree();
    bool hasMens();
    bool hasWomans();
    bool hasPlace();
    void add(TCreature *creature);
    void remove(int index);
    std::string getSignature(int ind);
    bool isFree(int index);
    int getSize();
};

void waitRandomTime();
void doWashing(int indexOfShower, std::queue<TCreature> *mans, std::queue<TCreature> *womans, TWashingRoom *washingRoom);
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

    std::vector <std::thread> threads;

    for (int i = 0; i < washingRoom.getSize(); ++i)
    {
        threads.push_back(std::thread(doWashing, i, &mens, &womans, &washingRoom));
        showersSemaphores.push_back(new std::binary_semaphore(1));
    }

    std::thread t3(addPeoples, &mens, &womans);
    std::thread t4(logData, &mens, &womans, &washingRoom);
    t3.join();
    t4.join();
    for (int i = 0; i < threads.size(); ++i)
        threads[i].join();

    
}

void doWashing(int indexOfShower, std::queue<TCreature> *mans, std::queue<TCreature> *womans, TWashingRoom *washingRoom)
{
    while (true)
    {
        // душевая занята
        showersSemaphores[indexOfShower]->acquire();
        if (!washingRoom->isFree(indexOfShower))
        {
            showersSemaphores[indexOfShower]->release();
            continue;
        }
        // смотрим, кто сейчас в ванной
        std::queue <TCreature> *whoCanEnterQueue; 
        std::binary_semaphore *semaphoreToBlock;


        if (washingRoom->asbolutelyFree())
        {
            // в кабинки может зайти кто угодно
            mensSemaphore.acquire();
            womansSemaphore.acquire();

            if (mans->size() != 0)
            {
                whoCanEnterQueue = mans;
                semaphoreToBlock = &mensSemaphore;
            }
            else
            if (womans->size() != 0)
            {
                whoCanEnterQueue = womans;
                semaphoreToBlock = &womansSemaphore;
            }
            else
            {
                mensSemaphore.release();
                womansSemaphore.release();     
                showersSemaphores[indexOfShower]->release();
                continue;          
            }

            mensSemaphore.release();
            womansSemaphore.release();

        }
        else
        {
            if (washingRoom->hasMens())
            {
                whoCanEnterQueue = mans;
                semaphoreToBlock = &mensSemaphore;
            }
            if (washingRoom->hasWomans())
            {
                whoCanEnterQueue = womans;
                semaphoreToBlock = &womansSemaphore;
            }
        }
        
        semaphoreToBlock->acquire();

        if (whoCanEnterQueue->size() == 0)
        {
            semaphoreToBlock->release();
            showersSemaphores[indexOfShower]->release();
            continue;
        }
        // моем чудика
        TCreature whoCanEnter = whoCanEnterQueue->front();
        whoCanEnterQueue->pop();
        semaphoreToBlock->release();
        
        washingRoom->add(&whoCanEnter);
        showersSemaphores[indexOfShower]->release();

        sleep(whoCanEnter.getTimeToWash() / 1000);
        showersSemaphores[indexOfShower]->acquire();
        washingRoom->remove(whoCanEnter.getIndex());
        showersSemaphores[indexOfShower]->release();
    }
};


void logData(
    std::queue<TCreature> *mans,
    std::queue<TCreature> *womans,
    TWashingRoom *washingRoom
)
{
    while (true)
    {
        sleep(1);
        
        mensSemaphore.acquire();
        womansSemaphore.acquire();

        std::cout << "Мужская очередь: " << mans->size() << " чел.\n";
        if (mans->size() != 0)
            std::cout << "Первый: " << mans->front().getSignature() << "\n\n";

        std::cout << "Женская очередь: " << womans->size() << " чел.\n";
        if (womans->size() != 0)
            std::cout << "Первая: " << womans->front().getSignature() << "\n\n";
        
        mensSemaphore.release();
        womansSemaphore.release();

        std::cout << "Душевые кабинки: \n";
        std::cout << "|";
        for (int i = 0; i < washingRoom->getSize(); ++i)
        {
            showersSemaphores[i]->acquire();
            std::cout << washingRoom->getSignature(i) << "\t|";
            showersSemaphores[i]->release();
        }
        std::cout << "\n\n\n";
    }   
};

bool TWashingRoom::asbolutelyFree()
{
    for (int i = 0; i < showers.size(); ++i)
        if (showers[i] != nullptr)
            return false;
    return true;
}

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

bool TWashingRoom::isFree(int index)
{
    return (showers[index] == nullptr);
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

void waitRandomTime()
{
    // новый человек приходит в диапазоне MIN..MAX секунд
    int MIN = 2000;
    int MAX = 5000;
    int timeToSleep = rand() % (MAX - MIN) + MIN;

    sleep(timeToSleep/1000);
};

TCreature::TCreature(Sex sex)
{
    this->sex = sex;
    personalIndex = ++INDEX;
    // моются чудики от MIN секунд до MAX
    
    int MIN = 6000;
    int MAX = 10000;
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