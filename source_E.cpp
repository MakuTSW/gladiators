//Piotr Makosiej
#include <iostream>

using namespace std;
class Gladiator
{
    friend class Caesar;
    friend class Squad;
protected:
    string ID;
    unsigned int MAX_HEALTH;
     unsigned int HEALTH=MAX_HEALTH;
    unsigned int BASE_DAMAGE;
    unsigned int BASE_RAPIDITY;
    unsigned int BASE_DEFENCE;

public:
    Gladiator *next=NULL;
    virtual unsigned int getRemainingHealth()=0;
    /*{
        return ((double)HEALTH / MAX_HEALTH) * 100;
    }*/
    virtual unsigned int getDamage()=0;
    /*{
        return BASE_DAMAGE;
    }*/
    virtual void takeDamage(unsigned int damage)=0;
    virtual unsigned int getRapidity()=0;
    /*{
        return BASE_RAPIDITY;
    }*/
    virtual void cure()=0;
    /*{
        HEALTH=MAX_HEALTH;
    }*/
    virtual void applyWinnerReward()=0;
    /*{
        BASE_DAMAGE+=2;
        BASE_RAPIDITY+=2;
        //cure();
    }*/
    virtual void printParams()=0;
    /*{

        cout << ID << ":" << getRemainingHealth() << ":" << getDamage() << ":" << getRapidity() << endl;
    }*/

private:
    virtual void die()=0;
    /*{
        HEALTH=0;
    }*/

};
class Human: virtual public Gladiator
{
public:
    Human(string name)
    {
        ID=name;
        HEALTH=200;
        MAX_HEALTH=200;
        BASE_DAMAGE=30;
        BASE_RAPIDITY=10;
        BASE_DEFENCE=10;
    }
    Human(){};
    void takeDamage(unsigned int damage)
    {
        if(damage>BASE_DEFENCE+BASE_RAPIDITY)
        damage=damage-BASE_DEFENCE-BASE_RAPIDITY;
        else damage=0;
        if(damage>0)
            if(HEALTH>damage)
                HEALTH=HEALTH-damage;
            else HEALTH=0;
    }
    unsigned int getDamage()
    {
        return BASE_DAMAGE;
    }
    void applyWinnerReward()
    {
        BASE_DAMAGE+=2;
        BASE_RAPIDITY+=2;
        //cure();
    }
    unsigned int getRemainingHealth()
    {
        return ((double)HEALTH / MAX_HEALTH) * 100;
    }
    void cure()
    {
        HEALTH=MAX_HEALTH;
    }
    void printParams()
    {

        cout << ID << ":" << getRemainingHealth() << ":" << getDamage() << ":" << getRapidity() << endl;
    }
    unsigned int getRapidity()
    {
        return BASE_RAPIDITY;
    }
private:

    void die()
    {
        HEALTH=0;
    }
};
class Beast: virtual public Gladiator
{
public:
    Beast(string species)
    {
        ID=species;
        HEALTH=150;
        MAX_HEALTH=150;
        BASE_DAMAGE=40;
        BASE_RAPIDITY=20;

    }
    Beast(){};
    void takeDamage(unsigned int damage)
    {
        if(damage>BASE_RAPIDITY/2)
        damage=damage-BASE_RAPIDITY/2;
        else damage=0;
        if(damage>0)
        {
            if(HEALTH>damage)
                HEALTH=HEALTH-damage;
            else HEALTH=0;
        }
    }
    unsigned int getDamage()
    {
        if(getRemainingHealth()>=25)
        return BASE_DAMAGE;
        else
            return BASE_DAMAGE*2;
    }
    void applyWinnerReward()
    {
        BASE_DAMAGE+=2;
        BASE_RAPIDITY+=2;
        //cure();
    }
    unsigned int getRemainingHealth()
    {
        return ((double)HEALTH / MAX_HEALTH) * 100;
    }
    void cure()
    {
        HEALTH=MAX_HEALTH;
    }
    void printParams()
    {

        cout << ID << ":" << getRemainingHealth() << ":" << getDamage() << ":" << getRapidity() << endl;
    }
    unsigned int getRapidity()
    {
        return BASE_RAPIDITY;
    }
private:

