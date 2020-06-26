#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

//все кучи на минимум

template<class T>
struct node
{
    T key;
    node* child;
    node* next;
    node()
    {
        child=nullptr;
        next=nullptr;
    }
    void clear()
    {
        node *p=this;
        if (p==nullptr) return;
        if (p->child!=nullptr)
        {
            p->child->clear();
        }
        if (p->next!=nullptr)
        p->next->clear();
        delete p;
    }
};

template<class T>
class Binomial_Heap
{
private:
    bool (*f)(const int& x, const int& y);
    node<T> **arr;
    int MAX_SIZE=64;
public:
    Binomial_Heap(bool (*fun)(const T& x, const T& y),int m=64)
    {
        f=fun;
        MAX_SIZE=m;
        arr= new node<T>*[MAX_SIZE];
        for (int i=0; i<MAX_SIZE; i++)
        {
            arr[i]=nullptr;
        }
    }
    node<T>* Create_node(T x)
    {
        node<T> *res= new node<T>();
        res->key=x;
        return res;
    }
    node<T>* Union_tree(node<T>* x, node<T>* y)
    {
        if (x==nullptr) return y;
        if (y==nullptr) return x;
        if (f(x->key , y->key))
        {
            node<T> *tmp=x->child;
            x->child=y;
            y->next=tmp;
            return x;
        }
        node<T> *tmp=y->child;
        y->child=x;
        x->next=tmp;
        return y;
    }
    void merge(Binomial_Heap<T>& x)
    {
        node<T> *tmp= nullptr;
        int num=1;
        for (int i=0;i<MAX_SIZE; i++)
        {
            num=0;
            if (arr[i]!=nullptr) num++;
            if (x.arr[i]!=nullptr) num++;
            if (tmp!=nullptr) num++;
            switch (num)
            {
            case 0:
                break;
            case 1:
                if (arr[i]!=nullptr) break;
                if (x.arr[i]!=nullptr)
                {
                    arr[i]=x.arr[i];
                    x.arr[i]=nullptr;
                    break;
                }
                if (tmp!=nullptr)
                {
                    arr[i]=tmp;
                    tmp=nullptr;
                    break;
                }
            case 2:
                if (arr[i]==nullptr)
                {
                    tmp=Union_tree(tmp,x.arr[i]);
                    x.arr[i]=nullptr;
                    break;
                }
                if (x.arr[i]==nullptr)
                {
                    tmp=Union_tree(tmp,arr[i]);
                    arr[i]=nullptr;
                    break;
                }
                if (tmp==nullptr)
                {
                    tmp=Union_tree(arr[i],x.arr[i]);
                    arr[i]=nullptr;
                    x.arr[i]=nullptr;
                    break;
                }

            case 3:
                tmp=Union_tree(tmp, x.arr[i]);
                x.arr[i]=nullptr;
                break;
            default:
                break;
            }
        }
    }

    void insert(T k)
    {
        node<T> *t=Create_node(k);
        Binomial_Heap<T> tmp(f);
        tmp.arr[0]=t;
        merge(tmp);
    }
    T erase_min()
    {
        T res;
        int flag=0, imin=0;
        for (int i=0; i<MAX_SIZE; i++)
            if (arr[i]!=nullptr)
            {
                res=arr[i]->key;
                imin=i;
                flag=1;
                break;
            }
        if (flag==0)
        {
            printf("heap is empty!\n");
            return -1;
        }
        for (int i=0; i<MAX_SIZE; i++)
            if (arr[i]!=nullptr && f(arr[i]->key , res))
            {
                res=arr[i]->key;
                imin=i;
            }
        if (imin==0)
        {
            delete arr[0];
            arr[0]=nullptr;
            return res;
        }
        Binomial_Heap<T> tmp(f);
        node<T>* s=arr[imin]->child;

        for (int i=imin-1; i>-1; i--)
        {
            tmp.arr[i]=s;
            s=s->next;
        }
        arr[imin]=nullptr;
        merge(tmp);
        return res;
    }
    void print(node<T> *x)
    {
        node<T> *p=x;
        if (p==nullptr) return;
        cout<<p->key<<" ";
        if (p->child!=nullptr)
        {
            print(p->child);
        }

        node<T> *t=p->next;
        print(t);
    }
    void print()
    {
        for (int i=0; i<MAX_SIZE; i++)
        {
            if (arr[i]==nullptr)
            {
                cout<<"\n"<<i<<" tree is empty\n";
            }
            else
            {
                cout<<i<<" tree: ";
                print(arr[i]);
                cout<<endl;
            }
        }
        cout<<"\n\n";
    }
    ~Binomial_Heap()
    {
        for (int i=0; i<MAX_SIZE; i++)
        {
            arr[i]->clear();
        }
        delete[] arr;
    }
};

template<class T, class V>
struct node2
{
    T key;
    V value;
    node2* child;
    node2* next;
    node2()
    {
        child=nullptr;
        next=nullptr;
    }
    void clear()
    {
        node2 *p=this;
        if (p==nullptr) return;
        if (p->child!=nullptr)
        {
            p->child->clear();
        }
        if (p->next!=nullptr)
        p->next->clear();
        delete p;
    }
};

