#include <iostream>
#include <string>

using namespace std;

class IArticlePub;
class IArticleSub;

class IArticlePub{
private:
    string pub_name;
    int pub_id;
    string recent_contents;
    IArticleSub* sub_list[5];
    int numOfSub = 0;
    static int static_pub_counter;
public:
    IArticlePub(const string name);
    IArticlePub(const string name, const string con);
    ~IArticlePub();
    void NotifyAttach(IArticleSub* subscriber);
    void NotifyAttachResponse(IArticleSub* subscriber);
    void NotifyDetach(IArticleSub* subscriber);
    void NotifyDetachResponse(IArticleSub* subscriber);
    void updatePubContents(string c);
    void Notify();
    int getPubID();
    string getPubName();
    int getSubSize();
    void PrintAllSub();
};

class IArticleSub {
private:
    string sub_name;
    int sub_id;
    string recent_article_contents;
    IArticlePub* recent_article_pub;
    IArticlePub* pub_list[5];
    int numOfPub = 0;
    static int static_sub_counter;
public:
    IArticleSub(string name);
    IArticleSub(string name, IArticlePub* articlePub);
    ~IArticleSub();
    void Attach(IArticlePub* publisher);
    void AttachResponse(IArticlePub* publisher);
    void Detach(IArticlePub* p_pub);
    void DetachResponse(IArticlePub* p_pub);
    void Update(IArticlePub* publisher, const string contents);
    void PrintContents();
    string getSubName();
    int getSubID();
    int getPubSize();
    void PrintAllPub();
};

