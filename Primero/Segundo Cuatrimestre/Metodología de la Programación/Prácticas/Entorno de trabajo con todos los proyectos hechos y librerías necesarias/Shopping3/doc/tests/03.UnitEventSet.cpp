/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <string>
#include <fstream>
#include "DateTime.h"
#include "Event.h"
#include "gtest/gtest.h"
#include "MPTests.h"
#include "EventSet.h"

using namespace std;

#define TODAY "2021-02-15 18:51:00 UTC"

string format(string f, int v);

#define MAXUSERS 10
#define MAXBRANDS 20
#define USER(number, B, U) "User_" + format("%03d", (1+ number / B))
#define BRAND(number, B, U) "Brand_" + std::to_string(1+i % B)

EventSet & IndexBuild(EventSet &es, int NBRANDS, int MUSERS);

EventSet & addMultiple(EventSet &es, int n) {
    Event ev;
    ifstream fi("./tests/validation/ECommerce_all_all_500.input");
    string line;

    if (fi) {
        //    getline(fi, line); // to take of \n    
        Event one;
        for (int i = 0; i < n; i++) {
            getline(fi, line); // to take of \n
            one.set(line); // Si viola alguna regla integridad, 
            // entonces tupla por defecto
            if (!one.isEmpty())
                es.add(one);
        }
    }
    return es;
}

TEST_F(_01_Basics, EventSet_Constructor) {
    EventSet es;

    SKIP_ASSERT_EQ_R(0, es.size()) << " A newly created instance of EventSet must have size = 0" << endl;
    SKIP_ASSERT_STREQ_R("0 ", es.to_string().c_str()) << " A newly created instance of EventSet must ha a to_string empty '0'" << endl;
}

TEST_F(_01_Basics, EventSet_add_event) {
    EventSet es;
    Event e;
    string expected;
    int count1, count2;

    es.add(e);
    expected = "1 ";
    expected += e.to_string() + "\n";
    SKIP_ASSERT_EQ_R(1, es.size()) << " Adding an event to a newly created instance of EventSet must have size = 1" << endl;
    SKIP_ASSERT_STREQ_R(expected.c_str(), es.to_string().c_str()) << "Adding the default event to an empty event set must have a to_string equal to the default event" << endl;

    addMultiple(es, 25);
    count1 = es.size();
    es.add(e);
    count2 = count1 + 1;
    SKIP_ASSERT_EQ_R(count2, es.size()) << " Adding 1 event to a filled EventSet increases its size in 1" << endl;

}

TEST_F(_01_Basics, EventSet_add_line) {
    EventSet es;
    Event e;
    string expected;
    int count1, count2;

    es.add(e.to_string());
    expected = "1 ";
    expected += e.to_string() + "\n";
    SKIP_ASSERT_EQ_R(1, es.size()) << " Adding a line to a newly created instance of EventSet must have size = 1" << endl;
    SKIP_ASSERT_STREQ_R(expected.c_str(), es.to_string().c_str()) << "Adding the default event, as a line, to an empty event set must have a to_string equal to the default event" << endl;

    addMultiple(es, 25);
    count1 = es.size();
    es.add(e.to_string());
    count2 = count1 + 1;
    SKIP_ASSERT_EQ_R(count2, es.size()) << " Adding 1 event, as a line, to a filled EventSet increases its size in 1" << endl;

}

TEST_F(_01_Basics, EventSet_at_basic) {
    EventSet es;
    Event e, event_returned;
    string expected;
    int count1, count2;

    es.add(e);
    addMultiple(es, 2);
    es.add(e);
    addMultiple(es, 4);
    event_returned = es.at(0);
    SKIP_ASSERT_STREQ_R(e.to_string().c_str(), event_returned.to_string().c_str()) << "Querying the event at the 0 position should match with the first event added to the EventSet" << endl;
    event_returned = es.at(3);
    SKIP_ASSERT_STREQ_R(e.to_string().c_str(), event_returned.to_string().c_str()) << "Querying the event at the middle position should match with the event added which was added at that point" << endl;
}

TEST_F(_02_Intermediate, EventSet_add_event_partial) {
    EventSet es;
    Event e;
    string expected;
    int count1, count2;

    addMultiple(es, MAXEVENT);
    addMultiple(es, MAXEVENT);
    SKIP_ASSERT_TRUE_R(MAXEVENT >= es.size()) << " Adding MAXEVENT events to a newly created EventSet increases its size in MAXEVENT" << endl;
}

