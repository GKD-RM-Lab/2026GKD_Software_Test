#include"all.hpp"
void Taskmanager::add(){
    int tem_key;
    std::string kind;
    cin>>tem_key>>kind;
    SensorTask*tem_task=nullptr;
    if(kind=="TaskFilter")tem_task=new TaskFilter();
    else if(kind=="TaskGain")tem_task=new TaskGain();
    else tem_task=new TaskDelayBuffer();
    tem_task->key=tem_key;
    if(tasklist.empty()){
        tasklist.push_back(tem_task);
        tasklist[0]->p_out=&out;
        b_n.push_back(std::make_unique<std::atomic<int>>(0));
        auto it=b_n.end()-1;
        tasklist[0]->p_in=it->get();
    }
    else{
        tasklist.push_back(tem_task);
        b_n.push_back(std::make_unique<std::atomic<int>>(0));
        auto it=b_n.end()-1;
        tasklist.back()->p_in=it->get();
        it--;
        tasklist.back()->p_out=it->get();
    }
    tasklist.back()->ready=true;
}
void Taskmanager::pop(){
    SensorTask*tem_task=tasklist.back();
    tem_task->stop();
    if(tem_task->running.joinable()){
        tem_task->running.join();
    }
    delete tem_task;
    tasklist.pop_back();
    b_n.pop_back();
    cout<<"已经删除最后一个任务"<<endl;
}
void Taskmanager::callbackuse() {
    int tem_key, msg;
    std::cin >> tem_key >> msg;
    vector<SensorTask*>::iterator it;
    for (it = tasklist.begin(); it != tasklist.end(); it++) {
        if ((*it)->key == tem_key)break;
    }
    (*it)->callback(msg);
}