template<class T, class V>
class Binomial_Heap2
{
private:
    bool (*f)(const int& x, const int& y);
    node2<T,V> **arr;
    int MAX_SIZE=64;
public:
    Binomial_Heap2(bool (*fun)(const T& x, const T& y),int m=64)
    {
        f=fun;
        MAX_SIZE=m;
        arr= new node2<T,V>*[MAX_SIZE];
        for (int i=0; i<MAX_SIZE; i++)
        {
            arr[i]=nullptr;
        }
    }
    node2<T,V>* Create_node(T x, V v)
    {
        node2<T,V> *res= new node2<T,V>();
        res->key=x;
        res->value=v;
        return res;
    }
    node2<T,V>* Union_tree(node2<T,V>* x, node2<T,V>* y)
    {
        if (x==nullptr) return y;
        if (y==nullptr) return x;
        if (f(x->key , y->key))
        {
            node2<T,V> *tmp=x->child;
            x->child=y;
            y->next=tmp;
            return x;
        }
        node2<T,V> *tmp=y->child;
        y->child=x;
        x->next=tmp;
        return y;
    }
    void merge(Binomial_Heap2<T,V>& x)
    {
        node2<T,V> *tmp= nullptr;
        int num=1;
        for (int i=0;i<MAX_SIZE; i++)
        {
            num=0;
            if (arr[i]!=nullptr) num++;
            if (x.arr[i]!=nullptr) num++;
            if (tmp!=nullptr) num++;
            switch (num)
            {
            case 0:
                break;
            case 1:
                if (arr[i]!=nullptr) break;
                if (x.arr[i]!=nullptr)
                {
                    arr[i]=x.arr[i];
                    x.arr[i]=nullptr;
                    break;
                }
                if (tmp!=nullptr)
                {
                    arr[i]=tmp;
                    tmp=nullptr;
                    break;
                }
            case 2:
                if (arr[i]==nullptr)
                {
                    tmp=Union_tree(tmp,x.arr[i]);
                    x.arr[i]=nullptr;
                    break;
                }
                if (x.arr[i]==nullptr)
                {
                    tmp=Union_tree(tmp,arr[i]);
                    arr[i]=nullptr;
                    break;
                }
                if (tmp==nullptr)
                {
                    tmp=Union_tree(arr[i],x.arr[i]);
                    arr[i]=nullptr;
                    x.arr[i]=nullptr;
                    break;
                }

            case 3:
                tmp=Union_tree(tmp, x.arr[i]);
                x.arr[i]=nullptr;
                break;
            default:
                break;
            }
        }
    }

    void insert(T k, V v)
    {
        node2<T,V> *t=Create_node(k,v);
        Binomial_Heap2<T,V> tmp(f);
        tmp.arr[0]=t;
        merge(tmp);
    }
    std::pair<T,V> erase_min()
    {
        std::pair<T,V> res;
        int flag=0, imin=0;
        for (int i=0; i<MAX_SIZE; i++)
            if (arr[i]!=nullptr)
            {
                res.first=arr[i]->key;
                imin=i;
                flag=1;
                break;
            }
        if (flag==0)
        {
            printf("heap is empty!\n");
            return {T(),V()};
        }
        for (int i=0; i<MAX_SIZE; i++)
            if (arr[i]!=nullptr && f(arr[i]->key , res.first))
            {
                res.first=arr[i]->key;
                res.second=arr[i]->value;
                imin=i;
            }
        if (imin==0)
        {
            delete arr[0];
            arr[0]=nullptr;
            return res;
        }
        Binomial_Heap2<T,V> tmp(f);
        node2<T,V>* s=arr[imin]->child;

        for (int i=imin-1; i>-1; i--)
        {
            tmp.arr[i]=s;
            s=s->next;
        }
        arr[imin]=nullptr;
        merge(tmp);
        return res;
    }
    void print(node2<T,V> *x)
    {
        node2<T,V> *p=x;
        if (p==nullptr) return;
        cout<<p->key<<": "<<p->value<<" ";
        if (p->child!=nullptr)
        {
            print(p->child);
        }

        node2<T,V> *t=p->next;
        print(t);
    }
    void print()
    {
        for (int i=0; i<MAX_SIZE; i++)
        {
            if (arr[i]==nullptr)
            {
                cout<<"\n"<<i<<" tree is empty\n";
            }
            else
            {
                cout<<i<<" tree: ";
                print(arr[i]);
                cout<<endl;
            }
        }
        cout<<"\n\n";
    }
    ~Binomial_Heap2()
    {
        for (int i=0; i<MAX_SIZE; i++)
        {
            arr[i]->clear();
        }
        delete[] arr;
    }
};

bool cmp(const int& x, const int& y)
{
    return x>y;
}

int main()
{
    srand(time(NULL));
    bool (*f)(const int& x, const int& y)=cmp;
    Binomial_Heap2<int,char> a(f);
    int size=9;
    for (int i= 0; i<size; i++)
    {
        a.insert(rand()%100,'a'+rand()%10);
    }
    Binomial_Heap2<int,char> b(f);
    for (int i= 0; i<size; i++)
    {
        b.insert(rand()%100,'b'+rand()%10);
    }
    //a.print();
    a.merge(b);
    //a.print();
    std::pair<int,int> tek=a.erase_min();
    std::pair<int,int>  next;
    for (int i=1; i<2*size; i++)
    {

        next=a.erase_min();
        if (next.first>tek.first) cout<<"fiasko\n";
        tek=next;
    }
    return 0;
}
