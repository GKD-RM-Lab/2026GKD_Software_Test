#include"all.hpp"

void TaskFilter::run(){
    while(is){
        if(*p_in!=0){
            std::lock_guard<mutex> lock(mtx);
            *p_out=*p_in+1;
            *p_in=0;
            cout<<"write filter "<<key<<": "<<*p_out<<endl;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
void TaskFilter::callback(int msg){
    *p_in=msg;
}
TaskFilter::~TaskFilter(){
    stop();
    if(running.joinable()){
        running.join();
    }
    if(p_in!=nullptr&&p_out!=nullptr){
        p_in=nullptr;
        p_out=nullptr;
    }
}



void TaskGain::run(){
    while(is){
        if(*p_in!=0){
            std::lock_guard<mutex> lock(mtx);
            *p_out=*p_in*k;
            *p_in=0;
            cout<<"wriet gain "<<key<<": "<<*p_out<<endl;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
void TaskGain::callback(int msg){
    k=msg;
    *p_in=1;
}
TaskGain::~TaskGain(){
    stop();
    if(running.joinable()){
        running.join();
    }
    if(p_in!=nullptr&&p_out!=nullptr){
        p_in=nullptr;
        p_out=nullptr;
    }
}
void TaskDelayBuffer::run(){
    while(is){
        if(*p_in!=0){
            std::lock_guard<mutex> lock(mtx);
            int t=*p_in;
            *p_in=0;
            *p_out=t;
            cout<<"write delay "<<key<<": "<<*p_out<<endl;
            std::this_thread::sleep_for(std::chrono::microseconds(1));
            *p_out=t+1;
            cout<<"write delay "<<key<<": "<<*p_out<<endl;
        }
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}
void TaskDelayBuffer::callback(int msg){
    *p_in=msg;
}
TaskDelayBuffer::~TaskDelayBuffer(){
    stop();
    if(running.joinable()){
        running.join();
    }
    if(p_in!=nullptr&&p_out!=nullptr){
        p_in=nullptr;
        p_out=nullptr;
    }
}