TEST_F(_02_Intermediate, EventSet_at_intermediate) {
    DateTime date;
    EventSet es;
    Event e, event_returned, last_event;
    string expected, before, later, mark;
    int count1, count2, position;

    addMultiple(es, 50);
    es.add(e);
    event_returned = es.at(es.size() - 1);
    SKIP_ASSERT_STREQ_R(e.to_string().c_str(), event_returned.to_string().c_str()) << "Querying the event at the last position should match with the last event added to the EventSet" << endl;
    es.add(e);
    mark = "test";
    position = es.size() - 1;
    event_returned = es.at(position);
    event_returned.setUserID(mark);
    SKIP_ASSERT_STRNE_R(mark.c_str(), es.at(position).getUserID().c_str()) << "Accessing EventSet at() a certain position and changing the user ID of the event, this change will remain in the EventSet itself" << endl;
    event_returned.setBrand(mark);
    SKIP_ASSERT_STRNE_R(mark.c_str(), es.at(position).getBrand().c_str()) << "Accessing EventSet at() a certain position and changing the brand of the event, this change will remain in the EventSet itself" << endl;
}

TEST_F(_03_Advanced, EventSet_add_event_full) {
    EventSet es;
    Event e;
    string expected;
    int count1, count2, returned;

    addMultiple(es, MAXEVENT - 1);
    returned = es.add(e);
    SKIP_ASSERT_EQ_R(1, returned) << " Adding one single Event events to a partly filled EventSet must return 1" << endl;
    returned = es.add(e);
    SKIP_ASSERT_EQ_R(MAXEVENT, es.size()) << " Adding one single Event events to a completely filled EventSet does not produce any change in the EventSet" << endl;
    SKIP_ASSERT_EQ_R(0, returned) << " Adding one single Event events to a completely filled EventSet must return 0" << endl;
}

TEST_F(_03_Advanced, EventSet_at_advanced) {
    DateTime date;
    EventSet es;
    Event e, last_event;
    string expected, before, later, mark;
    int count1, count2, position;

    addMultiple(es, 9);
    SKIP_ASSERT_TRUE_R(es.at(10).isEmpty()) << "Querying an EventSet beyond its legal limits gives an EMPTY event"<<endl;
    SKIP_ASSERT_TRUE_R(es.at(-1).isEmpty()) << "Querying an EventSet beyond its legal limits gives an EMPTY event"<<endl;
    SKIP_ASSERT_FALSE_R(es.at(0).isEmpty()) << "Querying an EventSet within its legal limits always gives a NON-EMPTY event"<<endl;
}

TEST_F(_03_Advanced, EventSet_externalfunctions) {
    DateTime date;
    EventSet es;
    Event e, last_event;
    string expected, before, later, mark1 = VALID_TYPES[1], mark2 = VALID_TYPES[2];
    int count1, count2, count3, position, n1, n2;
    float price;
    string dt1 = "2021-02-17 00:00:00 UTC", dt2 = "2020-02-29 00:00:00 UTC";

    count1 = 100;
    string res1[count1], res2[count1];
    count2 = 5;
    count3 = 25;
    price = 0.25;
    for (int i = 0; i < count1; i++) {
        if (i < count1 / 2)
            e.setPrice(price * 0.5);
        else
            e.setPrice(price * 1.5);
        e.setBrand(((string) "BRAND") + std::to_string(i % count2));
        e.setUserID(((string) "USER") + std::to_string(i % count3));
        es.add(e);
    }
    SKIP_ASSERT_EQ_R(count1*price, sumPrice(es)) << "sumPrice must give the sum of all prices of a given EventSet, and it doesnt " << endl;
    findUnique(es, "Brand", res1, n1);
    SKIP_ASSERT_EQ_R(count2, n1) << "UniqueBrands() must give the number of different brands, but it doesnt " << endl;
    findUnique(es, "UserID", res2, n2);
    SKIP_ASSERT_EQ_R(count3, n2) << "UniqueUsers() must give the number of different users, but it doesnt " << endl;
}

TEST_F(_03_Advanced, EventSet_write) {
    EventSet es;
    string spre, swrite, filename = "./tests/output/eventset_write.csv";
    ofstream fo(filename);
    if (fo) {
        IndexBuild(es, 5, 3);
        spre = es.to_string();
        CLEANUP(spre);
        es.write(fo);
        LOAD(swrite, filename);
        swrite = std::to_string(es.size()) + " " + swrite;
        SKIP_ASSERT_STREQ_R(spre.c_str(), swrite.c_str()) << "Any EventSet writes into a disk file exactly its to_string() without the number of events" << endl;
    } else {
        FAIL_TEST();
    }
}

TEST_F(_03_Advanced, EventSet_read) {
    EventSet es, es2;
    string swrite, spre, sread, filename = "./tests/output/eventset_write.csv";
    ofstream fo(filename);
    ifstream fi;
    if (fo) {
        IndexBuild(es, 5, 3);
        swrite = es.to_string();
        fo << swrite.substr(swrite.find(" ")) << endl;
        fo.close();
        LOAD(spre, filename);
        fi.open(filename);
        if (fi) {
            es2.read(fi,es.size());
            sread = es.to_string();
            sread = sread.substr(sread.find(" "));
            CLEANUP(sread);
            SKIP_ASSERT_STREQ_R(spre.c_str(), sread.c_str()) << "Any EventSet read from a disk file must have a to_string(), without the number of events, comparable to the content of the file" << endl;
        }
        else {
            FAIL_TEST();
        }
    } else {
        FAIL_TEST();
    }
}

