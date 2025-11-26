#include<iostream>
#include<mutex>
#include<thread>
#include<atomic>
std::mutex;
class SensorTask{
    virtual void run()=0;
    virtual void callback()=0;
    void stop(){
        is=false;
    }
    SensorTask() : running(&SensorTask::run,this){},ready(false){};
    ~SensorTask(){
        stop();
        if(running.joinable()){
            running.join();
        }
    }
    int key;
    std::atomic<int>*p_in;
    std::atomic<int>*p_out;
    std::atomic<bool>is{true};
    std::thread running;
    bool ready;
};