    void die()
    {
        HEALTH=0;
    }
};
class Berserker: virtual public Beast, virtual public Human
{
public:
    Berserker(string name)
    {
        ID=name;
        HEALTH=200;
        MAX_HEALTH=200;
        BASE_DAMAGE=35;
        BASE_RAPIDITY=5;
        BASE_DEFENCE=15;
    }
    void takeDamage(unsigned int damage)
    {
         if(getRemainingHealth()>=25)
            if(damage>BASE_DEFENCE+BASE_RAPIDITY)
            damage=damage-BASE_DEFENCE-BASE_RAPIDITY;
            else damage=0;

         if(damage>0)
        if(HEALTH>damage)
                HEALTH=HEALTH-damage;
            else HEALTH=0;
    }
    unsigned int getDamage()
    {
        if(getRemainingHealth()>=25)
        return BASE_DAMAGE;
        else
            return BASE_DAMAGE*2;
    }
    void applyWinnerReward()
    {
        BASE_DAMAGE+=2;
        BASE_RAPIDITY+=2;
        //cure();
    }
    unsigned int getRemainingHealth()
    {
        return ((double)HEALTH / MAX_HEALTH) * 100;
    }
    void cure()
    {
        HEALTH=MAX_HEALTH;
    }
    void printParams()
    {

        cout << ID << ":" << getRemainingHealth() << ":" << getDamage() << ":" << getRapidity() << endl;
    }
    unsigned int getRapidity()
    {
        return BASE_RAPIDITY;
    }
private:

    void die()
    {
        HEALTH=0;
    }

};
class Squad: virtual public Gladiator
{
public:
    Squad()
    {
        ID="Squad";
        MAX_HEALTH=100;
        BASE_DAMAGE=0;
        BASE_RAPIDITY=100;

    }
    unsigned int amount=0;
    Gladiator *first=NULL;

    void addGladiator(Gladiator* gladiator)
    {
        if(gladiator->getRemainingHealth()==0)
            return;
        Gladiator *x=first;
        while(x!=NULL)
        {
            if(gladiator==x)
                return;
            x=x->next;
        }
        BASE_DAMAGE+=gladiator->getDamage();
        if(BASE_RAPIDITY>gladiator->getRapidity())
            BASE_RAPIDITY=gladiator->getRapidity();
        gladiator->next=first;
        first=gladiator;
        amount++;
    }
    unsigned int getDamage()
    {
        Gladiator *x=first;
        unsigned int damage=0;
        while(x!=NULL)
        {
            damage+=x->getDamage();
            x=x->next;
        }
        return damage;
    }
    void takeDamage(unsigned int damage)
    {
        //if(amount==0)
          //  return;
        damage=damage/amount;
        Gladiator *x=first;
        Gladiator *prev=x;
        while(x!=NULL)
        {
            x->takeDamage(damage);
            if(x->getRemainingHealth()==0)
            {
                amount--;
                if(x==first)
                {
                    first=first->next;
                }
                else
                {
                    prev->next=x->next;
                }
            }
            prev=x;
            x=x->next;
        }
    }
    void applyWinnerReward()
    {
        Gladiator *x=first;
        while(x!=NULL)
        {
            x->applyWinnerReward();
            x=x->next;
        }
    }
    unsigned int getRemainingHealth()
    {
        Gladiator *x=first;
        unsigned int h=0;
        while(x!=NULL)
        {
            if(x->getRemainingHealth()>h)
                h=x->getRemainingHealth();
            x=x->next;
        }
        return h;
    }
    void cure()
    {
       Gladiator *x=first;
        while(x!=NULL)
        {
            x->cure();
            x=x->next;
        }
    }
    void printParams()
    {

        cout << ID << ":" << getRemainingHealth() << ":" << getDamage() << ":" << getRapidity() << endl;
    }
    unsigned int getRapidity()
    {
        Gladiator *x=first;
        unsigned int r=100013;
        while(x!=NULL)
        {
            if(x->getRapidity()<r)
                r=x->getRapidity();
            x=x->next;
        }
        if(r==100013)
            r=0;
        return r;
    }
private:

