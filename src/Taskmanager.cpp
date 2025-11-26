#include"all.hpp"

class Taskmanager{
public:
    void add(){
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
    std::atomic<int>out{0};
    vector<std::unique_ptr<std::atomic<int>>>b_n;
    vector<SensorTask*>tasklist;
};