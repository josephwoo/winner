#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace std;

bool showAll = false ;
int mineNum = 10 ;

class Every
{
private:
    int item ;
    bool viste ;
public:
    Every(int , bool) ;
    void setItem(int) ;
    int getItem() ;
    void setViste(bool) ;
    bool getViste() ;
};

Every::Every(int i=0 , bool b=false)
{
    this->item = i ;
    this->viste = b ;
}

void Every::setItem(int i=0)
{
    this->item = i ;
}

int Every::getItem()
{
    return this->item ;
}

void Every::setViste(bool b=false)
{
    this->viste = b ;
}

bool Every::getViste()
{
    return this->viste ;
}

class Winner
{
private:
    Every pan[10][10] ;

public :
    Winner()
    {
        reStart() ;
    }

    void dis() ;
    bool select(int , int , int) ;
    void scan(int , int) ;
    void showPart(int ,int) ;
    bool checkWin() ;
    void reStart() ;
};

void Winner::dis()
{
    system("clear") ;
    int i , j;
    if(showAll)
    {
        for(i=0 ; i<10 ; i++)
        {
            if(i==0)
                cout<<10<<' ' ;
            else
                cout<<10-i <<"  " ;

            for(j=0 ; j<10 ; j++)
            {
                switch( this->pan[i][j].getItem() )
                {
                case 'M':
                    cout<<'M' <<' ' ; break ;
                default:
                    if( this->pan[i][j].getItem()=='M'+10 )
                    {
                        cout<<'R' <<' ' ; break ;
                    }
                    else if(this->pan[i][j].getItem()>=10)
                    {
                        cout<<'W' <<' ' ; break ;
                    }
                    else
                    {
                        cout<<this->pan[i][j].getItem() <<' ' ; break ;
                    }
                }
            }
            cout<<endl ;
        }
    }
    else
    {
        for(i=0 ; i<10 ; i++)
        {
            if(i==0)
                cout<<10<<' ' ;
            else
                cout<<10-i <<"  " ;

            for(j=0 ; j<10 ; j++)
            {
                if(this->pan[i][j].getViste())
                {
                    switch( this->pan[i][j].getItem() )
                    {
                    case 0:
                        cout<<"  " ; break ;
                    default:
                        if(this->pan[i][j].getItem()>=10)
                        {
                            cout<<'#' <<' ' ; break ;
                        }
                        else
                        {
                            cout<<this->pan[i][j].getItem() <<' ' ; break ;
                        }
                    }
                }
                else
                    cout<<'@'<<' ' ;
            }
            cout<<endl ;
        }
    }
    cout<< 0 <<"  " ;
    for(i=1 ; i<=10 ; i++)
        cout<<i <<' ' ;
    cout<<endl ;
}

bool Winner::select(int x , int y , int op)
{
    switch(op)
    {
    case 1:
        this->pan[x][y].setViste(true) ;
        if( this->pan[x][y].getItem()=='M' )
        {
            showAll = true ;
            return false ;
        }
        return true ;
    case 2:

        if( (this->pan[x][y].getItem()<10 || this->pan[x][y].getItem()=='M') && !this->pan[x][y].getViste() )
        {
            this->pan[x][y].setViste(true) ;
            this->pan[x][y].setItem( this->pan[x][y].getItem()+10 ) ;
            mineNum -- ;
        }
        return true ;
    default:
        this->pan[x][y].setViste(false) ;
        if( this->pan[x][y].getItem()=='M'+10 || this->pan[x][y].getItem()>=10 )
        {
            this->pan[x][y].setItem( this->pan[x][y].getItem()-10 ) ;
            mineNum ++ ;
        }
        return true ;
    }
}

void Winner::scan(int x , int y)
{
    int i , j , cnt=0 ;
    if(x>0 && x<9 && y>0 && y<9)
    {
        for(i=x-1 ; i<=x+1 ; i++)
        {
            for(j=y-1 ; j<=y+1 ; j++)
            {
                if( this->pan[i][j].getItem()=='M' )
                    cnt ++ ;
            }
        }
    }
    else if(x==0 && y==0)
    {
        if( this->pan[x][y+1].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x+1][y].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x+1][y+1].getItem()=='M' )
            cnt ++ ;
    }
    else if(x==9 && y==0)
    {
        if( this->pan[x][y+1].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x-1][y].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x-1][y+1].getItem()=='M' )
            cnt ++ ;
    }
    else if(x==0 && y==9)
    {
        if( this->pan[x][y-1].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x+1][y].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x+1][y-1].getItem()=='M' )
            cnt ++ ;
    }
    else if(x==9 && y==9)
    {
        if( this->pan[x][y-1].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x-1][y].getItem()=='M' )
            cnt ++ ;
        if( this->pan[x-1][y-1].getItem()=='M' )
            cnt ++ ;
    }
    else if( x==0 && y>0 && y<9)
    {
        for(i=y-1 ; i<=y+1 ; i++)
        {
            if( this->pan[x][i].getItem()=='M' )
                cnt ++ ;
            if( this->pan[x+1][i].getItem()=='M' )
                cnt ++ ;
        }
    }
    else if( x==9 && y>0 && y<9)
    {
        for(i=y-1 ; i<=y+1 ; i++)
        {
            if( this->pan[x][i].getItem()=='M' )
                cnt ++ ;
            if( this->pan[x-1][i].getItem()=='M' )
                cnt ++ ;
        }
    }
    else if(y==0 && x>0 && x<9)
    {
        for(i=x-1 ; i<=x+1 ; i++)
        {
            if( this->pan[i][y].getItem()=='M' )
                cnt ++ ;
            if( this->pan[i][y+1].getItem()=='M' )
                cnt ++ ;
        }
    }
    else //if(y==9 && x>0 && x<9)
    {
        for(i=x-1 ; i<=x+1 ; i++)
        {
            if( this->pan[i][y].getItem()=='M' )
                cnt ++ ;
            if( this->pan[i][y-1].getItem()=='M' )
                cnt ++ ;
        }
    }

    this->pan[x][y].setItem(cnt) ;
}

