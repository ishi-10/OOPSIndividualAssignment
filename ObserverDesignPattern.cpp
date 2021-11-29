#include<iostream>
#include<bits/stdc++.h>

using namespace std;


/*
.
Observer class is an abstract class which
acts as an interface. It is inherited by the
subscriber class.
.
*/
class observer{
public:
    virtual void notify(string news)=0;// pure virtual function
    // overwritten in subscriber class
};

/*
.
subscriber class has to be notified
everytime a new news update is added to the portal
It implements the observer interface
.
*/
class subscriber: public observer{
private:
    string name; // name of the subscriber
    vector<string>allNews; // vector to store all the news updates
public:
    subscriber(string n){
        name=n;
        cout<<"New subscriber created with name: "<<name<<" \n";
    }
    string getName(){
        return name;
    }
    void notify(string news);
};


/*
.
subject class is the class which keeps a track of all the
registered subscribers for a news portal.
This class adds and removes subscribers for a news portal.
It is responsible for updating the subscribers whenever a
change occurs in news portal
.
*/
class subject{
private:
    vector<subscriber* >listOfSubscribers;
    // vector to store the list of subscribers for a news portal
public:
    void registerSubscriber(subscriber* sub);
    void removeSubscriber(subscriber* sub);
    void notifySubscriber(string news);
};

/*
.
newsPortal class is the real class that inherits the
subject class.
Whenever a new news is added, addNews() function
triggers the notifySubscriber() function of the subject class,
which in turn notifies every subscriber.
.
*/
class newsPortal : public subject{
public:
    newsPortal(){
        cout<<"News Portal created\n";
    }
    void addNews(string news);
};

/*
.
Functions of subject class
.
*/

// function to register new subscribers
void subject::registerSubscriber(subscriber *sub){
    listOfSubscribers.push_back(sub);
    cout<<sub->getName()<<" successfully subscribed\n";
}

// function to remove a certain subscriber
void subject::removeSubscriber(subscriber *sub){
    for (auto i=listOfSubscribers.begin();i!=listOfSubscribers.end();i++) {
        if (*i==sub) {
            listOfSubscribers.erase(i);
            cout<<sub->getName()<<" successfully unsubscribed\n";
            break;
        }
    }
}

// function to notify every subscriber whenever a news update happens
void subject::notifySubscriber(string news){
    for (auto i=listOfSubscribers.begin();i!=listOfSubscribers.end();i++) {
        (*i)->notify(news);
    }
}

/*
.
Functions of newsPortal class
.
*/

// function to add a news update
void newsPortal::addNews(string news){
    notifySubscriber(news);
}


/*
.
Functions of subscriber class
.
*/

// function to add the news update into the news feed of
// the subscriber and ntifies the subscriber of the change
void subscriber::notify(string news){
    allNews.push_back(news);
    cout<<"NEWS UPDATE FOR "<<name<<" !!\n";
    cout<<news<<"\n";
    cout<<"\n";
}

//main function
int main(){

    //creating a news portal
    newsPortal newPortal;

    //creating four subscribers
    subscriber sub1("Ishita");
    subscriber sub2("Priyanka");
    subscriber sub3("Ritik");
    subscriber sub4("Sakshi");

    //registering two subscribers to the newPortal
    newPortal.registerSubscriber(&sub1);
    newPortal.registerSubscriber(&sub2);

    //sending a news update to the portal which in turn notifies all the subscribers of the change
    cout<<"Sending a news update to the portal------------------------\n";
    newPortal.addNews("Messi scores a hat-trick to break Pelé’s international goals record!");

    //removing a subscriber
    newPortal.removeSubscriber(&sub1);

    //adding two new subscribers
    newPortal.registerSubscriber(&sub3);
    newPortal.registerSubscriber(&sub4);

    //sending a news update to the portal
    cout<<"Sending a news update to the portal--------------------------\n";
    newPortal.addNews("Floods are causing heavy destruction in Tamil Nadu.");

    return 0;
}
