#include "iostream"
using namespace std;

struct Task{
    char priority;
    int burst_time;
    int tt_time;
    char taskName[100];
    int total_time=0;
};

struct queues{
    char priority;
    int total_time=0;
    int length = 0;
    Task *p;
    bool executed = false;
};

bool notComplete(queues q[]){
    bool a=false;
    int countInc=0;
        for(int i=0;i<3;i++){
                countInc=0;
            for(int j=0;j<q[i].length;j++){
                if(q[i].p[j].burst_time != 0){
                    a=true;
                }
                else{
                    countInc+=1;
                }
            }
            if(countInc==q[i].length){

                q[i].executed = true;
            }
        }
        return a;
}



void sort_sfj(queues q){
    
    for(int i=1;i<q.length;i++){
        for(int j=0;j<q.length-1;j++){
            if(q.p[j].tt_time<q.p[j+1].tt_time){
                Task temp = q.p[j+1];
                q.p[j+1] = q.p[j];
                q.p[j] = temp;
            }
        }
    }
}

void sort_ps(queues q){
    
    for(int i=1;i<q.length;i++){
        for(int j=0;j<q.length-1;j++){
            if(q.p[j].priority<q.p[j+1].priority){
                Task temp = q.p[j+1];
                q.p[j+1] = q.p[j];
                q.p[j] = temp;
            }
        }
    }
}


void checkCompleteTimer(queues q[]){
    bool a = notComplete(q);
    for(int i=0;i<3;i++){
        if(q[i].executed==false){
            for(int j=0;j<q[i].length;j++){
                if(q[i].p[j].burst_time!=0){
                    q[i].p[j].total_time+=1;
                }
            }
            q[i].total_time+=1;
        }
    }
}