IArticlePub::IArticlePub(const string name) {
    pub_name = name;
    pub_id = static_pub_counter;
    static_pub_counter++;
    recent_contents = "";
    cout << "[Constructor]New Pub Created: ("<< pub_name << "," << pub_id << ")" << endl;
}
IArticlePub::IArticlePub(const string name, const string con) {
    pub_name = name;
    pub_id = static_pub_counter;
    static_pub_counter++;
    recent_contents = con;
    cout << "[Constructor]New Pub Created: ("<< pub_name << "," << pub_id << ")" << endl;
}
IArticlePub::~IArticlePub() {
    cout << "IArticlePub Destructor called" << endl;
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->DetachResponse(this);
    }
}
void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    bool exist_sub = false;
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            exist_sub = true;
            break;
        }
    }
    if (exist_sub == true) {
        cout << "error: the subscriber already exists in the publisher’s subscriber list" << endl;
    }
    else {
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
        sub_list[numOfSub] = subscriber;
        numOfSub++;
        subscriber->AttachResponse(this);
    }
}
void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    bool exist_sub = false;
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            exist_sub = true;
            break;
        }
    }
    if (exist_sub == true) {
        cout << "error: the subscriber already exists in the publisher’s subscriber list" << endl;
    }
    else {
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
        sub_list[numOfSub] = subscriber;
        numOfSub++;
    }
}
void IArticlePub::NotifyDetach(IArticleSub* subscriber) {
    bool exist_sub = false;
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            exist_sub = true;
            break;
        }
    }
    if (exist_sub == true) {
        cout << "[Pub] (" << getPubName() << "," << getPubID() << ") detach [Sub] (" << subscriber->getSubName() << "," << subscriber->getSubID() << ")" << endl;
        for (int i = 0; i < numOfSub; i++) {
            if (sub_list[i]->getSubID() == subscriber->getSubID()) {
                for (int j = i; j < numOfSub-1 ; j++) {
                    sub_list[j] = sub_list[j+1];
                }
                sub_list[numOfSub] = nullptr;
                numOfSub--;
                subscriber->DetachResponse(this);
                break;
            }
        }
    }
    else {
        cout << "error: the subscriber doesn’t exist in the publisher’s subscriber list" << endl;
    }
}
void IArticlePub::NotifyDetachResponse(IArticleSub* subscriber) {
    bool exist_sub = false;
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            exist_sub = true;
            break;
        }
    }
    if (exist_sub == true) {
        cout << "[Pub] (" << getPubName() << "," << getPubID() << ") detach [Sub] (" << subscriber->getSubName() << "," << subscriber->getSubID() << ")" << endl;
        for (int i = 0; i < numOfSub; i++) {
            if (sub_list[i]->getSubID() == subscriber->getSubID()) {
                for (int j = i; j < numOfSub-1 ; j++) {
                    sub_list[j] = sub_list[j+1];
                }
                sub_list[numOfSub] = nullptr;
                numOfSub--;
                break;
            }
        }
    }
    else {
        cout << "error: the subscriber doesn’t exist in the publisher’s subscriber list" << endl;
    }
}
void IArticlePub::updatePubContents(string c) {
    recent_contents = c;
    Notify();
}
void IArticlePub::Notify() {
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->Update(this, recent_contents);
    }
}
int IArticlePub::getPubID() {
    return pub_id;
}
string IArticlePub::getPubName() {
    return pub_name;
}
int IArticlePub::getSubSize() {
    return numOfSub;
}
void IArticlePub::PrintAllSub() {
    //존재하지 않는 경우
    cout << "All Sub of (" << getPubName() << "," << getPubID() << "): ";
    for (int i = 0; i < numOfSub; i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
}
int IArticlePub::static_pub_counter = 1;

IArticleSub::IArticleSub(string name) {
    sub_name = name;
    sub_id = static_sub_counter;
    static_sub_counter++;
    recent_article_contents = "";
    cout << "[Constructor]New Sub Created: ("<< sub_name << "," << sub_id << ")" << endl;
}
IArticleSub::IArticleSub(string name, IArticlePub* articlePub) {
    sub_name = name;
    sub_id = static_sub_counter;
    static_sub_counter++;
    recent_article_contents = "";
    cout << "[Constructor]New Sub Created: ("<< sub_name << "," << sub_id << ")" << endl;
    Attach(articlePub);
    //recent_article_pub = ;
    
}
IArticleSub::~IArticleSub() {
    cout << "IArticleSub Destructor called" << endl;
    for (int i = 0; i < numOfPub; i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }
}
void IArticleSub::Attach(IArticlePub* publisher) {
    cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
    pub_list[numOfPub] = publisher;
    numOfPub++;
    publisher->NotifyAttachResponse(this);
    
}
void IArticleSub::AttachResponse(IArticlePub* publisher) {
    cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
    pub_list[numOfPub] = publisher;
    numOfPub++;
}
void IArticleSub::Detach(IArticlePub* p_pub) {
    cout << "[Sub] (" << getSubName() << "," << getSubID() << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i]->getPubID() == p_pub->getPubID()) {
            for (int j = i; j < numOfPub-1 ; j++) {
                pub_list[j] = pub_list[j+1];
            }
            pub_list[numOfPub] = nullptr;
            numOfPub--;
            p_pub->NotifyDetachResponse(this);
            break;
        }
    }
}
void IArticleSub::DetachResponse(IArticlePub* p_pub) {
    cout << "[Sub] (" << getSubName() << "," << getSubID() << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i]->getPubID() == p_pub->getPubID()) {
            for (int j = i; j < numOfPub-1 ; j++) {
                pub_list[j] = pub_list[j+1];
            }
            pub_list[numOfPub] = nullptr;
            numOfPub--;
            break;
        }
    }
}
void IArticleSub::Update(IArticlePub* publisher, const string contents) {
    recent_article_pub = publisher;
    recent_article_contents = contents;
    PrintContents();
}
void IArticleSub::PrintContents() {
    cout << "Sub (" << getSubName() << "," << getSubID() << ")'s latest subscribed news is \"" << recent_article_contents <<  "\"" << " by " << recent_article_pub->getPubName() << endl;
}
string IArticleSub::getSubName() {
    return sub_name;
}
int IArticleSub::getSubID() {
    return sub_id;
}
int IArticleSub::getPubSize() {
    return numOfPub;
}
void IArticleSub::PrintAllPub() {
    cout << "All Pub of (" << getSubName() << "," << getSubID() << "): ";
    for (int i = 0; i < numOfPub; i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}
int IArticleSub::static_sub_counter = 1;

