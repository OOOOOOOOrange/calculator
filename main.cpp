#include<stack>
#include<string>
#include<iostream>
#include<vector>
using namespace std;

//获取操作符优先级
int getPri(char opr){
    if(opr=='+'||opr=='-'){
        return 1;
    }else if(opr=='*'||opr=='/'){
        return 2;
    }else if(opr=='('||opr==')'){
        return 0;
    }else{
        return -1;
    }
}

//判断是否为操作符
bool isop(char c){
    if(c=='+'||c=='-'||c=='*'||c=='/'||c=='('||c==')'){
        return true;
    }else{
        return false;
    }
}

//中缀转后缀
vector<string> convert(string mids){
    vector<string> result;
    stack<string> sta;
    string ss="";
    for(int i=0;i<mids.size();i++){
        if(isop(mids[i])){
            //运算符
            //栈空直接入栈或遇到左括号直接入栈
            if(sta.empty()||mids[i]=='('){
                sta.push(mids.substr(i, 1));
            }else if (')' == mids[i]) {
            //遇到右括号弹栈至左括号
                while (sta.top()[0]!= '(') {
                    result.push_back(sta.top());
                    sta.pop();
                }
                sta.pop();
            }else{
            //遇到其他运算符弹栈至空或优先级小于该运算符
                while (!sta.empty()&&getPri(mids[i])<=getPri(sta.top()[0])) {
                    result.push_back(sta.top());
                    sta.pop();
                }
                sta.push(mids.substr(i, 1));
            }
        }else{
            //运算数
            ss+=mids[i];
            i++;
            while (i<mids.size()&&!isop(mids[i])) {
                ss+=mids[i];
                i++;
            }
            result.push_back(ss);
            i--;
            ss="";
        }
    }
    //弹出所有剩余
    while (!sta.empty()){
        result.push_back(sta.top());
        sta.pop();
    }
    return result;
}

//计算结果
float countResult(vector<string> r){
    stack<float> num;
    for(int i=0;i<r.size();i++){
        if(!isop(r[i][0])){
            //运算数入栈
            num.push(atof(r[i].c_str()));
        }else{
            //运算符计算栈顶两个数
            float op2=num.top();
            num.pop();
            float op1=num.top();
            num.pop();
            float op;
            if(r[i]=="+"){
                op=op1+op2;
            }else if(r[i]=="-"){
                op=op1-op2;
            }else if(r[i]=="*"){
                op=op1*op2;
            }else{
                op=op1/op2;
            }
            num.push(op);
        }
    }
    return num.top();
}

int main(){
    string s;
    cout<<"请输入符合规则的计算式：";
    cin>>s;//输入计算式
    vector<string> r=convert(s);//转后缀
    cout<<"计算结果："<<countResult(r)<<endl;//输出结果
}