    void die()
    {
        Gladiator *x=first;
        Gladiator *prev=first;
        while(x!=NULL)
        {
            x->die();
            prev=x;
            x=x->next;
            prev->next=NULL;
        }
        first=NULL;
    }
};
class Caesar
{
public:

    unsigned int amount=0;
    void judgeDeathOrLife(Gladiator* gladiator)
    {
        //cout << amount << endl;
        if(++amount%3==0)
            gladiator->die();
    }
};
class Amphitheatre
{
private:
    Caesar* caesar;
public:
    Amphitheatre(Caesar* c)
    {
        caesar=c;
    }
    void fight(Gladiator* g1, Gladiator* g2)
    {

        if(g1->getRemainingHealth()==0 || g2->getRemainingHealth()==0)
            return;
        if(g1->getRapidity()>=g2->getRapidity())
        {

            int i;
            for(i=0;i<20;i++)
            {
                g2->takeDamage(g1->getDamage());
                if(g2->getRemainingHealth()<10)
                {
                    //Caesar->judgeDeathOrLife(g2);
                   // g1->printParams();
                    //g2->printParams();
                    break;
                }
                g1->takeDamage(g2->getDamage());
                if(g1->getRemainingHealth()<10)
                {
                    if(g1->getRemainingHealth()!=0)
                    caesar->judgeDeathOrLife(g1);
                    //g1->printParams();
                    //g2->printParams();
                    break;
                }
                g1->printParams();
                g2->printParams();
            }
            //g1->printParams();
            //g2->printParams();
            if(i==20)
            {
                caesar->judgeDeathOrLife(g1);
                caesar->judgeDeathOrLife(g2);
            }
            if(g1->getRemainingHealth()>0)
            {
                g1->applyWinnerReward();
                g1->cure();
            }
            if(g2->getRemainingHealth()>0)
            {
                g2->applyWinnerReward();
                g2->cure();
            }
            g1->printParams();
            g2->printParams();
        }else
        {
            //cout << "g2";
            int i;
            for(i=0;i<20;i++)
            {
                g1->takeDamage(g2->getDamage());
                if(g1->getRemainingHealth()<10)
                {
                    //Caesar->judgeDeathOrLife(g2);
                    //g2->printParams();
                    //g1->printParams();
                    break;
                }
                g2->takeDamage(g1->getDamage());
                if(g2->getRemainingHealth()<10)
                {
                    if(g2->getRemainingHealth()!=0)
                    caesar->judgeDeathOrLife(g2);
                    //g2->printParams();
                    //g1->printParams();
                    break;
                }
                g2->printParams();
                g1->printParams();
            }
            if(i==20)
            {
                caesar->judgeDeathOrLife(g2);
                caesar->judgeDeathOrLife(g1);
            }
            if(g2->getRemainingHealth()>0)
            {
                g2->applyWinnerReward();
                g2->cure();
            }
            if(g1->getRemainingHealth()>0)
            {
                g1->applyWinnerReward();
                g1->cure();
            }
            g2->printParams();
            g1->printParams();
        }
    }
};



int main() {
    Human h1("a");
    Human h2("b");
    Human h3("c");
    Human h4("d");

    Beast b1("e");
    Beast b2("f");
    Beast b3("g");
    Beast b4("h");

    Squad s1;
    Squad s2;

    Caesar c;
    Amphitheatre a(&c);

    Gladiator* g1(&h1);
    Gladiator* g2(&h2);
    Gladiator* g3(&h3);
    Gladiator* g4(&h4);
    Gladiator* g5(&b1);
    Gladiator* g6(&b2);
    Gladiator* g7(&b3);
    Gladiator* g8(&b4);

    s1.addGladiator(g1);
    s1.addGladiator(g2);
    s1.addGladiator(g5);
    s1.addGladiator(g6);
    s1.printParams();

    s2.addGladiator(g3);
    s2.addGladiator(g4);
    s2.addGladiator(g7);
    s2.addGladiator(g8);
    s2.printParams();

    cout << endl;

    Gladiator* g9(&s1);
    Gladiator* g10(&s2);

    a.fight(g9, g10);

    cout << endl;

    s1.printParams();
    s2.printParams();
}