int main(){

    
    queues q[4];
    q[0].priority='Z';
    q[1].priority='Y';
    q[2].priority='X';
    q[3].priority='Z';
    int a=0;
    int b=0;
    int c=0;

    int cpu1Idle=0;
    int cpu2Idle=0;
    int cpu3Idle=0;
    int cpu4Idle=0;

    int no_of_tasks,burst_time_of_task;
    char priority_of_task;
    char taskName[100];
    cin>>a>>b>>c;
    cin>>no_of_tasks;
    
    Task p1[10000];

    for(int i=0;i<no_of_tasks;i++){
        cin>>taskName;
        memcpy(p1[i].taskName, taskName, sizeof(taskName));
        cin>>priority_of_task;
        cin>>burst_time_of_task;
        
        p1[i].priority = priority_of_task;
        p1[i].burst_time = burst_time_of_task;
        p1[i].tt_time = burst_time_of_task;
        for(int j=0;j<4;j++){
            if(q[j].priority==priority_of_task){
                q[j].length++;
            }
        }
    }

    for(int i =0;i<3;i++){
        int len = q[i].length;
        q[i].p = new Task[len];
    }

    int i1=0,i2=0,i3=0;
    for(int i =0;i<3;i++){
        for(int j=0;j<priority_of_task;j++){
            if(q[i].priority==p1[j].priority){
                if(i==0){
                    q[i].p[i1++] = p1[j];

                    }
                else if(i==1){
                    q[i].p[i2++] = p1[j];
                    }
                else{
                    q[i].p[i3++] = p1[j];
                    }
            }
        }
    }

    int timer = 0;
    int l =-1;
    int rr_timer = 4;
    int counter=0;
    int countersjf=0;
    int counterfcfs=0;
    int counterps=0;
    while(notComplete(q)){
        if(timer == 10){
            timer = 0;
        }
        l+=1;
        if(l>=3){
            l=l%3;
        }

        if(q[l].executed == true){
                
            l+=1;
            if(l>=3){
                l=l%3;
            }
            continue;
        }

        if(l==0){
            
            if(rr_timer == 0){
                rr_timer = 4;
            }

            for(int i=0;i<q[l].length;i++){

                if(q[l].p[i].burst_time==0){
                    counter++;
                    a++;c++;
                    continue;
                }
                if(counter == q[l].length){
                    cpu1Idle++;
                    break;
                }

                if(q[l].p[i].burst_time==q[l].p[i].tt_time)
                {
                        if(a>0 && c>0)
                            {a--;c--;}
                        else
                            cpu1Idle++;
                    }
                while(rr_timer>0 && q[l].p[i].burst_time!=0 && timer!=10){
                    
                    q[l].p[i].burst_time--;
                    checkCompleteTimer(q);
                    rr_timer--;
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].burst_time==0 && rr_timer ==0){
                    rr_timer = 4;
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }
                if(q[l].p[i].burst_time==0 && rr_timer > 0){
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }
                if(rr_timer <= 0){
                    rr_timer = 4;
                    if(i == (q[i].length-1)){
                        i=-1;
                    }
                    continue;
                }

            }
        }


        else if(l==1){
            
            sort_sfj(q[l]);
            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].burst_time==0){
                    countersjf++;
                    continue;
                }
                if(countersjf == q[l].length){
                    cpu2Idle++;
                    break;
                }
                if(q[l].p[i].burst_time==q[l].p[i].tt_time)
                    {
                        if(b>0 && c>0)
                            {b--;c--;}
                        else
                            cpu2Idle++;
                    }
                while(q[l].p[i].burst_time!=0 && timer!=10){
                    
                    q[l].p[i].burst_time--;
                    checkCompleteTimer(q);
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].burst_time==0){
                        b++;c++;
                        continue;
                }

            }
        }
         else if(l==2){
            
            sort_sfj(q[l]);
            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].burst_time==0){
                    counterfcfs++;
                    continue;
                }
                if(counterfcfs == q[l].length){
                    cpu3Idle++;
                    break;
                }
                if(q[l].p[i].burst_time==q[l].p[i].tt_time)
                    {
                        if(a>0 && b>0)
                            {a--;b--;}
                        else
                            cpu3Idle++;
                    }
                while(q[l].p[i].burst_time!=0 && timer!=10){
                    
                    q[l].p[i].burst_time--;
                    checkCompleteTimer(q);
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].burst_time==0){
                        a++;b++;
                        continue;
                }

            }
        }
        else if(l==3){
            
            
            sort_ps(q[l]);
            for(int i=0;i<q[l].length;i++){
                if(q[l].p[i].burst_time==0){
                    counterps++;
                    continue;
                }
                if(counterps == q[l].length){
                    cpu4Idle++;
                    break;
                }
                if(q[l].p[i].burst_time==q[l].p[i].tt_time)
                    {
                        if(a>0 && c>0)
                            {a--;c--;}
                        else
                            cpu4Idle++;
                    }
                while(q[l].p[i].burst_time!=0 && timer!=10){
                    
                    q[l].p[i].burst_time--;
                    checkCompleteTimer(q);
                    timer++;

                }
                if(timer == 10){
                    break;
                }
                if(q[l].p[i].burst_time==0){
                        a++;c++;
                        continue;
                }

            }
        }
        cout<<"A: "<<a<<"B: "<<b<<"C: "<<c<<endl<<endl;
        if(counter+1<q[0].length)
            cout<<"Priority queue :"<<q[0].p[counter+1].taskName;
        if(counterps+1<q[3].length)
            cout<<"  "<<q[0].p[counter+1].taskName;
        cout<<endl<<endl;
        cout<<"Priority queue :"<<endl<<endl;

        if(counter<q[0].length)
            cout<<"cpu1:"<<q[0].p[counter].taskName;
        else
            cout<<"cpu1:Idle";
        if(countersjf<q[1].length)
            cout<<"cpu2:"<<q[1].p[countersjf].taskName;
        else
            cout<<"cpu2:Idle";
        if(counterfcfs<q[2].length)
            cout<<"cpu2:"<<q[2].p[counterfcfs].taskName;
        else
            cout<<"cpu2:Idle";
        if(counterps<q[3].length)
            cout<<"cpu3:"<<q[3].p[counterps].taskName;
        else
            cout<<"cpu3:Idle";
        cout<<endl<<endl;
    }


    cout<<"cpu1 Idl Time: "<<cpu1Idle;
    cout<<"cpu2 Idl Time: "<<cpu2Idle;
    cout<<"cpu3 Idl Time: "<<cpu3Idle;
    cout<<"cpu4 Idl Time: "<<cpu4Idle;


return 0;
}