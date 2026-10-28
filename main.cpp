#include <QApplication>
#include<QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QString>
#include <fstream>
#include<iostream>
#include <string>
using namespace std;

bool logging(string filename,string account,string password){
    ifstream fin(filename);
    string in_n,in_p;
    bool flage=false;
    while(fin>>in_n>>in_p){
        if(in_n==account && in_p ==password){
            cout<<in_n<<in_p<<endl;
            flage=true;
            break;
        }
    }
    return flage;
}

bool Creating(string filename,string account,string password){
    ifstream fin(filename);
    string in_n,in_p;
    bool flag = true;
    //判断是否有重复账号
    while(fin >> in_n >> in_p){
        if(in_n == account){
            flag = false;
            break; //找到重复直接跳出，不用继续读
        }
        }
    fin.close();

    //没有重复，追加写入
    if(flag){
        ofstream fout(filename, ios::app);
            if(fout.is_open()){
            fout << account << " " << password << endl;
        }
        fout.close();
    }
    return flag;
}
int main(int argc, char *argv[]){
    //文件管理初始化Filename
    string filename="/Users/hujiaming/Desktop/桌面文件/C++Program/demo2/data/data.txt";
    fstream fs;
    fs.open(filename,ios::in);
    if(!fs.is_open()){
        //若是不存在文件则新建文件
        fs.open(filename,ios::out);
    }
    fs.close();

    QApplication a(argc, argv);//创建界面循环对象
    //创建界面对象
    QWidget w;
    w.setWindowTitle("System of logging");
    w.resize(500,240);
    QLabel *lab = new QLabel("账号：", &w);//账号文本comment
    QLineEdit *ql=new QLineEdit(&w);//账号输入框
    ql->setFixedWidth(180);
    QLabel *password=new QLabel("password:",&w);//密码文本
    QLineEdit *qe=new QLineEdit(&w);//密码输入框
    qe->setFixedWidth(180);
    qe->setEchoMode(QLineEdit::Password);//密码mode设置

    //创建【查看】窗口
    QWidget *view =new QWidget();
    view->resize(300,400);

    //button生成与设置
    QPushButton *b1=new QPushButton("登陆",&w);
    b1->setFixedWidth(100);
    QPushButton *b2=new QPushButton("注册",&w);
    b2->setFixedWidth(100);
    QPushButton *b3=new QPushButton("查看",&w);
    QHBoxLayout *b_h=new QHBoxLayout;
    b_h->addWidget(b1);
    b_h->addWidget(b2);
    b_h->addWidget(b3);
    b_h->addStretch();//弹性布局
    b_h->setSpacing(8);//间距设置

    //设置布局格式为横向布局
    QHBoxLayout *u_h=new QHBoxLayout;
    QHBoxLayout *p_h=new QHBoxLayout;
    u_h->addWidget(lab);//设置h横向布局的元素
    u_h->addWidget(ql);
    u_h->addStretch();//控制拉伸
    u_h->setSpacing(8);//设置横向布局的元素间距

    p_h->addWidget(password);
    p_h->addWidget(qe);
    p_h->addStretch();//控制拉伸
    p_h->setSpacing(8);
    
    //纵向左布局
    QVBoxLayout *v1=new QVBoxLayout();
    v1->addLayout(u_h);
    v1->addLayout(p_h);
    v1->addLayout(b_h);
    v1->setSpacing(1);

    //纵向右布局
    QVBoxLayout *v2=new QVBoxLayout();
    QFrame *color=new QFrame(&w);
    //创建内部布局
    QVBoxLayout *v_color=new QVBoxLayout(color);
    //创建文本Label
    QLabel *status=new QLabel("",color);
    //添加到内部布局
    v_color->addWidget(status);
    //设置平铺
    status->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //设置居中
    status->setAlignment(Qt::AlignCenter);
    color->setLayout(v_color);
    color->setFixedSize(100,100);
    color->setStyleSheet("background:white;");
    v2->addWidget(color);

    //横向布局
    QHBoxLayout *H_main=new QHBoxLayout();
    H_main->addLayout(v1);
    H_main->addLayout(v2);
    H_main->addStretch();
    H_main->addSpacing(1);

    //布局添加纵向布局
    v1->setContentsMargins(30,30,30,30);
    w.setLayout(H_main);
    w.show();

    //创建状态对象
    QLabel *success=new QLabel("登陆",&w);
    QLabel *fail=new QLabel("注册",&w);
    success->hide();
    fail->hide();


    //登陆按钮的配置如下
    QObject::connect(b1,&QPushButton::clicked,[=](){
        QString input1=ql->text();
        QString input2=qe->text();
        string acc = input1.toStdString();
        string pwd = input2.toStdString();
        //登陆逻辑如下
        bool flag=logging(filename,acc,pwd);//返回是否登陆成功
        if(flag){
            status->setText("success");
            color->setStyleSheet("background:green;");
        }else{
            status->setText("fail");
            color->setStyleSheet("background:red;");
        }
    });

    //注册按钮的配置如下
    QObject::connect(b2,&QPushButton::clicked,[=](){
        QString input1=ql->text();
        QString input2=qe->text();
        string acc = input1.toStdString();
        string pwd = input2.toStdString();
        bool flag=Creating(filename,acc,pwd);//返回是否注册成功
        if(flag){
            status->setText("success");
            color->setStyleSheet("background:green;");
        }else{
            status->setText("fail");
            color->setStyleSheet("background:red;");
        }
    });

    //查看按钮的显示view
    QObject::connect(b3,&QPushButton::clicked,[=](){
        ifstream fin(filename);
        string f_n,f_p;
        QVBoxLayout *V_view=new QVBoxLayout();
        while(fin>>f_n>>f_p){
            //释放内存,再次点击删除上一份的date
            if(view->layout()){
                cout<<"date has been deleted"<<endl;
                delete view->layout();
            }
            //设置H的排版
            QHBoxLayout *H_view=new QHBoxLayout();
            //设置account and password 的string转换Qstring
            QString f_t_n = QString::fromStdString(f_n);
            QString f_t_p = QString::fromStdString(f_p);
            //添加控件Label
            QLabel *i_n=new QLabel(f_t_n,view);
            QLabel *i_p=new QLabel(f_t_p,view);
            //横排布局添加label
            H_view->addWidget(i_n);
            H_view->addWidget(i_p);
            H_view->addStretch();
            H_view->setSpacing(8);
            //竖排布局添加HLayout
            V_view->addLayout(H_view);
            V_view->addStretch();
            V_view->setSpacing(5);
        }
        view->setLayout(V_view);
        view->show();
    });
    return a.exec();//循环
}