void Winner::showPart(int x , int y )
{
    srand( (unsigned)time( NULL ) );
    int xLeft=rand()%5 , xRight=rand()%5 ;
    int yLeft=rand()%5 , yRight=rand()%5 ;

    while( x<xLeft )
        xLeft = rand()%5 ;
    while( x+xRight>9 )
        xRight = rand()%5 ;
    while( y<yLeft )
        yLeft = rand()%5 ;
    while( y+yRight>9 )
        yRight = rand()%5 ;

    int xTmp = rand()%5 , yTmp ;
    for(int i=x-xLeft ; i<x+ (xRight<xTmp?xRight:xTmp) ; i++ )
    {
        yTmp = rand()%5 ;
        for(int j=y-yLeft ; j<y+ (yRight<yTmp?yRight:yTmp) ; j++)
        {
            if( this->pan[i][j].getItem()!='M' )
                this->pan[i][j].setViste(true) ;
        }
    }
}

bool Winner::checkWin()
{
    int i , j , cnt = 0 ;
    for(i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(this->pan[i][j].getItem()=='M'+10)
                cnt ++ ;
        }
    }
    if(cnt==10)
        return true ;
    else
        return false ;
}

void Winner::reStart()
{
    int i , j , x , y ;

    for( i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            this->pan[i][j].setViste(false) ;
            this->pan[i][j].setItem(0) ;
        }
    }

    srand( (unsigned)time( NULL ) );
    for(i=0 ; i<10 ; )
    {
        x = rand()%10 ;  y = rand()%10 ;
        if(this->pan[x][y].getItem()!='M')
        {
            this->pan[x][y].setItem('M') ;
            i ++ ;
        }
    }

    for( i=0 ; i<10 ; i++)
    {
        for(j=0 ; j<10 ; j++)
        {
            if(this->pan[i][j].getItem()!='M')
                scan(i , j) ;
        }
    }

    dis() ;
}

int main()
{
    cout<<"NOTICE : 功能4.标记？ 没有实现" << endl ;
    int judge(int , Winner , char , int ) ;
    int judge(int , Winner , int , int ) ;


    Winner game ;
    int x , y , option ;
    bool flag = true;

    while(flag)
    {
        cout<<"剩余地雷数: " <<mineNum <<endl ;
        if( mineNum<=0)
        {
            if(mineNum==0&&game.checkWin())
            {
                cout<<"Congratulations ! You win !" <<endl ;

                cout<<"退出: 0    再来一局: 任意非0数字 :" ;
                int rew = 0 ;
                cin>>rew ;
                if(rew)
                {
                    showAll = false ;
                    game.reStart() ;
                    flag = true ;
                    continue ;
                }
                else
                    break ;
            }
            else
                cout<<"Still have mines !"<<endl ;
        }

        cout<<"请输入横坐标X:" ;
        cin>> x ;
        x = judge(x , game , 'X' , x) ;
        cout<<"请输入纵坐标Y:" ;
        cin>> y ;
        y = judge(y , game , 'Y' , x) ;
        cout<<"选项: 1.单击打开 2.设置红旗(代表符号为#) 3.取消红旗 4.标记？ : " ;
        cin>>option ;
        option = judge(x , game , option , y) ;

        if(option==4)
        {
            game.dis() ;
            continue ;
        }

        --x ;
        flag =game.select(10-y , x , option) ;
        if(!flag)
        {
            game.dis() ;
            cout<<"Game Over !" << endl ;

            cout<<"退出: 0:   再来一局: 任意非0数字 :" ;
            int re = 0 ;
            cin>>re ;
            if(re)
            {
                showAll = false ;
                game.reStart() ;
                flag = true ;
                continue ;
            }
            else
                break ;
        }
        if( option==1 )
            game.showPart(10-y , x) ;

        game.dis() ;
    }

    return 0;
}

int judge(int i , Winner g , char c , int x)
{
    if( i>10 || x<0 )
    {
        g.dis() ;
        cout<<"now :X = " << x <<endl ;
        cout<<c <<" = "<< i <<" is wrong !" <<endl ;
        cout<<"请输入有效的坐标"<<c<<":" ;
        cin>> i ;
        if(c=='X')
            x = i ;
        return judge(i , g , c , x) ;
    }
    else
        return i ;
}

int judge(int x , Winner g , int op , int y)
{
    if( op>4 || op<0 )
    {
        g.dis() ;
        cout<<"now :X = " << x <<" & Y = " <<y <<endl ;
        cout<<"Not have "<< op <<" option !" <<endl ;
        cout<<"选项: 1.单击打开 2.设置红旗(代表符号为#) 3.取消红旗 4.标记？ : " ;
        cin>> op ;

        return judge(x , g , op , y) ;
    }
    else
        return op ;
}
