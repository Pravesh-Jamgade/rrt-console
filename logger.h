#ifndef LOGGER_H
#define LOGGER_H

#include<iostream>

using namespace std;

class logger
{
    public:
        logger(bool tap);
        virtual ~logger(){

        }
        void log();
        
        template<typename P, typename ...Param>
        void log(const P &p, const Param& ...param);
        
    protected:

    private:
        bool flag=false;
};

logger::logger(bool flag){
    this->flag = flag;
}

void logger::log(){
    cout<<"";
}

template<typename P, typename ...Param>
void logger::log(const P &p, const Param& ...param){
    if(this->flag){
        cout<<p<<" ";
        logger::log(param...);
    }
}

#endif // LOGGER_H
